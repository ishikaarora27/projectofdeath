#include "model.hxx"


Model::Model(Board b)
    : board_(b)
{}

void
Model::create_move(Position start, Position end) {

    Tile t1 = Tile(start);
    Tile t2 = Tile(end);
    Move move = (t1, t2);
    current_piece = board_[start];
    if(current_piece.valid_move(board_)){
        board_.move(&move);
    }


}

