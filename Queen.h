#pragma once
#include "Piece.h"
class Queen :
    public Piece
{
    public:
    Queen(Piece::Color pieceColor) : Piece(pieceColor) {};

    Piece::Type getPieceType() const override;
    virtual bool areSquaresValid(const Coords& c, const std::unique_ptr<Piece> board[8][8]) const override;
};