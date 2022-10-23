#include "Piece.h"
#pragma once
class King :
    public Piece
{
    public:
    King(Piece::Color pieceColor) : Piece(pieceColor) {};
    virtual King::Type getPieceType() const override;
    virtual bool areSquaresValid(const Coords& c, const std::unique_ptr<Piece> board[8][8]) const override;
    virtual std::unique_ptr<Piece> clone() const override;
};