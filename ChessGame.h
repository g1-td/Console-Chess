#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include "Board.h"
#include "NotationToCoords.h"
class ChessGame
{
	public:
	ChessGame();
	void start();
	

	private:
	void turn();
	void nextTurn();
	bool gameOver() const;
	bool inputHasCommands(std::string userInput); // REDO THIS 
	static std::string getParsedUserInput();

	// Visual 
	void draw() const;
	bool callDrawToggle();
	void callDraw() const;
	bool CHECKMATE() const;
	bool STALEMATE() const;
	static void help();
	static void invalidMove();

	static void drawLineA();
	static void drawFooter();
	static bool isNotFillerSpace(int number);

	private:
	std::unique_ptr<Board> brd;
	bool autoDraw = true;
};