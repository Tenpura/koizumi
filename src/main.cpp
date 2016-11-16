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
float flog[2][10000] = { 0 };

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

	my7seg::blink(8, 100, 5);

	myprintf("vol -> %f\n\r", get_battery());

	if (get_battery() < 3.8) {
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

	my7seg::turn_off();

	mpu6000::init_mpu6000();

	my7seg::turn_off();

	//マップをリセットする
	map::reset_wall();
	map::output_map_data(&mouse::now_map);

	uint8_t select = 0;	//モード管理用
	while (1) {
		//チャタリング対策
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0)
			;
		wait::ms(100);

		if (get_battery() < 3.8) {
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

		select = mode::select_mode(7, PHOTO_TYPE::right);

		switch (select) {
		case 0:		//壁の値を読むだけ	事故防止のためにモード0は実害ない奴にしとく
			while (1) {
				myprintf("right %d  ", photo::get_value(right));
				myprintf("left %d  ", photo::get_value(left));
				myprintf("f_r %d  ", photo::get_value(front_right));
				myprintf("f_l %d  ", photo::get_value(front_left));
				myprintf("front %d  ", photo::get_value(front));
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
			path::create_path();
			map::draw_map(false);
			run::path(0, 0);
			path::draw_path();
			//mode::shortest_mode();
			break;

		case 3:		//データ消去
			//マップをリセットする
			map::reset_wall();
			map::output_map_data(&mouse::now_map);
			break;

		case 4:		//調整用
			while (1) {
				my7seg::blink(8, 500, 1);
				if (photo::check_wall(PHOTO_TYPE::front))
					break;
			}
			my7seg::count_down(3, 500);
			mouse::run_init(true, true);
			flog[0][0] = -1;

			//control::stop_wall_control();

			run::accel_run_wall_eage(0.09 * 2, SEARCH_VELOCITY, 0, 0.09);
			//run::accel_run(0.045+0.09, SEARCH_VELOCITY, 0);
			run::slalom_for_search(small, MUKI_RIGHT, 0);
			//run::accel_run_wall_eage(0.09*5, SEARCH_VELOCITY, 0, 0.09*4.5);
			run::accel_run(0.045, 0, 0);

			//run::spin_turn(180);
			//run::fit_run(0);

			wait::ms(1000);

			motor::sleep_motor();
			my7seg::turn_off();

			while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 1) {
			}
			//map::draw_map(false);

			for (int i = 0; i < 2000; i++) {
				myprintf("%f,%f\n\r", flog[0][i], flog[1][i]);
			}
			break;

		case 5:		//調整用
			while (1) {
				my7seg::blink(8, 500, 1);
				if (photo::check_wall(PHOTO_TYPE::front))
					break;
			}
			my7seg::count_down(3, 500);
			mouse::run_init(true, true);
			flog[0][0] = -1;

			//control::stop_wall_control();

			run::accel_run_wall_eage(0.09 * 2, SEARCH_VELOCITY, 0, 0.09);
			run::accel_run(0.045, 0, 0);

			wait::ms(1000);

			motor::sleep_motor();
			my7seg::turn_off();

			while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 1) {
			}
			//map::draw_map(false);

			for (int i = 0; i < 2000; i++) {
				myprintf("%f,%f\n\r", flog[0][i], flog[1][i]);
			}
			break;


		case 6:
			map::draw_map(false);
			break;

		}

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
	if (motor::isEnable()) {
		if (i == 0) {
			if (flog[0][0] == -1) {
				i++;
			}
		} else if (i < 10000) {
			flog[0][i] = mouse::get_distance_m();
			flog[1][i] = photo::get_value(left);
			i++;
			GPIO_ResetBits(GPIOA, GPIO_Pin_14);

		}
	}

	GPIO_ResetBits(GPIOA, GPIO_Pin_14);

}

#ifdef __cplusplus
void abort(void) {
}
#endif
