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
	std::string cutNotationStringInHalf(std::string& notationString, bool isXinString) { return notationString.substr(0, notationString.length() - (2 + isXinString)); }
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
	bool isInvalidColCharCoordinate(char c) { return colCharToInt(c) == 0 ? true : false; }
	bool notationStringInvalidLength(const std::string& notationString) { notationString.length() < 2 || notationString.length() > 5 ? true : false; }
	bool isXinNotationString(const std::string& notationString) { return notationString[notationString.length() - 3] == 'X'; }
	bool areLastTwoCoordsNotValid(char last, char preLast) { return !isdigit(last) || isInvalidColCharCoordinate(preLast); }
	bool isCastling(const std::string notationString) { return notationString[0] == 'O' ? true : false; }
	bool isKingSideCastle(const std::string notationString) { notationString == "O-O" ? true : false; }
	bool isQueenSideCastle(const std::string notationString) { notationString == "O-O-O" ? true : false; }
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
	Coords invalidCoords() { Coords c; return c; }

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

		if (notationString.length() == 2)
		{
			c.startX = c.exitX;

			for (int i = 1; i < 3; i++)
			{
				int y = c.exitY - (direction * i);
				int x = c.exitX;

				if (board[y][x]->isSquareNotEmpty() &&
					board[y][x]->isSquareType(Piece::Type::PAWN))
				{
					c.startY = y;
					return c;
				}
			}
			return invalidCoords();
		}

		bool charXinNotationStr = isXinNotationString(notationString);
		notationString = cutNotationStringInHalf(notationString, charXinNotationStr);

		if (notationString.length() == 1)
		{
			if (!isInvalidColCharCoordinate(notationString[0]))
			{
				c.startX = colCharToInt(notationString[0]) - 1;
				c.startY = c.exitY - direction;

				return c;
			}

			for (int y = 0; y < 8; y++)
			{
				for (int x = 0; x < 8; x++)
				{
					if (board[y][x]->isSquareNotEmpty() &&
						board[y][x]->isSquareType(Piece::Type::PAWN) &&
						board[y][x]->areSquaresValid(c, board))
					{
						c.startY = y;
						c.startX = x;
						return c;
					}
				}
			}
		}
		else
		{
			Piece::Type notationPiece = (Piece::Type)notationString[0];

			if (!isInvalidColCharCoordinate(notationString[1]))
			{
				int col = colCharToInt(notationString[1]) - 1;

				for (int y = 0; y < 8; y++)
				{
					if (board[y][col]->isSquareNotEmpty() &&
						board[y][col]->isSquareType(notationPiece) &&
						board[y][col]->areSquaresValid(c, board))
					{
						c.startX = col;
						c.startY = y;

						return c;
					}
				}
			}
			else
			{
				int row = notationString[1] - 1;

				for (int x = 0; x < 8; x++)
				{
					if (board[row][x]->isSquareNotEmpty() &&
						board[row][x]->isSquareType(notationPiece) &&
						board[row][x]->areSquaresValid(c, board))
					{
						c.startX = x;
						c.startY = row;

						return c;
					}
				}
			}
		}
		return c;
	}
};