#include "King.h"

King::Type King::getPieceType() const
{
	return Type::KING;
}

bool King::areSquaresValid(const Coords& c, const std::unique_ptr<Piece> board[8][8]) const
{
	return (
		( abs(c.exitX - c.startX) <= 1 ) &&
		( abs(c.exitY - c.startY) <= 1 )
		);
}

std::unique_ptr<Piece> King::clone() const
{
	return std::make_unique<King>(*this);
}
