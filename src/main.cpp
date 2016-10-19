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

int main(void);

#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif

extern uint32_t wait_counter;

int main(void) {
	uint16_t temp;

	//‰ŠúÝ’è
	init_all();
	mpu6000::init_mpu6000();


	my7seg::count_down(3, 500);

	myprintf("vol -> %f\n\r", get_battery());


	motor::stanby_motor();
	wait::ms(100);
	motor::set_duty(motor_left, 20);
	motor::set_duty(motor_right, 20);

	while (1) {
		myprintf("gyro -> 0x%x\n\r", mpu6000::get_mpu6000_value(sen_gyro, axis_z));
		wait::ms(100);
	}
	return 1;
}

#ifdef __cplusplus
void abort(void) {
}
#endif
