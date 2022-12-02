#include "linemove.hxx"

LineMove::LineMove(Piece::Player player, Tile tile)
        : Piece(player, tile) {
}

void LineMove::check_move(const Board &board, std::list<Move> &moves,
                                  bool &direction, int dx, int dy) const {
    int x = this->get_current_tile().get_x();
    int y = this->get_current_tile().get_y();

    if (!direction) { return; }
    Tile t = Tile(x + dx, y + dy);
    if (!t.valid_tile()) {
        direction = false;
        return;
    }
    if (board.get_piece(t) != nullptr) {
        direction = false;
        if (board.get_piece(t)->get_player() != this->player) {
            moves.push_back(Move(Tile(x, y), t));
        }
    } else {
        moves.push_back(Move(Tile(x, y), t));
    }
}