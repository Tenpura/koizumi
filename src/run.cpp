/*
 * run.cpp
 *
 *  Created on: 2016/10/23
 *      Author: Koizumi
 */

#include"run.h"
uint32_t mouse::debag_val_enc_l;
uint32_t mouse::debag_val_enc_r;
float mouse::ideal_acceleration, mouse::ideal_angular_acceleration;
float mouse::ideal_velocity, mouse::ideal_angular_velocity,
		mouse::ideal_angle_degree, mouse::ideal_distance;
float mouse::relative_base_rad = 0;
float mouse::velocity;
float mouse::run_distance;
COORDINATE mouse::place;
COORDINATE mouse::relative;
unsigned long mouse::mouse_count_ms;

MAP_DATA mouse::now_map;

POSITION mouse::position;
//unsigned char mouse::mouse_direction = MUKI_UP;
compas mouse::direction = north;

bool mouse::is_fail_safe = false;
bool mouse::is_spin_turn = false;

void mouse::reset_count() {
	mouse_count_ms = 0;
}

void mouse::add_one_count_ms() {
	mouse_count_ms = mouse_count_ms + 1;
}

unsigned long mouse::get_count_ms() {
	return mouse_count_ms;
}

void mouse::set_ideal_accel(const float set_value_m_ss) {
	ideal_acceleration = set_value_m_ss;
}

float mouse::get_ideal_accel() {
	return ideal_acceleration;	//m/s^2
}

void mouse::set_ideal_angular_accel(const float set_value_m_ss) {
	ideal_angular_acceleration = set_value_m_ss;
}

