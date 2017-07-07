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
	enum DIRECTION {
		front, back, right, left
	};

	static void light(const my7seg::DIRECTION direction);//up,right,leftを指定すると上辺、右辺、左辺が光る
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
enum MOTOR_SIDE {
	m_left = 0, m_right = 1
};

class motor {
private:

	static signed char right_duty, left_duty;		//duty[％]

	static const char MAX_DUTY;	 	//Dutyの最大値［％］
	static const char MAX_COUNT;	//Dutyの最大値［％］

	static bool motor_state;		//motorが起動していればTRUE。

	motor();

public:
	static signed short get_duty_left();	//左モーターのDuty取得
	static signed short get_duty_right();	//右モーターのDuty取得

	static void set_duty(const MOTOR_SIDE side, const float set_duty);//モーターのDuty決定

	static void sleep_motor();		//モータードライバをスリープ状態に
	static void stanby_motor();		//モータードライバをスタンバイ状態に

	static bool isEnable();		//motorが起動しているかどうか

	~motor();
};

//gyro関連
//時計回りが正
//センサータイプを表す列挙型
typedef enum {
	axis_x = 0, axis_y = 1, axis_z = 2, dim_num
} AXIS_t;
class mpu6000 {
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
	static uint16_t read_spi(uint16_t read_reg);		//SPI通信でregレジスタから読みだす
	static void write_spi(uint16_t reg, uint16_t data);	//SPI通信でregレジスタにdataを書き込む


public:
	static volatile int16_t get_mpu_val(SEN_TYPE sen, AXIS_t axis);//senセンサーのaxis軸方向のデータを読む

	mpu6000();

public:
	static void init_mpu6000();

	~mpu6000();

};

class accelmeter: public mpu6000 {
public:		//松井式速度推定法で用いるため
	static const uint8_t AVERAGE_COUNT;		//加速度計の平均取る回数[回]
	static const float ACCEL_PERIOD;		//加速度計の制御周期[s]
private:
	static const float REF_TIME;			//加速度計のリファレンスとる時間[s]

	static float accel_ad[AXIS_t::dim_num];		//加速度の生値
	static float accel_ref[AXIS_t::dim_num];
	static float accel[AXIS_t::dim_num];		//加速度 [m/ss]

	static float get_accel_ref(AXIS_t xyz);
	static float get_accel_ad(AXIS_t xyz);		//xyz方向の加速度[m/s]を返す

	accelmeter();

public:

	static void interrupt();
	static void set_accel_ref();
	static void set_accel_ref(AXIS_t xyz);
	static void cal_accel();	//生値を加速度に変換[m/ss]

	static float get_accel();		//進行方向の加速度[m/s]
	static float get_accel(AXIS_t xyz);		//m/sでXYZ方向の加速度を返す

};

class gyro: public mpu6000 {
private:
	static const float GYRO_PERIOD;			//ジャイロの制御周期[s]
	static const float REF_TIME;			//ジャイロのリファレンスとる時間[s]

	static int16_t gyro_value;
	static float default_angle;				//最小二乗法で補正をかけてない角度
	static float angle, gyro_ref;
	static float angular_velocity;

	static float get_gyro_ref();
	static void set_least_square_slope();				//最小二乗法をまわして補正項を計算

	static void cal_angular_velocity();				//角速度計算[rad/s]
	static void cal_angle();				//角度計算[rad]

	gyro();

public:
	static float least_square_slope;				//補正項の傾き

	static void interrupt();		//割り込み内で呼ばれる
	static int16_t get_gyro();
	static void set_gyro_ref();

	static void reset_angle();
	static float get_angle();
	static float get_angular_velocity();

	~gyro();

};

//encoder
typedef enum {
	enc_right = 0, enc_left = 1
} ENC_SIDE;
class encoder {
private:
	const static uint8_t MOVING_AVERAGE;	//移動平均をとる時間　単位は制御周期
	const static uint32_t MEDIAN;		//カウントの中央値
	static float correct[2][4097];	//補正用のテーブル
	static bool correct_flag[2];	//補正中か否か
	static uint32_t init_time[2];	//補正の開始時間
	static int16_t finish_time[2];	//補正終了時の時間

	static bool isCorrect[2];		//Y.I.式補正を行っているかどうかのフラグ

	encoder();

	static volatile float raw_to_correct(ENC_SIDE enc_side, int16_t raw_delta);	//補正テーブルで生値を補正する,返り値はコンバートした後の差分値



public:


	static float right_velocity, left_velocity, velocity;
	static int16_t raw_count[2];	//エンコーダ―の生値

	static void interrupt();		//モーターのEncoderの値計算
	static float get_velocity();	//左右の平均(重心速度)のEncoder取得[m/s]　 移動平均取ってることに注意！

	static volatile void yi_correct(ENC_SIDE enc_right);		//片方ずつY.I.式補正法を行う。（補正テーブルの作成）
	static void yi_correct();		//Y.I.式補正法を行う。（補正テーブルの作成）

	static void draw_correct(bool right, bool left);		//Y.I.式補正テーブルを表示

	~encoder();
};

