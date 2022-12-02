#pragma once

#include <ge211.hxx>

#include <bitset>
#include <cstddef>
#include <initializer_list>
// A position set for a piece accessed when selected on the board
class Move {
public:
    // All positions must be in bound of the chess board
    static constexpr int off_board = 8;
    // The position of the move on the board
    using position = ge211::Posn<int>;
private:
    // All the positions on the board
    static constexpr std:size_t all_positions = off_board * off_board;
    // All the tiles on the board
    using tiles_t = std::bitset<all_positions>;
    // The square itself
    tiles_t = bits_;
public:

    enum MoveType : int {
        Standard = 0,
        Capture = 1,
        Promotion = 2
    };
    // move constructor with a source position and a destination position
    Move(Tile src, Tile dst);
    // move constructor with an additional type parameter
    Move(Tile src, Tile dst, MoveType type);
    // Copy constructor
    Move(const Move &move);
    //deletes everything including the taken piece if not null ptr
    ~Move();
    // source move getter
    Tile get_move_src() const;
    // destination move getter
    Tile get_move_dst() const;
    // adds a type to a move
    void add_type(MoveType type);
    // checks if a move is of a given type
    bool is_type(MoveType type) const;
    // Returns a pointer to the captured piece if the move is a capture.
    // If not it returns a nullptr
    Piece* get_captured_piece() const;

    //Adds the type capture to the move and stores the given piece pointer.
    void set_taken_move(Piece *piece);

    bool operator==(const Move &toCompare);

private:
    Tile src;
    Tile dst;
    int type;
    Piece *taken;
};
#endif
