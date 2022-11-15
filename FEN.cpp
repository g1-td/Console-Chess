#include "FEN.h"

std::string FEN::toString(const std::unique_ptr<Board>& brd)
{
	std::string fen;

	fen = boardToStr(brd->board);
	fen += ' ';

	fen += colorToChar(brd->playerTurnColor);
	fen += ' ';

	fen += hasMovedKingRook(brd->board);
	fen += ' ';

	fen += enPassantCapture(brd->board, brd->playerTurnColor);
	fen += ' ';

	fen += std::to_string(brd->fiftyMoveCounter);
	fen += ' ';

	int nextFullTurnCounter = ((brd->turnCounter + 1) / 2);
	fen += std::to_string(nextFullTurnCounter);

	return fen;
}

std::unique_ptr<Board> FEN::toPosition(std::string fen)
{
	/* ASSUME VALID FEN */
	std::unique_ptr<Board> brd = std::make_unique<Board>();

	auto lfen = cutTillSpace(fen);
	strToBoard(lfen, brd->board);

	lfen = cutTillSpace(fen);
	brd->playerTurnColor = charToColor(lfen[0]);

	lfen = cutTillSpace(fen);
	setCastleFlags(brd->board, lfen);

	lfen = cutTillSpace(fen);
	setEnPassantFlag(brd->board, lfen);

	lfen = cutTillSpace(fen);
	brd->fiftyMoveCounter = NotationToCoords::charToInt(lfen[0]);

	lfen = cutTillSpace(fen);
	brd->turnCounter = NotationToCoords::charToInt(lfen[0]);

	return brd;
}

bool FEN::isFenValid(std::string fen)
{
	// TODO
	return true;
}

std::string FEN::boardToStr(const std::unique_ptr<Piece> board[8][8])
{
	std::string fen;

	for (int y = 7; y > -1; y--)
	{
		int counter = 0;
		for (int x = 0; x < 8; x++)
		{
			char result{}; // equals nothing by default
			if (board[y][x]->isSquareOccupied())
			{
				result = (char)board[y][x]->getPieceType();

				if (board[y][x]->isPieceColor(Piece::Color::BLACK))
					result = tolower(result);

				if (counter != 0)
					fen += std::to_string(counter);

				fen += result;
				counter = 0;
			}
			else counter++;

			if (x == 7 && y != 0)
			{
				if (counter != 0)
					fen += std::to_string(counter);
				fen += '/';
			}
		}
	}
	return fen;
}

std::string FEN::hasMovedKingRook(const std::unique_ptr<Piece> board[8][8])
{
	std::string moved;
	if (board[0][7]->isSquareOccupied() && !board[0][7]->getMovedFlag()) { moved += "K"; }
	if (board[0][0]->isSquareOccupied() && !board[0][0]->getMovedFlag()) { moved += "Q"; }
	if (board[7][7]->isSquareOccupied() && !board[7][7]->getMovedFlag()) { moved += "k"; }
	if (board[0][7]->isSquareOccupied() && !board[0][7]->getMovedFlag()) { moved += "q"; }

	if (moved.length() == 0) { moved += "-"; }

	return moved;
}

std::string FEN::enPassantCapture(const std::unique_ptr<Piece> board[8][8], const Piece::Color& color)
{
	std::string ep;
	Coords c;

	for (int y = 3; y < 5; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			Piece* sqr = board[y][x].get();

			if (sqr->isSquareOccupied() &&
				sqr->isPieceType(Piece::Type::PAWN) &&
				sqr->isPieceColor(color))
			{
				int dir = Piece::getPawnMoveDirection(color);

				c.startX = x;
				c.startY = y;
				c.exitY += dir;

				std::unique_ptr<Board> ng = std::make_unique<Board>();
				Board::copyBoard(board, ng->board);
				ng->playerTurnColor = color;

				if (x - 1 > 0)
				{
					c.exitX += x - 1;

					if (!ng->board[c.exitY][c.exitX]->isSquareOccupied() &&
						ng->isMoveLegal(c))
					{
						ep += std::to_string((char)(c.exitX + 65));
						ep += std::to_string(c.exitY);
					}

				}
				if (x + 1 < 7)
				{
					c.exitX += x + 1;

					if (!ng->board[c.exitY][c.exitX]->isSquareOccupied() &&
						ng->isMoveLegal(c))
					{
						ep += std::to_string((char)(c.exitX + 65));
						ep += std::to_string(c.exitY);
					}
				}
			}
		}
	}
	return ep.length() == 0 ? "-" : ep;
}

char FEN::colorToChar(const Piece::Color& color)
{
	return (int)color == 0 ? 'w' : 'b';
}

void FEN::setEnPassantFlag(const std::unique_ptr<Piece> board[8][8], const std::string& str)
{
	if (str[0] != '-')
	{
		int x = NotationToCoords::colCharToInt(str[0]) - 1;
		int y = NotationToCoords::charToInt(str[1]) - 1;

		y == 3 ? y += 1 : y += -1;

		board[y][x]->setMovedFlag(true);
	}
}

void FEN::setCastleFlags(const std::unique_ptr<Piece> board[8][8], const std::string& str)
{
	for (int i = 0; i < str.length(); i++)
	{
		     if (str[i] == 'K') board[0][7]->setMovedFlag(true);
		else if (str[i] == 'Q') board[0][0]->setMovedFlag(true);
		else if (str[i] == 'k') board[7][7]->setMovedFlag(true);
		else if (str[i] == 'q') board[7][0]->setMovedFlag(true);
	}
}

Piece::Color FEN::charToColor(const char& c)
{
	if (c == 'w') return Piece::Color::WHITE;
	if (c == 'b') return Piece::Color::BLACK;
}

void FEN::strToBoard(const std::string& str, std::unique_ptr<Piece> board[8][8])
{
	/*
		FEN str is parsed
		Top Left to
		Bottom Right
	*/

	int y = 7, x = 0;
	for (int i = 0; i < str.length(); i++)
	{
		char fchar = str[i];
		auto color = isupper((int)fchar) ? Piece::Color::WHITE : Piece::Color::BLACK;

		fchar = toupper(fchar);
		switch (fchar)
		{
			case 'R':
			board[y][x] = std::make_unique<Rook>(color);
			++x;
			break;

			case 'N':
			board[y][x] = std::make_unique<Knight>(color);
			++x;
			break;

			case 'B':
			board[y][x] = std::make_unique<Bishop>(color);
			++x;
			break;

			case 'Q':
			board[y][x] = std::make_unique<Queen>(color);
			++x;
			break;

			case 'K':
			board[y][x] = std::make_unique<King>(color);
			++x;
			break;

			case 'P':
			board[y][x] = std::make_unique<Pawn>(color);
			++x;
			break;

			case '/':
			x = 0;
			--y;
			break;

			default:
			x += (int)fchar - '0';
			break;
		}
	}
}

std::string FEN::cutTillSpace(std::string& str)
{
	int space = str.find(' ');
	auto lfen = str.substr(0, space);

	space += 1;
	str = str.substr(space, str.length());
	return lfen;
}
