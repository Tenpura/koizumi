/*
 * init.h
 *
 *  Created on: 2016/08/21
 *      Author: Koizumi
 */

#ifndef INIT_H_
#define INIT_H_

#include "stm32f4xx.h"

void init_all(void);		//�ȉ���init�Q���Ăяo���Ă邾��

void init_tim(void);		//�^�C�}�[���芄�荞�݂Ƃ�����
void init_gpio(void);		//IO
void init_adc(void);		//AD�ϊ�
void init_usart(void);		//UART�ʐM
void init_spi(void);		//SPI�ʐM

#endif /* INIT_H_ */
