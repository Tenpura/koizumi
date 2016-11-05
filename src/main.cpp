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
	for (int16_t j = 0; j < 100; j++) {
		for (volatile int16_t i = 0; i < 10000; i++) {
			//クロックを安定させる？
		}
	}

	//初期設定
	init_all();
	mouse::reset_count();

	myprintf("vol -> %f\n\r", get_battery());
	my7seg::turn_off();
	if (get_battery() < 4) {
		while (1) {

			my7seg::light_error();
			wait::ms(500);

			my7seg::turn_off();
			wait::ms(500);

			if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0) {
				break;
			}

		}
	}

/*
	while(1){
		if(photo::check_wall(right)) GPIO_ResetBits(GPIOH, GPIO_Pin_1);	//Pinを1に
		else GPIO_SetBits(GPIOH, GPIO_Pin_1);	//Pinを1に

		if(photo::check_wall(front)) GPIO_ResetBits(GPIOC, GPIO_Pin_2);	//Pinを1に
		else GPIO_SetBits(GPIOC, GPIO_Pin_2);	//Pinを1に

		if(photo::check_wall(left)) GPIO_ResetBits(GPIOC, GPIO_Pin_15);	//Pinを1に
		else GPIO_SetBits(GPIOC, GPIO_Pin_15);	//Pinを1に

		wait::ms(10);



	}
*/
	mpu6000::init_mpu6000();

	while (1) {
		myprintf("right %d  ", photo::get_value(right));
		myprintf("left %d  ", photo::get_value(left));
		myprintf("f_r %d  ", photo::get_value(front_right));
		myprintf("f_l %d  ", photo::get_value(front_left));
		myprintf("front %d  ", photo::get_value(front));
		myprintf("\n\r");

		wait::ms(100);

		if(photo::get_value(front)>(parameter::get_min_wall_photo(front)*1.5)){
				break;
			}


	}



	my7seg::count_down(3, 1000);




	while(photo::get_value(front)<(parameter::get_min_wall_photo(front)*1.5)){
		my7seg::blink(8,100,1);
	}

	my7seg::turn_off();

	map::reset_wall();
	map::output_map_data(&mouse::now_map);
	map::input_map_data(&mouse::now_map);

	mouse::set_position(0, 0);
	mouse::set_direction(MUKI_UP);

	my7seg::count_down(3,500);
	mouse::run_init(true,false);


	my7seg::turn_off();

//	adachi::left_hand_method(GOAL_x, GOAL_y);
//	adachi::adachi_method_spin(GOAL_x, GOAL_y);


	flog[0][0] = -1;
	run::accel_run(0.09 * 2, 0, 0);
	//run::spin_turn(360);
	my7seg::light(5);

	wait::ms(1000);


	motor::sleep_motor();
	my7seg::turn_off();

	while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 1) {
	}

	for (int i = 0; i < 2000; i++) {
		myprintf("%f,%f\n\r", flog[0][i], flog[1][i]);
	}

	/*
	 while (1) {
	 //myprintf("gyro -> 0x%x\n\r", mpu6000::get_mpu6000_value(sen_gyro, axis_z));
	 myprintf("%f \n\r",encoder::get_velocity());
	 //TIM2が左で前転カウントアップ、TIM3が右で前転カウントダウン
	 wait::ms(100);
	 }
	 */
	return 1;
}

void interrupt_timer() {
	GPIO_SetBits(GPIOA,GPIO_Pin_14);

	wait_counter++;	//ms(ミリ秒)のカウントを1増加
	mouse::add_one_count_ms();

	photo::interrupt(true);

	gyro::interrupt_gyro();				//gyroの値を取得
	gyro::cal_angular_velocity();	//gyroから角速度を計算[°/s]
	gyro::cal_angle();				//gyroから角度を計算

	accelmeter::interrupt();
	encoder::interrupt_encoder();

	mouse::interrupt();

	control::cal_delta();			//姿勢制御に用いる偏差を計算
	control::posture_control();

//	control::fail_safe();

	static volatile uint16_t i = 0;
	if (motor::isEnable()) {
		if (i == 0) {
			if (flog[0][0] == -1) {
				i++;
			}
		} else if (i < 10000) {
			flog[0][i] = encoder::get_velocity();//gyro::get_angular_velocity();//encoder::get_velocity();
			flog[1][i] = mouse::get_ideal_velocity();//mouse::get_ideal_angular_velocity();
			i++;
			GPIO_ResetBits(GPIOA,GPIO_Pin_14);

		}
	}


	GPIO_ResetBits(GPIOA,GPIO_Pin_14);

}

#ifdef __cplusplus
void abort(void) {
}
#endif
