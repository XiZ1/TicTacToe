/*
* Copyright (C) 2022 Jakub Górecki - All Right Reserved.
* Gmail: jakub.xiz1.gorecki@gmail.com
* GitHub: https://github.com/XiZ1
*/

// ReSharper disable CppClangTidyModernizeUseNodiscard

#pragma once

#include <vector>
#include <string>
#include <cmath>
#include "TicTacToe.h"

using std::to_string;

class c_leaderboard
{
public:

	void show_leaderboard();
	void save_match_results(const string& player_one, const int& flag_player_one, const string& player_two, const int& flag_player_two);

private:

	std::vector<string> leaderboard_;
	std::vector<int> vector_score_;

	string field_of_leaderboard_;
	int field_number_ = 0, all_match_ = 0, win_match_ = 0, remiss_match_ = 0, loose_match_ = 0, score_ = 0;
	double win_loose_ratio_ = 0;

	enum flags { WIN = 0, REMISS = 1, LOOSE = 2 };

	bool download_leaderboard();
	void upload_leaderboard() const;
	bool is_user_exist(const string& user_nick_name);
	void update_user_stats(const string& user_nick_name, const int& flag);
	void add_user_stats(const string& user_nick_name, const int& flag);
	void get_user_statistic(const string& player_name);
	void create_new_user_stats(const int& all, const int& win, const int& remiss, const int& loose);
	void create_field_of_leaderboard(const string& user_nick_name);
	void win_loose_ratio();
	void score();
	void get_score();
	void sorting_leaderboard();

};

inline void c_leaderboard::create_new_user_stats(const int& all, const int& win, const int& remiss, const int& loose)
{
	all_match_ = all;
	win_match_ = win;
	remiss_match_ = remiss;
	loose_match_ = loose;
}

inline void c_leaderboard::create_field_of_leaderboard(const string& user_nick_name)
{
	field_of_leaderboard_ = user_nick_name + '\t' + to_string(all_match_) + '\t' + to_string(win_match_) + '\t' + to_string(remiss_match_) + '\t' + to_string(loose_match_) + '\t' + to_string(win_loose_ratio_) + '\t' + to_string(score_);
}

inline void c_leaderboard::win_loose_ratio()
{
	if(loose_match_ == 0)
	{
		win_loose_ratio_ = static_cast<double>(win_match_ + remiss_match_);
	}
	win_loose_ratio_ = static_cast<double>(win_match_ + remiss_match_) / loose_match_;
	win_loose_ratio_ = round(win_loose_ratio_ * 100.0) / 100.0;
}

inline void c_leaderboard::score()
{
	score_ = static_cast<int>(((win_loose_ratio_ * 0.75) * (all_match_ * 0.25)) * 10000);
}
