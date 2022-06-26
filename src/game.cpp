/*
* Copyright (C) 2022 Jakub Górecki - All Right Reserved.
* Gmail: jakub.xiz1.gorecki@gmail.com
* GitHub: https://github.com/XiZ1
*/

#include "game.h"
#include "leaderboard.h"
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
		round_need_to_win_ = set_round_need_to_win(max_round_);
	}
	if(set_name_)
	{
		set_name();
	}
}

void c_game::start_game() 
{
	set_default_value_for_variables();
	for (auto match = 0; match < max_round_; match++)
	{
		clear_board();
		for (auto round = 0; round < 9; round++)
		{
			c_tictactoe::clear_screen();
			c_tictactoe::show_message("\t      MATCH: " + std::to_string(match + 1) + "\n\n");
			c_tictactoe::show_message(name_player_one_ + ": " + std::to_string(player_one_points_) + "	VS	" + std::to_string(player_two_points_) + " :" + name_player_two_ + "\n\n");
			show_board();
			if (round % 2 == 0)
			{
				set_char(player_one_character_);
			}
			else
			{
				set_char(player_two_character_);
			}
			if (round >= 4)
			{
				if(check_win())
				{
					break;
				}
			}
			if (round == 8)
			{
				c_tictactoe::clear_screen();
				c_tictactoe::show_message("REMISS MATCH!\n\n");
				system("pause");
				break;
			}
		}
		if (check_who_win_match())
		{
			break;
		}
		if (match == (max_round_ - 1))
		{
			check_who_win_without_needed_points();
		}
	}
	if (save_score_)
	{
		c_leaderboard o_leaderboard;
		if(remiss_match_)
		{
			o_leaderboard.save_match_results(name_player_one_, REMISS, name_player_two_, REMISS);
		}
		o_leaderboard.save_match_results(winner_, WIN, loser_, LOOSE);
	}
}


/*
 * PRIVATE:
 */


int c_game::set_max_round()
{
	int how_many_rounds = -1;
	while (true)
	{
		c_tictactoe::clear_screen();
		c_tictactoe::show_message("Enter the maximum number of rounds.");
		cin >> how_many_rounds;
		if(how_many_rounds > 0)
		{
			return how_many_rounds;
		}
	}
}

int c_game::set_round_need_to_win(const int& maximum_round)
{
	int how_many_rounds_need_to_win = -1;
	while (true)
	{
		c_tictactoe::clear_screen();
		c_tictactoe::show_message("Enter the number of rounds needed to win.");
		cin >> how_many_rounds_need_to_win;
		if ((how_many_rounds_need_to_win > 0) && (how_many_rounds_need_to_win < maximum_round))
		{
			return how_many_rounds_need_to_win;
		}
	}
}

void c_game::set_name()
{
	c_tictactoe::show_message("Enter the first player's name.");
	cin >> name_player_one_;
	c_tictactoe::show_message("Enter the second player's name.");
	cin >> name_player_two_;
}

void c_game::set_default_value_for_variables()
{
	player_one_points_ = 0;
	player_two_points_ = 0;
	winner_ = "";
	loser_ = "";
	remiss_match_ = false;
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

void c_game::show_board() const
{
	cout << "\t     " << tab_board_[0][0] << " | " << tab_board_[0][1] << " | " << tab_board_[0][2] << '\n';
	cout << "\t    -----------\n";
	cout << "\t     " << tab_board_[1][0] << " | " << tab_board_[1][1] << " | " << tab_board_[1][2] << '\n';
	cout << "\t    -----------\n";
	cout << "\t     " << tab_board_[2][0] << " | " << tab_board_[2][1] << " | " << tab_board_[2][2] << '\n';
}

void c_game::set_char(const char player_character)
{
	bool end_loop = true;
	do
	{
		const char temp = static_cast<char>(_getch());
		for (auto i = 0; i < 3; i++)  // NOLINT(modernize-loop-convert)
		{
			for (auto j = 0; j < 3; j++)
			{
				if (check_field_is_empty(temp, tab_board_[i][j]))
				{
					tab_board_[i][j] = player_character;
					end_loop = false;
				}
			}
		}
	}
	while (end_loop);
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
	const char tab_character[2]{ player_one_character_, player_two_character_ };
	int* tab_point[2] = { &player_one_points_, &player_two_points_ };
	const string tab_name[2]{ name_player_one_, name_player_two_ };
	for (auto i = 0; i < 2; i++)
	{
		if ((check_x(tab_character[i])) || check_y(tab_character[i]) || check_diagonal(tab_character[i]))
		{
			c_tictactoe::clear_screen();
			c_tictactoe::show_message(tab_name[i] + " WIN THIS ROUND!\n\n");
			add_point(tab_point[i]);
			system("pause");
			return true;
		}
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

bool c_game::check_diagonal(const char& player_character) const
{
	for (auto i = 0; i < 3; i += 2)
	{
		if ((tab_board_[0][0 + i] == player_character) && (tab_board_[1][1] == player_character) && (tab_board_[2][2 - i] == player_character))
		{
			return true;
		}
	}
	return false;
}

void c_game::add_point(int* player_point)
{
	*player_point += 1;
}

bool c_game::check_who_win_match()
{
	const int tab_player_points[2] = {player_one_points_, player_two_points_};
	const string tab_player_names[2] = { name_player_one_, name_player_two_ };
	for (auto i = 0; i < 2; i++)
	{
		if (tab_player_points[i] == round_need_to_win_)
		{
			c_tictactoe::clear_screen();
			c_tictactoe::show_message("WINNER IS " + tab_player_names[i] + "!\n\n");
			if (i == 0)
			{
				set_match_results(tab_player_names[i], tab_player_names[i + 1]);
			}
			if (i == 1)
			{
				set_match_results(tab_player_names[i], tab_player_names[i - 1]);
			}
			system("pause");
			return true;
		}
	}
	return false;
}

void c_game::check_who_win_without_needed_points()
{
	int tab_player_points[2] = {player_one_points_, player_two_points_};
	string tab_player_names[2] = {name_player_one_, name_player_two_};
	if (player_one_points_ == player_two_points_)
	{
		c_tictactoe::clear_screen();
		c_tictactoe::show_message("REMISS GAME!\n\n");
		remiss_match_ = true;
		system("pause");
	}
	for (auto i = 0; i < 2; i++)
	{
		if (tab_player_points[0] > tab_player_points[1])
		{
			c_tictactoe::clear_screen();
			c_tictactoe::show_message("WINNER IS " + tab_player_names[0] + "!\n\n");
			set_match_results(tab_player_names[0], tab_player_names[1]);
			system("pause");
		}
		std::swap(tab_player_points[0], tab_player_points[1]);
		std::swap(tab_player_names[0], tab_player_names[1]);
	}
}

void c_game::set_match_results(const string& winner, const string& loser)
{
	winner_ = winner;
	loser_ = loser;
}
