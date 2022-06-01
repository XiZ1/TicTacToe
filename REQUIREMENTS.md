# TicTacToe - Requirements

## Game mode

	Quick match  
		Default player name (Player_1 and Player_2)  
		Max 5 rounds  
		Rounds to win match 3  
		Score no save to LeaderBoards  

	Ranking match  
		User set custom player name  
		Max 9 rounds  
		Rounds to win 5  
		Score save to LeaderBoards  

	Custom match  
		User set custom player name  
		User set max rounds  
		User set rounds to win  
		Score no save to Leaderboards  

## Leaderboards
	
	Show top 10 players ever  
		Example display  
			NUMBER_ON_BOARD		NICK_NAME		ALL_MATCH		WIN_MATCH		LOSS_MATCH		K/D_RATIO		TOTAL_SCORE  

### FILE STRUCTURE

	main.cpp - start app  
	tictactoe.cpp / .h - include game and leaderboard  
	game.cpp / .h - game mode  
	leaderboard.cpp / .h - leaderboard  