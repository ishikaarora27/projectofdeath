#include "view.hxx"


void View::print_board(Board const *board) const {
    print_board_labels();
    print_top_line();
    for (int i = 0; i < 8; i ++) {
        std::cout << i + 1 << " │ ";
        for (int j = 0; j < 8; j ++) {
            print_piece(board->get_piece(Tile(i, j)));
            std::cout << " │ ";
        }
        std::cout << " "  << i + 1 << std::endl;
        if (i < 7) {
            print_line();
        }
    }
    print_bottom_line();
    print_board_labels();

}

void View::print_line() const {
    std::cout <<
              "  ├───┼───┼───┼───┼───┼───┼───┼───┤"
              << std::endl;
}

void View::print_top_line() const {
    std::cout <<
              "  ┌───┬───┬───┬───┬───┬───┬───┬───┐"
              << std::endl;
}

void View::print_bottom_line() const {
    std::cout <<
              "  └───┴───┴───┴───┴───┴───┴───┴───┘"
              << std::endl;
}

void View::print_board_labels() const {
    std::cout << "    A   B   C   D   E   F   G   H" << std::endl;
}

void View::print_piece(const Piece *piece) const {
    if (piece == nullptr) {
        std::cout << " ";
        return;
    }
    if (piece->get_player() != Piece::White) {
        switch (piece->get_type()) {
            case Piece::Bishop :
                std::cout << "♗";
                break;
            case Piece::King :
                std::cout << "♔";
                break;
            case Piece::Knight :
                std::cout << "♘";
                break;
            case Piece::Pawn :
                std::cout << "♙";
                break;
            case Piece::Queen :
                std::cout << "♕";
                break;
            case Piece::Rook :
                std::cout << "♖";
                break;
        }
    } else {
        switch (Piece->get_type()) {
            case Piece::Bishop :
                std::cout << "♝";
                break;
            case Piece::King :
                std::cout << "♚";
                break;
            case Piece::Knight :
                std::cout << "♞";
                break;
            case Piece::Pawn :
                std::cout << "♟";
                break;
            case Piece::Queen :
                std::cout << "♛";
                break;
            case Piece::Rook :
                std::cout << "♜";
                break;
        }
    }
}

void View::print_invalid_move() const {
    std::cout << "Invalid move. Try again" << std::endl;
}

void View::print_invalid_player_input() const {
    std::cout << "Invalid input. Try again" << std::endl;
}

void View::print_goodbye() const {
    std::cout << "That's the game!" << std::endl;
}

Piece::PieceType View::get_promotion_type() const {
    while (true) {
        std::cout << "What piece do you want the pawn be promoted to?:" << std::endl;
        std::cout << "K(Knight), B(Bishop), R(Rook), Q(Queen)" << std::endl;
        std::string type;
        std::cin >> type;
        switch (toupper(type[0])) {
            case 'Q':
                return Piece::Queen;
            case 'K':
                return Piece::Knight;
            case 'R':
                return Piece::Rook;
            case 'B':
                return Piece::Bishop;
            default:
                continue;
        }
    }
}

PlayerInput* View::get_player_input() const {
    std::cout << "Select a piece: ";
    std::string src, dst;
    std::cin >> src;
    if(origin[0] == ':') {
        switch (toupper(origin[1])) {
            case 'S':
                return new PlayerInput(PlayerInput::Save);
            case 'L':
                return new PlayerInput(PlayerInput::Load);
            case 'Q':
                return new PlayerInput(PlayerInput::Quit);
            case 'U':
                return new PlayerInput(PlayerInput::Undo);
            default:
                return new PlayerInput(PlayerInput::Invalid);
        }
    }
    std::cout << std::endl << "Select where you want to move it: ";
    std::cin >> dst;
    if(src.length() == 2 && dst.length() == 2
       && toupper(origin[0]) - 'A' >= 0 &&  toupper(origin[0]) - 'A' < 8
       && origin[1] - '0' > 0 &&  origin[1] - '0' <= 8
       && toupper(target[0]) - 'A' >= 0 &&  toupper(target[0]) - 'A' < 8
       && target[1] - '0' > 0 &&  target[1] - '0' <= 8) {
        return new PlayerInput(new Move(Tile(src), Tile(dst)));
    }
    return new PlayerInput(PlayerInput::Invalid);
}

void View::print_hello() const {
    std::cout << " ___________________________________" << std::endl << std::endl;
    std::cout << " Welcome to Chess!" << std::endl;
    std::cout << " ___________________________________" << std::endl << std::endl << std::endl;
}

void View::print_check() const {
    std::cout << "You're in check!" << std::endl;
}

void View::print_checkmate() const {
    std::cout << "You're in Checkmate! Game over :(" << std::endl;
}

void View::print_draw() const {
    std::cout << "It's a tie!" << std::endl;
}

void View::save_to_file(std::list<Move *> moves) const {
    std::ofstream myStream("./SaveFile.txt");
    if(myStream.is_open()) {
        for(Move *m : moves){
            myStream << (char) ('A' + m->get_move_src().get_y()) << m->get_move_src().get_x() + 1 << " "
                     << (char) ('A' + m->get_move_dst().get_y()) << m->get_move_dst().get_x() + 1 << std::endl;
        }
    }
    myStream.close();
}

std::list<Move*> View::read_from_file() const {
    std::list<Move*> moves;
    std::ifstream myStream("./SaveFile.txt");
    if(!myStream.is_open()) {
        std::cout << "There is no file to open" << std::endl;
        myStream.close();
        return moves;
    }
    std::string line;
    while(getline(myStream,line)) {
        if (line.size() == 5) {
            moves.push_back(new Move(Tile(line.substr(0, 2)), Tile(line.substr(3, 5))));
        }
    }
    myStream.close();
    return moves;
}
