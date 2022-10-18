#include <iostream>
#include <memory>
#include "Piece.h"
#include "NotationToCoords.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"
#pragma once
class ChessGame
{
	std::unique_ptr<Piece> board[8][8];
	Piece::Color playerTurn;
	bool autoDraw = true;

	void setupDefaultGame();

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