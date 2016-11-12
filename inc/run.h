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
#include"map.h"

//position
typedef union {
	unsigned char all;
	struct {
		unsigned char x :4;
		unsigned char y :4;
	} bit;
} POSITION;

class mouse {
private:
	static float ideal_acceleration;			//�}�E�X�̉����x[m/s^2]
	static float ideal_angular_acceleration;			//�}�E�X�̉��p���x[rad/s^2]

	static float ideal_velocity;			//�}�E�X�̖ڕW���x[m/s]
	static float ideal_angular_velocity;			//�}�E�X�̖ڕW�p���x[rad/s]

	//���z�l����v�Z���������Ɗp�x
	static float ideal_distance;
	static float ideal_angle;

	static float run_distance;			//�}�E�X�̑��s����[m]

	static unsigned long mouse_count_ms;			//�}�E�X�̎���[msec].��{���Z�b�g���Ȃ�

	static bool fail_flag;		//�t�F�C���Z�[�t��������Ƃ��̃t���O��TRUE��

	static POSITION position;		//�}�E�X�̈ʒu�i���W�j
	static unsigned char mouse_direction;		//�}�E�X�̌���

	static void cal_velocity();		//�������s���B���x�̉����Z
	static void cal_distance();		//�����v�Z

	mouse();

public:

	static MAP_DATA now_map;

	static void reset_count();
	static void add_one_count_ms();		//�J�E���g��1���Z�B���荞�ݓ��݂̂ŌĂяo��
	static unsigned long get_count_ms();		//�J�E���g�擾�B�P�ʂ�ms

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

	static float get_distance_m();		//�������擾
	static void set_distance_m(const float set_value_m);		//�������Z�b�g

	static unsigned char get_x_position();
	static unsigned char get_y_position();
	static void set_position(const uint8_t set_x, const uint8_t set_y);

	static unsigned char get_direction();	//define���ꂽMUKI_??�ŕԂ�
	static void get_direction(signed char *direction_x,
			signed char *direction_y);		//�����̒l���|�C���^�o�R�ŕύX����
	static void set_direction(const unsigned char muki);
	static void set_direction(const signed char direction_x,
			const signed char direction_y);

	static bool get_fail_flag();		//�t�F�C���Z�[�t�������������ǂ����̔��ʗp
	static void set_fail_flag(bool set_flag);

	static void interrupt();	//���荞�݊֐����Ŏ��s����悤

	static void run_init(bool posture_ctrl, bool wall_ctrl);	//���钼�O�Ɏ��s������

	//�ǂ����āA�ǂ����݂���Ȃ�ǂ����A�Ȃ��Ȃ�󂷁B�������Ƃ��L�^
	//�}�E�X�̌�������W�������ł�����ƍl����
	static void look_wall(bool comb_ignore);	//�ǂ�����֐�

	//�ǂ����邩�m�F�p�̊֐�
	static void velify_wall();

	static void error();	//�t�F�C���Z�[�t�Ƃ��A�����������ɁA�����ɔ�т܂���

	~mouse();

};

class run {
private:
	run();
	static uint8_t WALL_EAGE_DISTANCE[PHOTO_TYPE::element_count];

public:
	static void accel_run(const float distance_m, const float end_velocity,
			const unsigned char select_mode);
	static void accel_run_wall_eage(const float distance_m, const float end_velocity,
			const unsigned char select_mode, const float check_distance);

	static void slalom(const SLALOM_TYPE slalom_type, const signed char right_or_left,const uint8_t select_mode);
	static void spin_turn(const float target_degree);
	~run();

};

//ACTION_TYPE �����@�̂Ƃ����Ɏ��s���̎��
typedef enum {
	go_straight, turn_right, turn_left, back, stop
} ACTION_TYPE;

class adachi {
private:
	static signed char direction_x, direction_y;

	static void set_direction();

	//���݂̍��W�ƌ�����^����ƕ����I�ɂ��̃}�X�ɐi�߂邩�𔻕�
	static bool check_move_by_step(unsigned char target_x,
			unsigned char target_y, unsigned char muki);

	//�ڕW�̃}�X�̂܂����ĂȂ��ǂ̐��𐔂��グ��
	static unsigned int count_unknown_wall(unsigned char target_x,
			unsigned char target_y);

	//�����ɉ����Ď��̍s�����}�E�X�����s����i���ۂɓ��������j
	static void run_next_action_by_spin(ACTION_TYPE next_action);
	static void run_next_action(ACTION_TYPE next_action);
	static void simulate_next_action(ACTION_TYPE next_action);//�@�͓̂����Ȃ��B���z�I�ɕϐ��Ƃ��X�V�B�f�o�b�N�p

	//���s�������ƍ��̌�����^����ƁA���Ɏ��s����Ԃ��B�D��x�́A���i�A�E�^�[���A���^�[���A�o�b�N�̏�
	static ACTION_TYPE get_next_action(DIRECTION next_direction,
			uint8_t now_muki);

	adachi();

public:
	static bool adachi_method(const unsigned char target_x,
			const unsigned char target_y, bool is_FULUKAWA);
	static bool adachi_method_spin(unsigned char target_x,
			unsigned char target_y, bool is_FULUKAWA);

	static bool left_hand_method(const uint8_t target_x,
			const uint8_t target_y);
	~adachi();

};

#endif /* RUN_H_ */
