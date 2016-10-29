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

//target_wall��edit_number�ڂ�set_number��������֐�
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
	unsigned char maze_check = 0;		//��FALSE

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

	//x���W������ύX����Ƃ�
	if ((muki == MUKI_RIGHT) || (muki == MUKI_LEFT)) {
		if (muki == MUKI_RIGHT) {
		} else if (muki == MUKI_LEFT) {
			if (wall_x == 0) {		//��ԍ��ǂ͊Ǘ����Ȃ�
				return;
			} else {
				set_x = wall_x - 1;	//�K���E�ǂ��X�V����悤�ɁA���W��ς���
			}
		}
		if (set_x < MAZE_SIZE) {
			set_maze_wall(&x_wall_exist[set_y], set_x, true);//x_maze_wall[y]��x�Ԗڂ̉E�ǂ�1����
		} else {		//�K�؂łȂ��l�������Ă�
			mouse::error();
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("���݂��Ȃ�x���W�ɕǂ̑��݂���낤�Ƃ��Ă��܂�\n\r");
			myprintf("remember_exist�֐���\n\r");
		}

		//y���W������ύX����Ƃ�
	} else if ((muki == MUKI_UP) || (muki == MUKI_DOWN)) {
		if (muki == MUKI_UP) {
		} else if (muki == MUKI_DOWN) {
			if (wall_y == 0) {		//��ԉ��ǂ͊Ǘ����Ȃ�
				return;
			} else {
				set_y = wall_y - 1;	//�K����ǂ��X�V����悤�ɁA���W��ς���
			}
		}
		if (set_y < MAZE_SIZE) {
			set_maze_wall(&y_wall_exist[set_x], set_y, true);//x_maze_wall[y]��x�Ԗڂ̉E�ǂ�1����
		} else {		//�K�؂łȂ��l�������Ă�
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("���݂��Ȃ�y���W�ɕǂ̑��݂���낤�Ƃ��Ă��܂�\n\r");
			myprintf("remember_exist�֐���\n\r");
		}

	}

}
void map::forget_exist(unsigned char wall_x, unsigned char wall_y,
		unsigned char muki) {
	unsigned char set_x = wall_x, set_y = wall_y;

	//x���W������ύX����Ƃ�
	if ((muki == MUKI_RIGHT) || (muki == MUKI_LEFT)) {
		if (muki == MUKI_RIGHT) {
		} else if (muki == MUKI_LEFT) {
			if (wall_x == 0) {		//��ԍ��ǂ͊Ǘ����Ȃ�
				return;
			} else {
				set_x = wall_x - 1;	//�K���E�ǂ��X�V����悤�ɁA���W��ς���
			}
		}
		if (set_x < MAZE_SIZE) {
			set_maze_wall(&x_wall_exist[set_y], set_x, false);//x_maze_wall[y]��x�Ԗڂ̉E�ǂ�false����
		} else {		//�K�؂łȂ��l�������Ă�
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("���݂��Ȃ�x���W�̕ǂ̑��݂��������Ƃ��Ă��܂�\n\r");
			myprintf("forget_exist�֐���\n\r");
		}

		//y���W������ύX����Ƃ�
	} else if ((muki == MUKI_UP) || (muki == MUKI_DOWN)) {
		if (muki == MUKI_UP) {
		} else if (muki == MUKI_DOWN) {
			if (wall_y == 0) {		//��ԉ��ǂ͊Ǘ����Ȃ�
				return;
			} else {
				set_y = wall_y - 1;	//�K����ǂ��X�V����悤�ɁA���W��ς���
			}
		}
		if (set_y < MAZE_SIZE) {
			set_maze_wall(&y_wall_exist[set_x], set_y, false);//x_maze_wall[y]��x�Ԗڂ̏�ǂ�1false���
		} else {		//�K�؂łȂ��l�������Ă�
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("���݂��Ȃ�y���W�̕ǂ̑��݂��������Ƃ��Ă��܂�\n\r");
			myprintf("forget_exist�֐���\n\r");
		}

	}

}
bool map::check_exist(unsigned char wall_x, unsigned char wall_y,
		unsigned char muki) {
	unsigned char target_x = wall_x, target_y = wall_y;

	//x���W���������邷��Ƃ�
	if ((muki == MUKI_RIGHT) || (muki == MUKI_LEFT)) {
		if (muki == MUKI_RIGHT) {
		} else if (muki == MUKI_LEFT) {
			if (wall_x == 0) {		//��ԍ��ǂ͊Ǘ����Ȃ�
				return true;
			} else {
				target_x = wall_x - 1;	//�K���E�ǂ�����悤�ɁA���W��ς���
			}
		}
		if (target_x < MAZE_SIZE) {
			return get_maze_wall(x_wall_exist[target_y], target_x);
		} else {		//�K�؂łȂ��l�������Ă�
			mouse::error();
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("���݂��Ȃ�x���W�̕ǂ̑��݂�ǂ����Ƃ��Ă��܂�\n\r");
			myprintf("check_exist�֐���\n\r");
			return -1;
		}

		//y���W������ύX����Ƃ�
	} else if ((muki == MUKI_UP) || (muki == MUKI_DOWN)) {
		if (muki == MUKI_UP) {
		} else if (muki == MUKI_DOWN) {
			if (wall_y == 0) {		//��ԉ��ǂ͏�ɕǂ�����
				return true;
			} else {
				target_y = wall_y - 1;	//�K����ǂ��X�V����悤�ɁA���W��ς���
			}
		}
		if (target_y < MAZE_SIZE) {
			return get_maze_wall(y_wall_exist[target_x], target_y);
		} else {		//�K�؂łȂ��l�������Ă�
			mouse::error();
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("���݂��Ȃ�y���W�̕ǂ̑��݂�ǂ����Ƃ��Ă��܂�\n\r");
			myprintf("check_exist�֐���\n\r");
			return -1;
		}
	}

	return false;
}

