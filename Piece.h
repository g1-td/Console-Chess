#pragma once
#include <memory>
#include "Coords.h"
class Piece
{
	public:
	enum class Color { WHITE, BLACK };
	enum class Type { ROOK = 'R', KNIGHT = 'N', BISHOP = 'B', QUEEN = 'Q', KING = 'K', PAWN = 'P' };

	Piece(Color pieceColor) : pieceColor{ pieceColor } {};
	~Piece() = default;

	virtual bool areSquaresValid(const Coords& c, const std::unique_ptr<Piece> piece[8][8]) const = 0;
	virtual std::unique_ptr<Piece> clone() const = 0;

	// Properties Functions
	bool setMovedFlag(bool newFlag) { return movedFlag = newFlag; };
	bool getMovedFlag() const { return movedFlag; };
	Color getPieceColor() const { return pieceColor; };
	virtual Type getPieceType() const = 0;
	static int getPawnMoveDirection(const Color pieceColor) { return pieceColor == Color::WHITE ? 1 : -1; };
	bool isPieceType(const Type pieceType) const { return getPieceType() == pieceType; };
	bool isPieceColor(const Color color) const { return pieceColor == color; };
	bool isSquareOccupied() const { return this != nullptr; };

	// Movement Rules
	static int getExitToStartDirection(const int start, const int exit) { return start > exit ? 1 : -1; };
	static bool areIntermediateXSquaresEmpty(const Coords& c, const std::unique_ptr<Piece> board[8][8])
	{
		int exitToStartDirection = getExitToStartDirection(c.startX, c.exitX);

		for (int intermediateX = c.exitX + exitToStartDirection;
			intermediateX != c.startX;
			intermediateX += exitToStartDirection)
		{
			int y = c.startY;
			int x = intermediateX;

			if (board[y][x]->isSquareOccupied())
			{
				return false;
			}
		}
		return true;
	};
	static bool areIntermediateYSquaresEmpty(const Coords& c, const std::unique_ptr<Piece> board[8][8])
	{
		int exitToStartDirection = getExitToStartDirection(c.startY, c.exitY);

		for (int intermediateY = c.exitY + exitToStartDirection;
			intermediateY != c.startY;
			intermediateY += exitToStartDirection)
		{
			int y = intermediateY;
			int x = c.exitX;

			if (board[y][x]->isSquareOccupied())
			{
				return false;
			}
		}
		return true;
	};
	static bool areIntermediateDiagonalSquaresEmpty(const Coords& c, const std::unique_ptr<Piece> board[8][8])
	{
		int exitToStartXDirection = getExitToStartDirection(c.startX, c.exitX);
		int exitToStartYDirection = getExitToStartDirection(c.startY, c.exitY);

		int intermediateX = c.exitX + exitToStartXDirection;
		int intermediateY = c.exitY + exitToStartYDirection;

		for (int i = intermediateY; i != c.startY; i += exitToStartYDirection)
		{
			if (board[intermediateY][intermediateX]->isSquareOccupied())
			{
				return false;
			}
			intermediateX += exitToStartXDirection;
			intermediateY += exitToStartYDirection;
		}

		return true;
	};
	static bool isStartExitOnSameDiagonal(const Coords& c)
	{
		return (c.exitX - c.startX == c.exitY - c.startY) || (c.exitX - c.startX == c.startY - c.exitY);
	};


	protected:
	Color pieceColor;
	bool movedFlag = false;
};