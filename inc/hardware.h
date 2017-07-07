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
	enum DIRECTION {
		front, back, right, left
	};

	static void light(const my7seg::DIRECTION direction);//up,right,left���w�肷��Ə�ӁA�E�ӁA���ӂ�����
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
enum MOTOR_SIDE {
	m_left = 0, m_right = 1
};

class motor {
private:

	static signed char right_duty, left_duty;		//duty[��]

	static const char MAX_DUTY;	 	//Duty�̍ő�l�m���n
	static const char MAX_COUNT;	//Duty�̍ő�l�m���n

	static bool motor_state;		//motor���N�����Ă����TRUE�B

	motor();

public:
	static signed short get_duty_left();	//�����[�^�[��Duty�擾
	static signed short get_duty_right();	//�E���[�^�[��Duty�擾

	static void set_duty(const MOTOR_SIDE side, const float set_duty);//���[�^�[��Duty����

	static void sleep_motor();		//���[�^�[�h���C�o���X���[�v��Ԃ�
	static void stanby_motor();		//���[�^�[�h���C�o���X�^���o�C��Ԃ�

	static bool isEnable();		//motor���N�����Ă��邩�ǂ���

	~motor();
};

//gyro�֘A
//���v��肪��
//�Z���T�[�^�C�v��\���񋓌^
typedef enum {
	axis_x = 0, axis_y = 1, axis_z = 2, dim_num
} AXIS_t;
class mpu6000 {
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
	static uint16_t read_spi(uint16_t read_reg);		//SPI�ʐM��reg���W�X�^����ǂ݂���
	static void write_spi(uint16_t reg, uint16_t data);	//SPI�ʐM��reg���W�X�^��data����������


public:
	static volatile int16_t get_mpu_val(SEN_TYPE sen, AXIS_t axis);//sen�Z���T�[��axis�������̃f�[�^��ǂ�

	mpu6000();

public:
	static void init_mpu6000();

	~mpu6000();

};

class accelmeter: public mpu6000 {
public:		//���䎮���x����@�ŗp���邽��
	static const uint8_t AVERAGE_COUNT;		//�����x�v�̕��ώ���[��]
	static const float ACCEL_PERIOD;		//�����x�v�̐������[s]
private:
	static const float REF_TIME;			//�����x�v�̃��t�@�����X�Ƃ鎞��[s]

	static float accel_ad[AXIS_t::dim_num];		//�����x�̐��l
	static float accel_ref[AXIS_t::dim_num];
	static float accel[AXIS_t::dim_num];		//�����x [m/ss]

	static float get_accel_ref(AXIS_t xyz);
	static float get_accel_ad(AXIS_t xyz);		//xyz�����̉����x[m/s]��Ԃ�

	accelmeter();

public:

	static void interrupt();
	static void set_accel_ref();
	static void set_accel_ref(AXIS_t xyz);
	static void cal_accel();	//���l�������x�ɕϊ�[m/ss]

	static float get_accel();		//�i�s�����̉����x[m/s]
	static float get_accel(AXIS_t xyz);		//m/s��XYZ�����̉����x��Ԃ�

};

class gyro: public mpu6000 {
private:
	static const float GYRO_PERIOD;			//�W���C���̐������[s]
	static const float REF_TIME;			//�W���C���̃��t�@�����X�Ƃ鎞��[s]

	static int16_t gyro_value;
	static float default_angle;				//�ŏ����@�ŕ␳�������ĂȂ��p�x
	static float angle, gyro_ref;
	static float angular_velocity;

	static float get_gyro_ref();
	static void set_least_square_slope();				//�ŏ����@���܂킵�ĕ␳�����v�Z

	static void cal_angular_velocity();				//�p���x�v�Z[rad/s]
	static void cal_angle();				//�p�x�v�Z[rad]

	gyro();

public:
	static float least_square_slope;				//�␳���̌X��

	static void interrupt();		//���荞�ݓ��ŌĂ΂��
	static int16_t get_gyro();
	static void set_gyro_ref();

	static void reset_angle();
	static float get_angle();
	static float get_angular_velocity();

	~gyro();

};

