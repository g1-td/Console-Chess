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
	ChessGame(const std::string& fen);
	void start();
	void newGame();


	private:
	bool makeMove(const Coords& c);
	void nextTurn();
	bool gameOver() const;
	bool hasCommands(std::string userInput);
	Coords getUserInput();
	Coords InputHasCommandsCode();

	// Visual 
	void draw() const;
	bool callDrawToggle();
	void visualize() const;
	bool CHECKMATE() const;
	bool STALEMATE() const;
	static void help();
	static bool invalidMove();

	static void drawLineA();
	static void drawFooter();
	static bool isNotFillerSpace(int number);

	private:
	std::unique_ptr<Board> brd;
	bool autoDraw = true;
};