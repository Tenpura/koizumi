/*
 * run.cpp
 *
 *  Created on: 2016/10/23
 *      Author: Koizumi
 */

#include"run.h"

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
unsigned char mouse::mouse_direction = MUKI_UP;

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
	mouse::reset_count();		//�ŏ����@�̕␳���߃J�E���g�����Z�b�g

	//�}�E�X�̌����Ă�������ɉ�����angle��relative_rad��ύX����
	//TODO �΂ߕ����͗v����
	float rad = 0;
	switch (get_direction()) {
	case MUKI_RIGHT:
		rad = PI() / 2;
		break;
	case MUKI_LEFT:
		rad = -PI() / 2;
		break;
	case MUKI_DOWN:
		rad = PI();
		break;
	case MUKI_UP:
		rad = 0;
		break;
	}
	set_ang(rad);	//��Ίp�x��ύX

	set_relative_rad(0, false);	//��̓��Z�b�g����
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

	//���Έʒu���v�Z����
	relative.x = x_m;
	relative.y = y_m;
	//mod1��Ԃ��s��
	while ((relative.x > 0.09 * MOUSE_MODE) || (relative.y > 0.09 * MOUSE_MODE)) {
		if (relative.x > 0.09 * MOUSE_MODE)
			relative.x -= 0.09 * MOUSE_MODE;
		if (relative.y > 0.09 * MOUSE_MODE)
			relative.y -= 0.09 * MOUSE_MODE;
	}
	//���̒��S�����_
	relative.x -= 0.045 * MOUSE_MODE;
	relative.y -= 0.045 * MOUSE_MODE;
}

COORDINATE mouse::get_place() {
	return place;
}

float mouse::get_relative_displace() {
	signed char dir_x, dir_y;		//�}�E�X�̕���
	mouse::get_direction(&dir_x, &dir_y);

	//TODO �΂߂̂Ƃ��I�h���g������v�Z����������ǂ��������͗v����
	if ((dir_x != 0) && (dir_y != 0))
		return 0;

	return (dir_y * relative.x - dir_x * relative.y);
}

float mouse::get_relative_go() {
	signed char dir_x, dir_y;		//�}�E�X�̕���
	mouse::get_direction(&dir_x, &dir_y);

	//TODO �΂߂̂Ƃ��I�h���g������v�Z�������Έʒu���ǂ��������͗v����
	if ((dir_x != 0) && (dir_y != 0))
		return 0;

	return (dir_x * relative.x + dir_y * relative.y);
}

void mouse::set_relative_go(float set_value, bool updata_abs) {
	signed char dir_x, dir_y;		//�}�E�X�̕���
	mouse::get_direction(&dir_x, &dir_y);
	float delta = set_value - get_relative_go();		//���ݒl�Ƃ̍���

			//���΍��W���X�V
	relative.x += dir_x * delta;
	relative.y += dir_y * delta;

	if (updata_abs) {		//��΍��W���X�V
		place.x += dir_x * delta;
		place.y += dir_y * delta;
	}

}

void mouse::set_relative_displacement(float set_value, bool updata_abs) {
	signed char dir_x, dir_y;		//�}�E�X�̕���
	mouse::get_direction(&dir_x, &dir_y);
	float delta = set_value - get_relative_displace();		//���ݒl�Ƃ̍���

			//���΍��W���X�V
	relative.x += dir_y * delta;
	relative.y += -dir_x * delta;

	if (updata_abs) {		//��΍��W���X�V
		place.x += dir_y * delta;
		place.y += -dir_x * delta;
	}
}

float mouse::get_relative_rad() {
	//���Ίp�x���v�Z�@(��Ίp�x-��p�x)
	return get_angle_radian() - relative_base_rad;
}

void mouse::set_relative_rad(float set_rad, bool update_abs) {

	float delta = set_rad - get_relative_rad();
	//��Ίp�x���X�V���Ȃ��ꍇ�͊�����������ďI��
	if (!update_abs) {
		relative_base_rad -= delta;

	} else {		//��Ίp�x���X�V����ꍇ�͋t�Ɋ�͂�����Ȃ�
		set_ang(get_angle_radian() + delta);

	}
}

void mouse::set_relative_base_rad(SLALOM_TYPE sla, bool is_right) {
	float correct = 0;	//�C���ʂ̕ۑ��p
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

	if (!is_right)		//���v��肪��
		correct *= -1;
	relative_base_rad += correct;	//��p�x��ύX

}

unsigned char mouse::get_direction() {
	return mouse_direction;
}

inline void mouse::get_direction(signed char *direction_x,
		signed char *direction_y) {
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
	//�i���x+=�����x�j�𐧌�ɂԂ�����
	set_ideal_velocity(
			get_ideal_velocity() + get_ideal_accel() * CONTORL_PERIOD);
	//�i�p���x+=���p���x�j�𐧌�ɂԂ�����
	set_ideal_angular_velocity(
			get_ideal_angular_velocity() + get_ideal_angular_accel() * CONTORL_PERIOD);
}

void mouse::cal_distance() {
	run_distance += mouse::get_velocity() * CONTORL_PERIOD;
	ideal_distance += get_ideal_velocity() * CONTORL_PERIOD;
}

void mouse::cal_place() {
	float theta = get_angle_radian();		//�}�E�X�̊p�x���擾
	//�������ԂɃ}�E�X���i�ދ���
	float dx = velocity * CONTORL_PERIOD * my_math::sin(theta);
	float dy = velocity * CONTORL_PERIOD * my_math::cos(theta);

	place.x += dx;
	place.y += dy;

	//���ΓI�ʒu���A�����X�V���āA�͈͊O�ɏo����I�[�o�[�t���[����
	relative.x += dx;
	relative.y += dy;
	//+-����Ԃ͈̔͂���o����A���ɖ߂�
	if (ABS(relative.x) > 0.045 * MOUSE_MODE)
		relative.x -= SIGN(relative.x) * 0.09 * MOUSE_MODE;
	if (ABS(relative.y) > 0.045 * MOUSE_MODE)
		relative.y -= SIGN(relative.y) * 0.09 * MOUSE_MODE;

}

void mouse::interrupt() {

	//XXX �J���}���t�B���^�̐���l�i�����x�Z���T�j�Ɗϑ��l�i�G���R�[�_�[�j�̕��U
	static kalman v_kal(0.101, 630);		//���x�p�̃J���}���t�B���^�N���X���Ăяo��
	if (get_spin_flag()) {		//���M�n���Ȃ�
		v_kal.update(encoder::get_velocity(), encoder::get_velocity());	//�����x�Z���T�͖������ăJ���}���t�B���^��������
	} else {
		v_kal.update(accelmeter::get_accel(axis_y) * CONTORL_PERIOD,
				encoder::get_velocity());		//�J���}���t�B���^��������
	}
	velocity = v_kal.get_value();		//���ݑ��x�Ƃ��ĕ␳��̑��x���̗p����
	//���x�Ƌ������v�Z
	mouse::cal_velocity();
	mouse::cal_distance();
	mouse::cal_place();

	ideal_angle_degree += get_ideal_angular_velocity() * CONTORL_PERIOD;

}

