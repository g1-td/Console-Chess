#include "Piece.h"
#pragma once
class Bishop :
    public Piece
{
    public:
    Bishop(Piece::Color pieceColor) : Piece(pieceColor) {};
    virtual Bishop::Type getPieceType() const override;
    virtual bool areSquaresValid(const Coords& c, const std::unique_ptr<Piece> board[8][8]) const override;
};