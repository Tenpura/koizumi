/*
 * hardware.cpp
 *
 *  Created on: 2015/06/13
 *      Author: Koizumi
 */

#include"hardware.h"

//����7�Z�O�֘A

void my7seg::light(const unsigned char number) {

	//7�Z�O�ŕ\���ł���킯�˂�����I
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

//motor�֘A
signed char motor::right_duty = 0, motor::left_duty = 0;
const char motor::MAX_DUTY = 100;

void motor::set_duty(const MOTOR_SIDE side, const signed short set_duty) {
	signed short duty = 0;		//�ꎞ�I�ȕۑ�

	//Duty�ɐ�Βl���Ƃ�
	duty = ABS(set_duty);

	//�����؂�
	if (set_duty > MAX_DUTY)
		duty = MAX_DUTY;

	static TIM_OCInitTypeDef TIM_OC_InitStructure;
	TIM_OC_InitStructure.TIM_OCMode = TIM_OCMode_PWM1;		//���[�h��PWM1
	TIM_OC_InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//���Ԃ񂢂�Ȃ��BThis parameter is valid only for TIM1 and TIM8.
	TIM_OC_InitStructure.TIM_OutputState = TIM_OutputState_Enable;//���Ԃ񂢂�Ȃ��BThis parameter is valid only for TIM1 and TIM8.

	TIM_OC_InitStructure.TIM_Pulse = (uint32_t) (MAX_PERIOD * duty * 0.01);	//duty�ɉ����ăJ�E���g��ύX
//static_cast<uint32_t>
	myprintf("duty ->%d\n\r", (duty));
	myprintf("motor's duty ->%f\n\r", (MAX_PERIOD * duty * 0.01));

	if (side == motor_left) {

		if (set_duty == 0) {					//0�̂Ƃ���stop
			TIM_OC_InitStructure.TIM_Pulse = 0;		//duty0�̎��͈ꉞ0�������Ă���
			TIM_OC1Init(TIM4, &TIM_OC_InitStructure);		//TIM4��CH1
			TIM_OC2Init(TIM4, &TIM_OC_InitStructure);		//TIM4��CH2

		} else if (set_duty > 0) {				//���̂Ƃ��͐��]
			TIM_OC1Init(TIM4, &TIM_OC_InitStructure);		//TIM4��CH1
			TIM_OC_InitStructure.TIM_Pulse = 0;		//�d�ʍ�����邽�߁A�Е���0��
			TIM_OC2Init(TIM4, &TIM_OC_InitStructure);		//TIM4��CH2

		} else {									//���̂Ƃ��͋t�]
			TIM_OC2Init(TIM4, &TIM_OC_InitStructure);		//TIM4��CH2
			TIM_OC_InitStructure.TIM_Pulse = 0;		//�d�ʍ�����邽�߁A�Е���0��
			TIM_OC1Init(TIM4, &TIM_OC_InitStructure);		//TIM4��CH1

		}

		left_duty = duty;
	}

	if (side == motor_right) {

		if (set_duty == 0) {					//0�̂Ƃ���stop
			TIM_OC_InitStructure.TIM_Pulse = 0;		//duty0�̎��͈ꉞ0�������Ă���

			TIM_OC1Init(TIM5, &TIM_OC_InitStructure);		//TIM5��CH1
			TIM_OC2Init(TIM5, &TIM_OC_InitStructure);		//TIM5��CH2
		} else if (set_duty > 0) {				//���̂Ƃ��͐��]
			TIM_OC1Init(TIM5, &TIM_OC_InitStructure);		//TIM5��CH1

			TIM_OC_InitStructure.TIM_Pulse = 0;		//�d�ʍ�����邽�߁A�Е���0��
			TIM_OC2Init(TIM5, &TIM_OC_InitStructure);		//TIM5��CH2

		} else {									//���̂Ƃ��͋t�]
			TIM_OC2Init(TIM5, &TIM_OC_InitStructure);		//TIM5��CH2

			TIM_OC_InitStructure.TIM_Pulse = 0;		//�d�ʍ�����邽�߁A�Е���0��
			TIM_OC1Init(TIM5, &TIM_OC_InitStructure);		//TIM5��CH1
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
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);	//���[�^�[�h���C�o�[�X���[�v
	TIM_Cmd(TIM4, DISABLE);
	TIM_Cmd(TIM5, DISABLE);
	motor::set_duty(motor_left, 0);
	motor::set_duty(motor_right, 0);

}

void motor::stanby_motor() {
	GPIO_SetBits(GPIOA, GPIO_Pin_2);	//���[�^�[�h���C�o�[�X�^���o�C
	TIM_Cmd(TIM4, ENABLE);
	TIM_Cmd(TIM5, ENABLE);

}

motor::motor() {
}

motor::~motor() {

}

//gyro�֘A
SPI_TypeDef* mpu6000::use_SPI = SPI1;		//SPI1~3�̂ǂ�g���Ă邩
GPIO_TypeDef* mpu6000::cs_GPIOx = GPIOA;		//cs�@���s���̐ݒ�
const uint16_t mpu6000::cs_GPIO_Pin = GPIO_Pin_4;	//cs�@���s���̐ݒ�

//���W�X�^�[��`
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
	uint16_t reg = (read_reg | 128);	//read���̓��W�X�^�[�̍ŏ��Bit��1��

	GPIO_ResetBits(cs_GPIOx, cs_GPIO_Pin); // CS���Z�b�g

	//���W�X�^�w��
	while (SPI_I2S_GetFlagStatus(use_SPI, SPI_I2S_FLAG_TXE) == RESET)
		; // ���M�\�ɂȂ�܂ő҂�
	SPI_I2S_SendData(use_SPI, reg); // ���M
	while (SPI_I2S_GetFlagStatus(use_SPI, SPI_I2S_FLAG_RXNE) == RESET)
		; // ��M�\�ɂȂ�܂ő҂�
	data = SPI_I2S_ReceiveData(use_SPI); // ��f�[�^����M����

	//�f�[�^�̑���M
	while (SPI_I2S_GetFlagStatus(use_SPI, SPI_I2S_FLAG_TXE) == RESET)
		; // ���M�\�ɂȂ�܂ő҂�
	SPI_I2S_SendData(use_SPI, 0x00); // ���M
	while (SPI_I2S_GetFlagStatus(use_SPI, SPI_I2S_FLAG_RXNE) == RESET)
		; // ��M�\�ɂȂ�܂ő҂�
	data = SPI_I2S_ReceiveData(use_SPI); // ��M����
	while (SPI_I2S_GetFlagStatus(use_SPI, SPI_I2S_FLAG_TXE) == RESET)
		;

	GPIO_SetBits(cs_GPIOx, cs_GPIO_Pin); //CS�����Z�b�g

	return data;
}

void mpu6000::write_spi(uint16_t reg, uint16_t data) {

	GPIO_ResetBits(cs_GPIOx, cs_GPIO_Pin); // CS���Z�b�g

	//���W�X�^�w��
	while (SPI_I2S_GetFlagStatus(use_SPI, SPI_I2S_FLAG_TXE) == RESET)
		; // ���M�\�ɂȂ�܂ő҂�
	SPI_I2S_SendData(use_SPI, reg); // ���M
	while (SPI_I2S_GetFlagStatus(use_SPI, SPI_I2S_FLAG_RXNE) == RESET)
		; // ��M�\�ɂȂ�܂ő҂�
	SPI_I2S_ReceiveData(use_SPI); // ��f�[�^����M����

	//�f�[�^�̑���M
	while (SPI_I2S_GetFlagStatus(use_SPI, SPI_I2S_FLAG_TXE) == RESET)
		; // ���M�\�ɂȂ�܂ő҂�
	SPI_I2S_SendData(use_SPI, data); // ���M
	while (SPI_I2S_GetFlagStatus(use_SPI, SPI_I2S_FLAG_RXNE) == RESET)
		; // ��M�\�ɂȂ�܂ő҂�
	SPI_I2S_ReceiveData(use_SPI); // ��M����
	while (SPI_I2S_GetFlagStatus(use_SPI, SPI_I2S_FLAG_TXE) == RESET)
		;

	GPIO_SetBits(cs_GPIOx, cs_GPIO_Pin); //CS�����Z�b�g

}

uint16_t mpu6000::get_mpu6000_value(SEN_TYPE sen, AXIS_t axis) {
	uint16_t data = 0;
	uint16_t reg_h = 0;	//high�̒l�ւ̃��W�X�^
	uint16_t reg_l = 0;	//Low�̒l�ւ̃��W�X�^

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

	default:		//gyro�Ɖ����x�ȊO�͓ǂ߂Ȃ��̂ŏ����l��Ԃ��ďI��
		return data;
		break;
	}

	//High�̕��͏�ʂ�8�r�b�g���炵��Low�ƍ��킹�āA�ړI�̃f�[�^�𓾂�B
	data = (read_spi(reg_h) << 8) + read_spi(reg_l);

	return data;
}

