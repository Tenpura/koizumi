/*
 * map.cpp
 *
 *  Created on: 2016/10/29
 *      Author: Koizumi
 */

#include"map.h"

//map_wall(x,y,RIGHT)->1or0
MAZE_WALL map::x_maze_wall[MAZE_SIZE], map::y_maze_wall[MAZE_SIZE];
MAZE_WALL map::x_wall_exist[MAZE_SIZE], map::y_wall_exist[MAZE_SIZE];

//target_wallのedit_number目にset_numberを代入する関数
void map::set_maze_wall(MAZE_WALL* const maze_wall, unsigned char edit_number,
		bool is_wall) {
	int8_t set_number;
	if (is_wall)
		set_number = 1;
	else
		set_number = 0;

	switch (edit_number) {
	case 0:
		maze_wall->bit.B0 = set_number;
		break;
	case 1:
		maze_wall->bit.B1 = set_number;
		break;
	case 2:
		maze_wall->bit.B2 = set_number;
		break;
	case 3:
		maze_wall->bit.B3 = set_number;
		break;
	case 4:
		maze_wall->bit.B4 = set_number;
		break;
	case 5:
		maze_wall->bit.B5 = set_number;
		break;
	case 6:
		maze_wall->bit.B6 = set_number;
		break;
	case 7:
		maze_wall->bit.B7 = set_number;
		break;
	case 8:
		maze_wall->bit.B8 = set_number;
		break;
	case 9:
		maze_wall->bit.B9 = set_number;
		break;
	case 10:
		maze_wall->bit.B10 = set_number;
		break;
	case 11:
		maze_wall->bit.B11 = set_number;
		break;
	case 12:
		maze_wall->bit.B12 = set_number;
		break;
	case 13:
		maze_wall->bit.B13 = set_number;
		break;
	case 14:
		maze_wall->bit.B14 = set_number;
		break;
	case 15:
		maze_wall->bit.B15 = set_number;
		break;
	case 16:
		maze_wall->bit.B16 = set_number;
		break;
	case 17:
		maze_wall->bit.B17 = set_number;
		break;
	case 18:
		maze_wall->bit.B18 = set_number;
		break;
	case 19:
		maze_wall->bit.B19 = set_number;
		break;
	case 20:
		maze_wall->bit.B20 = set_number;
		break;
	case 21:
		maze_wall->bit.B21 = set_number;
		break;
	case 22:
		maze_wall->bit.B22 = set_number;
		break;
	case 23:
		maze_wall->bit.B23 = set_number;
		break;
	case 24:
		maze_wall->bit.B24 = set_number;
		break;
	case 25:
		maze_wall->bit.B25 = set_number;
		break;
	case 26:
		maze_wall->bit.B26 = set_number;
		break;
	case 27:
		maze_wall->bit.B27 = set_number;
		break;
	case 28:
		maze_wall->bit.B28 = set_number;
		break;
	case 29:
		maze_wall->bit.B29 = set_number;
		break;
	case 30:
		maze_wall->bit.B30 = set_number;
		break;
	case 31:
		maze_wall->bit.B31 = set_number;
		break;

	}
}
unsigned char map::get_maze_wall(MAZE_WALL maze_wall,
		unsigned char edit_number) {
	unsigned char maze_check = 0;		//元FALSE

	switch (edit_number) {
	case 0:
		maze_check = maze_wall.bit.B0;
		break;
	case 1:
		maze_check = maze_wall.bit.B1;
		break;
	case 2:
		maze_check = maze_wall.bit.B2;
		break;
	case 3:
		maze_check = maze_wall.bit.B3;
		break;
	case 4:
		maze_check = maze_wall.bit.B4;
		break;
	case 5:
		maze_check = maze_wall.bit.B5;
		break;
	case 6:
		maze_check = maze_wall.bit.B6;
		break;
	case 7:
		maze_check = maze_wall.bit.B7;
		break;
	case 8:
		maze_check = maze_wall.bit.B8;
		break;
	case 9:
		maze_check = maze_wall.bit.B9;
		break;
	case 10:
		maze_check = maze_wall.bit.B10;
		break;
	case 11:
		maze_check = maze_wall.bit.B11;
		break;
	case 12:
		maze_check = maze_wall.bit.B12;
		break;
	case 13:
		maze_check = maze_wall.bit.B13;
		break;
	case 14:
		maze_check = maze_wall.bit.B14;
		break;
	case 15:
		maze_check = maze_wall.bit.B15;
		break;
	case 16:
		maze_check = maze_wall.bit.B16;
		break;
	case 17:
		maze_check = maze_wall.bit.B17;
		break;
	case 18:
		maze_check = maze_wall.bit.B18;
		break;
	case 19:
		maze_check = maze_wall.bit.B19;
		break;
	case 20:
		maze_check = maze_wall.bit.B20;
		break;
	case 21:
		maze_check = maze_wall.bit.B21;
		break;
	case 22:
		maze_check = maze_wall.bit.B22;
		break;
	case 23:
		maze_check = maze_wall.bit.B23;
		break;
	case 24:
		maze_check = maze_wall.bit.B24;
		break;
	case 25:
		maze_check = maze_wall.bit.B25;
		break;
	case 26:
		maze_check = maze_wall.bit.B26;
		break;
	case 27:
		maze_check = maze_wall.bit.B27;
		break;
	case 28:
		maze_check = maze_wall.bit.B28;
		break;
	case 29:
		maze_check = maze_wall.bit.B29;
		break;
	case 30:
		maze_check = maze_wall.bit.B30;
		break;
	case 31:
		maze_check = maze_wall.bit.B31;
		break;
	}

	return maze_check;
}

void map::remember_exist(unsigned char wall_x, unsigned char wall_y,
		unsigned char muki) {
	unsigned char set_x = wall_x, set_y = wall_y;

	//x座標方向を変更するとき
	if ((muki == MUKI_RIGHT) || (muki == MUKI_LEFT)) {
		if (muki == MUKI_RIGHT) {
		} else if (muki == MUKI_LEFT) {
			if (wall_x == 0) {		//一番左壁は管理しない
				return;
			} else {
				set_x = wall_x - 1;	//必ず右壁を更新するように、座標を変える
			}
		}
		if (set_x < MAZE_SIZE) {
			set_maze_wall(&x_wall_exist[set_y], set_x, true);//x_maze_wall[y]のx番目の右壁に1を代入
		} else {		//適切でない値が入ってる
			mouse::error();
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("存在しないx座標に壁の存在を作ろうとしています\n\r");
			myprintf("remember_exist関数内\n\r");
		}

		//y座標方向を変更するとき
	} else if ((muki == MUKI_UP) || (muki == MUKI_DOWN)) {
		if (muki == MUKI_UP) {
		} else if (muki == MUKI_DOWN) {
			if (wall_y == 0) {		//一番下壁は管理しない
				return;
			} else {
				set_y = wall_y - 1;	//必ず上壁を更新するように、座標を変える
			}
		}
		if (set_y < MAZE_SIZE) {
			set_maze_wall(&y_wall_exist[set_x], set_y, true);//x_maze_wall[y]のx番目の右壁に1を代入
		} else {		//適切でない値が入ってる
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("存在しないy座標に壁の存在を作ろうとしています\n\r");
			myprintf("remember_exist関数内\n\r");
		}

	}

}
void map::forget_exist(unsigned char wall_x, unsigned char wall_y,
		unsigned char muki) {
	unsigned char set_x = wall_x, set_y = wall_y;

	//x座標方向を変更するとき
	if ((muki == MUKI_RIGHT) || (muki == MUKI_LEFT)) {
		if (muki == MUKI_RIGHT) {
		} else if (muki == MUKI_LEFT) {
			if (wall_x == 0) {		//一番左壁は管理しない
				return;
			} else {
				set_x = wall_x - 1;	//必ず右壁を更新するように、座標を変える
			}
		}
		if (set_x < MAZE_SIZE) {
			set_maze_wall(&x_wall_exist[set_y], set_x, false);//x_maze_wall[y]のx番目の右壁にfalseを代入
		} else {		//適切でない値が入ってる
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("存在しないx座標の壁の存在を消そうとしています\n\r");
			myprintf("forget_exist関数内\n\r");
		}

		//y座標方向を変更するとき
	} else if ((muki == MUKI_UP) || (muki == MUKI_DOWN)) {
		if (muki == MUKI_UP) {
		} else if (muki == MUKI_DOWN) {
			if (wall_y == 0) {		//一番下壁は管理しない
				return;
			} else {
				set_y = wall_y - 1;	//必ず上壁を更新するように、座標を変える
			}
		}
		if (set_y < MAZE_SIZE) {
			set_maze_wall(&y_wall_exist[set_x], set_y, false);//x_maze_wall[y]のx番目の上壁に1false代入
		} else {		//適切でない値が入ってる
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("存在しないy座標の壁の存在を消そうとしています\n\r");
			myprintf("forget_exist関数内\n\r");
		}

	}

}
bool map::check_exist(unsigned char wall_x, unsigned char wall_y,
		unsigned char muki) {
	unsigned char target_x = wall_x, target_y = wall_y;

	//x座標方向を見るするとき
	if ((muki == MUKI_RIGHT) || (muki == MUKI_LEFT)) {
		if (muki == MUKI_RIGHT) {
		} else if (muki == MUKI_LEFT) {
			if (wall_x == 0) {		//一番左壁は管理しない
				return true;
			} else {
				target_x = wall_x - 1;	//必ず右壁を見るように、座標を変える
			}
		}
		if (target_x < MAZE_SIZE) {
			return get_maze_wall(x_wall_exist[target_y], target_x);
		} else {		//適切でない値が入ってる
			mouse::error();
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("存在しないx座標の壁の存在を読もうとしています\n\r");
			myprintf("check_exist関数内\n\r");
			return -1;
		}

		//y座標方向を変更するとき
	} else if ((muki == MUKI_UP) || (muki == MUKI_DOWN)) {
		if (muki == MUKI_UP) {
		} else if (muki == MUKI_DOWN) {
			if (wall_y == 0) {		//一番下壁は常に壁が存在
				return true;
			} else {
				target_y = wall_y - 1;	//必ず上壁を更新するように、座標を変える
			}
		}
		if (target_y < MAZE_SIZE) {
			return get_maze_wall(y_wall_exist[target_x], target_y);
		} else {		//適切でない値が入ってる
			mouse::error();
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("存在しないy座標の壁の存在を読もうとしています\n\r");
			myprintf("check_exist関数内\n\r");
			return -1;
		}
	}

	return false;
}

