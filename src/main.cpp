/*
 * main.cpp
 *
 *  Created on: 2016/08/21
 *      Author: Koizumi
 */

#include "stm32f4xx.h"

#include "extern_c.h"

#include "define.h"
#include "init.h"
#include "hardware.h"
#include "ad_convert.h"
#include "user.h"
#include "run.h"
#include "map.h"

int main(void);

#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif

uint32_t wait_counter = 0;
static const int16_t flog_number = 2000;
float flog[3][flog_number] = { 0 };

void interrupt_timer();			//CONTROL_PERIODごとに割り込む関数

int main(void) {
	for (int16_t j = 0; j < 10; j++) {
		for (volatile int16_t i = 0; i < 10000; i++) {
			//クロックを安定させる？
		}
	}

	//初期設定
	init_all();
	mouse::reset_count();

	myprintf("Compile DATE: %s\n\r", __DATE__);
	myprintf("Compile TIME: %s\n\r", __TIME__);

	myprintf("vol -> %f\n\r", get_battery());

	my7seg::blink(8, 200, 5);

	mpu6000::init();

	my7seg::turn_off();

	//マップをリセットする
	map::reset_wall();
	map::output_map_data(&mouse::now_map);

	encoder::yi_correct();		//YI式補正

	uint8_t select = 0;	//モード管理用
	while (1) {
		//チャタリング対策
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0)
			;
		wait::ms(100);
		if (get_battery() < 3.5) {
			while (1) {
				my7seg::light_error();
				if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0) {
					wait::ms(100);
					break;
				}
			}
		} else if (get_battery() < 3.8) {
			while (1) {
				my7seg::light_error();
				wait::ms(500);
				my7seg::turn_off();
				wait::ms(500);
				if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0) {
					wait::ms(100);
					break;
				}
			}
		}

		//チャタリング対策
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0)
			;
		wait::ms(100);

		select = mode::select_mode(8 + 1, PHOTO_TYPE::right);

		GPIO_SetBits(GPIOC, GPIO_Pin_3);	//LED2
		mouse::set_direction(0, 1);	//スラロームで方向が変化するので初期化を忘れずに
		mouse::set_place(0.045 * MOUSE_MODE, 0.045 * MOUSE_MODE);	//(0,0)の中心

		switch (select) {
		case 0:		//壁の値を読むだけ	事故防止のためにモード0は実害ない奴にしとく
			while (1) {
				myprintf("right %4.3f  ", photo::get_value(right));
				myprintf("left %4.3f  ", photo::get_value(left));
				myprintf("f_r %4.3f  ", photo::get_value(front_right));
				myprintf("f_l %4.3f  ", photo::get_value(front_left));
				myprintf("front %4.3f  ", photo::get_value(front));
				myprintf("\n\r");

				wait::ms(100);
				if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0) {
					wait::ms(100);
					break;
				}
			}
			break;

		case 1:		//探索
			mode::search_mode();
			motor::sleep_motor();
			break;

		case 2:		//最短
			//TODO パス作れなかったら抜けるように
			mode::shortest_mode();
			//path::draw_path();
			motor::sleep_motor();
			break;

		case 3:		//データ消去
			//マップをリセットする
			map::reset_wall();
			map::output_map_data(&mouse::now_map);
			break;

		case 4:		//調整用
			//encoder::yi_correct();		//YI式補正
			encoder::draw_correct(false, false);
			while (1) {
				my7seg::blink(8, 500, 1);
				if (photo::check_wall(PHOTO_TYPE::front))
					break;
			}
			my7seg::count_down(3, 500);
			mouse::run_init(true, true);

			flog[0][0] = -1;
			run::accel_run(0.09 * 6, 0, 0);
			//run::accel_run_wall_eage(0.09 * 8, SEARCH_VELOCITY, 0, 0.09 * 7);
			//run::accel_run(0.045 + 0.09, SEARCH_VELOCITY, 0);
			//run::slalom_for_search(small, MUKI_RIGHT, 0);
			//run::accel_run_wall_eage(0.09 * 8, SEARCH_VELOCITY, 0, 0.09 * 7);
			//run::accel_run(0.045* 2, 0, 0);
			//run::slalom_for_search(small, MUKI_RIGHT, 0);
			//control::stop_wall_control();
			//run::accel_run(0.045*3, 0, 0);
			//run::spin_turn(-360);
			//run::spin_turn(360);
			//flog[0][0] = -1;
			//run::accel_run(0.09 * 5, 0, 0);
			wait::ms(2000);
			motor::sleep_motor();
			my7seg::turn_off();
			break;

		case 5:		//調整用
			while (1) {
				my7seg::blink(8, 500, 1);
				if (photo::check_wall(PHOTO_TYPE::left))
					break;
			}
			my7seg::count_down(3, 500);
			//	mouse::run_init(true, false);

			flog[0][0] = -1;

			wait::ms(2000);

			motor::sleep_motor();
			my7seg::turn_off();

			break;

		case 6: {		//スラローム調整
			select = mode::select_mode(slalom_type_count, right);
			float b_dis = 0.09 * 2 * MOUSE_MODE;		//スラロームの前にどれだけ進むか
			float a_dis = 0.09 * 2 * MOUSE_MODE;		//スラロームの後にどれだけ進むか
			SLALOM_TYPE sla_type = none;
			int8_t right_or_left = MUKI_RIGHT;

			switch (select) {
			case none:
			case spin_turn:
				b_dis = 0;
				a_dis = 0;
				break;
			case small:
				sla_type = small;
				b_dis -= 0.045 * MOUSE_MODE;
				a_dis -= 0.045 * MOUSE_MODE;
				break;
			case big_90:
				sla_type = big_90;
				break;
			case big_180:
				sla_type = big_180;
				break;
			case begin_45:
				sla_type = begin_45;
				a_dis *= SQRT2;		//斜めなので√2倍
				break;
			case end_45:
				sla_type = end_45;
				b_dis *= SQRT2;		//斜めなので√2倍
				break;
			case begin_135:
				sla_type = begin_135;
				a_dis *= SQRT2;		//斜めなので√2倍
				break;
			case end_135:
				sla_type = end_135;
				b_dis *= SQRT2;		//斜めなので√2倍
				break;
			case oblique_90:
				sla_type = oblique_90;
				b_dis *= SQRT2;		//斜めなので√2倍
				a_dis *= SQRT2;		//斜めなので√2倍
				break;
			}
			if (b_dis != 0) {		//前距離0のパターン(none,spin_turn)は調整しない

				select = mode::select_mode(3, right);

				while (1) {
					my7seg::blink(8, 500, 1);
					if (photo::check_wall(PHOTO_TYPE::front))
						break;
				}
				my7seg::count_down(3, 500);
				mouse::run_init(true, true);

				flog[0][0] = -1;
				run::accel_run(b_dis,
						parameter::get_slalom(sla_type, true, select)->velocity,
						1);
				run::slalom(sla_type, right_or_left, select);
				run::accel_run(a_dis, 0, 1);
			}

			wait::ms(1000);
			motor::sleep_motor();
			my7seg::turn_off();

			break;
		}
		case 7:
			GPIO_ResetBits(GPIOC, GPIO_Pin_3);	//LED2
			while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 1) {
			}

			for (int i = 0; i < flog_number; i++) {
				myprintf("%f,%f,%f\n\r", flog[0][i], flog[1][i], flog[2][i]);
			}
			break;
		case 8: {
			map::draw_map(false);

			std::vector<std::pair<uint8_t, uint8_t> > goal;
			goal.emplace_back(std::make_pair(GOAL_x, GOAL_y));
			goal.emplace_back(std::make_pair(GOAL_x + 1, GOAL_y));
			goal.emplace_back(std::make_pair(GOAL_x, GOAL_y + 1));
			goal.emplace_back(std::make_pair(GOAL_x + 1, GOAL_y + 1));
			node_search search;
			search.input_map_data(&mouse::now_map);		//保存していたマップを読みだす
			search.set_weight_algo(based_distance);		//重みづけの方法を設定
			uint32_t temp_cnt = wait::get_count();
			step::spread_step(GOAL_x, GOAL_y, true);		//歩数マップを作製
			map::draw_map(true);
			myprintf("square cal. count->%d\n\r", wait::get_count() - temp_cnt);
			temp_cnt = wait::get_count();
			search.spread_step(goal, false);		//歩数マップを作製
			myprintf("node cal. count->%d\n\r", wait::get_count() - temp_cnt);
			search.draw_step();

			search.create_small_path(goal,std::make_pair<uint8_t, uint8_t>(0,0),north);
			search.convert_path();

			path::draw_path();
			break;
		}

		}

		GPIO_ResetBits(GPIOC, GPIO_Pin_3);	//LED2

	}
	return 1;
}

void interrupt_timer() {

	GPIO_SetBits(GPIOA, GPIO_Pin_14);

	wait_counter++;	//ms(ミリ秒)のカウントを1増加
	mouse::add_one_count_ms();
	wait::set_count(wait_counter);

	photo::interrupt(true);
	gyro::interrupt();
	accelmeter::interrupt();
	encoder::interrupt();

	mouse::interrupt();

	control::cal_delta();			//姿勢制御に用いる偏差を計算
	control::posture_control();

	control::fail_safe();

	static volatile uint16_t i = 0;
	if (i == 0) {
		if (flog[0][0] == -1) {
			i++;
		}
	} else if (i < flog_number) {
		flog[0][i] = mouse::get_place().y;
		flog[1][i] = photo::get_displacement_from_center_debag(right);//photo::get_value(right);
		flog[2][i] = photo::get_displacement_from_center_debag(left);//photo::get_value(left);
		i++;
	}else if ( i == flog_number){
		flog[0][0]=0;
		i=0;
	}

	GPIO_ResetBits(GPIOA, GPIO_Pin_14);

}

#ifdef __cplusplus
void abort(void) {
}
#endif
