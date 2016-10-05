/*
 * init.c
 *
 *  Created on: 2016/08/21
 *      Author: Koizumi
 */

#include "init.h"

void init_all(void) {
	init_system();
	//init_tim();
	init_gpio();
	init_adc();
	init_usart();
	init_spi();
	init_pwm();
}

void init_system() {
	//���̕ӊ��S�ɗ����͂ł��ĂȂ�
	SystemInit();		//�N���b�N���Ȃ���V�X�e������̏������H
	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq(&RCC_Clocks);	//RCC_Clocks�ɒl�����H ���Ԃ�SYSCLK_Frequency16MH�����������Ă�.HCLK��SYSCLK�Ɠ����H(16MH��)
	SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);//SysTick���荞�݂̎������߁B�J�E���g�̍ő�����B����Ŏ���1ms�̂͂��B
	//SysTick���荞�݂̗D��x��15�ōŒ�B�Y�ꂻ�������烁�����Ă����B

}

void init_tim(void) {

	//���荞�݃R���g���[���[
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_BRK_TIM9_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitSturcture;	//�������p�\���̂�錾

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);	//TIM9�ɃN���b�N����

	TIM_TimeBaseInitSturcture.TIM_Period = 420 - 1;	//�J�E���^�N���A�v��
	TIM_TimeBaseInitSturcture.TIM_Prescaler = 10 - 1; //�v���X�P�[��(�J�E���^��Prescaler��J�E���g���ꂽ�^�C�~���O�ŁCTIM9�̃J�E���^��1���Z�����)
	TIM_TimeBaseInitSturcture.TIM_ClockDivision = 0; //�f�b�g�^�C��������H�p�̕����B�ʏ�0(�������Ȃ�)�B
	TIM_TimeBaseInitSturcture.TIM_CounterMode = TIM_CounterMode_Up;	//�A�b�v�J�E���g
	TIM_TimeBaseInit(TIM9, &TIM_TimeBaseInitSturcture);	//�ݒ�

	TIM_ClearITPendingBit(TIM9, TIM_IT_Update); //�^�C�}�X�V�C�x���g�ł̊��荞�݃t���O���N���A
	TIM_ITConfig(TIM9, TIM_IT_Update, ENABLE); //�^�C�}�X�V�C�x���g�ł̊��荞�݂�����

}

void init_gpio(void) {
	/* Reset HSEON, CSSON and PLLON bits */
	RCC->CR &= (uint32_t) 0xFEF6FFFF; //HSE�I�V���[�^�[�͎g�p���Ȃ��̂ŁA���Z�b�g���Ă���(SystemInit()����ON�ɂȂ��Ă��邽��)

	//IO�̏o�͐ݒ�
	GPIO_InitTypeDef GPIO_InitStructure;	//�����ݒ�̂��߂̍\���̂�錾

	//GPIOB
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);	//�N���b�N����
	GPIO_StructInit(&GPIO_InitStructure);	//�\���̂�������
	GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_4 | GPIO_Pin_12 | GPIO_Pin_15);	//�ݒ肷��s�������߂�
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//�N���b�N
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		//�o�͂ɐݒ�
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//�I�[�v���h���C��or�v�b�V���v��
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	//�v���A�b�v���v���_�E����
	GPIO_Init(GPIOB, &GPIO_InitStructure);	//�ݒ�

	//GPIOC
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);	//�N���b�N����
	GPIO_StructInit(&GPIO_InitStructure);	//�\���̂�������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_10
			| GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_14 | GPIO_Pin_15;//�ݒ肷��s�������߂�
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//�N���b�N
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		//�o�͂ɐݒ�
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//�I�[�v���h���C��or�v�b�V���v��
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	//�v���A�b�v���v���_�E����
	GPIO_Init(GPIOC, &GPIO_InitStructure);	//�ݒ�

	//�����l
	GPIO_SetBits(GPIOC, GPIO_Pin_2);	//Pin��1��
	GPIO_SetBits(GPIOC, GPIO_Pin_3);	//Pin��1��
	GPIO_SetBits(GPIOC, GPIO_Pin_10);	//Pin��1��
	GPIO_SetBits(GPIOC, GPIO_Pin_11);	//Pin��1��
	GPIO_SetBits(GPIOC, GPIO_Pin_12);	//Pin��1��
	GPIO_SetBits(GPIOC, GPIO_Pin_14);	//Pin��1��
	GPIO_SetBits(GPIOC, GPIO_Pin_15);	//Pin��1��

	//GPIOH
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
	GPIO_StructInit(&GPIO_InitStructure);	//�\���̂�������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;	//�ݒ肷��s�������߂�
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//�N���b�N
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		//�o�͂ɐݒ�
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//�I�[�v���h���C��or�v�b�V���v��
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	//�v���A�b�v���v���_�E����
	GPIO_Init(GPIOH, &GPIO_InitStructure);	//�ݒ�

	GPIO_SetBits(GPIOH, GPIO_Pin_0);
	GPIO_SetBits(GPIOH, GPIO_Pin_1);

}

