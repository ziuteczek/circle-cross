#include <vector>
#include <iostream>
#include <array>

#include "./header_files/board.hpp"

int main()
{
    std::array<std::array<char, 3>, 3> x{{{'o', 'x', 'o'}, {'x', 'o', ' '}, {' ', 'x', ' '}}};
    Board a(x);
    std::cout << a.gen_board();
    std::cout << a.check_win();
    return 0;
}