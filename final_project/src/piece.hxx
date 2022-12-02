#pragma once

#include <iostream>
#include <ge211.hxx>
// piece needs to hold both its color, type, and position
class Piece {
public:
    enum Player {Black, White, Neither};
    enum Type {None, Pawn, Rook, Knight, Bishop, Queen, King};
    enum Captured : bool;
    using Position = ge211::Posn<int>;
    // each piece has three values: it's type of piece, its color, and its
    // point value
    Piece(Player player, Type type, Captured captured, Position pos);
    // destructor for the piece
    virtual ~Piece() = default;
    // get player
    Player get_player(Player player);
    //set player
    void set_player(Player player);
    // get type
    Type get_type(Type type);
    // set type
    void set_type(Type type);
    // set captured
    void set_captured(Captured captured);
    // get pos
    Position get_position(Position pos);
    // get x_coordinate
    /* how do you implement these? */
    // get y_coord
    // set pos
    void set_position(Position pos);
    // valid move for any piece

    // checks if it will be in bounds and the move is unoccupied
    bool valid_move(Position start, Position end, Board board);
    // valid moves for rooks and queens
    bool valid_line_move(Position start, Position end, Board board);
    // valid moves for bishops and queens
    bool valid_diagonal_move(Position start, Position end, Board board);

private:

    // the player (white or black)
    Player player;
    // the type of piece it is (doesn't change)
    Type type;
    //
    bool captured;
    //
    Position position;
    //
    int x;
    //
    int y;

    std::string filename_white const;
    std::string filename_black const;
};

