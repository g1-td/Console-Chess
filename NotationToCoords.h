#pragma once
#include <memory>
#include <string>
#include <map>
#include "Coords.h"
#include "Piece.h"

class NotationToCoords
{
	public:
	static Coords toCoords(const std::unique_ptr<Piece> board[8][8], const Piece::Color playerTurnColor, std::string notationString);
	static std::string stringToUpper(std::string& str);


	private:
	static std::string cutStringInHalf(std::string& notationString, bool isXinString);
	static int colCharToInt(char c);
	static int charToInt(char c);
	static bool isInvalidColCoordinate(char c);
	static bool notationStringInvalidLength(const std::string& notationString);
	static bool isXinNotationString(const std::string& notationString);
	static bool areLastTwoCoordsNotValid(char last, char preLast);
	static bool isCastling(const std::string notationString);
	static bool isKingSideCastle(const std::string notationString);
	static bool isQueenSideCastle(const std::string notationString);
	static bool isPawnAdvance(const std::string notationString);
	static Coords invalidCoords();
	static Coords kingSideCastle(const Piece::Color playerTurnColor);
	static Coords queenSideCastle(const Piece::Color playerTurnColor);
	static Coords castle(const Piece::Color playerTurnColor, const std::string notationString);
	static Coords pawnAdvance(const std::unique_ptr<Piece> board[8][8], Coords c, int direction);

	friend class FEN;
};