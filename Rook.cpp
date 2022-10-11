#include "Rook.h"
#include "Rules.h"

Piece::Type Rook::getPieceType() const
{
	return Piece::Type::ROOK;
}

bool Rook::areSquaresValid(const Coords& c, const std::unique_ptr<Piece> board[8][8]) const
{
	if (c.startY == c.exitY)
	{
		return Rules::areIntermediateXSquaresEmpty(c, board);
	}
	else if (c.startX == c.exitX)
	{
		return Rules::areIntermediateYSquaresEmpty(c, board);
	}
	return false;
}