void map::create_wall(unsigned char wall_x, unsigned char wall_y,
		unsigned char muki) {
	unsigned char set_x = wall_x, set_y = wall_y;

	//x���W������ύX����Ƃ�
	if ((muki == MUKI_RIGHT) || (muki == MUKI_LEFT)) {
		if (muki == MUKI_RIGHT) {
		} else if (muki == MUKI_LEFT) {
			if (wall_x == 0) {		//��ԍ��ǂ͊Ǘ����Ȃ�
				return;
			} else {
				set_x = wall_x - 1;	//�K���E�ǂ��X�V����悤�ɁA���W��ς���
			}
		}
		if (set_x < MAZE_SIZE) {
			set_maze_wall(&x_maze_wall[set_y], set_x, true);//x_maze_wall[y]��x�Ԗڂ̉E�ǂ�1����
		} else {		//�K�؂łȂ��l�������Ă�
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("���݂��Ȃ�x���W�ɕǂ���낤�Ƃ��Ă��܂�\n\r");
			myprintf("create_wall�֐���\n\r");
		}

		//y���W������ύX����Ƃ�
	} else if ((muki == MUKI_UP) || (muki == MUKI_DOWN)) {
		if (muki == MUKI_UP) {
		} else if (muki == MUKI_DOWN) {
			if (wall_y == 0) {		//��ԉ��ǂ͊Ǘ����Ȃ�
				return;
			} else {
				set_y = wall_y - 1;	//�K����ǂ��X�V����悤�ɁA���W��ς���
			}
		}
		if (set_y < MAZE_SIZE) {
			set_maze_wall(&y_maze_wall[set_x], set_y, true);//x_maze_wall[y]��x�Ԗڂ̉E�ǂ�1����
		} else {		//�K�؂łȂ��l�������Ă�
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("���݂��Ȃ�y���W�ɕǂ���낤�Ƃ��Ă��܂�\n\r");
			myprintf("create_wall�֐���\n\r");
		}

	}

}
void map::destroy_wall(unsigned char wall_x, unsigned char wall_y,
		unsigned char muki) {
	unsigned char set_x = wall_x, set_y = wall_y;

	//x���W������ύX����Ƃ�
	if ((muki == MUKI_RIGHT) || (muki == MUKI_LEFT)) {
		if (muki == MUKI_RIGHT) {
		} else if (muki == MUKI_LEFT) {
			if (wall_x == 0) {		//��ԍ��ǂ͊Ǘ����Ȃ�
				return;
			} else {
				set_x = wall_x - 1;	//�K���E�ǂ��X�V����悤�ɁA���W��ς���
			}
		}
		if (set_x < MAZE_SIZE) {
			set_maze_wall(&x_maze_wall[set_y], set_x, false);//x_maze_wall[y]��x�Ԗڂ̉E�ǂ�false����
		} else {		//�K�؂łȂ��l�������Ă�
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("���݂��Ȃ�x���W�ɕǂ���낤�Ƃ��Ă��܂�\n\r");
			myprintf("destroy_wall�֐���\n\r");
		}

		//y���W������ύX����Ƃ�
	} else if ((muki == MUKI_UP) || (muki == MUKI_DOWN)) {
		if (muki == MUKI_UP) {
		} else if (muki == MUKI_DOWN) {
			if (wall_y == 0) {		//��ԉ��ǂ͊Ǘ����Ȃ�
				return;
			} else {
				set_y = wall_y - 1;	//�K����ǂ��X�V����悤�ɁA���W��ς���
			}
		}
		if (set_y < MAZE_SIZE) {
			set_maze_wall(&y_maze_wall[set_x], set_y, false);//x_maze_wall[y]��x�Ԗڂ̏�ǂ�1false���
		} else {		//�K�؂łȂ��l�������Ă�
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("���݂��Ȃ�y���W�ɕǂ���낤�Ƃ��Ă��܂�\n\r");
			myprintf("destroy_wall�֐���\n\r");
		}

	}

}
bool map::get_wall(unsigned char wall_x, unsigned char wall_y,
		unsigned char muki) {
	unsigned char target_x = wall_x, target_y = wall_y;

	//x���W���������邷��Ƃ�
	if ((muki == MUKI_RIGHT) || (muki == MUKI_LEFT)) {
		if (muki == MUKI_RIGHT) {
		} else if (muki == MUKI_LEFT) {
			if (wall_x == 0) {		//��ԍ��ǂ͊Ǘ����Ȃ�
				return true;
			} else {
				target_x = wall_x - 1;	//�K���E�ǂ�����悤�ɁA���W��ς���
			}
		}
		if (target_x < MAZE_SIZE) {
			return get_maze_wall(x_maze_wall[target_y], target_x);
		} else {		//�K�؂łȂ��l�������Ă�
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("���݂��Ȃ�x���W�̕ǂ�ǂ����Ƃ��Ă��܂�\n\r");
			myprintf("get_wall�֐���\n\r");
			return -1;
		}

		//y���W������ύX����Ƃ�
	} else if ((muki == MUKI_UP) || (muki == MUKI_DOWN)) {
		if (muki == MUKI_UP) {
		} else if (muki == MUKI_DOWN) {
			if (wall_y == 0) {		//��ԉ��ǂ͏�ɕǂ�����
				return true;
			} else {
				target_y = wall_y - 1;	//�K����ǂ��X�V����悤�ɁA���W��ς���
			}
		}
		if (target_y < MAZE_SIZE) {
			return get_maze_wall(y_maze_wall[target_x], target_y);
		} else {		//�K�؂łȂ��l�������Ă�
			myprintf("\n\r!!!ERROR!!!\n\r");
			myprintf("���݂��Ȃ�y���W�̕ǂ�ǂ����Ƃ��Ă��܂�\n\r");
			myprintf("get_wall�֐���\n\r");
			return -1;
		}
	}

	return false;
}