void mouse::run_init(bool posture_ctrl, bool wall_ctrl) {

	motor::sleep_motor();

	//�����؂�
	control::stop_wall_control();
	control::stop_control();

	//�t�F�C���Z�[�t��������
	mouse::set_fail_flag(false);

	accelmeter::set_accel_ref(AXIS_t::axis_y);
	gyro::set_gyro_ref();
	mouse::reset_angle();
	mouse::set_distance_m(0);
	mouse::set_ideal_accel(0);
	mouse::set_ideal_velocity(0);
	mouse::set_ideal_angular_accel(0);
	mouse::set_ideal_angular_velocity(0);
	static const float half_section = 0.045 * MOUSE_MODE;	//����敪�̒���
	mouse::set_place(half_section * (1 + 2 * mouse::get_x_position()),
			half_section * (1 + 2 * mouse::get_y_position()));		//���ݍ��W�̒��S�ʒu
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

void mouse::velify_wall() {
	my7seg::turn_off();
	if (photo::check_wall(front))
		my7seg::light(my7seg::front);
	if (photo::check_wall(right))
		my7seg::light(my7seg::right);
	if (photo::check_wall(left))
		my7seg::light(my7seg::left);

}

void mouse::turn_direction(const unsigned char right_or_left) {
	//�}�E�X�̌�����90����]

	if (right_or_left == MUKI_RIGHT) {
		switch (mouse_direction) {
		case MUKI_UP:
			mouse_direction = MUKI_RIGHT;
			break;

		case MUKI_DOWN:
			mouse_direction = MUKI_LEFT;
			break;

		case MUKI_RIGHT:
			mouse_direction = MUKI_DOWN;
			break;

		case MUKI_LEFT:
			mouse_direction = MUKI_UP;
			break;
		}

	} else {
		switch (mouse_direction) {
		case MUKI_UP:
			mouse_direction = MUKI_LEFT;
			break;

		case MUKI_DOWN:
			mouse_direction = MUKI_RIGHT;
			break;

		case MUKI_RIGHT:
			mouse_direction = MUKI_UP;
			break;

		case MUKI_LEFT:
			mouse_direction = MUKI_DOWN;
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
		turn_direction(right_or_left);
		break;

	case big_180:
		turn_direction(right_or_left);
		turn_direction(right_or_left);
		break;

	case begin_45:
	case end_45:
		//FIX_ME �΂߂̕����Ǘ����@���m������ĂȂ�
		break;

	case begin_135:
	case end_135:
		//FIX_ME �΂߂̕����Ǘ����@���m������ĂȂ�
		break;

	case oblique_90:
		//FIX_ME �΂߂̕����Ǘ����@���m������ĂȂ�
		break;
	}
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

//XXX �ǃL���̋���[m]
// right left front_right front_left front
float run::WALL_EAGE_DISTANCE[PHOTO_TYPE::element_count] = { 0.04, 0.035, 0, 0,
		0 };

void run::accel_run(const float distance_m, const float end_velocity,
		const unsigned char select_mode) {

	float max_velocity = parameter::get_run_max_velocity(select_mode);
	float accel_value = ABS(parameter::get_run_acceleration(select_mode));
	float de_accel_value = ABS(parameter::get_run_de_acceleration(select_mode));

	float de_accel_distance = ABS(
			mouse::get_ideal_velocity() * mouse::get_ideal_velocity()
			- end_velocity * end_velocity) / (2 * de_accel_value);	//�����ɕK�v�ȋ���

	float sign = 1;
	//�o�b�N����Ȃ�
	if (distance_m < 0) {
		sign = -1;
		max_velocity *= -1;
		accel_value *= -1;
		de_accel_value *= -1;
		de_accel_distance *= -1;
	}

	//����
	mouse::set_ideal_accel(accel_value);
	while (0 < sign * (max_velocity - mouse::get_ideal_velocity())) {
		//���ݑ��x���猸���ɂ����鋗�����v�Z
		de_accel_distance = (mouse::get_ideal_velocity()
				* mouse::get_ideal_velocity() - end_velocity * end_velocity)
				/ (2 * de_accel_value);

		//�����ɋ������K�v�ȋ���������Ȃ��Ȃ����甲����
		if (ABS(de_accel_distance)
				>= sign * (distance_m - mouse::get_distance_m())) {
			break;
		}

		if (mouse::get_fail_flag())
			return;
	}

	//����
	mouse::set_ideal_accel(0);
	while (1) {
		//���ݑ��x���猸���ɂ����鋗�����v�Z
		de_accel_distance = (mouse::get_ideal_velocity() * mouse::get_ideal_velocity()
				- end_velocity * end_velocity) / (2 * de_accel_value);

		//�����ɋ������K�v�ȋ���������Ȃ��Ȃ����甲����
		if (ABS(de_accel_distance)
				>= sign * (distance_m - mouse::get_distance_m())) {
			break;
		}

		if (mouse::get_fail_flag())
			return;
	}

	//����
	mouse::set_ideal_accel(-de_accel_value);
	while (sign * (mouse::get_ideal_velocity() - end_velocity) > 0) {
		//���x����ɋ������Ȃ��Ȃ����甲����
		if (distance_m < mouse::get_distance_m())
			break;


		if (mouse::get_fail_flag())
			return;
	}

	mouse::set_ideal_accel(0);
	mouse::set_ideal_velocity(end_velocity);

	//���x0���Ƃ����ɕ����߂��Ă��܂�
	if (sign * end_velocity > 0) {
		//�������x����ɖ����Ȃ��Ă��A�Ō�܂ő��肫��悤
		while (sign * (distance_m - mouse::get_distance_m()) > 0) {
			if (mouse::get_fail_flag())
				return;
		}
	}

	mouse::set_distance_m(0);
}

void run::accel_run_wall_eage(const float distance_m, const float end_velocity,
		const unsigned char select_mode, const float check_distance) {

	float target_distance = check_distance;
	bool wall_eage_flag = true;
	float wall_eage[PHOTO_TYPE::element_count];	//���̒l�����������ǃL��

	GPIO_SetBits(GPIOC, GPIO_Pin_3);	//LED2

	//�ǃL���̃��t�@�����X
	wall_eage[PHOTO_TYPE::right] = -0.015;
	wall_eage[PHOTO_TYPE::left] = 0.02;

	//�`�F�b�N�����܂ł͕��ʂɑ���
	accel_run(distance_m - check_distance, end_velocity, select_mode);

	//���O�܂ŕǂ������Ă���ǃL��������@���@臒l���܂����̂𔻒f����悤
	uint8_t right = 0;
	uint8_t left = 0;

	//���O�ɉ�ms�ȏ� 臒l�𒴂��Ă���ΕǃL�����N����Ɣ��f���邩�i�l���o�����΍�j
	static const uint8_t w_cnt = 3;

	//1ms �܂��Ă��玟�̃Z���T�[�l���݂邽�߂ɁA���荞�݂����ꂽ�����f����悤
	uint32_t time_count = mouse::get_count_ms();

	while (mouse::get_distance_m() < target_distance) {
		//�t�F�C���Z�[�t���|�����Ă���΂����Ŕ�����
		if (mouse::get_fail_flag()) {
			return;
		}

		while (time_count == mouse::get_count_ms()) {
			//���荞�݂�����܂ő҂�
		}
		time_count = mouse::get_count_ms();

		if (!wall_eage_flag) {
			GPIO_ResetBits(GPIOC, GPIO_Pin_3);	//LED2
		} else {
			//���Ow_cnt[ms]�ȏ�臒l�̔��Α��ɂ��āA���̂Ƃ��͂��߂�臒l�𒴂����Ȃ�
			if (left >= w_cnt) {
				if (photo::get_displacement_from_center(PHOTO_TYPE::left)
						> wall_eage[PHOTO_TYPE::left]) {
					target_distance = WALL_EAGE_DISTANCE[PHOTO_TYPE::left];
					mouse::set_relative_go(0.045 * MOUSE_MODE - target_distance,
							true);	//��撆�������_�Ƃ��Ĉʒu���X�V
					mouse::set_distance_m(0);
					wall_eage_flag = false;
				}
			} else {
				//�ǃL����҂O�ɂ��������ǃL�����N����̂��𔻒f
				if (photo::get_displacement_from_center(PHOTO_TYPE::left)
						< wall_eage[PHOTO_TYPE::left])
					left++;
				else
					left = 0;
			}

			//���Ow_cnt[ms]�ȏ�臒l�̔��Α��ɂ��āA���̂Ƃ��͂��߂�臒l�𒴂����Ȃ�
			if (right >= w_cnt) {
				if (photo::get_displacement_from_center(PHOTO_TYPE::right)
						< wall_eage[PHOTO_TYPE::right]) {
					target_distance = WALL_EAGE_DISTANCE[PHOTO_TYPE::right];
					mouse::set_relative_go(0.045 * MOUSE_MODE - target_distance,
							true);	//��撆�������_�Ƃ��Ĉʒu���X�V
					mouse::set_distance_m(0);
					wall_eage_flag = false;
				}
			} else {
				//�ǃL����҂O�ɂ��������ǃL�����N����̂��𔻒f
				if (photo::get_displacement_from_center(PHOTO_TYPE::right)
						> wall_eage[PHOTO_TYPE::right])
					right++;
				else
					right = 0;
			}

		}

	}

	my7seg::turn_off();
	mouse::set_distance_m(0);
	GPIO_SetBits(GPIOC, GPIO_Pin_3);	//LED2
}

void run::accel_run_by_place(const COORDINATE finish, const float end_velocity,
		const unsigned char select_mode) {

	COORDINATE init = mouse::get_place();
	float max_velocity = parameter::get_run_max_velocity(select_mode);
	float accel_value = ABS(parameter::get_run_acceleration(select_mode));
	float de_accel_value = ABS(parameter::get_run_de_acceleration(select_mode));
	float de_accel_distance = ABS(
			mouse::get_ideal_velocity() * mouse::get_ideal_velocity()
			- end_velocity * end_velocity) / (2 * de_accel_value);	//�����ɕK�v�ȋ���

	if (finish.x == 0) {
		if (finish.y == 0) {			//x�����ɂ�y�����ɂ��ړ����Ȃ��ꍇ�͋��������Z�b�g���ďI��
			mouse::set_distance_m(0);
			return;
		}
	}

	float l_square = (finish.x - init.x) * (finish.x - init.x)
			+ (finish.y - init.y) * (finish.y - init.y);//�O�����̒藝����ړ�������2������߂�
	float tar_l = my_math::sqrt(l_square);
	float run_square = 0;		//���s�����Ǘ��p�ϐ�

	//����
	mouse::set_ideal_accel(accel_value);
	while (mouse::get_ideal_velocity() < max_velocity) {
		//���ݑ��x���猸���ɂ����鋗�����v�Z
		de_accel_distance = (mouse::get_ideal_velocity()
				* mouse::get_ideal_velocity() - end_velocity * end_velocity)
				/ (2 * de_accel_value);

		//��΍��W����ړ����������߂�
		run_square = (mouse::get_place().x - init.x)
				* (mouse::get_place().x - init.x);
		run_square += (mouse::get_place().y - init.y)
				* (mouse::get_place().y - init.y);
		//�����ɋ������K�v�ȋ���������Ȃ��Ȃ����甲����
		if (run_square
				>= (tar_l - de_accel_distance) * (tar_l - de_accel_distance)) {
			break;
		}

		if (mouse::get_fail_flag())
			return;
	}

	//����
	mouse::set_ideal_accel(0);
	while (1) {
		//���ݑ��x���猸���ɂ����鋗�����v�Z
		de_accel_distance = (mouse::get_ideal_velocity()
				* mouse::get_ideal_velocity() - end_velocity * end_velocity)
				/ (2 * de_accel_value);

		//��΍��W����ړ����������߂�
		run_square = (mouse::get_place().x - init.x)
				* (mouse::get_place().x - init.x);
		run_square += (mouse::get_place().y - init.y)
				* (mouse::get_place().y - init.y);

		//�����ɋ������K�v�ȋ���������Ȃ��Ȃ����甲����
		if (run_square
				>= (tar_l - de_accel_distance) * (tar_l - de_accel_distance)) {
			break;
		}

		if (mouse::get_fail_flag())
			return;
	}

	//����
	mouse::set_ideal_accel(-de_accel_value);
	while (mouse::get_ideal_velocity() > end_velocity) {
		//��΍��W����ړ����������߂�
		run_square = (mouse::get_place().x - init.x)
				* (mouse::get_place().x - init.x);
		run_square += (mouse::get_place().y - init.y)
				* (mouse::get_place().y - init.y);

		//���x����ɋ������Ȃ��Ȃ����甲����
		if (l_square < run_square) {
			break;
		}

		if (mouse::get_fail_flag())
			return;
	}
	mouse::set_ideal_accel(0);
	mouse::set_ideal_velocity(end_velocity);

	//���x0���Ƃ����ɕ����߂��Ă��܂�
	if (end_velocity > 0) {
		//�������x����ɖ����Ȃ��Ă��A�Ō�܂ő��肫��悤
		while (l_square > run_square) {
			//��΍��W����ړ����������߂�
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

	//�Q�C��
	static const PID gain_vel = { 0.2, 0.05, 0 }, gain_ang = { 0, 0, 0 };
	PID diff_vel = { 0 };	//�����̕΍�
	PID diff_ang = { 0 };	//�p�x�̕΍�

	//����
	mouse::set_ideal_accel(-de_accel_value);
	while (mouse::get_ideal_velocity() > 0) {		//���x���Ȃ��Ȃ�܂Ō���

		//���荞�݂ɑg�ݍ��ނ̖ʓ|������A�e���[�v1ms�҂��Ƃŋ^���I�ɐ�������œ�����
		while (time_count == wait::get_count())
			;		//1ms�o�܂ő҂�
		time_count = wait::get_count();			//�X�V

		//�K�i�����Ă݂�
		//front�̒l�����̂ق����u�����Ȃ��ĐM�p�ł���
		diff_front = 1
				- static_cast<float>(photo::get_value(PHOTO_TYPE::front))
						/ parameter::get_ideal_photo(PHOTO_TYPE::front);

		//	diff_front_left = 1
		//		- static_cast<float>(photo::get_value(PHOTO_TYPE::front_left))
		//					/ parameter::get_ideal_photo(PHOTO_TYPE::front_left);

		//�΍��v�Z
		diff_vel.P = (diff_front + diff_front_left);
		diff_vel.I += diff_vel.P * 0.001;		//�e���[�v1ms�Ȃ̂�
		diff_ang.P = (-diff_front + diff_front_left);
		diff_ang.I += diff_ang.P * 0.001;		//�e���[�v1ms�Ȃ̂�

		//���炩�ɂȂ���悤�ɁA���z���x�ƑO�ǐ���l���������炢�̎��Ɉڍs������
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
		//���荞�݂ɑg�ݍ��ނ̖ʓ|������A�e���[�v1ms�҂��Ƃŋ^���I�ɐ�������œ�����
		while (time_count == wait::get_count())
			;		//1ms�o�܂ő҂�
		time_count = wait::get_count();			//�X�V
		loop_count++;

		//�K�i�����Ă݂�
		//front�̒l�����̂ق����u�����Ȃ��ĐM�p�ł���
		diff_front = 1
				- static_cast<float>(photo::get_value(PHOTO_TYPE::front))
						/ parameter::get_ideal_photo(PHOTO_TYPE::front);

		//	diff_front_left = 1
		//		- static_cast<float>(photo::get_value(PHOTO_TYPE::front_left))
		//					/ parameter::get_ideal_photo(PHOTO_TYPE::front_left);

		//�΍��v�Z
		diff_vel.P = (diff_front + diff_front_left);
		diff_vel.I += diff_vel.P * 0.001;		//�e���[�v1ms�Ȃ̂�
		diff_ang.P = (-diff_front + diff_front_left);
		diff_ang.I += diff_ang.P * 0.001;		//�e���[�v1ms�Ȃ̂�

		mouse::set_ideal_velocity(
				diff_vel.P * gain_vel.P + diff_vel.I * gain_vel.I);

		//		mouse::set_ideal_angular_velocity(diff_ang.P * gain_ang.P + diff_ang.I * gain_ang.I );

		if (ABS(diff_vel.P) < 0.0025)
			break;

		if (loop_count > 1000)
			break;

		if (mouse::get_fail_flag())
			return;

		if (mouse::get_distance_m() > 0.02)
			break;

	}
	mouse::set_ideal_accel(0);
	mouse::set_ideal_velocity(0);
	mouse::set_distance_m(0);

	run::accel_run(0.02, 0, 0);

	//���X�ǐ��䂩�����Ă��Ȃ畜��
	if (wall_flag)
		control::start_wall_control();
}

void run::slalom(const SLALOM_TYPE slalom_type, const signed char right_or_left,
		const uint8_t select_mode) {
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
		return;
	}

	//�X�����[���̖ڕW�p�͑��ΓI�Ȋp�x�Ȃ̂ŁA�ŏ��̊p�x���L�^���Ă���
	float init_angle = mouse::get_angle_degree();
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
	mouse::set_ideal_angular_accel(angular_acceleration);
	while (ABS(mouse::get_angle_degree() - init_angle) < clothoid_angle_degree) {
//�t�F�C���Z�[�t���|�����Ă���΂����Ŕ�����
		if (mouse::get_fail_flag()) {
			return;
		}
		//�ő�p���x�ɒB������I��
		if (ABS(mouse::get_ideal_angular_velocity()) > ABS(max_angular)) {
			mouse::set_ideal_angular_velocity(max_angular);
			break;
		}
	}

//�������ɂ����l�̊p�x�������Ɨ\�z����邩��
//�Ǐ]�x��Ő�����������Ԃ̊p�x�̗��z�ƌ����̍����L�^���Ă���
	float def_angle = (clothoid_angle_degree
			- ABS(mouse::get_angle_degree() - init_angle));

//���p���x
	mouse::set_ideal_angular_accel(0);

	while (ABS(mouse::get_angle_degree() - init_angle)
			< (target_angle_degree - clothoid_angle_degree)) {
//�t�F�C���Z�[�t���|�����Ă���΂����Ŕ�����
		if (mouse::get_fail_flag()) {
			return;
		}

		de_accel_angle = degree(
		//(gyro::get_angular_velocity() * gyro::get_angular_velocity())
				(mouse::get_ideal_angular_velocity()
						* mouse::get_ideal_angular_velocity())
						/ (2 * angular_acceleration));

//�����ɕK�v�Ȋp�x���c���ĂȂ���Δ�����
		//�Ǐ]�x��̂��߂Ɍ����ɂ͗]���Ȋp�x���K�v�Ȃ͂�
		if ((ABS(de_accel_angle) + def_angle)
				>= (target_angle_degree
						- ABS(mouse::get_angle_degree() - init_angle))) {
			break;
		}

	}

//�p�������
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

//�t�F�C���Z�[�t���|�����Ă���΂����Ŕ�����
		if (mouse::get_fail_flag()) {
			return;
		}
	}

	mouse::set_ideal_angular_accel(0);
	mouse::set_ideal_angular_velocity(0);

	mouse::turn_direction_slalom(slalom_type, right_or_left);		//�}�E�X�̌�����ς���
	//TODO �}�E�X�̑��΍��W���ϊ�����

//��닗��������
	if (wall_flag)
		control::start_wall_control();	//���Ƃ��ƕǐ��䂪�������Ă��畜��������

	mouse::set_distance_m(0);
	distance = parameter::get_slalom((slalom_type), after_distance,
			right_or_left, select_mode);
	accel_run(distance, slalom_velocity, select_mode);
	control::reset_delta(sen_gyro);

}

void run::slalom_for_search(const SLALOM_TYPE slalom_type,
		const signed char right_or_left, const uint8_t select_mode) {

	my7seg::light(4);

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

	if (slalom_type == none) {
		return;
	}

	//�X�����[���̖ڕW�p�͑��ΓI�Ȋp�x�Ȃ̂ŁA�ŏ��̊p�x���L�^���Ă���
	float init_angle = mouse::get_angle_degree();
	control::reset_delta(sen_gyro);

	float correct = 0;	//�␳��

	if (photo::check_wall(front)) {
		correct = (photo::get_displacement_from_center(front));

	} else {
		if (mouse::get_relative_go() > 0) {
			correct = 0.045 - mouse::get_relative_go();
		} else {
			correct = -0.045 - mouse::get_relative_go();
		}
	}

	if (distance - correct > 0) {	//�O�����̕�����
		accel_run(distance - correct, slalom_velocity, select_mode);

	} else if (distance - correct < -0.045) {	//�I�[�o�[���߂����Ƃ��͒��M�n�ɂ���
		accel_run(distance - correct + 0.045 * MOUSE_MODE, 0, select_mode);
		mouse::turn_direction(right_or_left);	//������90���ς���
		//���v��肪��
		if (right_or_left == MUKI_RIGHT) {
			run::spin_turn(90);
			mouse::set_relative_go(-mouse::get_relative_displace(), false);	//�}�E�X�̑��΍��W���ϊ�����
			mouse::set_relative_displacement(mouse::get_relative_go(), false);
		} else {
			run::spin_turn(-90);
			mouse::set_relative_go(mouse::get_relative_displace(), false);//�}�E�X�̑��΍��W���ϊ�����
			mouse::set_relative_displacement(-mouse::get_relative_go(), false);
		}
		accel_run(0.045 * MOUSE_MODE, slalom_velocity, select_mode);	//�����O�i
		return;		//�X�����[���͂��Ȃ��ŏI��
	}

	bool wall_flag = control::get_wall_control_phase();
	control::stop_wall_control();

//���v��肪��
	if (right_or_left == MUKI_LEFT) {
		angular_acceleration = -ABS(angular_acceleration);
		max_angular = -ABS(max_angular);
	}
	mouse::set_ideal_angular_velocity(0);

//�p�������
	mouse::set_ideal_angular_accel(angular_acceleration);
	while (ABS(mouse::get_angle_degree() - init_angle) < clothoid_angle_degree) {
//�t�F�C���Z�[�t���|�����Ă���΂����Ŕ�����
		if (mouse::get_fail_flag()) {
			return;
		}
		//�ő�p���x�ɒB������I��
		if (ABS(mouse::get_ideal_angular_velocity()) > ABS(max_angular)) {
			mouse::set_ideal_angular_velocity(max_angular);
			break;
		}
	}

//�������ɂ����l�̊p�x�������Ɨ\�z����邩��
//�Ǐ]�x��Ő�����������Ԃ̊p�x�̗��z�ƌ����̍����L�^���Ă���
	float def_angle = (clothoid_angle_degree
			- ABS(mouse::get_angle_degree() - init_angle));

//���p���x
	mouse::set_ideal_angular_accel(0);

	while (ABS(mouse::get_angle_degree() - init_angle)
			< (target_angle_degree - clothoid_angle_degree)) {
//�t�F�C���Z�[�t���|�����Ă���΂����Ŕ�����
		if (mouse::get_fail_flag()) {
			return;
		}

		de_accel_angle = degree(
		//(gyro::get_angular_velocity() * gyro::get_angular_velocity())
				(mouse::get_ideal_angular_velocity()
						* mouse::get_ideal_angular_velocity())
						/ (2 * angular_acceleration));

//�����ɕK�v�Ȋp�x���c���ĂȂ���Δ�����
		//�Ǐ]�x��̂��߂Ɍ����ɂ͗]���Ȋp�x���K�v�Ȃ͂�
		if ((ABS(de_accel_angle) + def_angle)
				>= (target_angle_degree
						- ABS(mouse::get_angle_degree() - init_angle))) {
			break;
		}

	}

//�p�������
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

//�t�F�C���Z�[�t���|�����Ă���΂����Ŕ�����
		if (mouse::get_fail_flag()) {
			return;
		}
	}

	mouse::set_ideal_angular_accel(0);
	mouse::set_ideal_angular_velocity(0);

	mouse::turn_direction(right_or_left);	//������90���ς���
	//�}�E�X�̑��΍��W���ϊ�����
	if (right_or_left == MUKI_LEFT) {		//���v��肪��
		mouse::set_relative_base_rad(slalom_type, false);
		mouse::set_relative_go(-mouse::get_relative_displace(), false);
		mouse::set_relative_displacement(mouse::get_relative_go(), false);
	} else {
		mouse::set_relative_base_rad(slalom_type, true);
		mouse::set_relative_go(mouse::get_relative_displace(), false);
		mouse::set_relative_displacement(-mouse::get_relative_go(), false);
	}

//��닗��������
	if (wall_flag)
		control::start_wall_control();	//���Ƃ��ƕǐ��䂪�������Ă��畜��������

	mouse::set_distance_m(0);
	distance = parameter::get_slalom((slalom_type), after_distance,
			right_or_left, select_mode);
	accel_run(distance, slalom_velocity, select_mode);

	//TODO �X�����[���̂��тɊp���x�̕΍������Z�b�g���邩�͗v����
	//control::reset_delta(sen_gyro);

}

void run::spin_turn(const float target_degree) {
	float max_angular_velocity = 5.0;	//rad/s
	float angular_acceleration = 50.0;				//rad/s^2
	float angle_degree = 0;
	float init_angle = mouse::get_angle_degree();//������target_degree�͑��ΓI�Ȋp�x�Ȃ̂ŁA�ŏ��̊p�x���L�^���Ă���
	bool wall_flag = control::get_wall_control_phase();

	float sign = 1;		//�ڕW�p�x�̕������Ǘ�

	control::stop_wall_control();
	mouse::set_spin_flag(true);		//���M�n�J�n

//���v��肪��
	if (target_degree < 0) {
		angular_acceleration = -ABS(angular_acceleration);
		max_angular_velocity = -ABS(max_angular_velocity);
		sign = -1;
	}

	control::reset_delta(sen_encoder);
	control::reset_delta(sen_gyro);
	mouse::set_ideal_angular_velocity(0);

//�p�������
	mouse::set_ideal_angular_accel(angular_acceleration);

	while (sign * (mouse::get_angle_degree() - init_angle)
			< ABS(target_degree / 3)) {
		//�����ɕK�v�Ȋp�x���v�Z
		angle_degree = degree(
				(mouse::get_ideal_angular_velocity()
						* mouse::get_ideal_angular_velocity())
						/ (2 * angular_acceleration));
		//�����ɕK�v�Ȋp�x���c���ĂȂ���Δ�����
		if (ABS(angle_degree)
				>= sign
						* (target_degree
								- (mouse::get_angle_degree() - init_angle))) {
			break;
		}

		//�ő�p���x�ɒB������I��
		if (ABS(
				mouse::get_ideal_angular_velocity()) > ABS(max_angular_velocity)) {
			mouse::set_ideal_angular_velocity(max_angular_velocity);
			break;
		}

		if (mouse::get_fail_flag())
			return;

	}

//���p���x���
	mouse::set_ideal_angular_accel(0);
	while (1) {
		//�����ɕK�v�Ȋp�x���v�Z
		angle_degree = degree(
				(mouse::get_ideal_angular_velocity()
						* mouse::get_ideal_angular_velocity())
						/ (2 * angular_acceleration));
		//�����ɕK�v�Ȋp�x���c���ĂȂ���Δ�����
		if (ABS(angle_degree)
				>= sign
						* (target_degree
								- (mouse::get_angle_degree() - init_angle))) {
			break;
		}

		if (mouse::get_fail_flag())
			return;

	}

//�p�������
	mouse::set_ideal_angular_accel(-angular_acceleration);
	while (sign * (mouse::get_angle_degree() - init_angle) < ABS(target_degree)) {
		//���̏����t���Ȃ��ƁA��Ɋp���x��0�ɂȂ����ꍇ���܂ł����Ă����[�v�𔲂��Ȃ�
		if (ABS(mouse::get_ideal_angular_velocity()) < 0.5) {
			mouse::set_ideal_angular_accel(0);
		}

		if (mouse::get_fail_flag())
			return;
	}

	mouse::set_ideal_angular_accel(0);
	mouse::set_ideal_angular_velocity(0);
	mouse::set_distance_m(0);
	wait::ms(500);
	control::reset_delta(sen_gyro);

//���Ƃ��ƕǐ��䂩�����Ă��Ȃ畜��������
	if (wall_flag)
		control::start_wall_control();

	mouse::set_spin_flag(false);		//���M�n�I��
}

void run::path(const float finish_velocity, const unsigned char run_mode) {
	float next_velocity = 0;
	bool naname_flag = false;
	SLALOM_TYPE slalom_type;
	unsigned char slalom_muki;

	//FIX_ME ���m��ԉ����ł���悤�ɂȂ��ĂȂ�
	mouse::run_init(true, true);

	my7seg::count_down(3, 500);

	for (uint16_t path_count = 0; path::get_path_flag(path_count);
			path_count++) {

		//�z��O�ɂł�Ȃ�
		if (path_count >= PATH_MAX) {
			break;
		}

		if (mouse::get_fail_flag()) {		//�t�F�C���Z�[�t���|�����Ă�����I��
			break;
		}

		mouse::set_distance_m(0);

//�����̏���
		if (path::get_path_straight(path_count) == 0) {		//�������Ȃ��ꍇ
			//���ɏI����Ă��ꍇ
			if ((path::get_path_flag(path_count)) == false) {
				next_velocity = finish_velocity;
				//��O�����Ȃ̂ōŌ�̒����𑖂��ďI���
				run::accel_run(0.045 * MOUSE_MODE, next_velocity, run_mode);
				break;

			}
		} else {
			//���̃p�X�ŏI������ꍇ
			if ((path::get_path_flag(path_count + 1)) == false) {
				if (path::get_path_turn_type(path_count) == none) {	//���̒����ōŌ�
					next_velocity = finish_velocity;
					//��O�����Ȃ̂ōŌ�̒����𑖂��ďI���
					run::accel_run(path::get_path_straight(path_count),
							next_velocity, run_mode);
					break;

				} else {
					//���̃^�[�����x�ɍ��킹��
					next_velocity = parameter::get_slalom(
							path::get_path_turn_type(path_count), velocity,
							path::get_path_turn_muki(path_count), run_mode);

				}

			} else {
				//���̃^�[�����x�ɍ��킹��
				next_velocity = parameter::get_slalom(
						path::get_path_turn_type(path_count), velocity,
						path::get_path_turn_muki(path_count), run_mode);
			}

			if (naname_flag) {	//�i�i�����s��
				run::accel_run(path::get_path_straight(path_count),
						next_velocity, run_mode);

			} else {				//���ʂ̒��i
				control::start_wall_control();
				if (path_count == 0)	//�ŏ��̒��i�̏ꍇ�͕ǃL���ǂ߂Ȃ��C������̂ŕ��ʂɑ���
					run::accel_run(path::get_path_straight(path_count),
							next_velocity, run_mode);
				else
					run::accel_run_wall_eage(
							path::get_path_straight(path_count), next_velocity,
							run_mode, 0.045 * MOUSE_MODE);
			}

		}

		if (mouse::get_fail_flag()) {		//�t�F�C���Z�[�t���|�����Ă�����I��
			break;
		}

//�^�[���̏���
		slalom_type = path::get_path_turn_type(path_count);
		slalom_muki = path::get_path_turn_muki(path_count);

		run::slalom(slalom_type, slalom_muki, run_mode);

		//FIXME
		/*
		 switch (path::get_path_turn_type(path_count)) {
		 //�i�i���ɓ���Ȃ�
		 case begin_45:
		 case begin_135:
		 naname_flag = true;
		 break;
		 //�i�i������o��Ȃ�
		 case end_45:
		 case end_135:
		 naname_flag = false;
		 break;
		 default:
		 break;
		 }
		 */
	}

	wait::ms(100);
	motor::sleep_motor();

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
		if ((map::get_wall(target_x, target_y, muki) == false)) {		//�ǂ��Ȃ��Ȃ�
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

void adachi::run_next_action(const ACTION_TYPE next_action, bool slalom) {
	my7seg::light(2);
	static uint8_t str_score = 0;	//�ǐ����������钼�������A��������������
	bool check_right = false;//photo::check_wall(PHOTO_TYPE::right);
	bool check_left = false;//photo::check_wall(PHOTO_TYPE::left);

	my7seg::light(3);

	//�����łȂ�or ���݂����ȗ��ǂȂ��Ƃ��͕ǐ���M�p�ł��Ȃ��̂ŃX�R�A���Z�b�g
	if (next_action != go_straight)
		str_score = 0;
	else if (!(check_right || check_left))
		str_score = 0;

	if (mouse::get_fail_flag())
		return;

	switch (next_action) {
	case go_straight:
		//�ǂ�����ΐ��䂪������̂Ŏp����������邽�߁A�X�R�A���Z
		if (check_right)
			str_score++;
		if (check_left)
			str_score++;

		//1��Ԓ��i
		run::accel_run_wall_eage((0.09 * MOUSE_MODE), SEARCH_VELOCITY, 0,
				(0.09 * MOUSE_MODE));
		//���ǂ��蒼�����A��2��@���炢�̕␳���������Ă�����p����������Ă���Ɣ��f���p�x���C��
		if (str_score >= 4) {
			mouse::set_relative_rad(mouse::get_relative_rad() * 0.9, true);
		}
		break;

	case turn_right:
		//�X�����[�������M�n����
		if (slalom) {
			run::slalom_for_search(small, MUKI_RIGHT, 0);
		} else {
			run::accel_run((0.045 * MOUSE_MODE), 0, 0);
			run::spin_turn(90);
			run::accel_run((0.045 * MOUSE_MODE), SEARCH_VELOCITY, 0);
			mouse::turn_direction(MUKI_RIGHT);	//������90���ς���
		}
		break;

	case turn_left:
		//�X�����[�������M�n����
		if (slalom) {
			run::slalom_for_search(small, MUKI_LEFT, 0);
		} else {
			run::accel_run((0.045 * MOUSE_MODE), 0, 0);
			run::spin_turn(270);
			run::accel_run((0.045 * MOUSE_MODE), SEARCH_VELOCITY, 0);
			mouse::turn_direction(MUKI_LEFT);	//������90���ς���
		}
		break;

	case back: {
		//����Ԑi���180���^�[�����Ĕ���Ԓ��i

		//�O�ǂ�����ΑO�ǐ���
		float correct = 0;	//�␳��
		if (photo::check_wall(PHOTO_TYPE::front)) {
			correct = photo::get_displacement_from_center(front);//���̋��ڂ���ǂꂾ������Ă��邩
		}
		if (0.045 * MOUSE_MODE - correct < 0.016)//��������������؂�@��������1/64 2ax=v^2 a=2,v=0.25
			correct = 0.045 * MOUSE_MODE - 0.016;
		run::accel_run((0.045 * MOUSE_MODE) - correct, 0, 0);			//����Ԓ��i
		wait::ms(300);
		run::spin_turn(180 - degree(mouse::get_relative_rad()));//���Ίp�x�����肭�����悤�ɕύX����
		mouse::turn_direction(MUKI_RIGHT);	//������90���ς���
		mouse::turn_direction(MUKI_RIGHT);	//������90���ς���
		mouse::set_relative_base_rad(big_180, true);		//180����p�x�ύX
		mouse::set_relative_displacement(-mouse::get_relative_displace(),
				false);	//���΍��W�𔽓]������
		mouse::set_relative_go(-mouse::get_relative_go(), false);	//���΍��W�𔽓]������

		mouse::set_distance_m(0);
		run::accel_run(-(0.02 * MOUSE_MODE), 0, 0);	//����Ԓ��i
		if (check_right | check_left) {
			run::accel_run_wall_eage((0.065 * MOUSE_MODE), SEARCH_VELOCITY, 0,
					(0.03 * MOUSE_MODE));	//����Ԓ��i
		} else {
			run::accel_run((0.065 * MOUSE_MODE) - mouse::get_relative_go(),
			SEARCH_VELOCITY, 0);	//����Ԓ��i
		}
		break;
	}
	case stop:
		//����Ԑi��ŃX�g�b�v
		run::accel_run((0.045 * MOUSE_MODE), 0, 0);			//����Ԓ��i
		break;
	}
	return;
}

void adachi::simulate_next_action(ACTION_TYPE next_action) {
	switch (next_action) {
	case go_straight:
		//1��Ԓ��i
		break;

	case turn_right:
		//����ԁ˒��M�n�˔����
		mouse::turn_direction(MUKI_RIGHT);	//������90���ς���
		break;

	case turn_left:
		//����ԁ˒��M�n�˔����
		mouse::turn_direction(MUKI_LEFT);	//������90���ς���
		break;

	case back:
		//����Ԑi���180���^�[�����Ĕ���Ԓ��i
		mouse::turn_direction(MUKI_RIGHT);	//������90���ς���
		mouse::turn_direction(MUKI_RIGHT);	//������90���ς���
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

ACTION_TYPE adachi::get_next_action(compas next, compas now) {
	std::pair<int8_t, int8_t> next_dir = compas_to_direction(next);
	std::pair<int8_t, int8_t> now_dir = compas_to_direction(now);

	//next��now�̓��ς��Ƃ�
	switch (next_dir.first * now_dir.first + next_dir.second * now_dir.second) {
	case 1:		//��������
		return go_straight;
		break;
	case -1:	//�t����
		return back;
		break;
	case 0:		//���E�ǂ��炩�̃^�[��
		//��]�s����l���āA0�łȂ������̕������ǂ��ω����Ă��邩�ō��E�ǂ���̉�]���킩��͂�
		if (now_dir.first == 0) {		//x��0�̎�
			if (next_dir.first * now_dir.second == 1)
				return turn_right;
			else
				return turn_left;
		} else if (now_dir.second == 0) {	//����0�̎�
			if (next_dir.second * now_dir.first == -1)
				return turn_right;
			else
				return turn_left;
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
//�������擾
		mouse::get_direction(&direction_x, &direction_y);

//���W���X�V
		now_x = mouse::get_x_position() + direction_x;
		now_y = mouse::get_y_position() + direction_y;
		mouse::set_position(now_x, now_y);

//�Ǐ��X�V
		mouse::look_wall(false);

//�ڕW�̍��W�ɂ��ǂ蒅������I��
		if ((now_x == target_x) && (now_y == target_y)) {
			run_next_action(stop, true);
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
				priority_direction.all = 0;			//���̕����͂���Ȃ��̂Ń��Z�b�g
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
				priority_direction.all = 0;			//���̕����͂���Ȃ��̂Ń��Z�b�g
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
				priority_direction.all = 0;			//���̕����͂���Ȃ��̂Ń��Z�b�g
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
				priority_direction.all = 0;			//���̕����͂���Ȃ��̂Ń��Z�b�g
				priority_direction.element.down = 1;
			}

		}

//���T����Ԃ����̒��ɂ���Ȃ�A���ɍs�������͂��̒�����I��
		if ((priority_direction.all != 0) && is_FULUKAWA) {
			next_direction.all = priority_direction.all;
		}

//next_dirrction���玟�s��������I�сA�s������
		next_action = get_next_action(next_direction, mouse::get_direction());
		run_next_action(next_action, true);
		my7seg::turn_off();

		//�����~�܂�ׂ��Əo���Ȃ�R�R�ő����@����߂�
		if (next_action == stop) {
			adachi_flag = false;
		}

	}

	if (adachi_flag) {
		//�����@�����Ȃ̂Ń}�b�v��ۑ�����
		map::output_map_data(&mouse::now_map);
		return true;				//�����@����!!

	} else {
//�����ɗ���Ƃ������Ƃ͑����@�����s���Ă�
		motor::sleep_motor();
		COORDINATE place = mouse::get_place();
		float displace = mouse::get_relative_displace();
		float go = mouse::get_relative_go();
//TODO �킩��₷���������~����
		mouse::error();
		myprintf("Adachi method failed!\n\r");
		if (mouse::get_fail_flag()) {
			myprintf("fail safe!\n\r");
		}

		myprintf("now -> (%d,%d)\n\r", mouse::get_x_position(),
				mouse::get_y_position());
		myprintf("place -> (%f,%f)\n\r", place.x, place.y);
		myprintf("relative (displace,go)-> (%f,%f)\n\r", displace, go);
	}

	return false;
}

/*
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
 //�������擾
 mouse::get_direction(&direction_x, &direction_y);

 //���W���X�V
 now_x = mouse::get_x_position() + direction_x;
 now_y = mouse::get_y_position() + direction_y;
 mouse::set_position(now_x, now_y);

 //�Ǐ��X�V
 mouse::velify_wall();
 mouse::look_wall(false);

 //�ڕW�̍��W�ɂ��ǂ蒅������I��
 if ((now_x == target_x) && (now_y == target_y)) {
 run_next_action(stop, false);
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
 priority_direction.all = 0;			//���̕����͂���Ȃ��̂Ń��Z�b�g
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
 priority_direction.all = 0;			//���̕����͂���Ȃ��̂Ń��Z�b�g
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
 priority_direction.all = 0;			//���̕����͂���Ȃ��̂Ń��Z�b�g
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
 priority_direction.all = 0;			//���̕����͂���Ȃ��̂Ń��Z�b�g
 priority_direction.element.down = 1;
 }

 }

 //���T����Ԃ����̒��ɂ���Ȃ�A���ɍs�������͂��̒�����I��
 if ((priority_direction.all != 0) && is_FULUKAWA) {
 next_direction.all = priority_direction.all;
 }

 //next_dirrction���玟�s��������I�сA�s������
 next_action = get_next_action(next_direction, mouse::get_direction());
 run_next_action(next_action, false);

 //�����~�܂�ׂ��Əo���Ȃ�R�R�ő����@����߂�
 if (next_action == stop) {
 adachi_flag = false;
 }

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
 */

bool adachi::adachi_method_place(unsigned char target_x, unsigned char target_y,
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

	COORDINATE next_place = mouse::get_place();	//�ړ���̋������Ǘ�����ϐ�
	next_place.y += (0.045 * MOUSE_MODE);		//�ŏ��̔���Ԓ��i
	run::accel_run_by_place(next_place, SEARCH_VELOCITY, 0);

	while (adachi_flag) {
//�t�F�C���Z�[�t���|�����Ă���΂����Ŕ�����
		if (mouse::get_fail_flag()) {
			adachi_flag = false;
			break;
		}

//�������擾
		mouse::get_direction(&direction_x, &direction_y);

//���W���X�V
		now_x = mouse::get_x_position() + direction_x;
		now_y = mouse::get_y_position() + direction_y;
		mouse::set_position(now_x, now_y);

//�Ǐ��X�V
		mouse::velify_wall();
		mouse::look_wall(false);

//�ڕW�̍��W�ɂ��ǂ蒅������I��
		if ((now_x == target_x) && (now_y == target_y)) {
			run_next_action(stop, false);
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
				priority_direction.all = 0;			//���̕����͂���Ȃ��̂Ń��Z�b�g
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
				priority_direction.all = 0;			//���̕����͂���Ȃ��̂Ń��Z�b�g
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
				priority_direction.all = 0;			//���̕����͂���Ȃ��̂Ń��Z�b�g
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
				priority_direction.all = 0;			//���̕����͂���Ȃ��̂Ń��Z�b�g
				priority_direction.element.down = 1;
			}

		}

//���T����Ԃ����̒��ɂ���Ȃ�A���ɍs�������͂��̒�����I��
		if ((priority_direction.all != 0) && is_FULUKAWA) {
			next_direction.all = priority_direction.all;
		}

//next_dirrction���玟�s��������I�сA�s������
		next_action = get_next_action(next_direction, mouse::get_direction());
		if (next_action != go_straight)
			run_next_action(next_action, true);
		else {		//���i�̏ꍇ�́A�ʏ�Ƃ͈قȂ��΍��W��̒��i���s��
			signed char dx, dy;
			mouse::get_direction(&dx, &dy);
			//���ɂǂ̋��ڂɍs���̂��H
			next_place.x = 0.045 * MOUSE_MODE
					* (2 * mouse::get_x_position() + 1 + dx);
			next_place.y = 0.045 * MOUSE_MODE
					* (2 * mouse::get_y_position() + 1 + dy);
			run::accel_run_by_place(next_place, SEARCH_VELOCITY, 0);
		}

		//�����~�܂�ׂ��Əo���Ȃ�R�R�ő����@����߂�
		if (next_action == stop) {
			adachi_flag = false;
		}

	}

	if (adachi_flag) {
		//�����@�����Ȃ̂Ń}�b�v��ۑ�����
		map::output_map_data(&mouse::now_map);
		return true;				//�����@����!!

	} else {
//�����ɗ���Ƃ������Ƃ͑����@�����s���Ă�
		COORDINATE fin_pl = mouse::get_place();
		COORDINATE rel_pl;
		rel_pl.x = mouse::get_relative_displace();
		rel_pl.y = mouse::get_relative_go();
		motor::sleep_motor();
//TODO �킩��₷���������~����
		mouse::error();
		myprintf("Adachi method failed!\n\r");
		if (mouse::get_fail_flag()) {
			myprintf("fail safe!\n\r");
		}

		myprintf("now -> (%d,%d)\n\r", mouse::get_x_position(),
				mouse::get_y_position());
		myprintf("ABSpostion (x,y)=(%f,%f)\n\r", fin_pl.x, fin_pl.y);
		myprintf("RELpostion (side,go)=(%f,%f)\n\r", rel_pl.x, rel_pl.y);
	}

	return false;
}

/*
 bool adachi::left_hand_method(const uint8_t target_x, const uint8_t target_y) {
 bool search_flag = true;	//�r���Ń~�X����������false��
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

	search.input_map_data(&mouse::now_map);		//�ۑ����Ă����}�b�v��ǂ݂���
	search.set_weight_algo(method);		//�d�݂Â��̕��@��ݒ�
	search.spread_step(finish, false);		//�����}�b�v���쐻

	bool success_flag = true;	//�r���Ń~�X����������false��
	unsigned char now_x, now_y;	//���W�ꎞ�ۑ��p�B���Ղ��̂���
	compas next_compas;		//���p�ꎞ�ۑ��p�B���₷���̂��߁B
	uint16_t next_step = search.init_step;		//���̕����ۑ��p�B���₷���̂��߁B
	ACTION_TYPE next_action;	//���̍s�����Ǘ�

	my7seg::turn_off();

	search.spread_step(finish, false);		//�����}�b�v���쐻

	mouse::get_direction(&direction_x, &direction_y);	//�������擾

	mouse::run_init(true, true);

	my7seg::count_down(3, 500);

	run::accel_run((0.045 * MOUSE_MODE), SEARCH_VELOCITY, 0);

	//����Ԑi�񂾃m�[�h��0�Ȃ�A�ڂ̑O�̃}�X���S�[���Ȃ̂ŏI��
	if (search.get_step(now_x, now_y, muki_to_compas(mouse::get_direction()))
			== 0) {
		run_next_action(stop, true);
		//�����@�����Ȃ̂Ń}�b�v��ۑ�����
		map::output_map_data(&mouse::now_map);
		return true;				//�����@����!!
	}

	while (success_flag) {
		//�t�F�C���Z�[�t���|�����Ă���΂����Ŕ�����
		if (mouse::get_fail_flag()) {
			success_flag = false;
			break;
		}

		//�������擾
		mouse::get_direction(&direction_x, &direction_y);

		//���W���X�V
		now_x = mouse::get_x_position() + direction_x;
		now_y = mouse::get_y_position() + direction_y;
		mouse::set_position(now_x, now_y);

		//�Ǐ��X�V
		//mouse::velify_wall();
		mouse::look_wall(false);

		//�O��A����0�Ɉړ����Ă�����I��
		if (next_step == 0) {
			run_next_action(stop, false);
			break;
		}

		//�����}�b�v�쐻
		search.spread_step(finish, false);		//�����}�b�v���쐻

		//�ł������̏������m�[�h�֌�����
		next_compas = search.get_min_compas(now_x, now_y);
		next_step = search.get_step(now_x, now_y, next_compas);
		if (next_step == search.init_step) {	//�ŏ������������l�͖��H���ӂ�����Ă�
			success_flag = false;
			run_next_action(stop, false);
			break;
		}

		//next_dirrction���玟�s��������I�сA�s������
		next_action = get_next_action(next_compas,
				muki_to_compas(mouse::get_direction()));
		run_next_action(next_action, true);

		//�����~�܂�ׂ��Əo���Ȃ�R�R�ő����@����߂�
		if (next_action == stop) {
			success_flag = false;
		}

	}

	if (success_flag) {
		//�����@�����Ȃ̂Ń}�b�v��ۑ�����
		map::output_map_data(&mouse::now_map);
		return true;				//�����@����!!

	} else {
		//�����ɗ���Ƃ������Ƃ͑����@�����s���Ă�
		COORDINATE fin_pl = mouse::get_place();
		COORDINATE rel_pl;
		rel_pl.x = mouse::get_relative_displace();
		rel_pl.y = mouse::get_relative_go();
		motor::sleep_motor();
		//TODO �킩��₷���������~����
		mouse::error();
		myprintf("Adachi method failed!\n\r");
		if (mouse::get_fail_flag()) {
			myprintf("fail safe!\n\r");
		}
		if (next_step == search.init_step) {	//�ŏ������������l�͖��H���ӂ�����Ă�
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

