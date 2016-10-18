/*
 * ad_convert.h
 *
 *  Created on: 2016/09/17
 *      Author: Koizumi
 */

#ifndef AD_CONVERT_H_
#define AD_CONVERT_H_

//AD変換まわりの関数のまとめ

#include"stm32f4xx.h"
#include"define.h"

//それぞれのAD変換結果をunsigned int型で返す
uint16_t ad_convert_batt();		//バッテリ監視部分


//バッテリー電圧を読んで、float型で返す関数
float get_battery();


#endif /* AD_CONVERT_H_ */


