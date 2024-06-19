#include <array>
#include <string>

class Board
{
private:
    char check_win_row(int row_number)
    {

        char char_to_find = this->board_data[row_number][0];

        if (char_to_find == ' ')
        {
            return ' ';
        }
        for (int column = 1; column < this->board_data[row_number].size(); column++)
        {
            if (this->board_data[row_number][column] != char_to_find)
            {
                return ' ';
            }
        }

        return char_to_find;
    }
    char check_win_column(int column_number)
    {
        char winning_char = this->board_data[0][column_number];
        for (int row = 1; row < this->board_data.size(); row++)
        {
            if (this->board_data[row][column_number] != winning_char)
            {
                return ' ';
            }
        }
        return winning_char;
    }

    char chek_win_cross_1()
    {
        int cell_0_0 = this->board_data[0][0];
        for (int i = 1; i < 3; i++)
        {
            if (board_data[i][i] != cell_0_0)
            {
                return ' ';
            }
        }
        return cell_0_0;
    }
    char chek_win_cross_2()
    {
        int cell_0_last = this->board_data[0].back();
        for (int i = 1; i < 3; i++)
        {
            if (board_data[i][board_data.size() - 1 - i] != cell_0_last)
            {
                return ' ';
            }
        }
        return cell_0_last;
    }

public:
    std::array<std::array<char, 3>, 3> board_data{{{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}}};
    Board(std::array<std::array<char, 3>, 3> preset_board) : board_data(preset_board) {}
    Board() = default;

    /*
    @param
        0 - circle
        1 - cross
    @return
        0 - succes
        1 - cell out of range
        2 - cell already selected
     */
    int player_move(bool player, int row, int column)
    {
        char player_sign = player ? 'x' : 'o';
        if (row > 3 || row < 0 || column > 3 || row < 0)
        {
            return 1;
        }
        char *selected_cell = &this->board_data[row][column];
        if (*selected_cell != ' ')
        {
            return 2;
        }
        *selected_cell = player_sign;
        return 0;
    }

    /*
    @return
        ' ' - no win
        'x' - x won
        'o' - o won
    */
    char check_win()
    {
        // checking for row win
        for (int row = 0; row < 3; row++)
        {
            char winning_char = check_win_row(row);
            if (winning_char != ' ')
            {
                return winning_char;
            }
        }
        // checking for column win
        for (int column = 0; column < 3; column++)
        {
            char winning_char = check_win_column(column);
            if (winning_char != ' ')
            {
                return winning_char;
            }
        }
        // checking for cross win

        char winning_char_1 = chek_win_cross_1();
        if (winning_char_1 != ' ')
        {
            return winning_char_1;
        }

        return chek_win_cross_2();
    }
    bool end_of_space()
    {
        for (int row = 0; row < 3; row++)
        {
            for (int column = 0; column < 3; column++)
            {
                if (this->board_data[row][column] == ' ')
                {
                    return false;
                }
            }
        }
        return true;
    }
};