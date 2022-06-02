/*
* Copyright (C) 2022 Jakub Górecki - All Right Reserved.
* Gmail: jakub.xiz1.gorecki@gmail.com
* GitHub: https://github.com/XiZ1
*/

#include "game.h"
#include <string>
#include <conio.h>


/*
 * PUBLIC:
 */


c_game::c_game(const int round, const int win, const bool name, const bool score)
{
	max_round_ = round;
	round_need_to_win_ = win;
	set_name_ = name;
	save_score_ = score;
	if (max_round_ == -1)
	{
		max_round_ = set_max_round();
	}
	if (round_need_to_win_ == -1)
	{
		round_need_to_win_ = set_round_need_to_win();
	}
	if(set_name_)
	{
		set_name();
	}
}

void c_game::start_game()
{
	for (auto i = 0; i < max_round_; i++)
	{
		for (auto j = 0; j < 9; j++)
		{
			c_tictactoe::clear_screen();
			c_tictactoe::show_message(name_player_one_ + ": " + std::to_string(player_one_points_) + "		VS		" + std::to_string(player_two_points_) + " :" + name_player_two_);
			show_board();
			if (j % 2 == 0)
			{
				set_char(player_one_character_);
			}
			else
			{
				set_char(player_two_character_);
			}
			if (j == 4)
			{
				if(check_win())
				{
					//add point
					break;
				}
			}
		}
	}
}


/*
 * PRIVATE:
 */


int c_game::set_max_round()
{
	int how_many_rounds = -1;
	cin >> how_many_rounds;
	return how_many_rounds;
}

int c_game::set_round_need_to_win()
{
	int how_many_rounds_need_to_win = -1;
	cin >> how_many_rounds_need_to_win;
	return how_many_rounds_need_to_win;
}

void c_game::set_name()
{
	cin >> name_player_one_;
	cin >> name_player_two_;
}

void c_game::show_board() const
{
	c_tictactoe::clear_screen();
	cout << tab_board_[0][0] << " | " << tab_board_[0][1] << " | " << tab_board_[0][2] << '\n';
	cout << "---------\n";
	cout << tab_board_[1][0] << " | " << tab_board_[1][1] << " | " << tab_board_[1][2] << '\n';
	cout << "---------\n";
	cout << tab_board_[2][0] << " | " << tab_board_[2][1] << " | " << tab_board_[2][2] << '\n';
}

void c_game::set_char(const char player_character)
{
	switch (_getch())
	{
		case '1':
		{
			tab_board_[0][0] = player_character;
		}break;

		case '2':
		{
			tab_board_[0][1] = player_character;
		}break;

		case '3':
		{
			tab_board_[0][2] = player_character;
		}break;

		case '4':
		{
			tab_board_[1][0] = player_character;
		}break;

		case '5':
		{
			tab_board_[1][1] = player_character;
		}break;

		case '6':
		{
			tab_board_[1][2] = player_character;
		}break;

		case '7':
		{
			tab_board_[2][0] = player_character;
		}break;

		case '8':
		{
			tab_board_[2][1] = player_character;
		}break;

		case '9':
		{
			tab_board_[2][2] = player_character;
		}break;

		default:
		{
			NULL;
		}break;
	}
}

bool c_game::check_win()
{
	return true;
}
