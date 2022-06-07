/*
* Copyright (C) 2022 Jakub Górecki - All Right Reserved.
* Gmail: jakub.xiz1.gorecki@gmail.com
* GitHub: https://github.com/XiZ1
*/

#pragma once

#include "TicTacToe.h"
#include <vector>

class c_leaderboard
{
public:

	void show_leaderboard();
	void save_match_results(const string& winner, const string& loser);
	void save_remiss_match_results(const string& remiss_one, const string& remiss_two);

private:

	std::vector<string> leaderboard_;
	string part_of_leaderboard_;
	int all_match_ = 0, win_match_ = 0, remiss_match_ = 0, loose_match_ = 0, win_loose_ratio_ = 0, score_ = 0;

	bool download_leaderboard();

};
