/*
 * serial.c
 *
 *  Created on: 2015/09/12
 *      Author: Koizumi
 */

#include"serial.h"

//1�o�C�g���M
void put1byte(char send_data) {
	USART_SendData(USART1, send_data); //1�o�C�g�f�[�^�̑��M
	while( USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);//�f�[�^���M���I������܂őҋ@
}


//n�o�C�g���M
void putnbyte(char *buf, int16_t len) {
	for (uint16_t byte_count = 0; byte_count < len; byte_count++) {
		put1byte(buf[byte_count]);
	}
}


//�����o�͊֐��@myprintf�@�̒�`
int myprintf(const char *fmt, ...) {
	static char buffer[100];
	int len;	//���M�f�[�^�̑傫��
	va_list ap;		//�ϒ����������Ɏg�p����ϐ���`
	va_start(ap, fmt);		//�ϒ������A�N�Z�X�̂��߂̏�������
	len = vsprintf(buffer, fmt, ap);	// �ϒ������f�[�^�̏�������
	putnbyte(buffer, len);	//�����f�[�^���M
	va_end(ap);		//�ϒ������A�N�Z�X��̏I������
	return len;
	SystemInit();		//�N���b�N���Ȃ���V�X�e������̏������H
	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq(&RCC_Clocks);	//RCC_Clocks�ɒl�����H ���Ԃ�SYSCLK_Frequency16MH�����������Ă�.HCLK��SYSCLK�Ɠ����H(16MH��)
	SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);//SysTick���荞�݂̎������߁B�J�E���g�̍ő�����B����Ŏ���1ms�̂͂��B
	//SysTick���荞�݂̗D��x��15�ōŒ�B�Y�ꂻ�������烁�����Ă����B


}


