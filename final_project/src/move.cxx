#include "move.hxx"

Move::Move(Tile src, Tile dst)
        : src(src), dst(dst), type(Move::MoveType::Standard), taken(nullptr) {
}

Move::Move(Tile src, Tile dst, Move::MoveType type)
        : src(src), dst(dst), type(type), taken(nullptr) {
}

Move::Move(const Move &move)
        : src(move.src), dst(move.dst), type(move.type), taken(){
    if(move.get_captured_piece() == nullptr) {
        this->taken = nullptr;
    } else {
        this->taken = move.get_captured_piece()->clone();
    }
}

Move::~Move() {
    if(this->taken != nullptr) {
        delete this->taken;
    }
}

Tile Move::get_move_src() const {
    return this->src;
}

Tile Move::get_move_dst() const {
    return this->dst;
}

void Move::add_type(MoveType type) {
    this->type |= type;
}

bool Move::is_type(Move::MoveType type) const {
    return this->type & type;
}

Piece* Move::get_captured_piece() const {
    return this->taken;
}

void Move::set_taken_move(Piece *piece) {
    this->add_type(Move::Capture);
    this->taken = piece->clone();
}

bool Move::operator==(const Move &toCompare) {
    return this->get_move_src() == toCompare.get_move_src() && this->get_move_dst() == toCompare.get_move_dst()
           && this->type == toCompare.type;
}