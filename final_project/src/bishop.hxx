#ifndef BISHOP_HXX
#define BISHOP_HXX

#include "linemove.hxx"

class Bishop : public LineMove {
public:
    // constructor for rook
    Bishop(Piece::Player player, Tile tile);
    // copy constructor.
    virtual Piece* clone() const;
    // returns all possible moves for this figure
    virtual std::list<Move> get_possible_moves(const Board &board) const;
};
#endif