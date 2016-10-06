/*
 * hardware.cpp
 *
 *  Created on: 2015/06/13
 *      Author: Koizumi
 */

#include"hardware.h"

//自作7セグ関連

void my7seg::light(const unsigned char number) {

	//7セグで表示できるわけねえだろ！
	if (number > 9) {
		//error
		light_error();
		return;
	}
	switch (number) {

	case 0:
		GPIO_SetBits(GPIOB, GPIO_Pin_4);	//LED7
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);	//LED3
		GPIO_ResetBits(GPIOC, GPIO_Pin_2);	//LED8
		GPIO_ResetBits(GPIOC, GPIO_Pin_3);	//LED2
		GPIO_ResetBits(GPIOC, GPIO_Pin_14);	//LED5
		GPIO_ResetBits(GPIOC, GPIO_Pin_15);	//LED6
		GPIO_ResetBits(GPIOH, GPIO_Pin_0);	//LED9
		GPIO_ResetBits(GPIOH, GPIO_Pin_1);	//LED4
		break;
	case 1:
		GPIO_SetBits(GPIOB, GPIO_Pin_4);	//LED7
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);	//LED3
		GPIO_SetBits(GPIOC, GPIO_Pin_2);	//LED8
		GPIO_ResetBits(GPIOC, GPIO_Pin_3);	//LED2
		GPIO_SetBits(GPIOC, GPIO_Pin_14);	//LED5
		GPIO_SetBits(GPIOC, GPIO_Pin_15);	//LED6
		GPIO_SetBits(GPIOH, GPIO_Pin_0);	//LED9
		GPIO_ResetBits(GPIOH, GPIO_Pin_1);	//LED4
		break;
	case 2:
		GPIO_ResetBits(GPIOB, GPIO_Pin_4);	//LED7
		GPIO_SetBits(GPIOB, GPIO_Pin_12);	//LED3
		GPIO_ResetBits(GPIOC, GPIO_Pin_2);	//LED8
		GPIO_ResetBits(GPIOC, GPIO_Pin_3);	//LED2
		GPIO_ResetBits(GPIOC, GPIO_Pin_14);	//LED5
		GPIO_SetBits(GPIOC, GPIO_Pin_15);	//LED6
		GPIO_ResetBits(GPIOH, GPIO_Pin_0);	//LED9
		GPIO_ResetBits(GPIOH, GPIO_Pin_1);	//LED4
		break;
	case 3:
		GPIO_ResetBits(GPIOB, GPIO_Pin_4);	//LED7
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);	//LED3
		GPIO_ResetBits(GPIOC, GPIO_Pin_2);	//LED8
		GPIO_ResetBits(GPIOC, GPIO_Pin_3);	//LED2
		GPIO_SetBits(GPIOC, GPIO_Pin_14);	//LED5
		GPIO_SetBits(GPIOC, GPIO_Pin_15);	//LED6
		GPIO_ResetBits(GPIOH, GPIO_Pin_0);	//LED9
		GPIO_ResetBits(GPIOH, GPIO_Pin_1);	//LED4
		break;
	case 4:
		GPIO_ResetBits(GPIOB, GPIO_Pin_4);	//LED7
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);	//LED3
		GPIO_SetBits(GPIOC, GPIO_Pin_2);	//LED8
		GPIO_ResetBits(GPIOC, GPIO_Pin_3);	//LED2
		GPIO_SetBits(GPIOC, GPIO_Pin_14);	//LED5
		GPIO_ResetBits(GPIOC, GPIO_Pin_15);	//LED6
		GPIO_SetBits(GPIOH, GPIO_Pin_0);	//LED9
		GPIO_ResetBits(GPIOH, GPIO_Pin_1);	//LED4
		break;
	case 5:
		GPIO_ResetBits(GPIOB, GPIO_Pin_4);	//LED7
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);	//LED3
		GPIO_ResetBits(GPIOC, GPIO_Pin_2);	//LED8
		GPIO_ResetBits(GPIOC, GPIO_Pin_3);	//LED2
		GPIO_SetBits(GPIOC, GPIO_Pin_14);	//LED5
		GPIO_ResetBits(GPIOC, GPIO_Pin_15);	//LED6
		GPIO_ResetBits(GPIOH, GPIO_Pin_0);	//LED9
		GPIO_SetBits(GPIOH, GPIO_Pin_1);	//LED4
		break;
	case 6:
		GPIO_ResetBits(GPIOB, GPIO_Pin_4);	//LED7
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);	//LED3
		GPIO_ResetBits(GPIOC, GPIO_Pin_2);	//LED8
		GPIO_ResetBits(GPIOC, GPIO_Pin_3);	//LED2
		GPIO_ResetBits(GPIOC, GPIO_Pin_14);	//LED5
		GPIO_ResetBits(GPIOC, GPIO_Pin_15);	//LED6
		GPIO_ResetBits(GPIOH, GPIO_Pin_0);	//LED9
		GPIO_SetBits(GPIOH, GPIO_Pin_1);	//LED4
		break;
	case 7:
		GPIO_SetBits(GPIOB, GPIO_Pin_4);	//LED7
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);	//LED3
		GPIO_SetBits(GPIOC, GPIO_Pin_2);	//LED8
		GPIO_ResetBits(GPIOC, GPIO_Pin_3);	//LED2
		GPIO_SetBits(GPIOC, GPIO_Pin_14);	//LED5
		GPIO_ResetBits(GPIOC, GPIO_Pin_15);	//LED6
		GPIO_ResetBits(GPIOH, GPIO_Pin_0);	//LED9
		GPIO_ResetBits(GPIOH, GPIO_Pin_1);	//LED4
		break;
	case 8:
		GPIO_ResetBits(GPIOB, GPIO_Pin_4);	//LED7
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);	//LED3
		GPIO_ResetBits(GPIOC, GPIO_Pin_2);	//LED8
		GPIO_ResetBits(GPIOC, GPIO_Pin_3);	//LED2
		GPIO_ResetBits(GPIOC, GPIO_Pin_14);	//LED5
		GPIO_ResetBits(GPIOC, GPIO_Pin_15);	//LED6
		GPIO_ResetBits(GPIOH, GPIO_Pin_0);	//LED9
		GPIO_ResetBits(GPIOH, GPIO_Pin_1);	//LED4
		break;
	case 9:
		GPIO_ResetBits(GPIOB, GPIO_Pin_4);	//LED7
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);	//LED3
		GPIO_ResetBits(GPIOC, GPIO_Pin_2);	//LED8
		GPIO_ResetBits(GPIOC, GPIO_Pin_3);	//LED2
		GPIO_SetBits(GPIOC, GPIO_Pin_14);	//LED5
		GPIO_ResetBits(GPIOC, GPIO_Pin_15);	//LED6
		GPIO_ResetBits(GPIOH, GPIO_Pin_0);	//LED9
		GPIO_ResetBits(GPIOH, GPIO_Pin_1);	//LED4
		break;
	}
}

