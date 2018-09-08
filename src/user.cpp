/*
 * user.cpp
 *
 *  Created on: 2016/08/21
 *      Author: Koizumi
 */

#include"user.h"

float degree(float radian) {
	return (radian * 180 / PI());
}

float radian(float degree) {
	return (degree * PI() / 180.0);
}

compas muki_to_compas(uint8_t muki) {
	switch (muki) {
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
	return north;
}

uint8_t compas_to_muki(compas from) {
	switch (from) {
	case east:
		return MUKI_RIGHT;
	case west:
		return MUKI_LEFT;
	case north:
		return MUKI_UP;
	case south:
		return MUKI_DOWN;
	}
	return 0;
}

uint32_t wait::counter = 0;

void wait::set_count(uint32_t count) {
	counter = count;
}

void wait::reset_count() {
	counter = 0;
}

uint32_t wait::get_count() {
	return counter;
}

void wait::ms(uint32_t wait_time) {
	uint32_t temp_counter = 0;
	set_count(wait_counter);
	if (get_count() > (400000000 - wait_time)) {	//オーバーフロー対策
		reset_count();	//カウンターをリセットして
		wait_counter = 0;
		temp_counter = wait_time;
	} else {
		temp_counter = get_count() + wait_time;
	}

	while (get_count() < temp_counter) {
		set_count(wait_counter);
	};		//目標の時間まで待機
}

uint8_t mode::select_mode(const unsigned char mode_number,
		const PHOTO_TYPE type) {
	unsigned char select = 0;
	bool stnby_flag = true;		//モード送り可能のときtrue	センサーを反応させてるとき高速でモードが送られないように

	while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 1) {	//押されたら決定
		my7seg::light(select);
		wait::ms(10);

		if (photo::check_wall(type)) {
			if (stnby_flag) {
				select++;
				stnby_flag = false;
			}
		} else {
			stnby_flag = true;
		}

		if (select >= mode_number) {	//上限に達したら、下限に飛ばす
			select = 0;
		}

	}

	my7seg::blink(select, 250, 5);		//決定したときは選択したモードを強調

	return select;
}
bool mode::select_RorL(const PHOTO_TYPE type) {
	bool is_right = true;
	bool stnby_flag = true;		//モード送り可能のときtrue	センサーを反応させてるとき高速でモードが送られないように

	while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 1) {	//押されたら決定
		my7seg::turn_off();
		if (is_right)
			my7seg::light(my7seg::DIRECTION::right);
		else
			my7seg::light(my7seg::DIRECTION::left);
		wait::ms(10);

		if (photo::check_wall(type)) {
			if (stnby_flag) {
				is_right = !is_right;	//正負反転
				stnby_flag = false;
			}
		} else {
			stnby_flag = true;
		}

	}
	//決定したときは選択したモードを強調
	for (int i = 0; i < 5; i++) {
		if (is_right)
			my7seg::light(my7seg::DIRECTION::right);
		else
			my7seg::light(my7seg::DIRECTION::left);
		wait::ms(250);
		my7seg::turn_off();
		wait::ms(250);
	}

	return is_right;
}

