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
bool motor::motor_state = false;

void motor::set_duty(const MOTOR_SIDE side, const float set_duty) {
	signed short duty = 0;		//一時的な保存

	//Dutyに絶対値をとる
	duty = ABS(set_duty);

	//上限を切る
	if (set_duty > MAX_DUTY)
		duty = MAX_DUTY;

	static TIM_OCInitTypeDef TIM_OC_InitStructure;
	TIM_OC_InitStructure.TIM_OCMode = TIM_OCMode_PWM1;		//モードはPWM1
	TIM_OC_InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//たぶんいらない。This parameter is valid only for TIM1 and TIM8.
	TIM_OC_InitStructure.TIM_OutputState = TIM_OutputState_Enable;//たぶんいらない。This parameter is valid only for TIM1 and TIM8.

	TIM_OC_InitStructure.TIM_Pulse = static_cast<uint32_t>(MAX_PERIOD * duty
			* 0.01);	//dutyに応じてカウントを変更

	if (side == motor_right) {

		if (set_duty == 0) {					//0のときはstop
			TIM_OC_InitStructure.TIM_Pulse = 0;		//duty0の時は一応0を代入しておく
			TIM_OC1Init(TIM4, &TIM_OC_InitStructure);		//TIM4のCH1
			TIM_OC2Init(TIM4, &TIM_OC_InitStructure);		//TIM4のCH2

		} else if (set_duty > 0) {				//正のときは正転
			TIM_OC1Init(TIM4, &TIM_OC_InitStructure);		//TIM4のCH1
			TIM_OC_InitStructure.TIM_Pulse = 0;		//電位差を作るため、片方は0に
			TIM_OC2Init(TIM4, &TIM_OC_InitStructure);		//TIM4のCH2

		} else {									//負のときは逆転
			TIM_OC2Init(TIM4, &TIM_OC_InitStructure);		//TIM4のCH2
			TIM_OC_InitStructure.TIM_Pulse = 0;		//電位差を作るため、片方は0に
			TIM_OC1Init(TIM4, &TIM_OC_InitStructure);		//TIM4のCH1

		}

		right_duty = duty;
	}

	if (side == motor_left) {

		if (set_duty == 0) {					//0のときはstop
			TIM_OC_InitStructure.TIM_Pulse = 0;		//duty0の時は一応0を代入しておく

			TIM_OC1Init(TIM5, &TIM_OC_InitStructure);		//TIM5のCH1
			TIM_OC2Init(TIM5, &TIM_OC_InitStructure);		//TIM5のCH2
		} else if (set_duty > 0) {				//正のときは正転
			TIM_OC1Init(TIM5, &TIM_OC_InitStructure);		//TIM5のCH1

			TIM_OC_InitStructure.TIM_Pulse = 0;		//電位差を作るため、片方は0に
			TIM_OC2Init(TIM5, &TIM_OC_InitStructure);		//TIM5のCH2

		} else {									//負のときは逆転
			TIM_OC2Init(TIM5, &TIM_OC_InitStructure);		//TIM5のCH2

			TIM_OC_InitStructure.TIM_Pulse = 0;		//電位差を作るため、片方は0に
			TIM_OC1Init(TIM5, &TIM_OC_InitStructure);		//TIM5のCH1
		}

		left_duty = duty;
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
	TIM_Cmd(TIM4, DISABLE);
	TIM_Cmd(TIM5, DISABLE);
	motor::set_duty(motor_left, 0);
	motor::set_duty(motor_right, 0);
	motor_state = false;

}

void motor::stanby_motor() {
	GPIO_SetBits(GPIOA, GPIO_Pin_2);	//モータードライバースタンバイ
	TIM_Cmd(TIM4, ENABLE);
	TIM_Cmd(TIM5, ENABLE);
	motor_state = true;
}

bool motor::isEnable() {
	return motor_state;
}

motor::motor() {
}

motor::~motor() {

}

//gyro関連
SPI_TypeDef* mpu6000::use_SPI = SPI1;		//SPI1~3のどれ使ってるか
GPIO_TypeDef* mpu6000::cs_GPIOx = GPIOA;		//cs叩くピンの設定
const uint16_t mpu6000::cs_GPIO_Pin = GPIO_Pin_4;	//cs叩くピンの設定

//レジスター定義
const uint16_t mpu6000::GYRO_XOUT_H = 0x43;
const uint16_t mpu6000::GYRO_XOUT_L = 0x44;
const uint16_t mpu6000::GYRO_YOUT_H = 0x45;
const uint16_t mpu6000::GYRO_YOUT_L = 0x46;
const uint16_t mpu6000::GYRO_ZOUT_H = 0x47;
const uint16_t mpu6000::GYRO_ZOUT_L = 0x48;
const uint16_t mpu6000::ACCEL_XOUT_H = 0x3b;
const uint16_t mpu6000::ACCEL_XOUT_L = 0x3c;
const uint16_t mpu6000::ACCEL_YOUT_H = 0x3d;
const uint16_t mpu6000::ACCEL_YOUT_L = 0x3e;
const uint16_t mpu6000::ACCEL_ZOUT_H = 0x3f;
const uint16_t mpu6000::ACCEL_ZOUT_L = 0x40;

uint16_t mpu6000::read_spi(uint16_t read_reg) {
	uint16_t data = 0;
	uint16_t reg = (read_reg | 128);	//read時はレジスターの最上位Bitを1に

	GPIO_ResetBits(cs_GPIOx, cs_GPIO_Pin); // CSをセット

	//レジスタ指定
	while (SPI_I2S_GetFlagStatus(use_SPI, SPI_I2S_FLAG_TXE) == RESET)
		; // 送信可能になるまで待つ
	SPI_I2S_SendData(use_SPI, reg); // 送信
	while (SPI_I2S_GetFlagStatus(use_SPI, SPI_I2S_FLAG_RXNE) == RESET)
		; // 受信可能になるまで待つ
	data = SPI_I2S_ReceiveData(use_SPI); // 空データを受信する

	//データの送受信
	while (SPI_I2S_GetFlagStatus(use_SPI, SPI_I2S_FLAG_TXE) == RESET)
		; // 送信可能になるまで待つ
	SPI_I2S_SendData(use_SPI, 0x00); // 送信
	while (SPI_I2S_GetFlagStatus(use_SPI, SPI_I2S_FLAG_RXNE) == RESET)
		; // 受信可能になるまで待つ
	data = SPI_I2S_ReceiveData(use_SPI); // 受信する
	while (SPI_I2S_GetFlagStatus(use_SPI, SPI_I2S_FLAG_TXE) == RESET)
		;

	GPIO_SetBits(cs_GPIOx, cs_GPIO_Pin); //CSをリセット

	//連続して行ってもうまくいくように少しだけ待つ。
	for (int i = 0; i < 5; i++)
		;

	return data;
}

void mpu6000::write_spi(uint16_t reg, uint16_t data) {

	GPIO_ResetBits(cs_GPIOx, cs_GPIO_Pin); // CSをセット

	//レジスタ指定
	while (SPI_I2S_GetFlagStatus(use_SPI, SPI_I2S_FLAG_TXE) == RESET)
		; // 送信可能になるまで待つ
	SPI_I2S_SendData(use_SPI, reg); // 送信
	while (SPI_I2S_GetFlagStatus(use_SPI, SPI_I2S_FLAG_RXNE) == RESET)
		; // 受信可能になるまで待つ
	SPI_I2S_ReceiveData(use_SPI); // 空データを受信する

	//データの送受信
	while (SPI_I2S_GetFlagStatus(use_SPI, SPI_I2S_FLAG_TXE) == RESET)
		; // 送信可能になるまで待つ
	SPI_I2S_SendData(use_SPI, data); // 送信
	while (SPI_I2S_GetFlagStatus(use_SPI, SPI_I2S_FLAG_RXNE) == RESET)
		; // 受信可能になるまで待つ
	SPI_I2S_ReceiveData(use_SPI); // 受信する
	while (SPI_I2S_GetFlagStatus(use_SPI, SPI_I2S_FLAG_TXE) == RESET)
		;

	GPIO_SetBits(cs_GPIOx, cs_GPIO_Pin); //CSをリセット

	//連続して行ってもうまくいくように少しだけ待つ。
	for (int i = 0; i < 10; i++)
		;

}

int16_t mpu6000::get_mpu_value(SEN_TYPE sen, AXIS_t axis) {
	int16_t data = 0;
	uint16_t reg_h = 0;	//highの値へのレジスタ
	uint16_t reg_l = 0;	//Lowの値へのレジスタ

	switch (sen) {
	case sen_gyro:
		switch (axis) {
		case axis_x:
			reg_h = GYRO_XOUT_H;
			reg_l = GYRO_XOUT_L;
			break;
		case axis_y:
			reg_h = GYRO_YOUT_H;
			reg_l = GYRO_YOUT_L;
			break;
		case axis_z:
			reg_h = GYRO_ZOUT_H;
			reg_l = GYRO_ZOUT_L;
			break;
		}
		break;

	case sen_accel:
		switch (axis) {
		case axis_x:
			reg_h = ACCEL_XOUT_H;
			reg_l = ACCEL_XOUT_L;
			break;
		case axis_y:
			reg_h = ACCEL_YOUT_H;
			reg_l = ACCEL_YOUT_L;
			break;
		case axis_z:
			reg_h = ACCEL_ZOUT_H;
			reg_l = ACCEL_ZOUT_L;
			break;
		}
		break;

	default:		//gyroと加速度以外は読めないので初期値を返して終了
		return data;
		break;
	}

	//Highの方は上位に8ビットずらしてLowと合わせて、目的のデータを得る。
	data = static_cast<int16_t>((read_spi(reg_h) << 8) + read_spi(reg_l));

	return data;
}

void mpu6000::init_mpu6000() {
	static const uint16_t SIGNAL_PATH_RESET = 0x68;
	static const uint16_t PWR_MGMT_1 = 0x6B;
	static const uint16_t PWR_MGMT_2 = 0x6c;
	static const uint16_t USER_CTRL = 0x6a;
	static const uint16_t DATA_CONFIG = 0x1a;
	static const uint16_t GYRO_CONFIG = 0x1b;
	static const uint16_t ACCEL_CONFIG = 0x1c;

	write_spi(PWR_MGMT_1, 0x00);		//サイクル1、SLEEP解除、温度センサは使わない
	write_spi(PWR_MGMT_2, 0xEE);		//ジャイロのZ軸方向、加速度のY軸方向以外は停止//6c
	write_spi(USER_CTRL, 16);			//I2CをDisable、SPIをEnable
	write_spi(SIGNAL_PATH_RESET, 0x06);	//ジャイロ、加速度リセット//04
	write_spi(DATA_CONFIG, 0x00);		//フィルターはかけない
	write_spi(GYRO_CONFIG, 0x18);		//ジャイロを±2000°/sに設定
	write_spi(ACCEL_CONFIG, 0x18);		//加速度を±16g/sに設定

	//確認用
	/*
	 myprintf("PWR_MGMT_1 0x%x\n\r",read_spi(PWR_MGMT_1));
	 myprintf("PWR_MGMT_2 0x%x\n\r",read_spi(PWR_MGMT_2));
	 myprintf("USER_CTRL 0d%d\n\r",read_spi(USER_CTRL));
	 myprintf("SIGNAL_PATH_RESET 0x%x\n\r",read_spi(SIGNAL_PATH_RESET));
	 myprintf("DATA_CONFIG 0x%x\n\r",read_spi(DATA_CONFIG));
	 myprintf("GYRO_CONFIG 0x%x\n\r",read_spi(GYRO_CONFIG));
	 myprintf("ACCEL_CONFIG 0x%x\n\r",read_spi(ACCEL_CONFIG));
	 */
}

mpu6000::mpu6000() {
}

mpu6000::~mpu6000() {

}

const float accelmeter::ACCEL_PERIOD = CONTORL_PERIOD;		//加速度計の制御周期[s]
const float accelmeter::REF_TIME = 1;			//加速度計のリファレンスとる時間[s]
const uint8_t accelmeter::AVERAGE_COUNT = 20;			//加速度計の平均回数[回]
float accelmeter::accel_ad, accelmeter::accel_ref;
float accelmeter::accel;

void accelmeter::interrupt() {
	static float buff[AVERAGE_COUNT] = { 0 };	//データを保存しておく配列
	float sum = 0;

	for (uint8_t i = 0; (i + 1) < AVERAGE_COUNT; i++) {
		buff[i + 1] = buff[i];	//配列を1つずらす
		sum += buff[i + 1];			//ついでに加算する
	}

	//配列の最初に入れる
	buff[0] = mpu6000::get_mpu_value(sen_accel, axis_y);	//加速度のy方向

	sum += buff[0];

	accel_ad = sum / AVERAGE_COUNT;

	accel = (accel_ad - accel_ref) / ACCEL_SENSITIVITY / 9.8;//加速度[g]を[m/ss]に直すため重力加速度で割る

}

float accelmeter::get_accel_ref() {
	float accel_sum = 0;
	int32_t i;
	for (i = 0; i < static_cast<int32_t>(REF_TIME / ACCEL_PERIOD); i++) {
		accel_sum += get_accel_ad();
		wait::ms(1);
	}
	return (accel_sum / (i + 1));
}

float accelmeter::get_accel_ad() {
	return accel_ad;
}

void accelmeter::set_accel_ref() {
	accel_ref = get_accel_ref();
}

float accelmeter::get_accel() {
	return accel;
}

int16_t gyro::gyro_value;
float gyro::default_angle;
float gyro::angle, gyro::gyro_ref;
float gyro::angular_velocity;
float gyro::least_square_slope = 0;
const float gyro::GYRO_PERIOD = CONTORL_PERIOD;		//制御周期[s]
const float gyro::REF_TIME = 2;							//リファレンスとる時間[s]

void gyro::interrupt() {
	gyro_value = -mpu6000::get_mpu_value(sen_gyro, axis_z);	//Z方向のジャイロを見る。時計回り正
	gyro::cal_angular_velocity();	//gyroから角速度を計算[°/s]
	gyro::cal_angle();				//gyroから角度を計算

}

int16_t gyro::get_gyro() {
	return gyro_value;
}

float gyro::get_gyro_ref() {
	int32_t gyro_sum = 0;
	int32_t i;
	for (i = 0; i < static_cast<int32_t>(REF_TIME / GYRO_PERIOD); i++) {
		gyro_sum += get_gyro();
		wait::ms(1);
	}

	return (gyro_sum / (i + 1));
}

void gyro::set_least_square_slope() {
	//x,yとかはWikiの最小二乗法と同じ。xは時間[ms],yは角度[°]
	float x_square_sum = 0, x_sum = 0, y_sum = 0, xy_sum = 0;
	float temp_count = 0;
	float temp_gyro;

	mouse::reset_count();

	while (mouse::get_count_ms() < LEAST_SQUARE_TIME) {
		temp_count = (float) mouse::get_count_ms();
		temp_gyro = gyro::get_angle();

		y_sum += temp_gyro;
		x_sum += temp_count;
		x_square_sum += (temp_count * temp_count);
		xy_sum += (temp_count * temp_gyro);

		//1ms経つまで待機
		while (temp_count >= mouse::get_count_ms()) {
		}
	}

	if ((x_square_sum - x_sum * x_sum) == 0) {
		least_square_slope = 0;
		return;
	}
	least_square_slope += (float) ((LEAST_SQUARE_TIME * xy_sum - x_sum * y_sum)
			/ (LEAST_SQUARE_TIME * x_square_sum - x_sum * x_sum));
}

void gyro::set_gyro_ref() {
	gyro_ref = get_gyro_ref();
	//XXX ジャイロの補正に最小二乗法は使ってない
	/*
	 set_least_square_slope();	//最小二乗法による補正項導出
	 mouse::reset_count();
	 */
}

void gyro::reset_angle() {
	default_angle = 0;
	angle = 0;
}

void gyro::cal_angle() {
	angle += angular_velocity * GYRO_PERIOD;
	//XXX最小二乗法での補正はしてない
	//最小二乗法で補正する
	//angle = default_angle	- (least_square_slope * (float) mouse::get_count_ms());
}

float gyro::get_angle() {
	return angle;	//°
}

void gyro::cal_angular_velocity() {
	angular_velocity = radian((gyro_value - gyro_ref) / GYRO_SENSITIVITY);
}

float gyro::get_angular_velocity() {
	return angular_velocity;	//[rad/s]
}

gyro::gyro() {

}

gyro::~gyro() {

}

//encoder関連
const uint8_t encoder::MOVING_AVERAGE = 70;
const uint32_t encoder::MEDIAN = 32762;
float encoder::left_velocity, encoder::right_velocity, encoder::velocity;

void encoder::interrupt() {
	static float data_r[MOVING_AVERAGE] = { 0 };	//データを保存しておく配列
	float sum_r = 0;
	static float data_l[MOVING_AVERAGE] = { 0 };	//データを保存しておく配列
	float sum_l = 0;

	for (uint8_t i = 0; (i + 1) < MOVING_AVERAGE; i++) {
		data_r[i + 1] = data_r[i];	//配列を1つずらす
		sum_r += data_r[i + 1];			//ついでに加算する
		data_l[i + 1] = data_l[i];	//配列を1つずらす
		sum_l += data_l[i + 1];			//ついでに加算する
	}

	//配列の最初に入れる
	data_r[0] = (32762 - static_cast<float>(TIM3->CNT)) * ENCODER_CONST
			/ CONTROL_PERIOD * tire_R;	//count*[rad/count]/[sec]*[m]
	data_l[0] = (static_cast<float>(TIM2->CNT) - 32762) * ENCODER_CONST
			/ CONTORL_PERIOD * tire_R;	//m/s

	TIM2->CNT = 32762;
	TIM3->CNT = 32762;

	sum_r += data_r[0];
	sum_l += data_r[0];

	right_velocity = sum_r / MOVING_AVERAGE;
	left_velocity = sum_l / MOVING_AVERAGE;

	velocity = (right_velocity + left_velocity) / 2;

}

float encoder::get_velocity() {

	//松井さん方式　http://matsui-mouse.blogspot.jp/2014/03/blog-post_26.html
	return (velocity
			+ accelmeter::get_accel() * accelmeter::AVERAGE_COUNT
					* accelmeter::ACCEL_PERIOD / 2);
}

encoder::encoder() {
}

encoder::~encoder() {

}

signed int photo::right_ad, photo::left_ad, photo::front_right_ad,
		photo::front_left_ad, photo::front_ad;
signed int photo::right_ref, photo::left_ref, photo::front_right_ref,
		photo::front_left_ref, photo::front_ref;
bool photo::light_flag = false;

void photo::switch_led(PHOTO_TYPE sensor_type, bool is_light) {
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;

	//どのIOをいじるか設定
	switch (sensor_type) {

	//左右は同時発行
	case right:
	case left:
		GPIOx = GPIOD;
		GPIO_Pin = GPIO_Pin_2;
		break;

	case front_right:
		GPIOx = GPIOC;
		GPIO_Pin = GPIO_Pin_11;
		break;

	case front_left:
		GPIOx = GPIOC;
		GPIO_Pin = GPIO_Pin_10;
		break;

	case front:
		GPIOx = GPIOC;
		GPIO_Pin = GPIO_Pin_12;
		break;
	}

	//光らせる
	if (is_light)
		GPIO_SetBits(GPIOx, GPIO_Pin);
	else
		GPIO_ResetBits(GPIOx, GPIO_Pin);

}

uint16_t photo::get_ad(PHOTO_TYPE sensor_type) {
	uint8_t ADC_CH;
	ADC_TypeDef* ADCx;

	//どのIOをいじるか設定
	switch (sensor_type) {
	case right:
		ADCx = ADC1;
		ADC_CH = ADC_Channel_15;
		break;

	case left:
		ADCx = ADC1;
		ADC_CH = ADC_Channel_11;
		break;

	case front_right:
		ADCx = ADC1;
		ADC_CH = ADC_Channel_8;
		break;

	case front_left:
		ADCx = ADC1;
		ADC_CH = ADC_Channel_10;
		break;

	case front:
		ADCx = ADC1;
		ADC_CH = ADC_Channel_14;
		break;
	}

	//ad変換
	ADC_ClearFlag(ADCx, ADC_FLAG_EOC);		//EndFlagをクリアする
	ADC_RegularChannelConfig(ADCx, ADC_CH, 1,
	ADC_SampleTime_3Cycles);		//ADCxのADC_CHを
	ADC_SoftwareStartConv(ADCx);	//ADCを開始
	while (ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC) == RESET)
		;		//終わるまで待つ

	return (ADC_GetConversionValue(ADCx) >> 4);	//XXX 値を取得　4ビットシフトでうまくいってる気がする　右詰めのはずなのに意味わからん。

}

