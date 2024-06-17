#include <vector>
#include <iostream>
#include <array>

#include "./header_files/chose.hpp"
#include "./header_files/board.hpp"

int main()
{
    Board board;
    board.player_move(true, 0, 0);
    Chose(board.board_data);
    return 0;
}