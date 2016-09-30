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

//1�o�C�g���M
void put1byte(char c);

//n�o�C�g���M
void putnbyte(char *buf, int16_t len);

//�����o�͊֐��@myprintf�@�̒�`
int myprintf(const char *fmt, ...);

#endif /* SERIAL_H_ */
