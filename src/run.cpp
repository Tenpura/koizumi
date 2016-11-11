/*
 * run.cpp
 *
 *  Created on: 2016/10/23
 *      Author: Koizumi
 */

#include"run.h"

float mouse::ideal_acceleration, mouse::ideal_angular_acceleration;
float mouse::ideal_velocity, mouse::ideal_angular_velocity, mouse::ideal_angle,
		mouse::ideal_distance;
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

void mouse::set_ideal(const float accel, const float vel, const float dis) {
	set_acceleration(accel);
	set_ideal_velocity(vel);
	set_distance_m(dis);
}
void mouse::set_ideal_ang(const float ang_a, const float ang_omega) {
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
	return degree(gyro::get_angle());
}

float mouse::get_ideal_angle_degree() {
	return degree(ideal_angle);
}

float mouse::get_distance_m() {
	return run_distance;
}

void mouse::set_distance_m(const float set_value_m) {
	run_distance = set_value_m;
}

unsigned char mouse::get_x_position() {
	return position.bit.x;
}

unsigned char mouse::get_y_position() {
	return position.bit.y;
}

void mouse::set_position(const uint8_t set_x, const uint8_t set_y) {
	position.bit.y = set_y;
	position.bit.x = set_x;

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

bool mouse::get_fail_flag() {
	return fail_flag;
}

void mouse::set_fail_flag(bool set_flag) {
	fail_flag = set_flag;
}

void mouse::cal_velocity() {
	//（速度+=加速度）を制御にぶち込む
	set_ideal_velocity(
			get_ideal_velocity() + get_acceleration() * CONTORL_PERIOD);
	//（角速度+=加角速度）を制御にぶち込む
	set_ideal_angular_velocity(
			get_ideal_angular_velocity() + get_angular_acceleration() * CONTORL_PERIOD);
}

void mouse::cal_distance() {
	run_distance += get_ideal_velocity() * CONTORL_PERIOD;
	ideal_distance += get_ideal_velocity() * CONTORL_PERIOD;
}

void mouse::interrupt() {
	//速度と距離を計算
	mouse::cal_velocity();
	mouse::cal_distance();
	ideal_angle += get_ideal_angular_velocity() * CONTORL_PERIOD;

}

void mouse::run_init(bool posture_ctrl, bool wall_ctrl) {

	motor::sleep_motor();

	//制御を切る
	control::stop_wall_control();
	control::stop_control();

	//フェイルセーフを初期化
	mouse::set_fail_flag(false);

	accelmeter::set_accel_ref();
	gyro::set_gyro_ref();
	mouse::reset_angle();
	mouse::set_distance_m(0);
	mouse::set_ideal_velocity(0);
	mouse::set_ideal_angular_velocity(0);
	control::reset_delta();

	if (posture_ctrl)
		control::start_control();
	if (wall_ctrl)
		control::start_wall_control();

	motor::stanby_motor();

}

void mouse::look_wall(bool comb_ignore) {
	//壁を見て、壁が存在するなら壁を作り、ないなら壊す。見たことも記録
	//マウスの向きや座標も内部できちんと考える

	signed char direction_x, direction_y;
	mouse::get_direction(&direction_x, &direction_y);

	switch (mouse_direction) {
	case MUKI_UP:
		//壁情報を更新
		//マウスから見て右
		map::remember_exist(get_x_position(), get_y_position(), MUKI_RIGHT);//壁を見たことを記録
		if (photo::check_wall(MUKI_RIGHT)) {
			map::create_wall(get_x_position(), get_y_position(), MUKI_RIGHT);
		} else {
			map::destroy_wall(get_x_position(), get_y_position(), MUKI_RIGHT);

			//櫛無視するなら
			if (comb_ignore) {
				//既に見ていて壁がないなら
				if (map::check_exist(get_x_position() - direction_x,
						get_y_position() - direction_y,
						MUKI_RIGHT)) {
					if (map::get_wall(get_x_position() - direction_x,
							get_y_position() - direction_y,
							MUKI_RIGHT) == false) {
						//ルール的に壁があるはず
						map::create_wall(get_x_position() + 1, get_y_position(),
						MUKI_DOWN);
						map::remember_exist(get_x_position() + 1,
								get_y_position(),
								MUKI_DOWN);		//壁を見たことを記録
					}
				}
			}
		}
		//マウスから見て前
		map::remember_exist(get_x_position(), get_y_position(), MUKI_UP); //壁を見たことを記録
		if (photo::check_wall(MUKI_UP)) {
			map::create_wall(get_x_position(), get_y_position(), MUKI_UP);
		} else {
			map::destroy_wall(get_x_position(), get_y_position(), MUKI_UP);
		}
		//マウスから見て左
		map::remember_exist(get_x_position(), get_y_position(), MUKI_LEFT);	//壁を見たことを記録
		if (photo::check_wall(MUKI_LEFT)) {
			map::create_wall(get_x_position(), get_y_position(), MUKI_LEFT);
		} else {
			map::destroy_wall(get_x_position(), get_y_position(), MUKI_LEFT);

			//櫛無視するなら
			if (comb_ignore) {
				//既に見ていて壁がないなら
				if (map::check_exist(get_x_position() - direction_x,
						get_y_position() - direction_y,
						MUKI_LEFT)) {
					if (map::get_wall(get_x_position() - direction_x,
							get_y_position() - direction_y,
							MUKI_LEFT) == false) {
						//ルール的に壁があるはず
						map::create_wall(get_x_position() - 1, get_y_position(),
						MUKI_DOWN);
						map::remember_exist(get_x_position() - 1,
								get_y_position(),
								MUKI_DOWN);	//壁を見たことを記録
					}
				}
			}

		}

		break;

	case MUKI_RIGHT:
		//壁情報を更新
		//マウスから見て右
		map::remember_exist(get_x_position(), get_y_position(), MUKI_DOWN);	//壁を見たことを記録
		if (photo::check_wall(MUKI_RIGHT)) {
			map::create_wall(get_x_position(), get_y_position(), MUKI_DOWN);
		} else {
			map::destroy_wall(get_x_position(), get_y_position(), MUKI_DOWN);

			//櫛無視するなら
			if (comb_ignore) {
				//既に見ていて壁がないなら
				if (map::check_exist(get_x_position() - direction_x,
						get_y_position() - direction_y,
						MUKI_DOWN)) {
					if (map::get_wall(get_x_position() - direction_x,
							get_y_position() - direction_y,
							MUKI_DOWN) == false) {
						//ルール的に壁があるはず
						map::create_wall(get_x_position(), get_y_position() - 1,
						MUKI_LEFT);
						map::remember_exist(get_x_position(),
								get_y_position() - 1,
								MUKI_LEFT);	//壁を見たことを記録
					}
				}
			}

		}
		//マウスから見て前
		map::remember_exist(get_x_position(), get_y_position(), MUKI_RIGHT);//壁を見たことを記録
		if (photo::check_wall(MUKI_UP)) {
			map::create_wall(get_x_position(), get_y_position(), MUKI_RIGHT);
		} else {
			map::destroy_wall(get_x_position(), get_y_position(), MUKI_RIGHT);
		}
		//マウスから見て左
		map::remember_exist(get_x_position(), get_y_position(), MUKI_UP);//壁を見たことを記録
		if (photo::check_wall(MUKI_LEFT)) {
			map::create_wall(get_x_position(), get_y_position(), MUKI_UP);
		} else {
			map::destroy_wall(get_x_position(), get_y_position(), MUKI_UP);
			//櫛無視するなら
			if (comb_ignore) {
				//既に見ていて壁がないなら
				if (map::check_exist(get_x_position() - direction_x,
						get_y_position() - direction_y,
						MUKI_UP)) {
					if (map::get_wall(get_x_position() - direction_x,
							get_y_position() - direction_y,
							MUKI_UP) == false) {
						//ルール的に壁があるはず
						map::create_wall(get_x_position(), get_y_position() + 1,
						MUKI_LEFT);
						map::remember_exist(get_x_position(),
								get_y_position() + 1,
								MUKI_LEFT);	//壁を見たことを記録
					}
				}
			}

		}

		break;

	case MUKI_LEFT:
		//壁情報を更新
		//マウスから見て右
		map::remember_exist(get_x_position(), get_y_position(), MUKI_UP);//壁を見たことを記録
		if (photo::check_wall(MUKI_RIGHT)) {
			map::create_wall(get_x_position(), get_y_position(), MUKI_UP);
		} else {
			map::destroy_wall(get_x_position(), get_y_position(), MUKI_UP);

			//櫛無視するなら
			if (comb_ignore) {
				//既に見ていて壁がないなら
				if (map::check_exist(get_x_position() - direction_x,
						get_y_position() - direction_y,
						MUKI_UP)) {
					if (map::get_wall(get_x_position() - direction_x,
							get_y_position() - direction_y,
							MUKI_UP) == false) {
						//ルール的に壁があるはず
						map::create_wall(get_x_position(), get_y_position() + 1,
						MUKI_RIGHT);
						map::remember_exist(get_x_position(),
								get_y_position() + 1,
								MUKI_RIGHT);	//壁を見たことを記録
					}
				}
			}

		}
		//マウスから見て前
		map::remember_exist(get_x_position(), get_y_position(), MUKI_LEFT);	//壁を見たことを記録
		if (photo::check_wall(MUKI_UP)) {
			map::create_wall(get_x_position(), get_y_position(), MUKI_LEFT);
		} else {
			map::destroy_wall(get_x_position(), get_y_position(), MUKI_LEFT);
		}
		//マウスから見て左
		map::remember_exist(get_x_position(), get_y_position(), MUKI_DOWN);	//壁を見たことを記録
		if (photo::check_wall(MUKI_LEFT)) {
			map::create_wall(get_x_position(), get_y_position(), MUKI_DOWN);
		} else {
			map::destroy_wall(get_x_position(), get_y_position(), MUKI_DOWN);

			//櫛無視するなら
			if (comb_ignore) {
				//既に見ていて壁がないなら
				if (map::check_exist(get_x_position() - direction_x,
						get_y_position() - direction_y,
						MUKI_DOWN)) {
					if (map::get_wall(get_x_position() - direction_x,
							get_y_position() - direction_y,
							MUKI_DOWN) == false) {
						//ルール的に壁があるはず
						map::create_wall(get_x_position(), get_y_position() - 1,
						MUKI_RIGHT);
						map::remember_exist(get_x_position(),
								get_y_position() - 1,
								MUKI_RIGHT);	//壁を見たことを記録
					}
				}
			}

		}

		break;

	case MUKI_DOWN:
		//壁情報を更新
		//マウスから見て右
		map::remember_exist(get_x_position(), get_y_position(), MUKI_LEFT);	//壁を見たことを記録
		if (photo::check_wall(MUKI_RIGHT)) {
			map::create_wall(get_x_position(), get_y_position(), MUKI_LEFT);
		} else {
			map::destroy_wall(get_x_position(), get_y_position(), MUKI_LEFT);

			//櫛無視するなら
			if (comb_ignore) {
				//既に見ていて壁がないなら
				if (map::check_exist(get_x_position() - direction_x,
						get_y_position() - direction_y,
						MUKI_LEFT)) {
					if (map::get_wall(get_x_position() - direction_x,
							get_y_position() - direction_y,
							MUKI_LEFT) == false) {
						//ルール的に壁があるはず
						map::create_wall(get_x_position() - 1, get_y_position(),
						MUKI_UP);
						map::remember_exist(get_x_position() - 1,
								get_y_position(),
								MUKI_UP);	//壁を見たことを記録
					}
				}
			}

		}
		//マウスから見て前
		map::remember_exist(get_x_position(), get_y_position(), MUKI_DOWN);	//壁を見たことを記録
		if (photo::check_wall(MUKI_UP)) {
			map::create_wall(get_x_position(), get_y_position(), MUKI_DOWN);
		} else {
			map::destroy_wall(get_x_position(), get_y_position(), MUKI_DOWN);
		}
		//マウスから見て左
		map::remember_exist(get_x_position(), get_y_position(), MUKI_RIGHT);//壁を見たことを記録
		if (photo::check_wall(MUKI_LEFT)) {
			map::create_wall(get_x_position(), get_y_position(), MUKI_RIGHT);
		} else {
			map::destroy_wall(get_x_position(), get_y_position(), MUKI_RIGHT);

			//櫛無視するなら
			if (comb_ignore) {
				//既に見ていて壁がないなら
				if (map::check_exist(get_x_position() - direction_x,
						get_y_position() - direction_y,
						MUKI_RIGHT)) {
					if (map::get_wall(get_x_position() - direction_x,
							get_y_position() - direction_y,
							MUKI_RIGHT) == false) {
						//ルール的に壁があるはず
						map::create_wall(get_x_position() + 1, get_y_position(),
						MUKI_UP);
						map::remember_exist(get_x_position() + 1,
								get_y_position(),
								MUKI_UP);	//壁を見たことを記録
					}
				}
			}
		}

		break;

	}

}

void mouse::velify_wall(){
	my7seg::turn_off();
	if(photo::check_wall(front)) my7seg::light(my7seg::front);
	if(photo::check_wall(right)) my7seg::light(my7seg::right);
	if(photo::check_wall(left)) my7seg::light(my7seg::left);

}

void mouse::error() {
	//TODO エラー処理は必要に応じて書くこと
	while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 1) {
		my7seg::light_error();
		wait::ms(500);
		my7seg::turn_off();
		wait::ms(500);
	}

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
		while (distance_m > mouse::get_distance_m()) {
		}
	}

	mouse::set_distance_m(0);
}

