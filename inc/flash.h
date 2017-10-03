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

//flashの機能を使うためのClass
#define BACKUP_FLASH_NUM FLASH_Sector_10	//バックアップに使用するセクター
#define BACKUP_SECTOR_START_ADDR 0x080C0000	//上のセクターの開始アドレス
class flash{
private:
	static const uint16_t BACKUP_FLASH_SIZE = 1024*2;	//flashのサイズは3KBくらい　Flashは最大128k使えるけどそれを移す先のRAMが足りないから
	static uint32_t* const BACKUP_SECTOR_START_POINTER;	//sector10の初期アドレスのポインタを管理
public:
	static uint32_t work_ram[(BACKUP_FLASH_SIZE / sizeof(uint32_t))];
	bool clear();	//対称のsectorのフラッシュメモリを消去
	uint32_t* load();	//work_ramにflashのデータを移してwork_ramのポインタを返す
	bool write_block();
};

//flashを用いて実際に迷路とか保存するclass
//flashのwork_ramにMAZE_DATAを順番に保存する運用を想定
class flash_maze : public flash{
private:
	static const uint8_t save_maze_num = 2;	//迷路を何セットまで保存するか　これによってflashのRAMサイズが変わってくる
	static const size_t maze_size;		//MAZE_DATAのサイズ

public:
	bool save_maze(uint8_t index, const MAP_DATA* const input);		//index番目にinputのデータを保存
	bool load_maze(uint8_t index, MAP_DATA* const output);			//index番目からoutputのデータを取り出す

};

#endif /* FLASH_H_ */
