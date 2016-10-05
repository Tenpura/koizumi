/*
 * hardware.h
 *
 *  Created on: 2015/06/14
 *      Author: Koizumi
 */

#ifndef HARDWARE_H_
#define HARDWARE_H_

#include "stm32f4xx.h"
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


#endif /* HARDWARE_H_ */
