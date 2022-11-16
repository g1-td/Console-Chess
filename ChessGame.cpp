#include "ChessGame.h"

ChessGame::ChessGame()
{
	brd = std::make_unique<Board>();
	brd->newGame();
	start();
}

ChessGame::ChessGame(const std::string& fen)
{
	if (FEN::isFenValid(fen))
		brd = std::make_unique<Board>(FEN::toPosition(fen));

	else brd->newGame();

	start();
}

void ChessGame::start()
{
	while (!gameOver())
	{
		visualize();

		auto c = getUserInput();

		makeMove(c);
	}
	system("break");
}

void ChessGame::newGame()
{
	brd.release();
	brd = std::make_unique<Board>();
	brd->newGame();
}

bool ChessGame::makeMove(const Coords& c)
{
	auto& board = brd->board;
	auto& turn = brd->playerTurnColor;
	auto& turnCounter = brd->turnCounter;

	brd->expireEnPassantFlags();

	if (!brd->isMoveLegal(c))
	{
		return Coords::cmpCoords(c, InputHasCommandsCode()) ? false : invalidMove();
	}

	brd->setFlags(c);
	brd->updateRepetitionState(c);
	brd->movePiece(c);

	++turnCounter;
	nextTurn();
	return true;
}

void ChessGame::nextTurn()
{
	brd->alternateTurn();
}

bool ChessGame::gameOver() const
{
	if (!brd->playerHasLegalMoves())
		return brd->isKingInCheck() ? CHECKMATE() : STALEMATE();

	else if (brd->fiftyMove_check() || brd->threeFold_check())
		return STALEMATE();

	else return false;
}

Coords ChessGame::getUserInput()
{
	std::cout << "\n>> ";
	std::string userInput;
	std::getline(std::cin, userInput);

	if (hasCommands(userInput)) // returns bool ~~AND~~ executes commands
		return InputHasCommandsCode();

	else
		return NotationToCoords::toCoords(brd->board, brd->playerTurnColor, userInput);
}

Coords ChessGame::InputHasCommandsCode()
{
	return Coords{ 1,1,1,1 };
}

bool ChessGame::hasCommands(std::string str)
{
	if (FEN::isFenValid(str))
	{
		brd = std::make_unique<Board>(FEN::toPosition(str));
		return true;
	}

	NotationToCoords::stringToUpper(str);

	if (str == "HELP" || str == "?")
	{
		// system("cls");
		help();
		return true;
	}
	else if (str == "DRAW")
	{
		// system("cls");
		draw();
		return true;
	}
	else if (str == "AUTO")
	{
		system("cls");

		auto status = autoDraw ? "Enabled" : "Disabled";
		std::cout << "AutoDraw has been " << status;

		callDrawToggle();
		return true;
	}
	else if (str == "RESET" || str == "RESTART" || str == "-r")
	{
		newGame();
		return true;
	}
	else if (str == "CLEAR" || str == "CLS")
	{
		system("cls");
		return true;
	}
	else if (str == "FEN")
	{
		std::cout << "\n\n\n\n" << FEN::toString(brd) << "\n\n";
		return true;
	}

	else return false;
}

bool ChessGame::callDrawToggle() { return (autoDraw = !autoDraw); }

bool ChessGame::invalidMove()
{
	std::cout << "\n\n     Move Invalid.\n";
	return false;
}

bool ChessGame::CHECKMATE() const
{
	draw();

	std::string winner;
	(bool)brd->ReturnAlternateTurn() ? winner = "BLACK" : winner = "WHITE";

	std::cout << "\nCHECKMATE, " << winner << " IS VICTORIOUS!\n";

	return true;
}

bool ChessGame::STALEMATE() const
{
	draw();
	std::cout << "STALEMATE!";

	return true;
}
void ChessGame::help()
{
	std::cout << "\n\nEnter moves using Standard Chess notation\n";
	std::cout << "Examples: \"e4\", \"exd5\", \"Neg3\"\n\n";
	std::cout << "COMMANDS : \n";
	std::cout << "\"draw\" - Draws the current board position\n";
	std::cout << "\"auto\" - Toggle calling draw after every turn\n";
}

void ChessGame::draw() const
{
	/*
	*  Drawing is happening
	*  Top to Bottom
	*  Left to Right
	*/

	drawLineA();

	int sideCoordinatesNumber = 8;
	for (int totalRow = 16; totalRow > 0; --totalRow)
	{
		if (isNotFillerSpace(totalRow))
		{
			std::cout << "  " << sideCoordinatesNumber << "  |";
			--sideCoordinatesNumber;

			auto board = brd->board;
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
		else drawLineA();
	}
	drawFooter();
}
void ChessGame::visualize() const { autoDraw ? draw() : void(); }

void ChessGame::drawLineA()
{
	std::cout << "     |-------------------------------|\n";
}

void ChessGame::drawFooter()
{
	std::cout << "       a   b   c   d   e   f   g   h\n";
}

bool ChessGame::isNotFillerSpace(int number)
{
	return !(number % 2) && number != 0;
}