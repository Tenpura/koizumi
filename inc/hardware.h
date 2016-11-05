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
#include "ad_convert.h"
#include "parameter.h"
#include"run.h"




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

	static bool motor_state;		//motor���N�����Ă����TRUE�B

	motor();

public:
	static signed char right_duty,left_duty;		//duty[��]

	static void set_duty(const MOTOR_SIDE side, const float set_duty);//���[�^�[��Duty����

	static void sleep_motor();//���[�^�[�h���C�o���X���[�v��Ԃ�
	static void stanby_motor();//���[�^�[�h���C�o���X�^���o�C��Ԃ�

	static bool isEnable();		//motor���N�����Ă��邩�ǂ���

	~motor();
};



//gyro�֘A
//���v��肪��
//�Z���T�[�^�C�v��\���񋓌^
typedef enum {
	axis_x = 0, axis_y = 1, axis_z = 2
} AXIS_t;
class mpu6000{
private:
	//���W�X�^�[��`
	static const uint16_t GYRO_XOUT_H;
	static const uint16_t GYRO_XOUT_L;
	static const uint16_t GYRO_YOUT_H;
	static const uint16_t GYRO_YOUT_L;
	static const uint16_t GYRO_ZOUT_H;
	static const uint16_t GYRO_ZOUT_L;
	static const uint16_t ACCEL_XOUT_H;
	static const uint16_t ACCEL_XOUT_L;
	static const uint16_t ACCEL_YOUT_H;
	static const uint16_t ACCEL_YOUT_L;
	static const uint16_t ACCEL_ZOUT_H;
	static const uint16_t ACCEL_ZOUT_L;


	static SPI_TypeDef* use_SPI;	//�g��SPI�̃^�C�v
	static GPIO_TypeDef* cs_GPIOx;	//cs��������IO�s���̃^�C�v		ex)GPIOA
	const static uint16_t cs_GPIO_Pin;	//cs��������IO�s���̔ԍ�

protected:
public:
	static uint16_t read_spi(uint16_t read_reg);		//SPI�ʐM��reg���W�X�^����ǂ݂���
	static void write_spi(uint16_t reg, uint16_t data);		//SPI�ʐM��reg���W�X�^��data����������
	static int16_t get_mpu_value(SEN_TYPE sen, AXIS_t axis);		//sen�Z���T�[��axis�������̃f�[�^��ǂ�

	mpu6000();

public:
	static void init_mpu6000();

	~mpu6000();


};

class accelmeter : public mpu6000{
public:
	static const uint8_t AVERAGE_COUNT;		//�����x�v�̕��ώ���[��]
	static const float ACCEL_PERIOD;		//�����x�v�̐������[s]

private:
	static const float REF_TIME;			//�����x�v�̃��t�@�����X�Ƃ鎞��[s]

	static float accel_ad;		//�O������̉����x�̐��l
	static float accel_ref;
	static float accel;		//�O������̉����x [m/ss]

	static float get_accel_ref();
	static float get_accel_ad();

	accelmeter();

public:

	static void interrupt();
	static void set_accel_ref();
	static void cal_accel();	//���l�������x�ɕϊ�[m/ss]

	static float get_accel();



};

class gyro : public mpu6000{
private:
	static const float GYRO_PERIOD;			//�W���C���̐������[s]
	static const float REF_TIME;			//�W���C���̃��t�@�����X�Ƃ鎞��[s]

	static int16_t gyro_value;
	static float default_angle;				//�ŏ����@�ŕ␳�������ĂȂ��p�x
	static float angle,gyro_ref;
	static float angular_velocity;

	static float get_gyro_ref();
	static void set_least_square_slope();//�ŏ����@���܂킵�ĕ␳�����v�Z

	gyro();

public:
	static float least_square_slope;//�␳���̌X��

	static void interrupt_gyro();
	static int16_t get_gyro();
	static void set_gyro_ref();

