/*
 * main.cpp
 *
 *  Created on: 2016/08/21
 *      Author: Koizumi
 */

#include "stm32f4xx.h"

#include "extern_c.h"

#include "define.h"
#include "init.h"
#include "hardware.h"
#include "ad_convert.h"
#include "user.h"
#include "run.h"
#include "map.h"

int main(void);

#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif

uint32_t wait_counter = 0;
static const int16_t flog_number = 2000;
float flog[2][flog_number] = { 0 };

void interrupt_timer();			//CONTROL_PERIOD���ƂɊ��荞�ފ֐�

int main(void) {
	for (int16_t j = 0; j < 10; j++) {
		for (volatile int16_t i = 0; i < 10000; i++) {
			//�N���b�N�����肳����H
		}
	}

	//�����ݒ�
	init_all();
	mouse::reset_count();

	my7seg::blink(8, 100, 5);

	myprintf("Compile DATE: %s\n\r", __DATE__);
	myprintf("Compile TIME: %s\n\r", __TIME__);

	myprintf("vol -> %f\n\r", get_battery());

	mpu6000::init_mpu6000();

	my7seg::turn_off();

	//�}�b�v�����Z�b�g����
	map::reset_wall();
	map::output_map_data(&mouse::now_map);

	uint8_t select = 0;	//���[�h�Ǘ��p
	while (1) {
		//�`���^�����O�΍�
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0)
			;
		wait::ms(100);
		if (get_battery() < 3.5) {
			while (1) {
				my7seg::light_error();
				wait::ms(200);
				my7seg::turn_off();
				wait::ms(200);
				if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0) {
					wait::ms(100);
					break;
				}
			}
		} else if (get_battery() < 3.8) {
			while (1) {
				my7seg::light_error();
				wait::ms(500);
				my7seg::turn_off();
				wait::ms(500);
				if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0) {
					wait::ms(100);
					break;
				}
			}
		}

		//�`���^�����O�΍�
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0)
			;
		wait::ms(100);

		select = mode::select_mode(7, PHOTO_TYPE::right);

		switch (select) {
		case 0:		//�ǂ̒l��ǂނ���	���̖h�~�̂��߂Ƀ��[�h0�͎��Q�Ȃ��z�ɂ��Ƃ�
			while (1) {
				/*
				 myprintf("gyro %4.4f  ", gyro::get_angular_velocity());
				 myprintf("accel y %4.4f", accelmeter::get_accel(AXIS_t::axis_y));
				 myprintf("accel z %4.4f", accelmeter::get_accel(AXIS_t::axis_z));

				 myprintf("\n\r");
				 */

				myprintf("right %d  ", photo::get_value(right));
				myprintf("left %d  ", photo::get_value(left));
				myprintf("f_r %d  ", photo::get_value(front_right));
				myprintf("f_l %d  ", photo::get_value(front_left));
				myprintf("front %d  ", photo::get_value(front));
				myprintf("\n\r");

				wait::ms(100);
				if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0) {
					wait::ms(100);
					break;
				}
			}
			break;

		case 1:		//�T��
			mode::search_mode();
			motor::sleep_motor();
			break;

		case 2:		//�ŒZ
			path::create_path();
			//map::draw_map(false);
			mode::shortest_mode();
			//run::path(0, 0);
			//path::draw_path();
			motor::sleep_motor();
			break;

		case 3:		//�f�[�^����
			//�}�b�v�����Z�b�g����
			map::reset_wall();
			map::output_map_data(&mouse::now_map);
			break;

		case 4:		//�����p
			encoder::yi_correct();		//YI���␳
			encoder::draw_correct(false, false);
			while (1) {
				my7seg::blink(8, 500, 1);
				if (photo::check_wall(PHOTO_TYPE::front))
					break;
			}
			my7seg::count_down(3, 500);
			mouse::run_init(true, false);
			//run::accel_run_wall_eage(0.09 * 2, SEARCH_VELOCITY, 0, 0.09);

			flog[0][0] = -1;
			run::accel_run(0.09 * 4, 0, 1);

			//run::accel_run(0.09*1.5, SEARCH_VELOCITY,0);
			//run::slalom_for_search(small, MUKI_RIGHT, 0);
			//flog[0][0] = mouse::get_angle_degree();
			//run::accel_run_wall_eage(0.09*5, SEARCH_VELOCITY, 0, 0.09*4.5);
			//control::stop_wall_control();
			//run::accel_run(0.045 * 2, 0, 0);
			//run::spin_turn(-180);
			//run::accel_run(0.09*10, 0, 0);

			//run::fit_run(0);

			wait::ms(2000);

			motor::sleep_motor();
			my7seg::turn_off();

			while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 1) {
			}
			//map::draw_map(false);

			for (int i = 0; i < flog_number; i++) {
				myprintf("%f,%f\n\r", flog[0][i], flog[1][i]);
			}
			break;

		case 5:		//�����p
			while (1) {
				my7seg::blink(8, 500, 1);
				if (photo::check_wall(PHOTO_TYPE::front))
					break;
			}
			my7seg::count_down(3, 500);
			//	mouse::run_init(true, false);

			flog[0][0] = -1;

			wait::ms(2000);

			motor::sleep_motor();
			my7seg::turn_off();

			while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 1) {
			}

			for (int i = 0; i < flog_number; i++) {
				myprintf("%f,%f\n\r", flog[0][i], flog[1][i]);
			}
			break;

		case 6:
			map::draw_map(false);
			path::draw_path();
			break;

		}

	}
	return 1;
}

void interrupt_timer() {
	//XXX �J���}���t�B���^�̐���l�i�����x�Z���T�j�Ɗϑ��l�i�G���R�[�_�[�j�̕��U
	static kalman v_kal(0.101, 630);		//���x�p�̃J���}���t�B���^�N���X���Ăяo��

	GPIO_SetBits(GPIOA, GPIO_Pin_14);

	wait_counter++;	//ms(�~���b)�̃J�E���g��1����
	mouse::add_one_count_ms();
	wait::set_count(wait_counter);

	photo::interrupt(true);
	gyro::interrupt();
	accelmeter::interrupt();
	encoder::interrupt();

	v_kal.update(accelmeter::get_accel(axis_y) * CONTORL_PERIOD,
			encoder::get_velocity());		//�J���}���t�B���^��������
	mouse::set_velocity(v_kal.get_value());		//���ݑ��x�Ƃ��ĕ␳��̑��x���̗p����

	mouse::interrupt();

	control::cal_delta();			//�p������ɗp����΍����v�Z
	control::posture_control();

	//control::fail_safe();

	static volatile uint16_t i = 0;
	if (i == 0) {
		if (flog[0][0] == -1) {
			i++;
		}
	} else if (i < flog_number) {
		flog[0][i] = photo::get_value(right);//encoder::get_velocity();//mouse::get_velocity();//gyro::get_angular_velocity();
		flog[1][i] = photo::get_displacement_from_center(right);//accelmeter::get_accel(axis_y);//mouse::get_ideal_angular_velocity();
		i++;
	}

	GPIO_ResetBits(GPIOA, GPIO_Pin_14);

}

#ifdef __cplusplus
void abort(void) {
}
#endif
