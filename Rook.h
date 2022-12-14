#pragma once
#include "Piece.h"
class Rook :
    public Piece
{
    public:
    Rook(Piece::Color pieceColor) : Piece(pieceColor) {};
    virtual Rook::Type getPieceType() const override;
    virtual bool areSquaresValid(const Coords& c, const std::unique_ptr<Piece> board[8][8]) const override;
    virtual std::unique_ptr<Piece> clone() const override;
};