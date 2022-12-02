#include "board.hxx"
#include "piece.hxx"
#include "pawn.hxx"
#include "rook.hxx"
#include "knight.hxx"
#include "bishop.hxx"
#include "queen.hxx"
#include "king.hxx"

#include <cmath>
#include <iostream>

using namespace ge211;

static int const board_size = 8;
Board::Board(){
    this->board = new Board[board_size][board_size]
    reset_board();
}
/* ask about this in OH
Board::~Board() {
    set_board(new Piece[][]);

} */

void Board::make_board() {
    for (int x = 0; x < board_size; x++) {
        for (int y = 0; y < board_size; y++) {
            board[x][y] = nullptr;
        }
    }
}

void Board::set_board(Board board) {
    this->board = board;
}

Piece::get_piece(Position pos) {
    return this->Piece::position[pos];
}

void Board::reset_board() {

    make_board();

    for (int i = 0; i < board_size; i++) {
        board[1][i] = new Pawn(Piece::Player::White);
    }
        for (int j = 0; j < board_size; j++) {
            board[i][j] = nullptr;
        }
    }
    for (int i = 0; i < board_size; i++) {
        board[1][i] = new Pawn(Piece::Player::White, Tile(1, i));
        board[6][i] = new Pawn(Piece::Player::Black, Tile(6, i));
    }
    board[0][0] = new Rook(Piece::Player::White, Tile(0, 0));
    board[0][7] = new Rook(Piece::Player::White, Tile(0, 7));
    board[7][0] = new Rook(Piece::Player::Black, Tile(7, 0));
    board[7][7] = new Rook(Piece::Player::Black, Tile(7, 7));
    board[0][1] = new Knight(Piece::Player::White, Tile(0, 1));
    board[0][6] = new Knight(Piece::Player::White, Tile(0, 6));
    board[7][1] = new Knight(Piece::Player::Black, Tile(7, 1));
    board[7][6] = new Knight(Piece::Player::Black, Tile(7, 6));
    board[0][2] = new Bishop(Piece::Player::White, Tile(0, 2));
    board[0][5] = new Bishop(Piece::Player::White, Tile(0, 5));
    board[7][2] = new Bishop(Piece::Player::Black, Tile(7, 2));
    board[7][5] = new Bishop(Piece::Player::Black, Tile(7, 5));
    board[0][3] = new Queen(Piece::Player::White, Tile(0, 3));
    board[7][3] = new Queen(Piece::Player::Black, Tile(7, 3));
    board[0][4] = new King(Piece::Player::White, Tile(0, 4));
    board[7][4] = new King(Piece::Player::Black, Tile(7, 4));
    return board;
}

//sets up the tiles
void make_grid(){
    for (int i = 0; i<8; i++){
        for (int j = 0; j<8; j++){
            Tile t = Tile(this->board[i][j], {i,j});
            this->grid [i][j] = t;
        }
    }
}

Piece *Board::get_piece(Tile) const {
    return this->board[tile.get_x()][tile.get_y()];
}

bool Board::move(Move *move) {
    Piece *currentPiece = get_piece(move->get_move_src());
    bool in_check = this->in_check();

    if (currentPiece != nullptr
        && currentPiece->valid_move(*this, *move)
        && currentPiece->get_player() == currentPlayer) {
        Board::move(move);
        //check if after the move the player is still in check
        if (in_check && this->in_check()) {
            other_player();
            this->undo_move();
            return false;
        }

        other_player();

        return true;
    }
    return false;
}

void Board::move(Move *move) {

    Tile src = move->get_move_src();
    Tile dst = move->get_move_dst();
    Piece *srcPiece = this->board[src.get_x()][dst.get_y()];
    this->board[src.get_x()][src.get_y()] = nullptr;

    Piece *dstPiece = this->board[dst.get_x()][dst.get_y()];
    if (dstPiece != nullptr) {
        dstPiece->take();
        move->set_taken_move(dstPiece);
        taken.push_back(dstPiece);
    }
    this->board[dst.get_x()][dst.get_y()] = srcPiece;
    srcPiece->set_current_tile(dst);
    this->previous_moves.push_back(new Move(*move));
}

