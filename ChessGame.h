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
	protected:
	std::unique_ptr<Piece> board[8][8];
	Piece::Color playerTurnColor;
	bool autoDraw = true;


	public:
	ChessGame();
	void start();
	

	private:
	void turn();
	void alternateTurn();
	bool gameOver() const;
	
	void setupDefaultBoard();
	bool isKingInCheck(const std::unique_ptr<Piece> board[8][8]) const;
	bool isMoveLegal(const Coords& c) const;
	bool doesPlayerHaveMoves() const;
	void CHECKMATE() const;
	void STALEMATE() const;

	Coords findKing(const std::unique_ptr<Piece> board[8][8]) const;
	Piece::Color ReturnAlternateTurn() const;

	void copyCurrentBoardTo(std::unique_ptr<Piece> copy[8][8]) const;
	void makeMoveInBoard(const Coords c, std::unique_ptr<Piece> copy[8][8]) const;
	void filterInputForCommands(const std::string& input);
	bool callDrawToggle();
	void callDraw() const;
	void draw() const;
	static void invalidMove();
	static void help();

	struct helpers
	{
		static void drawLineA();
		static void drawFooter();
		static void drawCoordinates(int number);
		static bool isNotFillerSpace(int number);
	};
};