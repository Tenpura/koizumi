/*
 * define.h
 *
 *  Created on: 2016/08/21
 *      Author: Koizumi
 */

#ifndef DEFINE_H_
#define DEFINE_H_

#include <stdint.h>

#define CONTROL_PERIOD 0.001		//制御周期[sec]

//調整項目

#define MAZE_SIZE	16

#define GOAL_x 5
#define GOAL_y 6

#define PATH_MAX 200

static const uint8_t log_count = 100;	//Logの配列個数
static const uint16_t buf_count = 100;	//バッファ式ログのバッファ数。

//同じ機体を使ってる限り変わらないdefineはココに書く

//ハードウェア

#define LOGIK_V 3.3

#define CONTORL_PERIOD 0.001		//制御周期[s]

#define PINION	9	//ピニオンギアの歯数
#define SPAR	41	//スパーギアの歯数

#define V_BATT_RATIO 2.1	//バッテリー監視用の抵抗による分圧比。バッテリーの何分の1を見てるか

#define MOTOR_ORM	4.5		//モーターの端子間抵抗[Ω]
#define	M_DRIVER_ORM	1	//モータードライバーの抵抗[Ω]
#define M_SUM_ORM	5.5		//上2つの合算抵抗[Ω]

#define ACCEL_SENSITIVITY	8192	//加速度計の感度[count/g] これで測定値を割ると加速度
#define GYRO_SENSITIVITY	16.4		//Gyroの感度[count/(degree/s)]　これで測定値を割ると角速度になる
//#define GYRO_CONST	1.53		//gyroの定数[degree/V/ms]パラメーターの1つ
//XXX左右分ける必要があるかも？

#define ENCODER_CONST	(1.534 * 0.001)			//encoderの分解能[rad/count]

#define MOTOR_CONST	(222.6)		//モーターの回転定数[回転/s/V]

//疑似真偽値
/*
 #define ON	1
 #define OFF	0

 #define TRUE	1
 #define FALSE	0
 */

//#define ERROR	14
#define MUKI_RIGHT	0
#define MUKI_UP		1
#define MUKI_LEFT	2
#define MUKI_DOWN	3

//スイッチ。押すとtrue,離すとfalse
//#define SWITCH_LEFT (1-PORT7.PORT.BIT.B5)
//#define SWITCH_RIGHT (1-PORT7.PORT.BIT.B6)

//便利ゾーン/////////////////////////////////////////////////////////////////////////////////////////////////////
#define SQRT2 1.414	//√2
#define PI()		3.1415		//π　円周率

#define ABS(x)		((x) < 0 ? -(x) : (x))	//絶対値
#define	SIGN(x)	((x) < 0 ? -1 : 1 )		//符合
#define	MAX(a,b)	((a) > (b) ? (a) : (b))	//最大値
#define	MIN(a,b)	((a) < (b) ? (a) : (b))	//最小値

//MELODY
typedef union {
	//unsigned char all;				//一括
	struct {
		unsigned char semiton :2; //半音あげるか下げるかを表す	また曲のおわりも示す(ここがMELODY_ENDのとき終わり)
		unsigned char octave :1;			//オクターブを1つあげるかどうか
		unsigned char beat :2;			//拍数を表す
		unsigned char scale :3;			//音階を表す　0←ドレミファソラシ休→7
	} bit;

} MELODY;

//DIRECTION 向き管理用
typedef union {
	uint8_t all;				//一括
	struct {
		unsigned char :4;		//
		unsigned char up :1;		//↑	x=0,y=1の方向
		unsigned char down :1;		//↓	x=0,y=-1の方向
		unsigned char left :1;		//←	x=-1,y=0の方向
		unsigned char right :1;		//→	x=1,y=0の方向
	} element;
} DIRECTION;				//次に行くマスの方向を保存

enum BOOL {
	FALSE=0, TRUE=1
};