void Board::promote_piece(Move *move, Piece::PieceType type) {
    Piece *srcPiece = get_piece(move->get_move_dst());
    move->add_type(Move::Promotion);
    int x = move->get_move_dst().get_x();
    int y = move->get_move_dst().get_y();
    switch(type) {
        case Piece::Queen :
            board[x][y] = new Queen(srcPiece->get_player(), Tile(x,y));
            break;
        case Piece::Rook :
            board[x][y] = new Rook(srcPiece->get_player(), Tile(x,y));
            break;
        case Chessman::Bishop :
            board[x][y] = new Bishop(srcPiece->get_player(), Tile(x,y));
            break;
        case Piece::Knight :
            board[x][y] = new Knight(srcPiece->get_player(), Tile(x,y));
            break;
        default:
            break;
    }
    Move *m = previous_moves.back();
    previous_moves.pop_back();
    delete m;
    previous_moves.push_back(new Move(*move));
    taken.push_back(srcPiece);
    delete move;
}

void Board::undo_move() {
    if (previous_moves.size() == 0) {
        return;
    }
    Move *m = previous_moves.back();
    previous_moves.pop_back();

    Position src = m->get_move_src();
    Position dst = m->get_move_dst();
    Piece *srcPiece = this->board[dst.get_x()][dst.get_y()];
    if (m->is_type(Move::Promotion)) {
        delete srcPiece;
        srcPiece = taken.back();
        taken.pop_back();
    }

    if (m->is_type(Move::Capture)) {
        this->board[dst.get_x()][dst.get_y()] = m->get_taken_piece()->clone();
        this->board[dst.get_x()][dst.get_y()]->take_back();
    } else {
        this->board[dst.get_x()][dst.get_y()] = nullptr;
    }
    this->board[src.get_x()][src.get_y()] = srcPiece;
    srcPiece->set_current_tile(src);

    this->other_player();
    delete m;
}

void Board::other_player() {
    if (this->currentPlayer == Piece::Player::White) {
        this->currentPlayer = Piece::Player::Black;
    } else {
        this->currentPlayer = Piece::Player::White;
    }
}

bool Board::in_check() const {
    std::list<Move> moves = get_possible_moves(!this->currentPlayer);
    for (Move m : moves) {
        Piece *target = board[m.get_move_dst().get_x()][m.get_move_dst().get_y()];
        if (dst != nullptr
            && dst->get_type() == Piece::PieceType::King
            && dst->get_player() == this->currentPlayer) {
            return true;
        }
    }
    return false;
}

bool Board::in_checkmate() const {
    if (!this->in_check()) {
        return false;
    }
    std::list<Move> moves = get_possible_moves(this->currentPlayer);
    Board *b = new Board(*this);
    for (Move m : moves) {
        Move *m2 = new Move(m);
        if (b->applyMove(m2)) {
            delete b;
            delete m2;
            return false;
        }
        delete m2;
        b->undo_move();
    }
    return true;
}

bool Board::is_draw() const {
    if (!this->in_check() && get_possible_moves(!this->currentPlayer).size() == 0) {
        return true;
    }
    return false;
}

bool Board::is_promotion(Move *move) const {
    Piece *currentPiece = get_piece(move->get_move_dst());
    if (currentPiece == nullptr) {
        return false;
    }
    if (currentPiece->get_type() != Piece::Pawn) {
        return false;
    }
    if (move->get_move_dst().get_x() == 0 || move->get_move_dst().get_x() == 7) {
        move->add_type(Move::Promotion);
        return true;
    }
    return false;
}

Piece
Board::operator[](Position pos) const
{
    valid_move
    return board[pos.x][pos.y];
}