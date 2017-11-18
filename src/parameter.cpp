/*
 * parameter.cpp
 *
 *  Created on: 2016/10/23
 *      Author: Koizumi
 */

#include"parameter.h"
//ideal_photo[x][y]	xは0がハーフ,1がクラシック	yが光学センサの向きに対応。
//right left front_right front_left,front
const float parameter::ideal_photo[2][5] = { { /*130*/ 12/*14*/, /*200*/ -9, 0, 0, -9/*中心からどれだけオフセットがあるか[mm]*/ },
		{ 3250, 3200, 10815, 10100, 0 } };
const int16_t parameter::min_wall_photo[2][5] = { { 15, 60, 1400, 130, 350 }, {
		20000, 20000, 0, 0, 0 } };

//0番目は探索用
//				普通							斜め
//		加速度、最高速、減速度、		加速度、最高速、減速度
const TRAPEZOID parameter::straight_run[RUN_MODE_NUMBER] = {
		{ 3.0, SEARCH_VELOCITY, 3.0, 3.0, SEARCH_VELOCITY, 3.0 },
		{ 3.0, 0.5, 3.0, 3.0, 0.5, 3.0 },
		{ 3.0, 1.0, 3.0, 3.0, 0.5, 3.0 },
		{ 5.0, 1.5, 5.0, 3.0, 1.0, 3.0 },
		{ 6.0, 2.0, 6.0, 6.0, 1.0, 6.0 } };

//XXX スラロームパラメータ
//速度、角度、加速角度、前距離、後ろ距離、角加速度、最高角速度
//小回り90°ターン
const std::array<INIT_SLALOM, 2> right_small_half = { {
		{ SEARCH_VELOCITY, 91, 30, 0.008, 0.016, 162.2157, 13.0335, 0 },
		{ 0.35, 91, 30, 0.007, 0.008, 171.1409, 15.45826, 0 }, } };
const std::array<INIT_SLALOM, 2> left_small_half = { {
		{ SEARCH_VELOCITY, 89.6, 30, 0.009, 0.005, 119.1789, 11.17156, 0 },
		{ 0.35, 90, 30, 0.01, 0.07, 171.1409, 15.45826, 0 } } };

//大まわり90°ターン
const std::array<INIT_SLALOM, 2> right_big90_half = { {
		{ 0.5, 91.5, 30, 0.018, 0.019, 119.1789, 11.17156, 0 },
		{ 0.6, 91.5, 30, 0.015, 0.025, 149.4980, 12.51215, 0 },
} };
const std::array<INIT_SLALOM, 2> left_big90_half = { {
		{ 0.5, 90, 30, 0.020, 0.016, 112.6498, 10.86124, 0 },
		{ 0.6, 89, 30, 0.010, 0.03, 149.4980, 12.51215, 0 },
} };

//大まわり180°ターン
const std::array<INIT_SLALOM, 1> right_big180_half ={ {
		{ 0.5, 181, 38, 0.020, 0.027, 94.5770, 11.49152, 0 },
//		{ 0.6, 180, 40, 0.020, 0.040, 148.5666, 14.40271, 0 },
} };
const std::array<INIT_SLALOM, 1> left_big180_half ={ {
		{ 0.5, 180, 40, 0.020, 0.008, 98.73437, 11.74134, 0 },
//		{ 0.6, 180, 40, 0.020, 0.030, 148.5666, 14.40271, 0 },
} };

//入り45°ターン
const std::array<INIT_SLALOM, 1> right_begin45_half = { {
		{ 0.5, 46, 20, 0.005, 0.030, 195.0775, 11.67003, 0 },
} };
const std::array<INIT_SLALOM, 1> left_begin45_half = { {
		{ 0.5, 44.6, 20, 0.011, 0.033, 195.0775, 11.67003, 0 },
} };

//出の45°ターン
const std::array<INIT_SLALOM, 1> right_end45_half = { {
		{ 0.5, 46, 20, 0.045, 0.007, 195.0775, 11.67003, 0 },
} };
const std::array<INIT_SLALOM, 1> left_end45_half = { {
		{ 0.5, 45, 20, 0.040, 0.036, 195.0775, 11.67003, 0 },
} };