void run::slalom(const SLALOM_TYPE slalom_type,
		const signed char right_or_left, const unsigned char select_mode) {
	//スラロームのパラメーター取得
	float distance = parameter::get_slalom(slalom_type, before_distance,
			right_or_left, select_mode);
	float slalom_velocity = parameter::get_slalom(slalom_type, velocity,
			right_or_left, select_mode);
	float angular_acceleration = parameter::get_slalom(slalom_type,
			angular_accel, right_or_left, select_mode);
	float target_angle_degree = parameter::get_slalom(slalom_type, target_angle,
			right_or_left, select_mode);
	float clothoid_angle_degree = parameter::get_slalom(slalom_type,
			clothoid_angle, right_or_left, select_mode);
	float max_angular = parameter::get_slalom(slalom_type, max_angular_velocity,
			right_or_left, select_mode);
	float de_accel_angle = 0;

	bool wall_flag = control::get_wall_control_phase();

	if (slalom_type == none) {
		return ;
	}

	gyro::reset_angle();
	control::reset_delta(sen_gyro);

//前距離の分走る
	mouse::set_distance_m(0);
	accel_run(distance, slalom_velocity, select_mode);

	//mouse::slalom_flag = true;
	control::stop_wall_control();

//時計回りが正
	if (right_or_left == MUKI_LEFT) {
		angular_acceleration = -ABS(angular_acceleration);
		max_angular = -ABS(max_angular);
	}
	mouse::set_ideal_angular_velocity(0);

//角加速区間
	mouse::set_angular_acceleration(angular_acceleration);
	while (ABS(gyro::get_angle()) < clothoid_angle_degree) {
//フェイルセーフが掛かっていればそこで抜ける
		if (mouse::get_fail_flag()) {
			return ;
		}
		//最大角速度に達したら終了
		if (ABS(mouse::get_ideal_angular_velocity()) > ABS(max_angular)) {
			mouse::set_ideal_angular_velocity(max_angular);
			break;
		}
	}

	//減速時にも同様の角度がずれると予想されるから
	//追従遅れで生じた加速区間の角度の理想と現実の差を記録しておく
	float def_angle = (clothoid_angle_degree - ABS(degree(gyro::get_angle())));

//等角速度
	mouse::set_angular_acceleration(0);

	while (ABS(gyro::get_angle())
			< (target_angle_degree - clothoid_angle_degree)) {
//フェイルセーフが掛かっていればそこで抜ける
		if (mouse::get_fail_flag()) {
			return ;
		}

		de_accel_angle = degree(
		//(gyro::get_angular_velocity() * gyro::get_angular_velocity())
				(mouse::get_ideal_angular_velocity()
						* mouse::get_ideal_angular_velocity())
						/ (2 * angular_acceleration));

//減速に必要な角度が残ってなければ抜ける
		//追従遅れのために減速には余分な角度が必要なはず
		if ((ABS(de_accel_angle) + def_angle)
				>= (target_angle_degree - ABS(mouse::get_angle_degree()))) {
			break;
		}

	}

//角減速区間
	mouse::set_angular_acceleration(-angular_acceleration);
	while (ABS(gyro::get_angle()) < target_angle_degree) {
		if (ABS(mouse::get_ideal_angular_velocity()) < 0.2) {
			mouse::set_angular_acceleration(0);
			if (right_or_left == MUKI_RIGHT) {
				mouse::set_ideal_angular_velocity(0.2);
			} else {
				mouse::set_ideal_angular_velocity(-0.2);
			}
			break;
		}

//フェイルセーフが掛かっていればそこで抜ける
		if (mouse::get_fail_flag()) {
			return ;
		}
	}

	mouse::set_angular_acceleration(0);
	mouse::set_ideal_angular_velocity(0);

//後ろ距離分走る
	if (wall_flag)
		control::start_wall_control();	//もともと壁制御がかかってたら復活させる

	mouse::set_distance_m(0);
	distance = parameter::get_slalom((slalom_type), after_distance,
			right_or_left, select_mode);
	accel_run(distance, slalom_velocity, select_mode);

	//mouse::slalom_flag = false;
	//gyro::reset_angle();
	control::reset_delta(sen_gyro);


}

