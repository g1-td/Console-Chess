#include "Knight.h"

Knight::Type Knight::getPieceType() const
{
	return Type::KNIGHT;
}

bool Knight::areSquaresValid(const Coords& c, const std::unique_ptr<Piece> board[8][8]) const
{
	if ((c.startX == c.exitX + 1) || (c.startX == c.exitX - 1))
		if ((c.startY == c.exitY + 2) || (c.startY == c.exitY - 2))
			return true;
	
	if ((c.startX == c.exitX + 2) || (c.startX == c.exitX - 2))
		if ((c.startY == c.exitY + 1) || (c.startY == c.exitY - 1))
			return true;
		
	return false;
}

std::unique_ptr<Piece> Knight::clone() const
{
	return std::make_unique<Knight>(*this);
}
