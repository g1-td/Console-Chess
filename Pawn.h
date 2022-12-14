#pragma once
#include "Piece.h"
class Pawn :
	public Piece
{
	public:
	Pawn(Piece::Color pieceColor) : Piece(pieceColor) {};
	virtual Pawn::Type getPieceType() const override;
	virtual bool areSquaresValid(const Coords& c, const std::unique_ptr<Piece> board[8][8]) const override;
	virtual std::unique_ptr<Piece> clone() const override;


	private:
	bool canEnPassant(const Coords& c, const std::unique_ptr<Piece> board[8][8]) const;
	bool isPawnNotMoved(const Coords& c) const;
	bool isMovedUpOnce(const Coords& c) const;
	bool isMovedUpTwice(const Coords& c) const;
	bool exitIsUpAndLeft(const Coords& c, int direction) const;
	bool exitIsUpAndRight(const Coords& c, int direction) const;
};