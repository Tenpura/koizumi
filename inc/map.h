/*
 * map.h
 *
 *  Created on: 2016/10/29
 *      Author: Koizumi
 */

#ifndef MAP_H_
#define MAP_H_

#include "stm32f4xx.h"
#include"define.h"
#include"extern_c.h"
#include"user.h"
#include <queue>

extern uint32_t loop;	//�f�o�b�N�p�@�����}�b�v�������̃��[�v�񐔂𐔂��Ă�

//TODO ����static�ɂ��ׂ��ŁA�������[�J���̂܂܂Œu���ׂ���

class map {

//�����o�ϐ�
private:
	//unsigned char x,y;//���W
	static MAZE_WALL x_maze_wall[MAZE_SIZE], y_maze_wall[MAZE_SIZE]; //�Ǐ��ۑ��p
	static MAZE_WALL x_wall_exist[MAZE_SIZE], y_wall_exist[MAZE_SIZE]; //�Ǐ����������ǂ������ʗp

protected:
	static void set_maze_wall(MAZE_WALL* const maze_wall,
			unsigned char edit_number, bool is_wall); //maze_wall�ɒl��������p
	static bool get_maze_wall(MAZE_WALL maze_wall, unsigned char edit_number); //maze_wall�̒l��ǂޗp

public:
	static void create_wall(unsigned char wall_x, unsigned char wall_y,
			unsigned char muki); //(x,y)��muki�����̕ǂ����
	static void destroy_wall(unsigned char wall_x, unsigned char wall_y,
			unsigned char muki);
	//�ǂ������define���ꂽTRUE�A�Ȃ����FALSE���Ԃ��Ă���B���H�O���ƃG���[�ɓ���o�͂́|1
	static bool get_wall(unsigned char wall_x, unsigned char wall_y,
			unsigned char muki);

	static void remember_exist(unsigned char wall_x, unsigned char wall_y,
			unsigned char muki); //(x,y)��muki�����̕ǂ����
	static void forget_exist(unsigned char wall_x, unsigned char wall_y,
			unsigned char muki);
	//�ǂ��������Ƃ������define���ꂽTRUE�A�Ȃ����FALSE���Ԃ��Ă���B���H�O���ƃG���[�ɓ���o�͂́|1
	static bool check_exist(unsigned char wall_x, unsigned char wall_y,
			unsigned char muki);
	static bool check_exist(unsigned char wall_x, unsigned char wall_y,
			compas dir);

	static void reset_maze();		//�Ǐ��ƌ������ǂ��������ׂă��Z�b�g

	static void draw_map(bool write_step);		//myprintf�Ŗ��H��`��
	void convert_mapdata(unsigned char (*hiramatu_data)[16]);//������y�̃}�b�v�f�[�^�`�����m�m�z���ɕϊ�

	static void input_map_data(const MAP_DATA* input_data);		//�O���ɕۑ������f�[�^�̓���
	static void output_map_data(MAP_DATA* output_data);		//�O���Ƀf�[�^�o��

	map();
	~map();

};

#define STEP_INIT 1025		//�����̏����l
class step {
private:
	static DIRECTION save_direction;				//���ɍs���}�X�̕�����ۑ�
	static unsigned short maze_step[MAZE_SIZE][MAZE_SIZE];

	static void step_reset();
	static void close_one_dead_end(unsigned char target_x,
			unsigned char target_y);

public:
	static void spread_step(uint8_t tar_x, uint8_t tar_y, bool by_known);//C++��Queue���g���ĕ����}�b�v�쐻
	static bool set_step(uint8_t _x, uint8_t _y, uint8_t _muki,
			uint8_t _set_step, bool _by_known);	//(x,y)��muki��set_step���������ށ@�������߂���true

//	static void set_step(unsigned char target_x,unsigned char target_y);//target_x,y����ɕ����}�b�v�쐻(������)
//	static void set_step_by_known(unsigned char target_x,unsigned char target_y);//���Ă��Ȃ��ǂ́A�ǂ�����ƌ��Ȃ�

	static unsigned int get_step(unsigned char target_x,
			unsigned char target_y);		//������W(x,y)�̕�����Ԃ�

	static void close_dead_end();		//�}�b�v��̑܏��H���Ԃ�

