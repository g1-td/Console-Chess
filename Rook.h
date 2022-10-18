#include "Piece.h"
#pragma once
class Rook :
    public Piece
{
    public:
    Rook(Piece::Color pieceColor) : Piece(pieceColor) {};
    virtual Rook::Type getPieceType() const override;
    virtual bool areSquaresValid(const Coords& c, const std::unique_ptr<Piece> board[8][8]) const override;
};