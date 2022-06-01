/*
* Copyright (C) 2022 Jakub Górecki - All Right Reserved.
* Gmail: jakub.xiz1.gorecki@gmail.com
* GitHub: https://github.com/XiZ1
*/

#include "game.h"


/*
 * PUBLIC:
 */


c_game::c_game(const int round, const int win, const bool name, const bool score)
{
	max_round_ = round;
	round_need_to_win_ = win;
	set_name_ = name;
	save_score_ = score;
	if (max_round_ == -1)
	{
		set_max_round();
	}
	if (round_need_to_win_ == -1)
	{
		set_round_need_to_win();
	}
	if(set_name_)
	{
		set_name();
	}
}


/*
 * PRIVATE:
 */


int c_game::set_max_round()
{
	int how_many_rounds = -1;
	cin >> how_many_rounds;
	return how_many_rounds;
}

int c_game::set_round_need_to_win()
{
	int how_many_rounds_need_to_win = -1;
	cin >> how_many_rounds_need_to_win;
	return how_many_rounds_need_to_win;
}

void c_game::set_name()
{
	cin >> name_player_one;
	cin >> name_player_two;
}
