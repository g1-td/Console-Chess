#include <memory>
#include "Coords.h"
#pragma once

class Piece
{
	public:

	enum class Color { WHITE, BLACK };
	enum class Type { R, N, B, Q, K, P };

	Piece(Color pieceColor) : pieceColor{ pieceColor } {};
	~Piece() = default;

	Color getPieceColor() const { return pieceColor; };
	bool getMovedFlag() const { return movedFlag; };
	int getPawnMoveDirection() const { return pieceColor == Color::WHITE ? 1 : -1; };
	virtual Type getPieceType() const = 0;
	void setMovedFlag(bool newFlag) { movedFlag = newFlag; };
	
	virtual bool areSquaresValid(const Coords& c, const std::unique_ptr<Piece> board[8][8]) const = 0;
	bool isPieceEnemy(int y, int x, const std::unique_ptr<Piece> board[8][8]) const { return board[y][x]->getPieceColor() != pieceColor; };
	bool isPieceBlack() const { return pieceColor == Color::BLACK; };


	protected:
	Color pieceColor;
	bool movedFlag = false;
};