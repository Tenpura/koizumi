/*
 * ad_convert.h
 *
 *  Created on: 2016/09/17
 *      Author: Koizumi
 */

#ifndef AD_CONVERT_H_
#define AD_CONVERT_H_

//AD�ϊ��܂��̊֐��̂܂Ƃ�

#include"stm32f4xx.h"
#include"define.h"

//���ꂼ���AD�ϊ����ʂ�unsigned int�^�ŕԂ�
uint16_t ad_convert_batt();		//�o�b�e���Ď�����


//�o�b�e���[�d����ǂ�ŁAfloat�^�ŕԂ��֐�
float get_battery();

//gyro�̒l��ǂ�ŁA�����int�ŕԂ��֐�
unsigned int ad_convert_gyro();
unsigned int ad_convert_gyro_ref();

#endif /* AD_CONVERT_H_ */