bool map::check_exist(unsigned char wall_x, unsigned char wall_y,
		compas dir) {
	unsigned char target_x = wall_x, target_y = wall_y;

	//x座標方向を見るするとき
	if ((dir == east) || (dir == west)) {
		if (dir == west) {
			if (wall_x == 0) {		//一番西壁は管理しない
				return true;
			} else {
				target_x = wall_x - 1;	//必ず東壁を見るように、座標を変える
			}
		}
		if (target_x < MAZE_SIZE) {
			return get_maze_wall(x_wall_exist[target_y], target_x);
		} else {		//適切でない値が入ってる
			mouse::error();
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("存在しないx座標の壁の存在を読もうとしています\n\r");
			myprintf("check_exist関数内\n\r");
			return -1;
		}

		//y座標方向を変更するとき
	} else if ((dir == north) || (dir == south)) {
		if (dir == south) {
			if (wall_y == 0) {		//一番南壁は常に壁が存在
				return true;
			} else {
				target_y = wall_y - 1;	//必ず北壁を更新するように、座標を変える
			}
		}
		if (target_y < MAZE_SIZE) {
			return get_maze_wall(y_wall_exist[target_x], target_y);
		} else {		//適切でない値が入ってる
			mouse::error();
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("存在しないy座標の壁の存在を読もうとしています\n\r");
			myprintf("check_exist関数内\n\r");
			return -1;
		}
	}

	return false;
}


void map::create_wall(unsigned char wall_x, unsigned char wall_y,
		unsigned char muki) {
	unsigned char set_x = wall_x, set_y = wall_y;

	//x座標方向を変更するとき
	if ((muki == MUKI_RIGHT) || (muki == MUKI_LEFT)) {
		if (muki == MUKI_RIGHT) {
		} else if (muki == MUKI_LEFT) {
			if (wall_x == 0) {		//一番左壁は管理しない
				return;
			} else {
				set_x = wall_x - 1;	//必ず右壁を更新するように、座標を変える
			}
		}
		if (set_x < MAZE_SIZE) {
			set_maze_wall(&x_maze_wall[set_y], set_x, true);//x_maze_wall[y]のx番目の右壁に1を代入
		} else {		//適切でない値が入ってる
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("存在しないx座標に壁を作ろうとしています\n\r");
			myprintf("create_wall関数内\n\r");
		}

		//y座標方向を変更するとき
	} else if ((muki == MUKI_UP) || (muki == MUKI_DOWN)) {
		if (muki == MUKI_UP) {
		} else if (muki == MUKI_DOWN) {
			if (wall_y == 0) {		//一番下壁は管理しない
				return;
			} else {
				set_y = wall_y - 1;	//必ず上壁を更新するように、座標を変える
			}
		}
		if (set_y < MAZE_SIZE) {
			set_maze_wall(&y_maze_wall[set_x], set_y, true);//x_maze_wall[y]のx番目の右壁に1を代入
		} else {		//適切でない値が入ってる
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("存在しないy座標に壁を作ろうとしています\n\r");
			myprintf("create_wall関数内\n\r");
		}

	}

}
void map::destroy_wall(unsigned char wall_x, unsigned char wall_y,
		unsigned char muki) {
	unsigned char set_x = wall_x, set_y = wall_y;

	//x座標方向を変更するとき
	if ((muki == MUKI_RIGHT) || (muki == MUKI_LEFT)) {
		if (muki == MUKI_RIGHT) {
		} else if (muki == MUKI_LEFT) {
			if (wall_x == 0) {		//一番左壁は管理しない
				return;
			} else {
				set_x = wall_x - 1;	//必ず右壁を更新するように、座標を変える
			}
		}
		if (set_x < MAZE_SIZE) {
			set_maze_wall(&x_maze_wall[set_y], set_x, false);//x_maze_wall[y]のx番目の右壁にfalseを代入
		} else {		//適切でない値が入ってる
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("存在しないx座標に壁を作ろうとしています\n\r");
			myprintf("destroy_wall関数内\n\r");
		}

		//y座標方向を変更するとき
	} else if ((muki == MUKI_UP) || (muki == MUKI_DOWN)) {
		if (muki == MUKI_UP) {
		} else if (muki == MUKI_DOWN) {
			if (wall_y == 0) {		//一番下壁は管理しない
				return;
			} else {
				set_y = wall_y - 1;	//必ず上壁を更新するように、座標を変える
			}
		}
		if (set_y < MAZE_SIZE) {
			set_maze_wall(&y_maze_wall[set_x], set_y, false);//x_maze_wall[y]のx番目の上壁に1false代入
		} else {		//適切でない値が入ってる
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("存在しないy座標に壁を作ろうとしています\n\r");
			myprintf("destroy_wall関数内\n\r");
		}

	}

}
bool map::get_wall(unsigned char wall_x, unsigned char wall_y,
		unsigned char muki) {
	unsigned char target_x = wall_x, target_y = wall_y;

	//x座標方向を見るするとき
	if ((muki == MUKI_RIGHT) || (muki == MUKI_LEFT)) {
		if (muki == MUKI_RIGHT) {
		} else if (muki == MUKI_LEFT) {
			if (wall_x == 0) {		//一番左壁は管理しない
				return true;
			} else {
				target_x = wall_x - 1;	//必ず右壁を見るように、座標を変える
			}
		}
		if (target_x < MAZE_SIZE) {
			return get_maze_wall(x_maze_wall[target_y], target_x);
		} else {		//適切でない値が入ってる
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("存在しないx座標の壁を読もうとしています\n\r");
			myprintf("get_wall関数内\n\r");
			return -1;
		}

		//y座標方向を変更するとき
	} else if ((muki == MUKI_UP) || (muki == MUKI_DOWN)) {
		if (muki == MUKI_UP) {
		} else if (muki == MUKI_DOWN) {
			if (wall_y == 0) {		//一番下壁は常に壁が存在
				return true;
			} else {
				target_y = wall_y - 1;	//必ず上壁を更新するように、座標を変える
			}
		}
		if (target_y < MAZE_SIZE) {
			return get_maze_wall(y_maze_wall[target_x], target_y);
		} else {		//適切でない値が入ってる
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("存在しないy座標の壁を読もうとしています\n\r");
			myprintf("get_wall関数内\n\r");
			return -1;
		}
	}

	return false;
}

void map::reset_wall() {
	//壁を消す
	for (int i = 0; i < MAZE_SIZE; i++) {
		x_maze_wall[i].all = 0;
		y_maze_wall[i].all = 0;
		x_wall_exist[i].all = 0;
		y_wall_exist[i].all = 0;
	}
	//外壁は入れる
	for (int i = 0; i < MAZE_SIZE; i++) {
		create_wall(0, i, MUKI_LEFT);
		remember_exist(0, i, MUKI_LEFT);
		create_wall(MAZE_SIZE - 1, i, MUKI_RIGHT);
		remember_exist(MAZE_SIZE - 1, i, MUKI_RIGHT);
		create_wall(i, 0, MUKI_DOWN);
		remember_exist(i, 0, MUKI_DOWN);
		create_wall(i, MAZE_SIZE - 1, MUKI_UP);
		remember_exist(i, MAZE_SIZE - 1, MUKI_UP);
	}
	//(0，0)はわかってる
	create_wall(0, 0, MUKI_RIGHT);
	remember_exist(0, 0, MUKI_RIGHT);
	destroy_wall(0, 0, MUKI_UP);
	remember_exist(0, 0, MUKI_UP);
}

