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
#define MASS	(20 * 0.001)			//�}�E�X�̏d��[kg]
#define tire_R (7.55 * 0.001)	//�^�C���̔��a�@[m]
#define TREAD_W	(44*0.001)		//�g���b�h��[m]

#define LEAST_SQUARE_TIME	20		//�W���C���̍ŏ����@����ms�o�����邩

#define LOG_COUNT 2000	//LOG�������Ƃ邩�B�Œ�1�A0�ɂ͂��Ȃ�����
#define INT_LOG_COUNT	1	//Int�^��Log�������Ƃ邩�@�Œ�1


#define MOUSE_MODE	1	//1���n�[�t,2���N���V�b�N



#define SEARCH_VELOCITY	0.3	//�T���̑��x[m/s]



#include"user.h"
#include"serial.h"
#include<array>

#define RUN_MODE_NUMBER	6	//���s���[�h������ޗp�ӂ��邩

class parameter {
private:
	const static float ideal_photo[2][5];			//ideal_photo[�N���V�b�Nor�n�[�t][���w�Z���T�̌���]
	const static int16_t min_wall_photo[2][5];			//�ǂ����鎞�̍ŏ��l[�N���V�b�Nor�n�[�t][���w�Z���T�̌���]
	const static TRAPEZOID straight_run[RUN_MODE_NUMBER];

public:
	static float get_ideal_photo(PHOTO_TYPE _type);
	static int16_t get_min_wall_photo(PHOTO_TYPE _type);

	static float get_run_acceleration(uint8_t _select_mode);
	static float get_run_max_velocity(uint8_t _select_mode);
	static float get_run_de_acceleration(uint8_t _select_mode);
	static const TRAPEZOID* const get_run(uint8_t _select_mode);

	static float get_slalom(SLALOM_TYPE slalom_type, SLALOM_ELEMENT slalom_element,
				signed char right_or_left, unsigned char select_mode);
	static const INIT_SLALOM* const get_slalom_p(SLALOM_TYPE _type, bool is_right, uint8_t select_mode);

};



#endif /* PARAMETER_H_ */