void run::spin_turn(const float target_degree) {
	const static float max_angular_velocity = 2.0;	//rad/s
	float angular_acceleration = 2.0;				//rad/s^2
	float angle_degree = 0;
	bool wall_flag = control::get_wall_control_phase();

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

	//もともと壁制御かかってたなら復活させる
	if (wall_flag)
		control::start_wall_control();
}

run::run() {
}

run::~run() {
}

signed char adachi::direction_x, adachi::direction_y;

void adachi::set_direction() {
	unsigned char direction = mouse::get_direction();

	switch (direction) {
	case MUKI_RIGHT:
		direction_x = 1;
		direction_y = 0;
		break;

	case MUKI_LEFT:
		direction_x = -1;
		direction_y = 0;
		break;

	case MUKI_UP:
		direction_x = 0;
		direction_y = 1;
		break;

	case MUKI_DOWN:
		direction_x = 0;
		direction_y = -1;
		break;
	}

}

bool adachi::check_move_by_step(unsigned char target_x, unsigned char target_y,
		unsigned char muki) {
	signed char muki_x, muki_y;

	switch (muki) {
	case MUKI_RIGHT:
		//迷路外ならfalseを返す
		if ((target_x + 1) >= MAZE_SIZE) {
			return false;
		}
		muki_x = 1;
		muki_y = 0;
		break;

	case MUKI_LEFT:
		//迷路外ならfalseを返す
		if ((target_x - 1) < 0) {
			return false;
		}
		muki_x = -1;
		muki_y = 0;
		break;

	case MUKI_UP:
		//迷路外ならfalseを返す
		if ((target_y + 1) >= MAZE_SIZE) {
			return false;
		}
		muki_x = 0;
		muki_y = 1;
		break;

	case MUKI_DOWN:
		//迷路外ならfalseを返す
		if ((target_y - 1) < 0) {
			return false;
		}
		muki_x = 0;
		muki_y = -1;
		break;
	}

	if (step::get_step((target_x + muki_x), (target_y + muki_y))
			< step::get_step(target_x, target_y)) {			//歩数の小さいほうへ
		if ((map::get_wall(target_x, target_y, muki) == false)) {	//壁がないなら
			return true;
		}
	}

	return false;
}