void map::reset_wall() {
	//�ǂ�����
	for (int i = 0; i < MAZE_SIZE; i++) {
		x_maze_wall[i].all = 0;
		y_maze_wall[i].all = 0;
		x_wall_exist[i].all = 0;
		y_wall_exist[i].all = 0;
	}
	//�O�ǂ͓����
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
	//(0�C0)�͂킩���Ă�
	create_wall(0, 0, MUKI_RIGHT);
	remember_exist(0, 0, MUKI_RIGHT);
	destroy_wall(0, 0, MUKI_UP);
	remember_exist(0, 0, MUKI_UP);
}

void map::draw_map() {
	signed char tekitou_x = 0, tekitou_y = MAZE_SIZE - 1;

	myprintf("\n-----start draw_map-------\n\r");

	//���
	for (tekitou_x = 0; tekitou_x < MAZE_SIZE; tekitou_x++)
		myprintf("+---");
	myprintf("+\n\r");

	myprintf("|");	//���[�̕�
	for (tekitou_x = 0; tekitou_x < MAZE_SIZE - 1; tekitou_x++) {

		//myprintf("%3d", step[tekitou_x][tekitou_y]);
		myprintf("   ");

		if ((get_wall(tekitou_x, tekitou_y, MUKI_RIGHT) == true)
				|| (get_wall(tekitou_x + 1, tekitou_y, MUKI_LEFT) == true)) {//���������}�X�̉E�̕ǂ�����Εǂ�����
			myprintf("|");
		} else {
			myprintf(" ");	//�Ȃ���Εǂ͏����Ȃ�
		}
	}

	//myprintf("%3d", step[tekitou_x][tekitou_y]);
	myprintf("   ");

	myprintf("|\n\r");	//�E�[�̕�

	for (tekitou_y = MAZE_SIZE - 2; tekitou_y >= 0; tekitou_y--) {
		//////////////////////////////////////////���H�̕ǂ̍s
		for (tekitou_x = 0; tekitou_x < MAZE_SIZE; tekitou_x++) {
			myprintf("+");	//��
			if ((get_wall(tekitou_x, tekitou_y, MUKI_UP) == true)
					|| (get_wall(tekitou_x, tekitou_y + 1, MUKI_DOWN) == true)) {//�ǂ�����Ȃ�
				myprintf("---");
			} else {
				myprintf("   ");
			}
		}
		myprintf("+\n\r");

		/////////////////////////////////////////���H�̃}�X�ڂ̍s
		myprintf("|");	//���[�̕�
		for (tekitou_x = 0; tekitou_x < MAZE_SIZE - 1; tekitou_x++) {

			//myprintf("%3d", step[tekitou_x][tekitou_y]);
			myprintf("   ");

			if ((get_wall(tekitou_x, tekitou_y, MUKI_RIGHT) == true)
					|| (get_wall(tekitou_x + 1, tekitou_y, MUKI_LEFT) == true)) {//���������}�X�̉E�̕ǂ�����Εǂ�����
				myprintf("|");
			} else {
				myprintf(" ");	//�Ȃ���Εǂ͏����Ȃ�
			}
		}
		//myprintf("%3d", step[tekitou_x][tekitou_y]);
		myprintf("   ");

		myprintf("|\n\r");	//�E�[�̕�
	}

	//����
	for (tekitou_x = 0; tekitou_x < MAZE_SIZE; tekitou_x++)
		myprintf("+---");
	myprintf("+\n\r");

}

/*
 void map::convert_mapdata(unsigned char (*hiramatu_data)[16]){
 for(char x=0;x<16;x++){
 for(char y=0;y<16;y++){
 if((hiramatu_data[x][y] & 2) == 2){		//���ǂ������
 create_wall(x,y,MUKI_RIGHT);
 }else{
 destroy_wall(x,y,MUKI_RIGHT);
 }
 if((hiramatu_data[x][y] & 1) == 1){		//��ǂ������
 create_wall(x,y,MUKI_UP);
 }else{
 destroy_wall(x,y,MUKI_UP);
 }
 }
 }
 }
 */

void map::input_map_data(const MAP_DATA *input_data) {
	//�f�[�^����
	for (int i = 0; i < MAZE_SIZE; i++) {
		x_maze_wall[i].all = input_data->x_wall[i].all;
		y_maze_wall[i].all = input_data->y_wall[i].all;
		x_wall_exist[i].all = input_data->x_known[i].all;
		y_wall_exist[i].all = input_data->y_known[i].all;
	}
}

