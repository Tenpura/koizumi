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

#endif /* HARDWARE_H_ */
