#pragma once
#include "Piece.h"
class Knight :
    public Piece
{
    public:
    Knight(Piece::Color pieceColor) : Piece(pieceColor) {};
    virtual Knight::Type getPieceType() const override;
    virtual bool areSquaresValid(const Coords& c, const std::unique_ptr<Piece> board[8][8]) const override;
    virtual std::unique_ptr<Piece> clone() const override;
};