void map::draw_map(bool write_step) {
	signed char tekitou_x = 0, tekitou_y = MAZE_SIZE - 1;

	myprintf("\n-----start draw_map-------\n\r");

	//上辺
	for (tekitou_x = 0; tekitou_x < MAZE_SIZE; tekitou_x++)
		myprintf("+---");
	myprintf("+\n\r");

	myprintf("|");	//左端の壁
	for (tekitou_x = 0; tekitou_x < MAZE_SIZE - 1; tekitou_x++) {

		if (write_step)
			myprintf("%3d", step::get_step(tekitou_x, tekitou_y));
		else
			myprintf("   ");

		if ((get_wall(tekitou_x, tekitou_y, MUKI_RIGHT) == true)
				|| (get_wall(tekitou_x + 1, tekitou_y, MUKI_LEFT) == true)) {//今書いたマスの右の壁があれば壁を書く
			myprintf("|");
		} else {
			myprintf(" ");	//なければ壁は書かない
		}
	}

	if (write_step)
		myprintf("%3d", step::get_step(tekitou_x, tekitou_y));
	else
		myprintf("   ");

	myprintf("|\n\r");	//右端の壁

	for (tekitou_y = MAZE_SIZE - 2; tekitou_y >= 0; tekitou_y--) {
		//////////////////////////////////////////迷路の壁の行
		for (tekitou_x = 0; tekitou_x < MAZE_SIZE; tekitou_x++) {
			myprintf("+");	//柱
			if ((get_wall(tekitou_x, tekitou_y, MUKI_UP) == true)
					|| (get_wall(tekitou_x, tekitou_y + 1, MUKI_DOWN) == true)) {//壁があるなら
				myprintf("---");
			} else {
				myprintf("   ");
			}
		}
		myprintf("+\n\r");

		/////////////////////////////////////////迷路のマス目の行
		myprintf("|");	//左端の壁
		for (tekitou_x = 0; tekitou_x < MAZE_SIZE - 1; tekitou_x++) {

			if (write_step)
				myprintf("%3d", step::get_step(tekitou_x, tekitou_y));
			else
				myprintf("   ");

			if ((get_wall(tekitou_x, tekitou_y, MUKI_RIGHT) == true)
					|| (get_wall(tekitou_x + 1, tekitou_y, MUKI_LEFT) == true)) {//今書いたマスの右の壁があれば壁を書く
				myprintf("|");
			} else {
				myprintf(" ");	//なければ壁は書かない
			}
		}
		if (write_step)
			myprintf("%3d", step::get_step(tekitou_x, tekitou_y));
		else
			myprintf("   ");

		myprintf("|\n\r");	//右端の壁
	}

	//下辺
	for (tekitou_x = 0; tekitou_x < MAZE_SIZE; tekitou_x++)
		myprintf("+---");
	myprintf("+\n\r");

}

/*
 void map::convert_mapdata(unsigned char (*hiramatu_data)[16]){
 for(char x=0;x<16;x++){
 for(char y=0;y<16;y++){
 if((hiramatu_data[x][y] & 2) == 2){		//東壁があれば
 create_wall(x,y,MUKI_RIGHT);
 }else{
 destroy_wall(x,y,MUKI_RIGHT);
 }
 if((hiramatu_data[x][y] & 1) == 1){		//南壁があれば
 create_wall(x,y,MUKI_UP);
 }else{
 destroy_wall(x,y,MUKI_UP);
 }
 }
 }
 }
 */

void map::input_map_data(const MAP_DATA *input_data) {
	//データ入力
	for (int i = 0; i < MAZE_SIZE; i++) {
		x_maze_wall[i].all = input_data->x_wall[i].all;
		y_maze_wall[i].all = input_data->y_wall[i].all;
		x_wall_exist[i].all = input_data->x_known[i].all;
		y_wall_exist[i].all = input_data->y_known[i].all;
	}
}

void map::output_map_data(MAP_DATA* const output_data) {
	//データ出力
	for (int i = 0; i < MAZE_SIZE; i++) {
		output_data->x_wall[i].all = x_maze_wall[i].all;
		output_data->y_wall[i].all = y_maze_wall[i].all;
		output_data->x_known[i].all = x_wall_exist[i].all;
		output_data->y_known[i].all = y_wall_exist[i].all;
	}
}

map::map() {
	reset_wall();
}

map::~map() {

}

DIRECTION step::save_direction;
unsigned short step::maze_step[MAZE_SIZE][MAZE_SIZE];

void step::step_reset() {
	for (int i = 0; i < MAZE_SIZE; i++) {
		for (int j = 0; j < MAZE_SIZE; j++) {
			maze_step[i][j] = STEP_INIT;
		}
	}
}

void step::set_step(unsigned char target_x, unsigned char target_y) {
	//座標を管理するための配列
	unsigned char x_coordinate[965];
	unsigned char y_coordinate[965];

	//array[x]={0};ってやるとメモリ食うらしいのでForで初期化
	for (int16_t i = 0; i < 965; i++) {
		x_coordinate[i] = 0;
		y_coordinate[i] = 0;
	}

	unsigned char x_count = 0, y_count = 0;	//一時的に座標をもっとくよう
	unsigned char head, tail;		//

	step_reset();
	maze_step[target_x][target_y] = 0;

	//coordinate  [tail][][][] -> [][][head]

	head = 1;
	tail = 0;

	//Qの最初には目標の座標を入れとく
	x_coordinate[tail] = target_x;
	y_coordinate[tail] = target_y;

	while (head != tail) {
		//座標を代入
		x_count = x_coordinate[tail];
		y_count = y_coordinate[tail];

		tail++;

		//左マス
		if ((x_count - 1) >= 0) {		//座標が迷路内(x-1が0以上)にあり
			if ((maze_step[x_count - 1][y_count] == STEP_INIT)) {//歩数を入れてない（入ってる歩数がSTEP_INIT）
				if (map::get_wall(x_count, y_count, MUKI_LEFT) == false) {//元のマスの左壁がないなら
					maze_step[x_count - 1][y_count] =
							maze_step[x_count][y_count] + 1;		//歩数を代入
					//この座標を保持
					x_coordinate[head] = (x_count - 1);
					y_coordinate[head] = y_count;
					head++;
				}
			}
		}

		//右マス
		if ((x_count + 1) < MAZE_SIZE) {	//座標が迷路内(x+1がMAZE_SIZE未満)にあり
			if ((maze_step[x_count + 1][y_count] == STEP_INIT)) {//歩数を入れてない（入ってる歩数がSTEP_INIT）
				if (map::get_wall(x_count, y_count, MUKI_RIGHT) == false) {	//元のマスの右壁がない
					maze_step[x_count + 1][y_count] =
							maze_step[x_count][y_count] + 1;	//歩数を代入
					//この座標を保持
					x_coordinate[head] = (x_count + 1);
					y_coordinate[head] = y_count;
					head++;
				}
			}
		}

		//下マス
		if ((y_count - 1) >= 0) {		//座標が迷路内(y-1が0以上)にあり
			if ((maze_step[x_count][y_count - 1] == STEP_INIT)) {//歩数を入れてない（入ってる歩数がSTEP_INIT）
				if (map::get_wall(x_count, y_count, MUKI_DOWN) == false) {//元のマスの下壁がない
					maze_step[x_count][y_count - 1] =
							maze_step[x_count][y_count] + 1;	//歩数を代入
					//この座標を保持
					x_coordinate[head] = x_count;
					y_coordinate[head] = (y_count - 1);
					head++;
				}
			}
		}

		//上マス
		if ((y_count + 1) < MAZE_SIZE) {	//x,y+1の座標が迷路内(MAZE_SIZE未満)である
			if ((maze_step[x_count][y_count + 1] == STEP_INIT)) {//歩数を入れてない（入ってる歩数がSTEP_INIT）
				if (map::get_wall(x_count, y_count, MUKI_UP) == false) {//元のマスの上壁がない
					maze_step[x_count][y_count + 1] =
							maze_step[x_count][y_count] + 1;	//歩数を代入
					//この座標を保持
					x_coordinate[head] = x_count;
					y_coordinate[head] = (y_count + 1);
					head++;
				}
			}
		}

		if (head > 965) {		//配列越えたらエラー
			myprintf("エラー!\n\radachi::set_step()内\n\r");
			break;
		}

	}

}

