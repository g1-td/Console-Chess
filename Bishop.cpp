#include "Bishop.h"
#include "Rules.h"

Bishop::Type Bishop::getPieceType() const
{
	return Type::BISHOP;
}

bool Bishop::areSquaresValid(const Coords& c, const std::unique_ptr<Piece> board[8][8]) const
{
	if (Rules::isStartExitOnSameDiagonal(c))
	{
		return Rules::areIntermediateDiagonalSquaresEmpty(c, board);
	}
	return false;
}