#include "Knight.h"

Piece::Type Knight::getPieceType() const
{
	return Piece::Type::N;
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