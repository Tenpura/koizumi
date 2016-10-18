/*
 * ad_convert.cpp
 *
 *  Created on: 2016/09/17
 *      Author: Koizumi
 */

#include"ad_convert.h"

uint16_t ad_convert_batt() {
	ADC_ClearFlag(ADC1, ADC_FLAG_EOC);		//EndFlagをクリアする
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1,
	ADC_SampleTime_3Cycles);		//ADC1_CH9を
	ADC_SoftwareStartConv(ADC1);	//ADC1を開始
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET)
		;		//終わるまで待つ
	return (ADC_GetConversionValue(ADC1) >> 4);	//XXX 値を取得　4ビットシフトでうまくいってる気がする　右詰めのはずなのに意味わからん。

}

float get_battery() {

	float temp_battery = 0;
	unsigned int ad_accurate = 4096;	//AD変換の精度格納用

	temp_battery = (float) LOGIK_V * ad_convert_batt()
			/ ad_accurate* V_BATT_RATIO;

	return temp_battery;
}

