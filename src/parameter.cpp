/*
 * parameter.cpp
 *
 *  Created on: 2016/10/23
 *      Author: Koizumi
 */

#include"parameter.h"
//ideal_photo[x][y]	xは0がハーフ,1がクラシック	yが光学センサの向きに対応。
//right left front_right front_left,front
const unsigned int parameter::ideal_photo[2][5] = { { 120, 250, 0, 1900, 480 },
		{ 3250, 3200, 10815, 10100, 0 } };
const int16_t parameter::min_wall_photo[2][5] = { { 40, 80, 1400, 130, 200 }, {
		20000, 20000, 0, 0, 0 } };

//0番目は探索用
const TRAPEZOID parameter::straight_run[RUN_MODE_NUMBER] = {
		{ 3.0, SEARCH_VELOCITY, 3.0 },
		{ 5.0, 1, 5.0 },
		{ 5.0, 1.5, 5.0 },
		{ 8.0, 2, 5.0 },
		{ 10.0, 2, 8.0 } };

//XXX スラロームパラメータ
//速度、角度、加速角度、前距離、後ろ距離、角加速度、最高角速度
//小回り90°ターン
const std::array<INIT_SLALOM, 2> right_small_half = { {
		{ SEARCH_VELOCITY, 91, 30, 0.010, 0.007, 119.1789, 11.17156, 0 },
		{ 0.35, 91, 30, 0.01, 0.01, 171.1409, 15.45826, 0 }, } };
const std::array<INIT_SLALOM, 2> left_small_half = { {
		{ SEARCH_VELOCITY, 90.5, 30, 0.01, 0.017, 119.1789, 11.17156, 0 },
		{ 0.35, 90, 30, 0.01, 0.01, 171.1409, 15.45826, 0 } } };

//大まわり90°ターン
const std::array<INIT_SLALOM, 3> right_big90_half = { {
		{ 0.5, 91.5, 30, 0.030, 0.033, 119.1789, 11.17156, 0 },
		{ 0.5, 91.5, 30, 0.030, 0.033, 119.1789, 11.17156, 0 },
		{ 0.6, 91.5, 30, 0.023, 0.033, 149.4980, 12.51215, 0 },
} };
const std::array<INIT_SLALOM, 3> left_big90_half = { {
		{ 0.5, 89, 30, 0.027, 0.03, 112.6498, 10.86124, 0 },
		{ 0.5, 89, 30, 0.027, 0.03, 112.6498, 10.86124, 0 },
		{ 0.6, 89, 30, 0.015, 0.03, 149.4980, 12.51215, 0 },
} };

//大まわり180°ターン
const std::array<INIT_SLALOM, 3> right_big180_half ={ {
		{ 0.5, 182, 40, 0.020, 0.030, 83.56877, 10.80203, 0 },
		{ 0.5, 182, 40, 0.020, 0.030, 83.56877, 10.80203, 0 },
		{ 0.6, 180, 40, 0.020, 0.040, 148.5666, 14.40271, 0 },
} };
const std::array<INIT_SLALOM, 3> left_big180_half ={ {
		{ 0.5, 180, 40, 0.020, 0.020, 98.73437, 11.74134, 0 },
		{ 0.5, 180, 40, 0.020, 0.020, 98.73437, 11.74134, 0 },
		{ 0.6, 180, 40, 0.020, 0.030, 148.5666, 14.40271, 0 },
} };

//入り45°ターン
const std::array<INIT_SLALOM, 1> right_begin45_half = { {
		{ 0.5, 45.8, 20, 0.020, 0.025, 195.0775, 11.67003, 0 },
} };
const std::array<INIT_SLALOM, 1> left_begin45_half = { {
		{ 0.5, 45, 20, 0.012, 0.03064, 195.0775, 11.67003, 0 },
} };

//出の45°ターン
const std::array<INIT_SLALOM, 1> right_end45_half = { {
		{ 0.5, 45.8, 20, 0.035, 0.014, 195.0775, 11.67003, 0 },
} };
const std::array<INIT_SLALOM, 1> left_end45_half = { {
		{ 0.5, 45, 20, 0.03064, 0.012, 195.0775, 11.67003, 0 },
} };

//入り135°ターン
const std::array<INIT_SLALOM, 1> right_begin135_half = { {
		{ 0.5, 136, 45, 0.024, 0.022, 141.1387, 14.89, 0 },
} };
const std::array<INIT_SLALOM, 1> left_begin135_half = { {
		{ 0.5, 136, 45, 0.02, 0.01228, 141.1387, 14.89, 0 },
} };

//出の135°ターン
const std::array<INIT_SLALOM, 1> right_end135_half = { {
		{ 0.5, 136, 45, 0.016, 0.028, 141.1387, 14.89, 0 },
} };
const std::array<INIT_SLALOM, 1> left_end135_half = { {
		{ 0.5, 135, 45, 0.016, 0.028, 141.1387, 14.89, 0 },
} };

//ななめ90°ターン
const std::array<INIT_SLALOM, 1> right_obli90_half = { {
		{ 0.5, 90, 40, 0.005, 0.005, 162.5137, 15.0636, 0 },
} };
const std::array<INIT_SLALOM, 1> left_obli90_half = { {
		{ 0.5, 90, 40, 0.005, 0.005, 162.5137, 15.0636, 0 },
} };


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

	default:
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

	default:
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

