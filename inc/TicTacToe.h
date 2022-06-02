/*
* Copyright (C) 2022 Jakub Górecki - All Right Reserved.
* Gmail: jakub.xiz1.gorecki@gmail.com
* GitHub: https://github.com/XiZ1
*/

#pragma once

#include <iostream>

using std::cout;
using std::cin;
using std::string;

class c_game;
class c_leaderboard;

class c_tictactoe
{
public:

	friend class c_leaderboard;
	friend class c_game;

	static void start_tictactoe();

private:

	enum tictactoe_main_menu{QUICK = 1, RANKING = 2, CUSTOM = 3, LEADER = 4, EXIT = 5};

	static void clear_screen();
	static void show_message(const string&);
	static bool whether_exit();

};
