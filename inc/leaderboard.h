/*
* Copyright (C) 2022 Jakub Górecki - All Right Reserved.
* Gmail: jakub.xiz1.gorecki@gmail.com
* GitHub: https://github.com/XiZ1
*/

// ReSharper disable CppClangTidyModernizeUseNodiscard

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
	double all_match_ = 0, win_match_ = 0, remiss_match_ = 0, loose_match_ = 0, win_loose_ratio_ = 0, score_ = 0;
	enum flags { WIN, LOOSE, REMISS };

	bool download_leaderboard();
	bool is_user_exist(const string& user_nick_name) const;
	void update_user_stats(const string& user_nick_name, const int& flag);
	void add_user(const string& user_nick_name, const int& flag);
	double win_loose_ratio() const;
	double score() const;
	bool save_leaderboard() const;

};
