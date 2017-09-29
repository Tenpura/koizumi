/*
 * init.h
 *
 *  Created on: 2016/08/21
 *      Author: Koizumi
 */

#ifndef INIT_H_
#define INIT_H_

#include "stm32f4xx.h"
#include "extern_c.h"


//const uint16_t MAX_PERIOD;	//PWM�̎��g�����߂̂��߂̍ő�J�E���g ��`����Ă�
//�Y��Ȃ��悤�R�����g�Ń������Ă���

void init_all(void);		//�ȉ���init�Q���Ăяo���Ă邾��

void init_system(void);
void init_tim(void);		//�^�C�}�[���芄�荞�݂Ƃ�����
void init_gpio(void);		//IO
void init_adc(void);		//AD�ϊ�
void init_usart(void);		//UART�ʐM
void init_spi(void);		//SPI�ʐM
void init_pwm(void);		//pwm�g�`
void init_enc(void);		//encoder �ʑ��W��
//void init_mpu(void);		//MPU

#endif /* INIT_H_ */