unsigned int adachi::count_unknown_wall(unsigned char target_x,
		unsigned char target_y) {
	unsigned int unknown_count = 0;

	//各方向について探索済みか調べる.未探索ならカウントアップ
	if ((map::check_exist(target_x, target_y, MUKI_RIGHT)) == false) {
		unknown_count++;
	}
	if ((map::check_exist(target_x, target_y, MUKI_LEFT)) == false) {
		unknown_count++;
	}
	if ((map::check_exist(target_x, target_y, MUKI_UP)) == false) {
		unknown_count++;
	}
	if ((map::check_exist(target_x, target_y, MUKI_DOWN)) == false) {
		unknown_count++;
	}

	return unknown_count;
}

void adachi::run_next_action(ACTION_TYPE next_action) {
	switch (next_action) {
	case go_straight:
		//1区間直進
		run::accel_run((0.09 * MOUSE_MODE), SEARCH_VELOCITY, 0);
		break;

	case turn_right:
		//スラローム
		run::slalom(small,MUKI_RIGHT,0);
		direction_turn(&direction_x, &direction_y, MUKI_RIGHT);	//向きを90°変える
		break;

	case turn_left:
		//スラローム
		run::slalom(small,MUKI_LEFT,0);
		direction_turn(&direction_x, &direction_y, MUKI_LEFT);	//向きを90°変える
		break;

	case back:
		//半区間進んで180°ターンして半区間直進
		run::accel_run((0.045 * MOUSE_MODE), 0, 0);			//半区間直進
		run::spin_turn(180);
		direction_turn(&direction_x, &direction_y, MUKI_RIGHT);	//向きを90°変える
		direction_turn(&direction_x, &direction_y, MUKI_RIGHT);	//向きを90°変える
		run::accel_run((0.045 * MOUSE_MODE), SEARCH_VELOCITY, 0);		//半区間直進
		break;

	case stop:
		//半区間進んでストップ
		run::accel_run((0.045 * MOUSE_MODE), 0, 0);			//半区間直進
		//TODO ここでモーターの電源切るべき？
		break;
	}
}