void my7seg::turn_off() {
	GPIO_SetBits(GPIOB, GPIO_Pin_4);	//LED7
	GPIO_SetBits(GPIOB, GPIO_Pin_12);	//LED3
	GPIO_SetBits(GPIOC, GPIO_Pin_2);	//LED8
	GPIO_SetBits(GPIOC, GPIO_Pin_3);	//LED2
	GPIO_SetBits(GPIOC, GPIO_Pin_14);	//LED5
	GPIO_SetBits(GPIOC, GPIO_Pin_15);	//LED6
	GPIO_SetBits(GPIOH, GPIO_Pin_0);	//LED9
	GPIO_SetBits(GPIOH, GPIO_Pin_1);	//LED4
}

void my7seg::light_error() {
	GPIO_ResetBits(GPIOB, GPIO_Pin_4);	//LED7
	GPIO_SetBits(GPIOB, GPIO_Pin_12);	//LED3
	GPIO_ResetBits(GPIOC, GPIO_Pin_2);	//LED8
	GPIO_ResetBits(GPIOC, GPIO_Pin_3);	//LED2
	GPIO_ResetBits(GPIOC, GPIO_Pin_14);	//LED5
	GPIO_ResetBits(GPIOC, GPIO_Pin_15);	//LED6
	GPIO_ResetBits(GPIOH, GPIO_Pin_0);	//LED9
	GPIO_SetBits(GPIOH, GPIO_Pin_1);	//LED4
}

