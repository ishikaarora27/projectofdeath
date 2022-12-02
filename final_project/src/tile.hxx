#pragma once

#include <iostream>
#include <ge211.hxx>
#include "piece.hxx"
#include "board.hxx"

// this class will act as the positions on the board
class Tile {
public:
    using Position = ge211::Posn<int>;
    // tile constructor
    Tile(Piece piece, Position pos);
    //constructor with pos only
    Tile(Position pos);

    // destructor
    virtual ~Tile() = default;
    //getter for the X coordinate
    int get_x() const;
    // getter for y coordinate
    int get_y() const;


    //checks if there is a piece at the tile
    bool empty();


    // checks if coordinates are in range
    bool valid_move() const;
    // pawn move
    bool valid_pawn_move(Tile start, Tile end, Board board) const;
    // rook move
    bool valid_rook_move() const;
    // knight move
    bool valid_knight_move() const;
    // bishop move
    bool valid_bishop_move() const;
    // queen move
    bool valid_queen_move() const;
    // king move
    bool valid_king_move() const;
    // none move
    bool valid_none_move() const;

    bool operator==(const Tile &toCompare);

private:
    Piece piece;
    Piece::Player player;
    Position position;
    int x;
    int y;
};
#endif