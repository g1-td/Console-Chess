#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include "Board.h"
#include "NotationToCoords.h"
#include "FEN.h"
class ChessGame
{
	public:
	ChessGame();
	ChessGame(const std::string& _fen);
	ChessGame(int _min, int _sec = 0, int _inc = 0);
	ChessGame(const std::string& _fen, int _min, int _sec = 0, int _inc = 0);
	
	void start();
	void newGame();
	void newGame(const std::string& _fen);


	private:
	bool makeMove(const Coords& _c);
	void nextTurn();
	bool gameOver() const;

	bool hasCommands(std::string userInput);
	Coords getUserInput();
	Coords InputHasCommandsCode();

	void setTimers(int _min, int _sec, int _inc);
	void timerController();
	Timer* currentPlayersTimer();

	// Visual 
	void draw() const;
	bool callDrawToggle();
	void visualize() const;
	bool CHECKMATE() const;
	bool STALEMATE() const;
	bool TIMEOUT() const;
	static void help();
	static bool invalidMove();

	void drawRemainingTime() const;
	static void drawLineA();
	static void drawFooter();
	static bool isNotFillerSpace(int number);


	std::unique_ptr<Board> brd;
	bool autoDraw = true;
	bool firstMove = false;
};