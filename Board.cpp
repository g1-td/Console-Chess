#include "Board.h"

Board::Board()
{
}

Board::Board(const Board& brd)
{
	copyBoard(brd.board, board);
	playerTurnColor = brd.playerTurnColor;
	fiftyMoveCounter = brd.fiftyMoveCounter;
	threeFoldCounter = brd.threeFoldCounter;
	turnCounter = brd.turnCounter;
}

bool Board::isKingInCheck() const
{
	Coords c;
	Coords king = findKing();

	c.exitX = king.startX;
	c.exitY = king.startY;

	auto enemyTurnColor = ReturnAlternateTurn();

	for (int y = 0; y < 8; ++y)
	{
		for (int x = 0; x < 8; ++x)
		{
			c.startX = x;
			c.startY = y;

			if (board[y][x]->isSquareOccupied() &&
				board[y][x]->isPieceColor(enemyTurnColor) &&
				isMoveLegal(c))
			{
				return true;
			}
		}
	}
	return false;
}

bool Board::playerHasLegalMoves() const
{
	Coords c;

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			if (board[y][x]->isSquareOccupied() &&
				board[y][x]->isPieceColor(playerTurnColor))
			{
				c.startY = y;
				c.startX = x;

				for (int yd = 0; yd < 8; yd++)
				{
					for (int xd = 0; xd < 8; xd++)
					{
						c.exitY = yd;
						c.exitX = xd;

						if (isMoveLegal(c)) return true;
					}
				}
			}
		}
	}
	return false;
}

bool Board::isMoveLegal(const Coords& c) const
{
	Piece* start = board[c.startY][c.startX].get();
	Piece* exit = board[c.exitY][c.exitX].get();

	if (start->isSquareOccupied() &&
		start->isPieceColor(playerTurnColor))
	{
		if (!exit->isSquareOccupied() ||
			!exit->isPieceColor(playerTurnColor))
		{
			if (start->areSquaresValid(c, board))
			{
				if (exit->isSquareOccupied() &&
					exit->isPieceType(Piece::Type::KING) &&
					!exit->isPieceColor(playerTurnColor))
				{
					return true;
				}

				Board boardCopy;
				copyBoard(board, boardCopy.board);
				boardCopy.movePiece(c);
				
				return !boardCopy.isKingInCheck();
			}
		}
	}
	return false;
}

bool Board::isKingOrRook(const Coords& c) const
{
	return board[c.startY][c.startX]->isPieceType(Piece::Type::KING) ||
		board[c.startY][c.startX]->isPieceType(Piece::Type::ROOK);
}

bool Board::isPawnMovedTwice(const Coords& c) const
{
	return (board[c.startY][c.startX]->isPieceType(Piece::Type::PAWN) &&
		c.exitY == c.startY + (2 * Piece::getPawnMoveDirection(playerTurnColor))) ? true : false;
}

bool Board::cmpBoard(const std::unique_ptr<Piece> other[8][8]) const
{
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			if (board[y][x]->isSquareOccupied() && other[y][x]->isSquareOccupied())
			{
				if (board[y][x]->getPieceColor() != other[y][x]->getPieceColor() ||
					board[y][x]->getPieceType() != other[y][x]->getPieceType())
				{
					return false;
				}
			}
			else if (board[y][x]->isSquareOccupied() != other[y][x]->isSquareOccupied())
				return false;
		}
	}
	return true;
}

bool Board::fiftyMove_check() const
{
	//	A turn is finished after both sides move
	//	the counter is incremented after each side moves
	//	and is thus doubled to account for this.
	return fiftyMoveCounter == 100 ? true : false;
}

bool Board::threeFold_check() const
{
	return threeFoldCounter == 3 ? true : false;
}

bool Board::isBeginningOfTurn() const
{
	// Turn is finished after BOTH sides 
	return turnCounter % 2 == 0;
}

void Board::fiftyMove_count(const Coords& c)
{
	Piece* start = board[c.startY][c.startX].get();
	Piece* exit = board[c.exitY][c.exitX].get();

	if (start->isPieceType(Piece::Type::PAWN) ||
		exit->isSquareOccupied())
	{
		fiftyMoveCounter = 0;
	}
	else ++fiftyMoveCounter;
}

void Board::threeFold_count(const Coords& c)
{
	Piece* start = board[c.startY][c.startX].get();
	Piece* exit = board[c.exitY][c.exitX].get();

	if (start->isPieceType(Piece::Type::PAWN) ||
		exit->isSquareOccupied())
	{
		threeFoldCounter = 0;
		threeFoldCoordsArray.clear();
	}
	else if (isBeginningOfTurn())
	{
		bool wasRepeated = false;
		for (auto& pos : threeFoldCoordsArray)
		{
			if (cmpBoard(pos.board))
			{
				threeFoldCounter = pos.repeated++;
				wasRepeated = true;
				break;
			}
		}

		if (!wasRepeated)
			threeFoldCoordsArray.push_back(board);
	}
}

