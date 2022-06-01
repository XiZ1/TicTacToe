/*
* Copyright (C) 2022 Jakub Górecki - All Right Reserved.
* Gmail: jakub.xiz1.gorecki@gmail.com
* GitHub: https://github.com/XiZ1
*/

#pragma once

#include <iostream>

using std::cout;
using std::cin;
using std::string;

class c_game
{
public:

	c_game(const int, const int, const bool, const bool);

private:

	int max_round_ = 0, round_need_to_win_ = 0;
	bool set_name_ = false, save_score_ = false;

	static int set_max_round();
	static int set_round_need_to_win();

};

