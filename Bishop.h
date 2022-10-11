#include "Piece.h"
#pragma once
class Bishop :
    public Piece
{
    public:
    Bishop(Piece::Color pieceColor) : Piece(pieceColor) {};

    Piece::Type getPieceType() const;
    virtual bool areSquaresValid(const Coords& c, const std::unique_ptr<Piece> board[8][8]) const override;
};