void step::set_step_by_known(unsigned char target_x, unsigned char target_y) {
	//座標を管理するための配列
	unsigned char x_coordinate[965];
	unsigned char y_coordinate[965];

	//array[x]={0};ってやるとメモリ食うらしいのでForで初期化
	for (int16_t i = 0; i < 965; i++) {
		x_coordinate[i] = 0;
		y_coordinate[i] = 0;
	}

	unsigned char x_count = 0, y_count = 0;	//一時的に座標をもっとくよう
	unsigned char head, tail;		//

	step_reset();
	maze_step[target_x][target_y] = 0;

	//coordinate  [tail][][][] -> [][][head]

	head = 1;
	tail = 0;

	//Qの最初には目標の座標を入れとく
	x_coordinate[tail] = target_x;
	y_coordinate[tail] = target_y;

	while (head != tail) {
		//座標を代入
		x_count = x_coordinate[tail];
		y_count = y_coordinate[tail];

		tail++;

		//左マス
		if ((x_count - 1) >= 0) {		//座標が迷路内(x-1が0以上)にあり
			if ((maze_step[x_count - 1][y_count] == STEP_INIT)) {//歩数を入れてない（入ってる歩数がSTEP_INIT）
				if (map::get_wall(x_count, y_count, MUKI_LEFT) == false) {//元のマスの左壁がないなら
					if (map::check_exist(x_count, y_count,
					MUKI_LEFT)) {		//左壁を見ているなら
						maze_step[x_count - 1][y_count] =
								maze_step[x_count][y_count] + 1;		//歩数を代入
						//この座標を保持
						x_coordinate[head] = (x_count - 1);
						y_coordinate[head] = y_count;
						head++;
					}
				}
			}
		}

		//右マス
		if ((x_count + 1) < MAZE_SIZE) {	//座標が迷路内(x+1がMAZE_SIZE未満)にあり
			if ((maze_step[x_count + 1][y_count] == STEP_INIT)) {//歩数を入れてない（入ってる歩数がSTEP_INIT）
				if (map::get_wall(x_count, y_count, MUKI_RIGHT) == false) {	//元のマスの右壁がない
					if (map::check_exist(x_count, y_count,
					MUKI_RIGHT)) {	//右壁を見ているなら
						maze_step[x_count + 1][y_count] =
								maze_step[x_count][y_count] + 1;	//歩数を代入
						//この座標を保持
						x_coordinate[head] = (x_count + 1);
						y_coordinate[head] = y_count;
						head++;
					}
				}
			}
		}

		//下マス
		if ((y_count - 1) >= 0) {		//座標が迷路内(y-1が0以上)にあり
			if ((maze_step[x_count][y_count - 1] == STEP_INIT)) {//歩数を入れてない（入ってる歩数がSTEP_INIT）
				if (map::get_wall(x_count, y_count, MUKI_DOWN) == false) {//元のマスの下壁がない
					if (map::check_exist(x_count, y_count,
					MUKI_DOWN)) {		//下壁が既知なら
						maze_step[x_count][y_count - 1] =
								maze_step[x_count][y_count] + 1;	//歩数を代入
						//この座標を保持
						x_coordinate[head] = x_count;
						y_coordinate[head] = (y_count - 1);
						head++;
					}
				}
			}
		}

		//上マス
		if ((y_count + 1) < MAZE_SIZE) {	//x,y+1の座標が迷路内(MAZE_SIZE未満)である
			if ((maze_step[x_count][y_count + 1] == STEP_INIT)) {//歩数を入れてない（入ってる歩数がSTEP_INIT）
				if (map::get_wall(x_count, y_count, MUKI_UP) == false) {//元のマスの上壁がない
					if (map::check_exist(x_count, y_count,
					MUKI_UP)) {		//上壁が既知なら
						maze_step[x_count][y_count + 1] =
								maze_step[x_count][y_count] + 1;	//歩数を代入
						//この座標を保持
						x_coordinate[head] = x_count;
						y_coordinate[head] = (y_count + 1);
						head++;
					}
				}
			}
		}

		if (head > 965) {		//配列越えたらエラー
			myprintf("エラー!\n\radachi::set_step()内\n\r");
			break;
		}

	}

}

unsigned int step::get_step(unsigned char target_x, unsigned char target_y) {
	return maze_step[target_x][target_y];
}

void step::close_one_dead_end(unsigned char target_x, unsigned char target_y) {
	union {
		unsigned char all;				//一括
		struct {
			unsigned char count :4;		//		行けない方向の個数
			unsigned char up :1;		//↑	x=0,y=1の方向
			unsigned char down :1;		//↓	x=0,y=-1の方向
			unsigned char left :1;		//←	x=-1,y=0の方向
			unsigned char right :1;		//→	x=1,y=0の方向
		} direction;
	} dead_end;

	dead_end.all = 0;	//初期化

	//左マス
	if ((map::get_wall(target_x, target_y, MUKI_LEFT))) {	//左壁があるなら
		dead_end.direction.left = 1;	//左フラグを建てる
		dead_end.direction.count++;		//1足す
	} else if ((target_x - 1) >= 0) {		//座標が迷路内(x-1が0以上)にあり
		if ((maze_step[target_x - 1][target_y] == STEP_INIT)
				|| (map::check_exist(target_x, target_y, MUKI_LEFT) == false)) {//左のマスに行けない（入ってる歩数が255 または ）
			dead_end.direction.left = 1;	//左フラグオン
			dead_end.direction.count++;		//1足す
		}
	}

	//右マス
	if ((map::get_wall(target_x, target_y, MUKI_RIGHT))) {	//右壁があるなら
		dead_end.direction.right = 1;		//右フラグを建てる
		dead_end.direction.count++;			//1足す
	} else if ((target_x + 1) < MAZE_SIZE) {	//座標が迷路内(x+1がMax_x未満)にあり
		if ((maze_step[target_x + 1][target_y] == STEP_INIT)
				|| (map::check_exist(target_x, target_y, MUKI_RIGHT) == false)) {//右のマスに行けない（入ってる歩数が255 または 壁がある）
			dead_end.direction.right = 1;	//右フラグを建てる
			dead_end.direction.count++;		//1足す
		}
	}

	//下マス
	if ((map::get_wall(target_x, target_y, MUKI_DOWN))) {	//下壁があるなら
		dead_end.direction.down = 1;		//下フラグを建てる
		dead_end.direction.count++;			//1足す
	} else if ((target_y - 1 >= 0)) {		//座標が迷路内(y-1が0以上)にあり
		if ((maze_step[target_x][target_y - 1] == STEP_INIT)
				|| (map::check_exist(target_x, target_y, MUKI_DOWN) == false)) {//下のマスに行けない（入ってる歩数が255 または 壁がある）
			dead_end.direction.down = 1;	//下フラグを建てる
			dead_end.direction.count++;		//1足す
		}
	}

	//上マス
	if ((map::get_wall(target_x, target_y, MUKI_UP))) {		//上壁があるなら
		dead_end.direction.up = 1;			//上フラグを建てる
		dead_end.direction.count++;			//1足す
	} else if ((target_y + 1 < MAZE_SIZE)) {	//x,y+1の座標が迷路内(MAX_y未満)である
		if ((maze_step[target_x][target_y + 1] == STEP_INIT)
				|| (map::check_exist(target_x, target_y, MUKI_UP) == false)) {//上のマスに行けない（入ってる歩数が255　または　壁がある）
			dead_end.direction.up = 1;		//上フラグを建てる
			dead_end.direction.count++;		//1足す
		}
	}

	//袋小路をふさぐ
	if (dead_end.direction.count >= 3) {		//行けない方向が3以上 = 袋小路なら
		if ((target_x == 0) && (target_y == 0)) {		//それがスタートなら何もしない
		} else if ((target_x == GOAL_x) && (target_y == GOAL_y)) {//それがゴールでも何もしない
		} else {							//上記以外なら袋小路を潰す
			maze_step[target_x][target_y] = STEP_INIT;	//歩数を初期化
			//袋小路のあいてる方向についてもう一回同じことを行う
			if (dead_end.direction.left == 0) {
				map::create_wall(target_x, target_y, MUKI_LEFT);
				map::remember_exist(target_x, target_y, MUKI_LEFT);
				close_one_dead_end(target_x - 1, target_y);

			}
			if (dead_end.direction.right == 0) {
				map::create_wall(target_x, target_y, MUKI_RIGHT);
				map::remember_exist(target_x, target_y, MUKI_RIGHT);
				close_one_dead_end(target_x + 1, target_y);
			}
			if (dead_end.direction.down == 0) {
				map::create_wall(target_x, target_y, MUKI_DOWN);
				map::remember_exist(target_x, target_y, MUKI_DOWN);
				close_one_dead_end(target_x, target_y - 1);
			}
			if (dead_end.direction.up == 0) {
				map::create_wall(target_x, target_y, MUKI_UP);
				map::remember_exist(target_x, target_y, MUKI_UP);
				close_one_dead_end(target_x, target_y + 1);
			}
		}
	}
}

void step::close_dead_end() {
	for (int i = 0; i < MAZE_SIZE; i++) {
		for (int j = 0; j < MAZE_SIZE; j++) {
			close_one_dead_end(i, j);
		}
	}
}

step::step() {
	map::reset_wall();
	step_reset();

}

step::step(const MAP_DATA* input_data) {
	map::input_map_data(input_data);
}

step::~step() {

}
PATH path::path_memory[PATH_MAX];

void path::set_step_for_shortest(unsigned char target_x,
		unsigned char target_y) {
	set_step_by_known(target_x, target_y);		//既知の壁だけで歩数マップを作成
	close_dead_end();							//袋小路を潰す
}

void path::displace_path(unsigned int path_number) {
	//1個ずらす
	for (uint16_t number = path_number;
			path_memory[number].element.flag == TRUE; number++) {
		path_memory[number].all = path_memory[number + 1].all;
	}
}

void path::improve_path() {
	unsigned int count = 0;

	while (path_memory[count].element.flag == TRUE) {		//pathが終われば終了

		if (path_memory[count].element.distance >= 1) {		//90mm以上直進するなら

			if (path_memory[count + 1].element.distance >= 1) {	//ターン後も90mm以上直進するなら	大回りのチェックを行う
				path_memory[count].element.turn = 2;				//大回りターンに変更
				path_memory[count].element.distance -= 1;		//直線距離を90mm減らす
				path_memory[count + 1].element.distance -= 1;	//直線距離を90mm減らす

			} else {										//ターン後90mm直進はしないなら

				if (path_memory[count].element.muki
						== path_memory[count + 1].element.muki) {//同じ方向に曲がるなら(Uターン)

					if (path_memory[count + 2].element.distance >= 1) {	//Uターン後90mm直進するなら
						path_memory[count].element.turn = 3;		//180°ターンに変更
						path_memory[count].element.distance -= 1;//直線距離を90mm減らす
						path_memory[count + 2].element.distance -= 1;//直線距離を90mm減らす

						//1個ずらす
						displace_path(count + 1);

					} else {									//Uターン後すぐ曲がるなら

						if (path_memory[count + 2].element.flag == FALSE) {	//pathが終わってないかチェック　終わってなければ逆方向にターンのはず
							//ナナメの処理なので何もしない
						}

					}

				} else {		//違う方法に曲がるなら
					//ナナメの処理なので何もしない
				}

			}

		}

		count++;
	}

}