	step();
	step(const MAP_DATA* input_data);
	~step();
};

class path: public step {
private:
	typedef union {
		unsigned char all;				//�ꊇ
		struct {
			unsigned char up :1;		//��	x=1,y=0�̕���
			unsigned char right :1;		//��	x=-1,y=0�̕���
			unsigned char down :1;		//��	x=0,y=-1�̕���
			unsigned char left :1;		//��	x=0,y=1�̕���
			unsigned char now :4;//���݂̕������Ǘ��A���̐��Asave_direction���r�b�g�V�t�g����ƌ��݂̌����ɑΉ�
		} element;
	} SAVE_DIRECTION;				//���ɍs���}�X�̕�����ۑ�
	static PATH path_memory[PATH_MAX];	//flag�͑��s�t���O

	static void set_step_for_shortest(unsigned char target_x,
			unsigned char target_y);	//�ŒZ�p�̕����}�b�v�쐻
	static void displace_path(unsigned int path_number);//path_number�ڂ�path�������Ă���path������炷

public:
	static void improve_path();	//����肾����path�ɑ����ǉ�
	static void improve_advance_path();	//����肾����path�ɑ���Ǝ΂߂�ǉ�

	static void create_path();	//����肾���̃p�X
	static void create_path_advance();	//�����ǉ������p�X(�i�i���̓i�V)
	static void create_path_naname();	//����ƃi�i����ǉ������p�X

	static void draw_path();

	static void path_reset();
	static bool get_path_flag(signed int index_number);	//path������Ȃ�true,�Ȃ��Ȃ�false��Ԃ�.
	static float get_path_straight(unsigned int index_number);		//�Ԃ�l�͋���[m]
	static SLALOM_TYPE get_path_turn_type(unsigned int index_number);
	static unsigned char get_path_turn_muki(unsigned int index_number);	//�Ԃ�l��MUKI_RIGHT�@or�@MUKI_LEFT
	static bool set_path(uint16_t _index, PATH _path);

};

//���������Ɖ�]���������^����ƁA�@�̂̌�����90��������֕ς���
void direction_turn(signed char *direction_x, signed char *direction_y,
		unsigned char direction_turn_muki);

//compas<->���p�x�N�g��   first��X�����A�@second��Y����
std::pair<int8_t, int8_t> compas_to_direction(compas tar);
compas direction_to_compas(std::pair<int8_t,int8_t>);

class node_step: public map {
protected:
	static const uint16_t x_size = 64;
	static const uint16_t y_size = 32;

private:
	std::vector<PATH> path;
	static uint16_t step[x_size][y_size];//�m�[�h�ɔz�u�������	x,y x�͉��ǂƏc�ǂ̗�����\�����邽�߂�2�{	[0][0]��(0,0)�̐���
/*
	static union {
		uint32_t all ;
		//�R�X�g
		uint16_t cost :16;	//compas��1�����邽��15
		//�e�m�[�h�̕��p
		compas parent :4;
		//�ڑ����Ă����
		struct {
			uint8_t n :1;
			uint8_t e :1;
			uint8_t w :1;
			uint8_t s :1;
			uint8_t ne :1;
			uint8_t nw :1;
			uint8_t se :1;
			uint8_t sw :1;
		} connect;
	} graph[x_size][y_size];
*/
	bool able_set_step(uint8_t double_x, uint8_t y, compas muki,
			uint16_t step_val, bool by_known);//����L�΂���Ȃ�True�@�ǂ��Ȃ����A���̕ǂ����Ă���̂��Astep_val���������傫�����`�F�b�N
	bool is_outside_array(uint8_t x_index, uint8_t y_index);//�z��̓Y�����ł݂����W�n�iX���������{�j�Ŗ��H�O�i�z��O�j�ɏo�Ă��邩

public:
	static const uint16_t init_step = 19999;
	bool set_step(uint8_t x, uint8_t y, compas muki, uint16_t step_val,
			bool by_known);
	bool set_step_double(uint8_t _double_x, uint8_t _double_y,
			uint16_t step_val, bool by_known);
	uint16_t get_step(uint8_t x, uint8_t y, compas muki);
	uint16_t get_step_double(uint8_t double_x, uint8_t double_y);
	compas get_min_compas(uint8_t x, uint8_t y);	//�ix,y�j��4�̕����̓��A�ŏ��̕������ǂ̕��p��

