/*
 * define.h
 *
 *  Created on: 2016/08/21
 *      Author: Koizumi
 */

#ifndef DEFINE_H_
#define DEFINE_H_

#include <stdint.h>

#define CONTROL_PERIOD 0.001		//�������[sec]

//��������

#define MAZE_SIZE	16

#define GOAL_x 5
#define GOAL_y 6

#define PATH_MAX 200

static const uint8_t log_count = 100;	//Log�̔z���
static const uint16_t buf_count = 100;	//�o�b�t�@�����O�̃o�b�t�@���B

//�����@�̂��g���Ă����ς��Ȃ�define�̓R�R�ɏ���

//�n�[�h�E�F�A

#define LOGIK_V 3.3

#define CONTORL_PERIOD 0.001		//�������[s]

#define PINION	9	//�s�j�I���M�A�̎���
#define SPAR	41	//�X�p�[�M�A�̎���

#define V_BATT_RATIO 2.1	//�o�b�e���[�Ď��p�̒�R�ɂ�镪����B�o�b�e���[�̉�����1�����Ă邩

#define MOTOR_ORM	4.5		//���[�^�[�̒[�q�Ԓ�R[��]
#define	M_DRIVER_ORM	1	//���[�^�[�h���C�o�[�̒�R[��]
#define M_SUM_ORM	5.5		//��2�̍��Z��R[��]

#define ACCEL_SENSITIVITY	8192	//�����x�v�̊��x[count/g] ����ő���l������Ɖ����x
#define GYRO_SENSITIVITY	16.4		//Gyro�̊��x[count/(degree/s)]�@����ő���l������Ɗp���x�ɂȂ�
//#define GYRO_CONST	1.53		//gyro�̒萔[degree/V/ms]�p�����[�^�[��1��
//XXX���E������K�v�����邩���H

#define ENCODER_CONST	(1.534 * 0.001)			//encoder�̕���\[rad/count]

#define MOTOR_CONST	(222.6)		//���[�^�[�̉�]�萔[��]/s/V]

//�^���^�U�l
/*
 #define ON	1
 #define OFF	0

 #define TRUE	1
 #define FALSE	0
 */

//#define ERROR	14
#define MUKI_RIGHT	0
#define MUKI_UP		1
#define MUKI_LEFT	2
#define MUKI_DOWN	3

//�X�C�b�`�B������true,������false
//#define SWITCH_LEFT (1-PORT7.PORT.BIT.B5)
//#define SWITCH_RIGHT (1-PORT7.PORT.BIT.B6)

//�֗��]�[��/////////////////////////////////////////////////////////////////////////////////////////////////////
#define SQRT2 1.414	//��2
#define PI()		3.1415		//�΁@�~����

#define ABS(x)		((x) < 0 ? -(x) : (x))	//��Βl
#define	SIGN(x)	((x) < 0 ? -1 : 1 )		//����
#define	MAX(a,b)	((a) > (b) ? (a) : (b))	//�ő�l
#define	MIN(a,b)	((a) < (b) ? (a) : (b))	//�ŏ��l

//MELODY
typedef union {
	//unsigned char all;				//�ꊇ
	struct {
		unsigned char semiton :2; //���������邩�����邩��\��	�܂��Ȃ̂���������(������MELODY_END�̂Ƃ��I���)
		unsigned char octave :1;			//�I�N�^�[�u��1�����邩�ǂ���
		unsigned char beat :2;			//������\��
		unsigned char scale :3;			//���K��\���@0���h���~�t�@�\���V�x��7
	} bit;

} MELODY;

//DIRECTION �����Ǘ��p
typedef union {
	uint8_t all;				//�ꊇ
	struct {
		unsigned char :4;		//
		unsigned char up :1;		//��	x=0,y=1�̕���
		unsigned char down :1;		//��	x=0,y=-1�̕���
		unsigned char left :1;		//��	x=-1,y=0�̕���
		unsigned char right :1;		//��	x=1,y=0�̕���
	} element;
} DIRECTION;				//���ɍs���}�X�̕�����ۑ�

enum BOOL {
	FALSE=0, TRUE=1
};

