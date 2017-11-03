/*
 * user.h
 *
 *  Created on: 2016/08/21
 *      Author: Koizumi
 */

#ifndef USER_H_
#define USER_H_

#include "stm32f4xx.h"
#include "extern_c.h"
#include "define.h"
#include "hardware.h"
#include "flash.h"
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <array>

//TODO �e���v���[�g�ł���[����������
/*
template <class T>
class queue{
private:
	uint16_t head,tail;
	T *data;

public:
	T& dequeue();					//����[����l���o��
	void enqueue(T set_value);		//����[�ɒl������

	queue(uint16_t size);
	queue(uint16_t size1, uint16_t size2);

	~queue();

};
*/

//�p�x�ϊ��֐�
float degree(float radian);		//���W�A��	->	�x��		-�΁��Ɓ���
float radian(float degree);		//�x��	->	���W�A��	-180���Ɓ�180

//compas<->muki
compas muki_to_compas(uint8_t muki);	//define���ꂽMUKI��^����ƁAcompas��Ԃ�.
uint8_t compas_to_muki(compas muki);	//�񋓌^��compas��Define���ꂽMUKI�ɕϊ�����



//wait�֐�
extern uint32_t wait_counter;	//���荞�ݓ���1�����Z�����ϐ�
class wait{
private:
	static uint32_t counter;
public:
	static void ms(uint32_t wait_time);	//wait_time[ms]�����҂֐�
	static void set_count(uint32_t count);			//�J�E���g�A�b�v����֐�
	static void reset_count(void);			//counter��0�Ƀ��Z�b�g����

	static uint32_t get_count(void);		//counter�̒l���擾�B�N�����Ă���̎��Ԃ��v������Ƃ��Ɏg�p�B

};


//mode�I���N���X
class mode {
private:

	mode();

public:
	//���̓X�C�b�`�ŐؑցA�X�C�b�`������
	static uint8_t select_mode(const unsigned char mode_number, const PHOTO_TYPE type);//mode�I�����A�I�񂾃��[�h�ԍ���Ԃ�
	static bool select_RorL(const PHOTO_TYPE type);	//right�Ȃ�true,left�Ȃ�false

	static bool search_mode();		//�T�����[�h
	static bool shortest_mode();	//�ŒZ���[�h

	~mode();
};

//�����}�b�v�W�J�p�̃����O�o�b�t�@Queue
#define QUEUE_SIZE 2560
class my_queue{
private:
	int8_t queue[QUEUE_SIZE];
	uint16_t head;
	uint16_t tail;
public:
	void reset();
	uint16_t size();
	int8_t pop();
	void push(int8_t _var);
	int8_t front();

	my_queue();
	~my_queue();

};


//log�N���X	������template�ŔC�ӂ̌^�ɑΉ����������c!

//���O�Ƃ������o�b�t�@�B�f���I
//���͂𕶎���Ƃ��ĕۊ�
//extern "C" void putnbyte(char *buf, int16_t len);	//printf_log�Ŏg�p
/*
class log{
private:
	static char buf[buf_count];	//�o�b�t�@�B+100�̓������I�[�o�[�t���[�΍�łƂ��Ă���(�Öق�1��̃��O��100byte�ȉ����Ɖ���)�B
	static uint16_t length;				//���݂̃o�b�t�@�ʋL�^�p�B��̓I�ɂ�buf[xx]��xx�����������B
	static bool available_flag;
		//�������߂邩�`�F�b�N�p�t���O�Bcheck_put_available�֐��ŗǂ����߁A�����I�ɂ͂�����Ȃ��Bprintf_log()�Ōx�����邽�߂Ɏg�p�B

	static bool check_put_available(uint16_t put_byte);	//put_byte�̃f�[�^���������݉\�����f����B�\�Ȃ�True�BAvailable�H
	static void add_buffer(char* add_buf, uint16_t buf_size);	//�^����ꂽbuf_size�̃o�C�g����add_buf��S�̂�buf�̌��ɒǉ�����B

public:
	static int16_t put_log(const char *fmt, ...);	//printf�Ɠ����`�ŕۑ����Ă�������������́B�Ԃ�l�͏������ݐ�������Byte���A���s���́\1�D
	static void printf_log();		//���߂Ă郍�O���R���\�[���ɂ��ׂďo��
	static void reset_log();		//�S�Ẵ��O��0�Ƀ��Z�b�g
};

class int_log {
private:
	static signed int log_case[2][log_count];
	static unsigned int log_counter;
	int init_number;

public:
	void reset_log();		//log�̒��g�������B�S��0�ɂ���B

	static void put_log(const int put_number);//log�̍Ō���Ɉ������i�[�B���ɖ��܂��Ă���Ή������Ȃ�
	static void put_log(const int put_number,const int put_number2);//��Ɠ����B������2�ۑ���

	int get_log(const unsigned int get_number);//get_number�ԖڂɊi�[����Ă�log�����o��
	int get_log(const unsigned int ordinal_number,const unsigned int get_number);//��Ɠ����B������2�ۑ���

	int_log();
	int_log(int initialize_number);//�������������鐔��0�ȊO�ɂ�����������A�����ŕύX���Ă�
	~int_log();
};
*/
/*
class float_log {
private:
	static float log_case[2][log_count];
	static unsigned int log_counter;
	static float init_number;

public:
	static void reset_log();		//log�̒��g�������B�S��0�ɂ���B

	//log�̍Ō���Ɉ������i�[�B���ɖ��܂��Ă���Ή������Ȃ�
	//a,b�͑������z��p�B1�����̏ꍇ��b�͖��������B
	static void put_log(const float put_number_a,const float put_number_b);

	//get_dimension�̎�����get_number�ԖڂɊi�[����Ă�log�����o��
	float get_log(const unsigned char get_dimension, const unsigned int get_number);

	float_log();
	float_log(float initialize_number);//�������������鐔��0�ȊO�ɂ�����������A�����ŕύX���Ă�
	~float_log();
};
*/


//���w�N���X
class my_math{
private:

	#define LOG_N 1000	//log�e�[�u���̗v�f��

	const static float sin_table[92];		//[]�̗v�f��degree�ɑΉ��B�O�̂���92��
	const static float log_table[LOG_N+1];		//log�e�[�u���B������y�̂��Q�l�ɌX���ɉ����ĕ������Ă���

public:
	static float sin(const float radian);
	static float cos(const float radian);

	static float log(float x);			//log��Ԃ��֐��@���R�ΐ��@0.1<x<10�͈̔͂ɂ����Ή����Ă��Ȃ����Ƃɒ��ӁI

	static float sqrt(float x);			//��������Ԃ��֐��@�j���[�g���@

};



#endif /* USER_H_ */
