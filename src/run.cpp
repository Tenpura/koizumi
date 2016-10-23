/*
 * run.cpp
 *
 *  Created on: 2016/10/23
 *      Author: Koizumi
 */

#include"run.h"

float mouse::ideal_acceleration, mouse::ideal_angular_acceleration;
float mouse::ideal_velocity, mouse::ideal_angular_velocity;
float mouse::run_distance;
unsigned long mouse::mouse_count_ms;

MAP_DATA mouse::now_map;

POSITION mouse::position;
unsigned char mouse::mouse_direction;

bool mouse::fail_flag = false;

void mouse::reset_count() {
	mouse_count_ms = 0;
}

void mouse::add_one_count_ms() {
	mouse_count_ms = mouse_count_ms + 1;
}

unsigned long mouse::get_count_ms() {
	return mouse_count_ms;
}

void mouse::set_acceleration(const float set_value_m_ss) {
	ideal_acceleration = set_value_m_ss;
}

float mouse::get_acceleration() {
	return ideal_acceleration;	//m/s^2
}

void mouse::set_angular_acceleration(const float set_value_m_ss) {
	ideal_angular_acceleration = set_value_m_ss;
}

float mouse::get_angular_acceleration() {
	return ideal_angular_acceleration;	//m/s^2
}

void mouse::set_ideal_velocity(const float set_value_m_s) {
	ideal_velocity = set_value_m_s;
}

float mouse::get_ideal_velocity() {
	return ideal_velocity;
}

void mouse::set_ideal_angular_velocity(const float set_value_rad_s) {
	ideal_angular_velocity = set_value_rad_s;
}


void mouse::set_ideal(const float accel, const float vel, const float dis){
	set_acceleration(accel);
	set_ideal_velocity(vel);
	set_distance_m(dis);
}
void mouse::set_ideal_ang(const float ang_a, const float ang_omega){
	set_angular_acceleration(ang_a);
	set_ideal_angular_velocity(ang_omega);
}

float mouse::get_ideal_angular_velocity() {
	return ideal_angular_velocity;
}

void mouse::reset_angle() {
	gyro::reset_angle();
	mouse::reset_count();		//最小二乗法の補正ためカウントをリセット
}

float mouse::get_angle_degree() {
	return gyro::get_angle();
}

float mouse::get_distance_m() {
	return run_distance;
}

void mouse::set_distance_m(const float set_value_m) {
	run_distance = set_value_m;
}

unsigned char mouse::get_x_position() {
	return position.x;
}

unsigned char mouse::get_y_position() {
	return position.y;
}

void mouse::set_position(const unsigned char x, const unsigned char y) {
	position.x = x;
	position.y = y;
}

unsigned char mouse::get_direction() {
	return mouse_direction;
}

void mouse::get_direction(signed char *direction_x, signed char *direction_y) {
	switch (mouse_direction) {
	case MUKI_RIGHT:
		*direction_x = 1;
		*direction_y = 0;
		break;

	case MUKI_LEFT:
		*direction_x = -1;
		*direction_y = 0;
		break;

	case MUKI_UP:
		*direction_x = 0;
		*direction_y = 1;
		break;

	case MUKI_DOWN:
		*direction_x = 0;
		*direction_y = -1;
		break;
	}
}

void mouse::set_direction(const unsigned char muki) {
	mouse_direction = muki;
}

void mouse::set_direction(const signed char direction_x,
		const signed char direction_y) {
	switch (direction_x) {
	case 1:
		mouse_direction = MUKI_RIGHT;
		break;

	case -1:
		mouse_direction = MUKI_LEFT;
		break;

	case 0:
		if (direction_y == 1) {
			mouse_direction = MUKI_UP;
		} else {
			mouse_direction = MUKI_DOWN;
		}
		break;
	}
}

bool mouse::get_fail_flag(){
	return fail_flag;
}

void mouse::set_fail_flag(bool set_flag){
	fail_flag = set_flag;
}

void mouse::cal_accel() {
	//（速度+=加速度）を制御にぶち込む
	set_ideal_velocity(get_ideal_velocity() + get_acceleration() * CONTORL_PERIOD);
	//（角速度+=加角速度）を制御にぶち込む
	set_ideal_angular_velocity(
			get_ideal_angular_velocity() + get_angular_acceleration() * CONTORL_PERIOD);
}

void mouse::cal_distance() {
	run_distance += get_ideal_velocity() * CONTORL_PERIOD;
}

void mouse::error(){
	//TODO エラー処理は必要に応じて書くこと
}

mouse::mouse() {
}

mouse::~mouse() {

}

