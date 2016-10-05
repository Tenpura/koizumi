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
	//この辺完全に理解はできてない
	SystemInit();		//クロックやらなんやらシステム周りの初期化？
	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq(&RCC_Clocks);	//RCC_Clocksに値を代入？ たぶんSYSCLK_Frequency16MHｚが代入されてる.HCLKはSYSCLKと同じ？(16MHｚ)
	SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);//SysTick割り込みの周期決め。カウントの最大を代入。これで周期1msのはず。
	//SysTick割り込みの優先度は15で最低。忘れそうだからメモしておく。

}

void init_tim(void) {

	//割り込みコントローラー
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_BRK_TIM9_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitSturcture;	//初期化用構造体を宣言

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);	//TIM9にクロック供給

	TIM_TimeBaseInitSturcture.TIM_Period = 420 - 1;	//カウンタクリア要因
	TIM_TimeBaseInitSturcture.TIM_Prescaler = 10 - 1; //プリスケーラ(カウンタがPrescaler回カウントされたタイミングで，TIM9のカウンタが1加算される)
	TIM_TimeBaseInitSturcture.TIM_ClockDivision = 0; //デットタイム発生回路用の分周。通常0(分周しない)。
	TIM_TimeBaseInitSturcture.TIM_CounterMode = TIM_CounterMode_Up;	//アップカウント
	TIM_TimeBaseInit(TIM9, &TIM_TimeBaseInitSturcture);	//設定

	TIM_ClearITPendingBit(TIM9, TIM_IT_Update); //タイマ更新イベントでの割り込みフラグをクリア
	TIM_ITConfig(TIM9, TIM_IT_Update, ENABLE); //タイマ更新イベントでの割り込みを許可

}

void init_gpio(void) {
	/* Reset HSEON, CSSON and PLLON bits */
	RCC->CR &= (uint32_t) 0xFEF6FFFF; //HSEオシレーターは使用しないので、リセットしておく(SystemInit()内でONになっているため)

	//IOの出力設定
	GPIO_InitTypeDef GPIO_InitStructure;	//初期設定のための構造体を宣言

	//GPIOB
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);	//クロック供給
	GPIO_StructInit(&GPIO_InitStructure);	//構造体を初期化
	GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_4 | GPIO_Pin_12 | GPIO_Pin_15);	//設定するピンを決める
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//クロック
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		//出力に設定
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//オープンドレインorプッシュプル
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	//プルアップかプルダウンか
	GPIO_Init(GPIOB, &GPIO_InitStructure);	//設定

	//GPIOC
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);	//クロック供給
	GPIO_StructInit(&GPIO_InitStructure);	//構造体を初期化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_10
			| GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_14 | GPIO_Pin_15;//設定するピンを決める
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//クロック
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		//出力に設定
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//オープンドレインorプッシュプル
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	//プルアップかプルダウンか
	GPIO_Init(GPIOC, &GPIO_InitStructure);	//設定

	//初期値
	GPIO_SetBits(GPIOC, GPIO_Pin_2);	//Pinを1に
	GPIO_SetBits(GPIOC, GPIO_Pin_3);	//Pinを1に
	GPIO_SetBits(GPIOC, GPIO_Pin_10);	//Pinを1に
	GPIO_SetBits(GPIOC, GPIO_Pin_11);	//Pinを1に
	GPIO_SetBits(GPIOC, GPIO_Pin_12);	//Pinを1に
	GPIO_SetBits(GPIOC, GPIO_Pin_14);	//Pinを1に
	GPIO_SetBits(GPIOC, GPIO_Pin_15);	//Pinを1に

	//GPIOH
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
	GPIO_StructInit(&GPIO_InitStructure);	//構造体を初期化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;	//設定するピンを決める
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//クロック
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		//出力に設定
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//オープンドレインorプッシュプル
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	//プルアップかプルダウンか
	GPIO_Init(GPIOH, &GPIO_InitStructure);	//設定

	GPIO_SetBits(GPIOH, GPIO_Pin_0);
	GPIO_SetBits(GPIOH, GPIO_Pin_1);

}

