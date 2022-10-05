#include "King.h"

Piece::Type King::getPieceType() const
{
	return Piece::Type::K;
}

bool King::areSquaresValid(const Coords& c, const Piece* board[8][8]) const
{
	return (
		( abs(c.exitX - c.startX) <= 1 ) &&
		( abs(c.exitY - c.startY) <= 1 )
		);
}