float mouse::get_ideal_angular_accel() {
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

float mouse::get_angular_velocity() {
	return gyro::get_angular_velocity();
}

void mouse::set_ideal(const float accel, const float vel, const float dis) {
	set_ideal_accel(accel);
	set_ideal_velocity(vel);
	set_distance_m(dis);
}
void mouse::set_ideal_ang(const float ang_a, const float ang_omega) {
	set_ideal_angular_accel(ang_a);
	set_ideal_angular_velocity(ang_omega);
}

void mouse::set_ang(const float set_rad) {
	gyro::set_angle(set_rad);
}

float mouse::get_ideal_angular_velocity() {
	return ideal_angular_velocity;
}

float mouse::get_velocity() {
	return velocity;
}

void mouse::reset_angle() {
	gyro::reset_angle();
	mouse::reset_count();		//最小二乗法の補正ためカウントをリセット

	//マウスの向いている向きに応じてangleとrelative_radを変更する
	//TODO 斜め方向は要検討
	float rad = 0;
	switch (get_compas()) {
	case north:
		rad = 0;
		break;
	case north_east:
		rad = PI() / 4;
		break;
	case east:
		rad = PI() / 2;
		break;
	case south_east:
		rad = PI() * 3 / 4;
		break;
	case south:
		rad = PI();
		break;
	case north_west:
		rad = -PI() / 4;
		break;
	case west:
		rad = -PI() / 2;
		break;
	case south_west:
		rad = -PI() * 3 / 4;
		break;
	}
	set_ang(rad);	//絶対角度を変更
	set_relative_rad(0, false);	//基準はリセットする
}

float mouse::get_angle_degree() {
	return degree(gyro::get_angle_radian());
}

float mouse::get_angle_radian() {
	return (gyro::get_angle_radian());
}

float mouse::get_ideal_angle_degree() {
	return degree(ideal_angle_degree);
}

float mouse::get_ideal_angle_radian() {
	return ideal_angle_degree;
}

float mouse::get_distance_m() {

	return run_distance;
	//return ideal_distance;

}

void mouse::set_distance_m(const float set_value_m) {
	run_distance = set_value_m;
	ideal_distance = set_value_m;
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

void mouse::set_place(COORDINATE set) {
	set_place(set.x, set.y);
}

void mouse::set_place(float x_m, float y_m) {
	place.x = x_m;
	place.y = y_m;

	//相対位置を計算する
	relative.x = x_m;
	relative.y = y_m;
	//mod1区間を行う
	while ((relative.x > 0.09 * MOUSE_MODE) || (relative.y > 0.09 * MOUSE_MODE)) {
		if (relative.x > 0.09 * MOUSE_MODE)
			relative.x -= 0.09 * MOUSE_MODE;
		if (relative.y > 0.09 * MOUSE_MODE)
			relative.y -= 0.09 * MOUSE_MODE;
	}
	//区画の中心が原点
	relative.x -= 0.045 * MOUSE_MODE;
	relative.y -= 0.045 * MOUSE_MODE;
}

COORDINATE mouse::get_place() {
	return place;
}

float mouse::get_relative_side() {
	static const float quart_sqrt = MOUSE_MODE * 0.0225 * SQRT2;	//1/4区間*√2
	float dir_x, dir_y;		//マウスの方向
	mouse::get_direction(&dir_x, &dir_y);
	float ans = (dir_y * relative.x - dir_x * relative.y);

	switch (mouse::direction) {
	//斜めじゃなければ何もしない
	case north:
	case south:
	case west:
	case east:
		break;
		//斜めなら
	case north_east:
	case north_west:
	case south_east:
	case south_west:
		ans -= quart_sqrt;	//基準を1/4区間*√2だけずらす
		while (ABS(ans) > quart_sqrt) {		//±1/4区間*√2にする
			ans -= 2 * quart_sqrt * SIGN(ans);
		}
		break;
	}
	return ans;

}

float mouse::get_relative_go() {
	static const float quart_sqrt = MOUSE_MODE * 0.0225 * SQRT2;	//1/4区間*√2
	float dir_x, dir_y;		//マウスの方向
	mouse::get_direction(&dir_x, &dir_y);
	float ans = (dir_x * relative.x + dir_y * relative.y);

	switch (mouse::direction) {
	//斜めじゃなければ何もしない
	case north:
	case south:
	case west:
	case east:
		break;
		//斜めなら
	case north_east:
	case north_west:
	case south_east:
	case south_west:
		while (ABS(ans) > quart_sqrt) {		//±1/4区間*√2にする
			ans -= 2 * quart_sqrt * SIGN(ans);
		}
		break;
	}
	return ans;

}

void mouse::set_relative_go(float set_value) {
	float dir_x, dir_y;		//マウスの方向
	mouse::get_direction(&dir_x, &dir_y);
	float delta = set_value - get_relative_go();		//現在値との差分

			//相対座標を更新
	relative.x += dir_x * delta;
	relative.y += dir_y * delta;

	//絶対座標を更新
	place.x += dir_x * delta;
	place.y += dir_y * delta;

}

void mouse::set_relative_side(float _set_value) {
	float dir_x, dir_y;		//マウスの方向
	mouse::get_direction(&dir_x, &dir_y);
	float delta = _set_value - get_relative_side();		//現在値との差分

			//相対座標を更新
	relative.x += dir_y * delta;
	relative.y += -dir_x * delta;

	//絶対座標を更新
	place.x += dir_y * delta;
	place.y += -dir_x * delta;

}

float mouse::get_relative_rad() {
	//相対角度を計算　(絶対角度-基準角度)
	return (get_angle_radian() - relative_base_rad);
}

void mouse::set_relative_rad(float set_rad, bool update_abs) {

	float delta = set_rad - get_relative_rad();
	//絶対角度を更新しない場合は基準だけいじって終了
	if (!update_abs) {
		relative_base_rad -= delta;

	} else {		//絶対角度を更新する場合は逆に基準はいじらない
		set_ang(get_angle_radian() + delta);

	}
}

void mouse::set_relative_base_rad(SLALOM_TYPE sla, bool is_right) {
	float correct = 0;	//修正量の保存用
	switch (sla) {
	case small:
	case big_90:
	case oblique_90:
		correct = PI() / 2;
		break;
	case begin_45:
	case end_45:
		correct = PI() / 4;
		break;
	case begin_135:
	case end_135:
		correct = PI() * 3 / 4;
		break;
	case big_180:
		correct = PI();
		break;
	default:
		break;
	}

	if (!is_right)		//時計回りが正
		correct *= -1;
	relative_base_rad += correct;	//基準角度を変更

}
/*
 unsigned char mouse::get_direction() {
 return compas_to_muki(direction);
 }
 */
compas mouse::get_compas() {
	return direction;
}

void mouse::get_direction(signed char *direction_x, signed char *direction_y) {
	switch (direction) {
	case east:
		*direction_x = 1;
		*direction_y = 0;
		break;

	case west:
		*direction_x = -1;
		*direction_y = 0;
		break;

	case north:
		*direction_x = 0;
		*direction_y = 1;
		break;

	case south:
		*direction_x = 0;
		*direction_y = -1;
		break;
	default:
		*direction_x = 0;
		*direction_y = 0;
		break;
	}
}

void mouse::get_direction(float *dir_x, float *dir_y) {
	switch (direction) {
	case east:
		*dir_x = 1;
		*dir_y = 0;
		break;

	case west:
		*dir_x = -1;
		*dir_y = 0;
		break;

	case north:
		*dir_x = 0;
		*dir_y = 1;
		break;

	case south:
		*dir_x = 0;
		*dir_y = -1;
		break;

	case north_east:
		*dir_x = SQRT2 / 2;
		*dir_y = SQRT2 / 2;
		break;
	case north_west:
		*dir_x = -SQRT2 / 2;
		*dir_y = SQRT2 / 2;
		break;
	case south_east:
		*dir_x = SQRT2 / 2;
		*dir_y = -SQRT2 / 2;
		break;
	case south_west:
		*dir_x = -SQRT2 / 2;
		*dir_y = -SQRT2 / 2;
		break;
	}

}

void mouse::set_direction(const compas dir) {
	direction = dir;
}

void mouse::set_direction(const signed char direction_x,
		const signed char direction_y) {
	switch (direction_x) {
	case 1:
		direction = east;
		break;

	case -1:
		direction = west;
		break;

	case 0:
		if (direction_y == 1) {
			direction = north;
		} else {
			direction = south;
		}
		break;
	}
}

bool mouse::get_fail_flag() {
	return is_fail_safe;
}

void mouse::set_fail_flag(bool set_flag) {
	is_fail_safe = set_flag;
}

bool mouse::get_spin_flag() {
	return is_spin_turn;
}

void mouse::set_spin_flag(bool is_spin) {
	is_spin_turn = is_spin;
}

void mouse::cal_velocity() {
	//（速度+=加速度）を制御にぶち込む
	set_ideal_velocity(
			get_ideal_velocity() + get_ideal_accel() * CONTORL_PERIOD);
	//（角速度+=加角速度）を制御にぶち込む
	set_ideal_angular_velocity(
			get_ideal_angular_velocity() + get_ideal_angular_accel() * CONTORL_PERIOD);
}

void mouse::cal_distance() {
	run_distance += (velocity + ideal_acceleration * CONTROL_PERIOD / 2)
			* CONTROL_PERIOD;
	ideal_distance += (ideal_velocity + ideal_acceleration * CONTROL_PERIOD / 2)
			* CONTROL_PERIOD;
}

void mouse::cal_place() {
	float theta = get_angle_radian();		//マウスの角度を取得
	//微小時間にマウスが進む距離
	float dl = (velocity + ideal_acceleration * CONTORL_PERIOD / 2)
			* CONTORL_PERIOD;
	float dx = dl * sinf(theta);
	float dy = dl * cosf(theta);

	place.x += dx;
	place.y += dy;

	//相対的位置も、逐次更新して、範囲外に出たらオーバーフロー処理
	relative.x += dx;
	relative.y += dy;
	//+-半区間の範囲から出たら、中に戻す
	if (ABS(relative.x) > 0.045 * MOUSE_MODE)
		relative.x -= SIGN(relative.x) * 0.09 * MOUSE_MODE;
	if (ABS(relative.y) > 0.045 * MOUSE_MODE)
		relative.y -= SIGN(relative.y) * 0.09 * MOUSE_MODE;

}

void mouse::interrupt() {

	//XXX カルマンフィルタの推定値（加速度センサ）と観測値（エンコーダー）の分散
	static kalman v_kal(0.101, 630);		//速度用のカルマンフィルタクラスを呼び出す
	if (get_spin_flag()) {		//超信地中なら
		v_kal.update(encoder::get_velocity(), encoder::get_velocity());	//加速度センサは無視してカルマンフィルタをかける
	} else {
		v_kal.update(accelmeter::get_accel(axis_y) * CONTORL_PERIOD,
				encoder::get_velocity());		//カルマンフィルタをかける
	}
	velocity = v_kal.get_value();		//現在速度として補正後の速度を採用する
	//速度と距離を計算
	mouse::cal_velocity();
	mouse::cal_distance();
	mouse::cal_place();

	ideal_angle_degree += get_ideal_angular_velocity() * CONTORL_PERIOD;

}

void mouse::run_init(bool posture_ctrl, bool wall_ctrl) {
	static const float half_section = 0.045 * MOUSE_MODE;	//半区画分の長さ

	motor::sleep_motor();
	//制御を切る
	control::stop_wall_control();
	control::stop_control();

	mouse::set_spin_flag(false);

	accelmeter::set_accel_ref(AXIS_t::axis_y);
	gyro::set_gyro_ref();
	mouse::reset_angle();
	mouse::set_distance_m(0);
	mouse::set_ideal_accel(0);
	mouse::set_ideal_velocity(0);
	mouse::set_ideal_angular_accel(0);
	mouse::set_ideal_angular_velocity(0);
	mouse::set_place(half_section * (1 + 2 * mouse::get_x_position()),
			half_section * (1 + 2 * mouse::get_y_position()));		//現在座標の中心位置
	wait::ms(1);
	control::reset_delta();
	wait::ms(1);

	//フェイルセーフを初期化
	mouse::set_fail_flag(false);


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

	switch (direction) {
	case north:
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

	case east:
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

	case west:
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

	case south:
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
	default:
		break;
	}

}

void mouse::velify_wall() {
	my7seg::turn_off();
	if (photo::check_wall(PHOTO_TYPE::front))
		my7seg::light(my7seg::front);
	if (photo::check_wall(PHOTO_TYPE::right))
		my7seg::light(my7seg::right);
	if (photo::check_wall(PHOTO_TYPE::left))
		my7seg::light(my7seg::left);

}

void mouse::turn_90_dir(const unsigned char right_or_left) {
	//マウスの向きを90°回転
	bool is_right = false;
	if (right_or_left == MUKI_RIGHT)
		is_right = true;
	turn_45_dir(is_right);
	turn_45_dir(is_right);
}

void mouse::turn_45_dir(bool is_right) {
	//マウスの向きを45°回転
	if (is_right) {
		switch (direction) {
		case north:
			direction = north_east;
			break;
		case north_east:
			direction = east;
			break;
		case east:
			direction = south_east;
			break;
		case south_east:
			direction = south;
			break;
		case south:
			direction = south_west;
			break;
		case south_west:
			direction = west;
			break;
		case west:
			direction = north_west;
			break;
		case north_west:
			direction = north;
			break;
		}
	} else {
		switch (direction) {
		case north:
			direction = north_west;
			break;
		case north_west:
			direction = west;
			break;
		case west:
			direction = south_west;
			break;
		case south_west:
			direction = south;
			break;
		case south:
			direction = south_east;
			break;
		case south_east:
			direction = east;
			break;
		case east:
			direction = north_east;
			break;
		case north_east:
			direction = north;
			break;
		}
	}
}

void mouse::turn_direction_slalom(const SLALOM_TYPE slalom_type,
		const unsigned char right_or_left) {
	switch (slalom_type) {
	case none:
	case spin_turn:
	case slalom_type_count:
		break;

	case small:
	case big_90:
		turn_90_dir(right_or_left);
		break;

	case big_180:
		turn_90_dir(right_or_left);
		turn_90_dir(right_or_left);
		break;

	case begin_45:
	case end_45:
		if (right_or_left == MUKI_RIGHT)
			turn_45_dir(true);
		else
			turn_45_dir(false);
		break;

	case begin_135:
	case end_135:
		turn_90_dir(right_or_left);
		if (right_or_left == MUKI_RIGHT)
			turn_45_dir(true);
		else
			turn_45_dir(false);
		break;

	case oblique_90:
		turn_90_dir(right_or_left);
		break;
	}
}

void mouse::error() {
	//TODO エラー処理は必要に応じて書くこと
	motor::sleep_motor();
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

//XXX 壁キレのパラメータ
// right left front_right front_left front
//センサ距離の閾値
const std::array<float, static_cast<int>(PHOTO_TYPE::element_count)> run::WALLEAGE_BODOR =
		{ -0.020, 0.020, 0, 0, 0 };
const std::array<float, static_cast<int>(PHOTO_TYPE::element_count)> run::WALLEAGE_BODOR_OBLI =
		{ -0.020, 0.000, 0, 0, 0 };

//距離[m]　区画の境目までどれくらいの距離なのか[m]
const std::array<float, static_cast<int>(PHOTO_TYPE::element_count)> run::DOWN_WALLEAGE_DISTANCE =
		{ 0.035, 0.032, 0, 0, 0 };
//斜めの場合は区画の境目"から"どのくらいずれているか
const std::array<float, static_cast<int>(PHOTO_TYPE::element_count)> run::DOWN_WALLEAGE_OBLI =
		{ 0.005, 0.003, 0, 0, 0 };

void run::accel_run(const float distance_m, const float end_velocity,
		const unsigned char select_mode) {

	float max_velocity = parameter::get_run_max_velocity(select_mode);
	float accel_value = ABS(parameter::get_run_acceleration(select_mode));
	float de_accel_value = ABS(parameter::get_run_de_acceleration(select_mode));
	float de_accel_distance = ABS(
			mouse::get_ideal_velocity() * mouse::get_ideal_velocity()
			- end_velocity * end_velocity) / (2 * de_accel_value);	//減速に必要な距離

	float sign = 1;
	//バックするなら
	if (distance_m < 0) {
		sign = -1;
		max_velocity *= -1;
		accel_value *= -1;
		de_accel_value *= -1;
		de_accel_distance *= -1;
	}

	//加速
	mouse::set_ideal_accel(accel_value);
	while (0 < sign * (max_velocity - mouse::get_ideal_velocity())) {
		//現在速度から減速にかかる距離を計算
		de_accel_distance = (mouse::get_ideal_velocity()
				* mouse::get_ideal_velocity() - end_velocity * end_velocity)
				/ (2 * de_accel_value);

		//減速に距離が必要な距離が足りなくなったら抜ける
		if (ABS(de_accel_distance)
				>= sign * (distance_m - mouse::get_distance_m())) {
			break;
		}

		if (mouse::get_fail_flag())
			return;
	}

	//等速
	mouse::set_ideal_accel(0);
	while (1) {
		//現在速度から減速にかかる距離を計算
		de_accel_distance = (mouse::get_ideal_velocity()
				* mouse::get_ideal_velocity() - end_velocity * end_velocity)
				/ (2 * de_accel_value);

		//減速に距離が必要な距離が足りなくなったら抜ける
		if (ABS(de_accel_distance)
				>= sign * (distance_m - mouse::get_distance_m())) {
			break;
		}

		if (mouse::get_fail_flag())
			return;
	}

	//減速
	mouse::set_ideal_accel(-de_accel_value);
	while (sign * (mouse::get_ideal_velocity() - end_velocity) > 0) {
		//速度より先に距離がなくなったら抜ける
		if (distance_m < mouse::get_distance_m())
			break;

		if (mouse::get_fail_flag())
			return;

		/*
		 de_accel_value = sign
		 * (max_velocity * max_velocity - end_velocity * end_velocity)
		 / (2 * (distance_m - mouse::get_distance_m()));
		 mouse::set_ideal_accel(-de_accel_value);
		 */

	}

	mouse::set_ideal_accel(0);
	mouse::set_ideal_velocity(end_velocity);

	//速度0だとここに閉じ込められてしまう
	if (sign * end_velocity > 0) {
		//もし速度が先に無くなっても、最後まで走りきるよう
		while (sign * (distance_m - mouse::get_distance_m()) > 0) {
			if (mouse::get_fail_flag())
				return;
		}
	}

	mouse::set_distance_m(sign * (distance_m - mouse::get_distance_m()));
	mouse::set_distance_m(0);
}

bool run::wall_edge_run_for_search(const float distance_m,
		const float end_velocity, const unsigned char select_mode,
		const float check_distance) {
	float target_distance = check_distance;
	bool wall_eage_flag = true;

	//right left front_right, front_left, front
	float wall_eage[static_cast<int>(PHOTO_TYPE::element_count)] = { -0.02,
			0.02, 0, 0, 0 };
	//この値を下回ったら壁キレ

	GPIO_SetBits(GPIOC, GPIO_Pin_3);	//LED2

	//チェック距離までは普通に走る
	accel_run(distance_m - check_distance, end_velocity, select_mode);

	//直前まで壁があってから壁キレを見る　＝　閾値をまたぐのを判断するよう
	uint8_t right = 0;
	uint8_t left = 0;

	//直前に何ms以上 閾値を超えていれば壁キレが起こると判断するか（値がバラつく対策）
	static const uint8_t w_cnt = 5;

	//1ms まってから次のセンサー値をみるために、割り込みがされたか判断するよう
	uint32_t time_count = mouse::get_count_ms();

	//安定しないので壁があるときだけ壁キレを読む
	bool check_l = photo::check_wall(PHOTO_TYPE::left);
	bool check_r = photo::check_wall(PHOTO_TYPE::right);

	while (mouse::get_distance_m() < target_distance) {
		//フェイルセーフが掛かっていればそこで抜ける
		if (mouse::get_fail_flag()) {
			return false;
		}

		while (time_count == mouse::get_count_ms()) {
			//割り込みが入るまで待つ
		}
		time_count = mouse::get_count_ms();

		if (!wall_eage_flag) {
			GPIO_ResetBits(GPIOC, GPIO_Pin_3);	//LED2
		} else {
			if (check_l) {
				//直前w_cnt[ms]以上閾値の反対側にいて、このときはじめて閾値を超えたなら
				if (left >= w_cnt) {
					if (photo::get_displa_from_center(PHOTO_TYPE::left)
							> wall_eage[static_cast<uint8_t>(PHOTO_TYPE::left)]) {
						target_distance =
								DOWN_WALLEAGE_DISTANCE[static_cast<uint8_t>(PHOTO_TYPE::left)];
						mouse::set_relative_go(
								0.045 * MOUSE_MODE - target_distance);//区画中央を原点として位置を更新
						mouse::set_distance_m(0);
						wall_eage_flag = false;
					}
				} else {
					//壁キレを待つ前にそもそも壁キレが起こるのかを判断
					if (photo::get_displa_from_center(PHOTO_TYPE::left)
							< wall_eage[static_cast<uint8_t>(PHOTO_TYPE::left)])
						left++;
					else
						left = 0;
				}
			}

			if (check_r) {
				//直前w_cnt[ms]以上閾値の反対側にいて、このときはじめて閾値を超えたなら
				if (right >= w_cnt) {
					if (photo::get_displa_from_center(PHOTO_TYPE::right)
							< wall_eage[static_cast<uint8_t>(PHOTO_TYPE::right)]) {
						target_distance =
								DOWN_WALLEAGE_DISTANCE[static_cast<uint8_t>(PHOTO_TYPE::right)];
						mouse::set_relative_go(
								0.045 * MOUSE_MODE - target_distance);//区画中央を原点として位置を更新
						mouse::set_distance_m(0);
						wall_eage_flag = false;
					}
				} else {
					//壁キレを待つ前にそもそも壁キレが起こるのかを判断
					if (photo::get_displa_from_center(PHOTO_TYPE::right)
							> wall_eage[static_cast<uint8_t>(PHOTO_TYPE::right)])
						right++;
					else
						right = 0;
				}
			}

		}

	}

	my7seg::turn_off();
	mouse::set_distance_m(0);
	GPIO_SetBits(GPIOC, GPIO_Pin_3);	//LED2
	return !wall_eage_flag;
}

void run::wall_edge_run_for_slalom(const float distance_m,
		const float end_velocity, const uint8_t select_mode,
		const bool is_right, const bool is_obli, const bool run_to_edge) {

	float run_dis = 0;		//走行距離
	bool wall_eage_flag = true;
	bool to_wall_edge = run_to_edge;
	std::array<float, static_cast<int>(PHOTO_TYPE::element_count)> down_dis;//壁キレ時に区画中心からどの程度ずれているか

	PHOTO_TYPE turn_photo = PHOTO_TYPE::right;	//曲がる方向　こっちの壁キレだけをみる
	int photo_Int = photo_R;
	int turn_sign = 1;	//右なら1,左なら-1		右と左でリファレンスとの閾値の関係（不等号が逆なのでつけとく）
	/*
	 if (is_right == false) {
	 turn_photo = PHOTO_TYPE::left;
	 photo_Int = photo_L;
	 turn_sign = -1;
	 }
	 */
	//right left front_right, front_left, front
	std::array<float, static_cast<int>(PHOTO_TYPE::element_count)> wall_edge;//この値を超えたら壁キレ
	if (is_obli) {	//斜めの閾値
		wall_edge.at(photo_R) = WALLEAGE_BODOR_OBLI.at(photo_R);
		wall_edge.at(photo_L) = WALLEAGE_BODOR_OBLI.at(photo_L);
		down_dis.at(photo_R) = DOWN_WALLEAGE_OBLI.at(photo_R);
		down_dis.at(photo_L) = DOWN_WALLEAGE_OBLI.at(photo_L);
	} else {
		wall_edge.at(photo_R) = WALLEAGE_BODOR.at(photo_R);
		wall_edge.at(photo_L) = WALLEAGE_BODOR.at(photo_L);
		down_dis.at(photo_R) = 0.045 * MOUSE_MODE
				- DOWN_WALLEAGE_DISTANCE.at(photo_R);
		down_dis.at(photo_L) = 0.045 * MOUSE_MODE
				- DOWN_WALLEAGE_DISTANCE.at(photo_L);
	}

	//この関数内でも加減速できるように
	//雑に目標速度まで加速or減速しかしない
	float accel_sign = 0;
	if (mouse::get_ideal_velocity() < end_velocity) {			//現在速度が足りないとき
		mouse::set_ideal_accel(
				ABS(parameter::get_run_acceleration(select_mode)));	//加速
		accel_sign = 1;	//加速なので正
	} else if (mouse::get_ideal_velocity() > end_velocity) {	//現在速度が超過してるとき
		mouse::set_ideal_accel(
				-ABS(parameter::get_run_de_acceleration(select_mode)));	//減速
		accel_sign = -1;	//減速なので負
	}

	//区画の中心からスタート想定

	//直前まで壁があってから壁キレを見る　＝　閾値をまたぐのを判断するよう	迷路の中心に近いか遠いか
	std::array<uint16_t, static_cast<int>(PHOTO_TYPE::element_count)> in = { 0 };
	std::array<uint16_t, static_cast<int>(PHOTO_TYPE::element_count)> out =
			{ 0 };

	//直前に何ms以上 閾値を超えていれば壁キレが起こると判断するか（値がバラつく対策）
	uint8_t w_cnt = 5;

	//1ms まってから次のセンサー値をみるために、割り込みがされたか判断するよう
	uint32_t time_count = mouse::get_count_ms();

	while (!mouse::get_fail_flag()) {	//フェイルセーフが掛かっていればそこで抜ける

		while (time_count == mouse::get_count_ms()) {
			//割り込みが入るまで待つ
		}
		time_count = mouse::get_count_ms();

		if (accel_sign != 0) {		//加速or減速している場合
			if (((mouse::get_ideal_velocity() - end_velocity) * accel_sign)
					>= 0) {		//目標速度を超えたら
				mouse::set_ideal_accel(0);		//加減速を止める
				mouse::set_ideal_velocity(end_velocity);	//目標速度をセット
			}
		}

		//区画中心から、どのくらいの位置にいるか
		run_dis = mouse::get_relative_go();

		//目標距離走ったら抜ける
		if (distance_m <= run_dis) {
			if ((!wall_eage_flag) || (!to_wall_edge))//to_wall_edge（壁キレ見るまで走る）場合は壁キレしてないと距離足りてても抜けない
				break;
		}

		//壁キレ！
		if (!wall_eage_flag) {
			GPIO_ResetBits(GPIOC, GPIO_Pin_3);	//LED2
		} else {
			//直前w_cnt[ms]以上閾値の反対側にいて、このときはじめて閾値を超えたなら
			if (in.at(photo_Int) >= w_cnt) {
				if ((photo::get_displa_from_center(turn_photo)
						- wall_edge[photo_Int]) * turn_sign < 0) {
					mouse::set_relative_go(down_dis.at(photo_Int));	//区画中央を原点として位置を更新
					in.at(photo_Int) = 0;
					wall_eage_flag = false;
				}
			} else if (out.at(photo_Int) > w_cnt) {
				if ((photo::get_displa_from_center(turn_photo)
						- wall_edge[photo_Int]) * turn_sign > 0) {
					out.at(photo_Int) = 0;
				}
			}
			//今閾値のどっち側にいるか
			if ((photo::get_displa_from_center(turn_photo)
					- wall_edge.at(photo_R)) * turn_sign > 0) {
				if (in.at(photo_Int) < 10000) {
					in.at(photo_Int)++;}
				out.at(photo_Int) = 0;
			} else {
				in.at(photo_Int) = 0;
				if (out.at(photo_Int) < 10000) {
					out.at(photo_Int)++;}
				}

				//直前w_cnt[ms]以上閾値の反対側にいて、このときはじめて閾値を超えたなら
			if (in.at(photo_L) >= w_cnt) {
				if ((photo::get_displa_from_center(PHOTO_TYPE::left)
						- wall_edge[photo_L]) * (-1) < 0) {
					mouse::set_relative_go(down_dis.at(photo_L));//区画中央を原点として位置を更新
					in.at(photo_L) = 0;
					wall_eage_flag = false;
				}
			} else if (out.at(photo_L) > w_cnt) {
				if ((photo::get_displa_from_center(PHOTO_TYPE::left)
						- wall_edge[photo_L]) * (-1) > 0) {
					out.at(photo_Int) = 0;
				}
			}
			//今閾値のどっち側にいるか
			if ((photo::get_displa_from_center(PHOTO_TYPE::left)
					- wall_edge.at(photo_L)) * (-1) > 0) {
				if (in.at(photo_L) < 10000) {
					in.at(photo_L) += 1;
				}
				out.at(photo_L) = 0;
			} else {
				in.at(photo_L) = 0;
				if (out.at(photo_L) < 10000) {
					out.at(photo_L) += 1;
				}
			}

		}
	}

	my7seg::turn_off();
	mouse::set_ideal_velocity(end_velocity);	//目標速度をセット
	mouse::set_distance_m(0);
	GPIO_SetBits(GPIOC, GPIO_Pin_3);	//LED2
}

void run::wall_edge_run_for_obli(const float distance_m,
		const float end_velocity, const uint8_t select_mode, bool run_to_edge) {

	float run_dis = 0;		//走行距離
	bool wall_eage_flag = true;
	bool to_wall_edge = run_to_edge;

	//right left front_right, front_left, front
	float wall_eage[static_cast<int>(PHOTO_TYPE::element_count)] = { -0.0, 0.0,
			0, 0, 0 };		//この値を超えたら壁キレ

	//この関数内でも加減速できるように
	//雑に目標速度まで加速or減速しかしない
	float accel_sign = 0;
	if (mouse::get_ideal_velocity() < end_velocity) {	//現在速度が足りないとき
		mouse::set_ideal_accel(
				ABS(parameter::get_run_acceleration(select_mode)));	//加速
		accel_sign = 1;	//加速なので正
	} else if (mouse::get_ideal_velocity() > end_velocity) {	//現在速度が超過してるとき
		mouse::set_ideal_accel(
				-ABS(parameter::get_run_de_acceleration(select_mode)));	//減速
		accel_sign = -1;	//減速なので負
	}

	//区画の中心からスタート想定

	//直前まで壁があってから壁キレを見る　＝　閾値をまたぐのを判断するよう	迷路の中心に近いか遠いか
	enum UpDown {
		inner = 0, outer = 1, element
	};
	uint16_t right[element] = { 0 };		//今閾値のどっち側にいるかカウントする
	uint16_t left[element] = { 0 };

	//直前に何ms以上 閾値を超えていれば壁キレが起こると判断するか（値がバラつく対策）
	uint8_t w_cnt = 5;

	//1ms まってから次のセンサー値をみるために、割り込みがされたか判断するよう
	uint32_t time_count = mouse::get_count_ms();

	while (!mouse::get_fail_flag()) {	//フェイルセーフが掛かっていればそこで抜ける

		while (time_count == mouse::get_count_ms()) {
			//割り込みが入るまで待つ
		}
		time_count = mouse::get_count_ms();

		if (accel_sign != 0) {		//加速or減速している場合
			if (((mouse::get_ideal_velocity() - end_velocity) * accel_sign)
					>= 0) {		//目標速度を超えたら
				mouse::set_ideal_accel(0);		//加減速を止める
				mouse::set_ideal_velocity(end_velocity);		//目標速度をセット
			}
		}

		//区画中心から、どのくらいの位置にいるか
		run_dis = mouse::get_relative_go();

		//目標距離走ったら抜ける
		if (distance_m <= run_dis) {
			if (!wall_eage_flag || !to_wall_edge)//to_wall_edge（壁キレ見るまで走る）場合は壁キレしてないと距離足りてても抜けない
				break;
		}

		//壁キレ！
		if (!wall_eage_flag) {
			GPIO_ResetBits(GPIOC, GPIO_Pin_3);	//LED2
		} else {
			//直前w_cnt[ms]以上閾値の反対側にいて、このときはじめて閾値を超えたなら
			if (left[inner] >= w_cnt) {
				if (photo::get_displa_from_center(PHOTO_TYPE::left)
						> wall_eage[photo_L]) {
					mouse::set_relative_go(DOWN_WALLEAGE_OBLI[photo_L]);//区画中央を原点として位置を更新
					left[inner] = 0;
					wall_eage_flag = false;
				}
			} else if (left[outer] > w_cnt) {
				if (photo::get_displa_from_center(PHOTO_TYPE::left)
						< wall_eage[photo_L]) {
					/*
					 mouse::set_relative_go(
					 0.045 * MOUSE_MODE
					 - DOWN_WALLEAGE_DISTANCE[static_cast<int>(PHOTO_TYPE::left)]);//区画中央を原点として位置を更新
					 left[down]=0;
					 wall_eage_flag = false;
					 */
				}
			}
			//直前w_cnt[ms]以上閾値の反対側にいて、このときはじめて閾値を超えたなら
			if (right[inner] >= w_cnt) {
				if (photo::get_displa_from_center(PHOTO_TYPE::right)
						< wall_eage[photo_R]) {
					mouse::set_relative_go(DOWN_WALLEAGE_OBLI[photo_R]);//区画中央を原点として位置を更新
					right[inner] = 0;
					wall_eage_flag = false;
				}
			} else if (right[outer] >= w_cnt) {
				if (photo::get_displa_from_center(PHOTO_TYPE::right)
						> wall_eage[photo_R]) {
					/*
					 mouse::set_relative_go(
					 0.045 * MOUSE_MODE
					 - UP_WALLEAGE_DISTANCE[static_cast<int>(PHOTO_TYPE::right)]);	//区画中央を原点として位置を更新
					 right[down]=0;
					 wall_eage_flag = false;
					 */
				}
			}

			//今閾値のどっち側にいるか
			if (photo::get_displa_from_center(PHOTO_TYPE::left)
					< wall_eage[photo_L]) {
				left[inner]++;
				left[outer] = 0;
			} else {
				left[inner] = 0;
				left[outer]++;
			}
			if (photo::get_displa_from_center(PHOTO_TYPE::right)
					> wall_eage[photo_R]) {
				right[inner]++;
				right[outer] = 0;
			} else {
				right[inner] = 0;
				right[outer]++;
			}

		}

	}

	my7seg::turn_off();
	mouse::set_ideal_velocity(end_velocity);	//目標速度をセット
	mouse::set_distance_m(0);
	GPIO_SetBits(GPIOC, GPIO_Pin_3);	//LED2
}

void run::path_accel_run_wall_edge(const float distance_m, const float end_v,
		const COORDINATE init, const uint8_t select, const bool is_obli) {

	enum {
		ACCEL, FLAT, DE_ACCEL, ENOUGH
	} mode = ACCEL;
	float run_square = 0;		//走行距離の２乗
	float tar_square = distance_m * distance_m;	//目標距離の2乗	毎回計算するの面倒だし長くなるから
	float sign = SIGN(distance_m);		//前進なら1、バックするなら―1
	float ideal_v = mouse::get_ideal_velocity();
	float max_v = ABS(parameter::get_run(select)->max_v) * sign;
	float accel = ABS(parameter::get_run(select)->accel) * sign;
	float de_accel = ABS(parameter::get_run(select)->de_accel) * sign;
	float de_accel_distance = (ideal_v * ideal_v - end_v * end_v)
			/ (2 * de_accel);		//減速に必要な距離
	uint32_t time = mouse::get_count_ms();		//1msに一回だけ処理が回るよう管理するため

	//直前まで壁があってから壁キレを見る　＝　閾値をまたぐのを判断するよう	迷路の中心に近いか遠いか
	enum {
		inner = 0, outer = 1, InOut
	};
	uint8_t cnt[static_cast<int>(PHOTO_TYPE::element_count)][InOut] = { 0 };//今閾値のどっち側にいるかカウントする
	//直前に何ms以上 閾値を超えていれば壁キレが起こると判断するか（値がバラつく対策）
	static const uint8_t w_cnt = 5;

	float Ph2Dis;
	bool safety = false;		//Dutyが100超えると制御できないので、その時は加速を止め落ち着くまで待つ
	COORDINATE now = { 0, 0 };

	//right left front_right, front_left, front
	std::array<float, static_cast<int>(PHOTO_TYPE::element_count)> wall_eage;//この値を超えたら壁キレ
	std::array<float, static_cast<int>(PHOTO_TYPE::element_count)> down_dis;//壁キレ時に区画中心からどの程度ずれているか

	if (is_obli) {
		wall_eage = WALLEAGE_BODOR_OBLI;
		down_dis = DOWN_WALLEAGE_OBLI;
	} else {
		wall_eage = WALLEAGE_BODOR;
		down_dis.at(photo_R) = 0.045 * MOUSE_MODE
				- DOWN_WALLEAGE_DISTANCE.at(photo_R);
		down_dis.at(photo_L) = 0.045 * MOUSE_MODE
				- DOWN_WALLEAGE_DISTANCE.at(photo_L);
	}

	GPIO_SetBits(GPIOC, GPIO_Pin_3);	//LED2
	my7seg::turn_off();

	while (!mouse::get_fail_flag()) {	//フェイルセーフで抜ける
		//1ms経つまで待機		必要ないはずだが、これなくすと壁キレで処理落ちする
		while (time == mouse::get_count_ms())
			;
		time = mouse::get_count_ms();

		//理想速度を取得
		ideal_v = mouse::get_ideal_velocity();

		//直前w_cnt[ms]以上閾値の反対側にいて、このときはじめて閾値を超えたなら
		Ph2Dis = photo::get_displa_from_center(PHOTO_TYPE::right);
		if (cnt[photo_R][inner] >= w_cnt) {
			if ((Ph2Dis < wall_eage.at(photo_R))) {
				mouse::set_relative_go(down_dis.at(photo_R));//区画中央を原点として位置を更新
				cnt[photo_R][inner] = 0;
				GPIO_SetBits(GPIOC, GPIO_Pin_3);			//LED2
			}
		} else if (cnt[photo_R][outer] >= w_cnt) {
			if ((Ph2Dis > wall_eage.at(photo_R))) {
				cnt[photo_R][outer] = 0;
				GPIO_ResetBits(GPIOC, GPIO_Pin_3);	//LED2
			}
		}
		//壁キレを待つ前にそもそも壁キレが起こるのかを判断
		if (Ph2Dis > wall_eage[photo_R]) {
			cnt[photo_R][inner]++;
			cnt[photo_R][outer] = 0;
		} else {
			cnt[photo_R][inner] = 0;
			cnt[photo_R][outer]++;
		}

		Ph2Dis = photo::get_displa_from_center(PHOTO_TYPE::left);
		if (cnt[photo_L][inner] >= w_cnt) {
			if (Ph2Dis > wall_eage[photo_L]) {
				mouse::set_relative_go(down_dis.at(photo_L));//区画中央を原点として位置を更新
				cnt[photo_L][inner] = 0;
				GPIO_SetBits(GPIOC, GPIO_Pin_3);	//LED2
			}
		} else if (cnt[photo_L][outer] >= w_cnt) {
			if (Ph2Dis < wall_eage[photo_L]) {
				cnt[photo_L][outer] = 0;
				GPIO_ResetBits(GPIOC, GPIO_Pin_3);	//LED2
			}
		}
		//壁キレを待つ前にそもそも壁キレが起こるのかを判断
		if (Ph2Dis < wall_eage[photo_L]) {
			cnt[photo_L][inner]++;
			cnt[photo_L][outer] = 0;
		} else {
			cnt[photo_L][inner] = 0;
			cnt[photo_L][outer]++;
		}

		/*
		 if (wall_flag.at(left)) {
		 if (photo::check_wall_edge(left, true))
		 wall_flag.at(left) = false;
		 } else if (photo::wall_edge_down.at(left)
		 > photo::get_displa_from_center(left)) {
		 wall_flag.at(left) = true;
		 }
		 */

		//絶対座標から移動距離を求める
		now = mouse::get_place();
		run_square = (now.x - init.x) * (now.x - init.x);
		run_square += (now.y - init.y) * (now.y - init.y);

		//目標距離走ったら抜ける
		if (tar_square <= run_square)
			break;

		//現在速度から減速にかかる距離を計算
		de_accel_distance = ABS(ideal_v * ideal_v - end_v * end_v)
				/ (2 * de_accel);
		de_accel_distance = ABS(distance_m) - de_accel_distance;//減速を考慮するとどこまで走ってよいのか
		if (run_square >= (de_accel_distance * de_accel_distance))//減速に距離が必要な距離が足りなくなったら減速モードに
			mode = DE_ACCEL;

		switch (mode) {
		case ACCEL: {		//加速
			//duty100%越えたら安全スイッチON
			if (MAX(ABS(motor::get_duty_right()), ABS(motor::get_duty_left()))
					>= 100)
				safety = true;
			if (safety) {
				mouse::set_ideal_accel(0);	//安全スイッチ入ったら加速はやめる
				if (MAX(ABS(motor::get_duty_right()),
						ABS(motor::get_duty_left())) <= 70)	//70%以下に落ち着いたら安全スイッチ解除
					safety = false;
			} else {
				mouse::set_ideal_accel(accel);
			}

			if (0 >= sign * (max_v - ideal_v)) {	//最大速度まで加速していたら
				mouse::set_ideal_accel(0);
				mouse::set_ideal_velocity(max_v);
				mode = FLAT;
			}
			my7seg::light(ACCEL);
			break;
		}
		case FLAT:		//等速			等速から減速への移り変わりは、このswitchの直前でやってる
			mouse::set_ideal_accel(0);
			my7seg::light(FLAT);
			break;

		case DE_ACCEL:		//減速
			mouse::set_ideal_accel(-de_accel);
			if (sign * (ideal_v - end_v) <= 0) {	//終端速度まで減速したら
				mouse::set_ideal_accel(0);
				mouse::set_ideal_velocity(end_v);
				mode = ENOUGH;
			}
			my7seg::light(DE_ACCEL);
			break;

		case ENOUGH:	//速度が先に終端速度になって距離が足りないときに走り切るモード
			mouse::set_ideal_accel(0);
			mouse::set_ideal_velocity(end_v);
			my7seg::light(ENOUGH);
			break;
		}
	}
	mouse::set_ideal_accel(0);
	mouse::set_ideal_velocity(end_v);
	mouse::set_distance_m(0);
}

void run::accel_run_by_distance(const float distance_m,
		const float end_velocity, const COORDINATE init,
		const uint8_t select_mode) {

	float max_velocity = ABS(parameter::get_run(select_mode)->max_v);
	float accel_value = ABS(parameter::get_run(select_mode)->accel);
	float de_accel_value = ABS(parameter::get_run(select_mode)->de_accel);
	float de_accel_distance = ABS(
			mouse::get_ideal_velocity() * mouse::get_ideal_velocity()
			- end_velocity * end_velocity) / (2 * de_accel_value);	//減速に必要な距離

	float run_square = 0;	//走行距離の２乗
	float tar_abs_m = ABS(distance_m);

	uint32_t time = mouse::get_count_ms();

	float sign = 1;
	//バックするなら
	if (distance_m < 0) {
		sign = -1;
		max_velocity *= -1;
		accel_value *= -1;
		de_accel_value *= -1;
		de_accel_distance *= -1;
	}

	//加速
	mouse::set_ideal_accel(accel_value);
	time = mouse::get_count_ms();
	while (0 < sign * (max_velocity - mouse::get_ideal_velocity())) {
		//現在速度から減速にかかる距離を計算
		de_accel_distance = (mouse::get_ideal_velocity()
				* mouse::get_ideal_velocity() - end_velocity * end_velocity)
				/ (2 * de_accel_value);

		//絶対座標から移動距離を求める
		run_square = (mouse::get_place().x - init.x)
				* (mouse::get_place().x - init.x);
		run_square += (mouse::get_place().y - init.y)
				* (mouse::get_place().y - init.y);

		//減速に距離が必要な距離が足りなくなったら抜ける
		if (run_square
				>= (tar_abs_m - de_accel_distance)
						* (tar_abs_m - de_accel_distance)) {
			break;
		}

		if (mouse::get_fail_flag())
			return;
		while (time == mouse::get_count_ms())
			;
		time = mouse::get_count_ms();

	}

	//等速
	mouse::set_ideal_accel(0);

	//現在速度から減速にかかる距離を計算	//等速だから1回計算すればいいよね
	de_accel_distance = (mouse::get_ideal_velocity() - end_velocity)
			* (mouse::get_ideal_velocity() + end_velocity)
			/ (2 * de_accel_value);
	time = mouse::get_count_ms();
	while (1) {

		//絶対座標から移動距離を求める
		run_square = (mouse::get_place().x - init.x)
				* (mouse::get_place().x - init.x);
		run_square += (mouse::get_place().y - init.y)
				* (mouse::get_place().y - init.y);

		//減速に距離が必要な距離が足りなくなったら抜ける
		if (run_square
				>= (tar_abs_m - de_accel_distance)
						* (tar_abs_m - de_accel_distance)) {
			break;
		}

		if (mouse::get_fail_flag())
			return;
		while (time == mouse::get_count_ms())
			;
		time = mouse::get_count_ms();

	}

	//減速
	mouse::set_ideal_accel(-de_accel_value);
	time = mouse::get_count_ms();
	while (sign * (mouse::get_ideal_velocity() - end_velocity) > 0) {
		//絶対座標から移動距離を求める
		run_square = (mouse::get_place().x - init.x)
				* (mouse::get_place().x - init.x);
		run_square += (mouse::get_place().y - init.y)
				* (mouse::get_place().y - init.y);

		//速度より先に距離がなくなったら抜ける
		if (tar_abs_m * tar_abs_m <= run_square)
			break;

		if (mouse::get_fail_flag())
			return;
		while (time == mouse::get_count_ms())
			;
		time = mouse::get_count_ms();

	}

	mouse::set_ideal_accel(0);
	mouse::set_ideal_velocity(end_velocity);

	//速度0だとここに閉じ込められてしまう
	if (sign * end_velocity > 0) {
		//もし速度が先に無くなっても、最後まで走りきるよう
		while (1) {
			//絶対座標から移動距離を求める
			run_square = (mouse::get_place().x - init.x)
					* (mouse::get_place().x - init.x);
			run_square += (mouse::get_place().y - init.y)
					* (mouse::get_place().y - init.y);

			if (tar_abs_m * tar_abs_m <= run_square)
				break;

			if (mouse::get_fail_flag())
				return;
		}

		while (time == mouse::get_count_ms())
			;
		time = mouse::get_count_ms();

	}

	mouse::set_distance_m(0);
}

void run::accel_run_by_place(const COORDINATE finish, const float end_velocity,
		const uint8_t select_mode) {

	COORDINATE init = mouse::get_place();
	float max_velocity = ABS(parameter::get_run(select_mode)->max_v);
	float accel_value = ABS(parameter::get_run(select_mode)->accel);
	float de_accel_value = ABS(parameter::get_run(select_mode)->de_accel);
	float de_accel_distance = ABS(
			mouse::get_ideal_velocity() * mouse::get_ideal_velocity()
			- end_velocity * end_velocity) / (2 * de_accel_value);	//減速に必要な距離

	if (finish.x == 0) {
		if (finish.y == 0) {			//x方向にもy方向にも移動しない場合は距離をリセットして終了
			mouse::set_distance_m(0);
			return;
		}
	}

	float l_square = (finish.x - init.x) * (finish.x - init.x)
			+ (finish.y - init.y) * (finish.y - init.y);//三平方の定理から移動距離の2乗を求める
	float tar_l = my_math::sqrt(l_square);
	float run_square = 0;			//走行距離管理用変数

	//加速
	mouse::set_ideal_accel(accel_value);
	while (mouse::get_ideal_velocity() < max_velocity) {
		//現在速度から減速にかかる距離を計算
		de_accel_distance = (mouse::get_ideal_velocity()
				* mouse::get_ideal_velocity() - end_velocity * end_velocity)
				/ (2 * de_accel_value);

		//絶対座標から移動距離を求める
		run_square = (mouse::get_place().x - init.x)
				* (mouse::get_place().x - init.x);
		run_square += (mouse::get_place().y - init.y)
				* (mouse::get_place().y - init.y);
		//減速に距離が必要な距離が足りなくなったら抜ける
		if (run_square
				>= (tar_l - de_accel_distance) * (tar_l - de_accel_distance)) {
			break;
		}

		if (mouse::get_fail_flag())
			return;
	}

	//等速
	mouse::set_ideal_accel(0);
	while (1) {
		//現在速度から減速にかかる距離を計算
		de_accel_distance = (mouse::get_ideal_velocity()
				* mouse::get_ideal_velocity() - end_velocity * end_velocity)
				/ (2 * de_accel_value);

		//絶対座標から移動距離を求める
		run_square = (mouse::get_place().x - init.x)
				* (mouse::get_place().x - init.x);
		run_square += (mouse::get_place().y - init.y)
				* (mouse::get_place().y - init.y);

		//減速に距離が必要な距離が足りなくなったら抜ける
		if (run_square
				>= (tar_l - de_accel_distance) * (tar_l - de_accel_distance)) {
			break;
		}

		if (mouse::get_fail_flag())
			return;
	}

	//減速
	mouse::set_ideal_accel(-de_accel_value);
	while (mouse::get_ideal_velocity() > end_velocity) {
		//絶対座標から移動距離を求める
		run_square = (mouse::get_place().x - init.x)
				* (mouse::get_place().x - init.x);
		run_square += (mouse::get_place().y - init.y)
				* (mouse::get_place().y - init.y);

		//速度より先に距離がなくなったら抜ける
		if (l_square < run_square) {
			break;
		}

		if (mouse::get_fail_flag())
			return;
	}
	mouse::set_ideal_accel(0);
	mouse::set_ideal_velocity(end_velocity);

	//速度0だとここに閉じ込められてしまう
	if (end_velocity > 0) {
		//もし速度が先に無くなっても、最後まで走りきるよう
		while (l_square > run_square) {
			//絶対座標から移動距離を求める
			run_square = (mouse::get_place().x - init.x)
					* (mouse::get_place().x - init.x);
			run_square += (mouse::get_place().y - init.y)
					* (mouse::get_place().y - init.y);
			if (mouse::get_fail_flag())
				return;
		}
	}

	mouse::set_distance_m(0);
}

void run::fit_run(const unsigned char select_mode) {

	float de_accel_value = ABS(parameter::get_run_de_acceleration(select_mode));
	float diff_front = 0, diff_front_left = 0;
	uint32_t time_count = wait::get_count();
	uint16_t loop_count = 0;

	//ゲイン
	static const PID gain_vel = { 0.2, 0.05, 0 }, gain_ang = { 0, 0, 0 };
	PID diff_vel = { 0 };	//距離の偏差
	PID diff_ang = { 0 };	//角度の偏差

	//減速
	mouse::set_ideal_accel(-de_accel_value);
	while (mouse::get_ideal_velocity() > 0) {		//速度がなくなるまで原則

		//割り込みに組み込むの面倒だから、各ループ1ms待つことで疑似的に制御周期で動かす
		while (time_count == wait::get_count())
			;		//1ms経つまで待つ
		time_count = wait::get_count();		//更新

		//規格化してみた
		//frontの値だけのほうがブレがなくて信用できる
		diff_front = 1
				- static_cast<float>(photo::get_value(PHOTO_TYPE::front))
						/ parameter::get_ideal_photo(PHOTO_TYPE::front);

		//	diff_front_left = 1
		//		- static_cast<float>(photo::get_value(PHOTO_TYPE::front_left))
		//					/ parameter::get_ideal_photo(PHOTO_TYPE::front_left);

		//偏差計算
		diff_vel.P = (diff_front + diff_front_left);
		diff_vel.I += diff_vel.P * 0.001;			//各ループ1msなので
		diff_ang.P = (-diff_front + diff_front_left);
		diff_ang.I += diff_ang.P * 0.001;			//各ループ1msなので

		//滑らかにつながるように、理想速度と前壁制御値が同じくらいの時に移行させる
		if (mouse::get_ideal_velocity()
				< (diff_vel.P * gain_vel.P + diff_vel.I * gain_vel.I))
			break;

		if (mouse::get_fail_flag())
			return;

	}
	mouse::set_ideal_accel(0);
	mouse::set_distance_m(0);

	bool wall_flag = control::get_wall_control_phase();
	control::stop_wall_control();

	while (1) {
		//割り込みに組み込むの面倒だから、各ループ1ms待つことで疑似的に制御周期で動かす
		while (time_count == wait::get_count())
			;			//1ms経つまで待つ
		time_count = wait::get_count();			//更新
		loop_count++;

		//規格化してみた
		//frontの値だけのほうがブレがなくて信用できる
		diff_front = 1
				- static_cast<float>(photo::get_value(PHOTO_TYPE::front))
						/ parameter::get_ideal_photo(PHOTO_TYPE::front);

		//	diff_front_left = 1
		//		- static_cast<float>(photo::get_value(PHOTO_TYPE::front_left))
		//					/ parameter::get_ideal_photo(PHOTO_TYPE::front_left);

		//偏差計算
		diff_vel.P = (diff_front + diff_front_left);
		diff_vel.I += diff_vel.P * 0.001;			//各ループ1msなので
		diff_ang.P = (-diff_front + diff_front_left);
		diff_ang.I += diff_ang.P * 0.001;			//各ループ1msなので


		if(diff_vel.P * gain_vel.P + diff_vel.I * gain_vel.I > SEARCH_VELOCITY)
			mouse::set_ideal_velocity(SEARCH_VELOCITY);
		else if(diff_vel.P * gain_vel.P + diff_vel.I * gain_vel.I < -SEARCH_VELOCITY)
			mouse::set_ideal_velocity(-SEARCH_VELOCITY);
		mouse::set_ideal_velocity(
				diff_vel.P * gain_vel.P + diff_vel.I * gain_vel.I);

		//		mouse::set_ideal_angular_velocity(diff_ang.P * gain_ang.P + diff_ang.I * gain_ang.I );

//		if (ABS(diff_vel.P) < 0.0025)
//			break;
//
//		if (loop_count > 1000)
//			break;

		if (mouse::get_fail_flag())
			return;

//		if (mouse::get_distance_m() > 0.02)
//			break;

	}
	mouse::set_ideal_accel(0);
	mouse::set_ideal_velocity(0);
	mouse::set_distance_m(0);

	run::accel_run(0.02, 0, 0);

	//元々壁制御かかってたなら復活
	if (wall_flag)
		control::start_wall_control();
}

void run::slalom(const SLALOM_TYPE slalom_type, const signed char right_or_left,
		const uint8_t select_mode) {
//スラロームのパラメーター取得
	COORDINATE init = mouse::get_place();
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
	bool is_right = true;
	if (right_or_left == MUKI_LEFT) {
		is_right = false;
		//時計回りが正
		angular_acceleration = -ABS(angular_acceleration);
		max_angular = -ABS(max_angular);
	}

	if (slalom_type == none) {
		return;
	}

	//スラロームの目標角は相対的な角度なので、最初の角度を記録しておく
	float init_angle = mouse::get_angle_degree();
	control::reset_delta(sen_gyro);

	float correct = 0;			//補正項
	if (slalom_type == small) {			//小回りだと前壁補正で距離合わせる
		if (photo::check_wall(PHOTO_TYPE::front)) {
			correct = (photo::get_displa_from_center(PHOTO_TYPE::front));//この関数で死ぬことあり
		}
	}

	if (distance - correct > 0) {	//前距離の分走る
		switch (slalom_type) {
		case big_90:
		case big_180:
		case begin_45:
		case begin_135:
			wall_edge_run_for_slalom(distance, slalom_velocity, select_mode,
					is_right, false, true);
			break;
		case end_45:
		case end_135:
		case oblique_90:
			//√2/4区間を超えると、relative座標で表せないのでその場合ははじく
			if (distance > MOUSE_MODE * 0.0225 * SQRT2)
				run::accel_run_by_distance(distance, slalom_velocity,
						mouse::get_place(), select_mode);
			else
				wall_edge_run_for_slalom(distance, slalom_velocity, select_mode,
						is_right, true, false);
			break;
		default:
			run::accel_run_by_distance(distance - correct, slalom_velocity,
					init, select_mode);
			break;
		}
	}

	control::stop_wall_control();

	mouse::set_ideal_angular_velocity(0);

//角加速区間
	mouse::set_ideal_angular_accel(angular_acceleration);
	while (ABS(mouse::get_angle_degree() - init_angle) < clothoid_angle_degree) {
//フェイルセーフが掛かっていればそこで抜ける
		if (mouse::get_fail_flag()) {
			return;
		}
		//最大角速度に達したら終了
		if (ABS(mouse::get_ideal_angular_velocity()) > ABS(max_angular)) {
			mouse::set_ideal_angular_velocity(max_angular);
			break;
		}
	}

//減速時にも同様の角度がずれると予想されるから
//追従遅れで生じた加速区間の角度の理想と現実の差を記録しておく
	float def_angle = (clothoid_angle_degree
			- ABS(mouse::get_angle_degree() - init_angle));

//等角速度
	mouse::set_ideal_angular_accel(0);

	while (ABS(mouse::get_angle_degree() - init_angle)
			< (target_angle_degree - clothoid_angle_degree)) {
//フェイルセーフが掛かっていればそこで抜ける
		if (mouse::get_fail_flag()) {
			return;
		}

		de_accel_angle = degree(
		//(gyro::get_angular_velocity() * gyro::get_angular_velocity())
				(mouse::get_ideal_angular_velocity()
						* mouse::get_ideal_angular_velocity())
						/ (2 * angular_acceleration));

//減速に必要な角度が残ってなければ抜ける
		//追従遅れのために減速には余分な角度が必要なはず
		if ((ABS(de_accel_angle) + def_angle)
				>= (target_angle_degree
						- ABS(mouse::get_angle_degree() - init_angle))) {
			break;
		}

	}

//角減速区間
	mouse::set_ideal_angular_accel(-angular_acceleration);
	while (ABS(mouse::get_angle_degree() - init_angle) < target_angle_degree) {
		if (ABS(mouse::get_ideal_angular_velocity()) < 0.2) {
			mouse::set_ideal_angular_accel(0);
			if (right_or_left == MUKI_RIGHT) {
				mouse::set_ideal_angular_velocity(0.2);
			} else {
				mouse::set_ideal_angular_velocity(-0.2);
			}
			break;
		}

//フェイルセーフが掛かっていればそこで抜ける
		if (mouse::get_fail_flag()) {
			return;
		}
	}

	mouse::set_ideal_angular_accel(0);
	mouse::set_ideal_angular_velocity(0);

	mouse::turn_direction_slalom(slalom_type, right_or_left);	//マウスの向きを変える

//後ろ距離分走る
	mouse::set_distance_m(0);
	distance = parameter::get_slalom((slalom_type), after_distance,
			right_or_left, select_mode);
	accel_run(distance, slalom_velocity, select_mode);

	if (wall_flag)
		control::start_wall_control();	//もともと壁制御がかかってたら復活させる

	//control::reset_delta(sen_gyro);

}

void run::slalom_for_search(const SLALOM_TYPE slalom_type,
		const signed char right_or_left, const uint8_t select_mode) {

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

	if (slalom_type == none) {
		return;
	}

	//スラロームの目標角は相対的な角度なので、最初の角度を記録しておく
	float init_angle = mouse::get_angle_degree();
	control::reset_delta(sen_gyro);
	float correct = 0;	//補正項
	bool front_b = photo::check_wall(PHOTO_TYPE::front);//ifに直接入れると死ぬことあるので経由する
	if (front_b) {
		correct = (photo::get_displa_from_center(PHOTO_TYPE::front));//この関数で死ぬことあり
		if (correct > 0)
			mouse::set_relative_go(correct - 0.045 * MOUSE_MODE);
		else
			mouse::set_relative_go(correct + 0.045 * MOUSE_MODE);
	}/* else {
	 if (mouse::get_relative_go() > 0) {
	 correct = 0.045 - mouse::get_relative_go();
	 } else {
	 correct = -0.045 - mouse::get_relative_go();
	 }
	 }*/

	if (distance - correct > 0) {	//前距離の分走る
		accel_run(distance - correct, slalom_velocity, select_mode);
	}
	/*else if (distance - correct < -0.045) {	//オーバーし過ぎたときは超信地にする
	 accel_run(distance - correct + 0.045 * MOUSE_MODE, 0, select_mode);
	 mouse::turn_90_dir(right_or_left);	//向きを90°変える
	 //時計回りが正
	 if (right_or_left == MUKI_RIGHT) {
	 run::spin_turn(90);
	 } else {
	 run::spin_turn(-90);
	 }
	 accel_run(0.045 * MOUSE_MODE, slalom_velocity, select_mode);	//半区画前進
	 return;			//スラロームはしないで終了
	 }
	 */

	bool wall_flag = control::get_wall_control_phase();
	control::stop_wall_control();

//時計回りが正
	if (right_or_left == MUKI_LEFT) {
		angular_acceleration = -ABS(angular_acceleration);
		max_angular = -ABS(max_angular);
	}
	mouse::set_ideal_angular_velocity(0);

//角加速区間
	mouse::set_ideal_angular_accel(angular_acceleration);
	while (ABS(mouse::get_angle_degree() - init_angle) < clothoid_angle_degree) {
//フェイルセーフが掛かっていればそこで抜ける
		if (mouse::get_fail_flag()) {
			return;
		}
		//最大角速度に達したら終了
		if (ABS(mouse::get_ideal_angular_velocity()) > ABS(max_angular)) {
			mouse::set_ideal_angular_velocity(max_angular);
			break;
		}
	}

//減速時にも同様の角度がずれると予想されるから
//追従遅れで生じた加速区間の角度の理想と現実の差を記録しておく
	float def_angle = (clothoid_angle_degree
			- ABS(mouse::get_angle_degree() - init_angle));

//等角速度
	mouse::set_ideal_angular_accel(0);

	while (ABS(mouse::get_angle_degree() - init_angle)
			< (target_angle_degree - clothoid_angle_degree)) {
//フェイルセーフが掛かっていればそこで抜ける
		if (mouse::get_fail_flag()) {
			return;
		}

		de_accel_angle = degree(
		//(gyro::get_angular_velocity() * gyro::get_angular_velocity())
				(mouse::get_ideal_angular_velocity()
						* mouse::get_ideal_angular_velocity())
						/ (2 * angular_acceleration));

//減速に必要な角度が残ってなければ抜ける
		//追従遅れのために減速には余分な角度が必要なはず
		if ((ABS(de_accel_angle) + def_angle)
				>= (target_angle_degree
						- ABS(mouse::get_angle_degree() - init_angle))) {
			break;
		}

	}

//角減速区間
	mouse::set_ideal_angular_accel(-angular_acceleration);
	while (ABS(mouse::get_angle_degree() - init_angle) < target_angle_degree) {
		if (ABS(mouse::get_ideal_angular_velocity()) < 0.2) {
			mouse::set_ideal_angular_accel(0);
			if (right_or_left == MUKI_RIGHT)
				mouse::set_ideal_angular_velocity(0.2);
			else
				mouse::set_ideal_angular_velocity(-0.2);
			break;
		}

//フェイルセーフが掛かっていればそこで抜ける
		if (mouse::get_fail_flag()) {
			return;
		}
	}

	mouse::set_ideal_angular_accel(0);
	mouse::set_ideal_angular_velocity(0);

	mouse::turn_direction_slalom(small, right_or_left);	//向きを90°変える
	//マウスの相対座標も変換する
	if (right_or_left == MUKI_LEFT) {		//時計回りが正
		mouse::set_relative_base_rad(slalom_type, false);
	} else {
		mouse::set_relative_base_rad(slalom_type, true);
	}

//後ろ距離分走る
	if (wall_flag)
		control::start_wall_control();		//もともと壁制御がかかってたら復活させる

	mouse::set_distance_m(0);
	distance = parameter::get_slalom((slalom_type), after_distance,
			right_or_left, select_mode);
	accel_run(distance, slalom_velocity, select_mode);

	//TODO スラロームのたびに角速度の偏差をリセットするかは要検討
	//control::reset_delta(sen_gyro);

}

void run::spin_turn(const float target_degree) {
	float max_angular_velocity = 5.0;	//rad/s
	float angular_acceleration = 50.0;	//rad/s^2
	float angle_degree = 0;
	float init_angle = mouse::get_angle_degree();//引数のtarget_degreeは相対的な角度なので、最初の角度を記録しておく
	bool wall_flag = control::get_wall_control_phase();

	float sign = 1;	//目標角度の符号を管理

	control::stop_wall_control();
	wait::ms(200);

	mouse::set_spin_flag(true);	//超信地開始

//時計回りが正
	if (target_degree < 0) {
		angular_acceleration = -ABS(angular_acceleration);
		max_angular_velocity = -ABS(max_angular_velocity);
		sign = -1;
	}

	control::reset_delta(sen_encoder);
	control::reset_delta(sen_gyro);
	mouse::set_ideal_angular_velocity(0);

//角加速区間
	mouse::set_ideal_angular_accel(angular_acceleration);

	while (sign * (mouse::get_angle_degree() - init_angle)
			< ABS(target_degree / 3)) {
		//減速に必要な角度を計算
		angle_degree = degree(
				(mouse::get_ideal_angular_velocity()
						* mouse::get_ideal_angular_velocity())
						/ (2 * angular_acceleration));
		//減速に必要な角度が残ってなければ抜ける
		if (ABS(angle_degree)
				>= sign
						* (target_degree
								- (mouse::get_angle_degree() - init_angle))) {
			break;
		}

		//最大角速度に達したら終了
		if (ABS(
				mouse::get_ideal_angular_velocity()) > ABS(max_angular_velocity)) {
			mouse::set_ideal_angular_velocity(max_angular_velocity);
			break;
		}

		if (mouse::get_fail_flag())
			break;

	}

//等角速度区間
	mouse::set_ideal_angular_accel(0);
	while (1) {
		//減速に必要な角度を計算
		angle_degree = degree(
				(mouse::get_ideal_angular_velocity()
						* mouse::get_ideal_angular_velocity())
						/ (2 * angular_acceleration));
		//減速に必要な角度が残ってなければ抜ける
		if (ABS(angle_degree)
				>= sign
						* (target_degree
								- (mouse::get_angle_degree() - init_angle))) {
			break;
		}

		if (mouse::get_fail_flag())
			break;

	}

//角減速区間
	mouse::set_ideal_angular_accel(-angular_acceleration);
	while (sign * (mouse::get_angle_degree() - init_angle) < ABS(target_degree)) {
		//この条件付けないと、先に角速度が0になった場合いつまでたってもループを抜けない
		if (ABS(mouse::get_ideal_angular_velocity()) < 0.5) {
			mouse::set_ideal_angular_accel(0);
		}

		if (mouse::get_fail_flag())
			break;
	}

	mouse::set_ideal_angular_accel(0);
	mouse::set_ideal_angular_velocity(0);
	mouse::set_distance_m(0);

	wait::ms(300);
	control::reset_delta(sen_gyro);

//もともと壁制御かかってたなら復活させる
	if (wall_flag)
		control::start_wall_control();

	mouse::set_spin_flag(false);	//超信地終了
}

void run::path(const float finish_velocity, const uint8_t _straight,
		const uint8_t _curve) {
	float next_velocity = 0;
	bool naname_flag = false;
	SLALOM_TYPE slalom_type;
	uint8_t slalom_muki;

	for (uint16_t path_count = 0; path::get_path_flag(path_count);
			path_count++) {

		//配列外にでるなら
		if (path_count >= PATH_MAX) {
			break;
		}

		if (mouse::get_fail_flag()) {		//フェイルセーフが掛かっていたら終了
			break;
		}

		mouse::set_distance_m(0);

//直線の処理
		if (path::get_path_straight(path_count) == 0) {		//直線がない場合
			//既に終わってた場合
			if ((path::get_path_flag(path_count)) == false) {
				next_velocity = finish_velocity;
				//例外処理なので最後の直線を走って終わり
				run::accel_run_by_distance(0.045 * MOUSE_MODE, next_velocity,
						mouse::get_place(), _straight);
				break;
			}
		} else {
			//次のパスで終了する場合
			if ((path::get_path_flag(path_count + 1)) == false) {
				if (path::get_path_turn_type(path_count) == none) {	//この直線で最後
					next_velocity = finish_velocity;
					//例外処理なので最後の直線を走って終わり
					run::accel_run_by_distance(
							path::get_path_straight(path_count), next_velocity,
							mouse::get_place(), _straight);
					break;

				} else {
					//次のターン速度に合わせる
					next_velocity = parameter::get_slalom(
							path::get_path_turn_type(path_count), velocity,
							path::get_path_turn_muki(path_count), _curve);

				}

			} else {
				//次のターン速度に合わせる
				next_velocity = parameter::get_slalom(
						path::get_path_turn_type(path_count), velocity,
						path::get_path_turn_muki(path_count), _curve);
			}

			if (naname_flag) {	//ナナメ走行中
				run::accel_run_by_distance(
						path::get_path_straight(path_count) * SQRT2,
						next_velocity, mouse::get_place(), _straight);
			} else {				//普通の直進
				control::start_wall_control();
				//小回りでも壁キレ見るように
				if (path::get_path_turn_type(path_count) == small) {
					if (path::get_path_straight(path_count) != 0) {
						run::accel_run_by_distance(
								path::get_path_straight(
										path_count)-0.045 * MOUSE_MODE,
								next_velocity, mouse::get_place(), _straight);
						run::wall_edge_run_for_slalom(0.035 * MOUSE_MODE,
								next_velocity, _straight, true, false, true);
						run::accel_run(0.010, next_velocity, _straight);
					}
				} else {
					run::accel_run_by_distance(
							path::get_path_straight(path_count), next_velocity,
							mouse::get_place(), _straight);
				}
			}

		}

		if (mouse::get_fail_flag()) {		//フェイルセーフが掛かっていたら終了
			break;
		}

//ターンの処理
		slalom_type = path::get_path_turn_type(path_count);
		slalom_muki = path::get_path_turn_muki(path_count);

		run::slalom(slalom_type, slalom_muki, _curve);

		switch (path::get_path_turn_type(path_count)) {
		//ナナメに入るなら
		case begin_45:
		case begin_135:
			naname_flag = true;
			break;
			//ナナメから出るなら
		case end_45:
		case end_135:
			naname_flag = false;
			break;
		default:
			break;
		}

	}

}

run::run() {
}

run::~run() {
}

signed char adachi::direction_x, adachi::direction_y;

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
		if ((map::get_wall(target_x, target_y, muki) == false)) {		//壁がないなら
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

void adachi::run_next_action(const ACTION_TYPE next_action, bool slalom) {
	static uint8_t str_score = 0;	//壁制御をかけれる直線が何連続したか数える

	//直線でないときは壁制御信用できないのでスコアリセット
	if (next_action != go_straight)
		str_score = 0;

	my7seg::turn_off();


	switch (next_action) {
	case go_straight: {

		//caseに入ってからここにたどり着くまでに止まることがある。
		//1区間直進
		float distance = 0;
		float check_l = 0.08 * MOUSE_MODE;
//		distance = SIGN(mouse::get_relative_go())
//				* (mouse::get_relative_go() - 0.045 * MOUSE_MODE);		//relative_go からずれた分だけ補正
		distance += 0.090 * MOUSE_MODE;
		//FIXME 両壁あり直線が連続すると何故か距離が延びるので適当にへらす
		str_score++;
		if (str_score >= 5) {
			distance -= 0.025;
			check_l = distance - 0.020;
			str_score = 0;

		}
		if (run::wall_edge_run_for_search(distance, SEARCH_VELOCITY, 0,
				check_l)) {
			str_score = 0;		//壁キレ見れたらリセット
		}

		break;
	}
	case turn_right: {
		//スラロームか超信地旋回か
		if (slalom) {
			run::slalom_for_search(small, MUKI_RIGHT, 0);
		} else {
			run::accel_run((0.045 * MOUSE_MODE), 0, 0);
			run::spin_turn(90);
			run::accel_run((0.045 * MOUSE_MODE), SEARCH_VELOCITY, 0);
			mouse::turn_90_dir(MUKI_RIGHT);	//向きを90°変える
		}
		break;
	}
	case turn_left: {
		//スラロームか超信地旋回か
		if (slalom) {
			run::slalom_for_search(small, MUKI_LEFT, 0);
		} else {
			run::accel_run((0.045 * MOUSE_MODE), 0, 0);
			run::spin_turn(270);
			run::accel_run((0.045 * MOUSE_MODE), SEARCH_VELOCITY, 0);
			mouse::turn_90_dir(MUKI_LEFT);	//向きを90°変える
		}
		break;
	}
	case back: {
		//半区間進んで180°ターンして半区間直進

		//前壁があれば前壁制御
		float correct = 0;	//補正項
		//bool check_f = map::get_wall(mouse::get_x_position(),mouse::get_y_position(),mouse::get_compas());

		if (photo::check_wall(PHOTO_TYPE::front)) {
			correct = photo::get_displa_from_center(PHOTO_TYPE::front);	//区画の境目からどれだけずれているか
			if(ABS(correct) > 0.09 * MOUSE_MODE ){
				correct = 0;
				//1区間以上ずれるのはおかしいので、センサ値のミスだと考え何もしない
			}else if (correct > 0){
				mouse::set_relative_go(correct - 0.045 * MOUSE_MODE);
			}else{
				mouse::set_relative_go(correct + 0.045 * MOUSE_MODE);
			}
		}
		if (0.045 * MOUSE_MODE - correct < 0.016)//減速しきる上限を切る　だいたい1/64 2ax=v^2 a=2,v=0.25
			correct = 0.045 * MOUSE_MODE - 0.016;
		run::accel_run((0.045 * MOUSE_MODE) - correct, 0, 0);	//半区間直進

		run::spin_turn(181);// - degree(mouse::get_relative_rad()));//相対角度から上手く合うように変更する
		static flash_maze flash_l;
		static MAP_DATA temp;
		map::output_map_data(&temp);
		flash_l.save_maze(0, &temp);
		mouse::turn_90_dir(MUKI_RIGHT);	//向きを90°変える
		mouse::turn_90_dir(MUKI_RIGHT);	//向きを90°変える
		mouse::set_relative_base_rad(big_180, true);	//180°基準角度変更
		mouse::set_distance_m(0);

		run::accel_run(-(0.025 * MOUSE_MODE), 0, 0);
		run::wall_edge_run_for_slalom(0.04*MOUSE_MODE, SEARCH_VELOCITY, 0, false, false, false);	//0.45にすると条件を抜けない
		run::accel_run((0.005 * MOUSE_MODE), SEARCH_VELOCITY, 0);

		break;
	}
	case stop:
		//半区間進んでストップ
		run::accel_run((0.045 * MOUSE_MODE), 0, 0);	//半区間直進
		break;
	}
	return;
}

void adachi::simulate_next_action(ACTION_TYPE next_action) {
	switch (next_action) {
	case go_straight:
		//1区間直進
		break;

	case turn_right:
		//半区間⇒超信地⇒半区間
		mouse::turn_90_dir(MUKI_RIGHT);	//向きを90°変える
		break;

	case turn_left:
		//半区間⇒超信地⇒半区間
		mouse::turn_90_dir(MUKI_LEFT);	//向きを90°変える
		break;

	case back:
		//半区間進んで180°ターンして半区間直進
		mouse::turn_90_dir(MUKI_RIGHT);	//向きを90°変える
		mouse::turn_90_dir(MUKI_RIGHT);	//向きを90°変える
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

ACTION_TYPE adachi::get_next_action(compas next, compas now) {
	std::pair<int8_t, int8_t> next_dir = compas_to_direction(next);
	std::pair<int8_t, int8_t> now_dir = compas_to_direction(now);

	//nextとnowの内積をとる
	switch (next_dir.first * now_dir.first + next_dir.second * now_dir.second) {
	case 1:		//同じ方向
		return go_straight;
		break;
	case -1:		//逆方向
		return back;
		break;
	case 0:		//左右どちらかのターン
		//回転行列を考えて、0でない成分の符号がどう変化しているかで左右どちらの回転かわかるはず
		if (now_dir.first == 0) {		//xが0の時
			if (next_dir.first * now_dir.second == 1)
				return turn_right;
			else
				return turn_left;
		} else if (now_dir.second == 0) {	//ｙが0の時
			if (next_dir.second * now_dir.first == -1)
				return turn_right;
			else
				return turn_left;
		}
		break;
	}

//ここにたどり着くのは、次行く方向がないか、予期せぬ例外なので、マウスを止める。
	return stop;
}

bool adachi::adachi_method(unsigned char target_x, unsigned char target_y,
		bool is_FULUKAWA) {

	bool adachi_flag = true;	//途中でミスがあったらfalseに
	uint8_t now_x, now_y;	//座標一時保存用。見易さのため
	DIRECTION next_direction, priority_direction;	//次に行く方向を管理
	uint8_t max_unknown_count, target_unknown_count;	//未探索の壁の数を管理
	ACTION_TYPE next_action;	//次の行動を管理

//保存していたマップを読みだす
	map::input_map_data(&mouse::now_map);

//向きを取得
	mouse::get_direction(&direction_x, &direction_y);

	mouse::run_init(true, true);
	my7seg::count_down(3, 500);

	//TODO 最初に後ろ下がってから？
	run::accel_run((0.045 * MOUSE_MODE), SEARCH_VELOCITY, 0);

	while (adachi_flag) {
//フェイルセーフが掛かっていればそこで抜ける
		if (mouse::get_fail_flag()) {
			adachi_flag = false;
			break;
		}
//向きを取得
		mouse::get_direction(&direction_x, &direction_y);

//座標を更新
		now_x = mouse::get_x_position() + direction_x;
		now_y = mouse::get_y_position() + direction_y;
		mouse::set_position(now_x, now_y);

//壁情報更新
		mouse::look_wall(false);

//目標の座標にたどり着いたら終了
		if ((now_x == target_x) && (now_y == target_y)) {
			run_next_action(stop, true);
			break;
		}

//歩数マップ作製
		step::spread_step(target_x, target_y, false);

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
				priority_direction.all = 0;			//他の方向はいらないのでリセット
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
				priority_direction.all = 0;			//他の方向はいらないのでリセット
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
				priority_direction.all = 0;			//他の方向はいらないのでリセット
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
				priority_direction.all = 0;			//他の方向はいらないのでリセット
				priority_direction.element.down = 1;
			}

		}

		//未探索区間が候補の中にあるなら、次に行く方向はその中から選ぶ
		if ((priority_direction.all != 0) && is_FULUKAWA) {
			next_direction.all = priority_direction.all;
		}

//next_dirrctionから次行く方向を選び、行動する
		next_action = get_next_action(next_direction,
				compas_to_muki(mouse::get_compas()));
		run_next_action(next_action, true);
		my7seg::turn_off();

		//もし止まるべきと出たならココで足立法をやめる
		if (next_action == stop) {
			adachi_flag = false;
		}

	}

	if (adachi_flag) {
		//足立法成功なのでマップを保存する
		map::output_map_data(&mouse::now_map);
		return true;			//足立法完了!!

	} else {
//ここに来るということは足立法が失敗してる
		motor::sleep_motor();
		COORDINATE place = mouse::get_place();
		float displace = mouse::get_relative_side();
		float go = mouse::get_relative_go();
//TODO わかりやすい何かが欲しい
		mouse::error();
		myprintf("Adachi method failed!\n\r");
		if (mouse::get_fail_flag()) {
			myprintf("fail safe!\n\r");
		}

		myprintf("now -> (%d,%d)\n\r", mouse::get_x_position(),
				mouse::get_y_position());
		myprintf("place -> (%f,%f)\n\r", place.x, place.y);
		myprintf("relative (displace,go)-> (%f,%f)\n\r", displace, go);
		map::draw_map(false);
	}

	return false;
}

/*
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
 //向きを取得
 mouse::get_direction(&direction_x, &direction_y);

 //座標を更新
 now_x = mouse::get_x_position() + direction_x;
 now_y = mouse::get_y_position() + direction_y;
 mouse::set_position(now_x, now_y);

 //壁情報更新
 mouse::velify_wall();
 mouse::look_wall(false);

 //目標の座標にたどり着いたら終了
 if ((now_x == target_x) && (now_y == target_y)) {
 run_next_action(stop, false);
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
 priority_direction.all = 0;			//他の方向はいらないのでリセット
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
 priority_direction.all = 0;			//他の方向はいらないのでリセット
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
 priority_direction.all = 0;			//他の方向はいらないのでリセット
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
 priority_direction.all = 0;			//他の方向はいらないのでリセット
 priority_direction.element.down = 1;
 }

 }

 //未探索区間が候補の中にあるなら、次に行く方向はその中から選ぶ
 if ((priority_direction.all != 0) && is_FULUKAWA) {
 next_direction.all = priority_direction.all;
 }

 //next_dirrctionから次行く方向を選び、行動する
 next_action = get_next_action(next_direction, mouse::get_direction());
 run_next_action(next_action, false);

 //もし止まるべきと出たならココで足立法をやめる
 if (next_action == stop) {
 adachi_flag = false;
 }

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
 */

/*
 bool adachi::left_hand_method(const uint8_t target_x, const uint8_t target_y) {
 bool search_flag = true;	//途中でミスがあったらfalseに
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

 run_next_action(next_action, true);

 }

 if (mouse::get_fail_flag())
 return false;

 return true;

 }
 */

bool adachi::node_adachi(std::vector<std::pair<uint8_t, uint8_t> > finish,
		weight_algo method) {
	node_search search;

	search.input_map_data(&mouse::now_map);		//保存していたマップを読みだす
	search.set_weight_algo(method);		//重みづけの方法を設定
	search.spread_step(finish, false);		//歩数マップを作製

	bool success_flag = true;		//途中でミスがあったらfalseに
	unsigned char now_x, now_y;		//座標一時保存用。見易さのため
	compas next_compas;		//方角一時保存用。見やすさのため。
	uint16_t next_step = search.init_step;		//次の歩数保存用。見やすさのため。
	ACTION_TYPE next_action;		//次の行動を管理

	my7seg::turn_off();

	search.spread_step(finish, false);		//歩数マップを作製

	mouse::get_direction(&direction_x, &direction_y);		//向きを取得

	mouse::run_init(true, true);

	my7seg::count_down(3, 500);

	run::accel_run((0.045 * MOUSE_MODE), SEARCH_VELOCITY, 0);

	//半区間進んだノードが0なら、目の前のマスがゴールなので終了
	if (search.get_step(now_x, now_y, mouse::get_compas()) == 0) {
		run_next_action(stop, true);
		//足立法成功なのでマップを保存する
		map::output_map_data(&mouse::now_map);
		return true;		//足立法完了!!
	}

	while (success_flag) {
		//フェイルセーフが掛かっていればそこで抜ける
		if (mouse::get_fail_flag()) {
			success_flag = false;
			break;
		}

		//向きを取得
		mouse::get_direction(&direction_x, &direction_y);

		//座標を更新
		now_x = mouse::get_x_position() + direction_x;
		now_y = mouse::get_y_position() + direction_y;
		mouse::set_position(now_x, now_y);

		//壁情報更新
		//mouse::velify_wall();
		mouse::look_wall(false);

		//前回、歩数0に移動していたら終了
		if (next_step == 0) {
			run_next_action(stop, false);
			break;
		}

		//歩数マップ作製
		search.spread_step(finish, false);			//歩数マップを作製

		//最も歩数の小さいノードへ向かう
		next_compas = search.get_min_compas(now_x, now_y);
		next_step = search.get_step(now_x, now_y, next_compas);
		if (next_step == search.init_step) {	//最小歩数が初期値は迷路がふさがれてる
			success_flag = false;
			run_next_action(stop, false);
			break;
		}

		//next_dirrctionから次行く方向を選び、行動する
		next_action = get_next_action(next_compas, mouse::get_compas());
		run_next_action(next_action, true);

		//もし止まるべきと出たならココで足立法をやめる
		if (next_action == stop) {
			success_flag = false;
		}

	}

	if (success_flag) {
		//足立法成功なのでマップを保存する
		map::output_map_data(&mouse::now_map);
		return true;	//足立法完了!!

	} else {
		//ここに来るということは足立法が失敗してる
		COORDINATE fin_pl = mouse::get_place();
		COORDINATE rel_pl;
		rel_pl.x = mouse::get_relative_side();
		rel_pl.y = mouse::get_relative_go();
		motor::sleep_motor();
		//TODO わかりやすい何かが欲しい
		mouse::error();
		myprintf("Adachi method failed!\n\r");
		if (mouse::get_fail_flag()) {
			myprintf("fail safe!\n\r");
		}
		if (next_step == search.init_step) {	//最小歩数が初期値は迷路がふさがれてる
			myprintf("next step is init step %d !\n\r", search.init_step);
			myprintf("	Thus, maze is closed !\n\r");
		}

		myprintf("now -> (%d,%d)\n\r", mouse::get_x_position(),
				mouse::get_y_position());
		myprintf("ABSpostion (x,y)=(%f,%f)\n\r", fin_pl.x, fin_pl.y);
		myprintf("RELpostion (side,go)=(%f,%f)\n\r", rel_pl.x, rel_pl.y);
	}

	return false;

}

adachi::adachi() {
}

adachi::~adachi() {

}

