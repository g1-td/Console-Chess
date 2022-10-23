#include "Piece.h"
#pragma once
class Queen :
    public Piece
{
    public:
    Queen(Piece::Color pieceColor) : Piece(pieceColor) {};
    virtual Queen::Type getPieceType() const override;
    virtual bool areSquaresValid(const Coords& c, const std::unique_ptr<Piece> board[8][8]) const override;
    virtual std::unique_ptr<Piece> clone() const override;
};