//入り135°ターン
const std::array<INIT_SLALOM, 1> right_begin135_half = { {
		{ 0.5, 135.5, 45, 0.017, 0.017, 141.1387, 14.89, 0 },
} };
const std::array<INIT_SLALOM, 1> left_begin135_half = { {
		{ 0.5, 136.5, 45, 0.025, 0.005, 141.1387, 14.89, 0 },
} };

//出の135°ターン
const std::array<INIT_SLALOM, 1> right_end135_half = { {
		{ 0.5, 136, 45, 0.020, 0.030, 141.1387, 14.89, 0 },
} };
const std::array<INIT_SLALOM, 1> left_end135_half = { {
		{ 0.5, 134.8, 45, 0.025, 0.031, 141.1387, 14.89, 0 },
} };

//ななめ90°ターン
const std::array<INIT_SLALOM, 1> right_obli90_half = { {
		{ 0.5, 90.5, 40, 0.003, 0.008, 162.5137, 15.0636, 0 },
} };
const std::array<INIT_SLALOM, 1> left_obli90_half = { {
		{ 0.5, 89.5, 40, 0.005, 0.007, 162.5137, 15.0636, 0 },
} };


float parameter::get_run_acceleration(const uint8_t _select_mode) {
	if (_select_mode >= RUN_MODE_NUMBER) {			//存在しないモードを選択したらエラー
		mouse::error();
		myprintf("存在しない走行モード[%d]の加速度を選択しています!!", _select_mode);
		return 0;
	}
	return straight_run[_select_mode].accel;
}

float parameter::get_ideal_photo(const PHOTO_TYPE _type) {

	switch (_type) {
	case PHOTO_TYPE::right:
	case PHOTO_TYPE::left:
	case PHOTO_TYPE::front_right:
	case PHOTO_TYPE::front_left:
	case PHOTO_TYPE::front:
		break;
	default:
		return 0;
		break;
	}
	return ideal_photo[MOUSE_MODE - 1][static_cast<int>(_type)];
}

int16_t parameter::get_min_wall_photo(const PHOTO_TYPE _type) {
	switch (_type) {
	case PHOTO_TYPE::right:
	case PHOTO_TYPE::left:
	case PHOTO_TYPE::front_right:
	case PHOTO_TYPE::front_left:
	case PHOTO_TYPE::front:
		break;

	default:
		return 0;
		break;
	}
	return min_wall_photo[MOUSE_MODE - 1][static_cast<int>(_type)];
}

float parameter::get_run_max_velocity(const uint8_t _select_mode) {
	if (_select_mode >= RUN_MODE_NUMBER) {			//存在しないモードを選択したらエラー
		mouse::error();
		myprintf("存在しない走行モード[%d]の最高速度を選択しています!!", _select_mode);
		return 0;
	}
	return straight_run[_select_mode].max_v;
}

float parameter::get_run_de_acceleration(const uint8_t _select_mode) {
	if (_select_mode >= RUN_MODE_NUMBER) {			//存在しないモードを選択したらエラー
		mouse::error();
		myprintf("存在しない走行モード[%d]の減速度を選択しています!!", _select_mode);
		return 0;
	}
	return straight_run[_select_mode].de_accel;
}

const TRAPEZOID* const parameter::get_run(uint8_t _select_mode){
	if (_select_mode >= RUN_MODE_NUMBER) {			//存在しないモードを選択したらエラー
		mouse::error();
		myprintf("存在しない走行モード[%d]を選択しています!!", _select_mode);
		return &straight_run[0];
	}
	return &straight_run[_select_mode];
}


float parameter::get_slalom(const SLALOM_TYPE slalom_type,
		const SLALOM_ELEMENT slalom_element, const signed char right_or_left,
		const unsigned char select_mode) {
	const INIT_SLALOM* tar;
	bool isR = true;
	if (right_or_left == MUKI_LEFT)
		isR = false;
	tar = get_slalom_p(slalom_type, isR, select_mode);

	switch (slalom_element) {
	case velocity:
		return tar->velocity;
	case target_angle:
		return tar->target_angle;
	case clothoid_angle:
		return tar->clothoid_angle;
	case before_distance:
		return tar->before_distance;
	case after_distance:
		return tar->after_distance;
	case angular_accel:
		return tar->angular_accel;
	case max_angular_velocity:
		return tar->max_angular_velocity;
	case time:
		return tar->time;
	}
	return 0;
}

