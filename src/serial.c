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

}


