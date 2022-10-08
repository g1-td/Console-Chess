#include "Bishop.h"
#include "Rules.h"

Piece::Type Bishop::getPieceType() const
{
	return Piece::Type::B;
}

bool Bishop::areSquaresValid(const Coords& c, const std::unique_ptr<Piece> board[8][8]) const
{
	if (Rules::isStartExitOnSameDiagonal(c))
	{
		return Rules::areIntermediateDiagonalSquaresEmpty(c, board);
	}
	return false;
}