//PATH
typedef union {
	uint16_t all;					//一括で見る
	struct {
		unsigned char :1;		//
		unsigned char flag :1;		//配列の最後かチェック用
		unsigned char turn :4;		//ターンの種類を判別
		unsigned char muki :2;		//ターンの方向を判別
		unsigned char distance :8;		//直進する距離を判別
	} element;
} PATH;

//MAZE_WALL
typedef union {
	uint32_t all;		//全て一括で変更する用
	struct {
		uint16_t high :16;
		uint16_t low :16;
	} SHORT;
	struct {
		//trueなら壁が存在、falseなら存在しない
		unsigned char B0 :1;		//x座標0と1の間の壁　or　y座標0と1の間の壁
		unsigned char B1 :1;
		unsigned char B2 :1;
		unsigned char B3 :1;
		unsigned char B4 :1;
		unsigned char B5 :1;
		unsigned char B6 :1;
		unsigned char B7 :1;
		unsigned char B8 :1;
		unsigned char B9 :1;
		unsigned char B10 :1;
		unsigned char B11 :1;
		unsigned char B12 :1;
		unsigned char B13 :1;
		unsigned char B14 :1;
		unsigned char B15 :1;
		unsigned char B16 :1;		//x座標0と1の間の壁　or　y座標0と1の間の壁
		unsigned char B17 :1;
		unsigned char B18 :1;
		unsigned char B19 :1;
		unsigned char B20 :1;
		unsigned char B21 :1;
		unsigned char B22 :1;
		unsigned char B23 :1;
		unsigned char B24 :1;
		unsigned char B25 :1;
		unsigned char B26 :1;
		unsigned char B27 :1;
		unsigned char B28 :1;
		unsigned char B29 :1;
		unsigned char B30 :1;
		unsigned char B31 :1;
	} bit;
} MAZE_WALL;

//MAP_DATA
typedef struct {
	MAZE_WALL x_wall[MAZE_SIZE], y_wall[MAZE_SIZE];	//壁情報保存用
	MAZE_WALL x_known[MAZE_SIZE], y_known[MAZE_SIZE];	//壁情報を見たかどうか判別用
} MAP_DATA;

//光学センサの種類
enum PHOTO_TYPE {
	right = 0, left = 1, front_right = 2, front_left = 3, front = 4, element_count
};

//台形加速に用いるパラメータ用構造体
typedef struct {
	float acceleration;
	float max_velocity;
	float de_acceleration;
} TRAPEZOID;

//スラモームの種類
typedef enum {
	none = 0,
	small = 1,
	big_90 = 2,
	big_180 = 3,
	begin_45 = 4,
	end_45 = 5,
	begin_135 = 6,
	end_135 = 7,
	oblique_90 = 8,
	spin_turn = 9,
	slalom_type_count		//要素数を表す
} SLALOM_TYPE;

//スラローム用構造体
typedef struct {
	float velocity;				//重心速度[m/s]
	float target_angle;			//何度のターンか[°]
	float clothoid_angle;		//何度までクロソイドするのか（角速度の加速区間	[°]
	float before_distance;		//前距離[m]
	float after_distance;		//後距離[m]
	float angular_accel;		//角加速度
	float max_angular_velocity;	//最大角速度
	float time;					//どれだけ時間がかかるのか[sec]
} INIT_SLALOM;

//スラロームパラメーターの要素
typedef enum {
	velocity,
	target_angle,
	clothoid_angle,
	before_distance,
	after_distance,
	angular_accel,
	max_angular_velocity,
	time
} SLALOM_ELEMENT;

//センサータイプを表す列挙型
typedef enum {
	sen_gyro,
	sen_encoder,
	sen_photo,
	sen_accel,
	sen_all
} SEN_TYPE;

//座標軸。マス単位でなく、厳密に距離とかを扱う用
typedef struct {
	float x;
	float y;
} COORDINATE;

#endif /* DEFINE_H_ */
