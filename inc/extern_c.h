/*
 * extern_c.h
 *
 *  Created on: 2016/08/21
 *      Author: Koizumi
 */

#ifndef EXTERN_C_H_
#define EXTERN_C_H_

#ifdef __cplusplus		//�R���p�C����C++�̂Ƃ�

#include "stm32f4xx.h"

//#include <cstdint> //unitXX_t�Ƃ��g�����߂ɕK�v�����ǁA���stm32f4xx.h���ŌĂ΂�Ă邩����v�B���Ă����̃R���p�C���ł�C++�p�̂���̓T�|�[�g����ĂȂ��Bstdint.h���g���ׂ�

//stm32�̃��C�u�����֐�
extern "C" void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
extern "C" void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
extern "C" uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

extern "C" void GPIO_PinAFConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_PinSource, uint8_t GPIO_AF);

extern "C" void ADC_ClearFlag(ADC_TypeDef* ADCx, uint8_t ADC_FLAG);
extern "C" void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);
extern "C" FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, uint8_t ADC_FLAG);

extern "C" void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);
extern "C" void RCC_AHB1PeriphClockCmd(uint32_t RCC_AHB1Periph, FunctionalState NewState);
extern "C" void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);

extern "C" void TIM_ClearITPendingBit(TIM_TypeDef* TIMx, uint16_t TIM_IT);
extern "C" void TIM_ITConfig(TIM_TypeDef* TIMx, uint16_t TIM_IT, FunctionalState NewState);

extern "C" FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);
extern "C" void SPI_I2S_SendData(SPI_TypeDef* SPIx, uint16_t Data);

extern "C" void TIM_SetAutoreload(TIM_TypeDef* TIMx, uint32_t Autoreload);
extern "C" void TIM_EncoderInterfaceConfig(TIM_TypeDef* TIMx, uint16_t TIM_EncoderMode,uint16_t TIM_IC1Polarity, uint16_t TIM_IC2Polarity);

extern "C" void TIM_OC1PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
extern "C" void TIM_OC2PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);

extern "C" void USART_ITConfig(USART_TypeDef* USARTx, uint16_t USART_IT, FunctionalState NewState);

extern "C" uint32_t SysTick_Config(uint32_t ticks);

extern "C" FLASH_Status FLASH_EraseSector(uint32_t FLASH_Sector, uint8_t VoltageRange);
extern "C" FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data);
extern "C" void         FLASH_ClearFlag(uint32_t FLASH_FLAG);


//���[�U�[��`�֐�
extern "C" void init_all(void);

extern "C" void putnbyte(char *buf, int16_t len);	//printf_log�Ŏg�p
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

//���荞��
extern "C" void interrupt_cmt0();
extern "C" void interrupt_cmt1();
extern "C" void interrupt_mtu0_tgid0();
extern "C" void interrupt_speaker();

//���[�U�[�֐�
extern "C" void wait_ms(unsigned int wait_ms_count);//ms(�~���b)�P�ʂő҂֐��B
extern "C" void set_count_ms(unsigned long set_ms_value);//ms���J�E���g����ϐ��ɑ���B
extern "C" unsigned long get_count_ms();//ms�̃J�E���g��Ԃ��B

extern "C" void sound_bz(unsigned int Hz, unsigned int bz_miri_second);
*/

extern "C" void interrupt_timer();

#endif

#endif /* EXTERN_C_H_ */