void adachi::run_next_action_by_spin(ACTION_TYPE next_action) {
	switch (next_action) {
	case go_straight:
		//1区間直進
		run::accel_run((0.09 * MOUSE_MODE), SEARCH_VELOCITY, 0);
		break;

	case turn_right:
		//半区間⇒超信地⇒半区間
		run::accel_run((0.045 * MOUSE_MODE), 0, 0);
		run::spin_turn(90);
		run::accel_run((0.045 * MOUSE_MODE), SEARCH_VELOCITY, 0);
		direction_turn(&direction_x, &direction_y, MUKI_RIGHT);	//向きを90°変える
		break;

	case turn_left:
		//半区間⇒超信地⇒半区間
		run::accel_run((0.045 * MOUSE_MODE), 0, 0);
		run::spin_turn(270);
		run::accel_run((0.045 * MOUSE_MODE), SEARCH_VELOCITY, 0);
		direction_turn(&direction_x, &direction_y, MUKI_LEFT);	//向きを90°変える
		break;

	case back:
		//半区間進んで180°ターンして半区間直進
		run::accel_run((0.045 * MOUSE_MODE), 0, 0);			//半区間直進
		run::spin_turn(180);
		direction_turn(&direction_x, &direction_y, MUKI_RIGHT);	//向きを90°変える
		direction_turn(&direction_x, &direction_y, MUKI_RIGHT);	//向きを90°変える
		run::accel_run((0.045 * MOUSE_MODE), SEARCH_VELOCITY, 0);		//半区間直進
		break;

	case stop:
		//半区間進んでストップ
		run::accel_run((0.045 * MOUSE_MODE), 0, 0);			//半区間直進
		//TODO ここでモーターの電源切るべき？
		break;
	}
}