bool mode::search_mode() {
	//ゴール座標を変数に
	std::vector<std::pair<uint8_t, uint8_t> > goal_vect;
	goal_vect.emplace_back(std::make_pair(GOAL_x, GOAL_y));
	goal_vect.emplace_back(std::make_pair(GOAL_x + 1, GOAL_y));
	goal_vect.emplace_back(std::make_pair(GOAL_x, GOAL_y + 1));
	goal_vect.emplace_back(std::make_pair(GOAL_x + 1, GOAL_y + 1));

	uint8_t select = select_mode(6 + 1, PHOTO_TYPE::right);
	//encoder::yi_correct();		//YI式補正

	while (select != 0) {
		my7seg::blink(8, 500, 1);
		if (photo::check_wall(PHOTO_TYPE::front))
			break;
	}

	switch (select) {
	case 0:		//0はメニューに戻る
		break;

	case 1:		//1は普通の足立法
		mouse::set_position(0, 0);
		mouse::set_direction(north);
		if (adachi::adachi_method(GOAL_x, GOAL_y, false)) {		//足立方が成功したら
			wait::ms(300);
			motor::sleep_motor();
			flash_maze flash_l;
			MAP_DATA temp;
			map::output_map_data(&temp);
			flash_l.save_maze(0, &temp);
			//	flash_l.save_maze(1, &temp);

		}
		break;

	case 2:		//2は帰りもあるよ
		mouse::set_position(0, 0);
		mouse::set_direction(north);
		if (adachi::adachi_method(GOAL_x, GOAL_y, false)) {	//足立法が成功したら
			wait::ms(300);
			flash_maze flash_l;
			MAP_DATA temp;
			map::output_map_data(&temp);
			flash_l.save_maze(0, &temp);
			//flash_l.save_maze(1, &temp);

			mouse::set_position(GOAL_x, GOAL_y);
			run::spin_turn(180);
			mouse::turn_90_dir(MUKI_RIGHT);
			mouse::turn_90_dir(MUKI_RIGHT);
			wait::ms(500);

			control::stop_wall_control();
			run::accel_run((-0.02 * MOUSE_MODE), 0, 0);
			control::start_wall_control();
			wait::ms(500);


			if (adachi::adachi_method(0, 0, false)) {
				wait::ms(300);
				map::output_map_data(&temp);
				flash_l.save_maze(0, &temp);
				//flash_l.save_maze(1, &temp);
				motor::sleep_motor();

			}

		}
		break;

	case 3:			//ノード型足立法
		mouse::set_position(0, 0);
		mouse::set_direction(north);
		if (adachi::adachi_method(GOAL_x, GOAL_y, true)) {		//足立方が成功したら
			wait::ms(300);
			motor::sleep_motor();
			flash_maze flash_l;
			MAP_DATA temp;
			map::output_map_data(&temp);
			flash_l.save_maze(0, &temp);
			//	flash_l.save_maze(1, &temp);

		}
		break;

	case 4:
		mouse::set_position(0, 0);
		mouse::set_direction(north);
		if (adachi::adachi_method(15, 0, false)) {	//足立法が成功したら
			flash_maze flash_l;
			MAP_DATA temp;
			map::output_map_data(&temp);
			flash_l.save_maze(0, &temp);
			flash_l.save_maze(1, &temp);

			mouse::set_position(15, 0);
			run::spin_turn(180);
			mouse::turn_90_dir(MUKI_RIGHT);
			mouse::turn_90_dir(MUKI_RIGHT);
			wait::ms(500);

			if (adachi::adachi_method(GOAL_x, GOAL_y, false)) {	//足立法が成功したら
				flash_maze flash_l;
				MAP_DATA temp;
				map::output_map_data(&temp);
				flash_l.save_maze(0, &temp);
				flash_l.save_maze(1, &temp);

				mouse::set_position(GOAL_x, GOAL_y);
				run::spin_turn(180);
				mouse::turn_90_dir(MUKI_RIGHT);
				mouse::turn_90_dir(MUKI_RIGHT);
				wait::ms(500);

				adachi::adachi_method(0, 0, false);
			}

		}
		break;

	case 5:
		mouse::set_position(0, 0);
		mouse::set_direction(north);
		if (adachi::adachi_method(GOAL_x, GOAL_y, true)) {	//足立法が成功したら
			flash_maze flash_l;
			MAP_DATA temp;
			map::output_map_data(&temp);
			flash_l.save_maze(0, &temp);
			flash_l.save_maze(1, &temp);

			mouse::set_position(GOAL_x, GOAL_y);
			run::spin_turn(180);
			mouse::turn_90_dir(MUKI_RIGHT);
			mouse::turn_90_dir(MUKI_RIGHT);
			wait::ms(500);

			adachi::adachi_method(0, 0, false);
		}
		break;

	case 6:
		mouse::set_position(0, 0);
		mouse::set_direction(north);
		if (adachi::adachi_method(GOAL_x, GOAL_y, true)) {	//古川式足立法（櫛無視）が成功したら
			wait::ms(100);
			mouse::set_position(GOAL_x, GOAL_y);
			run::spin_turn(180);
			mouse::turn_90_dir(MUKI_RIGHT);
			mouse::turn_90_dir(MUKI_RIGHT);
			wait::ms(100);

			adachi::adachi_method(0, 0, true);
		}
		break;

	}

	return false;

}