void path::improve_advance_path() {
	unsigned int count = 0;
	unsigned char temp_distance = 0;	//一時的な距離保存
	unsigned char naname_flag = FALSE;	//現在機体が斜めかを判断	ONなら斜め走行中

	while (path_memory[count].element.flag == TRUE) {		//pathが終われば終了

		if (naname_flag == TRUE) {			//斜め走行中なら	確実に直進距離(distance)が0のはず

			if (path_memory[count + 1].element.distance >= 1) {	//次のターン後90mm以上直進(斜め終わり)

				path_memory[count].element.turn = 5;			//終わり45°ターンに変更
				path_memory[count + 1].element.distance -= 1;	//直線距離を90mm減らす
				naname_flag = FALSE;
				count++;												//配列を次へ

			} else if (path_memory[count + 2].element.distance >= 1) {//次の次のターン後90mm以上直進(斜め終わり)

				if (path_memory[count].element.muki
						== path_memory[count + 1].element.muki) {	//同じ方向の2回ターン

					path_memory[count].element.turn = 7;		//終わり135°ターンに変更
					displace_path(count + 1);							//一個ずらす
					path_memory[count + 1].element.distance -= 1;//ターン後の直線距離を90mm減らす
					naname_flag = FALSE;
					count++;										//配列を次へ

				} else {										//交互のターン(ギザギザ)

					path_memory[count].element.distance += 1;	//斜めの直線距離を1増やす
					temp_distance = path_memory[count].element.distance;//距離を一時的に持っておく
					displace_path(count);							//一個ずらす
					path_memory[count].element.distance = temp_distance;//距離を入れなおす

				}

			} else {											//まだまだ斜めは続くなら

				if (path_memory[count].element.muki
						== path_memory[count + 1].element.muki) {//同じ方向の2回ターン	コの字

					path_memory[count].element.turn = 8;		//斜め90°ターンに変更
					displace_path(count + 1);							//一個ずらす
					count++;										//配列を次へ

				} else {									//違う方向の2回ターン	ギザギザ

					path_memory[count].element.distance += 1;	//斜めの直線距離を1増やす
					temp_distance = path_memory[count].element.distance;//距離を一時的に持っておく
					displace_path(count);							//一個ずらす
					path_memory[count].element.distance = temp_distance;//距離を入れなおす

				}
			}

		} else {										//斜めじゃなければ

			if (path_memory[count + 1].element.distance >= 1) {	//ターン後も90mm以上直進するなら	大回りのチェックを行う

				if ((count != 0) || (path_memory[0].element.distance > 1)) {//初っ端のターンじゃなければ

					path_memory[count].element.turn = 2;			//大回りターンに変更
					path_memory[count].element.distance -= 1;	//直線距離を90mm減らす
					path_memory[count + 1].element.distance -= 1;//直線距離を90mm減らす

				} else {
					//TODO 初っ端大回り90ターンの処理
				}

			} else {										//ターン後90mm直進はしないなら

				if (path_memory[count].element.muki
						== path_memory[count + 1].element.muki) {//同じ方向に曲がるなら(Uターン)

					if (path_memory[count + 2].element.distance >= 1) {	//Uターン後90mm直進するなら

						path_memory[count].element.turn = 3;		//180°ターンに変更
						path_memory[count].element.distance -= 1;//直線距離を90mm減らす
						path_memory[count + 2].element.distance -= 1;//直線距離を90mm減らす
						displace_path(count + 1);						//一個ずらす

					} else {									//Uターン後すぐ曲がるなら

						if (path_memory[count + 2].all != 0) {//pathが終わってないかチェック　終わってなければ逆方向にターンのはず

							path_memory[count].element.turn = 6;	//135°ターンに変更
							path_memory[count].element.distance -= 1;//直線距離を90mm減らす
							displace_path(count + 1);					//一個ずらす
							naname_flag = TRUE;

						}

					}

				} else {		//違う方法に曲がるなら

					path_memory[count].element.turn = 4;			//45°ターンに変更
					path_memory[count].element.distance -= 1;	//直線距離を90mm減らす
					naname_flag = TRUE;

				}

			}
			count++;		//配列を次へ
		}
	}

}

void path::create_path() {
	int8_t path_x, path_y;							//位置管理用
	int8_t path_direction_x, path_direction_y;		//方向管理用
	bool straight_flag;			//直線できるかどうか判別用フラグ
	SAVE_DIRECTION save_direction;				//次に行くマスの方向を保存
	uint16_t count = 0;	//数を数えるだけの変数

	//set_step_for_shortest(GOAL_x,GOAL_y);

	set_step_by_known(GOAL_x, GOAL_y);

	path_reset();

	path_direction_x = 0;	//方向を初期化
	path_direction_y = 1;

	path_x = 0;		//位置を初期化
	path_y = 0;

	straight_flag = false;	//フラグは折っておく

	path_memory[count].element.distance += 1;	//最初は必ず半区画直進する
	path_memory[count].element.flag = TRUE;		//最初だし続行フラグを建てる

	while (1) {

		save_direction.all = 0;		//次に行く方向初期化
		straight_flag = false;	//フラグは折っておく

		path_x += path_direction_x; 		//位置修正
		path_y += path_direction_y;

		//GOALにたどり着いたら終了
		if ((path_x == GOAL_x) && (path_y == GOAL_y)) {
			path_memory[count].element.distance += 1;	//90mm直進を追加	ゴールに入りきるため
			path_memory[count + 1].element.flag = FALSE;		//続行フラグを折っておく
			break;
		}

		//左
		if ((path_x - 1) >= 0) {		//path_x-1,path_yの座標が迷路内(0以上)である
			if (get_step(path_x - 1, path_y) < get_step(path_x, path_y)) {//歩数の小さいほうへ
				if ((map::get_wall(path_x, path_y, MUKI_LEFT) == false)) {//壁がないなら
					save_direction.element.left = 1;		//次に進む方向の選択肢に追加
					if ((path_direction_x == -1) && (path_direction_y == 0)) {//左を向いてるとき（直進できるとき）
						straight_flag = true;	//直進フラグをたてる
					}
				}
			}

		}

		//右
		if ((path_x + 1) < MAZE_SIZE) {	//path_x+1,path_yの座標が迷路内である
			if (get_step(path_x + 1, path_y) < get_step(path_x, path_y)) {//歩数の小さいほうへ
				if ((map::get_wall(path_x, path_y, MUKI_RIGHT) == false)) {	//壁がないなら
					save_direction.element.right = 1;		//次に進む方向の選択肢に追加
					if ((path_direction_x == 1) && (path_direction_y == 0)) {//右を向いてるとき（直進できるとき）
						straight_flag = true;	//直進フラグをたてる
					}
				}
			}
		}

		//下
		if ((path_y - 1) >= 0) {		//path_x,path_y-1の座標が迷路内(0以上)である
			if (get_step(path_x, path_y - 1) < get_step(path_x, path_y)) {//歩数の小さいほうへ
				if ((map::get_wall(path_x, path_y, MUKI_DOWN) == false)) {//壁がないなら
					save_direction.element.down = 1;		//次に進む方向の選択肢に追加
					if ((path_direction_x == 0) && (path_direction_y == -1)) {//下を向いてるとき（直進できるとき）
						straight_flag = true;	//直進フラグをたてる
					}
				}
			}
		}

		//上
		if ((path_y + 1) < MAZE_SIZE) {	//path_x,path_y+1の座標が迷路内(16以下)である
			if (get_step(path_x, path_y + 1) < get_step(path_x, path_y)) {//歩数の小さいほうへ
				if ((map::get_wall(path_x, path_y, MUKI_UP) == false)) {//壁がないなら
					save_direction.element.up = 1;		//次に進む方向の選択肢に追加
					if ((path_direction_x == 0) && (path_direction_y == 1)) {//上を向いてるとき（直進できるとき）
						straight_flag = true;	//直進フラグをたてる
					}
				}
			}
		}

		if (straight_flag) {			//直進できるなら
			path_memory[count].element.distance += 2;	//半区間直進*2 を追加

		} else {								//ターンするなら
			path_memory[count].element.turn = 1;	//小回りターン

			if (path_direction_x == 0) {						//上か下向きのとき
				//右に行きたい
				if (save_direction.element.right == 1) {
					if (path_direction_y == 1) {	//上を向いてる
						//右向きターン
						path_memory[count].element.muki = MUKI_RIGHT;
					} else {					//下を向いてる
						//左向きターン
						path_memory[count].element.muki = MUKI_LEFT;
					}
					//左に行きたい
				} else {
					if (path_direction_y == -1) {	//下を向いてる
						//右向きターン
						path_memory[count].element.muki = MUKI_RIGHT;
					} else {					//上を向いてる
						//左向きターン
						path_memory[count].element.muki = MUKI_LEFT;
					}
				}

			} else {											//右か左向きのとき
				//上に行きたい
				if (save_direction.element.up == 1) {
					if (path_direction_x == -1) {	//左を向いてる
						//右向きターン
						path_memory[count].element.muki = MUKI_RIGHT;
					} else {					//右を向いてる
						//左向きターン
						path_memory[count].element.muki = MUKI_LEFT;
					}
					//下に行きたい
				} else {
					if (path_direction_x == 1) {	//右を向いてる
						//右向きターン
						path_memory[count].element.muki = MUKI_RIGHT;
					} else {					//左を向いてる
						//左向きターン
						path_memory[count].element.muki = MUKI_LEFT;
					}
				}
			}
			//ターンによる方向修正
			direction_turn(&path_direction_x, &path_direction_y,
					path_memory[count].element.muki);

			count++;
			path_memory[count].element.flag = TRUE;		//パスが続くのなら続行フラグを建てる

		}

	}

}

