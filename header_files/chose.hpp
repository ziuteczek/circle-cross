#include <array>
#include <conio.h>
#include <thread>
#include <string>
#include <iostream>
#include <atomic>
#include <windows.h>
class Chose
{
private:
    std::array<std::array<char, 3>, 3> board_data;

    // std::array<int, 2> blink_pos{{0, 0}};
    int blink_row = 0;
    int blink_column = 0;

    bool do_blink = false;

    std::atomic_bool stop_blink = false;

    std::string gen_separator_row()
    {
        std::string row;
        for (int i = 0; i < 5; i++)
        {
            if (i % 2)
            {

                row.push_back(197);
            }
            else
            {
                row.push_back(196);
            }
        }
        row.push_back('\n');
        return row;
    }
    std::string gen_board(bool blinked = false)
    {
        std::string board;
        std::array<std::array<char, 3>, 3> board_data = this->board_data;
        if (blinked)
        {
            board_data[blink_row][blink_row] = 177;
        }
        for (int board_row = 0; board_row < 3; board_row++)
        {
            for (int board_column = 0; board_column < 3; board_column++)
            {
                char char_to_draw = board_data[board_row][board_column];
                board.push_back(char_to_draw);
                if (board_column < 2)
                {
                    board.push_back(179);
                }
            }
            board.push_back('\n');
            if (board_row < 2)
            {
                board += gen_separator_row();
            }
        }
        return board;
    }
    void frame()
    {
        while (!stop_blink)
        {
            system("cls");
            std::cout << gen_board(do_blink) << std::endl;
            do_blink = !do_blink;
            Sleep(750);
        }
    }
    bool is_arrrow(char to_check)
    {
        std::array<char, 4> arrow_codes = {72, 80, 75, 77};
        for (char c : arrow_codes)
        {
            if (c == to_check)
            {
                return true;
            }
        }
        return false;
    }
    bool is_cell_empty(int row, int column)
    {
        return this->board_data[row][column] == ' ';
    }

public:
    Chose(std::array<std::array<char, 3>, 3> board_input) : board_data(board_input)
    {
        int arrow_presed;
        char blinked_char;
        std::thread blink_thread(&frame, this);
        do
        {
            arrow_presed = getch();
            std::cout << arrow_presed << std::endl;
        } while (!is_arrrow(arrow_presed) && !(arrow_presed == 13 && is_cell_empty(blink_row, blink_row)));
        stop_blink = true;
        blink_thread.join();
        stop_blink = false;
    }
};