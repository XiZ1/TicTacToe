/*
* Copyright (C) 2022 Jakub Górecki - All Right Reserved.
* Gmail: jakub.xiz1.gorecki@gmail.com
* GitHub: https://github.com/XiZ1
*/

#include "leaderboard.h"
#include <fstream>
#include <string>

using std::stringstream;
using std::to_string;

/*
 * PUBLIC:
 */


void c_leaderboard::show_leaderboard()
{
	if(download_leaderboard())
	{
		c_tictactoe::clear_screen();
		c_tictactoe::show_message("\t\tLEADERBOARD!\n\n\n");
		for (auto i = 0; i < leaderboard_.size(); i++)
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

void c_leaderboard::save_match_results(const string& player_one, const int flag_player_one, const string& player_two, const int flag_player_two)
{
	if (download_leaderboard())
	{
		const string tab_user_name[2] = { player_one, player_two };
		const int tab_flags[2] = { flag_player_one, flag_player_two };
		for (auto i = 0; i < 2; i++)
		{
			if (is_user_exist(tab_user_name[i]))
			{
				update_user_stats(tab_user_name[i], tab_flags[i]);
			}
			else
			{
				add_user(tab_user_name[i], tab_flags[i]);
			}
		}
		//TODO sort leaderboard
		save_leaderboard();
	}
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
	while (std::getline(download_leaderboard, part_of_leaderboard_))
	{
		leaderboard_.push_back(part_of_leaderboard_);
	}
	download_leaderboard.close();
	return true;
}

bool c_leaderboard::is_user_exist(const string& user_nick_name)
{
	for (auto i = 0; i < leaderboard_.size(); i++)
	{
		if (leaderboard_[i].find(user_nick_name))
		{
			field_number_ = i;
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
			part_of_leaderboard_ = leaderboard_[field_number_];
			cut_part_of_leaderboard(user_nick_name);
			all_match_++;
			win_match_++;
			win_loose_ratio();
			score();
			part_of_leaderboard_ = user_nick_name + '\t' + to_string(all_match_) + '\t' + to_string(win_match_) + '\t' + to_string(remiss_match_) + '\t' + to_string(loose_match_) + '\t' + to_string(win_loose_ratio_) + '\t' + to_string(score_);
			leaderboard_[field_number_] = part_of_leaderboard_;
		}break;

		case REMISS:
		{
			part_of_leaderboard_ = leaderboard_[field_number_];
			cut_part_of_leaderboard(user_nick_name);
			all_match_++;
			remiss_match_++;
			win_loose_ratio();
			score();
			part_of_leaderboard_ = user_nick_name + '\t' + to_string(all_match_) + '\t' + to_string(win_match_) + '\t' + to_string(remiss_match_) + '\t' + to_string(loose_match_) + '\t' + to_string(win_loose_ratio_) + '\t' + to_string(score_);
			leaderboard_[field_number_] = part_of_leaderboard_;
		}break;

		case LOOSE:
		{
			part_of_leaderboard_ = leaderboard_[field_number_];
			cut_part_of_leaderboard(user_nick_name);
			all_match_++;
			loose_match_++;
			win_loose_ratio();
			score();
			part_of_leaderboard_ = user_nick_name + '\t' + to_string(all_match_) + '\t' + to_string(win_match_) + '\t' + to_string(remiss_match_) + '\t' + to_string(loose_match_) + '\t' + to_string(win_loose_ratio_) + '\t' + to_string(score_);
			leaderboard_[field_number_] = part_of_leaderboard_;
		}break;

		default:
		{
			NULL;
		}break;
	}
}

void c_leaderboard::add_user(const string& user_nick_name, const int& flag)
{
	switch (flag)
	{
		case WIN:
		{
			all_match_ = 1;
			win_match_ = 1;
			remiss_match_ = 0;
			loose_match_ = 0;
			win_loose_ratio();
			score();
			part_of_leaderboard_ = user_nick_name + '\t' + to_string(all_match_) + '\t' + to_string(win_match_) + '\t' + to_string(remiss_match_) + '\t' + to_string(loose_match_) + '\t' + to_string(win_loose_ratio_) + '\t' + to_string(score_);
			leaderboard_.push_back(part_of_leaderboard_);
		}break;

		case REMISS:
		{
			all_match_ = 1;
			win_match_ = 0;
			remiss_match_ = 1;
			loose_match_ = 0;
			win_loose_ratio();
			score();
			part_of_leaderboard_ = user_nick_name + '\t' + to_string(all_match_) + '\t' + to_string(win_match_) + '\t' + to_string(remiss_match_) + '\t' + to_string(loose_match_) + '\t' + to_string(win_loose_ratio_) + '\t' + to_string(score_);
			leaderboard_.push_back(part_of_leaderboard_);
		}break;

		case LOOSE:
		{
			all_match_ = 1;
			win_match_ = 0;
			remiss_match_ = 0;
			loose_match_ = 1;
			win_loose_ratio();
			score();
			part_of_leaderboard_ = user_nick_name + '\t' + to_string(all_match_) + '\t' + to_string(win_match_) + '\t' + to_string(remiss_match_) + '\t' + to_string(loose_match_) + '\t' + to_string(win_loose_ratio_) + '\t' + to_string(score_);
			leaderboard_.push_back(part_of_leaderboard_);
		}break;

		default:
		{
			NULL;
		}break;
	}
}

void c_leaderboard::cut_part_of_leaderboard(const string& player_name)
{
	const auto player_name_length = player_name.length();
	part_of_leaderboard_.erase(0, player_name_length + 4);
	string temp_string[6];
	int j = 0;

	for (auto i = 0; i < part_of_leaderboard_.size(); i++)
	{
		if (std::isdigit(part_of_leaderboard_[i]))
		{
			temp_string[j] += part_of_leaderboard_[i];
		}
		else
		{
			part_of_leaderboard_.erase(i, i + 4);
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

void c_leaderboard::win_loose_ratio()
{
	win_loose_ratio_ = (win_match_ + remiss_match_) / loose_match_;
}

void c_leaderboard::score()
{
	score_ = (win_loose_ratio_ * 0.75) * (all_match_ * 0.25);
}

bool c_leaderboard::save_leaderboard()
{
	std::ofstream download_leaderboard;
	download_leaderboard.open("date_base\\leaderboard.txt");
	if (download_leaderboard.bad())
	{
		return false;
	}
	for (const auto& i : leaderboard_)
	{
		download_leaderboard << i;
	}
	download_leaderboard.close();
	return true;
}
