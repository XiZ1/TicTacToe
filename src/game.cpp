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
		clear_board();
		for (auto j = 0; j < 9; j++)
		{
			c_tictactoe::clear_screen();
			c_tictactoe::show_message("ROUND: " + std::to_string(i + 1) + "\n\n");
			c_tictactoe::show_message(name_player_one_ + ": " + std::to_string(player_one_points_) + "	VS	" + std::to_string(player_two_points_) + " :" + name_player_two_ + "\n\n");
			show_board();
			if (j % 2 == 0)
			{
				set_char(player_one_character_);
			}
			else
			{
				set_char(player_two_character_);
			}
			if (j >= 4)
			{
				if(check_win())
				{
					break;
				}
			}
		}
		if (player_one_points_ == round_need_to_win_)
		{
			c_tictactoe::clear_screen();
			c_tictactoe::show_message("WINNER IS " + name_player_one_ + "!");
			set_match_results(name_player_one_, name_player_two_);
			break;
		}
		if(player_two_points_ == round_need_to_win_)
		{
			c_tictactoe::clear_screen();
			c_tictactoe::show_message("WINNER IS " + name_player_two_ + "!");
			set_match_results(name_player_two_, name_player_one_);
			break;
		}
		// TODO rozwiazanie kwesti remisu w przypadku meczy nie rozstrzygnietego nastepuje remis liczony do tablicy wynikow
	}
	if (save_score_)
	{
		//TODO ADD SAVE SCORE TO LEADERBOARD!
	}
}


/*
 * PRIVATE:
 */


int c_game::set_max_round()
{
	c_tictactoe::show_message("Enter the maximum number of rounds.");
	int how_many_rounds = -1;
	cin >> how_many_rounds;
	return how_many_rounds;
}

int c_game::set_round_need_to_win()
{
	c_tictactoe::show_message("Enter the number of rounds needed to win.");
	int how_many_rounds_need_to_win = -1;
	cin >> how_many_rounds_need_to_win;
	return how_many_rounds_need_to_win;
}

void c_game::set_name()
{
	c_tictactoe::show_message("Enter the first player's name.");
	cin >> name_player_one_;
	c_tictactoe::show_message("Enter the second player's name.");
	cin >> name_player_two_;
}

void c_game::show_board() const
{
	cout << tab_board_[0][0] << " | " << tab_board_[0][1] << " | " << tab_board_[0][2] << '\n';
	cout << "---------\n";
	cout << tab_board_[1][0] << " | " << tab_board_[1][1] << " | " << tab_board_[1][2] << '\n';
	cout << "---------\n";
	cout << tab_board_[2][0] << " | " << tab_board_[2][1] << " | " << tab_board_[2][2] << '\n';
}

void c_game::set_char(const char player_character)
{
	bool end_loop = true;
	do
	{
		switch (_getch())
		{
			case '1':
			{
				if (check_field_is_empty('1', tab_board_[0][0]))
				{
					tab_board_[0][0] = player_character;
					end_loop = false;
				}
			}break;

			case '2':
			{
				if (check_field_is_empty('2', tab_board_[0][1]))
				{
					tab_board_[0][1] = player_character;
					end_loop = false;
				}
			}break;

			case '3':
			{
				if (check_field_is_empty('3', tab_board_[0][2]))
				{
					tab_board_[0][2] = player_character;
					end_loop = false;
				}
			}break;

			case '4':
			{
				if (check_field_is_empty('4', tab_board_[1][0]))
				{
					tab_board_[1][0] = player_character;
					end_loop = false;
				}
			}break;

			case '5':
			{
				if (check_field_is_empty('5', tab_board_[1][1]))
				{
					tab_board_[1][1] = player_character;
					end_loop = false;
				}
			}break;

			case '6':
			{
				if (check_field_is_empty('6', tab_board_[1][2]))
				{
					tab_board_[1][2] = player_character;
					end_loop = false;
				}
					
			}break;

			case '7':
			{
				if (check_field_is_empty('7', tab_board_[2][0]))
				{
					tab_board_[2][0] = player_character;
					end_loop = false;
				}
					
			}break;

			case '8':
			{
				if (check_field_is_empty('8', tab_board_[2][1]))
				{
					tab_board_[2][1] = player_character;
					end_loop = false;
				}
					
			}break;

			case '9':
			{
				if (check_field_is_empty('9', tab_board_[2][2]))
				{
					tab_board_[2][2] = player_character;
					end_loop = false;
				}
					
			}break;

			default:
			{
				NULL;
			}break;
		}
	}while (end_loop);
}

bool c_game::check_field_is_empty(const char field_number, const char& field_of_board)
{
	if (field_number == field_of_board)
	{
		return true;
	}
	return false;
}

bool c_game::check_win()
{
	if (check_x(player_one_character_) || check_y(player_one_character_) || check_diagonal(player_one_character_))
	{
		c_tictactoe::clear_screen();
		c_tictactoe::show_message(name_player_one_ + " WIN THIS ROUND!");
		add_point(player_one_points_);
		return true;
	}
	if (check_x(player_two_character_) || check_y(player_two_character_) || check_diagonal( player_two_character_))
	{
		c_tictactoe::clear_screen();
		c_tictactoe::show_message(name_player_two_ + " WIN THIS ROUND!");
		add_point(player_two_points_);
		return true;
	}
	return false;
}

bool c_game::check_x(const char& player_character) const
{
	for (auto i = 0; i < 3; i++)  // NOLINT(modernize-loop-convert)
	{
		if((tab_board_[i][0] == player_character) && (tab_board_[i][1] == player_character) && (tab_board_[i][2] == player_character))
		{
			return true;
		}
	}
	return false;
}

bool c_game::check_y(const char& player_character) const
{
	for (auto i = 0; i < 3; i++)
	{
		if ((tab_board_[0][i] == player_character) && (tab_board_[1][i] == player_character) && (tab_board_[2][i] == player_character))
		{
			return true;
		}
	}
	return false;
}

bool c_game::check_diagonal(const char& player_character) const //TODO: IMPROVE CHECKING ALGORYTHM!
{
	if ((tab_board_[0][0] == player_character) && (tab_board_[1][1] == player_character) && (tab_board_[2][2] == player_character))
	{
		return true;
	}
	if ((tab_board_[0][2] == player_character) && (tab_board_[1][1] == player_character) && (tab_board_[2][0] == player_character))
	{
		return true;
	}
	return false;
}

void c_game::add_point(int& player_point)
{
	player_point++;
}

void c_game::clear_board()
{
	char temp_char = 49;
	for (auto i = 0; i < 3; i++)  // NOLINT(modernize-loop-convert)
	{
		for(auto j = 0; j < 3; j++)
		{
			tab_board_[i][j] = temp_char;
			temp_char++;
		}
	}
}

void c_game::set_match_results(const string& winner, const string& loser)
{
	winner_ = winner;
	loser_ = loser;
}
