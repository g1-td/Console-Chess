#include <memory>
#include "Coords.h"
#pragma once
class Piece
{
	public:

	enum class Color { WHITE, BLACK };
	enum class Type { ROOK = 'R', KNIGHT = 'N', BISHOP = 'B', QUEEN = 'Q', KING = 'K', PAWN = 'P', EMPTY = ' ' };

	Piece(Color pieceColor) : pieceColor{ pieceColor } {};
	~Piece() = default;

	Color getPieceColor() const { return pieceColor; };
	bool getMovedFlag() const { return movedFlag; };
	static int getPawnMoveDirection(const Color pieceColor) { return pieceColor == Color::WHITE ? 1 : -1; };
	Type getPieceType() const { return Type::EMPTY; };
	void setMovedFlag(bool newFlag) { movedFlag = newFlag; };

	virtual bool areSquaresValid(const Coords& c, const std::unique_ptr<Piece> board[8][8]) const = 0;
	bool isSquareNotEmpty() { return getPieceType() != Type::EMPTY; };
	bool isSquareType(Piece::Type pieceType) { return getPieceType() == pieceType; };
	bool isPieceEnemy(int y, int x, const std::unique_ptr<Piece> board[8][8]) const { return board[y][x]->getPieceColor() != pieceColor; };
	bool isPieceBlack() const { return pieceColor == Color::BLACK; };


	protected:
	Color pieceColor;
	bool movedFlag = false;
};