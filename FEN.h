#pragma once
#include <map>
#include <string>
#include "NotationToCoords.h"
#include "Board.h"
class FEN
{
	public:
	static std::string toString(const std::unique_ptr<Board>& brd);
	static std::unique_ptr<Board> toPosition(std::string fen);
	static bool isFenValid(std::string fen);

	private:
	static std::string boardToStr(const std::unique_ptr<Piece> board[8][8]);
	static std::string hasMovedKingRook(const std::unique_ptr<Piece> board[8][8]);
	static std::string enPassantCapture(const std::unique_ptr<Piece> board[8][8], const Piece::Color& color);
	static char colorToChar(const Piece::Color& color);

	static void setEnPassantFlag(const std::unique_ptr<Piece> board[8][8], const std::string& str);
	static void setCastleFlags(const std::unique_ptr<Piece> board[8][8], const std::string& str);
	static void strToBoard(const std::string& str, std::unique_ptr<Piece> board[8][8]);
	static std::string cutTillSpace(std::string& str);
	static Piece::Color charToColor(const char& c);
};