void map::output_map_data(MAP_DATA* const output_data) {
	//�f�[�^�o��
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
	//���W���Ǘ����邽�߂̔z��
	unsigned char x_coordinate[965] = { 0 };
	unsigned char y_coordinate[965] = { 0 };

	unsigned char x_count = 0, y_count = 0;	//�ꎞ�I�ɍ��W�������Ƃ��悤
	unsigned char head, tail;		//

	step_reset();
	maze_step[target_x][target_y] = 0;

	//coordinate  [tail][][][] -> [][][head]

	head = 1;
	tail = 0;

	//Q�̍ŏ��ɂ͖ڕW�̍��W�����Ƃ�
	x_coordinate[tail] = target_x;
	y_coordinate[tail] = target_y;

	while (head != tail) {
		//���W����
		x_count = x_coordinate[tail];
		y_count = y_coordinate[tail];

		tail++;

		//���}�X
		if ((x_count - 1) >= 0) {		//���W�����H��(x-1��0�ȏ�)�ɂ���
			if ((maze_step[x_count - 1][y_count] == STEP_INIT)) {//���������ĂȂ��i�����Ă������STEP_INIT�j
				if (map::get_wall(x_count, y_count, MUKI_LEFT) == false) {//���̃}�X�̍��ǂ��Ȃ��Ȃ�
					maze_step[x_count - 1][y_count] =
							maze_step[x_count][y_count] + 1;		//��������
					//���̍��W��ێ�
					x_coordinate[head] = (x_count - 1);
					y_coordinate[head] = y_count;
					head++;
				}
			}
		}

		//�E�}�X
		if ((x_count + 1) < MAZE_SIZE) {	//���W�����H��(x+1��MAZE_SIZE����)�ɂ���
			if ((maze_step[x_count + 1][y_count] == STEP_INIT)) {//���������ĂȂ��i�����Ă������STEP_INIT�j
				if (map::get_wall(x_count, y_count, MUKI_RIGHT) == false) {	//���̃}�X�̉E�ǂ��Ȃ�
					maze_step[x_count + 1][y_count] =
							maze_step[x_count][y_count] + 1;	//��������
					//���̍��W��ێ�
					x_coordinate[head] = (x_count + 1);
					y_coordinate[head] = y_count;
					head++;
				}
			}
		}

		//���}�X
		if ((y_count - 1) >= 0) {		//���W�����H��(y-1��0�ȏ�)�ɂ���
			if ((maze_step[x_count][y_count - 1] == STEP_INIT)) {//���������ĂȂ��i�����Ă������STEP_INIT�j
				if (map::get_wall(x_count, y_count, MUKI_DOWN) == false) {//���̃}�X�̉��ǂ��Ȃ�
					maze_step[x_count][y_count - 1] =
							maze_step[x_count][y_count] + 1;	//��������
					//���̍��W��ێ�
					x_coordinate[head] = x_count;
					y_coordinate[head] = (y_count - 1);
					head++;
				}
			}
		}

		//��}�X
		if ((y_count + 1) < MAZE_SIZE) {	//x,y+1�̍��W�����H��(MAZE_SIZE����)�ł���
			if ((maze_step[x_count][y_count + 1] == STEP_INIT)) {//���������ĂȂ��i�����Ă������STEP_INIT�j
				if (map::get_wall(x_count, y_count, MUKI_UP) == false) {//���̃}�X�̏�ǂ��Ȃ�
					maze_step[x_count][y_count + 1] =
							maze_step[x_count][y_count] + 1;	//��������
					//���̍��W��ێ�
					x_coordinate[head] = x_count;
					y_coordinate[head] = (y_count + 1);
					head++;
				}
			}
		}

		if (head > 965) {		//�z��z������G���[
			myprintf("�G���[!\n\radachi::set_step()��\n\r");
			break;
		}

	}

}

