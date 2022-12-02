#pragma once

#include <ge211.hxx>
#include "piece.hxx"
#include "board.hxx"
#include "move.hxx"


class Model
{


public:

    using Position = ge211::Posn<int>;

    Model(Board board);

    void create_move(Position start, Position end);

    void set_game_over();

private:

    Piece::Player turn_;
    Piece::Type type;
    Piece current_piece;
    Move move_attempt;
    Board board_;

    void calculate_valid_moves(Piece p);


};
