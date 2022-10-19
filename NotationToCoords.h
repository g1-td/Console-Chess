#include <memory>
#include <string>
#include <map>
#include "Coords.h"
#include "Piece.h"
#pragma once

namespace
{
	std::string stringToUpper(std::string& str)
	{
		for (char& currentChar : str) { currentChar = toupper(currentChar); }
		return str;
	}
	std::string cutStringInHalf(std::string& notationString, bool isXinString) { return notationString.substr(0, notationString.length() - (2 + isXinString)); }
	int colCharToInt(char c)
	{
		// return 0 means char is NOT 'A' through 'H'

		std::map<char, int> col;

		col['A'] = 1;
		col['B'] = 2;
		col['C'] = 3;
		col['D'] = 4;
		col['E'] = 5;
		col['F'] = 6;
		col['G'] = 7;
		col['H'] = 8;

		return col[c];
	}
	int coordNumberToInt(char c) { return c - '0'; }
	bool isInvalidColCoordinate(char c) { return colCharToInt(c) == 0; }
	bool notationStringInvalidLength(const std::string& notationString) { return notationString.length() < 2 || notationString.length() > 5; }
	bool isXinNotationString(const std::string& notationString) { return notationString[notationString.length() - 3] == 'X'; }
	bool areLastTwoCoordsNotValid(char last, char preLast) { return !isdigit(last) || isInvalidColCoordinate(preLast); }
	bool isCastling(const std::string notationString) { return notationString[0] == 'O'; }
	bool isKingSideCastle(const std::string notationString) { return notationString == "O-O"; }
	bool isQueenSideCastle(const std::string notationString) { return notationString == "O-O-O"; }
	bool isPawnAdvance(const std::string notationString) { return notationString.length() == 2; }
	Coords invalidCoords() { Coords c; return c; }
	Coords kingSideCastle(const Piece::Color playerTurn)
	{
		Coords c;
		int kingCoords = playerTurn == Piece::Color::BLACK ? 7 : 0;

		c.startX = 4;
		c.exitX = 6;
		c.startY = kingCoords;
		c.exitY = kingCoords;

		return c;
	}
	Coords queenSideCastle(const Piece::Color playerTurn)
	{
		Coords c;
		int kingCoords = playerTurn == Piece::Color::BLACK ? 7 : 0;

		c.startX = 4;
		c.exitX = 2;
		c.startY = kingCoords;
		c.exitY = kingCoords;

		return c;
	}
	Coords castle(const Piece::Color playerTurn, const std::string notationString)
	{
		if (isKingSideCastle(notationString))
			return kingSideCastle(playerTurn);

		if (isQueenSideCastle(notationString))
			return queenSideCastle(playerTurn);

		else return invalidCoords();
	}
	Coords pawnAdvance(const std::unique_ptr<Piece> board[8][8], Coords c, int direction)
	{
		c.startX = c.exitX;

		for (int i = 1; i < 3; i++)
		{

			int y = c.exitY - (direction * i);
			int x = c.exitX;

			if (board[y][x]->isSquareOccupied() &&
				board[y][x]->isPieceType(Piece::Type::PAWN))
			{
				c.startY = y;
				return c;
			}
		}
		return invalidCoords();
	}

	static Coords NotationToCoords(const std::unique_ptr<Piece> board[8][8], const Piece::Color playerTurn, std::string notationString)
	{
		Coords c;
		stringToUpper(notationString);

		if (notationStringInvalidLength(notationString)) return invalidCoords();
		if (isCastling(notationString)) return castle(playerTurn, notationString);

		char lastChar = notationString[notationString.length() - 1];
		char preLastChar = notationString[notationString.length() - 2];

		if (areLastTwoCoordsNotValid(lastChar, preLastChar)) return invalidCoords();

		/* 1 is subtracted to go from 1-8 notation style to 0-7 array style */
		c.exitX = colCharToInt(preLastChar) - 1;
		c.exitY = coordNumberToInt(lastChar) - 1;

		int direction = Piece::getPawnMoveDirection(playerTurn);

		// d4, a6, c3... 
		if (isPawnAdvance(notationString)) return pawnAdvance(board, c, direction);

		bool charXinNotationStr = isXinNotationString(notationString);
		notationString = cutStringInHalf(notationString, charXinNotationStr);

		Piece::Type notationPiece = (Piece::Type)notationString[0];

		if (notationString.length() == 1)
		{
			// axb4, dxc2, hxg5...
			if (!isInvalidColCoordinate(notationString[0]))
			{
				c.startX = colCharToInt(notationString[0]) - 1;
				c.startY = c.exitY - direction;

				return c;
			}
			// Bc4, Rxa3, Ke2...
			else
			{
				for (int y = 0; y < 8; y++)
				{
					for (int x = 0; x < 8; x++)
					{

						c.startY = y;
						c.startX = x;

						if (board[y][x]->isSquareOccupied() &&
							board[y][x]->isPieceType(notationPiece) &&
							board[y][x]->areSquaresValid(c, board))
						{
							return c;
						}
					}
				}
			}
		}
		else
		{
			// Rbd4, Nfxg2, Raa6... 
			if (!isInvalidColCoordinate(notationString[1]))
			{
				int col = colCharToInt(notationString[1]) - 1;
				c.startX = col;

				for (int y = 0; y < 8; y++)
				{
					c.startY = y;

					if (board[y][col]->isSquareOccupied() &&
						board[y][col]->isPieceType(notationPiece) &&
						board[y][col]->areSquaresValid(c, board))
					{
						return c;
					}
				}
			}
			// R2d4, N4xg3, R1a6... 
			else
			{
				int row = coordNumberToInt(notationString[1]) - 1;
				c.startY = row;

				for (int x = 0; x < 8; x++)
				{
					c.startX = x;

					if (board[row][x]->isSquareOccupied() &&
						board[row][x]->isPieceType(notationPiece) &&
						board[row][x]->areSquaresValid(c, board))
					{
						return c;
					}
				}
			}
		}
		return c;
	}
};