void step::set_step_by_known(unsigned char target_x, unsigned char target_y) {
	//���W���Ǘ����邽�߂̔z��
	unsigned char x_coordinate[965] = { 0 };
	unsigned char y_coordinate[965] = { 0 };

	unsigned char x_count = 0, y_count = 0;	//�ꎞ�I�ɍ��W�������Ƃ��悤
	unsigned char head, tail;		//

	step_reset();
	maze_step[target_x][target_y] = 0;

	//coordinate  [tail][][][] -> [][][head]

	head = 1;
	tail = 0;

	//Q�̍ŏ��ɂ͖ڕW�̍��W�����Ƃ�
	x_coordinate[tail] = target_x;
	y_coordinate[tail] = target_y;

	while (head != tail) {
		//���W����
		x_count = x_coordinate[tail];
		y_count = y_coordinate[tail];

		tail++;

		//���}�X
		if ((x_count - 1) >= 0) {		//���W�����H��(x-1��0�ȏ�)�ɂ���
			if ((maze_step[x_count - 1][y_count] == STEP_INIT)) {//���������ĂȂ��i�����Ă������STEP_INIT�j
				if (map::get_wall(x_count, y_count, MUKI_LEFT) == false) {//���̃}�X�̍��ǂ��Ȃ��Ȃ�
					if (map::check_exist(x_count, y_count,
					MUKI_LEFT)) {		//���ǂ����Ă���Ȃ�
						maze_step[x_count - 1][y_count] =
								maze_step[x_count][y_count] + 1;		//��������
						//���̍��W��ێ�
						x_coordinate[head] = (x_count - 1);
						y_coordinate[head] = y_count;
						head++;
					}
				}
			}
		}

		//�E�}�X
		if ((x_count + 1) < MAZE_SIZE) {	//���W�����H��(x+1��MAZE_SIZE����)�ɂ���
			if ((maze_step[x_count + 1][y_count] == STEP_INIT)) {//���������ĂȂ��i�����Ă������STEP_INIT�j
				if (map::get_wall(x_count, y_count, MUKI_RIGHT) == false) {	//���̃}�X�̉E�ǂ��Ȃ�
					if (map::check_exist(x_count, y_count,
					MUKI_RIGHT)) {	//�E�ǂ����Ă���Ȃ�
						maze_step[x_count + 1][y_count] =
								maze_step[x_count][y_count] + 1;	//��������
						//���̍��W��ێ�
						x_coordinate[head] = (x_count + 1);
						y_coordinate[head] = y_count;
						head++;
					}
				}
			}
		}

		//���}�X
		if ((y_count - 1) >= 0) {		//���W�����H��(y-1��0�ȏ�)�ɂ���
			if ((maze_step[x_count][y_count - 1] == STEP_INIT)) {//���������ĂȂ��i�����Ă������STEP_INIT�j
				if (map::get_wall(x_count, y_count, MUKI_DOWN) == false) {//���̃}�X�̉��ǂ��Ȃ�
					if (map::check_exist(x_count, y_count,
					MUKI_DOWN)) {		//���ǂ����m�Ȃ�
						maze_step[x_count][y_count - 1] =
								maze_step[x_count][y_count] + 1;	//��������
						//���̍��W��ێ�
						x_coordinate[head] = x_count;
						y_coordinate[head] = (y_count - 1);
						head++;
					}
				}
			}
		}

		//��}�X
		if ((y_count + 1) < MAZE_SIZE) {	//x,y+1�̍��W�����H��(MAZE_SIZE����)�ł���
			if ((maze_step[x_count][y_count + 1] == STEP_INIT)) {//���������ĂȂ��i�����Ă������STEP_INIT�j
				if (map::get_wall(x_count, y_count, MUKI_UP) == false) {//���̃}�X�̏�ǂ��Ȃ�
					if (map::check_exist(x_count, y_count,
					MUKI_UP)) {		//��ǂ����m�Ȃ�
						maze_step[x_count][y_count + 1] =
								maze_step[x_count][y_count] + 1;	//��������
						//���̍��W��ێ�
						x_coordinate[head] = x_count;
						y_coordinate[head] = (y_count + 1);
						head++;
					}
				}
			}
		}

		if (head > 965) {		//�z��z������G���[
			myprintf("�G���[!\n\radachi::set_step()��\n\r");
			break;
		}

	}

}

unsigned int step::get_step(unsigned char target_x, unsigned char target_y) {
	return maze_step[target_x][target_y];
}