void photo::light(PHOTO_TYPE sensor_type) {
	switch_led(sensor_type, true);
}

void photo::turn_off(PHOTO_TYPE sensor_type) {
	switch_led(sensor_type, false);
}

void photo::turn_off_all() {
	turn_off(right);
	turn_off(left);
	turn_off(front_right);
	turn_off(front_left);

}

void photo::set_ad(PHOTO_TYPE sensor_type, int16_t set_value) {

	static const int16_t PHOTO_AVERAGE_TIME = 10;	//いくつの移動平均をとるか
	static int16_t buf[element_count][PHOTO_AVERAGE_TIME] = { 0 };

	int16_t sum = 0;

	for (uint8_t i = 0; (i + 1) < PHOTO_AVERAGE_TIME; i++) {
		buf[sensor_type][i + 1] = buf[sensor_type][i];	//配列を1つずらす
		sum += buf[sensor_type][i + 1];			//ついでに加算する
	}

	//配列の最初に入れる
	buf[sensor_type][0] = set_value;	//count*[rad/count]/[sec]*[m]
	sum += set_value;

	switch (sensor_type) {
	case right:
		right_ad = sum / PHOTO_AVERAGE_TIME;
		break;

	case left:
		left_ad = sum / PHOTO_AVERAGE_TIME;
		break;

	case front_right:
		front_right_ad = sum / PHOTO_AVERAGE_TIME;
		;
		break;

	case front_left:
		front_left_ad = sum / PHOTO_AVERAGE_TIME;
		;
		break;

	case front:
		front_ad = sum / PHOTO_AVERAGE_TIME;
		;
		break;
	}
}