void Board::updateRepetitionState(const Coords& c)
{
	threeFold_count(c);
	fiftyMove_count(c);
}

void Board::expireEnPassantFlags()
{
	for (int y = 3; y < 5; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			Piece* sqr = board[y][x].get();

			if (sqr->isSquareOccupied() &&
				sqr->isPieceType(Piece::Type::PAWN) &&
				sqr->isPieceColor(playerTurnColor))
			{
				sqr->setMovedFlag(false);
			}
		}
	}
}

void Board::removePawnsTakenEnPassant(const Coords& c)
{
	/*
	*	This is a HORRIBLE way of doing things as runs on each move.
	*	But given that everything else is const and I have no way of knowing
	*	if something is a pawn I'm sort of forced into this for now...
	*/
	if (board[c.startY][c.startX - 1]->isSquareOccupied() &&
		board[c.startY][c.startX - 1]->getMovedFlag())
	{
		board[c.startY][c.startX - 1] = nullptr;
	}
	else if (board[c.startY][c.startX + 1]->isSquareOccupied() &&
		board[c.startY][c.startX + 1]->getMovedFlag())
	{
		board[c.startY][c.startX + 1] = nullptr;
	}
}

void Board::newGame()
{
	board[0][0] = std::make_unique<Rook>(Piece::Color::WHITE);
	board[0][1] = std::make_unique<Knight>(Piece::Color::WHITE);
	board[0][2] = std::make_unique<Bishop>(Piece::Color::WHITE);
	board[0][3] = std::make_unique<Queen>(Piece::Color::WHITE);
	board[0][4] = std::make_unique<King>(Piece::Color::WHITE);
	board[0][5] = std::make_unique<Bishop>(Piece::Color::WHITE);
	board[0][6] = std::make_unique<Knight>(Piece::Color::WHITE);
	board[0][7] = std::make_unique<Rook>(Piece::Color::WHITE);
	for (int i = 0; i < 8; i++)
	{
		board[1][i] = std::make_unique<Pawn>(Piece::Color::WHITE);
	}

	board[7][0] = std::make_unique<Rook>(Piece::Color::BLACK);
	board[7][1] = std::make_unique<Knight>(Piece::Color::BLACK);
	board[7][2] = std::make_unique<Bishop>(Piece::Color::BLACK);
	board[7][3] = std::make_unique<Queen>(Piece::Color::BLACK);
	board[7][4] = std::make_unique<King>(Piece::Color::BLACK);
	board[7][5] = std::make_unique<Bishop>(Piece::Color::BLACK);
	board[7][6] = std::make_unique<Knight>(Piece::Color::BLACK);
	board[7][7] = std::make_unique<Rook>(Piece::Color::BLACK);
	for (int i = 0; i < 8; i++)
	{
		board[6][i] = std::make_unique<Pawn>(Piece::Color::BLACK);
	}

	playerTurnColor = Piece::Color::WHITE;
}

void Board::setFlags(const Coords& c)
{
	if (isPawnMovedTwice(c) || isKingOrRook(c))
		setFlagTrue(c);

	removePawnsTakenEnPassant(c);
}

void Board::setFlagTrue(const Coords& c)
{
	board[c.startY][c.startX]->setMovedFlag(true);
}

void Board::movePiece(const Coords& c)
{
	board[c.exitY][c.exitX] = std::move(board[c.startY][c.startX]);

	if (board[c.exitY][c.exitX]->isPieceType(Piece::Type::KING))
	{
		int direction = Piece::getExitToStartDirection(c.startX, c.exitX);
		int rookXCoords = direction == 1 ? 0 : 7;

		board[c.startY][c.startX - direction] = std::move(board[c.exitY][rookXCoords]);
	}
}

void Board::copyBoard(const std::unique_ptr<Piece> original[8][8], std::unique_ptr<Piece> copy[8][8])
{
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			auto sqr = original[y][x].get();

			if (sqr->isSquareOccupied())
				copy[y][x] = sqr->clone();
		}
	}
}

Piece::Color Board::ReturnAlternateTurn() const
{
	auto WHITE = Piece::Color::WHITE;
	auto BLACK = Piece::Color::BLACK;

	return playerTurnColor == WHITE ? BLACK : WHITE;
}

Piece::Color Board::alternateTurn()
{
	return playerTurnColor = ReturnAlternateTurn();
}

Coords Board::findKing() const
{
	// Only startX & Y are used
	Coords c;

	// Initialize to impossible Coords
	// if returned king is not found
	c.startX = 10;

	for (int y = 0; y < 8; ++y)
	{
		for (int x = 0; x < 8; ++x)
		{
			if (board[y][x]->isSquareOccupied() &&
				board[y][x]->isPieceColor(playerTurnColor) &&
				board[y][x]->isPieceType(Piece::Type::KING))
			{
				c.startY = y;
				c.startX = x;

				return c;
			}
		}
	}
	return c;
}
