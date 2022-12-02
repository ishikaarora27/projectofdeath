#ifndef VIEW_HXX
#define VIEW_HXX

#include <iostream>
#include <fstream>
#include "board.hxx"
#include "piece.hxx"
#include "playerinput.hxx"

class View {
public:
    // prints chessboard
    void print_board(Board const *board) const;
    // asks player what kind of promotion they want
    Piece::PieceType get_promotion_type() const;
    // asks player for input. The caller is responsible to delete the given
    PlayerInput *get_player_input() const;
    // prints a check
    void print_check() const;
    // prints a checkmate
    void print_checkmate() const;
    // prints a draw
    void print_draw() const;
    // prints an invalid move
    void print_invalid_move() const;
    // prints an invalid player input action
    void print_invalid_player_input() const;
    // prints greeting when game starts
    void print_hello() const;
    // prints an ending message
    void print_goodbye() const;

    // saves list of moves to a file
    void save_to_file(std::list<Move*> moves) const;
    // returns list of moves from file
    std::list<Move*> read_from_file() const;

private:
    void print_line() const;
    void print_bottom_line() const;
    void print_top_line() const;
    void print_board_labels() const;
    void print_piece(Piece const *piece) const;

};
#endif