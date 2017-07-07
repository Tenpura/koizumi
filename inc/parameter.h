/*
 * parameter.h
 *
 *  Created on: 2016/10/23
 *      Author: Koizumi
 */

#ifndef PARAMETER_H_
#define PARAMETER_H_

#include"define.h"

//パラメータ
#define MASS	(20 * 0.001)			//マウスの重さ[kg]
#define tire_R (7.55 * 0.001)	//タイヤの半径　[m]
#define TREAD_W	(44*0.001)		//トレッド幅[m]

#define LEAST_SQUARE_TIME	2000		//ジャイロの最小二乗法を何ms出かけるか

#define LOG_COUNT 2000	//LOGをいくつとるか。最低1、0にはしないこと
#define INT_LOG_COUNT	1	//Int型のLogをいくつとるか　最低1


#define MOUSE_MODE	1	//1がハーフ,2がクラシック



#define SEARCH_VELOCITY	0.25	//探索の速度[m/s]



#include"user.h"
#include"serial.h"

#define RUN_MODE_NUMBER	5	//走行モードを何種類用意するか

class parameter {
private:
	const static unsigned int ideal_photo[2][5];			//ideal_photo[クラシックorハーフ][光学センサの向き]
	const static int16_t min_wall_photo[2][5];			//壁がある時の最小値[クラシックorハーフ][光学センサの向き]
	const static TRAPEZOID straight_run[RUN_MODE_NUMBER];

	//クラシック用パラメータ
	const static INIT_SLALOM right_slalom[slalom_type_count][RUN_MODE_NUMBER], left_slalom[slalom_type_count][RUN_MODE_NUMBER];

	//ハーフ用パラメータ
	const static INIT_SLALOM right_slalom_half[slalom_type_count][RUN_MODE_NUMBER], left_slalom_half[slalom_type_count][RUN_MODE_NUMBER];


public:
	static unsigned int get_ideal_photo(const PHOTO_TYPE photo_type);
	static int16_t get_min_wall_photo(const PHOTO_TYPE photo_type);

	static float get_run_acceleration(const unsigned char select_mode);
	static float get_run_max_velocity(const unsigned char select_mode);
	static float get_run_de_acceleration(const unsigned char select_mode);

	static float get_slalom(const SLALOM_TYPE slalom_type, const SLALOM_ELEMENT slalom_element,
				const signed char right_or_left, const unsigned char select_mode);

};



#endif /* PARAMETER_H_ */
