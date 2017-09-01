/*
 * parameter.cpp
 *
 *  Created on: 2016/10/23
 *      Author: Koizumi
 */

#include"parameter.h"
//ideal_photo[x][y]	x��0���n�[�t,1���N���V�b�N	y�����w�Z���T�̌����ɑΉ��B
//right left front_right front_left,front
const unsigned int parameter::ideal_photo[2][5] = { { 190, 300, 0, 1900, 400 },
		{ 3250, 3200, 10815, 10100, 0 } };
const int16_t parameter::min_wall_photo[2][5] = { { 45, 100, 1400, 130, 200 }, {
		20000, 20000, 0, 0, 0 } };

//0�Ԗڂ͒T���p
const TRAPEZOID parameter::straight_run[RUN_MODE_NUMBER] = { { 2.0,
SEARCH_VELOCITY, 2.0 }, { 5.0, SEARCH_VELOCITY * 2, 5.0 }, { 10.0,
SEARCH_VELOCITY * 2, 10.0 }, { 5.0,
SEARCH_VELOCITY * 3, 5.0 }, { 0 } };

const INIT_SLALOM parameter::right_slalom[slalom_type_count][RUN_MODE_NUMBER] =
		{
				0
		};

const INIT_SLALOM parameter::left_slalom[slalom_type_count][RUN_MODE_NUMBER] = {
		0 };

//�X�����[���v�f
//���x�A�p�x�A�����p�x�A�O�����A��닗���A�p�����x�A�ō��p���x
const INIT_SLALOM parameter::right_slalom_half[slalom_type_count][RUN_MODE_NUMBER] =
		{ { { 0 } },	//none
				{ { SEARCH_VELOCITY, 91, 30, 0.005, 0.01, 119.1789, 11.17156, 0 },
						{ SEARCH_VELOCITY, 90, 30, 0.005, 0.01, 121.389, 11.275,
								0 },
//				{ { SEARCH_VELOCITY, 90, 30, 0.01, 0.005, 92.939, 9.865, 0 }, { 0 },
						{ SEARCH_VELOCITY, 90, 30, 0.005, 0.08, 121.389, 11.275,
								0 }, { SEARCH_VELOCITY, 90, 30, 0.005, 0.01,
								121.389, 11.275, 0 }, { 0 } }	//small
		};

const INIT_SLALOM parameter::left_slalom_half[slalom_type_count][RUN_MODE_NUMBER] =
		{ { { 0 } },	//none
				{ { SEARCH_VELOCITY, 90, 30, 0.01, 0.01, 119.1789, 11.17156, 0 },
						{ SEARCH_VELOCITY, 90, 30, 0.009, 0.01, 121.389, 11.275,
								0 },
						//			{ { SEARCH_VELOCITY, 90, 30, 0.01, 0.005, 92.939, 9.865, 0 }, { 0 },
						{ SEARCH_VELOCITY, 90, 30, 0.009, 0.01, 121.389, 11.275,
								0 }, { SEARCH_VELOCITY, 90, 30, 0.009, 0.01,
								121.389, 11.275, 0 }, { 0 } }	//small
		};

float parameter::get_run_acceleration(const unsigned char select_mode) {
	if (select_mode >= RUN_MODE_NUMBER) {			//���݂��Ȃ����[�h��I��������G���[
		mouse::error();
		myprintf("���݂��Ȃ����s���[�h[%d]�̉����x��I�����Ă��܂�!!", select_mode);
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
	if (select_mode >= RUN_MODE_NUMBER) {			//���݂��Ȃ����[�h��I��������G���[
		mouse::error();
		myprintf("���݂��Ȃ����s���[�h[%d]�̍ō����x��I�����Ă��܂�!!", select_mode);
		return 0;
	}
	return straight_run[select_mode].max_velocity;
}

float parameter::get_run_de_acceleration(const unsigned char select_mode) {
	if (select_mode >= RUN_MODE_NUMBER) {			//���݂��Ȃ����[�h��I��������G���[
		mouse::error();
		myprintf("���݂��Ȃ����s���[�h[%d]�̌����x��I�����Ă��܂�!!", select_mode);
		return 0;
	}
	return straight_run[select_mode].de_acceleration;
}

float parameter::get_slalom(const SLALOM_TYPE slalom_type,
		const SLALOM_ELEMENT slalom_element, const signed char right_or_left,
		const unsigned char select_mode) {

	if (select_mode >= RUN_MODE_NUMBER) {			//���݂��Ȃ����[�h��I��������G���[
		mouse::error();
		myprintf("���݂��Ȃ����s���[�h[%d]�̃X�����[���v�f���Q�Ƃ��Ă��܂�!!", select_mode);
		return 0;
	}

//�N���V�b�N�Ȃ�
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

		//�n�[�t�Ȃ�
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

	return 0;
}