bool mode::shortest_mode() {
	std::vector<std::pair<uint8_t, uint8_t> > goal;
	//FIXME
	for (int x = 0; x <= 1; x++) {
		for (int y = 0; y <= 1; y++) {
			goal.emplace_back(std::make_pair(GOAL_x + x, GOAL_y + y));
		}
	}

	static node_search search;
	search.set_weight_algo(T_Wataru_method);		//重みづけの方法を設定
	search.input_map_data(&mouse::now_map);

	mouse::set_position(0, 0);		//マウスの現在位置を初期位置に
	if (!search.create_small_path(goal, std::pair<uint8_t, uint8_t>(0, 0),
			north))
		return false;
	search.convert_path();

	uint8_t select = select_mode(3 + 1, PHOTO_TYPE::right);

	switch (select) {
	case 0:		//0はメニューに戻る
		return false;
		break;

	case 1: {
		//小回り
		break;
	}
	case 2:
		path::improve_path();
		break;
	case 3: {
		path::improve_advance_path();
		break;
	}
	}

	uint8_t straight = select_mode(RUN_MODE_NUMBER, PHOTO_TYPE::right);
	uint8_t curve = select_mode(3, PHOTO_TYPE::right);

	while (straight != 0) {
		my7seg::blink(8, 500, 1);
		if (photo::check_wall(PHOTO_TYPE::front))
			break;
	}

	mouse::run_init(true, true);
	my7seg::count_down(3, 500);

	//壁に着けた状態からスタート想定
	run::accel_run(0.02 * MOUSE_MODE, 0.5, 1);
	mouse::set_place(0.045, 0.045);		//現在座標の中心位置

	run::path(0, straight, curve);
	//フェイルセーフがかかってなかったら帰りも
	if (!mouse::get_fail_flag()) {
		wait::ms(500);
		run::spin_turn(180);
		mouse::turn_90_dir(MUKI_RIGHT);
		mouse::turn_90_dir(MUKI_RIGHT);
		wait::ms(500);
		if (adachi::adachi_method(0, 0, true)) {
			wait::ms(300);
			MAP_DATA temp;
			map::output_map_data(&temp);
			flash_maze flash_l;
			flash_l.save_maze(0, &temp);
			//flash_l.save_maze(1, &temp);
		}
	}
	motor::sleep_motor();
	return false;

}

mode::mode() {
}

mode::~mode() {

}

void my_queue::reset() {
	head = 0;
	tail = 0;
}

uint16_t my_queue::size() {
	return (head + QUEUE_SIZE - tail) % QUEUE_SIZE;
}

int8_t my_queue::pop() {
	int8_t ans = queue[tail];
	//リング内でtailを1進める
	if (tail + 1 == QUEUE_SIZE)
		tail = 0;
	else
		tail++;
	return ans;
}

void my_queue::push(int8_t _var) {
	queue[head] = _var;		//Queueにぶち込む
	//リング内でheadを1進める
	if (head + 1 == QUEUE_SIZE)
		head = 0;
	else
		head++;
}

int8_t my_queue::front() {
	return queue[tail];		//head=tailだと変な値返すかも
}

my_queue::my_queue() {
	reset();
}

my_queue::~my_queue() {

}

/*
 char log::buf[buf_count] = { 0 };
 uint16_t log::length = 0;
 bool log::available_flag = true;

 bool log::check_put_available(uint16_t put_byte) {
 if (length < (buf_count - put_byte))
 return true;		//まだ書き込める
 else
 return false;
 }

 void log::add_buffer(char* add_buf, uint16_t buf_size) {
 //XXX 追加するのはここからで良いか要検討
 for (uint16_t byte_count = 0; byte_count < buf_size; byte_count++) {
 buf[(length + byte_count)] = add_buf[byte_count];
 }
 }

 int16_t log::put_log(const char* fmt, ...) {
 uint16_t len;
 char temp_buf[100] = { 0 };

 va_list ap;		//可変長引数処理に使用する変数定義
 va_start(ap, fmt);		//可変長引数アクセスのための初期処理
 len = vsprintf(temp_buf, fmt, ap);	// 可変長引数データの書き込み
 va_end(ap);		//可変長引数アクセス後の終了処理
 if (check_put_available(len)) {		//書き込めるなら書き込む
 add_buffer(temp_buf, len);		//全体のbufに追加
 length += len;					//長さを更新
 return len;
 }
 return -1;
 }

 void log::printf_log(void) {
 putnbyte(log::buf, length);		//ログを出力
 if (available_flag) {
 //書き込めるならOK
 } else {
 //書き込みミスったことある状態なら警告
 myprintf("\r\n------------Warning!!----------------\r\n");
 myprintf("\r\nバッファオーバーフローが発生しました！\r\n");
 }
 }

 void log::reset_log(void) {
 for (uint16_t count = 0; count < length; count++) {
 buf[count] = 0;
 }
 length = 0;
 available_flag = true;
 }

 signed int int_log::log_case[2][log_count];
 unsigned int int_log::log_counter;

 void int_log::reset_log() {
 log_counter = log_count;		//リセット中の書き込み対策。
 for (unsigned int i = 0; i < log_count; i++) {
 log_case[0][i] = init_number;
 log_case[1][i] = init_number;
 }
 log_counter = 0;	//カウントを初期化
 }

 void int_log::put_log(const int put_number) {
 if (log_counter >= log_count) {		//LOG_COUNT以上の個数は弾く。それ以上の配列が用意されてないから
 //何もしない
 } else {
 log_case[0][log_counter] = put_number;
 log_counter++;
 }
 }

 void int_log::put_log(const int put_number, const int put_number2) {
 if (log_counter >= log_count) {		//LOG_COUNT以上の個数は弾く。それ以上の配列が用意されてないから
 //何もしない
 } else {
 log_case[0][log_counter] = put_number;
 log_case[1][log_counter] = put_number;
 log_counter++;
 }
 }

 int int_log::get_log(const unsigned int get_number) {
 if (get_number >= log_count) {		//LOG_COUNT以上の個数は弾く。それ以上の配列が用意されてないから
 return init_number;
 } else {
 return log_case[0][get_number];
 }
 }

 int int_log::get_log(const unsigned int ordinal_number,
 const unsigned int get_number) {
 if (get_number >= log_count) {		//LOG_COUNT以上の個数は弾く。それ以上の配列が用意されてないから
 return init_number;
 } else {
 return log_case[ordinal_number][get_number];
 }
 }

 int_log::int_log() {
 init_number = 0;
 log_counter = 0;
 reset_log();
 }

 int_log::int_log(int initialize_number) {
 init_number = initialize_number;
 log_counter = 0;
 reset_log();
 }

 int_log::~int_log() {
 }
 */
