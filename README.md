# TIC TAC TOE
	Hello to all visitors to this repository, you will find here my proprietary implementation of a rather simplified Tic Tac Toe known from Windows 10.  
	The program was created out of the desire to learn programming in c ++, it is one of the projects I want to share with the world.  
	Feel free to browse, comment, rate, correct and develop the code.  
	Thank you in advance for any comments and evaluations.  
	
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

## TECHNOLOGY
	The program is a console application written in C ++ using the C ++ 20 standard.  
	The workbench is Visual Studio 2022 with JetBrains ReSharper extension.  
	The project build system is based on the .sln and .vcxproj files.  

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

## CONFIGURATION AND COMPILATION
	1. Visual Studio 2022  
		To properly build the application, I recommend the following changes to the project properties and then project builds.  
			Configuration Properties:  
				General:  
					Output directory: \$(SolutionDir)TicTacToe\bin\$(Platform)\$(Configuration)\  
					Intermediate directory: \$(SolutionDir)TicTacToe\bin\Intermediate\$(Platform)\$(Configuration)\  
					C ++ language standard: C ++ 20  
				C ++ Directories:  
					Header file directories: [PATH TO]\TicTacToe\include  

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

### APPLICATION USAGE
	The application consists of two modules divided into two separate classes:  
		- GAME  
		- LEADERBOARD  
	
	The game module contains three modes, each of the modes has a slightly different operating principle:    
		-QUICK MATCH  
			Max 5 rounds  
			3 rounds to win the match  
			Player name is the default  
			The result is not added to the scoreboard   
		-RANKING MATCH  
			Max 9 rounds  
			5 rounds to win the match  
			Player name set by players  
			The result is added to the scoreboard  
		-CUSTOME MATCH  
			Max rounds CUSTOME  
			Rounds to win CUSTOME  
			Player name set by players  
			The result is not added to the scoreboard  
			
	Leaderboard shows a list of player stats from the ranked matches sorted from best to worst player.  
	
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

#### COPYRIGHTS
	Copyright (C) 2022 Jakug Górecki - All Right Reserved.  
	Gmail: jakub.xiz1.gorecki@gmail.com  
	GitHub https://github.com/XiZ1  
