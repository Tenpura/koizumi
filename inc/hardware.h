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
#include "init.h"

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


//motor関連
extern const uint16_t MAX_PERIOD;
enum MOTOR_SIDE{
		motor_left=0,
		motor_right=1
};

class motor {
private:

	static signed short get_duty_left();	//左モーターのDuty取得
	static signed short get_duty_right();//右モーターのDuty取得

	static const char MAX_DUTY;	 	//Dutyの最大値［％］
	static const char MAX_COUNT;	//Dutyの最大値［％］

	motor();

public:
	static signed char right_duty,left_duty;		//duty[％]

	static void set_duty(const MOTOR_SIDE side, const signed short set_duty);//モーターのDuty決定

	static void sleep_motor();//モータードライバをスリープ状態に
	static void stanby_motor();//モータードライバをスタンバイ状態に

	~motor();
};


#endif /* HARDWARE_H_ */
