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
#include"flash.h"
#include <queue>
#include<cmath>

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
	static float ideal_angle_degree;
	//�}�E�X�̐i�s�����ɑ΂��Ă̑��Ίp�x[rad]�̊�@���̊p�x�Ɛ�Ίp�x�̍������Ίp�x
	static float relative_base_rad;
	//�}�E�X�̎��ۂ̑��x[m/s]�Ƌ���[m]
	static float velocity;
	static float run_distance;
	//�}�E�X�̐�Έʒu[m]
	static COORDINATE place;
	//�}�E�X�̋����ɑ΂��鑊�Έʒu[m] ���_�͋�撆��
	static COORDINATE relative;

	static unsigned long mouse_count_ms;			//�}�E�X�̎���[msec].��{���Z�b�g���Ȃ�

	static bool is_fail_safe;		//�t�F�C���Z�[�t��������Ƃ��̃t���O��TRUE��
	static bool is_spin_turn;

	static POSITION position;		//�}�E�X�̈ʒu�i���W�j
	//static unsigned char mouse_direction;		//�}�E�X�̌���
	static compas direction;		//�}�E�X�̌���

	static void cal_velocity();		//�������s���B���x�̉����Z
	static void cal_distance();		//�����v�Z
	static void cal_place();		//�ʒu���v�Z����@���H�̍��W�Ǝ��̕����͓���

	mouse();

public:

	static MAP_DATA now_map;

	static void reset_count();
	static void add_one_count_ms();		//�J�E���g��1���Z�B���荞�ݓ��݂̂ŌĂяo��
	static unsigned long get_count_ms();		//�J�E���g�擾�B�P�ʂ�ms

	static float get_ideal_accel();
	static void set_ideal_accel(const float set_value_m_ss);

	static float get_ideal_angular_accel();
	static void set_ideal_angular_accel(const float set_value_m_ss);

	static float get_ideal_velocity();
	static void set_ideal_velocity(const float set_value_m_s);
	static float get_velocity();

	static float get_ideal_angular_velocity();
	static void set_ideal_angular_velocity(const float set_value_rad_s);
	static float get_angular_velocity();

	static void set_ideal_ang(const float ang_a, const float ang_omega);
	static void set_ang(const float set_rad);
	static float get_ideal_angle_degree();
	static float get_ideal_angle_radian();
	static float get_angle_degree();
	static float get_angle_radian();
	static void reset_angle();

	static void set_ideal(const float accel, const float vel, const float dis);

	static float get_distance_m();		//�������擾
	static void set_distance_m(const float set_value_m);		//�������Z�b�g

	static unsigned char get_x_position();
	static unsigned char get_y_position();
	static void set_position(const uint8_t set_x, const uint8_t set_y);

	static void set_place(const COORDINATE set);
	static void set_place(const float x, const float y);
	static COORDINATE get_place();

	//TODO �֐����������Ƃ킩��₷��������
	static float get_relative_side();		//�i�s�����Ɛ��������ɂǂꂾ������Ă��邩[m] �}�E�X���猩�ĉE����
	static float get_relative_go();		//��撆�S�����_�Ƃ����Ƃ��A�i�s�����ɂǂꂾ���i��ł��邩[m]
	static void set_relative_go(float set_value, bool updata_abs);		//updata_abs �͐�΍��W���X�V���邩�ǂ���
	static void set_relative_side(float set_value, bool updata_abs);		//updata_abs �͐�΍��W���X�V���邩�ǂ���

	static float get_relative_rad();		//�i�s������0�Ƃ����Ƃ��ɂǂꂾ������Ă��邩
	static void set_relative_rad(float set_rad, bool updata_abs);		//relative_rad��set_rad�ɂȂ�悤�ɏC������
	static void set_relative_base_rad(SLALOM_TYPE sla, bool is_right);	//�^�[�����́A���Ίp�x�̊�ύX�p

	//static unsigned char get_direction();	//define���ꂽMUKI_??�ŕԂ�
	static compas get_compas();	//define���ꂽMUKI_??�ŕԂ�
	static void get_direction(signed char *direction_x,
				signed char *direction_y);		//�����̒l���|�C���^�o�R�ŕύX����
	static void get_direction(float *dir_x, float *dir_y);		//�΂ߑΉ�
	static void set_direction(const compas dir);
	static void set_direction(const signed char direction_x,
			const signed char direction_y);

	static bool get_fail_flag();		//�t�F�C���Z�[�t�������������ǂ����̔��ʗp
	static void set_fail_flag(bool set_flag);

	static bool get_spin_flag();		//�����M�n���񂵂Ă��邩�ǂ���
	static void set_spin_flag(bool is_spin);

	static void interrupt();	//���荞�݊֐����Ŏ��s����悤

	static void run_init(bool posture_ctrl, bool wall_ctrl);	//���钼�O�Ɏ��s������

	//�ǂ����āA�ǂ����݂���Ȃ�ǂ����A�Ȃ��Ȃ�󂷁B�������Ƃ��L�^
	//�}�E�X�̌�������W�������ł�����ƍl����
	static void look_wall(bool comb_ignore);	//�ǂ�����֐�

	//�ǂ����邩�m�F�p�̊֐�	�ǂ����������LED������
	static void velify_wall();

	static void turn_90_dir(const unsigned char right_or_left);
	static void turn_45_dir(bool is_right);
	static void turn_direction_slalom(const SLALOM_TYPE slalom_type, const unsigned char right_or_left);

	static void error();	//�t�F�C���Z�[�t�Ƃ��A�����������ɁA�����ɔ�т܂���

	~mouse();

};