void photo::interrupt(bool is_light) {
	const static int wait_number = 1000;
	photo::turn_off_all();

	photo::set_ref(right, get_ad(right));		//消えてる時をrefにする
	photo::set_ref(left, get_ad(left));		//消えてる時をrefにする
	photo::set_ref(front_right, get_ad(front_right));		//消えてる時をrefにする
	photo::set_ref(front_left, get_ad(front_left));		//消えてる時をrefにする
	photo::set_ref(front, get_ad(front));		//消えてる時をrefにする

	//左右の発光は回路的に同時におこるので、同時に左右の値をとる
	if (is_light) {
		photo::light(right);
		photo::light(left);
		for (int i = 0; i < wait_number * 2; i++) {
		}
	}
	photo::set_ad(right, get_ad(right) - get_ref(right));		//差分を代入
	photo::set_ad(left, get_ad(left) - get_ref(left));		//差分を代入
	photo::turn_off(right);

	if (is_light) {
		photo::light(front_right);
		for (int i = 0; i < wait_number; i++) {
		}
	}
	photo::set_ad(front_right, get_ad(front_right) - get_ref(front_right));	//差分を代入
	photo::turn_off(front_right);

	if (is_light) {
		photo::light(front_left);
		for (int i = 0; i < wait_number; i++) {
		}
	}
	photo::set_ad(front_left, get_ad(front_left) - get_ref(front_left));//差分を代入
	photo::turn_off(front_left);

	if (is_light) {
		photo::light(front);
		for (int i = 0; i < wait_number; i++) {
		}
	}
	photo::set_ad(front, get_ad(front) - get_ref(front));	//差分を代入
	photo::turn_off(front);
}