//PATH
typedef union {
	uint16_t all;					//�ꊇ�Ō���
	struct {
		unsigned char :1;		//
		unsigned char flag :1;		//�z��̍Ōォ�`�F�b�N�p
		unsigned char turn :4;		//�^�[���̎�ނ𔻕�
		unsigned char muki :2;		//�^�[���̕����𔻕�
		unsigned char distance :8;		//���i���鋗���𔻕�
	} element;
} PATH;

//MAZE_WALL
typedef union {
	uint32_t all;		//�S�Ĉꊇ�ŕύX����p
	struct {
		uint16_t high :16;
		uint16_t low :16;
	} SHORT;
	struct {
		//true�Ȃ�ǂ����݁Afalse�Ȃ瑶�݂��Ȃ�
		unsigned char B0 :1;		//x���W0��1�̊Ԃ̕ǁ@or�@y���W0��1�̊Ԃ̕�
		unsigned char B1 :1;
		unsigned char B2 :1;
		unsigned char B3 :1;
		unsigned char B4 :1;
		unsigned char B5 :1;
		unsigned char B6 :1;
		unsigned char B7 :1;
		unsigned char B8 :1;
		unsigned char B9 :1;
		unsigned char B10 :1;
		unsigned char B11 :1;
		unsigned char B12 :1;
		unsigned char B13 :1;
		unsigned char B14 :1;
		unsigned char B15 :1;
		unsigned char B16 :1;		//x���W0��1�̊Ԃ̕ǁ@or�@y���W0��1�̊Ԃ̕�
		unsigned char B17 :1;
		unsigned char B18 :1;
		unsigned char B19 :1;
		unsigned char B20 :1;
		unsigned char B21 :1;
		unsigned char B22 :1;
		unsigned char B23 :1;
		unsigned char B24 :1;
		unsigned char B25 :1;
		unsigned char B26 :1;
		unsigned char B27 :1;
		unsigned char B28 :1;
		unsigned char B29 :1;
		unsigned char B30 :1;
		unsigned char B31 :1;
	} bit;
} MAZE_WALL;

//MAP_DATA
typedef struct {
	MAZE_WALL x_wall[MAZE_SIZE], y_wall[MAZE_SIZE];	//�Ǐ��ۑ��p
	MAZE_WALL x_known[MAZE_SIZE], y_known[MAZE_SIZE];	//�Ǐ����������ǂ������ʗp
} MAP_DATA;

//���w�Z���T�̎��
enum PHOTO_TYPE {
	right = 0, left = 1, front_right = 2, front_left = 3, front = 4, element_count
};

//��`�����ɗp����p�����[�^�p�\����
typedef struct {
	float acceleration;
	float max_velocity;
	float de_acceleration;
} TRAPEZOID;

//�X�����[���̎��
typedef enum {
	none = 0,
	small = 1,
	big_90 = 2,
	big_180 = 3,
	begin_45 = 4,
	end_45 = 5,
	begin_135 = 6,
	end_135 = 7,
	oblique_90 = 8,
	spin_turn = 9,
	slalom_type_count		//�v�f����\��
} SLALOM_TYPE;

//�X�����[���p�\����
typedef struct {
	float velocity;				//�d�S���x[m/s]
	float target_angle;			//���x�̃^�[����[��]
	float clothoid_angle;		//���x�܂ŃN���\�C�h����̂��i�p���x�̉������	[��]
	float before_distance;		//�O����[m]
	float after_distance;		//�㋗��[m]
	float angular_accel;		//�p�����x
	float max_angular_velocity;	//�ő�p���x
	float time;					//�ǂꂾ�����Ԃ�������̂�[sec]
} INIT_SLALOM;

//�X�����[���p�����[�^�[�̗v�f
typedef enum {
	velocity,
	target_angle,
	clothoid_angle,
	before_distance,
	after_distance,
	angular_accel,
	max_angular_velocity,
	time
} SLALOM_ELEMENT;

//�Z���T�[�^�C�v��\���񋓌^
typedef enum {
	sen_gyro,
	sen_encoder,
	sen_photo,
	sen_accel,
	sen_all
} SEN_TYPE;

//���W���B�}�X�P�ʂłȂ��A�����ɋ����Ƃ��������p
typedef struct {
	float x;
	float y;
} COORDINATE;

#endif /* DEFINE_H_ */
