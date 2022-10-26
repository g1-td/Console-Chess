#include "Bishop.h"

Bishop::Type Bishop::getPieceType() const
{
	return Type::BISHOP;
}

bool Bishop::areSquaresValid(const Coords& c, const std::unique_ptr<Piece> board[8][8]) const
{
	if (isStartExitOnSameDiagonal(c))
	{
		return areIntermediateDiagonalSquaresEmpty(c, board);
	}
	return false;
}

std::unique_ptr<Piece> Bishop::clone() const
{
	return std::make_unique<Bishop>(*this);
}
