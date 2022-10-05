#include <memory>
#include "Coords.h"
#pragma once

class Piece
{
	public:

	enum class Color { WHITE, BLACK };
	enum class Type { R, N, B, Q, K, P };

	Piece(Color pieceColor) : pieceColor{ pieceColor } {};

	Color getPieceColor() const { return pieceColor; };
	bool getMovedFlag() const { return movedFlag; };
	void setMovedFlag(bool newFlag) { movedFlag = newFlag; };

	virtual Type getPieceType() const = 0;
	virtual bool areSquaresValid(const Coords& c, const Piece* board[8][8]) const = 0;

	bool isPieceEnemy(const Coords& c, const Piece* board[8][8]) const { return board[c.exitY][c.exitX]->getPieceColor() != pieceColor; };
	int getPawnMoveDirection() const { return pieceColor == Color::WHITE ? 1 : -1; };
	static int getExitToStartDirection(const int start, const int exit) { return start > exit ? 1 : -1; };
	static bool squareNotEmpty(const int y, const int x, const Piece* board[8][8]) { return board[y][x] != 0; };
	static bool areIntermediateXSquaresEmpty(const Coords& c, const Piece* board[8][8])
	{
		int exitToStartDirection = getExitToStartDirection(c.startX, c.exitX);

		for (int intermediateX = c.exitX + exitToStartDirection;
			intermediateX != c.startX;
			intermediateX += exitToStartDirection)
		{
			int y = c.startY;
			int x = intermediateX;

			if (squareNotEmpty(y, x, board))
			{
				return false;
			}
		}
		return true;
	};
	static bool areIntermediateYSquaresEmpty(const Coords& c, const Piece* board[8][8])
	{
		int exitToStartDirection = getExitToStartDirection(c.startY, c.exitY);

		for (int intermediateY = c.exitY + exitToStartDirection;
			intermediateY != c.startY;
			intermediateY += exitToStartDirection)
		{
			int y = intermediateY;
			int x = c.exitX;

			if (squareNotEmpty(y, x, board))
			{
				return false;
			}
		}
		return true;
	};
	static bool areIntermediateDiagonalSquaresEmpty(const Coords& c, const Piece* board[8][8])
	{
		int exitToStartXDirection = getExitToStartDirection(c.startX, c.exitX);
		int exitToStartYDirection = getExitToStartDirection(c.startY, c.exitY);

		int intermediateX = c.exitX + exitToStartXDirection;
		int intermediateY = c.exitY + exitToStartYDirection;

		for (int i = intermediateY; i != c.startY; i += exitToStartYDirection)
		{
			if (squareNotEmpty(intermediateY, intermediateX, board))
			{
				return false;
			}
			intermediateX += exitToStartXDirection;
			intermediateY += exitToStartYDirection;
		}

		return true;
	}
	static bool isStartExitOnSameDiagonal(const Coords& c)
	{
		return (c.exitX - c.startX == c.exitY - c.startY) || (c.exitX - c.startX == c.startY - c.exitX);
	};

	protected:
	Color pieceColor;
	bool movedFlag = false;
};