#ifndef KNIGHT_HXX
#define KNIGHT_HXX

#include "linemove.hxx"

class Knight : public LineMove {
public:
    // constructor for rook
    Knight(Piece::Player player, Tile tile);
    // copy constructor.
    virtual Piece* clone() const;
    // returns all possible moves for this figure
    virtual std::list<Move> get_possible_moves(const Board &board) const;
};
#endif