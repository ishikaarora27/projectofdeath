#pragma once

#include <ge211.hxx>

#include <bitset>
#include <cstddef>
#include <initializer_list>

class Move_set{
public:
    // All positions must be in bound of the chess board
    static constexpr int off_board = 8;
    // The position of the move on the board
    using position = ge211::Posn<int>;
private:
    // All the positions on the board
    static constexpr std::size_t all_positions = off_board * off_board;
    // All the tiles on the board
    using tiles = std::bitset<all_positions>;
    // The square itself
    tiles tiles_;
public:
    // constructs default move set
    Move_set() noexcept = default;
    // constructs the move set containing all the moves
    static Move_set game();
    // constructs move set with available moves
    Move_set(std::initializer_list<position> elms);
    // checks if set is empty
    bool empty() const;
    // empties the move set
    void clear();
    // returns if the move is within the set
    bool operator[](position p) const;
    // class that will add or remove a move with a boolean
    using reference = tiles::reference;
    // returns and object that can change whether a move is in a move_set
    reference operator[](position p);
    // remove from set1 any positions not present in set2:
    // set1 &= set 2;
    Move_set& operator&=(Move_set that);
    // sets the move set 1 to be the union both sets
    Move_set& operator|=(Move_set that);

};