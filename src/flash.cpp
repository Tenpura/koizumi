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
	FLASH_ClearFlag(FLASH_FLAG_PGSERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_WRPERR | FLASH_FLAG_OPERR | FLASH_FLAG_EOP); // clear error status
	FLASH_Status result = FLASH_EraseSector(BACKUP_FLASH_NUM, VoltageRange_3);
	FLASH_Lock();

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

	return (result == FLASH_COMPLETE);
}

uint32_t* flash::load() {
	memcpy(work_ram, BACKUP_SECTOR_START_POINTER, BACKUP_FLASH_SIZE);
	return work_ram;
}

bool flash::write_block() {
	myprintf("clear? \n");

	//Ç‹Ç∏ÇÕFlashÇè¡ãé
	if (!clear())
		return false;

	myprintf("clear! \n");

	FLASH_Unlock();

	//uint32_tÇ∏Ç¬èëÇ´çûÇÒÇ≈Ç¢Ç≠
	FLASH_Status result;
	const size_t write_cnt = BACKUP_FLASH_SIZE / sizeof(uint32_t);
	for (size_t i = 0; i < write_cnt; i++) {
		result = FLASH_ProgramWord(
				static_cast<uint32_t>(BACKUP_SECTOR_START_ADDR)
						+ sizeof(uint32_t) * i, work_ram[i]);
		//é∏îsÇµÇΩÇÁíÜíi
		if (result != FLASH_COMPLETE)
			break;
	}
	FLASH_Lock();

	if ((result == FLASH_COMPLETE))
		myprintf("true");
	else
		myprintf("false");

	return (result == FLASH_COMPLETE);

}

const size_t flash_log::maze_size = sizeof(MAP_DATA);

bool flash_log::save_maze(uint8_t index, const MAP_DATA* const input) {
	//ï€ë∂ç≈ëÂêîà»è„ÇÃñ¿òHÇèëÇ´çûÇ‡Ç§Ç∆ÇµÇΩÇÁé∏îs
	if (index >= save_maze_num)
		return false;

	//flashì‡ÇÃwork_ramÇÃindexî‘ñ⁄Ç…maze_dataÇèëÇ´çûÇﬁ
	memcpy(work_ram + maze_size * index, input, maze_size);

	return flash::write_block();
}

bool flash_log::load_maze(uint8_t index, MAP_DATA* const output) {
	//ï€ë∂ç≈ëÂêîà»è„ÇÃñ¿òHÇì«Ç›èoÇªÇ§Ç∆ÇµÇΩÇÁé∏îs
	if (index >= save_maze_num)
		return false;

	//flashì‡ÇÃwork_ramÇ©ÇÁindexî‘ñ⁄ÇÃmaze_dataÇà¯Ç´èoÇ∑
	memcpy(output, flash::load() + maze_size * index, maze_size);
	return true;
}
