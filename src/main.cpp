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

	//初期設定
	init_all();
	mpu6000::init_mpu6000();
	mouse::reset_count();

	my7seg::count_down(3, 500);

	myprintf("vol -> %f\n\r", get_battery());

	while (get_battery() < 3.9) {
		my7seg::light_error();
		wait::ms(500);
		my7seg::turn_off();
		wait::ms(500);
	}

	myprintf("whi am i -> 0x%x\n\r", mpu6000::read_spi(0xf5));
	myprintf("whi am i -> 0x%x\n\r", mpu6000::read_spi(0xf5));
	myprintf("whi am i -> 0x%x\n\r", mpu6000::read_spi(0xf5));

	motor::stanby_motor();

	motor::set_duty(motor_left,20);
	motor::set_duty(motor_right,20);

	wait::ms(100);
	control::start_control();
	mouse::set_acceleration(0);
	mouse::set_ideal_velocity(0);
	mouse::set_angular_acceleration(0);
	mouse::set_ideal_angular_velocity(0);
	control::reset_delta();

	mouse::set_distance_m(0);

	run::accel_run(0.18,0,0);

/*
	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)==1){
		my7seg::light(3);
		myprintf("right %.4f,left %.4f, ave %f\n\r",encoder::right_velocity,encoder::left_velocity,encoder::velocity);
		wait::ms(100);
	}
	*/
	wait::ms(10000);
	motor::sleep_motor();
	my7seg::turn_off();

	for(int i=0; i<10000;i++){
		myprintf("%f,%f\n\r",flog[0][i],flog[1][i]);
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
	wait_counter++;	//ms(ミリ秒)のカウントを1増加
	mouse::add_one_count_ms();

	/*
	 gyro::set_gyro();				//gyroの値を取得
	 gyro::cal_angle();				//gyroから角度を計算
	 gyro::cal_angular_velocity();	//gyroから角速度を計算[°/s]
	 */
	encoder::interrupt_encoder();

	//速度と距離を計算
	mouse::cal_accel();
	mouse::cal_distance();

	control::cal_delta();			//姿勢制御に用いる偏差を計算
	control::posture_control();

//	control::fail_safe();


	 static uint16_t i=0;
	 if(motor::isEnable()){
	 if(i<10000){
		 flog[0][i] = encoder::left_velocity;
		 flog[1][i] = encoder::right_velocity;
	 i++;
	 }
	 }


}

#ifdef __cplusplus
void abort(void) {
}
#endif
