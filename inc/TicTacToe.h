/*
* Copyright (C) 2022 Jakub Górecki - All Right Reserved.
* Gmail: jakub.xiz1.gorecki@gmail.com
* GitHub: https://github.com/XiZ1
*/

#pragma once

#include <iostream>

using std::cout;
using std::string;

class c_game;
class c_leaderboard;

class c_tictactoe
{
public:

	friend class c_learderboard;
	friend class c_game;

	void start_tictactoe();

private:

	void clear_screen();
	void show_message();
	bool whether_exit();

};
