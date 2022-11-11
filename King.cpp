#include "King.h"

King::Type King::getPieceType() const
{
	return Type::KING;
}

bool King::areSquaresValid(const Coords& c, const std::unique_ptr<Piece> board[8][8]) const
{


	if ((abs(c.exitX - c.startX) <= 1) && (abs(c.exitY - c.startY) <= 1))
		return true;

	else if (c.startY == c.exitY && abs((c.startX - c.exitX)) == 2)
	{
		int direction = Piece::getExitToStartDirection(c.startX, c.exitX);
		int rookXCoords = direction == 1 ? 0 : 7;

		Piece* rook = board[c.startY][rookXCoords].get();
		Piece* king = board[c.startY][c.startX].get();

		if (king->getMovedFlag() == false)
		{
			if (rook->isSquareOccupied() &&
				rook->isPieceType(Piece::Type::ROOK) &&
				rook->isPieceColor(pieceColor) &&
				rook->getMovedFlag() == false)
			{
				if (areIntermediateXSquaresEmpty(c, board))
				{
					std::unique_ptr<Board> CopyBoard = std::make_unique<Board>();
					Board::copyBoard(board, CopyBoard->board);
					CopyBoard->playerTurnColor = pieceColor;

					Coords c1;
					Coords::copyCoords(c, c1);
					c1.exitX = c.startX - direction;
					CopyBoard->movePiece(c1);

					return !CopyBoard->isKingInCheck();
				}
			}
		}
	}
	return false;
}

std::unique_ptr<Piece> King::clone() const
{
	return std::make_unique<King>(*this);
}
