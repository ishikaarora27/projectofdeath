#include "rook.hxx"
#include "../board.hxx"

Rook::Rook(Piece::Player player, Tile tile)
        : LineMove(player, tile) {
    this->type = Piece::Rook;
}

Piece* Rook::clone() const {
    return new Rook(*this);
}

std::list<Move> Rook::get_possible_moves(const Board &board) const {
    std::list<Move> moves;
    if (!is_taken()) {
        bool up = true;
        bool right = true;
        bool down = true;
        bool left = true;
        int i = 1;

        while (up || right || down || left) {
            check_move(board, moves, up, i, 0);
            check_move(board, moves, right, 0, i);
            check_move(board, moves, down, -i, 0);
            check_move(board, moves, left, 0, -i);
            i++;
        }
    }
    return moves;
}