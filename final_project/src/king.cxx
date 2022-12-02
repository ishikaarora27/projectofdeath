#include "king.hxx"
#include "../board.hxx"

King::King(Piece::Player player, Tile tile)
        : Piece(player, tile) {
    this->type = Piece::King;
}

Piece* King::clone() const {
    return new King(*this);
}

std::list<Move> King::get_possible_moves(const Board &board) const {
    std::list <Move> moves;
    if (!is_taken()) {
        int x = this->tile.get_x();
        int y = this->tile.get_y();
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                int dst_x = x + i;
                int dst_y = y + j;
                if (dst_x >= 0 && dst_x < 8 && dst_y >= 0 && dst_y < 8) {
                    if (board.get_piece(Tile(dst_x, dst_y)) != nullptr
                        && board.get_piece(Tile(dst_x, dst_y))->get_player() != this->get_player()) {
                        moves.push_back(Move(Tile(x, y), Tile(dst_x, dst_y)));
                    } else if (board.get_piece(Tile(dst_x, dst_y)) == nullptr) {
                        moves.push_back(Move(Tile(x, y), Tile(dst_x, dst_y)));
                    }
                }
            }
        }
    }
}