/*
 float float_log::log_case[LOG_DIMENSION][LOG_COUNT];
 unsigned int float_log::log_counter;
 float float_log::init_number;

 void float_log::reset_log() {
 log_counter = LOG_COUNT;		//リセット中の書き込み対策。
 for (unsigned int i = 0; i < LOG_COUNT; i++) {
 for (unsigned int j = 0; j < LOG_DIMENSION; j++) {
 log_case[j][i] = init_number;
 }
 }
 log_counter = 0;	//カウントを初期化
 }

 void float_log::put_log(const float put_number_a, const float put_number_b) {
 if (log_counter >= LOG_COUNT) {		//LOG_COUNT以上の個数は弾く。それ以上の配列が用意されてないから
 //何もしない
 } else {
 switch (LOG_DIMENSION) {
 case 1:
 log_case[0][log_counter] = put_number_a;
 break;

 case 2:
 log_case[0][log_counter] = put_number_a;
 log_case[1][log_counter] = put_number_b;
 break;

 }
 log_counter++;
 }
 }

 float float_log::get_log(const unsigned char get_dimension,
 const unsigned int get_number) {
 if (get_dimension >= LOG_DIMENSION) {	//LOG_DIMENSION以上の次元なんてねぇよ！
 return init_number;
 }
 if (get_number >= LOG_COUNT) {		//LOG_COUNT以上の個数は弾く。それ以上の配列が用意されてないから
 return init_number;
 }

 return log_case[get_dimension][get_number];

 }

 float_log::float_log() {
 init_number = 0;
 log_counter = 0;
 reset_log();
 }

 float_log::float_log(float initialize_number) {
 init_number = initialize_number;
 log_counter = 0;
 reset_log();
 }

 float_log::~float_log() {
 }
 */

const float my_math::sin_table[92] = { 0, 0.017452406, 0.034899497, 0.052335956,

0.069756474, 0.087155743, 0.104528463, 0.121869343, 0.139173101, 0.156434465,
		0.173648178, 0.190808995, 0.207911691, 0.224951054, 0.241921896,
		0.258819045, 0.275637356, 0.292371705, 0.309016994, 0.325568154,
		0.342020143, 0.35836795, 0.374606593, 0.390731128, 0.406736643,
		0.422618262, 0.438371147, 0.4539905, 0.469471563, 0.48480962, 0.5,
		0.515038075, 0.529919264, 0.544639035, 0.559192903, 0.573576436,
		0.587785252, 0.601815023, 0.615661475, 0.629320391, 0.64278761,
		0.656059029, 0.669130606, 0.68199836, 0.69465837, 0.707106781,
		0.7193398, 0.731353702, 0.743144825, 0.75470958, 0.766044443,
		0.777145961, 0.788010754, 0.79863551, 0.809016994, 0.819152044,
		0.829037573, 0.838670568, 0.848048096, 0.857167301, 0.866025404,
		0.874619707, 0.882947593, 0.891006524, 0.898794046, 0.906307787,
		0.913545458, 0.920504853, 0.927183855, 0.933580426, 0.939692621,
		0.945518576, 0.951056516, 0.956304756, 0.961261696, 0.965925826,
		0.970295726, 0.974370065, 0.978147601, 0.981627183, 0.984807753,
		0.987688341, 0.990268069, 0.992546152, 0.994521895, 0.996194698,
		0.99756405, 0.998629535, 0.999390827, 0.999847695, 1, 0.999847695 };