void path::create_path_advance() {
	create_path();
	improve_path();
}

void path::create_path_naname() {
	create_path();
	improve_advance_path();
}

void path::draw_path() {
	myprintf("path-start \n\r");

	for (int i = 0; path_memory[i].element.flag == TRUE; i++) {
		//直線
		myprintf("distance -> %2d *", path_memory[i].element.distance);
		if (MOUSE_MODE == 1)		//ハーフは半区間が45mm
			myprintf("45mm\n\r");
		else
			myprintf("90mm\n\r");

		//ターン
		//myprintf("turn -> %2d ", path_memory[i].element.turn);	//格納している値を表示
		myprintf("turn -> ");
		switch (path::get_path_turn_type(i)) {
		case none:
			myprintf("none");
			break;
		case small:
			myprintf("small");
			break;
		case big_90:
			myprintf("big_90");
			break;
		case big_180:
			myprintf("big_180");
			break;
		case begin_45:
			myprintf("begin_45");
			break;
		case end_45:
			myprintf("end_45");
			break;
		case begin_135:
			myprintf("begin_135");
			break;
		case end_135:
			myprintf("end_135");
			break;
		case oblique_90:
			myprintf("oblique_90");
			break;
		case spin_turn:
			myprintf("spin_turn");
			break;
		default:
			myprintf("error!! %d", path_memory[i].element.turn);
			break;
		}

		if (path_memory[i].element.muki == MUKI_RIGHT) {
			myprintf(" Right\n\r");
		} else if (path_memory[i].element.muki == MUKI_LEFT) {
			myprintf(" Left\n\r");
		}
	}
	myprintf("path-end \n\r");

}

void path::path_reset() {
	unsigned int reset_count;
	for (reset_count = 0; reset_count < PATH_MAX; reset_count++) {
		path_memory[reset_count].all = 0;
	}
}

bool path::get_path_flag(signed int index_number) {
	//pathがあるならtrue,ないならfalseを返す
	if (path_memory[index_number].element.flag == TRUE) {
		return true;
	} else {
		return false;
	}

}

float path::get_path_straight(unsigned int index_number) {
	return (0.045 * MOUSE_MODE
			* (float) path_memory[index_number].element.distance);
}

SLALOM_TYPE path::get_path_turn_type(unsigned int index_number) {
	switch (path_memory[index_number].element.turn) {
	case 0:
		return none;
		break;

	case 1:
		return small;
		break;

	case 2:
		return big_90;
		break;

	case 3:
		return big_180;
		break;

	case 4:
		return begin_45;
		break;

	case 5:
		return end_45;
		break;

	case 6:
		return begin_135;
		break;

	case 7:
		return end_135;
		break;

	case 8:
		return oblique_90;
		break;
	}

	return spin_turn;
}

unsigned char path::get_path_turn_muki(unsigned int index_number) {
	return path_memory[index_number].element.muki;
}

void direction_turn(signed char *direction_x, signed char *direction_y,
		unsigned char direction_turn_muki) {
	signed char temp_direction_x = (*direction_x);	//他の場所に保存しないと変換途中で参照する羽目になる
	signed char temp_direction_y = (*direction_y);
	if (direction_turn_muki == MUKI_LEFT) {
		*direction_x = (temp_direction_x) * 0 + (temp_direction_y) * (-1);//回転行列のθ=90の計算
		*direction_y = (temp_direction_x) * 1 + (temp_direction_y) * 0;	//回転行列のθ=90の計算
	} else {
		*direction_x = (temp_direction_x) * 0 + (temp_direction_y) * 1;	//回転行列のθ=-90の計算
		*direction_y = (temp_direction_x) * (-1) + (temp_direction_y) * 0;//回転行列のθ=-90の計算
	}

}

std::pair<int8_t, int8_t> compas_to_direction(compas tar){
	std::pair<int8_t, int8_t> ans(0,0);
	switch(tar){
	case north:
		ans.second = 1;
		break;
	case south:
		ans.second = -1;
		break;
	case east:
		ans.first = 1;
		break;
	case west:
		ans.first = -1;
		break;
	}
	return ans;
}

compas muki_to_compas(uint8_t muki){
	switch(muki){
	case MUKI_UP:
		return north;
		break;
	case MUKI_DOWN:
		return south;
		break;
	case MUKI_RIGHT:
		return east;
		break;
	case MUKI_LEFT:
		return west;
		break;
	}
}

uint16_t node_step::step[x_size][y_size];

bool node_step::able_set_step(uint8_t x, uint8_t y, compas muki, uint16_t step_val, bool by_known) {
	uint8_t def_muki = compas_to_define(muki);

	//見ていない部分には書き込めない
	if (by_known) {
		if (map::check_exist(x, y, def_muki) != TRUE)
			return false;
	}

	//壁がある部分には書き込めない
	if (map::get_wall(x, y, def_muki) == TRUE)
		return false;

	//書き込む歩数より小さい場所には書き込めない
	if (get_step(x, y, muki) <= step_val)
		return false;

	return true;
}

bool node_step::is_outside_array(uint8_t x_index, uint8_t y_index) {
	if (x_index >= x_size)
		return true;
	if (x_index < 0)
		return true;
	if (y_index >= y_size)
		return true;
	if (y_index < 0)
		return true;

	return false;
}

bool node_step::set_step(uint8_t x, uint8_t y, compas muki, uint16_t step_val, bool by_known){
	//代入用の変数
	uint8_t step_x=x;
	uint8_t step_y=y;

	switch (muki) {
	//南向きと西向きに変更してやりなおし
	case north:
		return set_step(x, y + 1, south, step_val, by_known);
		break;
	case east:
		return set_step(x+1, y, west, step_val, by_known);
		break;

	//南と西なら配列用にX座標を対応させる
	case south:
		step_x = 2 * x + 1;			//南向きだと横向きの壁なので、x方向が2x+1
		break;
	case west:
		step_x = 2*x;				//西向きだと縦向きの壁なので、x方向は2x
		break;
	}

	//配列の要素外に書き込むなら何もしない
	if (is_outside_array(step_x,step_y))
		return false;

	//書き込めるなら
	if (able_set_step(x,y,muki,step_val, by_known)) {
		step[step_x][step_y] = step_val;	//配列に歩数代入
		return true;
	}

	return false;
}

uint16_t node_step::get_step(uint8_t x, uint8_t y, compas muki) {
	//代入用の変数
	uint8_t step_x = x;
	uint8_t step_y = y;

	switch (muki) {
		//南向きと西向きに変更してやりなおして終了
	case north:
		return get_step(x, y + 1, south);
		break;
	case east:
		return get_step(x + 1, y, west);
		break;

		//南と西なら配列用にX座標を対応させる
	case south:
		step_x = 2 * x + 1;			//南向きだと横向きの壁なので、x方向が2x+1
		break;
	case west:
		step_x = 2 * x;				//西向きだと縦向きの壁なので、x方向は2x
		break;
	}

	//配列の要素外を読みだすときはInit_stepを
	if (is_outside_array(step_x, step_y))
		return init_step;

	return step[step_x][step_y];	//配列から歩数参照
}

compas node_step::get_min_compas(uint8_t x, uint8_t y) {
	compas ans;

	if (get_step(x, y, north) < get_step(x, y, south))
		ans = north;
	else
		ans = south;
	if (get_step(x, y, east) < get_step(x, y, ans))
		ans = east;
	if (get_step(x, y, west) < get_step(x, y, ans))
		ans = west;

	return ans;
}

void node_step::reset_step(uint16_t reset_val) {
	for (int x=0; x < x_size; x++) {
		for (int y = 0; y < y_size; y++)
		{
			step[x][y] = reset_val;
		}
	}

}

uint8_t node_step::compas_to_define(compas muki) {
	switch (muki) {
	case east:
		return MUKI_RIGHT;
	case west:
		return MUKI_LEFT;
	case north:
		return MUKI_UP;
	case south:
		return MUKI_DOWN;
	}
}


node_step::node_step() {
	reset_step(init_step);
}

node_step::node_step(uint16_t reset_val) {
	reset_step(reset_val);
}

node_step::~node_step() {

}

bool node_search::set_step_double(uint8_t double_x, uint8_t double_y, uint16_t step_val, bool by_known) {
	//2倍座標を通常の座標と向きに直す
	uint8_t x = double_x / 2;
	uint8_t y = double_y / 2;
	compas muki;
	if (double_x % 2 == 0) 		//縦壁なら
		muki = west;
	else if (double_y % 2 == 0) 	//横壁なら
		muki = south;

	return node_step::set_step(x, y, muki, step_val, by_known);

}

bool node_search::set_step_double(std::pair<uint8_t, uint8_t> xy, uint16_t step_val, bool by_known) {
	return set_step_double(xy.first, xy.second, step_val, by_known);
}

uint16_t node_search::get_step_double(uint8_t double_x, uint8_t double_y){
	//2倍座標を通常の座標と向きに直す
	uint8_t x = double_x / 2;
	uint8_t y = double_y / 2;
	compas muki;
	if (double_x % 2 == 0) 		//縦壁なら
		muki = west;
	else if (double_y % 2 == 0) 	//横壁なら
		muki = south;

	return node_step::get_step(x, y, muki);
}

