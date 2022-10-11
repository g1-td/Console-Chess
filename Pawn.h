#include "Piece.h"
#pragma once
class Pawn :
	public Piece
{
	public:
	Pawn(Piece::Color pieceColor) : Piece(pieceColor) {};

	Piece::Type getPieceType() const;
	virtual bool areSquaresValid(const Coords& c, const std::unique_ptr<Piece> board[8][8]) const override;


	private:
	bool canEnPassant(const Coords& c, const std::unique_ptr<Piece> board[8][8]) const;
	bool isPawnNotMoved(const Coords& c) const;
	bool isMovedUpOnce(const Coords& c) const;
	bool isMovedUpTwice(const Coords& c) const;
	bool exitIsUpAndLeft(const Coords& c) const;
	bool exitIsUpAndRight(const Coords& c) const;
};