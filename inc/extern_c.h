/*
 * extern_c.h
 *
 *  Created on: 2016/08/21
 *      Author: Koizumi
 */

#ifndef EXTERN_C_H_
#define EXTERN_C_H_

#ifdef __cplusplus		//コンパイラがC++のとき

#include "stm32f4xx.h"

//#include <cstdint> //unitXX_tとか使うために必要だけど、上のstm32f4xx.h内で呼ばれてるから大丈夫。ってかこのコンパイルではC++用のこれはサポートされてない。stdint.hを使うべし

//stm32のライブラリ関数
extern "C" void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
extern "C" void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

extern "C" void ADC_ClearFlag(ADC_TypeDef* ADCx, uint8_t ADC_FLAG);
extern "C" void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);
extern "C" FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, uint8_t ADC_FLAG);

extern "C" void RCC_AHB1PeriphClockCmd(uint32_t RCC_AHB1Periph, FunctionalState NewState);
extern "C" void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);

extern "C" void TIM_ClearITPendingBit(TIM_TypeDef* TIMx, uint16_t TIM_IT);
extern "C" void TIM_ITConfig(TIM_TypeDef* TIMx, uint16_t TIM_IT, FunctionalState NewState);

extern "C" FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);
extern "C" void SPI_I2S_SendData(SPI_TypeDef* SPIx, uint16_t Data);

extern "C" void TIM_OC1PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
extern "C" void TIM_OC2PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);

//ユーザー定義関数
extern "C" void init_all(void);

extern "C" int myprintf(const char *fmt, ...);

/*
//serial.h
extern "C" void put1byte(char c);
extern "C" void putnbyte(char *buf, int len);
extern "C" int myprintf(const char *fmt, ...);

//init.h
extern "C" void Init_ALL(void);
extern "C" void Init_MTU ( void );
extern "C" void Init_CMT0 ( void );
extern "C" void Init_SCI(void);
extern "C" void Init_SYSTEM(void);
extern "C" void Init_AD(void);

//ad_convert.h
extern "C" unsigned int ad_convert_an000();
extern "C" unsigned int ad_convert_an001();
extern "C" unsigned int ad_convert_an002();
extern "C" unsigned int ad_convert_an003();
extern "C" unsigned int ad_convert_an100();
extern "C" unsigned int ad_convert_an101();
extern "C" unsigned int ad_convert_an102();
extern "C" unsigned int ad_convert_an103();
extern "C" float get_battery();
extern "C" unsigned int ad_convert_gyro();
extern "C" unsigned int ad_convert_gyro_ref();

//割り込み
extern "C" void interrupt_cmt0();
extern "C" void interrupt_cmt1();
extern "C" void interrupt_mtu0_tgid0();
extern "C" void interrupt_speaker();

//ユーザー関数
extern "C" void wait_ms(unsigned int wait_ms_count);//ms(ミリ秒)単位で待つ関数。
extern "C" void set_count_ms(unsigned long set_ms_value);//msをカウントする変数に代入。
extern "C" unsigned long get_count_ms();//msのカウントを返す。

extern "C" void sound_bz(unsigned int Hz, unsigned int bz_miri_second);
*/

#endif

#endif /* EXTERN_C_H_ */
