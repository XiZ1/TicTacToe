/*
* Copyright (C) 2022 Jakub Górecki - All Right Reserved.
* Gmail: jakub.xiz1.gorecki@gmail.com
* GitHub: https://github.com/XiZ1
*/

#include "leaderboard.h"
#include <fstream>


/*
 * PUBLIC:
 */


void c_leaderboard::show_leaderboard()
{
	if(download_leaderboard())
	{
		c_tictactoe::clear_screen();
		c_tictactoe::show_message("\t\tLEADERBOARD!\n\n\n");
		c_tictactoe::show_message("NICK_NAME  ALL_MATCH  WIN_MATCH  REMISS_MATCH  LOOSE_MATCH  WIN_LOOSE_RATIO  SCORE\n");
		for (size_t i = 0; i < leaderboard_.size(); i++)
		{
			c_tictactoe::show_message("==================================================================================\n");
			cout << i+1 << ". " << leaderboard_[i] << '\n';
		}
		cout << '\n';
	}
	else
	{
		c_tictactoe::clear_screen();
		c_tictactoe::show_message("ERROR! LEADERBOARD IS EMPTY!\n");
	}
	system("pause");
}

void c_leaderboard::save_match_results(const string& player_one, const int& flag_player_one, const string& player_two, const int& flag_player_two)
{
	const string tab_user_name[2] = { player_one, player_two };
	const int tab_flags[2] = { flag_player_one, flag_player_two };
	download_leaderboard();
	for (auto i = 0; i < 2; i++)
	{
		if (is_user_exist(tab_user_name[i]))
		{
			update_user_stats(tab_user_name[i], tab_flags[i]);
		}
		else
		{
			add_user_stats(tab_user_name[i], tab_flags[i]);
		}
	}
	sorting_leaderboard();
	upload_leaderboard();
}


/*
 * PRIVATE:
 */


bool c_leaderboard::download_leaderboard()
{
	std::ifstream download_leaderboard;
	download_leaderboard.open("date_base\\leaderboard.txt");
	if (download_leaderboard.bad())
	{
		return false;
	}
	while (std::getline(download_leaderboard, field_of_leaderboard_))
	{
		leaderboard_.push_back(field_of_leaderboard_);
	}
	download_leaderboard.close();
	return true;
}

void c_leaderboard::upload_leaderboard() const
{
	std::ofstream download_leaderboard;
	download_leaderboard.open("date_base\\leaderboard.txt");
	for (const auto& i : leaderboard_)
	{
		download_leaderboard << i << '\n';
	}
	download_leaderboard.close();
}

bool c_leaderboard::is_user_exist(const string& user_nick_name)
{
	for (size_t i = 0; i < leaderboard_.size(); i++)
	{
		if (leaderboard_[i].find(user_nick_name) != string::npos)
		{
			field_number_ = static_cast<int>(i);
			return true;
		}
	}
	return false;
}

void c_leaderboard::update_user_stats(const string& user_nick_name, const int& flag)
{
	switch (flag)
	{
	case WIN:
		{
			get_user_statistic(user_nick_name);
			all_match_++;
			win_match_++;
			win_loose_ratio();
			score();
			create_field_of_leaderboard(user_nick_name);
			leaderboard_[field_number_] = field_of_leaderboard_;
		}break;
	case REMISS:
		{
			get_user_statistic(user_nick_name);
			all_match_++;
			remiss_match_++;
			win_loose_ratio();
			score();
			create_field_of_leaderboard(user_nick_name);
			leaderboard_[field_number_] = field_of_leaderboard_;
		}break;
	case LOOSE:
		{
			get_user_statistic(user_nick_name);
			all_match_++;
			loose_match_++;
			win_loose_ratio();
			score();
			create_field_of_leaderboard(user_nick_name);
			leaderboard_[field_number_] = field_of_leaderboard_;
		}break;
	default:
		{
			NULL;
		}break;
	}
}

void c_leaderboard::add_user_stats(const string& user_nick_name, const int& flag)
{
	switch (flag)
	{
	case WIN:
		{
			create_new_user_stats(1, 1, 0, 0);
			win_loose_ratio();
			score();
			create_field_of_leaderboard(user_nick_name);
			leaderboard_.push_back(field_of_leaderboard_);
		}break;
	case REMISS:
		{
			create_new_user_stats(1, 0, 1, 0);
			win_loose_ratio();
			score();
			create_field_of_leaderboard(user_nick_name);
			leaderboard_.push_back(field_of_leaderboard_);
		}break;
	case LOOSE:
		{
			create_new_user_stats(1, 0, 0, 1);
			win_loose_ratio();
			score();
			create_field_of_leaderboard(user_nick_name);
			leaderboard_.push_back(field_of_leaderboard_);
		}break;
	default:
		{
			NULL;
		}break;
	}
}

void c_leaderboard::get_user_statistic(const string& player_name)
{
	field_of_leaderboard_ = leaderboard_[field_number_];
	const auto player_name_length = player_name.length() + 2;
	string temp_string[4];
	int j = 0;

	for (auto i = player_name_length; i < field_of_leaderboard_.size(); i++)
	{
		if (j == 4)
		{
			break;
		}
		if (std::isdigit(field_of_leaderboard_[i]))
		{
			temp_string[j] += field_of_leaderboard_[i];
		}
		else
		{
			j++;
		}
	}
	all_match_ = std::stoi(temp_string[0]);
	win_match_ = std::stoi(temp_string[1]);
	remiss_match_ = std::stoi(temp_string[2]);
	loose_match_ = std::stoi(temp_string[3]);
}

void c_leaderboard::get_score()
{
	for (const auto& i : leaderboard_)
	{
		field_of_leaderboard_ = i;
		const size_t found = field_of_leaderboard_.find_last_of('\t');
		field_of_leaderboard_.erase(0, found + 1);
		vector_score_.push_back(std::stoi(field_of_leaderboard_));
	}
}

void c_leaderboard::sorting_leaderboard()
{
	get_score();
	for (size_t i = 0; i < vector_score_.size(); i++)
	{
		for (size_t j = 0; j < vector_score_.size() - 1; j++)
		{
			if (vector_score_[j] < vector_score_[j + 1])
			{
				std::swap(vector_score_[j], vector_score_[j + 1]);
				std::swap(leaderboard_[j], leaderboard_[j + 1]);
			}
		}
	}
}