void mpu6000::init_mpu6000() {
	static const uint16_t SIGNAL_PATH_RESET = 0x68;
	static const uint16_t PWR_MGMT_1 = 0x6B;
	static const uint16_t PWR_MGMT_2 = 0x6c;
	static const uint16_t USER_CTRL = 0x6a;
	static const uint16_t GYRO_CONFIG = 0x1b;
	static const uint16_t ACCEL_CONFIG = 0x1c;

	write_spi(SIGNAL_PATH_RESET, 0x06);	//�W���C���A�����x���Z�b�g
	write_spi(PWR_MGMT_1, 0x08);			//�T�C�N��1�ASLEEP�����A���x�Z���T�͎g��Ȃ�
	write_spi(USER_CTRL, 0x10);			//I2C��Disable�ASPI��Enable
	write_spi(GYRO_CONFIG, 0x18);		//�W���C�����}2000��/s�ɐݒ�
	write_spi(ACCEL_CONFIG, 0x18);		//�����x���}16g/s�ɐݒ�
	write_spi(PWR_MGMT_2, 0xEE);			//�W���C����Z�������A�����x��Y�������ȊO�͒�~
}

mpu6000::mpu6000() {
}

mpu6000::~mpu6000() {

}
unsigned short gyro::gyro_value;
float gyro::default_angle;
float gyro::angle, gyro::before_angle, gyro::gyro_ref;
float gyro::angular_velocity;
float gyro::least_square_slope = 0;
const float gyro::GYRO_PERIOD = CONTORL_PERIOD;		//�������[s]
const float gyro::REF_TIME = 1;							//���t�@�����X�Ƃ鎞��[s]

