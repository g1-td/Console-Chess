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
		brd = FEN::toPosition(fen);
	start();
}

void ChessGame::start()
{
	while (!gameOver())
	{
		callDraw();
		turn();
		nextTurn();
	}
}

void ChessGame::turn()
{
	auto& board = brd->board;
	auto& turn = brd->playerTurnColor;
	auto& turnCounter = brd->turnCounter;

	brd->expireEnPassantFlags();

	while (true)
	{
		std::cout << "\n\n>> ";
		std::string userInput = getParsedUserInput();

		if (!inputHasCommands(userInput))
		{
			Coords c = NotationToCoords::toCoords(board, turn, userInput);

			if (brd->isMoveLegal(c))
			{
				brd->setFlags(c);
				brd->updateRepetitionState(c);
				brd->movePiece(c);
				
				++turnCounter;
				break;
			}
			else invalidMove();
		}
	}
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

std::string ChessGame::getParsedUserInput()
{
	std::string userInput;
	std::cin >> userInput;

	return NotationToCoords::stringToUpper(userInput);
}
bool ChessGame::inputHasCommands(std::string userInput)
{
	if (userInput == "HELP")
	{
		system("cls");
		help();
		return true;
	}
	else if (userInput == "DRAW")
	{
		system("cls");
		draw();
		return true;
	}
	else if (userInput == "AUTO")
	{
		system("cls");
		callDrawToggle();
		return true;
	}
	return false;
}

bool ChessGame::callDrawToggle() { return (autoDraw = !autoDraw); }

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

bool ChessGame::CHECKMATE() const
{
	draw();

	std::string winner;
	(bool)brd->ReturnAlternateTurn() ? winner = "BLACK" : winner = "WHITE";

	std::cout << winner << " WON BY CHECKMATE!\n";

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
	std::cout << "Enter moves using Standard Chess notation\n";
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
void ChessGame::callDraw() const { autoDraw ? draw() : void(); }

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