void adachi::simulate_next_action(ACTION_TYPE next_action) {
	switch (next_action) {
	case go_straight:
		//1区間直進
		break;

	case turn_right:
		//半区間⇒超信地⇒半区間
		direction_turn(&direction_x, &direction_y, MUKI_RIGHT);	//向きを90°変える
		break;

	case turn_left:
		//半区間⇒超信地⇒半区間
		direction_turn(&direction_x, &direction_y, MUKI_LEFT);	//向きを90°変える
		break;

	case back:
		//半区間進んで180°ターンして半区間直進
		direction_turn(&direction_x, &direction_y, MUKI_RIGHT);	//向きを90°変える
		direction_turn(&direction_x, &direction_y, MUKI_RIGHT);	//向きを90°変える
		break;

	case stop:
		//半区間進んでストップ
		break;
	}
}

ACTION_TYPE adachi::get_next_action(DIRECTION next_direction,
		uint8_t now_muki) {
	switch (now_muki) {
	case MUKI_RIGHT:
		//真っ直ぐ行けるなら、それを最優先
		if (next_direction.element.right == 1) {
			return go_straight;
		}
		//右のターンを次に優先
		else if (next_direction.element.down == 1) {
			return turn_right;
		}
		//左のターンを次に優先
		else if (next_direction.element.up == 1) {
			return turn_left;
		}
		//Uターンは優先度最低
		else if (next_direction.element.left == 1) {
			return back;
		}
		break;

		//やってることは以下同様なのでコメントは省く
	case MUKI_LEFT:
		if (next_direction.element.left == 1) {
			return go_straight;
		} else if (next_direction.element.up == 1) {
			return turn_right;
		} else if (next_direction.element.down == 1) {
			return turn_left;
		} else if (next_direction.element.right == 1) {
			return back;
		}
		break;

	case MUKI_UP:
		if (next_direction.element.up == 1) {
			return go_straight;
		} else if (next_direction.element.right == 1) {
			return turn_right;
		} else if (next_direction.element.left == 1) {
			return turn_left;
		} else if (next_direction.element.down == 1) {
			return back;
		}
		break;

	case MUKI_DOWN:
		if (next_direction.element.down == 1) {
			return go_straight;
		} else if (next_direction.element.left == 1) {
			return turn_right;
		} else if (next_direction.element.right == 1) {
			return turn_left;
		} else if (next_direction.element.up == 1) {
			return back;
		}
		break;
	}

	//ここにたどり着くのは、次行く方向がないか、予期せぬ例外なので、マウスを止める。
	return stop;
}

