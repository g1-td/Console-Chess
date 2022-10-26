#include "ChessGame.h"


ChessGame::ChessGame()
{
	setupDefaultBoard();
	start();
}

void ChessGame::start()
{
	while (!gameOver())
	{
		callDraw();

		turn();
		alternateTurn();
	}
}

void ChessGame::turn()
{
	while (true)
	{
		std::cout << "Enter Move:\n\n >> ";

		std::string userInput;
		std::cin >> userInput;
		stringToUpper(userInput);

		if (!InputHasCommands(userInput))
		{
			Coords c = NotationToCoords(board, playerTurnColor, userInput);

			if (isMoveLegal(c, board, playerTurnColor))
			{
				movePiece(c, board);
				break;
			}
			else invalidMove();
		}
	}
}

bool ChessGame::isMoveLegal(const Coords& c, const std::unique_ptr<Piece> board[8][8], const Piece::Color& playerTurnColor)
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
				std::unique_ptr<Piece> boardCopy[8][8];
				copyBoard(board, boardCopy);

				movePiece(c, boardCopy);

				return !isKingInCheck(boardCopy, playerTurnColor);
			}
		}
	}
	return false;
}
Coords ChessGame::findKing(const std::unique_ptr<Piece> board[8][8], const Piece::Color& playerTurnColor)
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
bool ChessGame::gameOver() const
{
	bool hasMoves = doesPlayerHaveMoves(board, playerTurnColor);

	if (!hasMoves)
	{
		isKingInCheck(board, playerTurnColor) ? CHECKMATE() : STALEMATE();
		return true;
	}
	else return false;
}
bool ChessGame::isKingInCheck(const std::unique_ptr<Piece> board[8][8], const Piece::Color& playerTurnColor)
{
	Coords c;
	Coords king = findKing(board, playerTurnColor);

	c.exitX = king.startX;
	c.exitY = king.startY;

	auto enemyTurnColor = ReturnAlternateTurn(playerTurnColor);

	for (int y = 0; y < 8; ++y)
	{
		for (int x = 0; x < 8; ++x)
		{
			c.startX = x;
			c.startY = y;

			if (board[y][x]->isSquareOccupied() &&
				board[y][x]->isPieceColor(enemyTurnColor) &&
				isMoveLegal(c, board, enemyTurnColor))
			{
				return true;
			}
		}
	}
	return false;
}
bool ChessGame::doesPlayerHaveMoves(const std::unique_ptr<Piece> board[8][8], const Piece::Color& playerTurnColor)
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

						if (isMoveLegal(c, board, playerTurnColor)) return true;
					}
				}
			}
		}
	}
	return false;
}

void ChessGame::movePiece(const Coords& c, std::unique_ptr<Piece> b[8][8])
{
	b[c.exitY][c.exitX] = std::move(b[c.startY][c.startX]);
}
void ChessGame::copyBoard(const std::unique_ptr<Piece> original[8][8], std::unique_ptr<Piece> copy[8][8])
{
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			auto sqr = original[y][x].get();

			if (sqr->isSquareOccupied())
			{
				copy[y][x] = sqr->clone();
			}
		}
	}
}
Piece::Color ChessGame::ReturnAlternateTurn(const Piece::Color& playerTurnColor)
{
	auto WHITE = Piece::Color::WHITE;
	auto BLACK = Piece::Color::BLACK;

	return playerTurnColor == WHITE ? BLACK : WHITE;
}
void ChessGame::alternateTurn() { playerTurnColor = ReturnAlternateTurn(playerTurnColor); }
void ChessGame::setupDefaultBoard()
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
bool ChessGame::InputHasCommands(const std::string& input)
{
	if (input == "HELP")
	{
		system("cls");
		help();
		return true;
	}
	else if (input == "DRAW")
	{
		system("cls");
		draw();
		return true;
	}
	else if (input == "AUTO")
	{
		system("cls");
		callDrawToggle();
		return true;
	}
	return false;
}

bool ChessGame::callDrawToggle() { return (autoDraw = !autoDraw); }
void ChessGame::callDraw() const { autoDraw ? draw() : void(); }
void ChessGame::invalidMove()
{
	/*
		TODO :

		Add a reason why the move was invalid
		such as "No BISHOP found on e2"

		This is kind of useless and work for the sake of work,
		but it might be kinda cool for somebody who can't play chess
		so consider adding it after everything else is finished!
	*/
	std::cout << "Move is Invalid.\n\n";
}
void ChessGame::CHECKMATE() const
{
	draw();

	std::string winner;
	(bool)ReturnAlternateTurn(playerTurnColor) ? winner = "BLACK" : winner = "WHITE";

	std::cout << winner << " WON BY CHECKMATE!\n";
}
void ChessGame::STALEMATE() const
{
	draw();
	std::cout << "STALEMATE!";
}
void ChessGame::draw() const
{
	/*
	*  Drawing is happening
	*  Top to Bottom
	*  Left to Right
	*/

	helpers::drawLineA();

	int sideCoordinatesNumber = 8;
	for (int totalRow = 16; totalRow > 0; --totalRow)
	{
		if (helpers::isNotFillerSpace(totalRow))
		{
			std::cout << "  " << sideCoordinatesNumber << "  |";
			--sideCoordinatesNumber;

			int xDrawingPosition = 0;
			for (int currentX = 0; currentX < 8; currentX++)
			{
				// Default is a SPACE (ASCII - 32)
				char result = ' ';

				int y = sideCoordinatesNumber;
				int x = xDrawingPosition;

				if (board[y][x]->isSquareOccupied())
				{
					result = (char)board[y][x]->getPieceType();

					if (board[y][x]->isPieceColor(Piece::Color::BLACK))
						result = tolower(result);
				}

				std::cout << " " << result << " |";
				++xDrawingPosition;

				if (currentX == 7)
					std::cout << "\n";
			}
		}
		else helpers::drawLineA();
	}
	helpers::drawFooter();
}
void ChessGame::help()
{
	std::cout << "Enter moves using Standard Chess notation\n";
	std::cout << "Examples: \"e4\", \"exd5\", \"Neg3\"\n";
	std::cout << "COMMANDS : \n\n";
	std::cout << "\"draw\" - Draws the current board position\n";
	std::cout << "\"auto\" - Toggle calling draw after every turn\n";
}
void ChessGame::helpers::drawLineA()
{
	std::cout << "     |-------------------------------|\n";
}
void ChessGame::helpers::drawFooter()
{
	std::cout << "       a   b   c   d   e   f   g   h\n";
}
bool ChessGame::helpers::isNotFillerSpace(int number)
{
	return !(number % 2) && number != 0;
}