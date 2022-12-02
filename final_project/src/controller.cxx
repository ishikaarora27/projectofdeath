#include "controller.hxx"


void Controller::run() {

    Board *board = new Board();

    View view = View();

    view.print_hello();

    while (true) {
        if (board->in_check()) {
            view.print_check();
            if (board->in_checkmate()) {
                view.print_checkmate();
                view.print_board(board);
                break;
            }
        }
        if (board->is_draw()) {
            view.print_draw();
            view.print_board(board);
            break;
        }
        view.print_board(board);

        bool noInvalidInput = true;
        while (noInvalidInput) {
            PlayerInput *playerInput = view.get_player_input();
            Move *move;
            switch (playerInput->get_type()) {
                case PlayerInput::Save :
                    view.save_to_file(board->get_previous_moves());
                    noInvalidInput = false;
                    break;
                case PlayerInput::Load :
                    delete board;
                    board = new Board(view.read_from_file());
                    noInvalidInput = false;
                    break;
                case PlayerInput::Undo :
                    board->undo_move();
                    noInvalidInput = false;
                    break;
                case PlayerInput::MoveInput :
                    move = new Move(*PlayerInput->get_move());
                    if(!board->move_piece(move)) {
                        view.print_invalid_move();
                        delete move;
                        delete PlayerInput;
                        continue;
                    }
                    if (board->is_promotion(move)) {
                        board->promote_piece(move, view.get_promotion_type());
                    }
                    noInvalidInput = false;
                    //delete move;
                    break;
                case PlayerInput::Quit :
                    view.print_goodbye();
                    delete board;
                    delete PlayerInput;
                    return;
                default:
                    view.print_invalid_player_input();
            }
            delete PlayerInput;
        }
    }
}
}
