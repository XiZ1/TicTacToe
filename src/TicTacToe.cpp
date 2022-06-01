/*
* Copyright (C) 2022 Jakub Górecki - All Right Reserved.
* Gmail: jakub.xiz1.gorecki@gmail.com
* GitHub: https://github.com/XiZ1
*/

#include "tictactoe.h"
#include "game.h"
#include "leaderboard.h"
#include <conio.h>

/*
 * PUBLIC:
 */


void c_tictactoe::start_tictactoe()
{
	do
	{
		clear_screen();
		show_message("TicTacToe GAME!\n\n 1. Quick match.\n 2. Ranking match.\n 3. Custom match.\n 4. Leaderboard.\n\n");
		int choose = 0;
		cin >> choose;
		switch (choose)
		{
			case QUICK:
			{
				c_game o_quick_game;
			}break;

			case RANKING:
			{
				c_game o_ranking_game;
			}break;

			case CUSTOM:
			{
				c_game o_custom_game;
			}break;

			case LEADER:
			{
				c_leaderboard o_leaderboard;
			}break;

			default:
			{
				NULL;
			}break;
		}
	}while (true);
}


/*
 * PRIVATE:
 */


void c_tictactoe::clear_screen()
{
	system("cls");
}

void c_tictactoe::show_message(const string& message)
{
	cout << message;
}

bool c_tictactoe::whether_exit()
{
	clear_screen();
	show_message("Do you want exit ? Press y/n.");
	if (_getch() == 'y')
	{
		return true;
	}
	return false;
}
