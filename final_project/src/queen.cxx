#include "queen.hxx"
#include "../board.hxx"

Queen::Queen(Piece::Player player, Tile tile)
        : LineMove(player, tile) {
    this->type = Piece::Queen;
}

Piece* Queen::clone() const {
    return new Queen(*this);
}

std::list<Move> Queen::get_possible_moves(const Board &board) const {
    std::list<Move> moves;
    if (!is_taken()) {
        bool up = true;
        bool right = true;
        bool down = true;
        bool left = true;
        bool up_left = true;
        bool up_right = true;
        bool down_left = true;
        bool down_right = true;
        int i = 1;

        while (top || right || bottom || left || up_left || up_right || down_left || down_right) {
            check_move(board, moves, up_left, i, -i);
            check_move(board, moves, up_right, i, i);
            check_move(board, moves, down_left, -i, -i);
            check_move(board, moves, down_right, -i, i);
            check_move(board, moves, up, i, 0);
            check_move(board, moves, right, 0, i);
            check_move(board, moves, down, -i, 0);
            check_move(board, moves, left, 0, -i);
            i++;
        }
    }
    return moves;
}