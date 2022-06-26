/*
* Copyright (C) 2022 Jakub Górecki - All Right Reserved.
* Gmail: jakub.xiz1.gorecki@gmail.com
* GitHub: https://github.com/XiZ1
*/

#include "TicTacToe.h"
#include "game.h"
#include "leaderboard.h"
#include <conio.h>


/*
 * PUBLIC:
 */


void c_tictactoe::start_tictactoe()
{  // NOLINT(clang-diagnostic-missing-noreturn)
	while(true)
	{
		clear_screen();
		show_message("TicTacToe GAME!\n\n 1. Quick match.\n 2. Ranking match.\n 3. Custom match.\n 4. Leaderboard.\n 5. Exit.\n\n");
		switch (_getch())
		{
		case QUICK:
			{
				c_game o_quick_match(5, 3, false, false);
				do
				{
					o_quick_match.start_game();
				}while (whether_play_again());
			}break;
		case RANKING:
			{
				c_game o_ranking_match(9, 5, true, true);
				do
				{
					o_ranking_match.start_game();
				}while (whether_play_again());
			}break;
		case CUSTOM:
			{
				c_game o_custom_match(-1, -1, true, false);
				do
				{
					o_custom_match.start_game();
				}while (whether_play_again());
			}break;
		case LEADER:
			{
				c_leaderboard o_leaderboard;
				o_leaderboard.show_leaderboard();
			}break;
		case EXIT:
			{
				_exit(0);
			}
		default:
			{
				NULL;
			}break;
		}
	}
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

bool c_tictactoe::whether_play_again()
{
	clear_screen();
	show_message("Do you want to play again ? Press y/n.");
	if (_getch() == 'y')
	{
		return true;
	}
	return false;
}