void init_adc(void) {
//GPIO���ŃA�i���O���[�h�ɐݒ�
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4
			| GPIO_Pin_5;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

//AD�ϊ��̐ݒ�
	ADC_InitTypeDef ADC_InitStructure;		//�����ݒ�p�̍\���̒�`
	ADC_CommonInitTypeDef ADC_CommonInitStructure;

	ADC_Cmd(ADC1, DISABLE);		//ADC1��Disable��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);		//�N���b�N����
	ADC_DeInit();		//ADC�̎��Ӄ��W�X�^���f�t�H���g�̒l�Ƀ��Z�b�g����

	//AD�ϊ��̊�{�ݒ�
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;	//PCLK/4 = 16/4 MHz?
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;	//DMA�͎g�p���Ȃ�
	ADC_CommonInitStructure.ADC_TwoSamplingDelay =
	ADC_TwoSamplingDelay_20Cycles;//�A���X�L�����Ƃ��Ŏg�p�H�@ADC_delay_between_2_sampling_phases
	ADC_CommonInit(&ADC_CommonInitStructure);

	//ADC1�̐ݒ�
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;		//12bit��AD�ϊ�
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;		//�V���O�����[�h�œ���
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;		//�V���O�����[�h�œ���
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;	//AD�ϊ��̊J�n�ɊO���g���K�͎g�p���Ȃ�
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Left;	//�E�l�ߍ��l��
	ADC_InitStructure.ADC_NbrOfConversion = 9;		//AD�ϊ��̓��͂�9�`�����l��
	ADC_Init(ADC1, &ADC_InitStructure);

	ADC_Cmd(ADC1, ENABLE);		//ADC1��Enable��
	ADC_DMACmd(ADC1, DISABLE);	//DMA�͎g��Ȃ�

}

void init_usart(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	//�K�v�Ȏ��Ӌ@�\�ɃN���b�N������(PA9,PA10��TX,RX�Ȃ̂ŁAGPIOA��USART1)
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	//GPIO��USART��Remap����B�@����STM32�̃V���[�Y�Ƃ���GPIO_PinAFConfig�܂ł�����Ȃ��ėǂ��炵���B
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = 115200;	//�|�[���[�g�ݒ�
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//�p�P�b�g�̃��[�h����8bit��
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	//�X�g�b�v�r�b�g��1�ɐݒ�B
	USART_InitStructure.USART_Parity = USART_Parity_No;	//�p���e�B�[�𖳂�
	USART_InitStructure.USART_HardwareFlowControl =
	USART_HardwareFlowControl_None;		//�t���[������Ȃ��ɁB
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//TX��RX�Ƀ��[�h�ݒ�
	USART_Init(USART1, &USART_InitStructure);	//USART1�ݒ�
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1, ENABLE);		//USART1�N��

}