bool adachi::adachi_method(unsigned char target_x, unsigned char target_y,
		bool is_FULUKAWA) {
	bool adachi_flag = true;	//途中でミスがあったらfalseに
	unsigned char now_x, now_y;	//座標一時保存用。見易さのため
	DIRECTION next_direction, priority_direction;	//次に行く方向を管理
	unsigned char max_unknown_count, target_unknown_count;	//未探索の壁の数を管理
	ACTION_TYPE next_action;	//次の行動を管理

	my7seg::turn_off();

	//保存していたマップを読みだす
	map::input_map_data(&mouse::now_map);

//向きを取得
	mouse::get_direction(&direction_x, &direction_y);

	mouse::run_init(true, true);

	my7seg::count_down(3, 500);

	run::accel_run((0.045 * MOUSE_MODE), SEARCH_VELOCITY, 0);

	while (adachi_flag) {
//フェイルセーフが掛かっていればそこで抜ける
		if (mouse::get_fail_flag()) {
			adachi_flag = false;
			break;
		}

		my7seg::light(3);

//座標を更新
		now_x = mouse::get_x_position() + direction_x;
		now_y = mouse::get_y_position() + direction_y;
		mouse::set_position(now_x, now_y);

//向きも
		mouse::set_direction(direction_x, direction_y);

//壁情報更新
		mouse::look_wall(false);

//目標の座標にたどり着いたら終了
		if ((now_x == target_x) && (now_y == target_y)) {
			run_next_action(stop);
			break;
		}

//歩数マップ作製
		step::set_step(target_x, target_y);

//方向と未探索の壁の数をリセット
		next_direction.all = 0;
		priority_direction.all = 0;
		max_unknown_count = 1;	//0をはじくため

//歩数的に前後左右のマスへ行けるか判別.
//行ければ次行く方向の候補に入れる
//更に見てない壁の数が多ければpriority_directionの方にも候補として追加
		if (check_move_by_step(now_x, now_y, MUKI_RIGHT)) {			//右
			next_direction.element.right = 1;

			target_unknown_count = count_unknown_wall((now_x + 1), now_y);
			if (target_unknown_count == max_unknown_count) {
				priority_direction.element.right = 1;
			} else if (target_unknown_count > max_unknown_count) {
				max_unknown_count = target_unknown_count;
				priority_direction.all = 0;				//他の方向はいらないのでリセット
				priority_direction.element.right = 1;
			}

		}
		if (check_move_by_step(now_x, now_y, MUKI_LEFT)) {			//左

			next_direction.element.left = 1;

			target_unknown_count = count_unknown_wall((now_x - 1), now_y);
			if (target_unknown_count == max_unknown_count) {
				priority_direction.element.left = 1;
			} else if (target_unknown_count > max_unknown_count) {
				max_unknown_count = target_unknown_count;
				priority_direction.all = 0;				//他の方向はいらないのでリセット
				priority_direction.element.left = 1;
			}

		}
		if (check_move_by_step(now_x, now_y, MUKI_UP)) {			//上
			next_direction.element.up = 1;

			target_unknown_count = count_unknown_wall(now_x, (now_y + 1));
			if (target_unknown_count == max_unknown_count) {
				priority_direction.element.up = 1;
			} else if (target_unknown_count > max_unknown_count) {
				max_unknown_count = target_unknown_count;
				priority_direction.all = 0;				//他の方向はいらないのでリセット
				priority_direction.element.up = 1;
			}

		}
		if (check_move_by_step(now_x, now_y, MUKI_DOWN)) {			//下
			next_direction.element.down = 1;

			target_unknown_count = count_unknown_wall(now_x, (now_y - 1));
			if (target_unknown_count == max_unknown_count) {
				priority_direction.element.down = 1;
			} else if (target_unknown_count > max_unknown_count) {
				max_unknown_count = target_unknown_count;
				priority_direction.all = 0;				//他の方向はいらないのでリセット
				priority_direction.element.down = 1;
			}

		}

//未探索区間が候補の中にあるなら、次に行く方向はその中から選ぶ
		if ((priority_direction.all != 0) && is_FULUKAWA) {
			next_direction.all = priority_direction.all;
		}

//next_dirrctionから次行く方向を選び、行動する
		next_action = get_next_action(next_direction, mouse::get_direction());
		//TODO 壁キレようの関数を用意する
		run_next_action(next_action);

		//もし止まるべきと出たならココで足立法をやめる
		if (next_action == stop) {
			adachi_flag = false;
		}

//方向更新
		mouse::set_direction(direction_x, direction_y);

	}

	if (adachi_flag) {
		//足立法成功なのでマップを保存する
		map::output_map_data(&mouse::now_map);
		return true;				//足立法完了!!

	} else {
//ここに来るということは足立法が失敗してる
		motor::sleep_motor();
//TODO わかりやすい何かが欲しい
		mouse::error();
		myprintf("Adachi method failed!\n\r");
		if (mouse::get_fail_flag()) {
			myprintf("fail safe!\n\r");
		}

		myprintf("now -> (%d,%d)\n\r", mouse::get_x_position(),
				mouse::get_y_position());
	}

	return false;
}


