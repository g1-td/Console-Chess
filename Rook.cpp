#include "Rook.h"

Piece::Type Rook::getPieceType() const
{
	return Piece::Type::R;
}

bool Rook::areSquaresValid(const Coords& c, const Piece* board[8][8]) const
{
	if (c.startY == c.exitY)
	{
		return areIntermediateXSquaresEmpty(c, board);
	}
	else if (c.startX == c.exitX)
	{
		return areIntermediateYSquaresEmpty(c, board);
	}
	return false;
}