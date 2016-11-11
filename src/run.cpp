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
	mouse::reset_count();		//�ŏ����@�̕␳���߃J�E���g�����Z�b�g
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
	//�i���x+=�����x�j�𐧌�ɂԂ�����
	set_ideal_velocity(
			get_ideal_velocity() + get_acceleration() * CONTORL_PERIOD);
	//�i�p���x+=���p���x�j�𐧌�ɂԂ�����
	set_ideal_angular_velocity(
			get_ideal_angular_velocity() + get_angular_acceleration() * CONTORL_PERIOD);
}

void mouse::cal_distance() {
	run_distance += get_ideal_velocity() * CONTORL_PERIOD;
	ideal_distance += get_ideal_velocity() * CONTORL_PERIOD;
}

void mouse::interrupt() {
	//���x�Ƌ������v�Z
	mouse::cal_velocity();
	mouse::cal_distance();
	ideal_angle += get_ideal_angular_velocity() * CONTORL_PERIOD;

}

void mouse::run_init(bool posture_ctrl, bool wall_ctrl) {

	motor::sleep_motor();

	//�����؂�
	control::stop_wall_control();
	control::stop_control();

	//�t�F�C���Z�[�t��������
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
	//�ǂ����āA�ǂ����݂���Ȃ�ǂ����A�Ȃ��Ȃ�󂷁B�������Ƃ��L�^
	//�}�E�X�̌�������W�������ł�����ƍl����

	signed char direction_x, direction_y;
	mouse::get_direction(&direction_x, &direction_y);

	switch (mouse_direction) {
	case MUKI_UP:
		//�Ǐ����X�V
		//�}�E�X���猩�ĉE
		map::remember_exist(get_x_position(), get_y_position(), MUKI_RIGHT);//�ǂ��������Ƃ��L�^
		if (photo::check_wall(MUKI_RIGHT)) {
			map::create_wall(get_x_position(), get_y_position(), MUKI_RIGHT);
		} else {
			map::destroy_wall(get_x_position(), get_y_position(), MUKI_RIGHT);

			//����������Ȃ�
			if (comb_ignore) {
				//���Ɍ��Ă��ĕǂ��Ȃ��Ȃ�
				if (map::check_exist(get_x_position() - direction_x,
						get_y_position() - direction_y,
						MUKI_RIGHT)) {
					if (map::get_wall(get_x_position() - direction_x,
							get_y_position() - direction_y,
							MUKI_RIGHT) == false) {
						//���[���I�ɕǂ�����͂�
						map::create_wall(get_x_position() + 1, get_y_position(),
						MUKI_DOWN);
						map::remember_exist(get_x_position() + 1,
								get_y_position(),
								MUKI_DOWN);		//�ǂ��������Ƃ��L�^
					}
				}
			}
		}
		//�}�E�X���猩�đO
		map::remember_exist(get_x_position(), get_y_position(), MUKI_UP); //�ǂ��������Ƃ��L�^
		if (photo::check_wall(MUKI_UP)) {
			map::create_wall(get_x_position(), get_y_position(), MUKI_UP);
		} else {
			map::destroy_wall(get_x_position(), get_y_position(), MUKI_UP);
		}
		//�}�E�X���猩�č�
		map::remember_exist(get_x_position(), get_y_position(), MUKI_LEFT);	//�ǂ��������Ƃ��L�^
		if (photo::check_wall(MUKI_LEFT)) {
			map::create_wall(get_x_position(), get_y_position(), MUKI_LEFT);
		} else {
			map::destroy_wall(get_x_position(), get_y_position(), MUKI_LEFT);

			//����������Ȃ�
			if (comb_ignore) {
				//���Ɍ��Ă��ĕǂ��Ȃ��Ȃ�
				if (map::check_exist(get_x_position() - direction_x,
						get_y_position() - direction_y,
						MUKI_LEFT)) {
					if (map::get_wall(get_x_position() - direction_x,
							get_y_position() - direction_y,
							MUKI_LEFT) == false) {
						//���[���I�ɕǂ�����͂�
						map::create_wall(get_x_position() - 1, get_y_position(),
						MUKI_DOWN);
						map::remember_exist(get_x_position() - 1,
								get_y_position(),
								MUKI_DOWN);	//�ǂ��������Ƃ��L�^
					}
				}
			}

		}

		break;

	case MUKI_RIGHT:
		//�Ǐ����X�V
		//�}�E�X���猩�ĉE
		map::remember_exist(get_x_position(), get_y_position(), MUKI_DOWN);	//�ǂ��������Ƃ��L�^
		if (photo::check_wall(MUKI_RIGHT)) {
			map::create_wall(get_x_position(), get_y_position(), MUKI_DOWN);
		} else {
			map::destroy_wall(get_x_position(), get_y_position(), MUKI_DOWN);

			//����������Ȃ�
			if (comb_ignore) {
				//���Ɍ��Ă��ĕǂ��Ȃ��Ȃ�
				if (map::check_exist(get_x_position() - direction_x,
						get_y_position() - direction_y,
						MUKI_DOWN)) {
					if (map::get_wall(get_x_position() - direction_x,
							get_y_position() - direction_y,
							MUKI_DOWN) == false) {
						//���[���I�ɕǂ�����͂�
						map::create_wall(get_x_position(), get_y_position() - 1,
						MUKI_LEFT);
						map::remember_exist(get_x_position(),
								get_y_position() - 1,
								MUKI_LEFT);	//�ǂ��������Ƃ��L�^
					}
				}
			}

		}
		//�}�E�X���猩�đO
		map::remember_exist(get_x_position(), get_y_position(), MUKI_RIGHT);//�ǂ��������Ƃ��L�^
		if (photo::check_wall(MUKI_UP)) {
			map::create_wall(get_x_position(), get_y_position(), MUKI_RIGHT);
		} else {
			map::destroy_wall(get_x_position(), get_y_position(), MUKI_RIGHT);
		}
		//�}�E�X���猩�č�
		map::remember_exist(get_x_position(), get_y_position(), MUKI_UP);//�ǂ��������Ƃ��L�^
		if (photo::check_wall(MUKI_LEFT)) {
			map::create_wall(get_x_position(), get_y_position(), MUKI_UP);
		} else {
			map::destroy_wall(get_x_position(), get_y_position(), MUKI_UP);
			//����������Ȃ�
			if (comb_ignore) {
				//���Ɍ��Ă��ĕǂ��Ȃ��Ȃ�
				if (map::check_exist(get_x_position() - direction_x,
						get_y_position() - direction_y,
						MUKI_UP)) {
					if (map::get_wall(get_x_position() - direction_x,
							get_y_position() - direction_y,
							MUKI_UP) == false) {
						//���[���I�ɕǂ�����͂�
						map::create_wall(get_x_position(), get_y_position() + 1,
						MUKI_LEFT);
						map::remember_exist(get_x_position(),
								get_y_position() + 1,
								MUKI_LEFT);	//�ǂ��������Ƃ��L�^
					}
				}
			}

		}

		break;

	case MUKI_LEFT:
		//�Ǐ����X�V
		//�}�E�X���猩�ĉE
		map::remember_exist(get_x_position(), get_y_position(), MUKI_UP);//�ǂ��������Ƃ��L�^
		if (photo::check_wall(MUKI_RIGHT)) {
			map::create_wall(get_x_position(), get_y_position(), MUKI_UP);
		} else {
			map::destroy_wall(get_x_position(), get_y_position(), MUKI_UP);

			//����������Ȃ�
			if (comb_ignore) {
				//���Ɍ��Ă��ĕǂ��Ȃ��Ȃ�
				if (map::check_exist(get_x_position() - direction_x,
						get_y_position() - direction_y,
						MUKI_UP)) {
					if (map::get_wall(get_x_position() - direction_x,
							get_y_position() - direction_y,
							MUKI_UP) == false) {
						//���[���I�ɕǂ�����͂�
						map::create_wall(get_x_position(), get_y_position() + 1,
						MUKI_RIGHT);
						map::remember_exist(get_x_position(),
								get_y_position() + 1,
								MUKI_RIGHT);	//�ǂ��������Ƃ��L�^
					}
				}
			}

		}
		//�}�E�X���猩�đO
		map::remember_exist(get_x_position(), get_y_position(), MUKI_LEFT);	//�ǂ��������Ƃ��L�^
		if (photo::check_wall(MUKI_UP)) {
			map::create_wall(get_x_position(), get_y_position(), MUKI_LEFT);
		} else {
			map::destroy_wall(get_x_position(), get_y_position(), MUKI_LEFT);
		}
		//�}�E�X���猩�č�
		map::remember_exist(get_x_position(), get_y_position(), MUKI_DOWN);	//�ǂ��������Ƃ��L�^
		if (photo::check_wall(MUKI_LEFT)) {
			map::create_wall(get_x_position(), get_y_position(), MUKI_DOWN);
		} else {
			map::destroy_wall(get_x_position(), get_y_position(), MUKI_DOWN);

			//����������Ȃ�
			if (comb_ignore) {
				//���Ɍ��Ă��ĕǂ��Ȃ��Ȃ�
				if (map::check_exist(get_x_position() - direction_x,
						get_y_position() - direction_y,
						MUKI_DOWN)) {
					if (map::get_wall(get_x_position() - direction_x,
							get_y_position() - direction_y,
							MUKI_DOWN) == false) {
						//���[���I�ɕǂ�����͂�
						map::create_wall(get_x_position(), get_y_position() - 1,
						MUKI_RIGHT);
						map::remember_exist(get_x_position(),
								get_y_position() - 1,
								MUKI_RIGHT);	//�ǂ��������Ƃ��L�^
					}
				}
			}

		}

		break;

	case MUKI_DOWN:
		//�Ǐ����X�V
		//�}�E�X���猩�ĉE
		map::remember_exist(get_x_position(), get_y_position(), MUKI_LEFT);	//�ǂ��������Ƃ��L�^
		if (photo::check_wall(MUKI_RIGHT)) {
			map::create_wall(get_x_position(), get_y_position(), MUKI_LEFT);
		} else {
			map::destroy_wall(get_x_position(), get_y_position(), MUKI_LEFT);

			//����������Ȃ�
			if (comb_ignore) {
				//���Ɍ��Ă��ĕǂ��Ȃ��Ȃ�
				if (map::check_exist(get_x_position() - direction_x,
						get_y_position() - direction_y,
						MUKI_LEFT)) {
					if (map::get_wall(get_x_position() - direction_x,
							get_y_position() - direction_y,
							MUKI_LEFT) == false) {
						//���[���I�ɕǂ�����͂�
						map::create_wall(get_x_position() - 1, get_y_position(),
						MUKI_UP);
						map::remember_exist(get_x_position() - 1,
								get_y_position(),
								MUKI_UP);	//�ǂ��������Ƃ��L�^
					}
				}
			}

		}
		//�}�E�X���猩�đO
		map::remember_exist(get_x_position(), get_y_position(), MUKI_DOWN);	//�ǂ��������Ƃ��L�^
		if (photo::check_wall(MUKI_UP)) {
			map::create_wall(get_x_position(), get_y_position(), MUKI_DOWN);
		} else {
			map::destroy_wall(get_x_position(), get_y_position(), MUKI_DOWN);
		}
		//�}�E�X���猩�č�
		map::remember_exist(get_x_position(), get_y_position(), MUKI_RIGHT);//�ǂ��������Ƃ��L�^
		if (photo::check_wall(MUKI_LEFT)) {
			map::create_wall(get_x_position(), get_y_position(), MUKI_RIGHT);
		} else {
			map::destroy_wall(get_x_position(), get_y_position(), MUKI_RIGHT);

			//����������Ȃ�
			if (comb_ignore) {
				//���Ɍ��Ă��ĕǂ��Ȃ��Ȃ�
				if (map::check_exist(get_x_position() - direction_x,
						get_y_position() - direction_y,
						MUKI_RIGHT)) {
					if (map::get_wall(get_x_position() - direction_x,
							get_y_position() - direction_y,
							MUKI_RIGHT) == false) {
						//���[���I�ɕǂ�����͂�
						map::create_wall(get_x_position() + 1, get_y_position(),
						MUKI_UP);
						map::remember_exist(get_x_position() + 1,
								get_y_position(),
								MUKI_UP);	//�ǂ��������Ƃ��L�^
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
	//TODO �G���[�����͕K�v�ɉ����ď�������
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
			- end_velocity * end_velocity) / (2 * de_accel_value);	//�����ɕK�v�ȋ���

	//����
	mouse::set_acceleration(accel_value);
	while (mouse::get_ideal_velocity() < max_velocity) {
		//���ݑ��x���猸���ɂ����鋗�����v�Z
		de_accel_distance = ABS(
				mouse::get_ideal_velocity() * mouse::get_ideal_velocity()
				- end_velocity * end_velocity) / (2 * de_accel_value);

		//�����ɋ������K�v�ȋ���������Ȃ��Ȃ����甲����
		if (de_accel_distance >= distance_m - mouse::get_distance_m()) {
			break;
		}
	}

	//����
	mouse::set_acceleration(0);
	while (1) {
		//���ݑ��x���猸���ɂ����鋗�����v�Z
		de_accel_distance = ABS(
				mouse::get_ideal_velocity() * mouse::get_ideal_velocity()
				- end_velocity * end_velocity) / (2 * de_accel_value);

		//�����ɋ������K�v�ȋ���������Ȃ��Ȃ����甲����
		if (de_accel_distance >= distance_m - mouse::get_distance_m()) {
			break;
		}
	}

	//����
	mouse::set_acceleration(-de_accel_value);
	while (mouse::get_ideal_velocity() > end_velocity) {
		//���x����ɋ������Ȃ��Ȃ����甲����
		if (distance_m < mouse::get_distance_m()) {
			break;
		}
	}
	mouse::set_acceleration(0);
	mouse::set_ideal_velocity(end_velocity);

	//���x0���Ƃ����ɕ����߂��Ă��܂�
	if (end_velocity > 0) {
		//�������x����ɖ����Ȃ��Ă��A�Ō�܂ő��肫��悤
		while (distance_m > mouse::get_distance_m()) {
		}
	}

	mouse::set_distance_m(0);
}

void run::slalom(const SLALOM_TYPE slalom_type,
		const signed char right_or_left, const unsigned char select_mode) {
	//�X�����[���̃p�����[�^�[�擾
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

//�O�����̕�����
	mouse::set_distance_m(0);
	accel_run(distance, slalom_velocity, select_mode);

	//mouse::slalom_flag = true;
	control::stop_wall_control();

//���v��肪��
	if (right_or_left == MUKI_LEFT) {
		angular_acceleration = -ABS(angular_acceleration);
		max_angular = -ABS(max_angular);
	}
	mouse::set_ideal_angular_velocity(0);

//�p�������
	mouse::set_angular_acceleration(angular_acceleration);
	while (ABS(gyro::get_angle()) < clothoid_angle_degree) {
//�t�F�C���Z�[�t���|�����Ă���΂����Ŕ�����
		if (mouse::get_fail_flag()) {
			return ;
		}
		//�ő�p���x�ɒB������I��
		if (ABS(mouse::get_ideal_angular_velocity()) > ABS(max_angular)) {
			mouse::set_ideal_angular_velocity(max_angular);
			break;
		}
	}

	//�������ɂ����l�̊p�x�������Ɨ\�z����邩��
	//�Ǐ]�x��Ő�����������Ԃ̊p�x�̗��z�ƌ����̍����L�^���Ă���
	float def_angle = (clothoid_angle_degree - ABS(degree(gyro::get_angle())));

//���p���x
	mouse::set_angular_acceleration(0);

	while (ABS(gyro::get_angle())
			< (target_angle_degree - clothoid_angle_degree)) {
//�t�F�C���Z�[�t���|�����Ă���΂����Ŕ�����
		if (mouse::get_fail_flag()) {
			return ;
		}

		de_accel_angle = degree(
		//(gyro::get_angular_velocity() * gyro::get_angular_velocity())
				(mouse::get_ideal_angular_velocity()
						* mouse::get_ideal_angular_velocity())
						/ (2 * angular_acceleration));

//�����ɕK�v�Ȋp�x���c���ĂȂ���Δ�����
		//�Ǐ]�x��̂��߂Ɍ����ɂ͗]���Ȋp�x���K�v�Ȃ͂�
		if ((ABS(de_accel_angle) + def_angle)
				>= (target_angle_degree - ABS(mouse::get_angle_degree()))) {
			break;
		}

	}

//�p�������
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

//�t�F�C���Z�[�t���|�����Ă���΂����Ŕ�����
		if (mouse::get_fail_flag()) {
			return ;
		}
	}

	mouse::set_angular_acceleration(0);
	mouse::set_ideal_angular_velocity(0);

//��닗��������
	if (wall_flag)
		control::start_wall_control();	//���Ƃ��ƕǐ��䂪�������Ă��畜��������

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

	//���v��肪��
	if (target_degree < 0) {
		angular_acceleration = -ABS(angular_acceleration);
	}

	mouse::reset_angle();
	mouse::set_ideal_angular_velocity(0);

	//�p�������
	mouse::set_angular_acceleration(angular_acceleration);
	while (ABS(mouse::get_ideal_angular_velocity()) < max_angular_velocity) {
		//�����ɕK�v�Ȋp�x���v�Z
		angle_degree = degree(
				(mouse::get_ideal_angular_velocity()
						* mouse::get_ideal_angular_velocity())
						/ (2 * angular_acceleration));
		//�����ɕK�v�Ȋp�x���c���ĂȂ���Δ�����
		if (angle_degree >= (target_degree - mouse::get_angle_degree())) {
			break;
		}

	}

	//���p���x���
	mouse::set_angular_acceleration(0);
	angle_degree = target_degree - angle_degree;
	while (1) {
		//�����ɕK�v�Ȋp�x���v�Z
		angle_degree = degree(
				(mouse::get_ideal_angular_velocity()
						* mouse::get_ideal_angular_velocity())
						/ (2 * angular_acceleration));
		//�����ɕK�v�Ȋp�x���c���ĂȂ���Δ�����
		if (angle_degree >= (target_degree - mouse::get_angle_degree())) {
			break;
		}
	}

	//�p�������
	mouse::set_angular_acceleration(-angular_acceleration);
	while (ABS(mouse::get_angle_degree()) < ABS(target_degree)) {
		//���̏����t���Ȃ��ƁA��Ɋp���x��0�ɂȂ����ꍇ���܂ł����Ă����[�v�𔲂��Ȃ�
		if (ABS(mouse::get_ideal_angular_velocity()) < 0.02) {
			mouse::set_angular_acceleration(0);
		}

	}

	mouse::set_angular_acceleration(0);
	mouse::set_ideal_angular_velocity(0);
	mouse::set_distance_m(0);

	//���Ƃ��ƕǐ��䂩�����Ă��Ȃ畜��������
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
		//���H�O�Ȃ�false��Ԃ�
		if ((target_x + 1) >= MAZE_SIZE) {
			return false;
		}
		muki_x = 1;
		muki_y = 0;
		break;

	case MUKI_LEFT:
		//���H�O�Ȃ�false��Ԃ�
		if ((target_x - 1) < 0) {
			return false;
		}
		muki_x = -1;
		muki_y = 0;
		break;

	case MUKI_UP:
		//���H�O�Ȃ�false��Ԃ�
		if ((target_y + 1) >= MAZE_SIZE) {
			return false;
		}
		muki_x = 0;
		muki_y = 1;
		break;

	case MUKI_DOWN:
		//���H�O�Ȃ�false��Ԃ�
		if ((target_y - 1) < 0) {
			return false;
		}
		muki_x = 0;
		muki_y = -1;
		break;
	}

	if (step::get_step((target_x + muki_x), (target_y + muki_y))
			< step::get_step(target_x, target_y)) {			//�����̏������ق���
		if ((map::get_wall(target_x, target_y, muki) == false)) {	//�ǂ��Ȃ��Ȃ�
			return true;
		}
	}

	return false;
}

unsigned int adachi::count_unknown_wall(unsigned char target_x,
		unsigned char target_y) {
	unsigned int unknown_count = 0;

	//�e�����ɂ��ĒT���ς݂����ׂ�.���T���Ȃ�J�E���g�A�b�v
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
		//1��Ԓ��i
		run::accel_run((0.09 * MOUSE_MODE), SEARCH_VELOCITY, 0);
		break;

	case turn_right:
		//�X�����[��
		run::slalom(small,MUKI_RIGHT,0);
		direction_turn(&direction_x, &direction_y, MUKI_RIGHT);	//������90���ς���
		break;

	case turn_left:
		//�X�����[��
		run::slalom(small,MUKI_LEFT,0);
		direction_turn(&direction_x, &direction_y, MUKI_LEFT);	//������90���ς���
		break;

	case back:
		//����Ԑi���180���^�[�����Ĕ���Ԓ��i
		run::accel_run((0.045 * MOUSE_MODE), 0, 0);			//����Ԓ��i
		run::spin_turn(180);
		direction_turn(&direction_x, &direction_y, MUKI_RIGHT);	//������90���ς���
		direction_turn(&direction_x, &direction_y, MUKI_RIGHT);	//������90���ς���
		run::accel_run((0.045 * MOUSE_MODE), SEARCH_VELOCITY, 0);		//����Ԓ��i
		break;

	case stop:
		//����Ԑi��ŃX�g�b�v
		run::accel_run((0.045 * MOUSE_MODE), 0, 0);			//����Ԓ��i
		//TODO �����Ń��[�^�[�̓d���؂�ׂ��H
		break;
	}
}

void adachi::run_next_action_by_spin(ACTION_TYPE next_action) {
	switch (next_action) {
	case go_straight:
		//1��Ԓ��i
		run::accel_run((0.09 * MOUSE_MODE), SEARCH_VELOCITY, 0);
		break;

	case turn_right:
		//����ԁ˒��M�n�˔����
		run::accel_run((0.045 * MOUSE_MODE), 0, 0);
		run::spin_turn(90);
		run::accel_run((0.045 * MOUSE_MODE), SEARCH_VELOCITY, 0);
		direction_turn(&direction_x, &direction_y, MUKI_RIGHT);	//������90���ς���
		break;

	case turn_left:
		//����ԁ˒��M�n�˔����
		run::accel_run((0.045 * MOUSE_MODE), 0, 0);
		run::spin_turn(270);
		run::accel_run((0.045 * MOUSE_MODE), SEARCH_VELOCITY, 0);
		direction_turn(&direction_x, &direction_y, MUKI_LEFT);	//������90���ς���
		break;

	case back:
		//����Ԑi���180���^�[�����Ĕ���Ԓ��i
		run::accel_run((0.045 * MOUSE_MODE), 0, 0);			//����Ԓ��i
		run::spin_turn(180);
		direction_turn(&direction_x, &direction_y, MUKI_RIGHT);	//������90���ς���
		direction_turn(&direction_x, &direction_y, MUKI_RIGHT);	//������90���ς���
		run::accel_run((0.045 * MOUSE_MODE), SEARCH_VELOCITY, 0);		//����Ԓ��i
		break;

	case stop:
		//����Ԑi��ŃX�g�b�v
		run::accel_run((0.045 * MOUSE_MODE), 0, 0);			//����Ԓ��i
		//TODO �����Ń��[�^�[�̓d���؂�ׂ��H
		break;
	}
}


void adachi::simulate_next_action(ACTION_TYPE next_action) {
	switch (next_action) {
	case go_straight:
		//1��Ԓ��i
		break;

	case turn_right:
		//����ԁ˒��M�n�˔����
		direction_turn(&direction_x, &direction_y, MUKI_RIGHT);	//������90���ς���
		break;

	case turn_left:
		//����ԁ˒��M�n�˔����
		direction_turn(&direction_x, &direction_y, MUKI_LEFT);	//������90���ς���
		break;

	case back:
		//����Ԑi���180���^�[�����Ĕ���Ԓ��i
		direction_turn(&direction_x, &direction_y, MUKI_RIGHT);	//������90���ς���
		direction_turn(&direction_x, &direction_y, MUKI_RIGHT);	//������90���ς���
		break;

	case stop:
		//����Ԑi��ŃX�g�b�v
		break;
	}
}

ACTION_TYPE adachi::get_next_action(DIRECTION next_direction,
		uint8_t now_muki) {
	switch (now_muki) {
	case MUKI_RIGHT:
		//�^�������s����Ȃ�A������ŗD��
		if (next_direction.element.right == 1) {
			return go_straight;
		}
		//�E�̃^�[�������ɗD��
		else if (next_direction.element.down == 1) {
			return turn_right;
		}
		//���̃^�[�������ɗD��
		else if (next_direction.element.up == 1) {
			return turn_left;
		}
		//U�^�[���͗D��x�Œ�
		else if (next_direction.element.left == 1) {
			return back;
		}
		break;

		//����Ă邱�Ƃ͈ȉ����l�Ȃ̂ŃR�����g�͏Ȃ�
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

	//�����ɂ��ǂ蒅���̂́A���s���������Ȃ����A�\�����ʗ�O�Ȃ̂ŁA�}�E�X���~�߂�B
	return stop;
}

bool adachi::adachi_method(unsigned char target_x, unsigned char target_y,
		bool is_FULUKAWA) {
	bool adachi_flag = true;	//�r���Ń~�X����������false��
	unsigned char now_x, now_y;	//���W�ꎞ�ۑ��p�B���Ղ��̂���
	DIRECTION next_direction, priority_direction;	//���ɍs���������Ǘ�
	unsigned char max_unknown_count, target_unknown_count;	//���T���̕ǂ̐����Ǘ�
	ACTION_TYPE next_action;	//���̍s�����Ǘ�

	my7seg::turn_off();

	//�ۑ����Ă����}�b�v��ǂ݂���
	map::input_map_data(&mouse::now_map);

//�������擾
	mouse::get_direction(&direction_x, &direction_y);

	mouse::run_init(true, true);

	my7seg::count_down(3, 500);

	run::accel_run((0.045 * MOUSE_MODE), SEARCH_VELOCITY, 0);

	while (adachi_flag) {
//�t�F�C���Z�[�t���|�����Ă���΂����Ŕ�����
		if (mouse::get_fail_flag()) {
			adachi_flag = false;
			break;
		}

		my7seg::light(3);

//���W���X�V
		now_x = mouse::get_x_position() + direction_x;
		now_y = mouse::get_y_position() + direction_y;
		mouse::set_position(now_x, now_y);

//������
		mouse::set_direction(direction_x, direction_y);

//�Ǐ��X�V
		mouse::look_wall(false);

//�ڕW�̍��W�ɂ��ǂ蒅������I��
		if ((now_x == target_x) && (now_y == target_y)) {
			run_next_action(stop);
			break;
		}

//�����}�b�v�쐻
		step::set_step(target_x, target_y);

//�����Ɩ��T���̕ǂ̐������Z�b�g
		next_direction.all = 0;
		priority_direction.all = 0;
		max_unknown_count = 1;	//0���͂�������

//�����I�ɑO�㍶�E�̃}�X�֍s���邩����.
//�s����Ύ��s�������̌��ɓ����
//�X�Ɍ��ĂȂ��ǂ̐����������priority_direction�̕��ɂ����Ƃ��Ēǉ�
		if (check_move_by_step(now_x, now_y, MUKI_RIGHT)) {			//�E
			next_direction.element.right = 1;

			target_unknown_count = count_unknown_wall((now_x + 1), now_y);
			if (target_unknown_count == max_unknown_count) {
				priority_direction.element.right = 1;
			} else if (target_unknown_count > max_unknown_count) {
				max_unknown_count = target_unknown_count;
				priority_direction.all = 0;				//���̕����͂���Ȃ��̂Ń��Z�b�g
				priority_direction.element.right = 1;
			}

		}
		if (check_move_by_step(now_x, now_y, MUKI_LEFT)) {			//��

			next_direction.element.left = 1;

			target_unknown_count = count_unknown_wall((now_x - 1), now_y);
			if (target_unknown_count == max_unknown_count) {
				priority_direction.element.left = 1;
			} else if (target_unknown_count > max_unknown_count) {
				max_unknown_count = target_unknown_count;
				priority_direction.all = 0;				//���̕����͂���Ȃ��̂Ń��Z�b�g
				priority_direction.element.left = 1;
			}

		}
		if (check_move_by_step(now_x, now_y, MUKI_UP)) {			//��
			next_direction.element.up = 1;

			target_unknown_count = count_unknown_wall(now_x, (now_y + 1));
			if (target_unknown_count == max_unknown_count) {
				priority_direction.element.up = 1;
			} else if (target_unknown_count > max_unknown_count) {
				max_unknown_count = target_unknown_count;
				priority_direction.all = 0;				//���̕����͂���Ȃ��̂Ń��Z�b�g
				priority_direction.element.up = 1;
			}

		}
		if (check_move_by_step(now_x, now_y, MUKI_DOWN)) {			//��
			next_direction.element.down = 1;

			target_unknown_count = count_unknown_wall(now_x, (now_y - 1));
			if (target_unknown_count == max_unknown_count) {
				priority_direction.element.down = 1;
			} else if (target_unknown_count > max_unknown_count) {
				max_unknown_count = target_unknown_count;
				priority_direction.all = 0;				//���̕����͂���Ȃ��̂Ń��Z�b�g
				priority_direction.element.down = 1;
			}

		}

//���T����Ԃ����̒��ɂ���Ȃ�A���ɍs�������͂��̒�����I��
		if ((priority_direction.all != 0) && is_FULUKAWA) {
			next_direction.all = priority_direction.all;
		}

//next_dirrction���玟�s��������I�сA�s������
		next_action = get_next_action(next_direction, mouse::get_direction());
		//TODO �ǃL���悤�̊֐���p�ӂ���
		run_next_action(next_action);

		//�����~�܂�ׂ��Əo���Ȃ�R�R�ő����@����߂�
		if (next_action == stop) {
			adachi_flag = false;
		}

//�����X�V
		mouse::set_direction(direction_x, direction_y);

	}

	if (adachi_flag) {
		//�����@�����Ȃ̂Ń}�b�v��ۑ�����
		map::output_map_data(&mouse::now_map);
		return true;				//�����@����!!

	} else {
//�����ɗ���Ƃ������Ƃ͑����@�����s���Ă�
		motor::sleep_motor();
//TODO �킩��₷���������~����
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
	bool adachi_flag = true;	//�r���Ń~�X����������false��
	unsigned char now_x, now_y;	//���W�ꎞ�ۑ��p�B���Ղ��̂���
	DIRECTION next_direction, priority_direction;	//���ɍs���������Ǘ�
	unsigned char max_unknown_count, target_unknown_count;	//���T���̕ǂ̐����Ǘ�
	ACTION_TYPE next_action;	//���̍s�����Ǘ�

	my7seg::turn_off();

	//�ۑ����Ă����}�b�v��ǂ݂���
	map::input_map_data(&mouse::now_map);

//�������擾
	mouse::get_direction(&direction_x, &direction_y);

	mouse::run_init(true, true);

	my7seg::count_down(3, 500);

	run::accel_run((0.045 * MOUSE_MODE), SEARCH_VELOCITY, 0);

	while (adachi_flag) {
//�t�F�C���Z�[�t���|�����Ă���΂����Ŕ�����
		if (mouse::get_fail_flag()) {
			adachi_flag = false;
			break;
		}

		my7seg::light(3);

//���W���X�V
		now_x = mouse::get_x_position() + direction_x;
		now_y = mouse::get_y_position() + direction_y;
		mouse::set_position(now_x, now_y);

//������
		mouse::set_direction(direction_x, direction_y);

//�Ǐ��X�V
		mouse::velify_wall();
		mouse::look_wall(false);

//�ڕW�̍��W�ɂ��ǂ蒅������I��
		if ((now_x == target_x) && (now_y == target_y)) {
			run_next_action(stop);
			break;
		}

//�����}�b�v�쐻
		step::set_step(target_x, target_y);

//�����Ɩ��T���̕ǂ̐������Z�b�g
		next_direction.all = 0;
		priority_direction.all = 0;
		max_unknown_count = 1;	//0���͂�������

//�����I�ɑO�㍶�E�̃}�X�֍s���邩����.
//�s����Ύ��s�������̌��ɓ����
//�X�Ɍ��ĂȂ��ǂ̐����������priority_direction�̕��ɂ����Ƃ��Ēǉ�
		if (check_move_by_step(now_x, now_y, MUKI_RIGHT)) {			//�E
			next_direction.element.right = 1;

			target_unknown_count = count_unknown_wall((now_x + 1), now_y);
			if (target_unknown_count == max_unknown_count) {
				priority_direction.element.right = 1;
			} else if (target_unknown_count > max_unknown_count) {
				max_unknown_count = target_unknown_count;
				priority_direction.all = 0;				//���̕����͂���Ȃ��̂Ń��Z�b�g
				priority_direction.element.right = 1;
			}

		}
		if (check_move_by_step(now_x, now_y, MUKI_LEFT)) {			//��

			next_direction.element.left = 1;

			target_unknown_count = count_unknown_wall((now_x - 1), now_y);
			if (target_unknown_count == max_unknown_count) {
				priority_direction.element.left = 1;
			} else if (target_unknown_count > max_unknown_count) {
				max_unknown_count = target_unknown_count;
				priority_direction.all = 0;				//���̕����͂���Ȃ��̂Ń��Z�b�g
				priority_direction.element.left = 1;
			}

		}
		if (check_move_by_step(now_x, now_y, MUKI_UP)) {			//��
			next_direction.element.up = 1;

			target_unknown_count = count_unknown_wall(now_x, (now_y + 1));
			if (target_unknown_count == max_unknown_count) {
				priority_direction.element.up = 1;
			} else if (target_unknown_count > max_unknown_count) {
				max_unknown_count = target_unknown_count;
				priority_direction.all = 0;				//���̕����͂���Ȃ��̂Ń��Z�b�g
				priority_direction.element.up = 1;
			}

		}
		if (check_move_by_step(now_x, now_y, MUKI_DOWN)) {			//��
			next_direction.element.down = 1;

			target_unknown_count = count_unknown_wall(now_x, (now_y - 1));
			if (target_unknown_count == max_unknown_count) {
				priority_direction.element.down = 1;
			} else if (target_unknown_count > max_unknown_count) {
				max_unknown_count = target_unknown_count;
				priority_direction.all = 0;				//���̕����͂���Ȃ��̂Ń��Z�b�g
				priority_direction.element.down = 1;
			}

		}

//���T����Ԃ����̒��ɂ���Ȃ�A���ɍs�������͂��̒�����I��
		if ((priority_direction.all != 0) && is_FULUKAWA) {
			next_direction.all = priority_direction.all;
		}

//next_dirrction���玟�s��������I�сA�s������
		next_action = get_next_action(next_direction, mouse::get_direction());
		//TODO �ǃL���悤�̊֐���p�ӂ���
		run_next_action(next_action);

		//�����~�܂�ׂ��Əo���Ȃ�R�R�ő����@����߂�
		if (next_action == stop) {
			adachi_flag = false;
		}

//�����X�V
		mouse::set_direction(direction_x, direction_y);

	}

	if (adachi_flag) {
		//�����@�����Ȃ̂Ń}�b�v��ۑ�����
		map::output_map_data(&mouse::now_map);
		return true;				//�����@����!!

	} else {
//�����ɗ���Ƃ������Ƃ͑����@�����s���Ă�
		motor::sleep_motor();
//TODO �킩��₷���������~����
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
	bool search_flag = true;	//�r���Ń~�X����������false��
	uint8_t now_x, now_y;	//���W�ꎞ�ۑ��p�B���Ղ��̂���
	ACTION_TYPE next_action;	//���̍s�����Ǘ�

	my7seg::turn_off();

	//�ۑ����Ă����}�b�v��ǂ݂���
	map::input_map_data(&mouse::now_map);

	//�������擾
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

