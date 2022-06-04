/*
* Copyright (C) 2022 Jakub G�recki - All Right Reserved.
* Gmail: jakub.xiz1.gorecki@gmail.com
* GitHub: https://github.com/XiZ1
*/

#pragma once

#include "tictactoe.h"

class c_game
{
public:

	c_game(const int round, const int win, const bool name, const bool score);

	void start_game();

private:

	int max_round_, round_need_to_win_;
	bool set_name_, save_score_;
	string name_player_one_ = "Player_1", name_player_two_ = "Player_2";

	int player_one_points_ = 0, player_two_points_ = 0;
	char player_one_character_ = 'X', player_two_character_ = 'O';

	static constexpr int x_board_size = 3;
	static constexpr int y_board_size = 3;
	char tab_board_[x_board_size][y_board_size]{{'1', '2', '3'},{'4', '5', '6'},{'7', '8', '9'}};

	string winner_, loser_;

	static int set_max_round();
	static int set_round_need_to_win();
	void set_name();

	void show_board() const;
	void set_char(const char player_character);
	static bool check_field_is_empty(const char field_number, const char& field_of_board);
	bool check_win();
	bool check_x(const char& player_character) const;
	bool check_y(const char& player_character) const;
	bool check_diagonal(const char& player_character) const;
	static void add_point(int& player_point);
	void set_match_results(const string& winner, const string& loser);
};

