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

	//初期設定
	init_all();
	GPIO_SetBits(GPIOA, GPIO_Pin_4); // CSをセット

	my7seg::light(5);

	my7seg::count_down(3, 500);

	myprintf("vol -> %f\n\r", get_battery());

	while (1) {
		my7seg::light_error();
		wait::ms(100);
		my7seg::turn_off();
		wait::ms(100);

		ADC_ClearFlag(ADC1, ADC_FLAG_EOC);		//EndFlagをクリアする
		ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1,
		ADC_SampleTime_3Cycles);		//ADC1_CH9を
		ADC_SoftwareStartConv(ADC1);	//ADC1を開始
		while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET)
			;		//終わるまで待つ
		temp = (ADC_GetConversionValue(ADC1));//XXX 4ビットシフトでうまくいってる気がする　右詰めのはずなのに意味わからん。値を取得
		myprintf("temp -> %d\r\n", temp);


	}

	ADC_ClearFlag(ADC1, ADC_FLAG_EOC);		//EndFlagをクリアする
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1,
	ADC_SampleTime_3Cycles);		//ADC1_CH9を
	ADC_SoftwareStartConv(ADC1);	//ADC1を開始
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET)
		;		//終わるまで待つ
	temp = 0;
	temp = (ADC_GetConversionValue(ADC1));//XXX 4ビットシフトでうまくいってる気がする　右詰めのはずなのに意味わからん。値を取得
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

	// 送信，受信
	uint16_t ret;

	//MPU6000のリセット解除
	GPIO_ResetBits(GPIOA, GPIO_Pin_4); // CSをセット

	//レジスタ指定
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
		; // 送信可能になるまで待つ
	SPI_I2S_SendData(SPI1, 0x6B); // 送信(今回はSLEEP解除)
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
		; // 受信可能になるまで待つ
	SPI_I2S_ReceiveData(SPI1); // 空データを受信する

	//データの送受信
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
		; // 送信可能になるまで待つ
	SPI_I2S_SendData(SPI1, 0x00); // 送信
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
		; // 受信可能になるまで待つ
	SPI_I2S_ReceiveData(SPI1); // 空データを受信する
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
		;
	GPIO_SetBits(GPIOA, GPIO_Pin_4); //CSをリセット

	GPIO_ResetBits(GPIOA, GPIO_Pin_4); // CSをセット

	//レジスタ指定
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
		; // 送信可能になるまで待つ
	SPI_I2S_SendData(SPI1, 0xf5); // 送信(今回はWHO_AM_I)
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
		; // 受信可能になるまで待つ
	ret = SPI_I2S_ReceiveData(SPI1); // 空データを受信する

	//データの送受信
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
		; // 送信可能になるまで待つ
	SPI_I2S_SendData(SPI1, 0x00); // 送信
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
		; // 受信可能になるまで待つ
	ret = SPI_I2S_ReceiveData(SPI1); // 受信する
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
		;
	GPIO_SetBits(GPIOA, GPIO_Pin_4); //CSをリセット

	motor::stanby_motor();
	wait::ms(100);
	motor::set_duty(motor_left, 20);
	motor::set_duty(motor_right, 20);

	while (1) {
		myprintf("0x%x\n\r", ret);

		wait::ms(100);

		GPIO_ResetBits(GPIOA, GPIO_Pin_4); // CSをセット

		//レジスタ指定
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
			; // 送信可能になるまで待つ
		SPI_I2S_SendData(SPI1, 0xf5); // 送信(今回はWHO_AM_I)
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
			; // 受信可能になるまで待つ
		ret = SPI_I2S_ReceiveData(SPI1); // 空データを受信する

		//データの送受信
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
			; // 送信可能になるまで待つ
		SPI_I2S_SendData(SPI1, 0x00); // 送信
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
			; // 受信可能になるまで待つ
		ret = SPI_I2S_ReceiveData(SPI1); // 受信する
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
			;

		GPIO_SetBits(GPIOA, GPIO_Pin_4); //CSをリセット

	}
	return 1;
}

#ifdef __cplusplus
void abort(void) {
}
#endif