void node_search::set_weight_algo(weight_algo weight) {
	algo = weight;
}

weight_algo node_search::get_weight_algo() {
	return algo;
}

void node_search::spread_step(std::vector< std::pair<uint8_t, uint8_t> > finish, bool by_known) {
	//座標管理は歩数の配列(X方向だけ倍)と異なりX,Y方向両方で倍にする　隣接座標の取り扱いが楽だから

	std::queue< std::pair<uint8_t, uint8_t> > que;		//座標管理用Queue　FirstがX、SecondがY
	std::pair<uint8_t, uint8_t> temp;
	std::queue< std::pair<int8_t, int8_t> > dir;		//方向管理用Queue　FirstがX、SecondがY

	//歩数をリセット
	node_step::reset_step(init_step);
	//目標座標を最初にキューにぶち込む
	for (int index = 0; index < finish.size();index++) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if ((i + j) % 2 != 0) {			//2倍座標系では区画の間は奇数にしかありえない
					temp = std::make_pair<uint8_t, uint8_t>(2 * finish.at(index).first + i, 2 * finish.at(index).second + j);
					if (set_step_double(temp, 0, by_known)) {
						que.push(temp);
						dir.push(std::make_pair<int8_t, int8_t>(static_cast<int8_t>(i - 1), static_cast<int8_t>(j - 1)));		//方向も記録
					}
				}
			}
		}
	}

	uint16_t step = 0;	//現在の歩数
	uint8_t x, y;	//2倍座標
	int8_t dir_x, dir_y = 0;		//現在の方向
	int8_t dir_size;		//規格化していないので、判定時に規格化するため

	//歩数の重みを管理
	uint8_t straight;
	uint8_t oblique;
	std::vector<uint8_t> straight_w;
	std::vector<uint8_t> oblique_w;
	std::vector<uint8_t> curve_w{0,0,0};

	static const std::vector<uint8_t> temp_s{ 21,20,19,18,17,16,9,4 };		//直進方向の重みづけ
	static const std::vector<uint8_t> temp_o{ 15,14,13,12,11,10,9,4 };		//斜め方向の重みづけ
	static const std::vector<uint8_t> temp_c{ 14, 10, 0 };		//カーブに関する重みづけ、90°,45°,0°の順番


	switch (get_weight_algo()) {
	case weight_algo::adachi:
		straight_w.emplace_back(1);
		oblique_w.emplace_back(1);
		break;

	case weight_algo::based_distance:
		straight_w.emplace_back(7);
		oblique_w.emplace_back(5);
		break;

	case weight_algo::T_Wataru_method:
		curve_w = temp_c;
	case weight_algo::priority_straight:
		straight_w = (temp_s);	//staright_wに代入
		oblique_w = (temp_o);	//oblique_wに代入
		break;

	}



	while (!que.empty()) {
		//キューから座標を取り出す
		temp = que.front();
		x = temp.first;
		y = temp.second;
		step = get_step_double(x, y);
		que.pop();	//取り出したので削除

		//キューから方向を取り出す
		dir_x = dir.front().first;
		dir_y = dir.front().second;
		dir.pop();	//取り出したので削除
		dir_size = dir_x*dir_x + dir_y*dir_y;		//おおきさを2乗で計算

					//斜め方向
		for (int dx = -1; dx <= 1;dx++) {
			for (int dy = -1; dy <= 1;dy++) {
				if (dx == 0 && dy == 0) {
					//自分の今いるところなので何もしない
				}else if ((dx + dy) % 2 == 0) {			//区画の間はXY合計が奇数なので、変化幅はXY軸合計して偶数でないとダメ
					if ((dx*dir_x + dy*dir_y) >= 0) {		//現在の方向に対して、0°、45°、90°の方向だけチェックすればよい　135°180°は負になる
						dir_size *= (dx*dx + dy*dy);	//内積相手のサイズも考慮する
						step += curve_w.at((dx*dir_x + dy*dir_y)*(dx*dir_x + dy*dir_y) * 2 / dir_size);;			//カーブすることに対する重みを足す	添え字は内積の2乗 2をかけているのは分数を整数にするため
						//その直線方向に、書き込めなくなるまで書き込んでいく
						for (int i = 0; ;i++) {
							//直線が続くと足していく歩数は小さくなっていく
							if (i < oblique_w.size())
								oblique = oblique_w.at(i);			//要素外に出る場合は値を更新しない＝最後の値が続く
							//歩数を書き込めたら、書き込んだ座標をQueueにぶっこむ
							if (set_step_double(x + dx * (i + 1), y + dy * (i + 1), step + oblique, by_known)) {
								step += oblique;		//ステップを更新
								que.push(std::make_pair<uint8_t, uint8_t>(x + (i + 1) * dx, y + (i + 1) * dy));
								dir.push(std::make_pair<int8_t, int8_t>(static_cast<int8_t>(dx), static_cast<int8_t>(dy)));		//方向も記録
							}
							else
								break;	//書き込めなくなったらループを抜ける
						}
						dir_size /= (dx*dx + dy*dy);	//内積相手のサイズは引いておく

					}
					step = get_step_double(x, y);		//ステップをリセット

				}
			}
		}
		//直進方向　Xが2の倍数（縦壁）のときはX方向にだけ±2がある　横壁のときはYだけに　 ※XY両方が偶数になることはないはず
		//その直線方向に、書き込めなくなるまで書き込んでいく
		for (int sign = -1; sign < 2; sign += 2) {
			int delta_x, delta_y;	//座標代入時の変数（見やすさのため）
			int dx = (1 - x % 2) * sign;		//方向管理用
			int dy = (1 - y % 2) * sign;		//方向管理用

			if ((dx*dir_x + dy*dir_y) >= 0) {		//現在の方向に対して、0°、45°、90°の方向だけチェックすればよい　135°180°は負になる
				dir_size *= (dx*dx + dy*dy);	//内積相手のサイズも考慮する
				step += curve_w.at((dx*dir_x + dy*dir_y)*(dx*dir_x + dy*dir_y) * 2 / dir_size);;			//カーブすることに対する重みを足す	添え字は内積の2乗 2をかけているのは分数を整数にするため

				for (int i = 0; ;i++) {
					//直線が続くと足していく歩数は小さくなっていく
					if (i < straight_w.size())
						straight = straight_w.at(i);			//要素外に出る場合は値を更新しない＝最後の値が続く

					delta_x = 2 * dx * (i + 1);
					delta_y = 2 * dy * (i + 1);
					//歩数を書き込めたら、書き込んだ座標をQueueにぶっこむ
					if (set_step_double(x + delta_x, y + delta_y, step + straight, by_known)) {
						step += straight;		//ステップを更新
						que.push(std::make_pair<uint8_t, uint8_t>(x + delta_x, y + delta_y));
						dir.push(std::make_pair<int8_t, int8_t>(static_cast<int8_t>(dx), static_cast<int8_t>(dy)));		//方向も記録
					}
					else
						break;	//書き込めなくなったらループを抜ける
				}
				dir_size /= (dx*dx + dy*dy);	//内積相手のサイズは引いておく

			}
			step = get_step_double(x, y);		//ステップをリセット
		}

	}

}

bool node_search::create_small_path(std::vector< std::pair<uint8_t, uint8_t> > finish, std::pair<uint8_t, uint8_t> init, compas mouse_direction) {
	//歩数マップ作製
	node_step::reset_step(init_step);
	spread_step(finish, true);		//ここは既知壁だけで歩数マップ作製
	return node_path::create_path(init, mouse_direction);		//歩数マップに従ってパス作製

}

bool node_search::create_big_path(std::vector< std::pair<uint8_t, uint8_t> > finish, std::pair<uint8_t, uint8_t> init, compas mouse_direction) {
	if (create_small_path(finish, init, mouse_direction)) {		//小回りパス作製
		node_path::improve_path();		//小回りを大回りパスに改良
		return true;
	}
	return false;
}

void node_search::reset_finish(){
	//目的地情報をすべてリセット
	for (int i = 0; i < MAZE_SIZE; i++) {
		x_finish[i].all = 0;
		y_finish[i].all = 0;
	}
}

void node_search::set_finish(std::pair<uint8_t, uint8_t> finish, compas dir){

}

node_search::node_search() {
	set_weight_algo(weight_algo::adachi);
	reset_finish();
}

node_search::node_search(uint16_t init_step) {
	node_step::reset_step(init_step);
	set_weight_algo(weight_algo::adachi);
	reset_finish();
}

node_search::~node_search() {
}


std::vector<path_element> node_path::path(1);

PATH node_path::to_PATH(path_element from){
	PATH ans;

	ans.element.flag = FALSE;

	ans.element.distance = from.distance;

	if (from.is_right)
		ans.element.muki = MUKI_RIGHT;
	else
		ans.element.muki = MUKI_LEFT;

	switch (from.turn)
	{
	case none:
		ans.element.flag = TRUE;	//最後の直進で終わりのパターン
	case small:
	case big_90:
	case big_180:
		ans.element.turn = from.turn;
		break;

	case begin_45:
	case end_45:
		ans.element.turn = 4;
		break;

	case begin_135:
	case end_135:
		ans.element.turn = 5;
		break;

	case oblique_90:
		ans.element.turn = 6;
		break;
	}

	return ans;

}

