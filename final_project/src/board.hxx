#ifndef BOARD_HXX
#define BOARD_HXX

#include "piece.hxx";
#include "pawn.hxx";
#include "rook.hxx";
#include "knight.hxx";
#include "bishop.hxx;
#include "queen.hxx";
#include "king.hxx";
#include "tile.hxx"

class Board {
public:
    //
    void set_board(Board board);
    //
    void reset_board();
    //adds all the original pieces

    //constructs a grid of tiles
    void make_grid();

    Piece get_piece(position);
    // board constructor
    Board();
    // deletes each piece of the board and previous moves
    virtual ~Board() = default;
    // board initializer
    void make_board();
    // delete board
    void delete_board();
    // returns all possible moves for a given player
    std::list<Move> get_possible_moves(Piece::Player player) const;
    // returns all previous moves in a list of move pointer
    std::list<Move*> get_previous_moves() const;
    // returns pointer of a piece at a given tile (returns null ptr if there is no piece
    Piece get_piece(Tile) const;

    // applies move to board
    // checks if move is valid with all possible moves
    // checks if player is still in check after the move
    // after successful move, current player is changed

    bool move_piece(Move *move);
    // promotes the piece(pawn)
    void promote_piece(Move *move, Piece::PieceType type);
    // undoes the last move
    void undo_move();

    // checks if piece is in check by:
    // checking if one move can capture king
    // returns true if the current player is in check
    bool in_check() const;

    // checks if piece is in checkmate by:
    // applying each possible move to a copy of the board
    // then checking if the piece is still in check after its move
    // returns true if the player is in checkmate
    bool in_checkmate() const;
    // checks for a draw
    // if there is no possible move for the current player
    // returns true it is a draw
    bool is_draw() const;
    // checks if move is a promotion
    // returns true if promotion
    bool is_promotion(Move *move) const;

    //returns the piece at [][]
    Piece operator [] (Position pos) const;

private:
     Piece board [][];
     Tile grid [][];
};
#endif