#include "Queen.h"
#include "Rules.h"

Piece::Type Queen::getPieceType() const
{
	return Piece::Type::QUEEN;
}

bool Queen::areSquaresValid(const Coords& c, const std::unique_ptr<Piece> board[8][8]) const
{
	if (c.startY == c.exitY)
	{
		return Rules::areIntermediateXSquaresEmpty(c, board);
	}
	else if (c.startX == c.exitX)
	{
		return Rules::areIntermediateYSquaresEmpty(c, board);
	}
	else if (Rules::isStartExitOnSameDiagonal(c))
	{
		return Rules::areIntermediateDiagonalSquaresEmpty(c, board);
	}
	return false;
}