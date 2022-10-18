#include "ChessGame.h"
#include "Rules.h"


void ChessGame::setupDefaultGame()
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

	playerTurn = Piece::Color::WHITE;
}

ChessGame::ChessGame()
{
	setupDefaultGame();
}

void ChessGame::start()
{
}

void ChessGame::turn()
{
}

void ChessGame::autoDrawToggle()
{
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
			helpers::drawCoordinates(sideCoordinatesNumber);
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

					if (board[y][x]->isPieceBlack())
						result = tolower(result);

					helpers::drawCoordinates(result);
					++xDrawingPosition;

					if (currentX == 7)
						std::cout << "\n";
				}
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

void ChessGame::helpers::drawCoordinates(int number)
{
	std::cout << "  " << number << "  |";
}

bool ChessGame::helpers::isNotFillerSpace(int number)
{
	return !(number % 2) && number != 0;
}