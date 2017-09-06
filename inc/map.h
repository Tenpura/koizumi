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
#include <queue>


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
	//壁があればdefineされたTRUE、なければFALSEが返ってくる。迷路外だとエラーに入り出力は−1
	static bool get_wall(unsigned char wall_x, unsigned char wall_y, unsigned char muki);

	static void remember_exist(unsigned char wall_x, unsigned char wall_y, unsigned char muki);//(x,y)のmuki方向の壁を作る
	static void forget_exist(unsigned char wall_x, unsigned char wall_y, unsigned char muki);
	//壁を見たことがあればdefineされたTRUE、なければFALSEが返ってくる。迷路外だとエラーに入り出力は−1
	static bool check_exist(unsigned char wall_x, unsigned char wall_y, unsigned char muki);
	static bool check_exist(unsigned char wall_x, unsigned char wall_y, compas dir);

	static void reset_wall();		//壁情報と見たかどうかをすべてリセット

	static void draw_map(bool write_step);//myprintfで迷路を描画
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
	static PATH path_memory[PATH_MAX];	//flagは続行フラグ

	static void set_step_for_shortest(unsigned char target_x,unsigned char target_y);//最短用の歩数マップ作製
	static void displace_path(unsigned int path_number);//path_number目のpathを消してからpathを一個ずらす
	static void improve_path();//小回りだけのpathに大回りを追加
	static void improve_advance_path();//小回りだけのpathに大回りと斜めを追加

public:

	static void create_path();//小回りだけのパス
	static void create_path_advance();//大回りを追加したパス(ナナメはナシ)
	static void create_path_naname();//大回りとナナメを追加したパス

	static void draw_path();

	static void path_reset();
	static bool get_path_flag(signed int index_number);				//pathがあるならtrue,ないならfalseを返す.
	static float get_path_straight(unsigned int index_number);			//返り値は距離[m]
	static SLALOM_TYPE get_path_turn_type(unsigned int index_number);
	static unsigned char get_path_turn_muki(unsigned int index_number);		//返り値はMUKI_RIGHT　or　MUKI_LEFT

};

//方向成分と回転する向きを与えると、機体の向きを90°そちらへ変える
void direction_turn(signed char *direction_x, signed char *direction_y,
		unsigned char direction_turn_muki);

//compasを与えると、方角ベクトルを返す. firstがX方向、　secondがY方向
std::pair<int8_t, int8_t> compas_to_direction(compas tar);

//defineされたMUKIを与えると、compasを返す.
compas muki_to_compas(uint8_t muki);

class node_step :public map{
private:
	std::vector<PATH> path;
	static const uint16_t x_size=64;
	static const uint16_t y_size=32;
	static uint16_t step[x_size][y_size];			//ノードに配置する歩数	x,y xは横壁と縦壁の両方を表現するために2倍	[0][0]は(0,0)の西壁
	virtual bool able_set_step(uint8_t x, uint8_t y, compas muki, uint16_t step_val, bool by_known);	//歩を伸ばせるならTrue　壁がないか、その壁を見ているのか、step_valより歩数が大きいかチェック
	bool is_outside_array(uint8_t x_index, uint8_t y_index);		//配列の添え字でみた座標系（X方向だけ倍）で迷路外（配列外）に出ているか

public:
	static const uint16_t init_step = 60000;
	virtual bool set_step(uint8_t x, uint8_t y, compas muki, uint16_t step_val, bool by_known);
	uint16_t get_step(uint8_t x, uint8_t y, compas muki);
	compas get_min_compas(uint8_t x, uint8_t y);			//（x,y）の4つの歩数の内、最小の歩数がどの方角か

	void reset_step(uint16_t reset_val);		//全ての歩数をreset_valでリセット

	uint8_t compas_to_define(compas muki);			//列挙型のcompasをDefineされたMUKIに変換する　統一できてないから仕方なく

	node_step();
	node_step(uint16_t reset_val);
	~node_step();
};

typedef struct {
	uint8_t distance;
	SLALOM_TYPE turn;
	bool is_right;	//ターンが右か？

}  path_element;

class node_path :virtual public node_step {
private:
	static std::vector<path_element> path;

	static PATH to_PATH(path_element from);
	bool is_right_turn(compas now, compas next);		//次のターンが右向きならtrue
	static void push_straight(int half);	//何半区間進むか
	static void push_small_turn(bool is_right);		//小回りでどちらに曲がるか

public:
	static void format();
	static PATH get_path(uint16_t index);	//PATHを直接返す

protected:	//歩数をひいてから実行するのを前提としているので外部アクセス禁止にしておく
	bool create_path(std::pair<uint8_t, uint8_t> init, compas mouse_direction);
	//initマスの中心からfinishマスの中心までのPath　道がふさがってたらFasle
	//mouse_direction が引数になっている理由
	//基本的には最短走行か既知区間加速で使うので歩数の小さい方が今行くべき方向と一致しているが、最小歩数が複数あるとヤバいので最初の向きを要求している
	void improve_path();		//既存のPathを大回り斜めに変更

public:
	node_path();
	~node_path();

};

class node_search :virtual public node_step, virtual public  node_path {
private:
	MAZE_WALL x_finish[MAZE_SIZE],y_finish[MAZE_SIZE];//目的地の座標管理用

	bool set_step_double(uint8_t double_x, uint8_t double_y, uint16_t step_val, bool by_known);	//XY方向両方に倍取った座標軸での歩数代入関数
	bool set_step_double(std::pair<uint8_t, uint8_t> xy, uint16_t step_val, bool by_known);		//XY方向両方に倍取った座標軸での歩数代入関数
	uint16_t get_step_double(uint8_t double_x, uint8_t double_y);		//2倍座標系から歩数を取り出す
	weight_algo algo;		//重みづけの方法を管理する

public:
	void set_weight_algo(weight_algo weight);		//歩数マップの重みづけを変更する
	weight_algo get_weight_algo();

	//set_weight_algoで指定された重みづけに従って歩数を敷き詰める
	void spread_step(std::vector< std::pair<uint8_t, uint8_t> > finish, bool by_known);		//複数マスゴール対応　もちろん1マスでもおｋ

	bool create_small_path(std::vector< std::pair<uint8_t, uint8_t> > finish, std::pair<uint8_t, uint8_t> init, compas mouse_direction);
	//initマスの中心からfinishマスの中心までのPath　道がふさがってたらFasle
	//mouse_direction が引数になっている理由
	//基本的には最短走行か既知区間加速で使うので歩数の小さい方が今行くべき方向と一致しているが、最小歩数が複数あるとヤバいので最初の向きを要求している
	bool create_big_path(std::vector< std::pair<uint8_t, uint8_t> > finish, std::pair<uint8_t, uint8_t> init, compas mouse_direction);
	//大回りパス作製

	void reset_finish();		//目的地情報をすべてリセットする
	void set_finish(std::pair<uint8_t, uint8_t> finish);		//目標座標を設定する  そのマスの東西南北全て目標となる
	void set_finish(std::pair<uint8_t, uint8_t> finish, compas dir);	//目標座標の特定の方角を指定する


	node_search();
	node_search(uint16_t init_step);
	~node_search();

};


#endif /* MAP_H_ */
