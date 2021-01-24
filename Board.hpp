#ifndef BOARD_H
#define BOARD_H

#include "Player.hpp"

/** @class Board
  * Create default chinese checker board */

class Board
{
    private:
    static const int row = 17;
    static const int col = 25;
    char board[row][col];
    int boardColour[row][col];

    public:
    void increment_part(int row_start, int row_end, int start_indicator, int end_indicator);
    void decrement_part(int row_start, int row_end, int start_indicator, int end_indicator);
    void reset_board();
    void set_availableMove(Coordinate coor);
    char get_board(Coordinate coor);
    int get_boardColour(Coordinate coor);
    void update_board(Player players[]);
    void print_board(Coordinate* checker_ptr);
};

#endif