float parameter::get_slalom(const SLALOM_TYPE slalom_type,
		const SLALOM_ELEMENT slalom_element, const signed char right_or_left,
		const unsigned char select_mode) {
	const INIT_SLALOM* tar;

	if (right_or_left == MUKI_RIGHT)
		tar = get_slalom(slalom_type, true, select_mode);
	else
		tar = get_slalom(slalom_type, false, select_mode);

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

	/*
	 if (select_mode >= RUN_MODE_NUMBER) {			//存在しないモードを選択したらエラー
	 mouse::error();
	 myprintf("存在しない走行モード[%d]のスラローム要素を参照しています!!", select_mode);
	 return 0;
	 }

	 //クラシックなら
	 if (MOUSE_MODE == 2) {
	 switch (slalom_element) {
	 case velocity:
	 if (right_or_left == MUKI_RIGHT) {
	 return right_slalom[slalom_type][select_mode].velocity;
	 } else {
	 return left_slalom[slalom_type][select_mode].velocity;
	 }
	 break;

	 case target_angle:
	 if (right_or_left == MUKI_RIGHT) {
	 return right_slalom[slalom_type][select_mode].target_angle;
	 } else {
	 return left_slalom[slalom_type][select_mode].target_angle;
	 }
	 break;

	 case clothoid_angle:
	 if (right_or_left == MUKI_RIGHT) {
	 return right_slalom[slalom_type][select_mode].clothoid_angle;
	 } else {
	 return left_slalom[slalom_type][select_mode].clothoid_angle;
	 }
	 break;

	 case before_distance:
	 if (right_or_left == MUKI_RIGHT) {
	 return right_slalom[slalom_type][select_mode].before_distance;
	 } else {
	 return left_slalom[slalom_type][select_mode].before_distance;
	 }
	 break;

	 case after_distance:
	 if (right_or_left == MUKI_RIGHT) {
	 return right_slalom[slalom_type][select_mode].after_distance;
	 } else {
	 return left_slalom[slalom_type][select_mode].after_distance;
	 }
	 break;

	 case angular_accel:
	 if (right_or_left == MUKI_RIGHT) {
	 return right_slalom[slalom_type][select_mode].angular_accel;
	 } else {
	 return left_slalom[slalom_type][select_mode].angular_accel;
	 }
	 break;

	 case max_angular_velocity:
	 if (right_or_left == MUKI_RIGHT) {
	 return right_slalom[slalom_type][select_mode].max_angular_velocity;
	 } else {
	 return left_slalom[slalom_type][select_mode].max_angular_velocity;
	 }
	 break;

	 case time:
	 if (right_or_left == MUKI_RIGHT) {
	 return right_slalom[slalom_type][select_mode].time;
	 } else {
	 return left_slalom[slalom_type][select_mode].time;
	 }
	 break;
	 }

	 //ハーフなら
	 } else {
	 switch (slalom_element) {
	 case velocity:
	 if (right_or_left == MUKI_RIGHT) {
	 return right_slalom_half[slalom_type][select_mode].velocity;
	 } else {
	 return left_slalom_half[slalom_type][select_mode].velocity;
	 }
	 break;

	 case target_angle:
	 if (right_or_left == MUKI_RIGHT) {
	 return right_slalom_half[slalom_type][select_mode].target_angle;
	 } else {
	 return left_slalom_half[slalom_type][select_mode].target_angle;
	 }
	 break;

	 case clothoid_angle:
	 if (right_or_left == MUKI_RIGHT) {
	 return right_slalom_half[slalom_type][select_mode].clothoid_angle;
	 } else {
	 return left_slalom_half[slalom_type][select_mode].clothoid_angle;
	 }
	 break;

	 case before_distance:
	 if (right_or_left == MUKI_RIGHT) {
	 return right_slalom_half[slalom_type][select_mode].before_distance;
	 } else {
	 return left_slalom_half[slalom_type][select_mode].before_distance;
	 }
	 break;

	 case after_distance:
	 if (right_or_left == MUKI_RIGHT) {
	 return right_slalom_half[slalom_type][select_mode].after_distance;
	 } else {
	 return left_slalom_half[slalom_type][select_mode].after_distance;
	 }
	 break;

	 case angular_accel:
	 if (right_or_left == MUKI_RIGHT) {
	 return right_slalom_half[slalom_type][select_mode].angular_accel;
	 } else {
	 return left_slalom_half[slalom_type][select_mode].angular_accel;
	 }
	 break;

	 case max_angular_velocity:
	 if (right_or_left == MUKI_RIGHT) {
	 return right_slalom_half[slalom_type][select_mode].max_angular_velocity;
	 } else {
	 return left_slalom_half[slalom_type][select_mode].max_angular_velocity;
	 }
	 break;

	 case time:
	 if (right_or_left == MUKI_RIGHT) {
	 return right_slalom_half[slalom_type][select_mode].time;
	 } else {
	 return left_slalom_half[slalom_type][select_mode].time;
	 }
	 break;
	 }

	 }
	 */
	return 0;
}

const INIT_SLALOM* const parameter::get_slalom(const SLALOM_TYPE _type,
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
	}

	INIT_SLALOM temp = { 0 };
	return &temp;
}

