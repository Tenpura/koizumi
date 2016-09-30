/*
 * init.h
 *
 *  Created on: 2016/08/21
 *      Author: Koizumi
 */

#ifndef INIT_H_
#define INIT_H_

#include "stm32f4xx.h"

void init_all(void);		//以下のinit群を呼び出してるだけ

void init_tim(void);		//タイマー周り割り込みとかここ
void init_gpio(void);		//IO
void init_adc(void);		//AD変換
void init_usart(void);		//UART通信
void init_spi(void);		//SPI通信

#endif /* INIT_H_ */
