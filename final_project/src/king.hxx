#ifndef KING_HXX
#define KING_HXX

#include "piece.hxx"

class King : public Piece {
public:
    // king constructor
    King(Piece::Player player, Tile tile);
    // copy constructor.
    virtual Piece* clone() const;
    // all possible moves for the king
    virtual std::list<Move> get_possible_moves(const Board &board) const;
};
#endif