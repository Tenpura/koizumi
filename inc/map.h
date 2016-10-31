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


//TODO ����static�ɂ��ׂ��ŁA�������[�J���̂܂܂Œu���ׂ���


class map {

//�����o�ϐ�
private:
	//unsigned char x,y;//���W
	static MAZE_WALL x_maze_wall[MAZE_SIZE],y_maze_wall[MAZE_SIZE];//�Ǐ��ۑ��p
	static MAZE_WALL x_wall_exist[MAZE_SIZE],y_wall_exist[MAZE_SIZE];//�Ǐ����������ǂ������ʗp

	static void set_maze_wall( MAZE_WALL* const maze_wall,unsigned char edit_number,bool is_wall);//maze_wall�ɒl��������p
	static unsigned char get_maze_wall( MAZE_WALL maze_wall,unsigned char edit_number);//maze_wall�̒l��ǂޗp



public:
	static void create_wall(unsigned char wall_x, unsigned char wall_y, unsigned char muki);//(x,y)��muki�����̕ǂ����
	static void destroy_wall(unsigned char wall_x, unsigned char wall_y, unsigned char muki);
	//�ǂ������define���ꂽTRUE�A�Ȃ����FALSE���Ԃ��Ă���B���H�O���ƃG���[�ɓ���o�͂́|1
	static bool get_wall(unsigned char wall_x, unsigned char wall_y, unsigned char muki);

	static void remember_exist(unsigned char wall_x, unsigned char wall_y, unsigned char muki);//(x,y)��muki�����̕ǂ����
	static void forget_exist(unsigned char wall_x, unsigned char wall_y, unsigned char muki);
	//�ǂ��������Ƃ������define���ꂽTRUE�A�Ȃ����FALSE���Ԃ��Ă���B���H�O���ƃG���[�ɓ���o�͂́|1
	static bool check_exist(unsigned char wall_x, unsigned char wall_y, unsigned char muki);

	static void reset_wall();		//�Ǐ��ƌ������ǂ��������ׂă��Z�b�g

	void draw_map(bool write_step);//myprintf�Ŗ��H��`��
	void convert_mapdata(unsigned char (*hiramatu_data)[16]);//������y�̃}�b�v�f�[�^�`�����m�m�z���ɕϊ�

	static void input_map_data(const MAP_DATA* input_data);//�O���ɕۑ������f�[�^�̓���
	static void output_map_data(MAP_DATA* const output_data);//�O���Ƀf�[�^�o��

	map();
	~map();

};

#define STEP_INIT 999		//�����̏����l

class step {
private:
	static DIRECTION save_direction;				//���ɍs���}�X�̕�����ۑ�
	static unsigned short maze_step[MAZE_SIZE][MAZE_SIZE];

	static void step_reset();
	static void close_one_dead_end(unsigned char target_x, unsigned char target_y);

public:

	static void set_step(unsigned char target_x,unsigned char target_y);//target_x,y����ɕ����}�b�v�쐻(������)
	static void set_step_by_known(unsigned char target_x,unsigned char target_y);//���Ă��Ȃ��ǂ́A�ǂ�����ƌ��Ȃ�
	static unsigned int get_step(unsigned char target_x,unsigned char target_y);//������W(x,y)�̕�����Ԃ�

	static void close_dead_end();//�}�b�v��̑܏��H���Ԃ�

	step();
	step(const MAP_DATA* input_data);
	~step();

};

/*
class path:public step {
private:
	typedef union {
		unsigned char all;				//�ꊇ
		struct {
			unsigned char up :1;		//��	x=1,y=0�̕���
			unsigned char right :1;//��	x=-1,y=0�̕���
			unsigned char down :1;//��	x=0,y=-1�̕���
			unsigned char left :1;//��	x=0,y=1�̕���
			unsigned char now :4;//���݂̕������Ǘ��A���̐��Asave_direction���r�b�g�V�t�g����ƌ��݂̌����ɑΉ�
		}element;
	}SAVE_DIRECTION;				//���ɍs���}�X�̕�����ۑ�
	static PATH path_memory[PATH_MAX];

	void set_step_for_shortest(unsigned char target_x,unsigned char target_y);//�ŒZ�p�̕����}�b�v�쐻
	void displace_path(unsigned int path_number);//path_number�ڂ�path�������Ă���path������炷
	void improve_path();//����肾����path�ɑ����ǉ�
	void improve_advance_path();//����肾����path�ɑ���Ǝ΂߂�ǉ�

public:
	void create_path();//����肾���̃p�X
	void create_path_advance();//�����ǉ������p�X(�i�i���̓i�V)
	void create_path_naname();//����ƃi�i����ǉ������p�X

	void path_reset();
	unsigned char get_path_flag(unsigned int index_number);
	unsigned char get_path_straight(unsigned int index_number);
	unsigned char get_path_turn_type(unsigned int index_number);
	unsigned char get_path_turn_muki(unsigned int index_number);

};
*/

//���������Ɖ�]���������^����ƁA�@�̂̌�����90��������֕ς���
void direction_turn(signed char *direction_x, signed char *direction_y,
		unsigned char direction_turn_muki);




#endif /* MAP_H_ */
