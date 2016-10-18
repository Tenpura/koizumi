/*
 * main.cpp
 *
 *  Created on: 2016/08/21
 *      Author: Koizumi
 */

#include "stm32f4xx.h"

#include "extern_c.h"

#include "define.h"
#include "init.h"
#include "hardware.h"
#include "ad_convert.h"

int main(void);

#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif

extern uint32_t wait_counter;

int main(void) {
	uint16_t temp;

	//�����ݒ�
	init_all();
	GPIO_SetBits(GPIOA, GPIO_Pin_4); // CS���Z�b�g

	my7seg::light(5);

	my7seg::count_down(3, 500);

	myprintf("vol -> %f\n\r", get_battery());

	while (1) {
		my7seg::light_error();
		wait::ms(100);
		my7seg::turn_off();
		wait::ms(100);

		ADC_ClearFlag(ADC1, ADC_FLAG_EOC);		//EndFlag���N���A����
		ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1,
		ADC_SampleTime_3Cycles);		//ADC1_CH9��
		ADC_SoftwareStartConv(ADC1);	//ADC1���J�n
		while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET)
			;		//�I���܂ő҂�
		temp = (ADC_GetConversionValue(ADC1));//XXX 4�r�b�g�V�t�g�ł��܂������Ă�C������@�E�l�߂̂͂��Ȃ̂ɈӖ��킩���B�l���擾
		myprintf("temp -> %d\r\n", temp);


	}

	ADC_ClearFlag(ADC1, ADC_FLAG_EOC);		//EndFlag���N���A����
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1,
	ADC_SampleTime_3Cycles);		//ADC1_CH9��
	ADC_SoftwareStartConv(ADC1);	//ADC1���J�n
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET)
		;		//�I���܂ő҂�
	temp = 0;
	temp = (ADC_GetConversionValue(ADC1));//XXX 4�r�b�g�V�t�g�ł��܂������Ă�C������@�E�l�߂̂͂��Ȃ̂ɈӖ��킩���B�l���擾
	my7seg::turn_off();

	myprintf("temp -> %d\r\n", temp);
	myprintf("temp -> ");
	unsigned int tekitou = 32768;
	for (int i = 0; i < 16; i++) {
		if ((temp & tekitou) > 0) {
			myprintf("1");
		} else {
			myprintf("0");
		}
		tekitou /= 2;
	}
	myprintf("\n\r");

	// ���M�C��M
	uint16_t ret;

	//MPU6000�̃��Z�b�g����
	GPIO_ResetBits(GPIOA, GPIO_Pin_4); // CS���Z�b�g

	//���W�X�^�w��
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
		; // ���M�\�ɂȂ�܂ő҂�
	SPI_I2S_SendData(SPI1, 0x6B); // ���M(�����SLEEP����)
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
		; // ��M�\�ɂȂ�܂ő҂�
	SPI_I2S_ReceiveData(SPI1); // ��f�[�^����M����

	//�f�[�^�̑���M
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
		; // ���M�\�ɂȂ�܂ő҂�
	SPI_I2S_SendData(SPI1, 0x00); // ���M
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
		; // ��M�\�ɂȂ�܂ő҂�
	SPI_I2S_ReceiveData(SPI1); // ��f�[�^����M����
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
		;
	GPIO_SetBits(GPIOA, GPIO_Pin_4); //CS�����Z�b�g

	GPIO_ResetBits(GPIOA, GPIO_Pin_4); // CS���Z�b�g

	//���W�X�^�w��
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
		; // ���M�\�ɂȂ�܂ő҂�
	SPI_I2S_SendData(SPI1, 0xf5); // ���M(�����WHO_AM_I)
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
		; // ��M�\�ɂȂ�܂ő҂�
	ret = SPI_I2S_ReceiveData(SPI1); // ��f�[�^����M����

	//�f�[�^�̑���M
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
		; // ���M�\�ɂȂ�܂ő҂�
	SPI_I2S_SendData(SPI1, 0x00); // ���M
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
		; // ��M�\�ɂȂ�܂ő҂�
	ret = SPI_I2S_ReceiveData(SPI1); // ��M����
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
		;
	GPIO_SetBits(GPIOA, GPIO_Pin_4); //CS�����Z�b�g

	motor::stanby_motor();
	wait::ms(100);
	motor::set_duty(motor_left, 20);
	motor::set_duty(motor_right, 20);

	while (1) {
		myprintf("0x%x\n\r", ret);

		wait::ms(100);

		GPIO_ResetBits(GPIOA, GPIO_Pin_4); // CS���Z�b�g

		//���W�X�^�w��
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
			; // ���M�\�ɂȂ�܂ő҂�
		SPI_I2S_SendData(SPI1, 0xf5); // ���M(�����WHO_AM_I)
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
			; // ��M�\�ɂȂ�܂ő҂�
		ret = SPI_I2S_ReceiveData(SPI1); // ��f�[�^����M����

		//�f�[�^�̑���M
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
			; // ���M�\�ɂȂ�܂ő҂�
		SPI_I2S_SendData(SPI1, 0x00); // ���M
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
			; // ��M�\�ɂȂ�܂ő҂�
		ret = SPI_I2S_ReceiveData(SPI1); // ��M����
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
			;

		GPIO_SetBits(GPIOA, GPIO_Pin_4); //CS�����Z�b�g

	}
	return 1;
}

#ifdef __cplusplus
void abort(void) {
}
#endif
