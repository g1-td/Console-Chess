#include "ChessGame.h"

ChessGame::ChessGame()
{
	newGame();
	start();
}

ChessGame::ChessGame(const std::string& _fen)
{
	newGame(_fen);
	start();
}

ChessGame::ChessGame(int _min, int _sec, int _inc)
{
	newGame();
	setTimers(_min, _sec, _inc);

	std::thread t1(&ChessGame::timerController, this);

	start();
	t1.join();
}

ChessGame::ChessGame(const std::string& _fen, int _min, int _sec, int _inc)
{
	newGame(_fen);
	setTimers(_min, _sec, _inc);

	std::thread t1(&ChessGame::timerController, this);

	start();
	t1.join();
}

void ChessGame::start()
{
	while (!gameOver())
	{
		visualize();

		makeMove(getUserInput());
	}
}

void ChessGame::newGame()
{
	brd = std::make_unique<Board>();
	brd->newGame();
}

void ChessGame::newGame(const std::string& _fen)
{
	if (FEN::isFenValid(_fen))
		brd = std::make_unique<Board>(FEN::toPosition(_fen));

	else brd->newGame();
}

bool ChessGame::makeMove(const Coords& _c)
{
	auto& board = brd->board;
	auto& turn = brd->playerTurnColor;
	auto& turnCounter = brd->turnCounter;

	brd->expireEnPassantFlags();

	if (!brd->isMoveLegal(_c))
	{
		// This prevents invalid move from being printed
		// when the user is using commands
		return Coords::cmpCoords(_c, InputHasCommandsCode()) ? false : invalidMove();
	}

	brd->setFlags(_c);
	brd->updateRepetitionState(_c);
	brd->movePiece(_c);

	++turnCounter;
	nextTurn();
	firstMove = true;

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

	else if (brd->isTimed && brd->timeOut) return TIMEOUT();

	else return false;
}

Coords ChessGame::getUserInput()
{
	std::cout << "\n>> ";

	std::string userInput;
	std::getline(std::cin, userInput);

	if (hasCommands(userInput)) // returns bool ~~AND~~ executes commands
		return InputHasCommandsCode();

	else return NotationToCoords::toCoords(brd->board, brd->playerTurnColor, userInput);
}

Coords ChessGame::InputHasCommandsCode()
{
	return Coords{ 1,1,1,1 };
}

void ChessGame::setTimers(int _min, int _sec, int _inc)
{
	brd->whiteTimer = Timer(_min, _sec, _inc);
	brd->blackTimer = Timer(_min, _sec, _inc);
	brd->isTimed = true;
}

void ChessGame::timerController()
{
	Timer* prevTimer = currentPlayersTimer();

	while (!firstMove) { std::this_thread::sleep_for(std::chrono::milliseconds(100)); }

	while (!currentPlayersTimer()->isZero())
	{
		currentPlayersTimer()->countDown();

		if (prevTimer != currentPlayersTimer())
		{
			prevTimer->addIncrement();
			prevTimer = currentPlayersTimer();
		}
	}
	brd->timeOut = true;
}

Timer* ChessGame::currentPlayersTimer()
{
	return brd->playerTurnColor == Piece::Color::WHITE ?
		&brd->whiteTimer : &brd->blackTimer;
}

bool ChessGame::hasCommands(std::string str)
{
	/*
	
		TODO: 
		Make this into a menu system with options instead

	*/


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

bool ChessGame::callDrawToggle() { return autoDraw = !autoDraw; }

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

bool ChessGame::TIMEOUT() const
{
	draw();
	const char* winner;
	(bool)brd->ReturnAlternateTurn() ? winner = "white" : winner = "black";

	std::cout << "\nToo slow, " << winner << " won on time!\n";

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

	if (brd->isTimed) drawRemainingTime();
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

void ChessGame::drawRemainingTime() const
{
	// EXAMPLE : 2min 20sec

	// 2 min
	int whiteMinutes = (brd->whiteTimer.getTimeMillis() / 1000) / 60;
	int blackMinutes = (brd->blackTimer.getTimeMillis() / 1000) / 60;

	// 20 sec 
	int whiteSeconds = (brd->whiteTimer.getTimeMillis() / 1000) % 60;
	int blackSeconds = (brd->blackTimer.getTimeMillis() / 1000) % 60;

	std::cout << "White : " << whiteMinutes << "min : " << whiteSeconds << "sec" << std::endl;
	std::cout << "Black : " << blackMinutes << "min : " << blackSeconds << "sec" << std::endl;
}