int16_t photo::get_ref(PHOTO_TYPE sensor_type) {
	switch (sensor_type) {
	case right:
		return right_ref;
		break;

	case left:
		return left_ref;
		break;

	case front_right:
		return front_right_ref;
		break;

	case front_left:
		return front_left_ref;
		break;

	case front:
		return front_ref;
		break;
	}

	return 0;
}

void photo::set_ref(PHOTO_TYPE sensor_type, int16_t set_value) {
	switch (sensor_type) {
	case right:
		right_ref = set_value;
		break;

	case left:
		left_ref = set_value;
		break;

	case front_right:
		front_right_ref = set_value;
		break;

	case front_left:
		front_left_ref = set_value;
		break;

	case front:
		front_ref = set_value;
		break;
	}
}

int16_t photo::get_value(PHOTO_TYPE sensor_type) {
	switch (sensor_type) {
	case right:
		return right_ad;
		break;

	case left:
		return left_ad;
		break;

	case front_right:
		return front_right_ad;
		break;

	case front_left:
		return front_left_ad;
		break;

	case front:
		return front_ad;
		break;
	}

	return 0;
}

bool photo::check_wall(unsigned char muki) {

	switch (muki) {
	case MUKI_RIGHT:
		if (photo::get_value(right) >= parameter::get_min_wall_photo(right)) {
			return true;
		}
		return false;

	case MUKI_LEFT:
		//XXX leftは安定しないからFrontLeftでみる
		if (photo::get_value(front_left)
				>= parameter::get_min_wall_photo(front_left)) {
			return true;
		}
		return false;

	case MUKI_UP:
		//TODO 暇があったら、前壁見るのは斜めセンサいらない？？
		if (photo::get_value(front) >= parameter::get_min_wall_photo(front)) {
			//if ((front_right_ad >= parameter::get_min_wall_photo(front_right))
			//		|| (front_left_ad >= parameter::get_min_wall_photo(front_left))) {
			return true;
		}
		return false;
	}

	return false;

}

