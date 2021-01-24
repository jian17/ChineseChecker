#include "Board.hpp"
#include "Function.hpp"

#include <iostream>
#include <windows.h>
using namespace std;

void Board::increment_part(int row_start, int row_end, int start_indicator, int end_indicator)
{
    for(int i=row_start; i<row_end; i++)
	{
        for(int j=start_indicator; j<=end_indicator; j+=2)
		{
			board[i][j] = 'O';
		}

        start_indicator--;
        end_indicator++;
	}
}

void Board::decrement_part(int row_start, int row_end, int start_indicator, int end_indicator)
{
    for(int i=row_start; i<row_end; i++)
	{
		for(int j=start_indicator; j<=end_indicator; j+=2)
		{
			board[i][j] = 'O';
		}

        start_indicator++;
        end_indicator--;
	}
}

void Board::reset_board()
{
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            board[i][j] = ' ';
        }
    }

    increment_part(0, 4, 12, 13);
    decrement_part(4, 9, 0, 24);
    increment_part(9, 13, 3, 21);
    decrement_part(13, 17, 9, 15);
}

void Board::set_availableMove(Coordinate coor)
{
    board[coor.getRow()][coor.getCol()] = 'X';
}

char Board::get_board(Coordinate coor)
{
    return board[coor.getRow()][coor.getCol()];
}

int Board::get_boardColour(Coordinate coor)
{
    return boardColour[coor.getRow()][coor.getCol()];
}

void Board::update_board(Player players[])
{
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            boardColour[i][j] = 15;
        }
    }

    for(int m=0; m<6; m++)
    {
        for(int n=0; n<10; n++)
        {
            if(players[m].isExist() == true)
            {
                boardColour[players[m].getPlayerRow(n)][players[m].getPlayerCol(n)] = players[m].getColour();
            }
        }
        cout << endl;
    }
}

void Board::print_board(Coordinate* checker_ptr)
{
    system("cls");

    cout << "\n\n\n\n\n";

    for(int i=0; i<row; i++)
    {
        cout << "\t\t";

        for(int j=0; j<col; j++)
        {
            if(checker_ptr->getRow() == i && checker_ptr->getCol() == j)
            {
                set_color(boardColour[i][j], 8);
            }
            else
            {
                set_color(boardColour[i][j], 0);
            }

            cout << board[i][j];
            set_color(boardColour[i][j], 0);
        }
        cout << endl;
    }
}


