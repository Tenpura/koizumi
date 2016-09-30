/*
 * hardware.h
 *
 *  Created on: 2015/06/14
 *      Author: Koizumi
 */

#ifndef HARDWARE_H_
#define HARDWARE_H_

#include "stm32f4xx.h"
#include "extern_c.h"
#include "user.h"

/*
 #include"define.h"
 #include"parameter.h"
 #include"ad_convert.h"
 #include"user.h"
 #include"run.h"
 */


//自作7セグ関連
class my7seg {
private:
public:
	static void light(const unsigned char number);		//つける
	static void turn_off();		//消す

	static void light_error();		//Eと光らせる

	//repeat_count回だけ点滅する。消えてる状態で終わる
	static void blink(const unsigned char number,
			const unsigned short blink_cycle_ms,
			const unsigned short repeat_count);

	//start_numberから0までカウントダウン
	static void count_down(const unsigned char start_number,
			const unsigned short cycle_ms);

};

#endif /* HARDWARE_H_ */
