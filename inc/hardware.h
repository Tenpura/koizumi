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
#include "ad_convert.h"
#include "parameter.h"
#include"run.h"




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

	static bool motor_state;		//motorが起動していればTRUE。

	motor();

public:
	static signed char right_duty,left_duty;		//duty[％]

	static void set_duty(const MOTOR_SIDE side, const float set_duty);//モーターのDuty決定

	static void sleep_motor();//モータードライバをスリープ状態に
	static void stanby_motor();//モータードライバをスタンバイ状態に

	static bool isEnable();		//motorが起動しているかどうか

	~motor();
};



//gyro関連
//時計回りが正
//センサータイプを表す列挙型
typedef enum {
	axis_x = 0, axis_y = 1, axis_z = 2
} AXIS_t;
class mpu6000{
private:
	//レジスター定義
	static const uint16_t GYRO_XOUT_H;
	static const uint16_t GYRO_XOUT_L;
	static const uint16_t GYRO_YOUT_H;
	static const uint16_t GYRO_YOUT_L;
	static const uint16_t GYRO_ZOUT_H;
	static const uint16_t GYRO_ZOUT_L;
	static const uint16_t ACCEL_XOUT_H;
	static const uint16_t ACCEL_XOUT_L;
	static const uint16_t ACCEL_YOUT_H;
	static const uint16_t ACCEL_YOUT_L;
	static const uint16_t ACCEL_ZOUT_H;
	static const uint16_t ACCEL_ZOUT_L;


	static SPI_TypeDef* use_SPI;	//使うSPIのタイプ
	static GPIO_TypeDef* cs_GPIOx;	//csをたたくIOピンのタイプ		ex)GPIOA
	const static uint16_t cs_GPIO_Pin;	//csをたたくIOピンの番号

protected:
public:
	static uint16_t read_spi(uint16_t read_reg);		//SPI通信でregレジスタから読みだす
	static void write_spi(uint16_t reg, uint16_t data);		//SPI通信でregレジスタにdataを書き込む
	static int16_t get_mpu_value(SEN_TYPE sen, AXIS_t axis);		//senセンサーのaxis軸方向のデータを読む

	mpu6000();

public:
	static void init_mpu6000();

	~mpu6000();


};

class accelmeter : public mpu6000{
public:
	static const uint8_t AVERAGE_COUNT;		//加速度計の平均取る回数[回]
	static const float ACCEL_PERIOD;		//加速度計の制御周期[s]

private:
	static const float REF_TIME;			//加速度計のリファレンスとる時間[s]

	static float accel_ad;		//前後方向の加速度の生値
	static float accel_ref;
	static float accel;		//前後方向の加速度 [m/ss]

	static float get_accel_ref();
	static float get_accel_ad();

	accelmeter();

public:

	static void interrupt();
	static void set_accel_ref();
	static void cal_accel();	//生値を加速度に変換[m/ss]

	static float get_accel();



};

class gyro : public mpu6000{
private:
	static const float GYRO_PERIOD;			//ジャイロの制御周期[s]
	static const float REF_TIME;			//ジャイロのリファレンスとる時間[s]

	static int16_t gyro_value;
	static float default_angle;				//最小二乗法で補正をかけてない角度
	static float angle,gyro_ref;
	static float angular_velocity;

	static float get_gyro_ref();
	static void set_least_square_slope();//最小二乗法をまわして補正項を計算

	gyro();

public:
	static float least_square_slope;//補正項の傾き

	static void interrupt_gyro();
	static int16_t get_gyro();
	static void set_gyro_ref();

	static void reset_angle();
	static void cal_angle();//角度計算[rad]
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

	encoder();

public:
	static float right_velocity,left_velocity,velocity;

	static void interrupt_encoder();		//モーターのEncoderの値計算
	static float get_velocity();//左右の平均(重心速度)のEncoder取得[m/s]　 移動平均取ってることに注意！

	~encoder();
};

//光学センサー関連
class photo {
private:

	static signed int right_ad, left_ad, front_right_ad, front_left_ad,front_ad;
	static signed int right_ref, left_ref, front_right_ref, front_left_ref,front_ref;
	static bool light_flag;		//赤外線LEDを光らせてセンサー値を読むかどうかのフラグ

	static void switch_led(PHOTO_TYPE sensor_type, bool is_light);		//LEDをつけたり消したり

	static uint16_t get_ad(PHOTO_TYPE sensor_type);			//??_adの値を取得
	static void set_ad(PHOTO_TYPE sensor_type, int16_t set_value);		//??_adに値を代入

	static int16_t get_ref(PHOTO_TYPE sensor_type);	//OFFのときのAD値を返す
	static void set_ref(PHOTO_TYPE sensor_type, int16_t set_value);		//refの値を代入

	photo();

public:

	static void light(PHOTO_TYPE sensor_type);
	static void turn_off(PHOTO_TYPE sensor_type);
	static void turn_off_all();		//すべて消す


	//割り込み内で行う処理
	static void interrupt(bool is_light);

	static int16_t get_value(PHOTO_TYPE sensor_type);

	//TODO この関数はマウスclassにあるべきかも
	static bool check_wall(unsigned char muki);
	static bool check_wall(PHOTO_TYPE type);



	~photo();

};



//それぞれのセンサから制御をかけるクラス

//PIDのゲインと偏差を管理する用の構造体
typedef struct {
	float P;
	float I;
	float D;
} PID;

class control {
private:
	//TODO D項はいらないらしいハセシュン曰く
	static float cross_delta_gain(SEN_TYPE sensor);//P_GAIN*P_DELTA+・・・を行う

	static bool wall_control_flag;//壁制御をかけてればtrue、切ってればfalse。
	static bool control_phase;//姿勢制御をかけてるか否か。かけていればtrue

	static float control_velocity();//速度に関するPID制御(エンコーダーのみ)。戻り値はDuty？
	static float control_angular_velocity();//速度に関するPID制御(エンコーダーのみ)。戻り値はDuty？

	static float get_feedback(const signed char right_or_left);//FBを掛けた後のDutyを返す。PID制御。
	static float get_feedforward(const signed char right_or_left);//FFを掛けた後のDutyを返す。

	static bool is_FF_CONTROL,is_FB_CONTROL;	//FFとFBの制御かけるかどうか。かけるならTrue

	control();

public:
	static PID gyro_delta,photo_delta,encoder_delta;//各種Δ

	static void cal_delta();//割り込み関数内で、偏差を計算する

	static void posture_control();//FF,FB制御をかける。set_dutyまで行う。

	static void start_wall_control();//壁制御をかける
	static void stop_wall_control();//壁制御を切る

	static void start_control();//制御をかける
	static void stop_control();//制御をとめる

	static bool get_control_phase();//制御がかかっているかを取得。かかっていればtrue
	static bool get_wall_control_phase();//制御がかかっているかを取得。かかっていればtrue

	static void reset_delta();

	static void fail_safe();//Iゲインが一定以上いったらモーターを止める

	~control();
};


#endif /* HARDWARE_H_ */