const INIT_SLALOM* const parameter::get_slalom_p(const SLALOM_TYPE _type,
		bool _is_right, uint8_t _mode) {
	switch (_type) {
	case none:
		break;
	case small:
		if (_is_right) {
			if (MOUSE_MODE == 1) {
				if (_mode >= right_small_half.size())		//配列外アクセス時は最大のを返す
					return &right_small_half.back();
				else
					return &right_small_half.at(_mode);
			}
		} else {
			if (MOUSE_MODE == 1) {
				if (_mode >= left_small_half.size())		//配列外アクセス時は最大のを返す
					return &left_small_half.back();
				else
					return &left_small_half.at(_mode);
			}
		}
		break;
	case big_90:
		if (_is_right) {
			if (MOUSE_MODE == 1) {
				if (_mode >= right_big90_half.size())		//配列外アクセス時は最大のを返す
					return &right_big90_half.back();
				else
					return &right_big90_half.at(_mode);
			}
		} else {
			if (MOUSE_MODE == 1) {
				if (_mode >= left_big90_half.size())		//配列外アクセス時は最大のを返す
					return &left_big90_half.back();
				else
					return &left_big90_half.at(_mode);
			}
		}
		break;
	case big_180:
		if (_is_right) {
			if (MOUSE_MODE == 1) {
				if (_mode >= right_big180_half.size())		//配列外アクセス時は最大のを返す
					return &right_big180_half.back();
				else
					return &right_big180_half.at(_mode);
			}
		} else {
			if (MOUSE_MODE == 1) {
				if (_mode >= left_big180_half.size())		//配列外アクセス時は最大のを返す
					return &left_big180_half.back();
				else
					return &left_big180_half.at(_mode);
			}
		}
		break;
	case begin_45:
		if (_is_right) {
			if (MOUSE_MODE == 1) {
				if (_mode >= right_begin45_half.size())		//配列外アクセス時は最大のを返す
					return &right_begin45_half.back();
				else
					return &right_begin45_half.at(_mode);
			}
		} else {
			if (MOUSE_MODE == 1) {
				if (_mode >= left_begin45_half.size())		//配列外アクセス時は最大のを返す
					return &left_begin45_half.back();
				else
					return &left_begin45_half.at(_mode);
			}
		}
		break;
	case end_45:
		if (_is_right) {
			if (MOUSE_MODE == 1) {
				if (_mode >= right_end45_half.size())		//配列外アクセス時は最大のを返す
					return &right_end45_half.back();
				else
					return &right_end45_half.at(_mode);
			}
		} else {
			if (MOUSE_MODE == 1) {
				if (_mode >= left_end45_half.size())		//配列外アクセス時は最大のを返す
					return &left_end45_half.back();
				else
					return &left_end45_half.at(_mode);
			}
		}
		break;
	case begin_135:
		if (_is_right) {
			if (MOUSE_MODE == 1) {
				if (_mode >= right_big90_half.size())		//配列外アクセス時は最大のを返す
					return &right_begin135_half.back();
				else
					return &right_begin135_half.at(_mode);
			}
		} else {
			if (MOUSE_MODE == 1) {
				if (_mode >= left_begin135_half.size())		//配列外アクセス時は最大のを返す
					return &left_begin135_half.back();
				else
					return &left_begin135_half.at(_mode);
			}
		}
		break;
	case end_135:
		if (_is_right) {
			if (MOUSE_MODE == 1) {
				if (_mode >= right_end135_half.size())		//配列外アクセス時は最大のを返す
					return &right_end135_half.back();
				else
					return &right_end135_half.at(_mode);
			}
		} else {
			if (MOUSE_MODE == 1) {
				if (_mode >= left_end135_half.size())		//配列外アクセス時は最大のを返す
					return &left_end135_half.back();
				else
					return &left_end135_half.at(_mode);
			}
		}
		break;
	case oblique_90:
		if (_is_right) {
			if (MOUSE_MODE == 1) {
				if (_mode >= right_obli90_half.size())		//配列外アクセス時は最大のを返す
					return &right_obli90_half.back();
				else
					return &right_obli90_half.at(_mode);
			}
		} else {
			if (MOUSE_MODE == 1) {
				if (_mode >= left_obli90_half.size())		//配列外アクセス時は最大のを返す
					return &left_obli90_half.back();
				else
					return &left_obli90_half.at(_mode);
			}
		}
		break;
	default:
		break;
	}

	INIT_SLALOM temp = { 0 };
	return &temp;
}

