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
#include"flash.h"
#include <queue>
#include <cmath>
#include <array>

//position
typedef union {
	uint16_t all;
	struct {
		uint8_t x :8;
		uint8_t y :8;
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
	static float ideal_angle_degree;
	//マウスの進行方向に対しての相対角度[rad]の基準　この角度と絶対角度の差が相対角度
	static float relative_base_rad;
	//マウスの実際の速度[m/s]と距離[m]
	static float velocity;
	static float run_distance;
	//マウスの絶対位置[m]
	static COORDINATE place;
	//マウスの区画内に対する相対位置[m] 原点は区画中央
	static COORDINATE relative;

	static unsigned long mouse_count_ms;			//マウスの時間[msec].基本リセットしない

	static bool is_fail_safe;		//フェイルセーフがかかるとこのフラグがTRUEに
	static bool is_spin_turn;

	static POSITION position;		//マウスの位置（座標）
	//static unsigned char mouse_direction;		//マウスの向き
	static compas direction;		//マウスの向き

	static void cal_velocity();		//加速を行う。速度の加減算
	static void cal_distance();		//距離計算
	static void cal_place();		//位置を計算する　迷路の座標と軸の方向は同じ

	mouse();

public:
	static uint32_t debag_val_enc_l;		//デバック用変数
	static uint32_t debag_val_enc_r;		//デバック用変数

	static MAP_DATA now_map;

	static void reset_count();
	static void add_one_count_ms();		//カウントに1加算。割り込み内のみで呼び出す
	static unsigned long get_count_ms();		//カウント取得。単位はms

	static float get_ideal_accel();
	static void set_ideal_accel(const float set_value_m_ss);

	static float get_ideal_angular_accel();
	static void set_ideal_angular_accel(const float set_value_m_ss);

	static float get_ideal_velocity();
	static void set_ideal_velocity(const float set_value_m_s);
	static float get_velocity();

	static float get_ideal_angular_velocity();
	static void set_ideal_angular_velocity(const float set_value_rad_s);
	static float get_angular_velocity();

	static void set_ideal_ang(const float ang_a, const float ang_omega);
	static void set_ang(const float set_rad);
	static float get_ideal_angle_degree();
	static float get_ideal_angle_radian();
	static float get_angle_degree();
	static float get_angle_radian();
	static void reset_angle();

	static void set_ideal(const float accel, const float vel, const float dis);

	static float get_distance_m();		//距離を取得
	static void set_distance_m(const float set_value_m);		//距離をセット

	static unsigned char get_x_position();
	static unsigned char get_y_position();
	static void set_position(const uint8_t set_x, const uint8_t set_y);

	static void set_place(const COORDINATE set);
	static void set_place(const float x, const float y);
	static COORDINATE get_place();

	//TODO 斜めの処理
	static float get_relative_side();		//進行方向と垂直方向にどれだけずれているか[m] マウスから見て右側正
	static float get_relative_go();		//区画中心を原点としたとき、進行方向にどれだけ進んでいるか[m]
	static void set_relative_go(float _set_value);		//updata_abs は絶対座標を更新するかどうか
	static void set_relative_side(float _set_value);		//updata_abs は絶対座標を更新するかどうか

	static float get_relative_rad();		//進行方向を0としたときにどれだけずれているか
	static void set_relative_rad(float set_rad, bool updata_abs);		//relative_radがset_radになるように修正する
	static void set_relative_base_rad(SLALOM_TYPE sla, bool is_right);	//ターン時の、相対角度の基準変更用

	//static unsigned char get_direction();	//defineされたMUKI_??で返す
	static compas get_compas();	//defineされたMUKI_??で返す
	static void get_direction(signed char *direction_x,
				signed char *direction_y);		//引数の値をポインタ経由で変更する
	static void get_direction(float *dir_x, float *dir_y);		//斜め対応
	static void set_direction(compas dir);
	static void set_direction(const signed char direction_x,
			const signed char direction_y);

	static bool get_fail_flag();		//フェイルセーフがかかったかどうかの判別用
	static void set_fail_flag(bool set_flag);

	static bool get_spin_flag();		//今超信地旋回しているかどうか
	static void set_spin_flag(bool is_spin);

	static void interrupt();	//割り込み関数内で実行するよう

	static void run_init(bool posture_ctrl, bool wall_ctrl);	//走る直前に実行するやつ

	//壁を見て、壁が存在するなら壁を作り、ないなら壊す。見たことも記録
	//マウスの向きや座標も内部できちんと考える
	static void look_wall(bool comb_ignore);	//壁を見る関数

	//壁があるか確認用の関数	壁がある方向のLEDが光る
	static void velify_wall();

	static void turn_90_dir(const unsigned char right_or_left);
	static void turn_45_dir(bool is_right);
	static void turn_direction_slalom(const SLALOM_TYPE slalom_type, const unsigned char right_or_left);

	static void error();	//フェイルセーフとか、かかった時に、ここに飛びますよ

	~mouse();

};

//毎回書くのめんどくさいので、変数用意しとく
const static int photo_R = static_cast<int>(PHOTO_TYPE::right);
const static int photo_L = static_cast<int>(PHOTO_TYPE::left);


class run {
private:
	run();
public:
	static const std::array<float, static_cast<int>(PHOTO_TYPE::element_count)> WALLEAGE_BODOR;
	static const std::array<float, static_cast<int>(PHOTO_TYPE::element_count)> WALLEAGE_BODOR_OBLI;
	static const std::array<float, static_cast<int>(PHOTO_TYPE::element_count)> DOWN_WALLEAGE_DISTANCE;
	static const std::array<float, static_cast<int>(PHOTO_TYPE::element_count)> DOWN_WALLEAGE_OBLI;

public:
	static void accel_run(float distance_m, float end_velocity,
				unsigned char select_mode);
	static bool wall_edge_run_for_search(const float distance_m,
			const float end_velocity, const unsigned char select_mode,
			const float check_distance);		//探索用
	static void wall_edge_run_for_slalom(float distance_m,
			float end_velocity, uint8_t select_mode, bool is_right, bool is_obli, bool run_to_edge);	//最短の大廻スラロームの前距離用  distance_mは区画の中心からどれくらい進むか,is_obliは今斜め走行中か，run_to_edgeは壁キレ見るまで走り続けるか
	static void wall_edge_run_for_obli(float distance_m,
			float end_velocity, uint8_t select_mode, bool run_to_edge);	//最短の大廻スラロームの前距離用  distance_mは区画の中心からどれくらい進むか,run_to_edgeは壁キレ見るまで走り続けるか
	static void path_accel_run_wall_edge(float distance_m,
				float end_v, COORDINATE init, uint8_t select, bool is_obli);	//最短用の走行関数　壁キレを読んだら相対角度を補正する　最後だけ読むとかでなく、走行中ずっと読む

	static void accel_run_by_distance(float tar_L_m, float end_velocity,
			COORDINATE init, uint8_t select_mode);	//割り込みの積算距離ではなく、初期座標と現在座標の間の距離を考える
	static void accel_run_by_place(COORDINATE finish, float end_velocity,
				uint8_t select_mode);	//絶対座標を基準に走る。 現在座標と目標座標の距離で考える


	static void fit_run(const unsigned char select_mode);//前壁に対してうまく合うように調整して止まる

	static void slalom(const SLALOM_TYPE slalom_type,
			const signed char right_or_left, const uint8_t select_mode);
	//探索用のスラローム。
	static void slalom_for_search(SLALOM_TYPE slalom_type,
			signed char right_or_left, uint8_t select_mode);
	static void spin_turn(const float target_degree);

	static void path(const float finish_velocity, const uint8_t _straight, const uint8_t _curve);

	~run();

};

//ACTION_TYPE 足立法のとき次に取る行動の種類
typedef enum {
	go_straight, turn_right, turn_left, back, stop
} ACTION_TYPE;

class adachi {
private:
	static signed char direction_x, direction_y;

	//現在の座標と向きを与えると歩数的にそのマスに進めるかを判別
	static bool check_move_by_step(unsigned char target_x,
			unsigned char target_y, unsigned char muki);

	//目標のマスのまだ見てない壁の数を数え上げる
	static unsigned int count_unknown_wall(unsigned char target_x,
			unsigned char target_y);

	//引数に応じて次の行動をマウスが実行する（実際に動く部分）
	static void run_next_action(const ACTION_TYPE next_action, bool slalom);
	static void simulate_next_action(ACTION_TYPE next_action);//機体は動かない。仮想的に変数とか更新。デバック用

	//次行く方向と今の向きを与えると、次に取る行動を返す。優先度は、直進、右ターン、左ターン、バックの順
	static ACTION_TYPE get_next_action(DIRECTION next_direction, uint8_t now_muki);
	static ACTION_TYPE get_next_action(compas next, compas now);

public:
	static bool adachi_method(const unsigned char target_x,
			const unsigned char target_y, bool is_FULUKAWA);
	//static bool adachi_method_spin(unsigned char target_x,unsigned char target_y, bool is_FULUKAWA);
	//static bool left_hand_method(const uint8_t target_x,const uint8_t target_y);


	static bool node_adachi(std::vector< std::pair<uint8_t, uint8_t> > finish, weight_algo method);		//ノード型歩数マップで足立法

	adachi();
	~adachi();

};


#endif /* RUN_H_ */
