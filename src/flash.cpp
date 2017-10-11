/*
 * flash.cpp
 *
 *  Created on: 2017/10/02
 *      Author: Koizumi
 */

#include "flash.h"

uint32_t flash::work_ram[BACKUP_FLASH_SIZE / sizeof(uint32_t)];
uint32_t* const flash::BACKUP_SECTOR_START_POINTER =
		(uint32_t*) BACKUP_SECTOR_START_ADDR;

bool flash::clear() {

	FLASH_Unlock();
	//ここでフラグクリアしとかないと、ERROR_PROGRAMになる
	FLASH_ClearFlag(FLASH_FLAG_PGSERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_WRPERR | FLASH_FLAG_OPERR | FLASH_FLAG_EOP); // clear error status
	FLASH_Status result = FLASH_EraseSector(BACKUP_FLASH_NUM, VoltageRange_3);
	FLASH_Lock();

	/*	//デバック用
	switch (result) {
	case FLASH_BUSY:
		myprintf("BUSY!%\n");
		break;
	case FLASH_ERROR_PROGRAM:
		myprintf("ERROR_PROGRAM!%\n");
		break;
	case FLASH_ERROR_WRP:
		myprintf("ERROR_WRP!%\n");
		break;
	case FLASH_ERROR_OPERATION:
		myprintf("ERROR_OPERATION!%\n");
		break;
	}
	*/

	return (result == FLASH_COMPLETE);
}

uint32_t* flash::load() {
	memcpy(work_ram, BACKUP_SECTOR_START_POINTER, BACKUP_FLASH_SIZE);
	return work_ram;
}

bool flash::write_block() {

	//まずはFlashを消去
	if (!clear())
		return false;

	FLASH_Unlock();

	//uint32_tずつ書き込んでいく
	FLASH_Status result;
	const size_t write_cnt = BACKUP_FLASH_SIZE / sizeof(uint32_t);
	for (size_t i = 0; i < write_cnt; i++) {
		result = FLASH_ProgramWord(
				static_cast<uint32_t>(BACKUP_SECTOR_START_ADDR)
						+ sizeof(uint32_t) * i, work_ram[i]);
		//失敗したら中段
		if (result != FLASH_COMPLETE)
			break;
	}
	FLASH_Lock();

	return (result == FLASH_COMPLETE);

}
MAP_DATA size;
const size_t flash_maze::maze_size = sizeof(MAP_DATA);//sizeof(size.x_wall)*4;

bool flash_maze::save_maze(uint8_t index, const MAP_DATA* const input) {
	//保存最大数以上の迷路を書き込もうとしたら失敗
	if (index >= save_maze_num)
		return false;

	//flash内のwork_ramのindex番目にmaze_dataを書き込む
	memcpy((flash::load() + maze_size * index), input, maze_size);
	return flash::write_block();
}

bool flash_maze::load_maze(uint8_t index, MAP_DATA* const output) {
	//保存最大数以上の迷路を読み出そうとしたら失敗
	if (index >= save_maze_num)
		return false;

	//flash内のwork_ramからindex番目のmaze_dataを引き出す
	memcpy(output, (flash::load() + maze_size * index), maze_size);
	return true;
}
