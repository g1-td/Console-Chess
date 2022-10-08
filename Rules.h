#include <memory>
#include "Coords.h"
#include "Piece.h"

namespace Rules
{
	static int getExitToStartDirection(const int start, const int exit) { return start > exit ? 1 : -1; };
	static bool isSquareType(Piece::Type pieceType, int y, int x, const std::unique_ptr<Piece> board[8][8]) { return board[y][x]->getPieceType() == pieceType; };
	static bool squareNotEmpty(const int y, const int x, const std::unique_ptr<Piece> board[8][8]) { return board[y][x] != 0; };

	static bool areIntermediateXSquaresEmpty(const Coords& c, const std::unique_ptr<Piece> board[8][8])
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

	static bool areIntermediateYSquaresEmpty(const Coords& c, const std::unique_ptr<Piece> board[8][8])
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

	static bool areIntermediateDiagonalSquaresEmpty(const Coords& c, const std::unique_ptr<Piece> board[8][8])
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
	};

	static bool isStartExitOnSameDiagonal(const Coords& c)
	{
		return (c.exitX - c.startX == c.exitY - c.startY) || (c.exitX - c.startX == c.startY - c.exitX);
	};
};