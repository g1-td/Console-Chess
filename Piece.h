#include <memory>
#include "Coords.h"
#pragma once
class Piece
{
	public:

	enum class Color { WHITE, BLACK };
	enum class Type { ROOK = 'R', KNIGHT = 'N', BISHOP = 'B', QUEEN = 'Q', KING = 'K', PAWN = 'P' };

	Piece(Color pieceColor) : pieceColor{ pieceColor } {};
	~Piece() = default;


	Color getPieceColor() const { return pieceColor; };
	static int getPawnMoveDirection(const Color pieceColor) { return pieceColor == Color::WHITE ? 1 : -1; };
	virtual Type getPieceType() const = 0;
	virtual bool areSquaresValid(const Coords& c, const std::unique_ptr<Piece> piece[8][8]) const = 0;

	bool setMovedFlag(bool newFlag) { return movedFlag = newFlag; };
	bool getMovedFlag() const { return movedFlag; };
	bool isPieceType(const Type pieceType) const { return getPieceType() == pieceType; };
	bool isPieceEnemy(const Piece* piece) const { return piece->getPieceColor() != pieceColor; };
	bool isPieceBlack() const { return pieceColor == Color::BLACK; };
	bool isSquareOccupied() { return this != nullptr; };


	protected:
	Color pieceColor;
	bool movedFlag = false;
};