void init_adc(void) {
//GPIO側でアナログモードに設定
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

//AD変換の設定
	ADC_InitTypeDef ADC_InitStructure;		//初期設定用の構造体定義
	ADC_CommonInitTypeDef ADC_CommonInitStructure;

	ADC_Cmd(ADC1, DISABLE);		//ADC1をDisableに
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);		//クロック供給
	ADC_DeInit();		//ADCの周辺レジスタをデフォルトの値にリセットする

	//AD変換の基本設定
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;	//PCLK/4 = 16/4 MHz?
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;	//DMAは使用しない
	ADC_CommonInitStructure.ADC_TwoSamplingDelay =
	ADC_TwoSamplingDelay_20Cycles;//連続スキャンとかで使用？　ADC_delay_between_2_sampling_phases
	ADC_CommonInit(&ADC_CommonInitStructure);

	//ADC1の設定
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;		//12bitのAD変換
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;		//シングルモードで動作
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;		//シングルモードで動作
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;	//AD変換の開始に外部トリガは使用しない
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Left;	//右詰め左詰め
	ADC_InitStructure.ADC_NbrOfConversion = 9;		//AD変換の入力は9チャンネル
	ADC_Init(ADC1, &ADC_InitStructure);

	ADC_Cmd(ADC1, ENABLE);		//ADC1をEnableに
	ADC_DMACmd(ADC1, DISABLE);	//DMAは使わない

}

void init_usart(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	//必要な周辺機能にクロックを供給(PA9,PA10がTX,RXなので、GPIOAとUSART1)
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	//GPIOをUSARTにRemapする。　他のSTM32のシリーズとかはGPIO_PinAFConfigまでいじらなくて良いらしい。
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = 115200;	//ポーレート設定
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//パケットのワード長を8bitに
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	//ストップビットを1に設定。
	USART_InitStructure.USART_Parity = USART_Parity_No;	//パリティーを無し
	USART_InitStructure.USART_HardwareFlowControl =
	USART_HardwareFlowControl_None;		//フロー制御をなしに。
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//TXとRXにモード設定
	USART_Init(USART1, &USART_InitStructure);	//USART1設定
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1, ENABLE);		//USART1起動

}

void init_spi(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);		//クロック供給

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_StructInit(&GPIO_InitStructure);

	//スレーブセレクト端子
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//データ送信関係のGPIO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_SetBits(GPIOA, GPIO_Pin_4);		//スレーブセレクト

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);

	SPI_InitTypeDef SPI_InitStructure;

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	//双方向送信
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//データサイズは8bit
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;	//クロック定常状態はLow
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	//
	//部長の表だとこれでいいはずだけどなぜかうまくいかない。
	//SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;	//クロック定常状態はHigh　http://hantasmouse.hatenablog.jp/entry/2015/12/12/142413参照
	//SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;//http://hantasmouse.hatenablog.jp/entry/2015/12/12/142413参照
	SPI_InitStructure.SPI_NSS = SPI_NSSInternalSoft_Set | SPI_NSS_Soft;	//スレーブセレクトはソフトで
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;//SCKクロックの送受信のボーレート設定
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;			//MSBファースト
	SPI_InitStructure.SPI_CRCPolynomial = 7;		//誤り訂正（CRC）。0は設定禁止。でも使ってない。
	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd(SPI1, ENABLE);

	GPIO_SetBits(GPIOA, GPIO_Pin_4); // CSをセット

}

const uint16_t MAX_PERIOD = (420 - 1);//PWMの周波数決めのための最大カウント
void init_pwm() {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_ResetBits(GPIOC, GPIO_Pin_2);		//モータードライバーをスリープモードに

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
	TIM_InitStructure.TIM_Period = MAX_PERIOD;//カウンタクリア要因 200kHz ExcelファイルからTIMのクロックを確認
	TIM_InitStructure.TIM_Prescaler = 0;//プリスケーラ(カウンタがPrescaler回カウントされたタイミングで，TIMのカウンタが1加算される)
	TIM_InitStructure.TIM_ClockDivision = 0;	//デットタイム発生回路用の分周。通常0(分周しない)。
	TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;	//アップカウント
	TIM_InitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &TIM_InitStructure);
	TIM_TimeBaseInit(TIM5, &TIM_InitStructure);

	TIM_OCInitTypeDef TIM_OC_InitStructure;
	TIM_OC_InitStructure.TIM_OCMode = TIM_OCMode_PWM1;		//モードはPWM1
	TIM_OC_InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//たぶんいらない。This parameter is valid only for TIM1 and TIM8.
	TIM_OC_InitStructure.TIM_OutputState = TIM_OutputState_Enable;//たぶんいらない。This parameter is valid only for TIM1 and TIM8.
	TIM_OC_InitStructure.TIM_Pulse = 0;	//パルス幅。Duty比に関係。

	//PWM出力が4本必要なので各タイマ2つずつ
	TIM_OC1Init(TIM4, &TIM_OC_InitStructure);		//TIM4のCH1
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC2Init(TIM4, &TIM_OC_InitStructure);		//TIM4のCH2
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC1Init(TIM5, &TIM_OC_InitStructure);		//TIM5のCH1
	TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);
	TIM_OC2Init(TIM5, &TIM_OC_InitStructure);		//TIM5のCH2
	TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM5);

	//TIM起動
	TIM_ARRPreloadConfig(TIM4, ENABLE);
	TIM_ARRPreloadConfig(TIM5, ENABLE);
}
