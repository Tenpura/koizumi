/*
 * flash.h
 *
 *  Created on: 2017/10/02
 *      Author: Koizumi
 */

#ifndef FLASH_H_
#define FLASH_H_

#include "stm32f4xx_flash.h"
#include "extern_c.h"
#include "map.h"
#include <string.h>

//flash�̋@�\���g�����߂�Class
#define BACKUP_FLASH_NUM FLASH_Sector_10	//�o�b�N�A�b�v�Ɏg�p����Z�N�^�[
#define BACKUP_SECTOR_START_ADDR 0x080C0000	//��̃Z�N�^�[�̊J�n�A�h���X
class flash{
private:
	static const uint16_t BACKUP_FLASH_SIZE = 1024*2;	//flash�̃T�C�Y��3KB���炢�@Flash�͍ő�128k�g���邯�ǂ�����ڂ����RAM������Ȃ�����
	static uint32_t* const BACKUP_SECTOR_START_POINTER;	//sector10�̏����A�h���X�̃|�C���^���Ǘ�
public:
	static uint32_t work_ram[(BACKUP_FLASH_SIZE / sizeof(uint32_t))];
	bool clear();	//�Ώ̂�sector�̃t���b�V��������������
	uint32_t* load();	//work_ram��flash�̃f�[�^���ڂ���work_ram�̃|�C���^��Ԃ�
	bool write_block();
};

//flash��p���Ď��ۂɖ��H�Ƃ��ۑ�����class
//flash��work_ram��MAZE_DATA�����Ԃɕۑ�����^�p��z��
class flash_maze : public flash{
private:
	static const uint8_t save_maze_num = 2;	//���H�����Z�b�g�܂ŕۑ����邩�@����ɂ����flash��RAM�T�C�Y���ς���Ă���
	static const size_t maze_size;		//MAZE_DATA�̃T�C�Y

public:
	bool save_maze(uint8_t index, const MAP_DATA* const input);		//index�Ԗڂ�input�̃f�[�^��ۑ�
	bool load_maze(uint8_t index, MAP_DATA* const output);			//index�Ԗڂ���output�̃f�[�^�����o��

};

#endif /* FLASH_H_ */