//encoder
typedef enum {
	enc_right = 0, enc_left = 1
} ENC_SIDE;
class encoder {
private:
	const static uint8_t MOVING_AVERAGE;	//�ړ����ς��Ƃ鎞�ԁ@�P�ʂ͐������
	const static uint32_t MEDIAN;		//�J�E���g�̒����l
	static float correct[2][4097];	//�␳�p�̃e�[�u��
	static bool correct_flag[2];	//�␳�����ۂ�
	static uint32_t init_time[2];	//�␳�̊J�n����
	static int16_t finish_time[2];	//�␳�I�����̎���

	static bool isCorrect[2];		//Y.I.���␳���s���Ă��邩�ǂ����̃t���O

	encoder();

	static volatile float raw_to_correct(ENC_SIDE enc_side, int16_t raw_delta);	//�␳�e�[�u���Ő��l��␳����,�Ԃ�l�̓R���o�[�g������̍����l



public:


	static float right_velocity, left_velocity, velocity;
	static int16_t raw_count[2];	//�G���R�[�_�\�̐��l

	static void interrupt();		//���[�^�[��Encoder�̒l�v�Z
	static float get_velocity();	//���E�̕���(�d�S���x)��Encoder�擾[m/s]�@ �ړ����ώ���Ă邱�Ƃɒ��ӁI

	static volatile void yi_correct(ENC_SIDE enc_right);		//�Е�����Y.I.���␳�@���s���B�i�␳�e�[�u���̍쐬�j
	static void yi_correct();		//Y.I.���␳�@���s���B�i�␳�e�[�u���̍쐬�j

	static void draw_correct(bool right, bool left);		//Y.I.���␳�e�[�u����\��

	~encoder();
};

//���w�Z���T�[�֘A
#define GAP_AVE_COUNT 10	//XXX �ǂ̐؂�ڑ΍�ɂ����̕��ς��Ƃ邩
class photo {
private:
public:
	static int16_t ave_buf[element_count][GAP_AVE_COUNT];	//�Z���T�[�l�i���ώ������j�̃o�b�t�@�@�ǂ̐؂�ڃ`�F�b�N�Ƃ��Ŏg��
	static float diff_buf[element_count][GAP_AVE_COUNT];	//���̃Z���T�[�l��ave_buf�̍��@�ǂ̐؂�ڃ`�F�b�N�Ƃ��Ŏg��
	static uint8_t gap_buf[element_count][GAP_AVE_COUNT];		//count_wall_gap�Ő����グ���l��ۑ����Ă���

	static signed int right_ad, left_ad, front_right_ad, front_left_ad,
			front_ad;
	static signed int right_ref, left_ref, front_right_ref, front_left_ref,
			front_ref;
	static bool light_flag;		//�ԊO��LED�����点�ăZ���T�[�l��ǂނ��ǂ����̃t���O


	static void switch_led(PHOTO_TYPE sensor_type, bool is_light);//LED���������������

	static int16_t get_ref(PHOTO_TYPE sensor_type);	//OFF�̂Ƃ���AD�l��Ԃ�
	static void set_ref(PHOTO_TYPE sensor_type, int16_t set_value);	//ref�̒l����

	photo();

public:

	static uint16_t get_ad(PHOTO_TYPE sensor_type);			//??_ad�̒l���擾
	static void set_ad(PHOTO_TYPE sensor_type, int16_t set_value);	//??_ad�ɒl����

	static void light(PHOTO_TYPE sensor_type);
	static void turn_off(PHOTO_TYPE sensor_type);
	static void turn_off_all();		//���ׂď���

	//���荞�ݓ��ōs������
	static void interrupt(bool is_light);

	static int16_t get_value(PHOTO_TYPE sensor_type);

	//�Z���T�l���狗���ɕϊ����A��撆�S����ǂꂾ������Ă���̂�[mm]��Ԃ��B�E����
	static float get_displacement_from_center(PHOTO_TYPE sensor_type);

	//TODO ���̊֐��̓}�E�Xclass�ɂ���ׂ�����
	static bool check_wall(unsigned char muki);
	static bool check_wall(PHOTO_TYPE type);

