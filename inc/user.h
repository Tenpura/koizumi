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

//TODO テンプレートできゅーを実装する
/*
template <class T>
class queue{
private:
	uint16_t head,tail;
	T *data;

public:
	T& dequeue();					//きゅーから値を出す
	void enqueue(T set_value);		//きゅーに値を入れる

	queue(uint16_t size);
	queue(uint16_t size1, uint16_t size2);

	~queue();

};
*/

//角度変換関数
float degree(float radian);		//ラジアン	->	度数		-π≦θ≦π
float radian(float degree);		//度数	->	ラジアン	-180≦θ≦180

//compas<->muki
compas muki_to_compas(uint8_t muki);	//defineされたMUKIを与えると、compasを返す.
uint8_t compas_to_muki(compas muki);	//列挙型のcompasをDefineされたMUKIに変換する



//wait関数
extern uint32_t wait_counter;	//割り込み内で1ずつ加算される変数
class wait{
private:
	static uint32_t counter;
public:
	static void ms(uint32_t wait_time);	//wait_time[ms]だけ待つ関数
	static void set_count(uint32_t count);			//カウントアップする関数
	static void reset_count(void);			//counterを0にリセットする

	static uint32_t get_count(void);		//counterの値を取得。起動してからの時間を計測するときに使用。

};


//mode選択クラス
class mode {
private:

	mode();

public:
	//今はスイッチで切替、スイッチが決定
	static uint8_t select_mode(const unsigned char mode_number, const PHOTO_TYPE type);//mode選択し、選んだモード番号を返す
	static bool select_RorL(const PHOTO_TYPE type);	//rightならtrue,leftならfalse

	static bool search_mode();		//探索モード
	static bool shortest_mode();	//最短モード

	~mode();
};

//歩数マップ展開用のリングバッファQueue
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


//logクラス	いつかはtemplateで任意の型に対応させたい…!

//ログというよりバッファ。掲示板的
//入力を文字列として保管
//extern "C" void putnbyte(char *buf, int16_t len);	//printf_logで使用
/*
class log{
private:
	static char buf[buf_count];	//バッファ。+100はメモリオーバーフロー対策でとってある(暗黙で1回のログは100byte以下だと仮定)。
	static uint16_t length;				//現在のバッファ量記録用。具体的にはbuf[xx]のxx部分を示す。
	static bool available_flag;
		//書き込めるかチェック用フラグ。check_put_available関数で良いため、明示的にはいじらない。printf_log()で警告するために使用。

	static bool check_put_available(uint16_t put_byte);	//put_byteのデータを書き込み可能か判断する。可能ならTrue。Available？
	static void add_buffer(char* add_buf, uint16_t buf_size);	//与えられたbuf_sizeのバイト数のadd_bufを全体のbufの後ろに追加する。

public:
	static int16_t put_log(const char *fmt, ...);	//printfと同じ形で保存しておきたい物を入力。返り値は書き込み成功時はByte数、失敗時は―1．
	static void printf_log();		//貯めてるログをコンソールにすべて出力
	static void reset_log();		//全てのログを0にリセット
};

class int_log {
private:
	static signed int log_case[2][log_count];
	static unsigned int log_counter;
	int init_number;

public:
	void reset_log();		//logの中身を消去。全て0にする。

	static void put_log(const int put_number);//logの最後尾に引数を格納。既に埋まっていれば何もしない
	static void put_log(const int put_number,const int put_number2);//上と同じ。ただし2つ保存可

	int get_log(const unsigned int get_number);//get_number番目に格納されてるlogを取り出す
	int get_log(const unsigned int ordinal_number,const unsigned int get_number);//上と同じ。ただし2つ保存可

	int_log();
	int_log(int initialize_number);//もし初期化する数を0以外にしたかったら、ここで変更してね
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
	static void reset_log();		//logの中身を消去。全て0にする。

	//logの最後尾に引数を格納。既に埋まっていれば何もしない
	//a,bは多次元配列用。1次元の場合はbは無視される。
	static void put_log(const float put_number_a,const float put_number_b);

	//get_dimensionの次元のget_number番目に格納されてるlogを取り出す
	float get_log(const unsigned char get_dimension, const unsigned int get_number);

	float_log();
	float_log(float initialize_number);//もし初期化する数を0以外にしたかったら、ここで変更してね
	~float_log();
};
*/


//数学クラス
class my_math{
private:

	#define LOG_N 1000	//logテーブルの要素数

	const static float sin_table[92];		//[]の要素がdegreeに対応。念のため92個
	const static float log_table[LOG_N+1];		//logテーブル。高橋先輩のを参考に傾きに応じて分割している

public:
	static float sin(const float radian);
	static float cos(const float radian);

	static float log(float x);			//logを返す関数　自然対数　0.1<x<10の範囲にしか対応していないことに注意！

	static float sqrt(float x);			//平方根を返す関数　ニュートン法

};



#endif /* USER_H_ */
