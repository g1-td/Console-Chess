#pragma once
#include "Piece.h"
class Pawn :
    public Piece
{
    public:
    Pawn(Piece::Color pieceColor) : Piece(pieceColor) {};

    Piece::Type getPieceType() const override;
    virtual bool areSquaresValid(const Coords& c, const Piece* board[8][8]) const override;
    

    private:
    bool isPawnNotMoved(const Coords& c) const;
    bool isMovedUpOnce(const Coords& c) const;
    bool isMovedUpTwice(const Coords& c) const;
    bool isSquarePawn(int y, int x, const Piece* board[8][8]) const;
    bool canEnPassant(const Coords& c, const Piece* board[8][8]) const;
    bool exitIsUpAndLeft(const Coords& c) const;
    bool exitIsUpAndRight(const Coords& c) const;
};