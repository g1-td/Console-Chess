#include "Rook.h"

Rook::Type Rook::getPieceType() const
{
	return Type::ROOK;
}

bool Rook::areSquaresValid(const Coords& c, const std::unique_ptr<Piece> board[8][8]) const
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

std::unique_ptr<Piece> Rook::clone() const
{
	return std::make_unique<Rook>(*this);
}
