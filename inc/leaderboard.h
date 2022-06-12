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
	void save_match_results(const string& player_one, const int flag_player_one, const string& player_two, const int flag_player_two);

private:

	std::vector<string> leaderboard_;

	string part_of_leaderboard_;
	int field_number_;

	double all_match_, win_match_, remiss_match_, loose_match_, win_loose_ratio_, score_;

	enum match_result_flags { WIN = 0, REMISS = 1, LOOSE = 2 };

	bool download_leaderboard();
	bool is_user_exist(const string& user_nick_name);
	void update_user_stats(const string& user_nick_name, const int& flag);
	void add_user(const string& user_nick_name, const int& flag);
	void cut_part_of_leaderboard(const string& player_name);
	void win_loose_ratio();
	void score();
	bool save_leaderboard();

};
