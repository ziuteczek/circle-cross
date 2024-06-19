#include <iostream>
#include <array>

#include "./header_files/chose.hpp"
#include "./header_files/board.hpp"

int main()
{
    bool current_player = false;
    Board board;
    Chose pick(board.board_data);
    char winner;
    do
    {
        std::array<int, 2> picked_cell;
        picked_cell = pick.pick_cell();

        board.player_move(current_player, picked_cell[0], picked_cell[1]);
        pick.update_board_data(board.board_data);

        current_player = !current_player;

        winner = board.check_win();
    } while (winner == ' ' && !board.end_of_space());

    system("cls");

    if (winner == ' ')
    {
        std::cout << "No one has won" << std::endl;
    }
    else
    {
        std::cout << winner << " has won" << std::endl;
    }
    return 0;
}