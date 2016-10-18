/*
 * hardware.h
 *
 *  Created on: 2015/06/14
 *      Author: Koizumi
 */

#ifndef HARDWARE_H_
#define HARDWARE_H_

#include "stm32f4xx.h"
#include "define.h"
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



//gyro関連
//時計回りが正
class mpu6000{
private:
	static SPI_TypeDef* use_SPI;	//使うSPIのタイプ
	static GPIO_TypeDef* cs_GPIOx;	//csをたたくIOピンのタイプ		ex)GPIOA
	const static uint16_t cs_GPIO_Pin;	//csをたたくIOピンの番号

protected:
	static uint16_t read_spi(uint16_t read_reg);		//SPI通信でregレジスタから読みだす
	static void write_spi(uint16_t reg, uint16_t data);		//SPI通信でregレジスタにdataを書き込む
	mpu6000();

public:
	static void init_mpu6000();

	~mpu6000();


};

class gyro : public mpu6000{
private:
	static const float GYRO_PERIOD;			//ジャイロの制御周期[s]
	static const float REF_TIME;			//ジャイロのリファレンスとる時間[s]

	static unsigned short gyro_value;
	static float default_angle;				//最小二乗法で補正をかけてない角度
	static float angle,before_angle,gyro_ref;
	static float angular_velocity;

	static float get_gyro_ref();
	static void set_least_square_slope();//最小二乗法をまわして補正項を計算

	gyro();

public:
	static float least_square_slope;//補正項の傾き

	static void interrupt_gyro();
	static unsigned short get_gyro();
	static void set_gyro_ref();

	static void reset_angle();
	static void cal_angle();//角度計算[°]
	static float get_angle();

	static void cal_angular_velocity();//角速度計算[rad/s]
	static float get_angular_velocity();

	~gyro();

};


//encoder
class encoder {
private:
	const static uint32_t MOVING_AVERAGE;	//移動平均をとる時間　単位は制御周期
	const static uint32_t MEDIAN;		//カウントの中央値

	static float right_velocity,left_velocity,velocity;
	encoder();

public:
	static void cal_encoder();		//モーターのEncoderの値計算
	static float get_velocity();//左右の平均(重心速度)のEncoder取得[m/s]　 移動平均取ってることに注意！

	~encoder();
};

#endif /* HARDWARE_H_ */
