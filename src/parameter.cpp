/*
 * parameter.cpp
 *
 *  Created on: 2016/10/23
 *      Author: Koizumi
 */

#include"parameter.h"
//ideal_photo[x][y]	xは0がハーフ,1がクラシック	yが光学センサの向きに対応。
//right left front_right front_left,front
const unsigned int parameter::ideal_photo[2][5] = { { 400, 680, 10000, 300, 0 },
		{ 3250, 3200, 10815, 10100, 0 } };
const int16_t parameter::min_wall_photo[2][5] = { { 370, 600, 0, 250, 900 },
		{ 20000, 2000, 0, 0, 0 } };

//0番目は探索用
const TRAPEZOID parameter::straight_run[RUN_MODE_NUMBER] = { { 2.0,
		SEARCH_VELOCITY, 2.0 }, { 2.0, 2.0, 2.0 }, { 2.0, 2.0, 2.0 } };

const INIT_SLALOM parameter::right_slalom[RUN_MODE_NUMBER] = { 0 };
const INIT_SLALOM parameter::left_slalom[RUN_MODE_NUMBER] = { 0 };

float parameter::get_run_acceleration(const unsigned char select_mode) {
	if (select_mode >= RUN_MODE_NUMBER) {			//存在しないモードを選択したらエラー
		mouse::error();
		myprintf("存在しない走行モード[%d]の加速度を選択しています!!", select_mode);
		return 0;
	}
	return straight_run[select_mode].acceleration;
}

unsigned int parameter::get_ideal_photo(PHOTO_TYPE photo_type) {
	switch (photo_type) {
	case right:
		return ideal_photo[MOUSE_MODE - 1][right];
		break;

	case left:
		return ideal_photo[MOUSE_MODE - 1][left];
		break;

	case front_right:
		return ideal_photo[MOUSE_MODE - 1][front_right];
		break;

	case front_left:
		return ideal_photo[MOUSE_MODE - 1][front_left];
		break;

	case front:
		return ideal_photo[MOUSE_MODE - 1][front];
		break;

	}

	return 0;
}

int16_t parameter::get_min_wall_photo(PHOTO_TYPE photo_type) {
	switch (photo_type) {
	case right:
		return min_wall_photo[MOUSE_MODE - 1][right];
		break;

	case left:
		return min_wall_photo[MOUSE_MODE - 1][left];
		break;

	case front_right:
		return min_wall_photo[MOUSE_MODE - 1][front_right];
		break;

	case front_left:
		return min_wall_photo[MOUSE_MODE - 1][front_left];
		break;

	case front:
		return min_wall_photo[MOUSE_MODE - 1][front];
		break;
	}

	return 0;
}

float parameter::get_run_max_velocity(const unsigned char select_mode) {
	if (select_mode >= RUN_MODE_NUMBER) {			//存在しないモードを選択したらエラー
		mouse::error();
		myprintf("存在しない走行モード[%d]の最高速度を選択しています!!", select_mode);
		return 0;
	}
	return straight_run[select_mode].max_velocity;
}

float parameter::get_run_de_acceleration(const unsigned char select_mode) {
	if (select_mode >= RUN_MODE_NUMBER) {			//存在しないモードを選択したらエラー
		mouse::error();
		myprintf("存在しない走行モード[%d]の減速度を選択しています!!", select_mode);
		return 0;
	}
	return straight_run[select_mode].de_acceleration;
}

float parameter::get_slalom_para(const SLALOM_ELEMENT slalom_element,
		const int8_t right_or_left, const uint8_t select_mode) {

	if (select_mode >= RUN_MODE_NUMBER) {			//存在しないモードを選択したらエラー
		mouse::error();
		myprintf("存在しない走行モード[%d]のスラローム要素を参照しています!!", select_mode);
		return 0;
	}

	switch (slalom_element) {
	case velocity:
		if (right_or_left == MUKI_RIGHT) {
			return right_slalom[select_mode].velocity;
		} else {
			return left_slalom[select_mode].velocity;
		}
		break;

	case target_angle:
		if (right_or_left == MUKI_RIGHT) {
			return right_slalom[select_mode].target_angle;
		} else {
			return left_slalom[select_mode].target_angle;
		}
		break;

	case clothoid_angle:
		if (right_or_left == MUKI_RIGHT) {
			return right_slalom[select_mode].clothoid_angle;
		} else {
			return left_slalom[select_mode].clothoid_angle;
		}
		break;

	case before_distance:
		if (right_or_left == MUKI_RIGHT) {
			return right_slalom[select_mode].before_distance;
		} else {
			return left_slalom[select_mode].before_distance;
		}
		break;

	case after_distance:
		if (right_or_left == MUKI_RIGHT) {
			return right_slalom[select_mode].after_distance;
		} else {
			return left_slalom[select_mode].after_distance;
		}
		break;

	case angular_accel:
		if (right_or_left == MUKI_RIGHT) {
			return right_slalom[select_mode].angular_accel;
		} else {
			return left_slalom[select_mode].angular_accel;
		}
		break;

	case time:
		if (right_or_left == MUKI_RIGHT) {
			return right_slalom[select_mode].time;
		} else {
			return left_slalom[select_mode].time;
		}
		break;
	}

	return 0;
}