void init_spi(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);		//�N���b�N����

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_StructInit(&GPIO_InitStructure);

	//�X���[�u�Z���N�g�[�q
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//�f�[�^���M�֌W��GPIO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_SetBits(GPIOA, GPIO_Pin_4);		//�X���[�u�Z���N�g

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);

	SPI_InitTypeDef SPI_InitStructure;

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	//�o�������M
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//�f�[�^�T�C�Y��8bit
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;	//�N���b�N����Ԃ�Low
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	//
	//�����̕\���Ƃ���ł����͂������ǂȂ������܂������Ȃ��B
	//SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;	//�N���b�N����Ԃ�High�@http://hantasmouse.hatenablog.jp/entry/2015/12/12/142413�Q��
	//SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;//http://hantasmouse.hatenablog.jp/entry/2015/12/12/142413�Q��
	SPI_InitStructure.SPI_NSS = SPI_NSSInternalSoft_Set | SPI_NSS_Soft;	//�X���[�u�Z���N�g�̓\�t�g��
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;//SCK�N���b�N�̑���M�̃{�[���[�g�ݒ�
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;			//MSB�t�@�[�X�g
	SPI_InitStructure.SPI_CRCPolynomial = 7;		//�������iCRC�j�B0�͐ݒ�֎~�B�ł��g���ĂȂ��B
	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd(SPI1, ENABLE);

	GPIO_SetBits(GPIOA, GPIO_Pin_4); // CS���Z�b�g

}

const uint16_t MAX_PERIOD = (420 - 1);//PWM�̎��g�����߂̂��߂̍ő�J�E���g
void init_pwm() {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_ResetBits(GPIOC, GPIO_Pin_2);		//���[�^�[�h���C�o�[���X���[�v���[�h��

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	TIM_TimeBaseInitTypeDef TIM_InitStructure;
	TIM_InitStructure.TIM_Period = MAX_PERIOD;//�J�E���^�N���A�v�� 200kHz Excel�t�@�C������TIM�̃N���b�N���m�F
	TIM_InitStructure.TIM_Prescaler = 0;//�v���X�P�[��(�J�E���^��Prescaler��J�E���g���ꂽ�^�C�~���O�ŁCTIM�̃J�E���^��1���Z�����)
	TIM_InitStructure.TIM_ClockDivision = 0;	//�f�b�g�^�C��������H�p�̕����B�ʏ�0(�������Ȃ�)�B
	TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;	//�A�b�v�J�E���g
	TIM_InitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &TIM_InitStructure);
	TIM_TimeBaseInit(TIM5, &TIM_InitStructure);

	TIM_OCInitTypeDef TIM_OC_InitStructure;
	TIM_OC_InitStructure.TIM_OCMode = TIM_OCMode_PWM1;		//���[�h��PWM1
	TIM_OC_InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//���Ԃ񂢂�Ȃ��BThis parameter is valid only for TIM1 and TIM8.
	TIM_OC_InitStructure.TIM_OutputState = TIM_OutputState_Enable;//���Ԃ񂢂�Ȃ��BThis parameter is valid only for TIM1 and TIM8.
	TIM_OC_InitStructure.TIM_Pulse = 0;	//�p���X���BDuty��Ɋ֌W�B

	//PWM�o�͂�4�{�K�v�Ȃ̂Ŋe�^�C�}2����
	TIM_OC1Init(TIM4, &TIM_OC_InitStructure);		//TIM4��CH1
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC2Init(TIM4, &TIM_OC_InitStructure);		//TIM4��CH2
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC1Init(TIM5, &TIM_OC_InitStructure);		//TIM5��CH1
	TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);
	TIM_OC2Init(TIM5, &TIM_OC_InitStructure);		//TIM5��CH2
	TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM5);

	//TIM�N��
	TIM_ARRPreloadConfig(TIM4, ENABLE);
	TIM_ARRPreloadConfig(TIM5, ENABLE);
}
