#include "ChessGame.h"
#include "Rules.h"

ChessGame::ChessGame()
{
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

				if (board[y][x]->isSquareNotEmpty())
				{
					result = (char) board[y][x]->getPieceType();

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