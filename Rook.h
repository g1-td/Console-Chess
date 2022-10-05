#pragma once
#include "Piece.h"
class Rook :
    public Piece
{
    public:
    Rook(Piece::Color pieceColor) : Piece(pieceColor) {};

    Piece::Type getPieceType() const override;
    virtual bool areSquaresValid(const Coords& c, const Piece* board[8][8]) const override;
};