const float my_math::log_table[LOG_N + 1] = { -2.30259, -2.30159, -2.3006,
		-2.29961, -2.29862, -2.29762, -2.29663, -2.29563, -2.29463, -2.29364,
		-2.29264, -2.29164, -2.29063, -2.28963, -2.28863, -2.28762, -2.28662,
		-2.28561, -2.2846, -2.2836, -2.28259, -2.28158, -2.28056, -2.27955,
		-2.27854, -2.27752, -2.27651, -2.27549, -2.27447, -2.27345, -2.27244,
		-2.27141, -2.27039, -2.26937, -2.26835, -2.26732, -2.26629, -2.26527,
		-2.26424, -2.26321, -2.26218, -2.26115, -2.26012, -2.25908, -2.25805,
		-2.25701, -2.25598, -2.25494, -2.2539, -2.25286, -2.25182, -2.25078,
		-2.24973, -2.24869, -2.24764, -2.2466, -2.24555, -2.2445, -2.24345,
		-2.2424, -2.24135, -2.24029, -2.23924, -2.23819, -2.23713, -2.23607,
		-2.23501, -2.23395, -2.23289, -2.23183, -2.23077, -2.2297, -2.22864,
		-2.22757, -2.2265, -2.22543, -2.22436, -2.22329, -2.22222, -2.22115,
		-2.22007, -2.219, -2.21792, -2.21684, -2.21576, -2.21468, -2.2136,
		-2.21252, -2.21143, -2.21035, -2.20926, -2.20818, -2.20709, -2.206,
		-2.20491, -2.20381, -2.20272, -2.20163, -2.20053, -2.19943, -2.19834,
		-2.19724, -2.19614, -2.19503, -2.19393, -2.19283, -2.19172, -2.19061,
		-2.18951, -2.1884, -2.18729, -2.18617, -2.18506, -2.18395, -2.18283,
		-2.18172, -2.1806, -2.17948, -2.17836, -2.17724, -2.17611, -2.17499,
		-2.17386, -2.17274, -2.17161, -2.17048, -2.16935, -2.16822, -2.16709,
		-2.16595, -2.16482, -2.16368, -2.16254, -2.1614, -2.16026, -2.15912,
		-2.15798, -2.15683, -2.15568, -2.15454, -2.15339, -2.15224, -2.15109,
		-2.14993, -2.14878, -2.14763, -2.14647, -2.14531, -2.14415, -2.14299,
		-2.14183, -2.14067, -2.1395, -2.13834, -2.13717, -2.136, -2.13483,
		-2.13366, -2.13248, -2.13131, -2.13013, -2.12896, -2.12778, -2.1266,
		-2.12542, -2.12424, -2.12305, -2.12187, -2.12068, -2.11949, -2.1183,
		-2.11711, -2.11592, -2.11472, -2.11353, -2.11233, -2.11113, -2.10993,
		-2.10873, -2.10753, -2.10633, -2.10512, -2.10391, -2.10271, -2.1015,
		-2.10029, -2.09907, -2.09786, -2.09664, -2.09543, -2.09421, -2.09299,
		-2.09177, -2.09054, -2.08932, -2.08809, -2.08686, -2.08563, -2.0844,
		-2.08317, -2.08194, -2.0807, -2.07947, -2.07823, -2.07699, -2.07575,
		-2.0745, -2.07326, -2.07201, -2.07077, -2.06952, -2.06827, -2.06701,
		-2.06576, -2.06451, -2.06325, -2.06199, -2.06073, -2.05947, -2.05821,
		-2.05694, -2.05567, -2.05441, -2.05314, -2.05186, -2.05059, -2.04932,
		-2.04804, -2.04676, -2.04548, -2.0442, -2.04292, -2.04164, -2.04035,
		-2.03906, -2.03777, -2.03648, -2.03519, -2.03389, -2.0326, -2.0313,
		-2.03, -2.0287, -2.0274, -2.02609, -2.02479, -2.02348, -2.02217,
		-2.02086, -2.01955, -2.01823, -2.01691, -2.0156, -2.01428, -2.01295,
		-2.01163, -2.01031, -2.00898, -2.00765, -2.00632, -2.00499, -2.00365,
		-2.00232, -2.00098, -1.99964, -1.9983, -1.99696, -1.99561, -1.99426,
		-1.99292, -1.99157, -1.99021, -1.98886, -1.9875, -1.98615, -1.98479,
		-1.98343, -1.98206, -1.9807, -1.97933, -1.97796, -1.97659, -1.97522,
		-1.97384, -1.97247, -1.97109, -1.96971, -1.96833, -1.96694, -1.96556,
		-1.96417, -1.96278, -1.96139, -1.96, -1.9586, -1.9572, -1.9558, -1.9544,
		-1.953, -1.95159, -1.95019, -1.94878, -1.94737, -1.94595, -1.94454,
		-1.94312, -1.9417, -1.94028, -1.93886, -1.93743, -1.936, -1.93457,
		-1.93314, -1.93171, -1.93027, -1.92884, -1.9274, -1.92596, -1.92451,
		-1.92307, -1.92162, -1.92017, -1.91872, -1.91726, -1.9158, -1.91435,
		-1.91289, -1.91142, -1.90996, -1.90849, -1.90702, -1.90555, -1.90408,
		-1.9026, -1.90112, -1.89964, -1.89816, -1.89667, -1.89519, -1.8937,
		-1.89221, -1.89071, -1.88922, -1.88772, -1.88622, -1.88472, -1.88321,
		-1.88171, -1.8802, -1.87869, -1.87717, -1.87566, -1.87414, -1.87262,
		-1.87109, -1.86957, -1.86804, -1.86651, -1.86498, -1.86344, -1.86191,
		-1.86037, -1.85883, -1.85728, -1.85574, -1.85419, -1.85264, -1.85108,
		-1.84953, -1.84797, -1.84641, -1.84484, -1.84328, -1.84171, -1.84014,
		-1.83856, -1.83699, -1.83541, -1.83383, -1.83225, -1.83066, -1.82907,
		-1.82748, -1.82589, -1.82429, -1.82269, -1.82109, -1.81949, -1.81788,
		-1.81627, -1.81466, -1.81305, -1.81143, -1.80981, -1.80819, -1.80657,
		-1.80494, -1.80331, -1.80168, -1.80004, -1.7984, -1.79676, -1.79512,
		-1.79347, -1.79183, -1.79017, -1.78852, -1.78686, -1.7852, -1.78354,
		-1.78188, -1.78021, -1.77854, -1.77687, -1.77519, -1.77351, -1.77183,
		-1.77014, -1.76846, -1.76677, -1.76507, -1.76338, -1.76168, -1.75998,
		-1.75827, -1.75656, -1.75485, -1.75314, -1.75142, -1.7497, -1.74798,
		-1.74626, -1.74453, -1.7428, -1.74106, -1.73933, -1.73758, -1.73584,
		-1.7341, -1.73235, -1.73059, -1.72884, -1.72708, -1.72532, -1.72355,
		-1.72178, -1.72001, -1.71824, -1.71646, -1.71468, -1.7129, -1.71111,
		-1.70932, -1.70753, -1.70573, -1.70393, -1.70213, -1.70032, -1.69851,
		-1.6967, -1.69488, -1.69306, -1.69124, -1.68941, -1.68758, -1.68575,
		-1.68391, -1.68207, -1.68023, -1.67839, -1.67654, -1.67468, -1.67283,
		-1.67097, -1.6691, -1.66724, -1.66536, -1.66349, -1.66161, -1.65973,
		-1.65785, -1.65596, -1.65407, -1.65217, -1.65027, -1.64837, -1.64646,
		-1.64455, -1.64264, -1.64072, -1.6388, -1.63688, -1.63495, -1.63302,
		-1.63108, -1.62914, -1.6272, -1.62525, -1.6233, -1.62135, -1.61939,
		-1.61743, -1.61546, -1.61349, -1.61152, -1.60954, -1.60756, -1.60557,
		-1.60358, -1.60159, -1.59959, -1.59759, -1.59558, -1.59357, -1.59156,
		-1.58954, -1.58752, -1.58549, -1.58346, -1.58143, -1.57939, -1.57735,
		-1.5753, -1.57325, -1.5712, -1.56914, -1.56707, -1.56501, -1.56293,
		-1.56086, -1.55878, -1.55669, -1.5546, -1.55251, -1.55041, -1.54831,
		-1.5462, -1.54409, -1.54197, -1.53985, -1.53773, -1.5356, -1.53346,
		-1.53133, -1.52918, -1.52703, -1.52488, -1.52272, -1.52056, -1.5184,
		-1.51623, -1.51405, -1.51187, -1.50968, -1.50749, -1.5053, -1.5031,
		-1.50089, -1.49869, -1.49647, -1.49425, -1.49203, -1.4898, -1.48756,
		-1.48532, -1.48308, -1.48083, -1.47858, -1.47632, -1.47405, -1.47178,
		-1.46951, -1.46723, -1.46494, -1.46265, -1.46036, -1.45806, -1.45575,
		-1.45344, -1.45112, -1.4488, -1.44647, -1.44414, -1.4418, -1.43946,
		-1.43711, -1.43475, -1.43239, -1.43002, -1.42765, -1.42527, -1.42289,
		-1.4205, -1.41811, -1.41571, -1.4133, -1.41089, -1.40847, -1.40605,
		-1.40362, -1.40118, -1.39874, -1.39629, -1.39384, -1.39138, -1.38892,
		-1.38644, -1.38397, -1.38148, -1.37899, -1.3765, -1.37399, -1.37149,
		-1.36897, -1.36645, -1.36392, -1.36139, -1.35885, -1.3563, -1.35375,
		-1.35119, -1.34862, -1.34605, -1.34347, -1.34088, -1.33829, -1.33569,
		-1.33308, -1.33046, -1.32784, -1.32522, -1.32258, -1.31994, -1.31729,
		-1.31464, -1.31197, -1.30931, -1.30663, -1.30394, -1.30125, -1.29856,
		-1.29585, -1.29314, -1.29042, -1.28769, -1.28495, -1.28221, -1.27946,
		-1.2767, -1.27394, -1.27116, -1.26838, -1.26559, -1.2628, -1.25999,
		-1.25718, -1.25436, -1.25153, -1.2487, -1.24585, -1.243, -1.24014,
		-1.23727, -1.2344, -1.23151, -1.22862, -1.22571, -1.2228, -1.21989,
		-1.21696, -1.21402, -1.21108, -1.20812, -1.20516, -1.20219, -1.19921,
		-1.19622, -1.19323, -1.19022, -1.1872, -1.18418, -1.18114, -1.1781,
		-1.17505, -1.17199, -1.16892, -1.16583, -1.16274, -1.15964, -1.15654,
		-1.15342, -1.15029, -1.14715, -1.144, -1.14084, -1.13767, -1.13449,
		-1.13131, -1.12811, -1.1249, -1.12168, -1.11845, -1.11521, -1.11196,
		-1.10869, -1.10542, -1.10214, -1.09885, -1.09554, -1.09223, -1.0889,
		-1.08556, -1.08221, -1.07885, -1.07548, -1.0721, -1.0687, -1.0653,
		-1.06188, -1.05845, -1.05501, -1.05156, -1.04809, -1.04461, -1.04112,
		-1.03762, -1.03411, -1.03058, -1.02704, -1.02349, -1.01993, -1.01635,
		-1.01276, -1.00916, -1.00555, -1.00192, -0.998276, -0.994621, -0.990953,
		-0.987271, -0.983575, -0.979866, -0.976143, -0.972406, -0.968655,
		-0.96489, -0.961111, -0.957318, -0.953509, -0.949687, -0.94585,
		-0.941997, -0.93813, -0.934249, -0.930351, -0.926439, -0.922511,
		-0.918568, -0.914609, -0.910635, -0.906644, -0.902638, -0.898615,
		-0.894577, -0.890522, -0.88645, -0.882362, -0.878257, -0.874135,
		-0.869995, -0.865839, -0.861666, -0.857474, -0.853266, -0.849039,
		-0.844795, -0.840532, -0.836251, -0.831952, -0.827634, -0.823298,
		-0.818942, -0.814568, -0.810174, -0.805761, -0.801329, -0.796876,
		-0.792404, -0.787912, -0.783399, -0.778866, -0.774312, -0.769738,
		-0.765142, -0.760525, -0.755887, -0.751227, -0.746546, -0.741842,
		-0.737116, -0.732368, -0.727597, -0.722803, -0.717986, -0.713146,
		-0.708282, -0.703394, -0.698483, -0.693547, -0.688587, -0.683602,
		-0.678592, -0.673557, -0.668496, -0.663409, -0.658297, -0.653158,
		-0.647993, -0.642801, -0.637582, -0.632335, -0.627061, -0.621759,
		-0.616428, -0.611069, -0.605681, -0.600264, -0.594817, -0.589341,
		-0.583834, -0.578297, -0.572729, -0.56713, -0.5615, -0.555837,
		-0.550142, -0.544415, -0.538655, -0.532861, -0.527034, -0.521172,
		-0.515276, -0.509345, -0.503378, -0.497376, -0.491337, -0.485262,
		-0.479149, -0.472999, -0.466811, -0.460584, -0.454319, -0.448014,
		-0.441668, -0.435283, -0.428856, -0.422388, -0.415877, -0.409324,
		-0.402728, -0.396088, -0.389403, -0.382674, -0.375899, -0.369078,
		-0.36221, -0.355294, -0.34833, -0.341318, -0.334255, -0.327143,
		-0.31998, -0.312765, -0.305497, -0.298177, -0.290802, -0.283373,
		-0.275888, -0.268346, -0.260748, -0.253091, -0.245375, -0.237599,
		-0.229762, -0.221863, -0.213901, -0.205875, -0.197785, -0.189628,
		-0.181404, -0.173113, -0.164751, -0.15632, -0.147816, -0.13924,
		-0.13059, -0.121864, -0.113061, -0.10418, -0.0952193, -0.0861777,
		-0.0770536, -0.0678455, -0.0585519, -0.049171, -0.0397014, -0.0301412,
		-0.0204887, -0.0107421, -0.000899595, 0.00904074, 0.0190809, 0.0292229,
		0.0394687, 0.0498207, 0.0602809, 0.0708517, 0.0815355, 0.0923346,
		0.103252, 0.114289, 0.12545, 0.136737, 0.148152, 0.159699, 0.171382,
		0.183202, 0.195164, 0.20727, 0.219525, 0.231932, 0.244495, 0.257218,
		0.270104, 0.283159, 0.296387, 0.309791, 0.323378, 0.337152, 0.351119,
		0.365283, 0.379651, 0.394228, 0.409021, 0.424036, 0.43928, 0.45476,
		0.470484, 0.486458, 0.502692, 0.519194, 0.535973, 0.553037, 0.570399,
		0.588067, 0.606052, 0.624368, 0.643025, 0.662036, 0.681416, 0.701179,
		0.721341, 0.741917, 0.762926, 0.784386, 0.806316, 0.828738, 0.851674,
		0.875149, 0.899188, 0.923819, 0.949072, 0.97498, 1.00158, 1.0289,
		1.05699, 1.08589, 1.11566, 1.14633, 1.17798, 1.21066, 1.24445, 1.27941,
		1.31565, 1.35325, 1.39231, 1.43297, 1.47534, 1.5196, 1.5659, 1.61445,
		1.66548, 1.71925, 1.77608, 1.83634, 1.90046, 1.96897, 2.04253, 2.12193,
		2.20818, 2.30259 };