	void reset_step(uint16_t reset_val);		//�S�Ă̕�����reset_val�Ń��Z�b�g

	void draw_step();		//myprintf�ŕ\������

	node_step();
	node_step(uint16_t reset_val);
	~node_step();
};

typedef struct {
	uint8_t distance;
	SLALOM_TYPE turn;
	bool is_right;	//�^�[�����E���H

} path_element;

class node_path: virtual public node_step {
private:
	static std::vector<path_element> path;

	static PATH to_PATH(path_element from);
	bool is_right_turn(compas now, compas next);		//���̃^�[�����E�����Ȃ�true
	static void push_straight(int half);	//������Ԑi�ނ�
	static void push_small_turn(bool is_right);		//�����łǂ���ɋȂ��邩

public:
	static void format();
	static PATH get_path(uint16_t index);	//PATH�𒼐ڕԂ�

protected:
	//�������Ђ��Ă�����s����̂�O��Ƃ��Ă���̂ŊO���A�N�Z�X�֎~�ɂ��Ă���
	bool create_path(std::pair<uint8_t, uint8_t> init, compas mouse_direction);
	//init�}�X�̒��S����finish�}�X�̒��S�܂ł�Path�@�����ӂ������Ă���Fasle
	//mouse_direction �������ɂȂ��Ă��闝�R
	//��{�I�ɂ͍ŒZ���s�����m��ԉ����Ŏg���̂ŕ����̏������������s���ׂ������ƈ�v���Ă��邪�A�ŏ���������������ƃ��o���̂ōŏ��̌�����v�����Ă���
	void improve_path();		//������Path�����΂߂ɕύX

public:
	node_path();
	~node_path();

	void convert_path();		//node_path������܂ł�Path�`���ɒ���

};

class node_search: virtual public node_step, virtual public node_path {
private:
	MAZE_WALL x_finish[MAZE_SIZE], y_finish[MAZE_SIZE];		//�ړI�n�̍��W�Ǘ��p

public:
	//���i�A�΂߁A�^�[���̏d�݂��Ǘ��@set_weight_algo �ŕύX�����
	std::vector<uint8_t> straight_w;
	std::vector<uint8_t> oblique_w;
	std::vector<uint8_t> curve_w;
	weight_algo algo;		//�d�݂Â��̕��@���Ǘ�����

public:
	void set_weight_algo(weight_algo weight);		//�����}�b�v�̏d�݂Â���ύX����
	weight_algo get_weight_algo();

	//set_weight_algo�Ŏw�肳�ꂽ�d�݂Â��ɏ]���ĕ�����~���l�߂�
	void spread_step(std::vector<std::pair<uint8_t, uint8_t> > finish,
			bool by_known);		//�����}�X�S�[���Ή��@�������1�}�X�ł�����

	bool create_small_path(std::vector<std::pair<uint8_t, uint8_t> > finish,
			std::pair<uint8_t, uint8_t> init, compas mouse_direction);
	//init�}�X�̒��S����finish�}�X�̒��S�܂ł�Path�@�����ӂ������Ă���false
	//��mouse_direction �������ɂȂ��Ă��闝�R
	//��{�I�ɂ͍ŒZ���s�����m��ԉ����Ŏg���̂ŕ����̏������������s���ׂ������ƈ�v���Ă��邪�A�ŏ���������������ƃ��o���̂ōŏ��̌�����v�����Ă���
	bool create_big_path(std::vector<std::pair<uint8_t, uint8_t> > finish,
			std::pair<uint8_t, uint8_t> init, compas mouse_direction);
	//����p�X�쐻

	void reset_finish();		//�ړI�n�������ׂă��Z�b�g����
	void set_finish_cell(uint8_t _x, uint8_t _y);//�ڕW���W��ݒ肷��  ���̃}�X�̓�����k�S�ĖڕW�ƂȂ�
	void set_finish(uint8_t _x, uint8_t _y, compas dir);	//�ڕW���W�̓���̕��p���w�肷��
	bool get_finish(uint8_t _x, uint8_t _y, compas dir);

	node_search();
	node_search(uint16_t init_step);
	~node_search();

};

#endif /* MAP_H_ */
