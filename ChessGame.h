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
	void setupDefaultBoard();
	bool gameOver() const;
	
	static Piece::Color ReturnAlternateTurn(const Piece::Color& playerTurnColor);
	bool InputHasCommands(const std::string& input);
	static void movePiece(const Coords& c, std::unique_ptr<Piece> b[8][8]);
	static void copyBoard(const std::unique_ptr<Piece> original[8][8], std::unique_ptr<Piece> copy[8][8]);
	
	// Rules
	static bool isMoveLegal(const Coords& c, const std::unique_ptr<Piece> board[8][8], const Piece::Color& playerTurnColor);
	static bool isKingInCheck(const std::unique_ptr<Piece> board[8][8], const Piece::Color& playerTurnColor);
	static Coords findKing(const std::unique_ptr<Piece> board[8][8], const Piece::Color& playerTurnColor);
	static bool doesPlayerHaveMoves(const std::unique_ptr<Piece> board[8][8], const Piece::Color& playerTurnColor);

	// Visual 
	void draw() const;
	bool callDrawToggle();
	void callDraw() const;
	static void help();
	static void invalidMove();
	void CHECKMATE() const;
	void STALEMATE() const;
	struct helpers
	{
		static void drawLineA();
		static void drawFooter();
		static bool isNotFillerSpace(int number);
	};
};