/*
 * serial.c
 *
 *  Created on: 2015/09/12
 *      Author: Koizumi
 */

#include"serial.h"

//1バイト送信
void put1byte(char send_data) {
	USART_SendData(USART1, send_data); //1バイトデータの送信
	while( USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);//データ送信が終了するまで待機
}


//nバイト送信
void putnbyte(char *buf, int16_t len) {
	for (uint16_t byte_count = 0; byte_count < len; byte_count++) {
		put1byte(buf[byte_count]);
	}
}


//文字出力関数　myprintf　の定義
int myprintf(const char *fmt, ...) {
	static char buffer[100];
	int len;	//送信データの大きさ
	va_list ap;		//可変長引数処理に使用する変数定義
	va_start(ap, fmt);		//可変長引数アクセスのための初期処理
	len = vsprintf(buffer, fmt, ap);	// 可変長引数データの書き込み
	putnbyte(buffer, len);	//文字データ送信
	va_end(ap);		//可変長引数アクセス後の終了処理
	return len;

}


