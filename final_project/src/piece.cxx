#include "board.hxx"
#include "piece.hxx"
#include <string>


Piece::Piece(Player player, Type type, Captured captured, Position pos)
   : player(player),
    type(type),
    captured(captured),
    position(pos),
    {
        filename = stringify(player) + " " + stringify(type) + ".png"
    }

Piece::Player
Piece::get_player(Player player){
    return player;
}

void Piece::set_player(Player player){
    this->player = player;
}

Piece::Type
Piece::get_type(Type type){
    return type;
}

void Piece::set_type(Type type){
    this->type = type;
}

void Piece::set_captured(Captured capture){
    this->captured = true;
}

Piece::Position
Piece::get_position(Position pos){
    return pos;
}

void Piece::set_position(Position pos){
    this->position = pos;
}

//if the piece is in bounds of the board
bool Piece::valid_move(Position start, Position end, Board board) {
    Piece destination = board[end];
    if ((end.x < 8 && end.y < 8 && end.x >= 0 && end.y >= 0
    && destination.get_player() == Neither) || player !=
    destination.get_player
    ()) {
        return true;
    } else {
        return false;
    }
}



