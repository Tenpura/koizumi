/*
 * hardware.h
 *
 *  Created on: 2015/06/14
 *      Author: Koizumi
 */

#ifndef HARDWARE_H_
#define HARDWARE_H_

#include "stm32f4xx.h"
#include "define.h"
#include "extern_c.h"
#include "user.h"
#include "init.h"

/*
 #include"define.h"
 #include"parameter.h"
 #include"ad_convert.h"
 #include"user.h"
 #include"run.h"
 */


//����7�Z�O�֘A
class my7seg {
private:
public:
	static void light(const unsigned char number);		//����
	static void turn_off();		//����

	static void light_error();		//E�ƌ��点��

	//repeat_count�񂾂��_�ł���B�����Ă��ԂŏI���
	static void blink(const unsigned char number,
			const unsigned short blink_cycle_ms,
			const unsigned short repeat_count);

	//start_number����0�܂ŃJ�E���g�_�E��
	static void count_down(const unsigned char start_number,
			const unsigned short cycle_ms);

};


//motor�֘A
extern const uint16_t MAX_PERIOD;
enum MOTOR_SIDE{
		motor_left=0,
		motor_right=1
};

class motor {
private:

	static signed short get_duty_left();	//�����[�^�[��Duty�擾
	static signed short get_duty_right();//�E���[�^�[��Duty�擾

	static const char MAX_DUTY;	 	//Duty�̍ő�l�m���n
	static const char MAX_COUNT;	//Duty�̍ő�l�m���n

	motor();

public:
	static signed char right_duty,left_duty;		//duty[��]

	static void set_duty(const MOTOR_SIDE side, const signed short set_duty);//���[�^�[��Duty����

	static void sleep_motor();//���[�^�[�h���C�o���X���[�v��Ԃ�
	static void stanby_motor();//���[�^�[�h���C�o���X�^���o�C��Ԃ�

	~motor();
};



//gyro�֘A
//���v��肪��
class mpu6000{
private:
	static SPI_TypeDef* use_SPI;	//�g��SPI�̃^�C�v
	static GPIO_TypeDef* cs_GPIOx;	//cs��������IO�s���̃^�C�v		ex)GPIOA
	const static uint16_t cs_GPIO_Pin;	//cs��������IO�s���̔ԍ�

protected:
	static uint16_t read_spi(uint16_t read_reg);		//SPI�ʐM��reg���W�X�^����ǂ݂���
	static void write_spi(uint16_t reg, uint16_t data);		//SPI�ʐM��reg���W�X�^��data����������
	mpu6000();

public:
	static void init_mpu6000();

	~mpu6000();


};

class gyro : public mpu6000{
private:
	static const float GYRO_PERIOD;			//�W���C���̐������[s]
	static const float REF_TIME;			//�W���C���̃��t�@�����X�Ƃ鎞��[s]

	static unsigned short gyro_value;
	static float default_angle;				//�ŏ����@�ŕ␳�������ĂȂ��p�x
	static float angle,before_angle,gyro_ref;
	static float angular_velocity;

	static float get_gyro_ref();
	static void set_least_square_slope();//�ŏ����@���܂킵�ĕ␳�����v�Z

	gyro();

public:
	static float least_square_slope;//�␳���̌X��

	static void interrupt_gyro();
	static unsigned short get_gyro();
	static void set_gyro_ref();

	static void reset_angle();
	static void cal_angle();//�p�x�v�Z[��]
	static float get_angle();

	static void cal_angular_velocity();//�p���x�v�Z[rad/s]
	static float get_angular_velocity();

	~gyro();

};


//encoder
class encoder {
private:
	const static uint32_t MOVING_AVERAGE;	//�ړ����ς��Ƃ鎞�ԁ@�P�ʂ͐������
	const static uint32_t MEDIAN;		//�J�E���g�̒����l

	static float right_velocity,left_velocity,velocity;
	encoder();

public:
	static void cal_encoder();		//���[�^�[��Encoder�̒l�v�Z
	static float get_velocity();//���E�̕���(�d�S���x)��Encoder�擾[m/s]�@ �ړ����ώ���Ă邱�Ƃɒ��ӁI

	~encoder();
};

#endif /* HARDWARE_H_ */
