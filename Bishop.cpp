#include "Bishop.h"

Piece::Type Bishop::getPieceType() const
{
	return Piece::Type::B;
}

bool Bishop::areSquaresValid(const Coords& c, const Piece* board[8][8]) const
{
	if (isStartExitOnSameDiagonal(c))
	{
		return areIntermediateDiagonalSquaresEmpty(c, board);
	}
}