bool photo::check_wall(PHOTO_TYPE type) {

	return (photo::get_value(type) >= parameter::get_min_wall_photo(type));

}

photo::photo() {
}

photo::~photo() {
}

//XXX 各種ゲイン
//control関連
const PID gyro_gain = { 30, 150, 0 };
const PID photo_gain = { 0.5, 0, 0 };
const PID encoder_gain = { 500, 1500, 0 };

PID control::gyro_delta, control::photo_delta, control::encoder_delta;
bool control::control_phase = false;
bool control::wall_control_flag = false;
bool control::is_FF_CONTROL = false;
bool control::is_FB_CONTROL = true;

float control::cross_delta_gain(SEN_TYPE sensor) {
	switch (sensor) {
	case sen_gyro:
		return (gyro_delta.P * gyro_gain.P + gyro_delta.I * gyro_gain.I
				+ gyro_delta.D * gyro_gain.D);

	case sen_encoder:
		return (encoder_delta.P * encoder_gain.P
				+ encoder_delta.I * encoder_gain.I
				+ encoder_delta.D * encoder_gain.D);

	case sen_photo:
		return (photo_delta.P * photo_gain.P + photo_delta.I * photo_gain.I
				+ photo_delta.D * photo_gain.D);

	}
	return 0;
}

