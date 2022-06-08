/*
* Copyright (C) 2022 Jakub Górecki - All Right Reserved.
* Gmail: jakub.xiz1.gorecki@gmail.com
* GitHub: https://github.com/XiZ1
*/

#include "leaderboard.h"
#include <fstream>
#include <string>

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

void c_leaderboard::save_match_results(const string& winner, const string& loser)
{
	download_leaderboard();
	constexpr int tab_flag[2]{ WIN, LOOSE };
	const string tab_user_name[2] = { winner, loser };
	for (auto i = 0; i < 2; i++)
	{
		if (is_user_exist(tab_user_name[i]))
		{
			update_user_stats(tab_user_name[i], tab_flag[i]);
		}
		else
		{
			add_user(tab_user_name[i], tab_flag[i]);
		}
	}
	save_leaderboard();
}

void c_leaderboard::save_remiss_match_results(const string& remiss_one, const string& remiss_two)
{
	download_leaderboard();
	const string tab_user_name[2] = { remiss_one, remiss_two };
	for(auto i = 0; i < 2; i++)
	{
		if (is_user_exist(tab_user_name[i]))
		{
			update_user_stats(tab_user_name[i], REMISS);
		}
		else
		{
			add_user(tab_user_name[i], REMISS);
		}
	}
	save_leaderboard();
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
			return true;
		}
	}
	return false;
}

void c_leaderboard::update_user_stats(const string& user_nick_name, const int& flag)
{
	if (flag == 0)
	{
		//win
	}
	if(flag == 1)
	{
		//loose
	}
	if (flag == 2)
	{
		//remiss
	}
}

void c_leaderboard::add_user(const string& user_nick_name, const int& flag)
{
	string temp;
	if (flag == 0)
	{
		temp = user_nick_name + " 1 1 0 0";
		leaderboard_.push_back(temp);
	}
	if (flag == 1)
	{
		temp = user_nick_name + " 1 0 0 1";
		leaderboard_.push_back(temp);
	}
	if (flag == 2)
	{
		temp = user_nick_name + " 1 0 1 0";
		leaderboard_.push_back(temp);
	}
}

double c_leaderboard::win_loose_ratio()
{
	return (win_match_ + remiss_match_) / loose_match_;
}

double c_leaderboard::score()
{
	return (win_loose_ratio_ * 0.75) * (all_match_ * 0.25);
}

bool c_leaderboard::save_leaderboard()
{
	std::ofstream download_leaderboard;
	download_leaderboard.open("date_base\\leaderboard.txt");
	if (download_leaderboard.bad())
	{
		return false;
	}
	for (auto i = 0; i < leaderboard_.size(); i++)
	{
		download_leaderboard << leaderboard_[i];
	}
	download_leaderboard.close();
	return true;
}
