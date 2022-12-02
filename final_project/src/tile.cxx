#include "tile.hxx"

Tile::Tile(Piece piece, Position pos)
    : piece(piece),
    position(pos) {}


    //is there any piece at the tile
bool
Tile::empty(){
    if(piece& == nullptr){
        return true;
    }
    else return false;
}



    //checks if the move is in bounds
bool Tile::valid_move() const {
    if(this->position.x >= 0 && this->position.x < 8 &&
    this->position.y >= 0 && this->position.y < 8) {
        return true;
    }
    return false;
}

bool Tile::valid_pawn_move(Tile start, Tile end, Board board) const {
    if (board.get_piece()
}

bool Tile::operator==(const Tile &toCompare) {
    return this->get_x() == toCompare.get_x() && this->get_y() == toCompare.get_y();
}