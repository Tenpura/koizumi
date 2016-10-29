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
//#include"map.h"

//position
typedef union {
	unsigned char x :4;
	unsigned char y :4;
} POSITION;

class mouse {
private:
	static float ideal_acceleration;			//マウスの加速度[m/s^2]
	static float ideal_angular_acceleration;//マウスの加角速度[rad/s^2]

	static float ideal_velocity;//マウスの目標速度[m/s]
	static float ideal_angular_velocity;//マウスの目標角速度[rad/s]

	//理想値から計算した距離と角度
	static float ideal_distance;
	static float ideal_angle;

	static float run_distance;//マウスの走行距離[m]

	static unsigned long mouse_count_ms;//マウスの時間[msec].基本リセットしない

	static bool fail_flag;		//フェイルセーフがかかるとこのフラグがTRUEに

	static POSITION position;//マウスの位置（座標）
	static unsigned char mouse_direction;//マウスの向き

	static void cal_velocity();//加速を行う。速度の加減算
	static void cal_distance();//距離計算


	mouse();

public:

	static MAP_DATA now_map;

	static void reset_count();
	static void add_one_count_ms();//カウントに1加算。割り込み内のみで呼び出す
	static unsigned long get_count_ms();//カウント取得。単位はms

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

	static float get_distance_m();//距離を取得
	static void set_distance_m(const float set_value_m);//距離をセット

	static unsigned char get_x_position();
	static unsigned char get_y_position();
	static void set_position(const unsigned char x, const unsigned char y);

	static unsigned char get_direction();	//defineされたMUKI_??で返す
	static void get_direction(signed char *direction_x, signed char *direction_y);		//引数の値をポインタ経由で変更する
	static void set_direction(const unsigned char muki);
	static void set_direction(const signed char direction_x, const signed char direction_y);


	static bool get_fail_flag();		//フェイルセーフがかかったかどうかの判別用
	static void set_fail_flag(bool set_flag);

	static void interrupt();	//


	static void error();	//フェイルセーフとか、かかった時に、ここに飛びますよ

	~mouse();

};


class run {
private:
	run();

public:
	static void accel_run(const float distance_m, const float end_velocity, const unsigned char select_mode);
	static void slalom_for_path(const signed char right_or_left, const unsigned char select_mode);
	static void spin_turn(const float target_degree);
	~run();

};


#endif /* RUN_H_ */
