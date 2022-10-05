#include "Queen.h"

Piece::Type Queen::getPieceType() const
{
	return Piece::Type::Q;
}

bool Queen::areSquaresValid(const Coords& c, const Piece* board[8][8]) const
{
	if (c.startY == c.exitY)
	{
		return areIntermediateXSquaresEmpty(c, board);
	}
	else if (c.startX == c.exitX)
	{
		return areIntermediateYSquaresEmpty(c, board);
	}
	else if (isStartExitOnSameDiagonal(c))
	{
		return areIntermediateDiagonalSquaresEmpty(c, board);
	}
	return false;
}