bool adachi::adachi_method_spin(unsigned char target_x, unsigned char target_y,
		bool is_FULUKAWA) {
	bool adachi_flag = true;	//途中でミスがあったらfalseに
	unsigned char now_x, now_y;	//座標一時保存用。見易さのため
	DIRECTION next_direction, priority_direction;	//次に行く方向を管理
	unsigned char max_unknown_count, target_unknown_count;	//未探索の壁の数を管理
	ACTION_TYPE next_action;	//次の行動を管理

	my7seg::turn_off();

	//保存していたマップを読みだす
	map::input_map_data(&mouse::now_map);

//向きを取得
	mouse::get_direction(&direction_x, &direction_y);

	mouse::run_init(true, true);

	my7seg::count_down(3, 500);

	run::accel_run((0.045 * MOUSE_MODE), SEARCH_VELOCITY, 0);

	while (adachi_flag) {
//フェイルセーフが掛かっていればそこで抜ける
		if (mouse::get_fail_flag()) {
			adachi_flag = false;
			break;
		}

		my7seg::light(3);

//座標を更新
		now_x = mouse::get_x_position() + direction_x;
		now_y = mouse::get_y_position() + direction_y;
		mouse::set_position(now_x, now_y);

//向きも
		mouse::set_direction(direction_x, direction_y);

//壁情報更新
		mouse::velify_wall();
		mouse::look_wall(false);

//目標の座標にたどり着いたら終了
		if ((now_x == target_x) && (now_y == target_y)) {
			run_next_action(stop);
			break;
		}

//歩数マップ作製
		step::set_step(target_x, target_y);

//方向と未探索の壁の数をリセット
		next_direction.all = 0;
		priority_direction.all = 0;
		max_unknown_count = 1;	//0をはじくため

//歩数的に前後左右のマスへ行けるか判別.
//行ければ次行く方向の候補に入れる
//更に見てない壁の数が多ければpriority_directionの方にも候補として追加
		if (check_move_by_step(now_x, now_y, MUKI_RIGHT)) {			//右
			next_direction.element.right = 1;

			target_unknown_count = count_unknown_wall((now_x + 1), now_y);
			if (target_unknown_count == max_unknown_count) {
				priority_direction.element.right = 1;
			} else if (target_unknown_count > max_unknown_count) {
				max_unknown_count = target_unknown_count;
				priority_direction.all = 0;				//他の方向はいらないのでリセット
				priority_direction.element.right = 1;
			}

		}
		if (check_move_by_step(now_x, now_y, MUKI_LEFT)) {			//左

			next_direction.element.left = 1;

			target_unknown_count = count_unknown_wall((now_x - 1), now_y);
			if (target_unknown_count == max_unknown_count) {
				priority_direction.element.left = 1;
			} else if (target_unknown_count > max_unknown_count) {
				max_unknown_count = target_unknown_count;
				priority_direction.all = 0;				//他の方向はいらないのでリセット
				priority_direction.element.left = 1;
			}

		}
		if (check_move_by_step(now_x, now_y, MUKI_UP)) {			//上
			next_direction.element.up = 1;

			target_unknown_count = count_unknown_wall(now_x, (now_y + 1));
			if (target_unknown_count == max_unknown_count) {
				priority_direction.element.up = 1;
			} else if (target_unknown_count > max_unknown_count) {
				max_unknown_count = target_unknown_count;
				priority_direction.all = 0;				//他の方向はいらないのでリセット
				priority_direction.element.up = 1;
			}

		}
		if (check_move_by_step(now_x, now_y, MUKI_DOWN)) {			//下
			next_direction.element.down = 1;

			target_unknown_count = count_unknown_wall(now_x, (now_y - 1));
			if (target_unknown_count == max_unknown_count) {
				priority_direction.element.down = 1;
			} else if (target_unknown_count > max_unknown_count) {
				max_unknown_count = target_unknown_count;
				priority_direction.all = 0;				//他の方向はいらないのでリセット
				priority_direction.element.down = 1;
			}

		}

//未探索区間が候補の中にあるなら、次に行く方向はその中から選ぶ
		if ((priority_direction.all != 0) && is_FULUKAWA) {
			next_direction.all = priority_direction.all;
		}

//next_dirrctionから次行く方向を選び、行動する
		next_action = get_next_action(next_direction, mouse::get_direction());
		//TODO 壁キレようの関数を用意する
		run_next_action(next_action);

		//もし止まるべきと出たならココで足立法をやめる
		if (next_action == stop) {
			adachi_flag = false;
		}

//方向更新
		mouse::set_direction(direction_x, direction_y);

	}

	if (adachi_flag) {
		//足立法成功なのでマップを保存する
		map::output_map_data(&mouse::now_map);
		return true;				//足立法完了!!

	} else {
//ここに来るということは足立法が失敗してる
		motor::sleep_motor();
//TODO わかりやすい何かが欲しい
		mouse::error();
		myprintf("Adachi method failed!\n\r");
		if (mouse::get_fail_flag()) {
			myprintf("fail safe!\n\r");
		}

		myprintf("now -> (%d,%d)\n\r", mouse::get_x_position(),
				mouse::get_y_position());
	}

	return false;
}

bool adachi::left_hand_method(const uint8_t target_x, const uint8_t target_y) {
	bool search_flag = true;	//途中でミスがあったらfalseに
	uint8_t now_x, now_y;	//座標一時保存用。見易さのため
	ACTION_TYPE next_action;	//次の行動を管理

	my7seg::turn_off();

	//保存していたマップを読みだす
	map::input_map_data(&mouse::now_map);

	//向きを取得
	mouse::get_direction(&direction_x, &direction_y);

	mouse::run_init(true, true);

	my7seg::count_down(3, 500);

	run::accel_run((0.045 * MOUSE_MODE), SEARCH_VELOCITY, 0);

	while (search_flag) {
		if (photo::check_wall(left) == false)
			next_action = turn_left;
		else if (photo::check_wall(front) == false)
			next_action = go_straight;
		else if (photo::check_wall(right) == false)
			next_action = turn_right;
		else
			next_action = back;

		run_next_action(next_action);

	}

}

adachi::adachi() {
}

adachi::~adachi() {

}

