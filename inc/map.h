/*
 * map.h
 *
 *  Created on: 2016/10/29
 *      Author: Koizumi
 */

#ifndef MAP_H_
#define MAP_H_

#include "stm32f4xx.h"
#include"define.h"
#include"extern_c.h"
#include"user.h"


//TODO 何をstaticにすべきで、何をローカルのままで置くべきか


class map {

//メンバ変数
private:
	//unsigned char x,y;//座標
	static MAZE_WALL x_maze_wall[MAZE_SIZE],y_maze_wall[MAZE_SIZE];//壁情報保存用
	static MAZE_WALL x_wall_exist[MAZE_SIZE],y_wall_exist[MAZE_SIZE];//壁情報を見たかどうか判別用

	static void set_maze_wall( MAZE_WALL* const maze_wall,unsigned char edit_number,bool is_wall);//maze_wallに値を代入する用
	static unsigned char get_maze_wall( MAZE_WALL maze_wall,unsigned char edit_number);//maze_wallの値を読む用



public:
	static void create_wall(unsigned char wall_x, unsigned char wall_y, unsigned char muki);//(x,y)のmuki方向の壁を作る
	static void destroy_wall(unsigned char wall_x, unsigned char wall_y, unsigned char muki);
	//壁があればdefineされたTRUE、なければFALSEが返ってくる。迷路外だとエラーに入り出力は－1
	static bool get_wall(unsigned char wall_x, unsigned char wall_y, unsigned char muki);

	static void remember_exist(unsigned char wall_x, unsigned char wall_y, unsigned char muki);//(x,y)のmuki方向の壁を作る
	static void forget_exist(unsigned char wall_x, unsigned char wall_y, unsigned char muki);
	//壁を見たことがあればdefineされたTRUE、なければFALSEが返ってくる。迷路外だとエラーに入り出力は－1
	static bool check_exist(unsigned char wall_x, unsigned char wall_y, unsigned char muki);

	static void reset_wall();		//壁情報と見たかどうかをすべてリセット

	void draw_map(bool write_step);//myprintfで迷路を描画
	void convert_mapdata(unsigned char (*hiramatu_data)[16]);//平松先輩のマップデータ形式をノノホ式に変換

	static void input_map_data(const MAP_DATA* input_data);//外部に保存したデータの入力
	static void output_map_data(MAP_DATA* const output_data);//外部にデータ出力

	map();
	~map();

};

#define STEP_INIT 999		//歩数の初期値

class step {
private:
	static DIRECTION save_direction;				//次に行くマスの方向を保存
	static unsigned short maze_step[MAZE_SIZE][MAZE_SIZE];

	static void step_reset();
	static void close_one_dead_end(unsigned char target_x, unsigned char target_y);

public:

	static void set_step(unsigned char target_x,unsigned char target_y);//target_x,yを基準に歩数マップ作製(等高線)
	static void set_step_by_known(unsigned char target_x,unsigned char target_y);//見ていない壁は、壁があると見なす
	static unsigned int get_step(unsigned char target_x,unsigned char target_y);//ある座標(x,y)の歩数を返す

	static void close_dead_end();//マップ上の袋小路をつぶす

	step();
	step(const MAP_DATA* input_data);
	~step();

};

/*
class path:public step {
private:
	typedef union {
		unsigned char all;				//一括
		struct {
			unsigned char up :1;		//→	x=1,y=0の方向
			unsigned char right :1;//←	x=-1,y=0の方向
			unsigned char down :1;//↓	x=0,y=-1の方向
			unsigned char left :1;//↑	x=0,y=1の方向
			unsigned char now :4;//現在の方向を管理、この数、save_directionをビットシフトすると現在の向きに対応
		}element;
	}SAVE_DIRECTION;				//次に行くマスの方向を保存
	static PATH path_memory[PATH_MAX];

	void set_step_for_shortest(unsigned char target_x,unsigned char target_y);//最短用の歩数マップ作製
	void displace_path(unsigned int path_number);//path_number目のpathを消してからpathを一個ずらす
	void improve_path();//小回りだけのpathに大回りを追加
	void improve_advance_path();//小回りだけのpathに大回りと斜めを追加

public:
	void create_path();//小回りだけのパス
	void create_path_advance();//大回りを追加したパス(ナナメはナシ)
	void create_path_naname();//大回りとナナメを追加したパス

	void path_reset();
	unsigned char get_path_flag(unsigned int index_number);
	unsigned char get_path_straight(unsigned int index_number);
	unsigned char get_path_turn_type(unsigned int index_number);
	unsigned char get_path_turn_muki(unsigned int index_number);

};
*/

//方向成分と回転する向きを与えると、機体の向きを90°そちらへ変える
void direction_turn(signed char *direction_x, signed char *direction_y,
		unsigned char direction_turn_muki);




#endif /* MAP_H_ */