bool node_path::is_right_turn(compas now, compas next) {
	switch (now) {
	case north:
		if (next == east)
			return true;
		else
			return false;
		break;

	case south:
		if (next == west)
			return true;
		else
			return false;
		break;

	case east:
		if (next == south)
			return true;
		else
			return false;
		break;

	case west:
		if (next == north)
			return true;
		else
			return false;
		break;
	}
	return false;
}

void node_path::format() {
	std::vector<path_element>(1).swap(path);
}

void node_path::push_straight(int half) {
	(path.back()).distance += half;	//直線を増やす
}

void node_path::push_small_turn(bool is_right) {
	(path.back()).turn = small;		//種類は小回り
	(path.back()).is_right = is_right;	//右向き

	path_element temp;
	temp.distance = 0;
	temp.turn = none;
	path.emplace_back(temp);	//次の要素を作っておく

}

bool node_path::create_path(std::pair<uint8_t, uint8_t> init, compas mouse_direction) {
	node_path::format();				//パスを初期化
	node_path::push_straight(1);			//区画中心にいる想定なので半区間前進

										//向かっている方向の歩数が初期値なら、道が閉じているので終了
	uint16_t now_step = get_step(init.first, init.second, mouse_direction);
	if (now_step >= init_step)
		return false;

	//歩数の低い方へ下っていく
	compas now_compas = mouse_direction;
	uint8_t now_x = init.first;
	uint8_t now_y = init.second;
	int8_t dx, dy;
	uint16_t next_step = now_step;
	compas next_compas = now_compas;
	while (now_step != 0) {

		//次の方角へマスを移動　※区画外に出るとかは、歩数マップ作成時にはじかれてるはずと信じている
		switch (next_compas) {
		case north:
			//now_y += 1;
			dx = 0;
			dy = 1;
			break;
		case south:
			//now_y -= 1;
			dx = 0;
			dy = -1;
			break;
		case east:
			//now_x += 1;
			dx = 1;
			dy = 0;
			break;
		case west:
			//now_x -= 1;
			dx = -1;
			dy = 0;
			break;
		}
		now_x += dx;		//X座標更新
		now_y += dy;		//Y座標更新

		next_compas = get_min_compas(now_x, now_y);			//次に行く方角を決める
		next_step = get_step(now_x, now_y, next_compas);	//次に行く場所の歩数も取得

		if (now_step <= next_step)
			return false;		//今の歩数が次行くべき歩数と同じかそれ以下ということはあり得ないはずなので、とりあえず失敗しとく

								//パスを追加
		if (now_compas == next_compas)
			node_path::push_straight(2);	//今の向きと同じ方向に進むなら直進
		else //ターン以外の選択肢はないはず
			node_path::push_small_turn(is_right_turn(now_compas, next_compas));

		now_step = next_step;	//歩数を更新
		now_compas = next_compas;	//方角を更新

	}


	//次の方角の変化方向を取得
	switch (next_compas) {
	case north:
		//now_y += 1;
		dx = 0;
		dy = 1;
		break;
	case south:
		//now_y -= 1;
		dx = 0;
		dy = -1;
		break;
	case east:
		//now_x += 1;
		dx = 1;
		dy = 0;
		break;
	case west:
		//now_x -= 1;
		dx = -1;
		dy = 0;
		break;
	}

	//複数マスゴールの場合用に、0の続く限り直進
	while (1) {
		now_x += dx;		//X座標更新
		now_y += dy;		//Y座標更新

		if (get_step(now_x, now_y, next_compas) != 0) {	//ゴール外に出たら
			break;
		}
		else {									//ゴール区画がまだ続くなら
			node_path::push_straight(2);
		}

	}

	node_path::push_straight(1);		//区画に入りきるために半区画直進して終了
	return true;

}

void node_path::improve_path() {

	uint16_t count = 0;
	uint8_t temp_distance = 0;	//一時的な距離保存
	bool naname_flag = false;	//現在機体が斜めかを判断	ONなら斜め走行中
	uint16_t size = path.size();

	path.at(size - 1).distance -= 1;	//最後の区画の中心まで入り込むための半区間直進を消す。　こうしておかないと最後が大回りに丸め込まれて減速できなくなる可能性があるから

	while (count < path.size()) {		//pathが終われば終了
		if (naname_flag) {							//斜め走行中なら	確実に直進距離(distance)が0のはず

			if (get_path(count+1).element.distance >= 1) {			//次のターン後90mm以上直進(斜め終わり)
				path.at(count).turn=end_45;							//45°ターンに変更
				path.at(count + 1).distance -= 1;					//直線距離を90mm減らす
				naname_flag = false;
				count++;												//配列を次へ

			}
			else if (get_path(count + 2).element.distance >= 1) {	//次の次のターン後90mm以上直進(斜め終わり)

				if (path.at(count).is_right == path.at(count+1).is_right) {		//同じ方向の2回ターン
					path.at(count).turn = end_135;					//135°ターンに変更
					path.erase(path.begin() + count + 1);							//一個ずらす
					path.at(count + 1).distance -= 1;			//ターン後の直線距離を90mm減らす
					naname_flag = false;
					count++;										//配列を次へ

				}
				else {																//交互のターン(ギザギザ)
					path.at(count).distance += 1;				//斜めの直線距離を1増やす
					temp_distance = path.at(count).distance;	//距離を一時的に持っておく
					path.erase(path.begin() + count);							//一個ずらす
					path.at(count).distance = temp_distance;	//距離を入れなおす

				}

			}
			else {												//まだまだ斜めは続くなら
				if (count + 1 < size) {		//次のパスが存在する
					if (path.at(count + 1).turn == none) {
						//斜めの大回りで終わるパターン
						temp_distance = path.at(count).distance;	//距離を一時的に持っておく
						path.erase(path.begin() + count);							//一個ずらす
						path.at(count).distance = temp_distance;	//距離を入れなおす						count++;
						naname_flag = false;
					}
					else {
						if (path.at(count).is_right == path.at(count + 1).is_right) {		//同じ方向の2回ターン	コの字
							path.at(count).turn = oblique_90;					//斜め90°ターンに変更
							path.erase(path.begin() + count + 1);							//一個ずらす
							count++;										//配列を次へ
						}
						else {																//違う方向の2回ターン	ギザギザ
							path.at(count).distance += 1;				//斜めの直線距離を1増やす
							temp_distance = path.at(count).distance;	//距離を一時的に持っておく
							path.erase(path.begin() + count);							//一個ずらす
							path.at(count).distance = temp_distance;	//距離を入れなおす

						}
					}
				}
				else {																//TODO 斜めのままパスが終了する　とりあえず入りきらずに終了する
					//FIX_ME 斜めのまま終了するときの処理
					path.at(count).distance += 1;				//斜めの直線距離を1増やす
					path.at(count).turn = none;
					count = size;	//終了
				}
			}

		}
		else {										//斜めじゃなければ

			if (count + 1 < size) {	//count+1でもパスが終わらないなら

				if (path.at(count + 1).distance >= 1) {		//ターン後も90mm以上直進するなら	大回りのチェックを行う

					if ((count != 0) || (path.at(0).distance > 1)) {		//初っ端のターンじゃなければ
						path.at(count).turn = big_90;					//大回りターンに変更
						path.at(count).distance -= 1;				//直線距離を90mm減らす
						path.at(count + 1).distance -= 1;			//直線距離を90mm減らす

					}

				}
				else {											//ターン後90mm直進はしないなら

					if (path.at(count).is_right == path.at(count + 1).is_right) {	//同じ方向に曲がるなら(Uターン)
						if (count + 2 < size) {			//2つ先までパスが存在するなら
							if (path.at(count + 2).distance >= 1) {		//Uターン後90mm直進するなら
								path.at(count).turn = big_180;					//180°ターンに変更
								path.at(count).distance -= 1;				//直線距離を90mm減らす
								path.at(count + 2).distance -= 1;			//直線距離を90mm減らす
								path.erase(path.begin() + count + 1);		//一個ずらす

							}
							else {											//Uターン後すぐ曲がるなら
								path.at(count).turn = begin_135;					//135°ターンに変更
								path.at(count).distance -= 1;				//直線距離を90mm減らす
								path.erase(path.begin()+ count + 1);							//一個ずらす
								naname_flag = true;

							}

						}
					}
					else {		//違う方法に曲がるなら
						path.at(count).turn = begin_45;							//45°ターンに変更
						path.at(count).distance -= 1;						//直線距離を90mm減らす
						naname_flag = true;

					}


				}
			}
			count++;		//配列を次へ
		}

		size = path.size();		//sizeを更新

	}

	//最初に1つ削ったから忘れず足しておく
	if(naname_flag)
		path.at(size - 1).distance -= 1;
	else
		path.at(size - 1).distance += 1;

}



PATH node_path::get_path(uint16_t index) {
	if (path.size() <= index) {		//要素外アクセス禁止
		path_element temp;
		temp.distance = 0;
		temp.turn = none;
		PATH ans = to_PATH(temp);
		ans.element.flag = TRUE;
		return ans;
	}
	path_element tar = path.at(index);
	if ((tar.distance == 0) && (tar.turn == none)) {
		//path.erase(path.begin() + index);		//直進なしかつターンなしの場合（起こりうるのは末尾だけのはず）いらないので削除
		return get_path(index+1);
	}
	return to_PATH(tar);

}


node_path::node_path() {
	format();
}

node_path::~node_path() {

}

