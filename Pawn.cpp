#include "Pawn.h"
#include "Rules.h"

Pawn::Type Pawn::getPieceType() const
{
	return Type::PAWN;
}

bool Pawn::isMovedUpOnce(const Coords& c) const { return c.exitY == c.startY + getPawnMoveDirection(pieceColor); }
bool Pawn::isMovedUpTwice(const Coords& c) const { return c.exitY == c.startY + (2 * getPawnMoveDirection(pieceColor)); }
bool Pawn::isPawnNotMoved(const Coords& c) const
{
	int direction = getPawnMoveDirection(pieceColor);

	if (direction == 1 && c.startY == 1)
		return true;

	else if (direction == -1 && c.startY == 6)
		return true;

	return false;
}
bool Pawn::exitIsUpAndLeft(const Coords& c, int direction) const
{
	return c.exitY == c.startX + direction && c.startX == c.exitX + 1;
}
bool Pawn::exitIsUpAndRight(const Coords& c, int direction) const
{
	return c.exitY == c.startX + direction && c.startX == c.exitX - 1;
}
bool Pawn::canEnPassant(const Coords& c, const std::unique_ptr<Piece> board[8][8]) const
{
	int direction = getPawnMoveDirection(pieceColor);

	if (exitIsUpAndRight(c, direction) && 
		board[c.startY][c.startX - 1]->isSquareOccupied() && 
		board[c.startY][c.startX + 1]->isPieceType(Type::PAWN))
		return board[c.startY][c.startX + 1]->getMovedFlag();

	else if (exitIsUpAndLeft(c, direction) && 
		board[c.startY][c.startX - 1]->isSquareOccupied() &&
		board[c.startY][c.startX - 1]->isPieceType(Type::PAWN))
		return board[c.startY][c.startX - 1]->getMovedFlag();

	return false;
}

bool Pawn::areSquaresValid(const Coords& c, const std::unique_ptr<Piece> board[8][8]) const
{
	int direction = getPawnMoveDirection(pieceColor);

	if (!board[c.exitY][c.exitX]->isSquareOccupied())
	{
		if (c.startX == c.exitX)
		{
			if (isMovedUpOnce(c))
				return true;

			else
			{
				if (isPawnNotMoved(c) &&
					Rules::areIntermediateYSquaresEmpty(c, board) &&
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
		if (exitIsUpAndRight(c, direction) || exitIsUpAndLeft(c, direction))
			return isPieceEnemy(board[c.exitY][c.exitX].get());
	}
	return false;
}