void run::accel_run(const float distance_m, const float end_velocity,
		const unsigned char select_mode) {

	float max_velocity = parameter::get_run_max_velocity(select_mode);
	float accel_value = ABS(parameter::get_run_acceleration(select_mode));
	float de_accel_value = ABS(parameter::get_run_de_acceleration(select_mode));

	float de_accel_distance = ABS(
			mouse::get_ideal_velocity() * mouse::get_ideal_velocity()
			- end_velocity * end_velocity) / (2 * de_accel_value);	//減速に必要な距離

	//加速
	mouse::set_acceleration(accel_value);
	while (mouse::get_ideal_velocity() < max_velocity) {
		//現在速度から減速にかかる距離を計算
		de_accel_distance = ABS(
				mouse::get_ideal_velocity() * mouse::get_ideal_velocity()
				- end_velocity * end_velocity) / (2 * de_accel_value);

		//減速に距離が必要な距離が足りなくなったら抜ける
		if (de_accel_distance >= distance_m - mouse::get_distance_m()) {
			break;
		}
	}

	//等速
	mouse::set_acceleration(0);
	while (1) {
		//現在速度から減速にかかる距離を計算
		de_accel_distance = ABS(
				mouse::get_ideal_velocity() * mouse::get_ideal_velocity()
				- end_velocity * end_velocity) / (2 * de_accel_value);

		//減速に距離が必要な距離が足りなくなったら抜ける
		if (de_accel_distance >= distance_m - mouse::get_distance_m()) {
			break;
		}
	}

	//減速
	mouse::set_acceleration(-de_accel_value);
	while (mouse::get_ideal_velocity() > end_velocity) {
		//速度より先に距離がなくなったら抜ける
		if (distance_m < mouse::get_distance_m()) {
			break;
		}
	}
	mouse::set_acceleration(0);
	mouse::set_ideal_velocity(end_velocity);

	//速度0だとここに閉じ込められてしまう
	if (end_velocity > 0) {
		//もし速度が先に無くなっても、最後まで走りきるよう
		while (distance_m < mouse::get_distance_m()) {
		}
	}

	mouse::set_distance_m(0);
}

//TODO 実装テストはまだ。とりあえず書いただけ
void run::slalom_for_path(const signed char right_or_left,
		const unsigned char select_mode) {
	float distance = parameter::get_slalom_para(before_distance, right_or_left,
			select_mode);
	float slalom_velocity = parameter::get_slalom_para(velocity, right_or_left,
			select_mode);
	float angular_acceleration = ABS(
			parameter::get_slalom_para(angular_accel, right_or_left,
					select_mode));
	float angle_degree = 0;

	//前距離の分走る
	mouse::set_distance_m(0);
	accel_run(distance, slalom_velocity, select_mode);

	control::stop_wall_control();
	//時計回りが正
	if (right_or_left == MUKI_LEFT) {
		angular_acceleration = -ABS(angular_acceleration);
	}
	gyro::reset_angle();
	mouse::set_ideal_angular_velocity(0);

	//角加速区間
	mouse::set_angular_acceleration(angular_acceleration);
	angle_degree = parameter::get_slalom_para(clothoid_angle, right_or_left,
			select_mode);
	while (ABS(gyro::get_angle()) < angle_degree) {
	}

	//等角速度
	mouse::set_angular_acceleration(0);
	angle_degree = parameter::get_slalom_para(target_angle, right_or_left,
			select_mode) - angle_degree;
	while (ABS(gyro::get_angle()) < angle_degree) {
	}

	//角減速区間
	mouse::set_angular_acceleration(-angular_acceleration);
	angle_degree = parameter::get_slalom_para(target_angle, right_or_left,
			select_mode);
	while (ABS(gyro::get_angle()) < angle_degree) {
	}

	mouse::set_angular_acceleration(0);
	mouse::set_ideal_angular_velocity(0);

	//後ろ距離分走る
	control::start_wall_control();
	mouse::set_distance_m(0);
	distance = parameter::get_slalom_para(after_distance, right_or_left,
			select_mode);
	accel_run(distance, slalom_velocity, select_mode);

	mouse::set_distance_m(0);
}

void run::spin_turn(const float target_degree) {
	const static float max_angular_velocity = 2.0;	//rad/s
	float angular_acceleration = 2.0;				//rad/s^2
	float angle_degree = 0;

	control::stop_wall_control();

	//時計回りが正
	if (target_degree < 0) {
		angular_acceleration = -ABS(angular_acceleration);
	}

	mouse::reset_angle();
	mouse::set_ideal_angular_velocity(0);

	//角加速区間
	mouse::set_angular_acceleration(angular_acceleration);
	while (ABS(mouse::get_ideal_angular_velocity()) < max_angular_velocity) {
		//減速に必要な角度を計算
		angle_degree = degree(
				(mouse::get_ideal_angular_velocity()
						* mouse::get_ideal_angular_velocity())
						/ (2 * angular_acceleration));
		//減速に必要な角度が残ってなければ抜ける
		if (angle_degree >= (target_degree - mouse::get_angle_degree())) {
			break;
		}
	}

	//等角速度区間
	mouse::set_angular_acceleration(0);
	angle_degree = target_degree - angle_degree;
	while (1) {
		//減速に必要な角度を計算
		angle_degree = degree(
				(mouse::get_ideal_angular_velocity()
						* mouse::get_ideal_angular_velocity())
						/ (2 * angular_acceleration));
		//減速に必要な角度が残ってなければ抜ける
		if (angle_degree >= (target_degree - mouse::get_angle_degree())) {
			break;
		}
	}

	//角減速区間
	mouse::set_angular_acceleration(-angular_acceleration);
	while (ABS(mouse::get_angle_degree()) < ABS(target_degree)) {
		//この条件付けないと、先に角速度が0になった場合いつまでたってもループを抜けない
		if (ABS(mouse::get_ideal_angular_velocity()) < 0.02) {
			mouse::set_angular_acceleration(0);
		}
	}

	mouse::set_angular_acceleration(0);
	mouse::set_ideal_angular_velocity(0);
	mouse::set_distance_m(0);

	control::start_wall_control();
}

run::run() {
}

run::~run() {
}