//光学センサー関連
#define GAP_AVE_COUNT 10	//XXX 壁の切れ目対策にいくつの平均をとるか
class photo {
private:
public:
	static int16_t ave_buf[element_count][GAP_AVE_COUNT];	//センサー値（平均取ったやつ）のバッファ　壁の切れ目チェックとかで使う
	static float diff_buf[element_count][GAP_AVE_COUNT];	//今のセンサー値とave_bufの差　壁の切れ目チェックとかで使う
	static uint8_t gap_buf[element_count][GAP_AVE_COUNT];		//count_wall_gapで数え上げた値を保存しておく

	static signed int right_ad, left_ad, front_right_ad, front_left_ad,
			front_ad;
	static signed int right_ref, left_ref, front_right_ref, front_left_ref,
			front_ref;
	static bool light_flag;		//赤外線LEDを光らせてセンサー値を読むかどうかのフラグ


	static void switch_led(PHOTO_TYPE sensor_type, bool is_light);//LEDをつけたり消したり

	static int16_t get_ref(PHOTO_TYPE sensor_type);	//OFFのときのAD値を返す
	static void set_ref(PHOTO_TYPE sensor_type, int16_t set_value);	//refの値を代入

	photo();

public:

	static uint16_t get_ad(PHOTO_TYPE sensor_type);			//??_adの値を取得
	static void set_ad(PHOTO_TYPE sensor_type, int16_t set_value);	//??_adに値を代入

	static void light(PHOTO_TYPE sensor_type);
	static void turn_off(PHOTO_TYPE sensor_type);
	static void turn_off_all();		//すべて消す

	//割り込み内で行う処理
	static void interrupt(bool is_light);

	static int16_t get_value(PHOTO_TYPE sensor_type);

	//センサ値から距離に変換し、区画中心からどれだけずれているのか[mm]を返す。右側正
	static float get_displacement_from_center(PHOTO_TYPE sensor_type);

	//TODO この関数はマウスclassにあるべきかも
	static bool check_wall(unsigned char muki);
	static bool check_wall(PHOTO_TYPE type);

	static int8_t count_wall_gap(PHOTO_TYPE);	//diff_gapに保存されてる値の正負を数え上げて返す。
	static bool check_wall_gap(PHOTO_TYPE type, int16_t threshold);	//移動平均をとったやつでGAP_AVE_COUNT前と比較して絶対値がthreshold以上なら、壁の切れ目だからtrue

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
	static volatile float cross_delta_gain(SEN_TYPE sensor);		//P_GAIN*P_DELTA+・・・を行う
	static float ctrl_accel_int;			//加速度のFB制御量の積分値

	static bool wall_control_flag;		//壁制御をかけてればtrue、切ってればfalse。
	static bool control_phase;		//姿勢制御をかけてるか否か。かけていればtrue

	//加速度はカスケード接続ではなく、速度とは独立に制御量を出し、それの積分を速度制御量に足す
	static float control_accel();		//加速度に関するPID制御(加速度センサのみ)。戻り値は[Duty/時間]？
	static float control_velocity();		//速度に関するPID制御(エンコーダーのみ)。戻り値はDuty？
	static float control_angular_velocity();//速度に関するPID制御(エンコーダーのみ)。戻り値はDuty？

	static float get_feedback(const signed char right_or_left);	//FBを掛けた後のDutyを返す。PID制御。
	static float get_feedforward(const signed char right_or_left);//FFを掛けた後のDutyを返す。

	static bool is_FF_CONTROL, is_FB_CONTROL;	//FFとFBの制御かけるかどうか。かけるならTrue
	static bool is_accel_CONTROL;		//加速度のFB制御かけるかどうか
	control();

public:
	static PID gyro_delta, photo_delta, encoder_delta, accel_delta;	//各種Δ

	static void cal_delta();	//割り込み関数内で、偏差を計算する

	static void posture_control();	//FF,FB制御をかける。set_dutyまで行う。

	static void start_wall_control();	//壁制御をかける
	static void stop_wall_control();	//壁制御を切る

	static void start_control();	//制御をかける
	static void stop_control();	//制御をとめる

	static bool get_control_phase();	//制御がかかっているかを取得。かかっていればtrue
	static bool get_wall_control_phase();	//制御がかかっているかを取得。かかっていればtrue

	static void reset_delta();
	static volatile void reset_delta(SEN_TYPE type);	//特定のセンサーの偏差だけ0にする

	static void fail_safe();	//Iゲインが一定以上いったらモーターを止める

	~control();
};

//カルマンフィルタを行う
//値と分散を管理する用の構造体
class kalman{
//変数名の名づけ方はWikiに従う
//https://ja.wikipedia.org/wiki/%E3%82%AB%E3%83%AB%E3%83%9E%E3%83%B3%E3%83%95%E3%82%A3%E3%83%AB%E3%82%BF%E3%83%BC
private:
	float x;		//現在の値
	float p;		//現在の分散
	float EstP,ObsP;	//推定値と観測値の分散

public:
	//カルマンフィルタによる補正を行う。
	void update(float EstimateU, float ObserveZ);		//前回の値からどれだけ変化するかの推定値EstimateU,観測値ObserveZを入れると補正する。

	float get_value();				//現在の値を返す
	float get_dispersion();			//現在の分散を返す

	kalman();
	kalman(float EstimateP, float ObserveP);	//最初に推定値の分散と観測値の分散をパラメータとして入れる
	kalman(float initX, float initP, float EstimateP, float ObserveP);	//さらに初期値も入れたいなら
	~kalman();
};

#endif /* HARDWARE_H_ */