void control::cal_delta() {
	float before_p_delta;
	float photo_right_delta = 0, photo_left_delta = 0;

	//エンコーダーのΔ計算
	before_p_delta = encoder_delta.P;	//積分用
	encoder_delta.P = (mouse::get_ideal_velocity() - encoder::get_velocity());
	encoder_delta.I += (encoder_delta.P * CONTORL_PERIOD);
	//encoder_delta.D = (encoder_delta.P - before_p_delta) * 1000;

	//センサーのΔ計算
	before_p_delta = photo_delta.P;

	float delta = 0;
	float ideal = 0, actual = 0;//uint16 - uint16 の計算はマイナスになったときオーバーフローするからfloat変数を経由する

	if (photo::check_wall(right) && control::get_wall_control_phase()) {

		ideal = static_cast<float>(parameter::get_ideal_photo(right));
		actual = static_cast<float>(photo::get_value(right));
		delta = actual - ideal;		//理想値との差分
		//中央付近は制御しない
		if (ABS(delta) > 30) {
			photo_right_delta = delta;
		}
		if (delta < 0)
			photo_right_delta = 0;	//近づく方向には制御しない

	}

	if (photo::check_wall(left) && control::get_wall_control_phase()) {

		ideal = static_cast<float>(parameter::get_ideal_photo(front_left));
		actual = static_cast<float>(photo::get_value(front_left));
		delta = actual - ideal;		//理想値との差分
		//中央付近は制御しない
		if (ABS(delta) > 30) {
			photo_left_delta = delta;
			//左の制御が弱いので右ないときは2倍にする
			if (photo_right_delta == 0)
				photo_left_delta = delta * 2;
		}
		if (delta < 0)
			photo_left_delta = 0;	//近づく方向には制御しない
	}

	//速度が低いと制御が効きすぎるので（相対的に制御が大きくなる）、切る
	if (mouse::get_ideal_velocity() < (SEARCH_VELOCITY * 0.5)) {
		photo_left_delta = 0;
		photo_right_delta = 0;

	}

	//TODO　壁制御何かおかしい
	photo_delta.P = (photo_right_delta - photo_left_delta);
	//photo_delta.I += (photo_delta.P * CONTORL_PERIOD);
	//photo_delta.D = (photo_delta.P - before_p_delta) * 1000;

	//ジャイロのΔ計算
	before_p_delta = gyro_delta.P;	//積分用
	gyro_delta.P = (mouse::get_ideal_angular_velocity()
			- gyro::get_angular_velocity());
	gyro_delta.I += (gyro_delta.P * CONTORL_PERIOD);
	//gyro_delta.D = (gyro_delta.P - before_p_delta) * 1000;

	if (photo_delta.P != 0 && get_wall_control_phase())
		gyro_delta.I = 0;		//壁制御かけるときはGyroのIは使わない
	else
		photo_delta.I = 0;

}

