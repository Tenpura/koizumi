/*
 * hardware.cpp
 *
 *  Created on: 2015/06/13
 *      Author: Koizumi
 */

#include"hardware.h"

//自作7セグ関連

void my7seg::light(const my7seg::DIRECTION muki) {

	switch (muki) {
	case front:
		GPIO_ResetBits(GPIOH, GPIO_Pin_0);	//LED9
		break;

	case left:
		GPIO_ResetBits(GPIOC, GPIO_Pin_14);	//LED5
		GPIO_ResetBits(GPIOC, GPIO_Pin_15);	//LED6
		break;

	case right:
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);	//LED3
		GPIO_ResetBits(GPIOH, GPIO_Pin_1);	//LED4
		break;

	default:
		break;
	}
}

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
		GPIO_ResetBits(GPIOC, GPIO_Pin_14);	//LED5
		GPIO_ResetBits(GPIOC, GPIO_Pin_15);	//LED6
		GPIO_ResetBits(GPIOH, GPIO_Pin_0);	//LED9
		GPIO_ResetBits(GPIOH, GPIO_Pin_1);	//LED4
		break;
	case 1:
		GPIO_SetBits(GPIOB, GPIO_Pin_4);	//LED7
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);	//LED3
		GPIO_SetBits(GPIOC, GPIO_Pin_2);	//LED8
		GPIO_SetBits(GPIOC, GPIO_Pin_14);	//LED5
		GPIO_SetBits(GPIOC, GPIO_Pin_15);	//LED6
		GPIO_SetBits(GPIOH, GPIO_Pin_0);	//LED9
		GPIO_ResetBits(GPIOH, GPIO_Pin_1);	//LED4
		break;
	case 2:
		GPIO_ResetBits(GPIOB, GPIO_Pin_4);	//LED7
		GPIO_SetBits(GPIOB, GPIO_Pin_12);	//LED3
		GPIO_ResetBits(GPIOC, GPIO_Pin_2);	//LED8
		GPIO_ResetBits(GPIOC, GPIO_Pin_14);	//LED5
		GPIO_SetBits(GPIOC, GPIO_Pin_15);	//LED6
		GPIO_ResetBits(GPIOH, GPIO_Pin_0);	//LED9
		GPIO_ResetBits(GPIOH, GPIO_Pin_1);	//LED4
		break;
	case 3:
		GPIO_ResetBits(GPIOB, GPIO_Pin_4);	//LED7
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);	//LED3
		GPIO_ResetBits(GPIOC, GPIO_Pin_2);	//LED8
		GPIO_SetBits(GPIOC, GPIO_Pin_14);	//LED5
		GPIO_SetBits(GPIOC, GPIO_Pin_15);	//LED6
		GPIO_ResetBits(GPIOH, GPIO_Pin_0);	//LED9
		GPIO_ResetBits(GPIOH, GPIO_Pin_1);	//LED4
		break;
	case 4:
		GPIO_ResetBits(GPIOB, GPIO_Pin_4);	//LED7
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);	//LED3
		GPIO_SetBits(GPIOC, GPIO_Pin_2);	//LED8
		GPIO_SetBits(GPIOC, GPIO_Pin_14);	//LED5
		GPIO_ResetBits(GPIOC, GPIO_Pin_15);	//LED6
		GPIO_SetBits(GPIOH, GPIO_Pin_0);	//LED9
		GPIO_ResetBits(GPIOH, GPIO_Pin_1);	//LED4
		break;
	case 5:
		GPIO_ResetBits(GPIOB, GPIO_Pin_4);	//LED7
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);	//LED3
		GPIO_ResetBits(GPIOC, GPIO_Pin_2);	//LED8
		GPIO_SetBits(GPIOC, GPIO_Pin_14);	//LED5
		GPIO_ResetBits(GPIOC, GPIO_Pin_15);	//LED6
		GPIO_ResetBits(GPIOH, GPIO_Pin_0);	//LED9
		GPIO_SetBits(GPIOH, GPIO_Pin_1);	//LED4
		break;
	case 6:
		GPIO_ResetBits(GPIOB, GPIO_Pin_4);	//LED7
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);	//LED3
		GPIO_ResetBits(GPIOC, GPIO_Pin_2);	//LED8
		GPIO_ResetBits(GPIOC, GPIO_Pin_14);	//LED5
		GPIO_ResetBits(GPIOC, GPIO_Pin_15);	//LED6
		GPIO_ResetBits(GPIOH, GPIO_Pin_0);	//LED9
		GPIO_SetBits(GPIOH, GPIO_Pin_1);	//LED4
		break;
	case 7:
		GPIO_SetBits(GPIOB, GPIO_Pin_4);	//LED7
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);	//LED3
		GPIO_SetBits(GPIOC, GPIO_Pin_2);	//LED8
		GPIO_SetBits(GPIOC, GPIO_Pin_14);	//LED5
		GPIO_ResetBits(GPIOC, GPIO_Pin_15);	//LED6
		GPIO_ResetBits(GPIOH, GPIO_Pin_0);	//LED9
		GPIO_ResetBits(GPIOH, GPIO_Pin_1);	//LED4
		break;
	case 8:
		GPIO_ResetBits(GPIOB, GPIO_Pin_4);	//LED7
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);	//LED3
		GPIO_ResetBits(GPIOC, GPIO_Pin_2);	//LED8
		GPIO_ResetBits(GPIOC, GPIO_Pin_14);	//LED5
		GPIO_ResetBits(GPIOC, GPIO_Pin_15);	//LED6
		GPIO_ResetBits(GPIOH, GPIO_Pin_0);	//LED9
		GPIO_ResetBits(GPIOH, GPIO_Pin_1);	//LED4
		break;
	case 9:
		GPIO_ResetBits(GPIOB, GPIO_Pin_4);	//LED7
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);	//LED3
		GPIO_ResetBits(GPIOC, GPIO_Pin_2);	//LED8
		GPIO_SetBits(GPIOC, GPIO_Pin_14);	//LED5
		GPIO_ResetBits(GPIOC, GPIO_Pin_15);	//LED6
		GPIO_ResetBits(GPIOH, GPIO_Pin_0);	//LED9
		GPIO_ResetBits(GPIOH, GPIO_Pin_1);	//LED4
		break;
	}
	return;
}

