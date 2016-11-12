/*
 * run.h
 *
 *  Created on: 2016/10/23
 *      Author: Koizumi
 */

#ifndef RUN_H_
#define RUN_H_

#include"define.h"
#include"hardware.h"
#include"parameter.h"
#include"map.h"

//position
typedef union {
	unsigned char all;
	struct {
		unsigned char x :4;
		unsigned char y :4;
	} bit;
} POSITION;

class mouse {
private:
	static float ideal_acceleration;			//マウスの加速度[m/s^2]
	static float ideal_angular_acceleration;			//マウスの加角速度[rad/s^2]

	static float ideal_velocity;			//マウスの目標速度[m/s]
	static float ideal_angular_velocity;			//マウスの目標角速度[rad/s]

	//理想値から計算した距離と角度
	static float ideal_distance;
	static float ideal_angle;

	static float run_distance;			//マウスの走行距離[m]

	static unsigned long mouse_count_ms;			//マウスの時間[msec].基本リセットしない

	static bool fail_flag;		//フェイルセーフがかかるとこのフラグがTRUEに

	static POSITION position;		//マウスの位置（座標）
	static unsigned char mouse_direction;		//マウスの向き

	static void cal_velocity();		//加速を行う。速度の加減算
	static void cal_distance();		//距離計算

	mouse();

public:

	static MAP_DATA now_map;

	static void reset_count();
	static void add_one_count_ms();		//カウントに1加算。割り込み内のみで呼び出す
	static unsigned long get_count_ms();		//カウント取得。単位はms

	static float get_acceleration();
	static void set_acceleration(const float set_value_m_ss);

	static float get_angular_acceleration();
	static void set_angular_acceleration(const float set_value_m_ss);

	static float get_ideal_velocity();
	static void set_ideal_velocity(const float set_value_m_s);

	static float get_ideal_angular_velocity();
	static void set_ideal_angular_velocity(const float set_value_rad_s);

	static void set_ideal(const float accel, const float vel, const float dis);
	static void set_ideal_ang(const float ang_a, const float ang_omega);

	static float get_angle_degree();
	static float get_ideal_angle_degree();
	static void reset_angle();

	static float get_distance_m();		//距離を取得
	static void set_distance_m(const float set_value_m);		//距離をセット

	static unsigned char get_x_position();
	static unsigned char get_y_position();
	static void set_position(const uint8_t set_x, const uint8_t set_y);

	static unsigned char get_direction();	//defineされたMUKI_??で返す
	static void get_direction(signed char *direction_x,
			signed char *direction_y);		//引数の値をポインタ経由で変更する
	static void set_direction(const unsigned char muki);
	static void set_direction(const signed char direction_x,
			const signed char direction_y);

	static bool get_fail_flag();		//フェイルセーフがかかったかどうかの判別用
	static void set_fail_flag(bool set_flag);

	static void interrupt();	//割り込み関数内で実行するよう

	static void run_init(bool posture_ctrl, bool wall_ctrl);	//走る直前に実行するやつ

	//壁を見て、壁が存在するなら壁を作り、ないなら壊す。見たことも記録
	//マウスの向きや座標も内部できちんと考える
	static void look_wall(bool comb_ignore);	//壁を見る関数

	//壁があるか確認用の関数
	static void velify_wall();

	static void error();	//フェイルセーフとか、かかった時に、ここに飛びますよ

	~mouse();

};

class run {
private:
	run();
	static uint8_t WALL_EAGE_DISTANCE[PHOTO_TYPE::element_count];

public:
	static void accel_run(const float distance_m, const float end_velocity,
			const unsigned char select_mode);
	static void accel_run_wall_eage(const float distance_m, const float end_velocity,
			const unsigned char select_mode, const float check_distance);

	static void slalom(const SLALOM_TYPE slalom_type, const signed char right_or_left,const uint8_t select_mode);
	static void spin_turn(const float target_degree);
	~run();

};

//ACTION_TYPE 足立法のとき次に取る行動の種類
typedef enum {
	go_straight, turn_right, turn_left, back, stop
} ACTION_TYPE;

class adachi {
private:
	static signed char direction_x, direction_y;

	static void set_direction();

	//現在の座標と向きを与えると歩数的にそのマスに進めるかを判別
	static bool check_move_by_step(unsigned char target_x,
			unsigned char target_y, unsigned char muki);

	//目標のマスのまだ見てない壁の数を数え上げる
	static unsigned int count_unknown_wall(unsigned char target_x,
			unsigned char target_y);

	//引数に応じて次の行動をマウスが実行する（実際に動く部分）
	static void run_next_action_by_spin(ACTION_TYPE next_action);
	static void run_next_action(ACTION_TYPE next_action);
	static void simulate_next_action(ACTION_TYPE next_action);//機体は動かない。仮想的に変数とか更新。デバック用

	//次行く方向と今の向きを与えると、次に取る行動を返す。優先度は、直進、右ターン、左ターン、バックの順
	static ACTION_TYPE get_next_action(DIRECTION next_direction,
			uint8_t now_muki);

	adachi();

public:
	static bool adachi_method(const unsigned char target_x,
			const unsigned char target_y, bool is_FULUKAWA);
	static bool adachi_method_spin(unsigned char target_x,
			unsigned char target_y, bool is_FULUKAWA);

	static bool left_hand_method(const uint8_t target_x,
			const uint8_t target_y);
	~adachi();

};

#endif /* RUN_H_ */