float control::control_velocity() {
	return cross_delta_gain(sen_encoder);
}

float control::control_angular_velocity() {
	if (wall_control_flag) {
		return (cross_delta_gain(sen_gyro) - cross_delta_gain(sen_photo));
	} else {
		return cross_delta_gain(sen_gyro);
	}
}

void control::start_wall_control() {
	wall_control_flag = true;
}

void control::stop_wall_control() {
	wall_control_flag = false;
}

void control::start_control() {
	control_phase = true;
}

void control::stop_control() {
	control_phase = false;
}

float control::get_feedback(signed char right_or_left) {
	if (right_or_left == MUKI_RIGHT) {			//右のモーターなら
		return (control_velocity() - control_angular_velocity());

	} else {										//左のモーターなら
		return (control_velocity() + control_angular_velocity());

	}
}

float control::get_feedforward(const signed char right_or_left) {
	float velocity;		//目標速度

	if (right_or_left == MUKI_RIGHT) {			//右のモーターなら
		velocity = mouse::get_ideal_velocity()
				- (mouse::get_ideal_angular_velocity() * TREAD_W / 2 / 1000);

	} else {									//左のモーターなら
		velocity = mouse::get_ideal_velocity()
				+ (mouse::get_ideal_angular_velocity() * TREAD_W / 2 / 1000);

	}
	return (velocity / (2 * PI() * tire_R / 1000) * SPAR / PINION * M_SUM_ORM
			/ MOTOR_ORM / MOTOR_CONST / get_battery()) * 100;
}