	static int8_t count_wall_gap(PHOTO_TYPE);	//diff_gap�ɕۑ�����Ă�l�̐����𐔂��グ�ĕԂ��B
	static bool check_wall_gap(PHOTO_TYPE type, int16_t threshold);	//�ړ����ς��Ƃ������GAP_AVE_COUNT�O�Ɣ�r���Đ�Βl��threshold�ȏ�Ȃ�A�ǂ̐؂�ڂ�����true

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
	static volatile float cross_delta_gain(SEN_TYPE sensor);		//P_GAIN*P_DELTA+�E�E�E���s��
	static float ctrl_accel_int;			//�����x��FB����ʂ̐ϕ��l

	static bool wall_control_flag;		//�ǐ���������Ă��true�A�؂��Ă��false�B
	static bool control_phase;		//�p������������Ă邩�ۂ��B�����Ă����true

	//�����x�̓J�X�P�[�h�ڑ��ł͂Ȃ��A���x�Ƃ͓Ɨ��ɐ���ʂ��o���A����̐ϕ��𑬓x����ʂɑ���
	static float control_accel();		//�����x�Ɋւ���PID����(�����x�Z���T�̂�)�B�߂�l��[Duty/����]�H
	static float control_velocity();		//���x�Ɋւ���PID����(�G���R�[�_�[�̂�)�B�߂�l��Duty�H
	static float control_angular_velocity();//���x�Ɋւ���PID����(�G���R�[�_�[�̂�)�B�߂�l��Duty�H

	static float get_feedback(const signed char right_or_left);	//FB���|�������Duty��Ԃ��BPID����B
	static float get_feedforward(const signed char right_or_left);//FF���|�������Duty��Ԃ��B

	static bool is_FF_CONTROL, is_FB_CONTROL;	//FF��FB�̐��䂩���邩�ǂ����B������Ȃ�True
	static bool is_accel_CONTROL;		//�����x��FB���䂩���邩�ǂ���
	control();

public:
	static PID gyro_delta, photo_delta, encoder_delta, accel_delta;	//�e�탢

	static void cal_delta();	//���荞�݊֐����ŁA�΍����v�Z����

	static void posture_control();	//FF,FB�����������Bset_duty�܂ōs���B

	static void start_wall_control();	//�ǐ����������
	static void stop_wall_control();	//�ǐ����؂�

	static void start_control();	//�����������
	static void stop_control();	//������Ƃ߂�

	static bool get_control_phase();	//���䂪�������Ă��邩���擾�B�������Ă����true
	static bool get_wall_control_phase();	//���䂪�������Ă��邩���擾�B�������Ă����true

	static void reset_delta();
	static volatile void reset_delta(SEN_TYPE type);	//����̃Z���T�[�̕΍�����0�ɂ���

	static void fail_safe();	//I�Q�C�������ȏア�����烂�[�^�[���~�߂�

	~control();
};

//�J���}���t�B���^���s��
//�l�ƕ��U���Ǘ�����p�̍\����
class kalman{
//�ϐ����̖��Â�����Wiki�ɏ]��
//https://ja.wikipedia.org/wiki/%E3%82%AB%E3%83%AB%E3%83%9E%E3%83%B3%E3%83%95%E3%82%A3%E3%83%AB%E3%82%BF%E3%83%BC
private:
	float x;		//���݂̒l
	float p;		//���݂̕��U
	float EstP,ObsP;	//����l�Ɗϑ��l�̕��U

public:
	//�J���}���t�B���^�ɂ��␳���s���B
	void update(float EstimateU, float ObserveZ);		//�O��̒l����ǂꂾ���ω����邩�̐���lEstimateU,�ϑ��lObserveZ������ƕ␳����B

	float get_value();				//���݂̒l��Ԃ�
	float get_dispersion();			//���݂̕��U��Ԃ�

	kalman();
	kalman(float EstimateP, float ObserveP);	//�ŏ��ɐ���l�̕��U�Ɗϑ��l�̕��U���p�����[�^�Ƃ��ē����
	kalman(float initX, float initP, float EstimateP, float ObserveP);	//����ɏ����l�����ꂽ���Ȃ�
	~kalman();
};

#endif /* HARDWARE_H_ */
