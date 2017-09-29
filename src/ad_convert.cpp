/*
 * ad_convert.cpp
 *
 *  Created on: 2016/09/17
 *      Author: Koizumi
 */

#include"ad_convert.h"

uint16_t ad_convert_batt() {
	ADC_ClearFlag(ADC1, ADC_FLAG_EOC);		//EndFlag���N���A����
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1,
	ADC_SampleTime_3Cycles);		//ADC1_CH9��
	ADC_SoftwareStartConv(ADC1);	//ADC1���J�n
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET)
		;		//�I���܂ő҂�
	return (ADC_GetConversionValue(ADC1) >> 4);	//XXX �l���擾�@4�r�b�g�V�t�g�ł��܂������Ă�C������@�E�l�߂̂͂��Ȃ̂ɈӖ��킩���B

}

float get_battery() {

	float temp_battery = 0;
	unsigned int ad_accurate = 4096;	//AD�ϊ��̐��x�i�[�p

	temp_battery = (float) LOGIK_V * ad_convert_batt()
			/ ad_accurate* V_BATT_RATIO;

	return temp_battery;
}