void step::close_one_dead_end(unsigned char target_x, unsigned char target_y) {
	union {
		unsigned char all;				//�ꊇ
		struct {
			unsigned char count :4;		//		�s���Ȃ������̌�
			unsigned char up :1;		//��	x=0,y=1�̕���
			unsigned char down :1;		//��	x=0,y=-1�̕���
			unsigned char left :1;		//��	x=-1,y=0�̕���
			unsigned char right :1;		//��	x=1,y=0�̕���
		} direction;
	} dead_end;

	dead_end.all = 0;	//������

	//���}�X
	if ((map::get_wall(target_x, target_y, MUKI_LEFT))) {	//���ǂ�����Ȃ�
		dead_end.direction.left = 1;	//���t���O�����Ă�
		dead_end.direction.count++;		//1����
	} else if ((target_x - 1) >= 0) {		//���W�����H��(x-1��0�ȏ�)�ɂ���
		if ((maze_step[target_x - 1][target_y] == STEP_INIT)
				|| (map::check_exist(target_x, target_y, MUKI_LEFT) == false)) {//���̃}�X�ɍs���Ȃ��i�����Ă������255 �܂��� �j
			dead_end.direction.left = 1;	//���t���O�I��
			dead_end.direction.count++;		//1����
		}
	}

	//�E�}�X
	if ((map::get_wall(target_x, target_y, MUKI_RIGHT))) {	//�E�ǂ�����Ȃ�
		dead_end.direction.right = 1;		//�E�t���O�����Ă�
		dead_end.direction.count++;			//1����
	} else if ((target_x + 1) < MAZE_SIZE) {	//���W�����H��(x+1��Max_x����)�ɂ���
		if ((maze_step[target_x + 1][target_y] == STEP_INIT)
				|| (map::check_exist(target_x, target_y, MUKI_RIGHT) == false)) {//�E�̃}�X�ɍs���Ȃ��i�����Ă������255 �܂��� �ǂ�����j
			dead_end.direction.right = 1;	//�E�t���O�����Ă�
			dead_end.direction.count++;		//1����
		}
	}

	//���}�X
	if ((map::get_wall(target_x, target_y, MUKI_DOWN))) {	//���ǂ�����Ȃ�
		dead_end.direction.down = 1;		//���t���O�����Ă�
		dead_end.direction.count++;			//1����
	} else if ((target_y - 1 >= 0)) {		//���W�����H��(y-1��0�ȏ�)�ɂ���
		if ((maze_step[target_x][target_y - 1] == STEP_INIT)
				|| (map::check_exist(target_x, target_y, MUKI_DOWN) == false)) {//���̃}�X�ɍs���Ȃ��i�����Ă������255 �܂��� �ǂ�����j
			dead_end.direction.down = 1;	//���t���O�����Ă�
			dead_end.direction.count++;		//1����
		}
	}

	//��}�X
	if ((map::get_wall(target_x, target_y, MUKI_UP))) {		//��ǂ�����Ȃ�
		dead_end.direction.up = 1;			//��t���O�����Ă�
		dead_end.direction.count++;			//1����
	} else if ((target_y + 1 < MAZE_SIZE)) {	//x,y+1�̍��W�����H��(MAX_y����)�ł���
		if ((maze_step[target_x][target_y + 1] == STEP_INIT)
				|| (map::check_exist(target_x, target_y, MUKI_UP) == false)) {//��̃}�X�ɍs���Ȃ��i�����Ă������255�@�܂��́@�ǂ�����j
			dead_end.direction.up = 1;		//��t���O�����Ă�
			dead_end.direction.count++;		//1����
		}
	}

	//�܏��H���ӂ���
	if (dead_end.direction.count >= 3) {		//�s���Ȃ�������3�ȏ� = �܏��H�Ȃ�
		if ((target_x == 0) && (target_y == 0)) {		//���ꂪ�X�^�[�g�Ȃ牽�����Ȃ�
		} else if ((target_x == GOAL_x) && (target_y == GOAL_y)) {//���ꂪ�S�[���ł��������Ȃ�
		} else {							//��L�ȊO�Ȃ�܏��H��ׂ�
			maze_step[target_x][target_y] = STEP_INIT;	//������������
			//�܏��H�̂����Ă�����ɂ��Ă�����񓯂����Ƃ��s��
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
/*
PATH path::path_memory[PATH_MAX];

void path::set_step_for_shortest(unsigned char target_x,
		unsigned char target_y) {
	set_step_by_known(target_x, target_y);		//���m�̕ǂ����ŕ����}�b�v���쐬
	close_dead_end();							//�܏��H��ׂ�
}

void path::displace_path(unsigned int path_number) {
	//1���炷
	for (unsigned int number = path_number;
			path_memory[number].element.flag == FALSE; number++) {
		path_memory[number].all = path_memory[number + 1].all;
	}
}

void path::improve_path() {
	unsigned int count = 0;

	while (path_memory[count].element.flag == FALSE) {		//path���I���ΏI��

		if (path_memory[count].element.distance >= 1) {		//90mm�ȏ㒼�i����Ȃ�

			if (path_memory[count + 1].element.distance >= 1) {	//�^�[�����90mm�ȏ㒼�i����Ȃ�	����̃`�F�b�N���s��
				path_memory[count].element.turn = 2;				//����^�[���ɕύX
				path_memory[count].element.distance -= 1;		//����������90mm���炷
				path_memory[count + 1].element.distance -= 1;	//����������90mm���炷

			} else {										//�^�[����90mm���i�͂��Ȃ��Ȃ�

				if (path_memory[count].element.muki
						== path_memory[count + 1].element.muki) {//���������ɋȂ���Ȃ�(U�^�[��)

					if (path_memory[count + 2].element.distance >= 1) {	//U�^�[����90mm���i����Ȃ�
						path_memory[count].element.turn = 3;		//180���^�[���ɕύX
						path_memory[count].element.distance -= 1;//����������90mm���炷
						path_memory[count + 2].element.distance -= 1;//����������90mm���炷

						//1���炷
						displace_path(count + 1);

					} else {									//U�^�[���シ���Ȃ���Ȃ�

						if (path_memory[count + 2].element.flag == FALSE) {	//path���I����ĂȂ����`�F�b�N�@�I����ĂȂ���΋t�����Ƀ^�[���̂͂�
							//�i�i���̏����Ȃ̂ŉ������Ȃ�
						}

					}

				} else {		//�Ⴄ���@�ɋȂ���Ȃ�
					//�i�i���̏����Ȃ̂ŉ������Ȃ�
				}

			}

		}

		count++;
	}

}

void path::improve_advance_path() {
	unsigned int count = 0;
	unsigned char temp_distance = 0;	//�ꎞ�I�ȋ����ۑ�
	unsigned char naname_flag = FALSE;	//���݋@�̂��΂߂��𔻒f	ON�Ȃ�΂ߑ��s��

	while (path_memory[count].element.flag == FALSE) {		//path���I���ΏI��

		if (naname_flag == TRUE) {			//�΂ߑ��s���Ȃ�	�m���ɒ��i����(distance)��0�̂͂�

			if (path_memory[count + 1].element.distance >= 1) {	//���̃^�[����90mm�ȏ㒼�i(�΂ߏI���)

				path_memory[count].element.turn = 4;				//45���^�[���ɕύX
				path_memory[count + 1].element.distance -= 1;	//����������90mm���炷
				naname_flag = FALSE;
				count++;												//�z�������

			} else if (path_memory[count + 2].element.distance >= 1) {//���̎��̃^�[����90mm�ȏ㒼�i(�΂ߏI���)

				if (path_memory[count].element.muki
						== path_memory[count + 1].element.muki) {	//����������2��^�[��

					path_memory[count].element.turn = 5;			//135���^�[���ɕύX
					displace_path(count + 1);							//����炷
					path_memory[count + 1].element.distance -= 1;//�^�[����̒���������90mm���炷
					naname_flag = FALSE;
					count++;										//�z�������

				} else {										//���݂̃^�[��(�M�U�M�U)

					path_memory[count].element.distance += 1;	//�΂߂̒���������1���₷
					temp_distance = path_memory[count].element.distance;//�������ꎞ�I�Ɏ����Ă���
					displace_path(count);							//����炷
					path_memory[count].element.distance = temp_distance;//���������Ȃ���

				}

			} else {											//�܂��܂��΂߂͑����Ȃ�

				if (path_memory[count].element.muki
						== path_memory[count + 1].element.muki) {//����������2��^�[��	�R�̎�

					path_memory[count].element.turn = 6;		//�΂�90���^�[���ɕύX
					displace_path(count + 1);							//����炷
					count++;										//�z�������

				} else {									//�Ⴄ������2��^�[��	�M�U�M�U

					path_memory[count].element.distance += 1;	//�΂߂̒���������1���₷
					temp_distance = path_memory[count].element.distance;//�������ꎞ�I�Ɏ����Ă���
					displace_path(count);							//����炷
					path_memory[count].element.distance = temp_distance;//���������Ȃ���

				}
			}

		} else {										//�΂߂���Ȃ����

			if (path_memory[count + 1].element.distance >= 1) {	//�^�[�����90mm�ȏ㒼�i����Ȃ�	����̃`�F�b�N���s��

				if ((count != 0) || (path_memory[0].element.distance > 1)) {//�����[�̃^�[������Ȃ����

					path_memory[count].element.turn = 2;			//����^�[���ɕύX
					path_memory[count].element.distance -= 1;	//����������90mm���炷
					path_memory[count + 1].element.distance -= 1;//����������90mm���炷

				}

			} else {										//�^�[����90mm���i�͂��Ȃ��Ȃ�

				if (path_memory[count].element.muki
						== path_memory[count + 1].element.muki) {//���������ɋȂ���Ȃ�(U�^�[��)

					if (path_memory[count + 2].element.distance >= 1) {	//U�^�[����90mm���i����Ȃ�

						path_memory[count].element.turn = 3;		//180���^�[���ɕύX
						path_memory[count].element.distance -= 1;//����������90mm���炷
						path_memory[count + 2].element.distance -= 1;//����������90mm���炷
						displace_path(count + 1);						//����炷

					} else {									//U�^�[���シ���Ȃ���Ȃ�

						if (path_memory[count + 2].all != 0) {//path���I����ĂȂ����`�F�b�N�@�I����ĂȂ���΋t�����Ƀ^�[���̂͂�

							path_memory[count].element.turn = 5;	//135���^�[���ɕύX
							path_memory[count].element.distance -= 1;//����������90mm���炷
							displace_path(count + 1);					//����炷
							naname_flag = TRUE;

						}

					}

				} else {		//�Ⴄ���@�ɋȂ���Ȃ�

					path_memory[count].element.turn = 4;			//45���^�[���ɕύX
					path_memory[count].element.distance -= 1;	//����������90mm���炷
					naname_flag = TRUE;

				}

			}
			count++;		//�z�������
		}
	}

}

void path::create_path() {
	signed char path_x, path_y;							//�ʒu�Ǘ��p
	signed char path_direction_x, path_direction_y;		//�����Ǘ��p
	signed char straight_flag;			//�����ł��邩�ǂ������ʗp�t���O
	SAVE_DIRECTION save_direction;				//���ɍs���}�X�̕�����ۑ�
	unsigned int count = 0;	//���𐔂��邾���̕ϐ�

	set_step_for_shortest(GOAL_x, GOAL_y);

	path_reset();

	path_direction_x = 0;	//������������
	path_direction_y = 1;

	path_x = 0;		//�ʒu��������
	path_y = 0;

	straight_flag = FALSE;	//�t���O�͐܂��Ă���

	path_memory[count].element.distance += 1;	//�ŏ��͕K������撼�i����

	while (1) {

		save_direction.all = 0;		//���ɍs������������
		straight_flag = FALSE;	//�t���O�͐܂��Ă���

		path_x += path_direction_x; 		//�ʒu�C��
		path_y += path_direction_y;

		if ((path_x == GOAL_x) && (path_y == GOAL_y))
			break;	//GOAL�ɂ��ǂ蒅������I��

		//��
		if ((path_x - 1) >= 0) {		//path_x-1,path_y�̍��W�����H��(0�ȏ�)�ł���
			if (get_step(path_x - 1, path_y)
					== (get_step(path_x, path_y) - 1)) {		//1��,�����̏������ق���
				if ((map::get_wall(path_x, path_y, MUKI_LEFT) == false)) {//�ǂ��Ȃ��Ȃ�
					save_direction.element.left = 1;		//���ɐi�ޕ����̑I�����ɒǉ�
					if ((path_direction_x == -1) && (path_direction_y == 0)) {//���������Ă�Ƃ��i���i�ł���Ƃ��j
						straight_flag = TRUE;	//���i�t���O�����Ă�
					}
				}
			}

		}

		//�E
		if ((path_x + 1) < MAZE_SIZE) {	//path_x+1,path_y�̍��W�����H���ł���
			if (get_step(path_x + 1, path_y)
					== (get_step(path_x, path_y) - 1)) {			//�����̏������ق���
				if ((map::get_wall(path_x, path_y, MUKI_RIGHT) == false)) {	//�ǂ��Ȃ��Ȃ�
					save_direction.element.right = 1;		//���ɐi�ޕ����̑I�����ɒǉ�
					if ((path_direction_x == 1) && (path_direction_y == 0)) {//�E�������Ă�Ƃ��i���i�ł���Ƃ��j
						straight_flag = TRUE;	//���i�t���O�����Ă�
					}
				}
			}
		}

		//��
		if ((path_y - 1) >= 0) {		//path_x,path_y-1�̍��W�����H��(0�ȏ�)�ł���
			if (get_step(path_x, path_y - 1)
					== (get_step(path_x, path_y) - 1)) {			//�����̏������ق���
				if ((map::get_wall(path_x, path_y, MUKI_DOWN) == false)) {//�ǂ��Ȃ��Ȃ�
					save_direction.element.down = 1;		//���ɐi�ޕ����̑I�����ɒǉ�
					if ((path_direction_x == 0) && (path_direction_y == -1)) {//���������Ă�Ƃ��i���i�ł���Ƃ��j
						straight_flag = TRUE;	//���i�t���O�����Ă�
					}
				}
			}
		}

		//��
		if ((path_y + 1) < MAZE_SIZE) {	//path_x,path_y+1�̍��W�����H��(16�ȉ�)�ł���
			if (get_step(path_x, path_y + 1)
					== (get_step(path_x, path_y) - 1)) {			//�����̏������ق���
				if ((map::get_wall(path_x, path_y, MUKI_UP) == false)) {//�ǂ��Ȃ��Ȃ�
					save_direction.element.up = 1;		//���ɐi�ޕ����̑I�����ɒǉ�
					if ((path_direction_x == 0) && (path_direction_y == 1)) {//��������Ă�Ƃ��i���i�ł���Ƃ��j
						straight_flag = TRUE;	//���i�t���O�����Ă�
					}
				}
			}
		}

		if (straight_flag == TRUE) {			//���i�ł���Ȃ�
			path_memory[count].element.distance += 2;	//180mm���i��ǉ�

		} else {								//�^�[������Ȃ�
			path_memory[count].element.turn = 1;	//�����^�[��
			if (path_direction_x == 0) {						//�ォ�������̂Ƃ�
				//�E�ɍs������
				if (save_direction.element.right == 1) {
					if (path_direction_y == 1) {	//��������Ă�
						//�E�����^�[��
						path_memory[count].element.muki = MUKI_RIGHT;
						direction_turn(&path_direction_x, &path_direction_y,
						MUKI_RIGHT);
					} else {					//���������Ă�
						//�������^�[��
						path_memory[count].element.muki = MUKI_LEFT;
						direction_turn(&path_direction_x, &path_direction_y,
						MUKI_LEFT);
					}
					//���ɍs������
				} else {
					if (path_direction_y == -1) {	//���������Ă�
						//�E�����^�[��
						path_memory[count].element.muki = MUKI_RIGHT;
						direction_turn(&path_direction_x, &path_direction_y,
						MUKI_RIGHT);
					} else {					//��������Ă�
						//�������^�[��
						path_memory[count].element.muki = MUKI_LEFT;
						direction_turn(&path_direction_x, &path_direction_y,
						MUKI_LEFT);
					}
				}

			} else {											//�E���������̂Ƃ�
				//��ɍs������
				if (save_direction.element.up == 1) {
					if (path_direction_x == -1) {	//���������Ă�
						//�E�����^�[��
						path_memory[count].element.muki = MUKI_RIGHT;
						direction_turn(&path_direction_x, &path_direction_y,
						MUKI_RIGHT);
					} else {					//�E�������Ă�
						//�������^�[��
						path_memory[count].element.muki = MUKI_LEFT;
						direction_turn(&path_direction_x, &path_direction_y,
						MUKI_LEFT);
					}
					//���ɍs������
				} else {
					if (path_direction_x == 1) {	//�E�������Ă�
						//�E�����^�[��
						path_memory[count].element.muki = MUKI_RIGHT;
						direction_turn(&path_direction_x, &path_direction_y,
						MUKI_RIGHT);
					} else {					//���������Ă�
						//�������^�[��
						path_memory[count].element.muki = MUKI_LEFT;
						direction_turn(&path_direction_x, &path_direction_y,
						MUKI_LEFT);
					}
				}
			}

			count++;
		}

	}

	path_memory[count].element.distance += 1;	//90mm���i��ǉ�	�S�[���ɓ��肫�邽��
	path_memory[count].element.flag = TRUE;		//�I���t���O�����ĂĂ���

}

void path::create_path_advance() {
	create_path();
	improve_path();
}

void path::create_path_naname() {
	create_path();
	improve_advance_path();
}

void path::path_reset() {
	unsigned int reset_count;
	for (reset_count = 0; reset_count < PATH_MAX; reset_count++) {
		path_memory[reset_count].all = 0;
	}
	path_memory[PATH_MAX - 1].element.flag = 1;
}

unsigned char path::get_path_flag(unsigned int index_number) {
	return path_memory[index_number].element.flag;
}

unsigned char path::get_path_straight(unsigned int index_number) {
	return path_memory[index_number].element.distance;
}

unsigned char path::get_path_turn_type(unsigned int index_number) {
	return path_memory[index_number].element.turn;
}

unsigned char path::get_path_turn_muki(unsigned int index_number) {
	return path_memory[index_number].element.muki;
}
*/


void direction_turn(signed char *direction_x, signed char *direction_y,
		unsigned char direction_turn_muki) {
	signed char temp_direction_x = (*direction_x);	//���̏ꏊ�ɕۑ����Ȃ��ƕϊ��r���ŎQ�Ƃ���H�ڂɂȂ�
	signed char temp_direction_y = (*direction_y);
	if (direction_turn_muki == MUKI_LEFT) {
		*direction_x = (temp_direction_x) * 0 + (temp_direction_y) * (-1);//��]�s��̃�=90�̌v�Z
		*direction_y = (temp_direction_x) * 1 + (temp_direction_y) * 0;	//��]�s��̃�=90�̌v�Z
	} else {
		*direction_x = (temp_direction_x) * 0 + (temp_direction_y) * 1;	//��]�s��̃�=-90�̌v�Z
		*direction_y = (temp_direction_x) * (-1) + (temp_direction_y) * 0;//��]�s��̃�=-90�̌v�Z
	}

}

