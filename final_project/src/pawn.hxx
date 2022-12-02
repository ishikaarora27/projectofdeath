#ifndef PAWN_HXX
#define PAWN_HXX

#include "piece.hxx"
#include

class Pawn : public Piece {
public:
    // constructor for the pawn
    Pawn(Piece::Player player);
    // type getter
    Piece::Type get_type();
protected:
    bool pawn_move(Position start, Position end, Piece[][] board);
};
#endif