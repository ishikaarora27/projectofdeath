#ifndef QUEEN_HXX
#define QUEEN_HXX

#include "linemove.hxx"

class Queen : public LineMove {
public:
    // constructor for rook
    Queen(Piece::Player player, Tile tile);
    // copy constructor.
    virtual Piece* clone() const;
    // returns all possible moves for this figure
    virtual std::list<Move> get_possible_moves(const Board &board) const;
};
#endif