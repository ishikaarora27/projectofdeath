#ifndef ROOK_HXX
#define ROOK_HXX

#include "linemove.hxx"

class Rook : public LineMove {
public:
    // constructor for rook
    Rook(Piece::Player player, Tile tile);
    // copy constructor.
    virtual Piece* clone() const;
    // returns all possible moves for this figure
    virtual std::list<Move> get_possible_moves(const Board &board) const;
};
#endif