void my7seg::blink(const unsigned char number,
		const unsigned short blink_cycle_ms,
		const unsigned short repeat_count) {
	for (int i = 0; i < repeat_count; i++) {
		light(number);
		wait::ms(blink_cycle_ms);
		turn_off();
		wait::ms(blink_cycle_ms);
	}
}

void my7seg::count_down(const unsigned char start_number,
		const unsigned short cycle_ms) {
	for (int i = start_number; i > 0; i--) {
		light(i);
		wait::ms(cycle_ms);
	}
	light(0);
}

//motor関連
signed char motor::right_duty = 0, motor::left_duty = 0;
const char motor::MAX_DUTY = 100;

void motor::set_duty(const MOTOR_SIDE side, const signed short set_duty) {
	signed short duty = 0;		//一時的な保存

	//上限を切る
	if (set_duty > MAX_DUTY) {
		duty = MAX_DUTY;
	} else if (set_duty < -MAX_DUTY) {
		duty = -MAX_DUTY;
	}

	static TIM_OCInitTypeDef TIM_OC_InitStructure;
	TIM_OC_InitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OC_InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC_InitStructure.TIM_OutputState = TIM_OutputState_Enable;

	TIM_OC_InitStructure.TIM_Pulse = static_cast <uint32_t> (MAX_PERIOD * duty * 0.01);	//dutyに応じてカウントを変更

	if (side == motor_left) {

		if (set_duty == 0) {					//0のときはstop
			TIM_OC_InitStructure.TIM_Pulse = 0;		//duty0の時は一応0を代入しておく

			TIM_OC1Init(TIM4, &TIM_OC_InitStructure);		//TIM4のCH1
			TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
			TIM_OC2Init(TIM4, &TIM_OC_InitStructure);		//TIM4のCH2
			TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

		} else if (set_duty > 0) {				//正のときは正転
			TIM_OC1Init(TIM4, &TIM_OC_InitStructure);		//TIM4のCH1
			TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

			TIM_OC_InitStructure.TIM_Pulse = 0;		//電位差を作るため、片方は0に
			TIM_OC2Init(TIM4, &TIM_OC_InitStructure);		//TIM4のCH2
			TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

		} else {									//負のときは逆転
			TIM_OC2Init(TIM4, &TIM_OC_InitStructure);		//TIM4のCH2
			TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

			TIM_OC_InitStructure.TIM_Pulse = 0;		//電位差を作るため、片方は0に
			TIM_OC1Init(TIM4, &TIM_OC_InitStructure);		//TIM4のCH1
			TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

		}

		left_duty = duty;
	}

	if (side == motor_right) {

		if (set_duty == 0) {					//0のときはstop
			TIM_OC_InitStructure.TIM_Pulse = 0;		//duty0の時は一応0を代入しておく

			TIM_OC1Init(TIM5, &TIM_OC_InitStructure);		//TIM5のCH1
			TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);
			TIM_OC2Init(TIM5, &TIM_OC_InitStructure);		//TIM5のCH2
			TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);
		} else if (set_duty > 0) {				//正のときは正転
			TIM_OC1Init(TIM5, &TIM_OC_InitStructure);		//TIM5のCH1
			TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);

			TIM_OC_InitStructure.TIM_Pulse = 0;		//電位差を作るため、片方は0に
			TIM_OC2Init(TIM5, &TIM_OC_InitStructure);		//TIM5のCH2
			TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);

		} else {									//負のときは逆転
			TIM_OC2Init(TIM5, &TIM_OC_InitStructure);		//TIM5のCH2
			TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);

			TIM_OC_InitStructure.TIM_Pulse = 0;		//電位差を作るため、片方は0に
			TIM_OC1Init(TIM5, &TIM_OC_InitStructure);		//TIM5のCH1
			TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);
		}

		right_duty = duty;
	}

}

signed short motor::get_duty_left() {
	return left_duty;
}

signed short motor::get_duty_right() {
	return right_duty;
}

void motor::sleep_motor() {
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);	//モータードライバースリープ
	motor::set_duty(motor_left, 0);
	motor::set_duty(motor_right, 0);

}

void motor::stanby_motor() {
	GPIO_SetBits(GPIOA, GPIO_Pin_2);	//モータードライバースタンバイ
}

motor::motor() {
}

motor::~motor() {

}

