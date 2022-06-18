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
		for (size_t i = 0; i < leaderboard_.size(); i++)
		{
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
		download_leaderboard << i;
	}
	download_leaderboard.close();
}

bool c_leaderboard::is_user_exist(const string& user_nick_name)
{
	for (size_t i = 0; i < leaderboard_.size(); i++)
	{
		if (leaderboard_[i].find(user_nick_name))
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

void c_leaderboard::get_user_statistic(const string& player_name) //REWORK
{
	field_of_leaderboard_ = leaderboard_[field_number_];
	const auto player_name_length = player_name.length();
	field_of_leaderboard_.erase(0, player_name_length + 4);
	string temp_string[6];
	int j = 0;

	for (size_t i = 0; i < field_of_leaderboard_.size(); i++)
	{
		if (std::isdigit(field_of_leaderboard_[i]))
		{
			temp_string[j] += field_of_leaderboard_[i];
		}
		else
		{
			field_of_leaderboard_.erase(i, i + 4);
			j++;
		}
	}
	for (auto i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
			{
				all_match_ = std::stod(temp_string[i]);
			}break;
		case 1:
			{
				win_match_ = std::stod(temp_string[i]);
			}break;
		case 2:
			{
				remiss_match_ = std::stod(temp_string[i]);
			}break;
		case 3:
			{
				loose_match_ = std::stod(temp_string[i]);
			}break;
		default:
			{
				NULL;
			}break;
		}
	}
}

void c_leaderboard::get_score()
{
	for (const auto& i : leaderboard_)
	{
		field_of_leaderboard_ = i;
		const size_t found = field_of_leaderboard_.find_last_of(' ');
		field_of_leaderboard_.erase(0, found + 4);
		vector_score_.push_back(std::stod(field_of_leaderboard_));
	}
}

void c_leaderboard::sorting_leaderboard()
{
	get_score();
	for (size_t i = 0; i < vector_score_.size(); i++)
	{
		for (size_t j = 0; j < vector_score_.size() - 1; j++)
		{
			if (vector_score_[j] > vector_score_[j + 1])
			{
				std::swap(vector_score_[j], vector_score_[j + 1]);
				std::swap(leaderboard_[j], leaderboard_[j + 1]);
			}
		}
	}
}
