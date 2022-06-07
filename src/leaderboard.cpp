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
}

void c_leaderboard::save_remiss_match_results(const string& remiss_one, const string& remiss_two)
{

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