class run {
private:
	run();
public:
	static float WALL_EAGE_DISTANCE[PHOTO_TYPE::element_count];

public:
	static void accel_run(const float distance_m, const float end_velocity,
				const unsigned char select_mode);
	static void accel_run_wall_eage(const float distance_m,
			const float end_velocity, const unsigned char select_mode,
			const float check_distance);		//�T���p
	static void path_run_wall_eage(const float distance_m,
			const float end_velocity, const unsigned char select_mode);	//�ŒZ�̑��X�����[���̑O�����p
	static void accel_run_by_distance(const float tar_L_m, const float end_velocity,
				const unsigned char select_mode);	//���荞�݂̐ώZ�����ł͂Ȃ��A�������W�ƌ��ݍ��W�̊Ԃ̋������l����
	static void accel_run_by_place(const COORDINATE finish, const float end_velocity,
				const unsigned char select_mode);	//��΍��W����ɑ���B ���ݍ��W�ƖڕW���W�̋����ōl����


	static void fit_run(const unsigned char select_mode);//�O�ǂɑ΂��Ă��܂������悤�ɒ������Ď~�܂�

	static void slalom(const SLALOM_TYPE slalom_type,
			const signed char right_or_left, const uint8_t select_mode);
	//�T���p�̃X�����[���B
	static void slalom_for_search(const SLALOM_TYPE slalom_type,
			const signed char right_or_left, const uint8_t select_mode);
	static void spin_turn(const float target_degree);

	static void path(const float finish_velocity, const uint8_t _straight, const uint8_t _curve);

	~run();

};

//ACTION_TYPE �����@�̂Ƃ����Ɏ��s���̎��
typedef enum {
	go_straight, turn_right, turn_left, back, stop
} ACTION_TYPE;

class adachi {
private:
	static signed char direction_x, direction_y;

	//���݂̍��W�ƌ�����^����ƕ����I�ɂ��̃}�X�ɐi�߂邩�𔻕�
	static bool check_move_by_step(unsigned char target_x,
			unsigned char target_y, unsigned char muki);

	//�ڕW�̃}�X�̂܂����ĂȂ��ǂ̐��𐔂��グ��
	static unsigned int count_unknown_wall(unsigned char target_x,
			unsigned char target_y);

	//�����ɉ����Ď��̍s�����}�E�X�����s����i���ۂɓ��������j
	static void run_next_action(const ACTION_TYPE next_action, bool slalom);
	static void simulate_next_action(ACTION_TYPE next_action);//�@�͓̂����Ȃ��B���z�I�ɕϐ��Ƃ��X�V�B�f�o�b�N�p

	//���s�������ƍ��̌�����^����ƁA���Ɏ��s����Ԃ��B�D��x�́A���i�A�E�^�[���A���^�[���A�o�b�N�̏�
	static ACTION_TYPE get_next_action_old(DIRECTION next_direction, uint8_t now_muki);
	static ACTION_TYPE get_next_action(compas next, compas now);

public:
	static bool adachi_method(const unsigned char target_x,
			const unsigned char target_y, bool is_FULUKAWA);
	//static bool adachi_method_spin(unsigned char target_x,unsigned char target_y, bool is_FULUKAWA);
	static bool adachi_method_place(unsigned char target_x,
			unsigned char target_y, bool is_FULUKAWA);		//���i���̋����̊Ǘ����I�h���g�����狁�߂���΍��W�ɂ���Ver

	//static bool left_hand_method(const uint8_t target_x,const uint8_t target_y);


	static bool node_adachi(std::vector< std::pair<uint8_t, uint8_t> > finish, weight_algo method);		//�m�[�h�^�����}�b�v�ő����@

	adachi();
	~adachi();

};


#endif /* RUN_H_ */
