#include "Pawn.h"

Piece::Type Pawn::getPieceType() const
{
	return Piece::Type::P;
}
bool Pawn::isPawnNotMoved(const Coords& c) const
{
	int direction = getPawnMoveDirection();

	if (direction == 1 && c.startY == 1)
		return true;

	else if (direction == -1 && c.startY == 6)
		return true;

	return false;
}
bool Pawn::isMovedUpOnce(const Coords& c) const { return c.exitY == c.startY + getPawnMoveDirection(); }
bool Pawn::isMovedUpTwice(const Coords& c) const { return c.exitY == c.startY + (2 * getPawnMoveDirection()); }
bool Pawn::isSquarePawn(int y, int x, const Piece* board[8][8]) const
{
	if (board[y][x]->getPieceType() == Piece::Type::P)
		return true;

	return false;
}
bool Pawn::exitIsUpAndLeft(const Coords& c) const
{
	return c.startX == c.exitX + 1;
}
bool Pawn::exitIsUpAndRight(const Coords& c) const
{
	return c.startX == c.exitX - 1;
}
bool Pawn::canEnPassant(const Coords& c, const Piece* board[8][8]) const
{
	if (exitIsUpAndRight(c) && isSquarePawn(c.startY, c.startX + 1, board))
		return board[c.startY][c.startX + 1]->getMovedFlag();

	else if (exitIsUpAndLeft(c) && isSquarePawn(c.startY, c.startX - 1, board))
		return board[c.startY][c.startX - 1]->getMovedFlag();
}

bool Pawn::areSquaresValid(const Coords& c, const Piece* board[8][8]) const
{
	int direction = getPawnMoveDirection();

	if (squareNotEmpty(c.exitY, c.exitX, board))
	{
		if (c.startX == c.exitX)
		{
			if (isMovedUpOnce(c))
				return true;

			else
			{
				if (isPawnNotMoved(c) &&
					areIntermediateYSquaresEmpty(c, board) &&
					isMovedUpTwice(c))
				{
					return true;
				}
			}
		}
		else return canEnPassant(c, board);
	}
	else
	{
		if (exitIsUpAndRight(c) || exitIsUpAndLeft(c))
			return isPieceEnemy(c, board);
	}
	return false;
}