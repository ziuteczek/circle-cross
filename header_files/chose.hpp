#include <array>
#include <conio.h>
#include <thread>
#include <string>
#include <iostream>
#include <atomic>
#include <windows.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13

class Chose
{
private:
    std::array<std::array<char, 3>, 3> board_data;

    // std::array<int, 2> blink_pos{{0, 0}};
    std::atomic_int blink_row = 0;
    std::atomic_int blink_column = 0;

    bool do_blink = true;

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
            board_data[blink_row][blink_column] = 177;
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
        std::array<char, 4> arrow_codes = {KEY_UP, KEY_DOWN, KEY_RIGHT, KEY_LEFT};
        for (char c : arrow_codes)
        {
            if (c == to_check)
            {
                return true;
            }
        }
        return false;
    }
    bool is_cell_empty()
    {
        return this->board_data[blink_row][blink_column] == ' ';
    }
    void move_blink(char key_pressed)
    {
        switch (key_pressed)
        {
        case KEY_UP:
            if (blink_row > 0)
                blink_row--;
            break;
        case KEY_DOWN:
            if (blink_row < 2)
                blink_row++;
            break;
        case KEY_RIGHT:
            if (blink_column < 2)
                blink_column++;
            break;
        case KEY_LEFT:
            if (blink_column > 0)
                blink_column--;
            break;
        default:
            break;
        }
    }

public:
    Chose(std::array<std::array<char, 3>, 3> board_input) : board_data(board_input)
    {
        std::thread blink_thread(&frame, this);
        blink_thread.detach();
    }
    std::array<int, 2> pick_cell()
    {
        char key_pressed;
        do
        {
            key_pressed = getch();
            move_blink(key_pressed);
        } while (!(key_pressed == KEY_ENTER && is_cell_empty()));
        return std::array<int, 2>{{blink_row, blink_column}};
    }
    void stop_blinking()
    {
        this->stop_blink = true;
    }
    void update_board_data(std::array<std::array<char, 3>, 3> board)
    {
        this->board_data = board;
    }
};