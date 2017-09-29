/*
 * serial.h
 *
 *  Created on: 2016/09/12
 *      Author: Koizumi
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#include "stm32f4xx.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

//1バイト送信
void put1byte(char c);

//nバイト送信
void putnbyte(char *buf, int16_t len);

//文字出力関数　myprintf　の定義
int myprintf(const char *fmt, ...);

#endif /* SERIAL_H_ */