void control::posture_control() {
	if (get_control_phase()) {			//制御を掛けるなら
		if (is_FF_CONTROL || is_FB_CONTROL) {		//FFかFBのどちらかでも制御を掛けるとき

			float duty_r = 0, duty_l = 0;		//dutyを保存するよう

			if (is_FF_CONTROL) {			//FF制御を掛けるなら
				duty_r = get_feedforward(MUKI_RIGHT);
				duty_l = get_feedforward(MUKI_LEFT);
			}
			if (is_FB_CONTROL) {				//FB制御を掛けるなら
				duty_r += get_feedback(MUKI_RIGHT);
				duty_l += get_feedback(MUKI_LEFT);
			}

			motor::set_duty(motor_right, duty_r);
			motor::set_duty(motor_left, duty_l);
		}
	}
}

bool control::get_control_phase() {
	return control_phase;
}

bool control::get_wall_control_phase() {
	return wall_control_flag;
}

void control::reset_delta() {
	reset_delta(sen_gyro);
	reset_delta(sen_photo);
	reset_delta(sen_encoder);

}

void control::reset_delta(SEN_TYPE type) {

	switch (type) {
	case sen_gyro:
		gyro_delta.P = 0;
		gyro_delta.I = 0;
		gyro_delta.D = 0;
		break;

	case sen_photo:
		photo_delta.P = 0;
		photo_delta.I = 0;
		photo_delta.D = 0;
		break;

	case sen_encoder:
		encoder_delta.P = 0;
		encoder_delta.I = 0;
		encoder_delta.D = 0;
		break;

	case sen_accel:
		//現在は偏差がないため。
		break;
	}
}

void control::fail_safe() {
	//TODO 閾値どのくらいかわからない。Gyroも参照すべき？
	if (encoder_delta.P > 0.5) {
		motor::sleep_motor();
		mouse::set_fail_flag(true);
	}
}

control::control() {
}

control::~control() {

}

