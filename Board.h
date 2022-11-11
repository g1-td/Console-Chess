#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include "Piece.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"
class Board
{
	public:
	Board();
	Board(const Board& brd);

	bool isKingInCheck() const;
	bool playerHasLegalMoves() const;
	bool isMoveLegal(const Coords& c) const;
	bool isKingOrRook(const Coords& c) const;
	bool isPawnMovedTwice(const Coords& c) const;
	bool cmpBoard(const std::unique_ptr<Piece> other[8][8]) const;
	bool fiftyMove_check() const;
	bool threeFold_check() const;
	bool isBeginningOfTurn() const;

	void fiftyMove_count(const Coords& c);
	void threeFold_count(const Coords& c);
	void updateRepetitionState(const Coords& c);
	void removePawnsTakenEnPassant(const Coords& c);
	void expireEnPassantFlags();
	void setupDefaultBoard();
	void setFlags(const Coords& c);
	void setFlagTrue(const Coords& c);
	void movePiece(const Coords& c);

	Coords findKing() const;
	Piece::Color ReturnAlternateTurn() const;
	Piece::Color alternateTurn();
	static void copyBoard(const std::unique_ptr<Piece> original[8][8], std::unique_ptr<Piece> copy[8][8]);

	struct posInstance
	{
		posInstance(std::unique_ptr<Piece> b[8][8])
		{
			copyBoard(b, board);
		}

		std::unique_ptr<Piece> board[8][8];
		int repeated = 0;
	};

	std::unique_ptr<Piece> board[8][8];
	std::vector<posInstance> threeFoldCoordsArray;
	Piece::Color playerTurnColor;
	int fiftyMoveCounter = 0;
	int threeFoldCounter = 0;
	int turnCounter = 0;
};

