#include "Queen.h"

Queen::Type Queen::getPieceType() const
{
	return Type::QUEEN;
}

bool Queen::areSquaresValid(const Coords& c, const std::unique_ptr<Piece> board[8][8]) const
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

std::unique_ptr<Piece> Queen::clone() const
{
	return std::make_unique<Queen>(*this);
}
