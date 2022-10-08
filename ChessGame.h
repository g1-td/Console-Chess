#pragma once
#include <iostream>
#include <memory>
#include "Piece.h"
class ChessGame
{
	std::unique_ptr<Piece> board[8][8];
	Piece::Color playerTurn;
	bool autoDraw = true;


	public:
	ChessGame();

	void start();
	void turn();
	void autoDrawToggle();
	void draw() const;
	static void help();

	struct helpers
	{
		static void drawLineA();
		static void drawFooter();
		static void drawCoordinates(int number);
		static bool isNotFillerSpace(int number);
	};
};