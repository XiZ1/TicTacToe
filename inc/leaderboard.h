/*
* Copyright (C) 2022 Jakub Górecki - All Right Reserved.
* Gmail: jakub.xiz1.gorecki@gmail.com
* GitHub: https://github.com/XiZ1
*/

#pragma once

#include "tictactoe.h"

class c_leaderboard
{
public:

	void show_top_10_leaderboard();
	void save_match_results(const string& winner, const string& loser);
	void save_remiss_match_results(const string& remiss_one, const string& remiss_two);

private:



};