void my7seg::turn_off() {
	GPIO_SetBits(GPIOB, GPIO_Pin_4);	//LED7
	GPIO_SetBits(GPIOB, GPIO_Pin_12);	//LED3
	GPIO_SetBits(GPIOC, GPIO_Pin_2);	//LED8
	GPIO_SetBits(GPIOC, GPIO_Pin_14);	//LED5
	GPIO_SetBits(GPIOC, GPIO_Pin_15);	//LED6
	GPIO_SetBits(GPIOH, GPIO_Pin_0);	//LED9
	GPIO_SetBits(GPIOH, GPIO_Pin_1);	//LED4
}

void my7seg::light_error() {
	GPIO_ResetBits(GPIOB, GPIO_Pin_4);	//LED7
	GPIO_SetBits(GPIOB, GPIO_Pin_12);	//LED3
	GPIO_ResetBits(GPIOC, GPIO_Pin_2);	//LED8
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

	if (side == MOTOR_SIDE::m_right) {

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

	if (side == MOTOR_SIDE::m_left) {

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
	motor::set_duty(m_left, 0);
	motor::set_duty(m_right, 0);
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

volatile int16_t mpu6000::get_mpu_val(SEN_TYPE sen, AXIS_t axis) {
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

void mpu6000::init() {
	static const uint16_t SIGNAL_PATH_RESET = 0x68;
	static const uint16_t PWR_MGMT_1 = 0x6B;
	static const uint16_t PWR_MGMT_2 = 0x6c;
	static const uint16_t USER_CTRL = 0x6a;
	static const uint16_t DATA_CONFIG = 0x1a;
	static const uint16_t GYRO_CONFIG = 0x1b;
	static const uint16_t ACCEL_CONFIG = 0x1c;

	write_spi(PWR_MGMT_1, 0x00);		//サイクル1、SLEEP解除、温度センサは使わない
	write_spi(PWR_MGMT_2, 0xC6);		//ジャイロのZ軸方向以外は停止、加速度はXYZ軸方向全部許可
	write_spi(USER_CTRL, 16);			//I2CをDisable、SPIをEnable
	write_spi(SIGNAL_PATH_RESET, 0x06);	//ジャイロ、加速度リセット
	write_spi(DATA_CONFIG, 0x01);		//フィルターはかけない
	write_spi(GYRO_CONFIG, 0x18);		//ジャイロを±2000°/sに設定
	write_spi(ACCEL_CONFIG, 0x08);		//加速度を±4g/sに設定

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
const uint8_t accelmeter::AVERAGE_COUNT = 10;			//加速度計の平均回数[回]
float accelmeter::accel_ad[AXIS_t::dim_num] = { 0 },
		accelmeter::accel_ref[AXIS_t::dim_num] = { 0 };
float accelmeter::accel[AXIS_t::dim_num] = { 0 };

void accelmeter::interrupt() {
	static float buff[AXIS_t::dim_num][AVERAGE_COUNT] = { 0 };	//データを保存しておく配列
	float sum[AXIS_t::dim_num] = { 0 };

	for (int i = 0; (i + 1) < AVERAGE_COUNT; i++) {
		for (int j = 0; j < AXIS_t::dim_num; j++) {
			buff[j][i] = buff[j][i + 1];	//配列を1つずらす
			sum[j] += buff[j][i];			//ついでに加算する
		}
	}

	//配列の最後に入れる
	buff[AXIS_t::axis_x][(AVERAGE_COUNT - 1)] =
			static_cast<float>(mpu6000::get_mpu_val(sen_accel, axis_x));//加速度のx方向
	buff[AXIS_t::axis_y][(AVERAGE_COUNT - 1)] =
			static_cast<float>(mpu6000::get_mpu_val(sen_accel, axis_y));//加速度のy方向
	buff[AXIS_t::axis_z][(AVERAGE_COUNT - 1)] =
			static_cast<float>(mpu6000::get_mpu_val(sen_accel, axis_z));//加速度のz方向

	for (int j = 0; j < AXIS_t::dim_num; j++) {
		sum[j] += buff[j][(AVERAGE_COUNT - 1)];		//sumに最新の値を足す
		accel_ad[j] = sum[j] / AVERAGE_COUNT;		//平均をとって加速度の値とする
	}

	cal_accel();

}

float accelmeter::get_accel_ref(AXIS_t xyz) {
	float accel_sum = 0;
	int32_t i;
	for (i = 0; i < static_cast<int32_t>(REF_TIME / ACCEL_PERIOD); i++) {
		accel_sum += get_accel_ad(xyz);
		wait::ms(1);
	}
	return (accel_sum / (i + 1));
}

float accelmeter::get_accel_ad(AXIS_t xyz) {
	return accel_ad[xyz];
}

void accelmeter::set_accel_ref() {
	set_accel_ref(AXIS_t::axis_x);
	set_accel_ref(AXIS_t::axis_y);
	set_accel_ref(AXIS_t::axis_z);
}

void accelmeter::set_accel_ref(AXIS_t xyz) {
	accel_ref[xyz] = get_accel_ref(xyz);
}

void accelmeter::cal_accel() {
	for (int j = 0; j < AXIS_t::dim_num; j++)
		accel[j] = (accel_ad[j] - accel_ref[j]) / ACCEL_SENSITIVITY * 9.8;//加速度[g]を[m/ss]に直すため重力加速度をかける
}

float accelmeter::get_accel() {
	return accel[axis_y];		//進行方向の加速度
}

float accelmeter::get_accel(AXIS_t xyz) {
	return accel[xyz];
}

int16_t gyro::gyro_value;
float gyro::default_angle;
float gyro::angle, gyro::gyro_ref;
float gyro::angular_velocity;
float gyro::least_square_slope = 0;
const float gyro::GYRO_PERIOD = CONTORL_PERIOD;		//制御周期[s]
const float gyro::REF_TIME = 2;							//リファレンスとる時間[s]

void gyro::interrupt() {
	gyro_value = -mpu6000::get_mpu_val(sen_gyro, axis_z);	//Z方向のジャイロを見る。時計回り正
	gyro::cal_angular_velocity();	//gyroから角速度を計算[rad/s]
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
/*
 void gyro::set_least_square_slope() {
 //x,yとかはWikiの最小二乗法と同じ。xは時間[ms],yは角度[°]
 float x_square_sum = 0, x_sum = 0, y_sum = 0, xy_sum = 0;
 float temp_count = 0;
 float temp_gyro;

 mouse::reset_count();

 while (mouse::get_count_ms() < LEAST_SQUARE_TIME) {
 temp_count = (float) mouse::get_count_ms();
 temp_gyro = gyro::get_angle_radian();

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
 */
void gyro::set_gyro_ref() {
	gyro_ref = get_gyro_ref();

	/*	ジャイロの補正に最小二乗法は使ってない
	 set_least_square_slope();	//最小二乗法による補正項導出
	 mouse::reset_count();
	 */
}

void gyro::set_angle(float set_rad) {
	angle = set_rad;
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

float gyro::get_angle_radian() {
	return angle;
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
const uint8_t encoder::MOVING_AVERAGE = 1;
const uint32_t encoder::MEDIAN = 32762;
float encoder::left_velocity, encoder::right_velocity, encoder::velocity;
int16_t encoder::raw_count[2] = { 0 };
float encoder::correct[2][4097] = { 0 };
bool encoder::correct_flag[2] = { false, false };
uint32_t encoder::init_time[2] = { 0 };
bool encoder::isCorrect[2] = { false, false };		//Y.I.式補正を行っているかどうかのフラグ

void encoder::interrupt() {
	static float data_r[MOVING_AVERAGE] = { 0 };	//データを保存しておく配列
	float sum_r = 0;
	static float data_l[MOVING_AVERAGE] = { 0 };	//データを保存しておく配列
	float sum_l = 0;
	float delta_value_r, delta_value_l;

	for (uint8_t i = 0; (i + 1) < MOVING_AVERAGE; i++) {
		data_r[i] = data_r[i + 1];	//配列を1つずらす
		sum_r += data_r[i];			//ついでに加算する
		data_l[i] = data_l[i + 1];	//配列を1つずらす
		sum_l += data_l[i];			//ついでに加算する
	}

	//エンコーダ―の値を取得
	delta_value_r = 32762 - static_cast<float>(TIM3->CNT);
	delta_value_l = static_cast<float>(TIM2->CNT) - 32762;

	TIM2->CNT = 32762;
	TIM3->CNT = 32762;

	//Y.I.式補正テーブルが完成していたら、Y.I.式補正をする.してなかったら移動平均をとる
	if (isCorrect[enc_right])
		//補正した差分を使って速度をとる
		right_velocity = raw_to_correct(enc_right, delta_value_r)
				* ENCODER_CONST / CONTROL_PERIOD * tire_R;//count*[rad/count]/[sec]*[m]
	else {
		//移動平均をとる
		//配列の最後に入れる
		data_r[(MOVING_AVERAGE - 1)] = delta_value_r * ENCODER_CONST
				/ CONTROL_PERIOD * tire_R;		//count*[rad/count]/[sec]*[m]
		sum_r += data_r[(MOVING_AVERAGE - 1)];
		right_velocity = sum_r / MOVING_AVERAGE;
	}
	if (isCorrect[enc_left])
		//補正した差分を使って速度をとる
		left_velocity = raw_to_correct(enc_left, delta_value_l) * ENCODER_CONST
				/ CONTROL_PERIOD * tire_R;		//count*[rad/count]/[sec]*[m]
	else {
		//移動平均をとる
		//配列の最後に入れる
		data_l[(MOVING_AVERAGE - 1)] = delta_value_l * ENCODER_CONST
				/ CONTROL_PERIOD * tire_R;		//count*[rad/count]/[sec]*[m]
		sum_l += data_l[(MOVING_AVERAGE - 1)];
		left_velocity = sum_l / MOVING_AVERAGE;
	}

	velocity = (right_velocity + left_velocity) / 2;

	//補正用にデータを保存
	if (correct_flag[enc_right]) {
		raw_count[enc_right] += static_cast<int16_t>(delta_value_r);//正転で増えていく方向に
		if (raw_count[enc_right] < 0)
			raw_count[enc_right] += 4096;
		else if (raw_count[enc_right] > 4096) {
			raw_count[enc_right] %= 4096;
			correct_flag[enc_right] = false;	//補正テーブル作成完了
			isCorrect[enc_right] = true;		//補正フラグを建てる
			//（厳密には補正テーブルはまだできていないが作成途中ではエンコーダーの値を参照しないのでこの時点で建てる）
		} else {
			//オーバーフローしないときは保存していく
			correct[enc_right][raw_count[enc_right]] =
					static_cast<float>(wait::get_count() - init_time[enc_right]);//時間を保存
		}
	}
	if (correct_flag[enc_left]) {
		raw_count[enc_left] += static_cast<int16_t>(delta_value_l);	//正転で増えていく方向に
		if (raw_count[enc_left] < 0)
			raw_count[enc_left] += 4096;
		else if (raw_count[enc_left] > 4096) {
			raw_count[enc_left] %= 4096;
			correct_flag[enc_left] = false;
			isCorrect[enc_left] = true;		//補正を完了フラグを建てる
			//（厳密には補正テーブルはまだできていないが作成途中ではエンコーダーの値を参照しないのでこの時点で建てる）
		} else {
			//オーバーフローしないときは保存していく
			correct[enc_left][raw_count[enc_left]] =
					static_cast<float>(wait::get_count() - init_time[enc_left]);//時間を保存
		}
	}

}

float encoder::get_velocity() {
	return velocity;

	//松井さん方式　http://matsui-mouse.blogspot.jp/2014/03/blog-post_26.html
	//カルマンフィルタで加速度とセンサフュージョンしてるからコレしないでいい気がする
	/*
	 return (velocity
	 + accelmeter::get_accel(axis_y) * accelmeter::AVERAGE_COUNT
	 * accelmeter::ACCEL_PERIOD / 2);
	 */
}

volatile float encoder::raw_to_correct(ENC_SIDE enc_side, int16_t raw_delta) {
	float temp_delta = 0;						//エンコーダーの前回との差分をとる
	static float correct_cnt[2] = { 0 };		//補正後の値を記録

	raw_count[enc_right] += raw_delta;
	if (raw_count[enc_right] > 4096) {
		raw_count[enc_right] -= 4096;
		temp_delta += 4096;	//上方向のオーバーフローしたので差分値も先に補正しておく
	} else if (raw_count[enc_right] < 0) {
		raw_count[enc_right] += 4096;
		temp_delta -= 4096;	//下方向のオーバーフローしたので差分値も先に補正しておく
	}
	temp_delta += (correct[enc_right][raw_count[enc_right]]
			- correct_cnt[enc_right]);	//YI式補正テーブルで補正し、前回との差分をとる
	correct_cnt[enc_right] = correct[enc_right][raw_count[enc_right]];	//値を更新
	//補正直後の1msだけエンコーダーの差分を求める式が初期値の問題でバグる。そんなすぐにはエンコーダー参照しないので問題ないはず

	return temp_delta;	//速度を求めるために補正した差分を使う
}

volatile void encoder::yi_correct(ENC_SIDE enc_side) {
	mouse::run_init(false, false);
	if (enc_side == enc_right)
		motor::set_duty(MOTOR_SIDE::m_right, 30);
	else
		motor::set_duty(MOTOR_SIDE::m_left, 25);

	//補正テーブルを全消去
	isCorrect[enc_side] = false;	//Y.I.式補正は中止
	for (int i = 0; i < 4097; i++) {
		correct[enc_side][i] = -1;
	}

	wait::ms(3000);	//回転が平衡状態に達するまで待機

	correct_flag[enc_side] = true;
	//初期値代入
	raw_count[enc_side] = 0;
	correct[enc_side][0] = 0;
	init_time[enc_side] = wait::get_count();
	while (correct_flag[enc_side])
		;	//一周分測定
	int16_t finish_val = raw_count[enc_side];	//4096を少し超えて終了するので、0より少し大きい値のはず
	float finish_time = static_cast<float>(wait::get_count()
			- init_time[enc_side]);	//終了した時間を保存

	motor::sleep_motor();

	//とびとびで値が保存されているはずなので、補完する
	int16_t bigger_val = 0;		//線系補完するときの、大きいほうのエンコーダ―の生値
	float bigger_time = 0;		//線系補完するときの、大きいほうの時間
	if (correct[enc_side][4096] == -1) {	//ぴったり4096で終わってなかったら
		bigger_val = 4096 + finish_val;
		bigger_time = finish_time;
	} else {								//ぴったり終わっていれば、最後の値をそのまま入れる
		bigger_val = 4096;
		bigger_time = correct[enc_side][4096];
	}
	for (int i = 4096; i >= 0; i--) {	//おしりから値が入っていないところを探していく
		if (correct[enc_side][i] != -1) {		//値が入っていたら
			if (bigger_val - i <= 1) {
			}
			//値が入っているのが連続なら線系補完はしない(4096に値が入っている場合のために不等号)
			else {
				//間のやつらを線形補完する
				float a = (bigger_time - correct[enc_side][i])
						/ static_cast<float>(bigger_val - i);	//傾き
				for (int j = MIN(bigger_val - 1, 4096); j > i; j--) {//bigger_val ~ i までの間を線系補完
					correct[enc_side][j] = static_cast<float>(a * (j - i)
							+ correct[enc_side][i]);	//傾き×現在値＋切片　で線形補完
				}
			}
			//bigger を更新して次へ
			bigger_val = i;
			bigger_time = correct[enc_side][i];
		}
	}

	//ここまででcorrectに連続で値が入ったはず.なので次はcorrectを「correct[生値]=計測時間」から「correct[生値]=補正値」に直していく
	float slope = 4096 / correct[enc_side][4096];//生値/時間の傾き。観測量は曲線だが真の値は直線のはずなのでこれで補正値を求める
	//全て時間から補正値に変換
	for (int i = 0; i < 4097; i++)
		correct[enc_side][i] *= slope;

}

void encoder::yi_correct() {
	control::ignore_failsafe(true);		//補正中はフェイルセーフを切る

	//左右で補正を行う
	yi_correct(enc_right);
	yi_correct(enc_left);
	control::reset_delta(sen_encoder);

	control::ignore_failsafe(false);		//フェイルセーフを復活
}

void encoder::draw_correct(bool right, bool left) {
	if (!right)
		if (!left)
			return;
	for (int i = 0; i < 4097; i++) {
		myprintf("%d", i);
		if (right)
			myprintf(", %f", correct[enc_right][i]);
		if (left)
			myprintf(", %f", correct[enc_left][i]);
		myprintf("\n\r");
	}
}

encoder::encoder() {
}

encoder::~encoder() {

}

float photo::ave_buf[PHOTO_TYPE::element_count][GAP_AVE_COUNT] = { 0.0f };
//float photo::diff_buf[PHOTO_TYPE::element_count][GAP_AVE_COUNT] = { 0 };
//uint8_t photo::gap_buf[PHOTO_TYPE::element_count][GAP_AVE_COUNT] = { 0 };
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

	default:
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
	case PHOTO_TYPE::right:
		ADCx = ADC1;
		ADC_CH = ADC_Channel_15;
		break;

	case PHOTO_TYPE::left:
		ADCx = ADC1;
		ADC_CH = ADC_Channel_11;
		break;

	case PHOTO_TYPE::front_right:
		ADCx = ADC1;
		ADC_CH = ADC_Channel_8;
		break;

	case PHOTO_TYPE::front_left:
		ADCx = ADC1;
		ADC_CH = ADC_Channel_10;
		break;

	case PHOTO_TYPE::front:
		ADCx = ADC1;
		ADC_CH = ADC_Channel_14;
		break;

	default:
		break;
	}

	//ad変換
	ADC_ClearFlag(ADCx, ADC_FLAG_EOC);		//EndFlagをクリアする
	ADC_RegularChannelConfig(ADCx, ADC_CH, 1,
	ADC_SampleTime_3Cycles);		//ADCxのADC_CHを
	ADC_SoftwareStartConv(ADCx);	//ADCを開始
	while (ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC) == RESET)
		;		//終わるまで待つ

	return (ADC_GetConversionValue(ADCx) >> 4);	//値を取得　4ビットシフトでうまくいってる気がする　右詰めのはずなのに意味わからん。

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

	static int16_t buf[element_count][PHOTO_AVERAGE_TIME] = { 0 };

	int16_t sum = 0;
	float ave_sum = 0;

	for (uint8_t i = 0; (i + 1) < MAX(PHOTO_AVERAGE_TIME, GAP_AVE_COUNT); i++) {
		if ((i + 1) < PHOTO_AVERAGE_TIME) {		//配列の要素外にアクセスしないように
			buf[sensor_type][i] = buf[sensor_type][i + 1];	//配列を1つずらす
			sum += buf[sensor_type][i];			//ついでに加算する
		}
		if ((i + 1) < GAP_AVE_COUNT) {		//配列の要素外にアクセスしないように
			ave_buf[sensor_type][i] = ave_buf[sensor_type][i + 1];	//配列を1つずらす
			//diff_buf[sensor_type][i] = diff_buf[sensor_type][i + 1];//配列を1つずらす
			//gap_buf[sensor_type][i] = gap_buf[sensor_type][i + 1];	//配列を1つずらす
			ave_sum += ave_buf[sensor_type][i];			//ついでに加算する
		}
	}

	//配列の最後に入れる
	buf[sensor_type][(PHOTO_AVERAGE_TIME - 1)] = set_value;	//count*[rad/count]/[sec]*[m]
	sum += set_value;

	int16_t now_val = sum / PHOTO_AVERAGE_TIME; 	//見やすさのため名前を付ける
	switch (sensor_type) {
	case PHOTO_TYPE::right:
		right_ad = now_val;
		break;

	case PHOTO_TYPE::left:
		left_ad = now_val;
		break;

	case PHOTO_TYPE::front_right:
		front_right_ad = now_val;
		break;

	case PHOTO_TYPE::front_left:
		front_left_ad = now_val;
		break;

	case front:
		front_ad = now_val;
		break;

	default:
		break;
	}

	ave_buf[sensor_type][(GAP_AVE_COUNT - 1)] = now_val;

	/*
	 ave_sum += get_displacement_from_center(sensor_type);
	 //移動平均をとったセンサ値と、それのさらに平均をとったものとの差分を記録
	 //この値は平均を2回取るので、平均区間の真ん中あたりが強調される＝少し前の真値のようなものと考えることができる
	 //その差分なので、おおよそノイズの影響を除去した傾きが分かると信じてる
	 diff_buf[sensor_type][(GAP_AVE_COUNT - 1)] = ave_sum / GAP_AVE_COUNT
	 - static_cast<float>(now_val);
	 gap_buf[sensor_type][(GAP_AVE_COUNT - 1)] = count_wall_gap(sensor_type);//使ってない
	 */
}

void photo::interrupt(bool is_light) {
	const static int wait_number = 1200;	//1000でだいたい100us弱	1500で120usくらい
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
//FIX_ME 左右の発光時間を延ばすために、斜めセンサは切ってる
	/*
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
	 */
	if (is_light) {
		photo::light(front);
		for (int i = 0; i < wait_number * 2; i++) {
		}
	}
	photo::set_ad(front, get_ad(front) - get_ref(front));	//差分を代入
	photo::turn_off(front);
}

int16_t photo::get_ref(PHOTO_TYPE sensor_type) {
	switch (sensor_type) {
	case PHOTO_TYPE::right:
		return right_ref;
		break;

	case PHOTO_TYPE::left:
		return left_ref;
		break;

	case PHOTO_TYPE::front_right:
		return front_right_ref;
		break;

	case PHOTO_TYPE::front_left:
		return front_left_ref;
		break;

	case PHOTO_TYPE::front:
		return front_ref;
		break;

	default:
		break;
	}

	return 0;
}

void photo::set_ref(PHOTO_TYPE sensor_type, int16_t set_value) {
	switch (sensor_type) {
	case PHOTO_TYPE::right:
		right_ref = set_value;
		break;

	case PHOTO_TYPE::left:
		left_ref = set_value;
		break;

	case PHOTO_TYPE::front_right:
		front_right_ref = set_value;
		break;

	case PHOTO_TYPE::front_left:
		front_left_ref = set_value;
		break;

	case PHOTO_TYPE::front:
		front_ref = set_value;
		break;

	default:
		break;
	}
}

float photo::get_value(PHOTO_TYPE sensor_type) {
	int16_t ad = 0;
	switch (sensor_type) {
	case PHOTO_TYPE::right:{
		ad = right_ad;
		break;
	}
	case PHOTO_TYPE::left:{
		ad = left_ad;
		break;
	}
	case PHOTO_TYPE::front_right:{
		ad = front_right_ad;
		break;
	}
	case PHOTO_TYPE::front_left:{
		ad = front_left_ad;
		break;
	}
	case PHOTO_TYPE::front:{
		ad = front_ad;
		break;
	}
	default:
		break;
	}

	return static_cast<float>(ad) * 4.0 / get_battery();	//電圧で値が減っている気がするので補正
}

float photo::get_displacement_from_center_debag(PHOTO_TYPE sensor_type) {

	my7seg::light(4);

	float f = photo::get_value(sensor_type);		//現在のセンサ値に対して求める

	my7seg::light(5);

	float f_c = static_cast<float>(parameter::get_ideal_photo(sensor_type));//中心位置におけるセンサ値

	//フォトセンサの特性を示すパラメータ
	float a = 0;

	switch (sensor_type) {
	case PHOTO_TYPE::right:
		a = 0.058;
		break;

	case PHOTO_TYPE::left:
		a = -0.056;
		break;

	case PHOTO_TYPE::front_right:
		a = 0;
		break;

	case PHOTO_TYPE::front_left:
		a = 0;
		break;

	case PHOTO_TYPE::front:
		a = 0.0398;
		break;

	default:
		break;
	}

	my7seg::light(6);
	//センサ値fは f=f_c*exp(a*x) と仮定し、xを求める。-> x = 1/a*log(f/f_c)
	//f_c:中心のセンサ値、x:中心からのずれ[mm]
	if (a == 0)
		return 0;
	return (my_math::log(f / f_c) / a * 0.001);		//[m]

}

float photo::get_side_from_center(PHOTO_TYPE type) {
	float val = (photo::get_value(type));		//現在のセンサ値に対して求める
	return (get_side_from_center(type, val));
}

float photo::get_side_from_center(PHOTO_TYPE sensor_type, float val) {

	float f = val;		//対称のセンサ値
	float f_c = static_cast<float>(parameter::get_ideal_photo(sensor_type));//中心位置におけるセンサ値

	//フォトセンサの特性を示すパラメータ
	float a = 0;

	switch (sensor_type) {
	case PHOTO_TYPE::right:
		a = 0.058;
		break;

	case PHOTO_TYPE::left:
		a = -0.056;
		break;

	case PHOTO_TYPE::front_right:
		a = 0;
		break;

	case PHOTO_TYPE::front_left:
		a = 0;
		break;

	case PHOTO_TYPE::front: {
		a = 0.0398;
		break;
	}

	default:
		break;
	}

	//センサ値fは f=f_c*exp(a*x) と仮定し、xを求める。-> x = 1/a*log(f/f_c)
	//f_c:中心のセンサ値、x:中心からのずれ[mm]
	return (my_math::log(f / f_c) / a * 0.001);		//[m]
}

bool photo::check_wall(unsigned char muki) {

	switch (muki) {
	case MUKI_RIGHT:
		if (photo::get_value(PHOTO_TYPE::right)
				>= parameter::get_min_wall_photo(PHOTO_TYPE::right)) {
			return true;
		}
		return false;

	case MUKI_LEFT:
		if (photo::get_value(PHOTO_TYPE::left)
				>= parameter::get_min_wall_photo(PHOTO_TYPE::left)) {
			return true;
		}
		return false;

	case MUKI_UP:
		//TODO 暇があったら、前壁見るのは斜めセンサいらない？？
		if (photo::get_value(PHOTO_TYPE::front)
				>= parameter::get_min_wall_photo(PHOTO_TYPE::front)) {
			//if ((front_right_ad >= parameter::get_min_wall_photo(front_right))
			//		|| (front_left_ad >= parameter::get_min_wall_photo(front_left))) {
			return true;
		}
		return false;
	}

	return false;

}

bool photo::check_wall(PHOTO_TYPE type) {
	if (photo::get_value(type) >= parameter::get_min_wall_photo(type))
		return true;
	else
		return false;

}
/*
 int8_t photo::count_wall_gap(PHOTO_TYPE type) {
 int8_t count = 0;	//負（センサ値が下がってる）の数を数える
 for (uint8_t i = 0; i < GAP_AVE_COUNT; i++) {
 if (diff_buf[type][i] < 0)
 count--;
 else
 count++;
 }
 return count;
 }
 */
bool photo::check_wall_gap(PHOTO_TYPE type, float threshold) {
	//壁の切れ目ならtrue
	//急に壁が現れた時も制御を切る

	float before_val = get_side_from_center(type, ave_buf[type][0]);
	float now_val = get_side_from_center(type,
			ave_buf[type][GAP_AVE_COUNT - 1]);

	if (ABS(now_val-before_val) > ABS(threshold)) {		//壁の切れ目
		return true;
	}

	return false;

}

photo::photo() {
}

photo::~photo() {
}

//XXX 各種ゲイン
//control関連
const PID gyro_gain = { 15, 750, 0.015 };
const PID photo_gain = { 300, 0, 0.001 };
const PID encoder_gain = { 200, 1000, 0, };	//カルマンフィルタでエンコーダーと加速度センサから求めた速度に対するフィルタ
const PID accel_gain = { 0, 0, 0 };	//{50, 0, 0 };

PID control::gyro_delta, control::photo_delta, control::encoder_delta,
		control::accel_delta;
bool control::control_phase = false;
bool control::wall_control_flag = false;
bool control::ignore_fail_safe = false;
//XXX FF制御とFB制御やるかやらないか決める場所
bool control::is_FF_CONTROL = true;
bool control::is_FB_CONTROL = true;

volatile float control::cross_delta_gain(SEN_TYPE sensor) {
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

	case sen_accel:
		return (accel_delta.P * accel_gain.P + accel_delta.I * accel_gain.I
				+ accel_delta.D * accel_gain.D);

	default:
		break;

	}
	return 0;
}

//XXX 偏差を計算してる場所
void control::cal_delta() {
	float before_p_delta;

	//エンコーダーのΔ計算
	before_p_delta = encoder_delta.P;	//積分用
	encoder_delta.P = (mouse::get_ideal_velocity() - mouse::get_velocity());
	encoder_delta.I += (encoder_delta.P * CONTORL_PERIOD);
	encoder_delta.D = (encoder_delta.P - before_p_delta) / CONTORL_PERIOD;

	//センサーのΔ計算

	float photo_right_delta = 0, photo_left_delta = 0;
	before_p_delta = photo_delta.P;
	if (control::get_wall_control_phase()) {
		if (photo::check_wall(PHOTO_TYPE::right)) {
			//if (!photo::check_wall_gap(right, 0.005))		//壁キレでないなら
			photo_right_delta = photo::get_side_from_center(
					PHOTO_TYPE::right);		//中心からのずれてる距離[m]
		}
		if (photo::check_wall(PHOTO_TYPE::left)) {
			//if (!photo::check_wall_gap(left, 0.025))		//壁キレでないなら
			photo_left_delta = photo::get_side_from_center(
					PHOTO_TYPE::left);		//中心からのずれてる距離[m]
		}

		if (photo_right_delta == 0)
			photo_left_delta *= 2;
		else if (photo_left_delta == 0)
			photo_right_delta *= 2;

		//photo_correct = (photo_right_delta + photo_left_delta) / 2;		//センサ値から推定した値をカルマンフィルタの推定値とする
		photo_delta.P = (photo_right_delta + photo_left_delta) / 2;

		static const float half_section = 0.045 * MOUSE_MODE;	//1区間の半分の長さ
		//柱近傍はセンサ値を信用しない。 区画の中央部分
		if (ABS(mouse::get_relative_go() - 0.01 * MOUSE_MODE)
				< (half_section * 0.6)) {
			photo_delta.P = 0;//mouse::get_relative_side();		//センサを信用しない　= 推定値を突っ込んどく
		}

		//速度が低いと制御が効きすぎるので（相対的に制御が大きくなる）、切る
		if (mouse::get_ideal_velocity() < SEARCH_VELOCITY * 0.5) {
			photo_delta.P = 0;
		}
		photo_delta.I += (photo_delta.P * CONTORL_PERIOD);
		photo_delta.D = mouse::get_velocity() * mouse::get_relative_rad();//Vθ オドメトリから求めたD項　Sinθ~θと近似
		//if(photo_delta.P != 0)
		//	photo_delta.D = (photo_delta.P - before_p_delta) / CONTROL_PERIOD;
	} else {
		//壁制御かけないときは初期化し続ける。
		photo_delta.P = 0;
		photo_delta.I = 0;
		photo_delta.D = 0;
	}

	//ジャイロのΔ計算
	before_p_delta = gyro_delta.P;	//積分用
	gyro_delta.P = (mouse::get_ideal_angular_velocity()
			- gyro::get_angular_velocity());
	gyro_delta.P -= cross_delta_gain(sen_photo);		//壁制御量を目標角速度に追加
	gyro_delta.I += (gyro_delta.P * CONTORL_PERIOD);
	gyro_delta.D = (gyro_delta.P - before_p_delta) / CONTROL_PERIOD;
	/*
	 //加速度の偏差計算
	 before_p_delta = accel_delta.P;	//積分用
	 accel_delta.P = (mouse::get_ideal_accel() - accelmeter::get_accel());
	 accel_delta.I += (accel_delta.P * CONTORL_PERIOD);
	 accel_delta.D = (accel_delta.P - before_p_delta) / CONTORL_PERIOD;
	 */
}

float control::control_accel() {
	return cross_delta_gain(sen_accel);
}

float control::control_velocity() {
	return cross_delta_gain(sen_encoder);
}

float control::control_angular_velocity() {
	return cross_delta_gain(sen_gyro);
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
	float accel;		//目標加速度

	if (right_or_left == MUKI_RIGHT) {			//右のモーターなら
		velocity = mouse::get_ideal_velocity()
				- (mouse::get_ideal_angular_velocity() * TREAD_W / 2);
		accel = mouse::get_ideal_accel()
				- (mouse::get_ideal_angular_accel() * TREAD_W / 2);

	} else {									//左のモーターなら
		velocity = mouse::get_ideal_velocity()
				+ (mouse::get_ideal_angular_velocity() * TREAD_W / 2);
		accel = mouse::get_ideal_accel()
				+ (mouse::get_ideal_angular_accel() * TREAD_W / 2);

	}

	float Vinv;		//motorが回転することによる逆気電圧
	float Vt;		//motorを回転させるために必要なトルクを生み出すための電圧

	// V = v[m/s]/2πr[m] * ギア比  / 電圧特性[回/s/V]
	Vinv = (velocity / (2 * PI() * tire_R) * SPAR / PINION / MOTOR_CONST);

	float mu = 0.00035;	//摩擦力
	// V = 加速に必要な分 + 摩擦力を打ち消す分
	Vt = ((PI() * tire_R * MASS * MOTOR_ORM * MOTOR_CONST) * accel
			+ (2 * PI() * MOTOR_ORM * MOTOR_CONST * mu)) * PINION / SPAR;

	return ((Vinv + Vt) * M_SUM_ORM / MOTOR_ORM / get_battery()) * 100;
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

			motor::set_duty(m_right, duty_r);
			motor::set_duty(m_left, duty_l);
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
	reset_delta(sen_accel);

}

volatile void control::reset_delta(SEN_TYPE type) {

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
		accel_delta.P = 0;
		accel_delta.I = 0;
		accel_delta.D = 0;
		break;

	default:
		break;
	}
}

void control::fail_safe() {

	//フェイルセーフを無視するなら何もしない
	if (ignore_fail_safe)
		return;

	//閾値どのくらいかわからない。Gyroも参照すべき？
	if (ABS(encoder_delta.P) > 1) {
		if (ABS(gyro_delta.P) > 3) {
			motor::sleep_motor();
			mouse::set_fail_flag(true);
		}
	}
}

void control::ignore_failsafe(bool ignore) {
	ignore_fail_safe = ignore;
}

control::control() {
}

control::~control() {

}

void kalman::update(float EstimateU, float ObserveZ) {
	float esX = x + EstimateU;		//前回の値に推定分だけずれた値を推定値とする
	float esP = p + EstP;			//前回の分散に推定分だけ分散を増やす
	float delta = ObserveZ - esX;	//観測量と推定値の差分
	float K = esP / (ObsP + esP);	//カルマンゲイン

	x = esX + K * delta;	//カルマンフィルタで推定値を補正
	p = (1 - K) * esP;		//補正後の分散
}

float kalman::get_value() {
	return x;
}

float kalman::get_dispersion() {
	return p;
}

kalman::kalman() {
	x = 0;
	p = 0;
	EstP = 0;
	ObsP = 0;
}

kalman::kalman(float EstimateP, float ObserveP) {
	x = 0;
	p = 0;
	EstP = EstimateP;
	ObsP = ObserveP;
}

kalman::kalman(float initX, float initP, float EstimateP, float ObserveP) {
	x = initX;
	p = initP;
	EstP = EstimateP;
	ObsP = ObserveP;
}

kalman::~kalman() {
}