void gyro::interrupt_gyro() {
	gyro_value = mpu6000::get_mpu6000_value(sen_gyro, axis_z);		//Z�����̃W���C��������
}

unsigned short gyro::get_gyro() {
	return gyro_value;
}

float gyro::get_gyro_ref() {
	int32_t gyro_sum = 0;
	int i;
	for (i = 0; i < (REF_TIME / GYRO_PERIOD); i++) {
		gyro_sum += get_gyro();
		wait::ms(1);
	}

	return (gyro_sum / (i + 1));
}
/*
 void gyro::set_least_square_slope() {
 //x,y�Ƃ���Wiki�̍ŏ����@�Ɠ����Bx�͎���[ms],y�͊p�x[��]
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

 //1ms�o�܂őҋ@
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
	//XXX �W���C���̕␳�ɍŏ����@�͎g���ĂȂ�
	/*
	 set_least_square_slope();	//�ŏ����@�ɂ��␳�����o
	 mouse::reset_count();
	 */
}

void gyro::reset_angle() {
	default_angle = 0;
	before_angle = 0;
	angle = 0;
}

void gyro::cal_angle() {
	before_angle = angle;
	default_angle += (gyro_value - gyro_ref) * GYRO_CONST * LOGIK_V / 4096;

	angle = default_angle;
	//XXX�ŏ����@�ł̕␳�͂��ĂȂ�
	//�ŏ����@�ŕ␳����
	//angle = default_angle	- (least_square_slope * (float) mouse::get_count_ms());
}

float gyro::get_angle() {
	return angle;	//��
}

void gyro::cal_angular_velocity() {
	angular_velocity = radian((get_angle() - before_angle) / GYRO_PERIOD);
}

float gyro::get_angular_velocity() {
	return angular_velocity;	//[rad/s]
}

gyro::gyro() {

}

gyro::~gyro() {

}

//encoder�֘A
const uint32_t encoder::MOVING_AVERAGE = 30;
const uint32_t encoder::MEDIAN = 32762;
float encoder::left_velocity, encoder::right_velocity, encoder::velocity;

void encoder::cal_encoder() {
	static float sample_data[MOVING_AVERAGE] = { 0 };	//�f�[�^��ۑ����Ă����z��
	float sum = 0;

	//TODO ��ňڐA�I�I
	/*
	 left_velocity = (MTU2.TCNT - 32762) * ENCODER_CONST * TIRE_R;	//m/s
	 right_velocity = (MTU1.TCNT - 32762) * ENCODER_CONST * TIRE_R;//count*[rad/count]/[sec]*[m]
	 MTU1.TCNT = 32762;
	 MTU2.TCNT = 32762;

	 for (signed char i = 0; (i + 1) < MOVING_AVERAGE; i++) {
	 sample_data[i + 1] = sample_data[i];	//�z���1���炷
	 sum += sample_data[i + 1];			//���łɉ��Z����
	 }
	 sample_data[0] = (right_velocity + left_velocity) / 2;	//�z��̍ŏ��ɓ����
	 sum += sample_data[0];
	 */
	velocity = sum / MOVING_AVERAGE;
}

float encoder::get_velocity() {

	return velocity;
}

encoder::encoder() {
}

encoder::~encoder() {

}