	static void reset_angle();
	static void cal_angle();//�p�x�v�Z[rad]
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

	encoder();

public:
	static float right_velocity,left_velocity,velocity;

	static void interrupt_encoder();		//���[�^�[��Encoder�̒l�v�Z
	static float get_velocity();//���E�̕���(�d�S���x)��Encoder�擾[m/s]�@ �ړ����ώ���Ă邱�Ƃɒ��ӁI

	~encoder();
};

//���w�Z���T�[�֘A
class photo {
private:

	static signed int right_ad, left_ad, front_right_ad, front_left_ad,front_ad;
	static signed int right_ref, left_ref, front_right_ref, front_left_ref,front_ref;
	static bool light_flag;		//�ԊO��LED�����点�ăZ���T�[�l��ǂނ��ǂ����̃t���O

	static void switch_led(PHOTO_TYPE sensor_type, bool is_light);		//LED���������������

	static uint16_t get_ad(PHOTO_TYPE sensor_type);			//??_ad�̒l���擾
	static void set_ad(PHOTO_TYPE sensor_type, int16_t set_value);		//??_ad�ɒl����

	static int16_t get_ref(PHOTO_TYPE sensor_type);	//OFF�̂Ƃ���AD�l��Ԃ�
	static void set_ref(PHOTO_TYPE sensor_type, int16_t set_value);		//ref�̒l����

	photo();

public:

	static void light(PHOTO_TYPE sensor_type);
	static void turn_off(PHOTO_TYPE sensor_type);
	static void turn_off_all();		//���ׂď���


	//���荞�ݓ��ōs������
	static void interrupt(bool is_light);

	static int16_t get_value(PHOTO_TYPE sensor_type);

	//TODO ���̊֐��̓}�E�Xclass�ɂ���ׂ�����
	static bool check_wall(unsigned char muki);
	static bool check_wall(PHOTO_TYPE type);



	~photo();

};



//���ꂼ��̃Z���T���琧���������N���X

//PID�̃Q�C���ƕ΍����Ǘ�����p�̍\����
typedef struct {
	float P;
	float I;
	float D;
} PID;

class control {
private:
	//TODO D���͂���Ȃ��炵���n�Z�V�����H��
	static float cross_delta_gain(SEN_TYPE sensor);//P_GAIN*P_DELTA+�E�E�E���s��

	static bool wall_control_flag;//�ǐ���������Ă��true�A�؂��Ă��false�B
	static bool control_phase;//�p������������Ă邩�ۂ��B�����Ă����true

	static float control_velocity();//���x�Ɋւ���PID����(�G���R�[�_�[�̂�)�B�߂�l��Duty�H
	static float control_angular_velocity();//���x�Ɋւ���PID����(�G���R�[�_�[�̂�)�B�߂�l��Duty�H

	static float get_feedback(const signed char right_or_left);//FB���|�������Duty��Ԃ��BPID����B
	static float get_feedforward(const signed char right_or_left);//FF���|�������Duty��Ԃ��B

	static bool is_FF_CONTROL,is_FB_CONTROL;	//FF��FB�̐��䂩���邩�ǂ����B������Ȃ�True

	control();

public:
	static PID gyro_delta,photo_delta,encoder_delta;//�e�탢

	static void cal_delta();//���荞�݊֐����ŁA�΍����v�Z����

	static void posture_control();//FF,FB�����������Bset_duty�܂ōs���B

	static void start_wall_control();//�ǐ����������
	static void stop_wall_control();//�ǐ����؂�

	static void start_control();//�����������
	static void stop_control();//������Ƃ߂�

	static bool get_control_phase();//���䂪�������Ă��邩���擾�B�������Ă����true
	static bool get_wall_control_phase();//���䂪�������Ă��邩���擾�B�������Ă����true

	static void reset_delta();

	static void fail_safe();//I�Q�C�������ȏア�����烂�[�^�[���~�߂�

	~control();
};


#endif /* HARDWARE_H_ */
