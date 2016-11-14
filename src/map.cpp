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
	uint8_t want_next_turn = 0;
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
		myprintf("distance -> %d \n\r", path_memory[i].element.distance);
		myprintf("turn -> %d ", path_memory[i].element.turn);
		if (path_memory[i].element.muki == MUKI_RIGHT) {
			myprintf("R\n\r");
		} else if (path_memory[i].element.muki == MUKI_LEFT) {
			myprintf("L\n\r");
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