float my_math::sin(const float radian) {
	float temp_radian = radian;
	float temp_degree;
	uint16_t degree_index;
	float answer = 0, answer_sign = 1;

	//-π ~ π の間に落とし込む
	while (ABS(temp_radian) > PI()) {
		temp_radian -= (SIGN(radian) * 2 * PI());
	}

	temp_degree = degree(temp_radian);
	if (temp_degree < 0) {
//角度を反転し、符号を覚えておく
		temp_degree = -temp_degree;
		answer_sign = -1;
	}

	if (temp_degree > 90) {
		temp_degree = 180 - temp_degree;

	}
	degree_index = static_cast<uint16_t>(temp_degree);//charになる時に小数点以下は切り捨てられるはず
	answer = sin_table[degree_index];	//テーブルの内、目的の値に近い奴を入れる
	//線形近似
	answer += (temp_degree - degree_index)
			* (sin_table[degree_index + 1] - sin_table[degree_index]);

	return (answer * answer_sign);
}

float my_math::cos(const float radian) {
	return sin(radian + PI() / 2);
}

float my_math::log(float x) {
	//0.1<x<10 にしか対応していない！
	if (x < 0.1)
		return log_table[0];
	if (x > 10)
		return log_table[LOG_N];

	static float c = LOG_N / 9.9;	//配列のindexを求めるための定数

	//配列の要素番号を計算
	float index = c * (10 - 1 / x);
	uint16_t index_int = static_cast<uint16_t>(index);

	//大丈夫なはずだけど念のため、例外をはじく
	if (index_int < 0)
		return log_table[0];
	if (index_int > LOG_N)
		return log_table[LOG_N];

	//my7seg::light(7);

	//テーブルから線形近似でlogXを求める
	float log_x = log_table[index_int]
			+ (index - index_int)
					* (log_table[index_int + 1] - log_table[index_int]);

	return log_x;
}

float my_math::sqrt(float x) {
	float ans = x / 2;	//初期値は適当にa/2
	for (int i = 0; i < 10; i++) {
		ans = ans - (ans * ans - x) / (2 * ans);
	}
	return ABS(ans);
}
