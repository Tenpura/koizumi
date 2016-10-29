/*
 * parameter.h
 *
 *  Created on: 2016/10/23
 *      Author: Koizumi
 */

#ifndef PARAMETER_H_
#define PARAMETER_H_

#include"define.h"

//�p�����[�^
//TODO ���[�g���ɂ�����

#define tire_R (7.5 * 0.001)	//�^�C���̔��a�@[m]
#define TREAD_W	44		//�g���b�h��[mm]


#define LEAST_SQUARE_TIME	2000		//�W���C���̍ŏ����@����ms�o�����邩

#define LOG_COUNT 2000	//LOG�������Ƃ邩�B�Œ�1�A0�ɂ͂��Ȃ�����
#define INT_LOG_COUNT	1	//Int�^��Log�������Ƃ邩�@�Œ�1


#define MOUSE_MODE	1	//1���n�[�t,2���N���V�b�N



#define SEARCH_VELOCITY	0.25	//�T���̑��x[m/s]



#include"user.h"
#include"serial.h"

#define RUN_MODE_NUMBER	5	//���s���[�h������ޗp�ӂ��邩

class parameter {
private:
	const static unsigned int ideal_photo[2][4];			//ideal_photo[�N���V�b�Nor�n�[�t][���w�Z���T�̌���]
	const static unsigned int min_wall_photo[2][4];			//�ǂ����鎞�̍ŏ��l[�N���V�b�Nor�n�[�t][���w�Z���T�̌���]
	const static TRAPEZOID straight_run[RUN_MODE_NUMBER];
	const static INIT_SLALOM right_slalom[RUN_MODE_NUMBER], left_slalom[RUN_MODE_NUMBER];


public:
	static unsigned int get_ideal_photo(const PHOTO_TYPE photo_type);
	static unsigned int get_min_wall_photo(const PHOTO_TYPE photo_type);

	static float get_run_acceleration(const unsigned char select_mode);
	static float get_run_max_velocity(const unsigned char select_mode);
	static float get_run_de_acceleration(const unsigned char select_mode);

	static float get_slalom_para( const SLALOM_ELEMENT slalom_element, const int8_t right_or_left, const uint8_t select_mode);

};



#endif /* PARAMETER_H_ */
