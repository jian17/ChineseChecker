#include "Function.hpp"

#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <fstream>
#include <ctime>
using namespace std;

/** Go to specific coordinate in console
	@param int coordinate of x
	@param int coordinate of y */
void gotoxy ( int x, int y )
{
	COORD coord = {x, y};
	SetConsoleCursorPosition ( GetStdHandle ( STD_OUTPUT_HANDLE ) , coord );
}

/** Show or hide cursor in console
    @param visibility of cursor */
void set_cursor(bool visible)
{
	CONSOLE_CURSOR_INFO info;
	HANDLE hOutput = GetStdHandle (STD_OUTPUT_HANDLE);

	info.bVisible = visible;
	info.dwSize = 20;
	SetConsoleCursorInfo(hOutput,&info);
}

/** Set colour in console
    @param foreground colour
    @param background colour */
void set_color(int foreground_color, int background_color)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, foreground_color + (background_color  << 4) );
}

/** Set console size
    @param width of console
    @param height of console */
void set_ConsoleSize(int width, int height)
{
    static HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    static COORD largestWindow = GetLargestConsoleWindowSize(hOut);

    if (width < 1)
        width = 1;
    if (height < 1)
        height = 1;

    if (width > largestWindow.X)
        width = largestWindow.X;
    if (height > largestWindow.Y)
        height = largestWindow.Y;

    SMALL_RECT window_rect = {0, 0, 0, 0};

    if ( !SetConsoleWindowInfo(hOut, TRUE, &window_rect) )
    {
        cerr << "In \'setConsoleSize()\':"
             << "- Error at <SetConsoleWindowInfo>" << endl;
        cerr << "Aborting Function!" << endl;
        return;
    }

    window_rect.Right   = width - 1;
    window_rect.Bottom  = height - 1;

    if ( !SetConsoleWindowInfo(hOut, TRUE, &window_rect) )
    {
        cerr << "In \'setConsoleSize()\':"
             << "- Error calling <SetConsoleWindowInfo>" << endl;
        cerr << "Aborting Function!" << endl;

        return;
    }
}

/** Function start with the word print
    used to output the basic user interface */
void print_menu()
{
    system("cls");
    cout << "1. New Game\n";
    cout << "2. Load Game\n";
    cout << "3. Exit\n\n";
    cout << "Please enter your choice: ";
}

void print_select()
{
    system("cls");
    cout << "Select 4 players (2 pair of players):" << endl;
    cout << "1. RED  CYAN\t2. GREEN  BLUE\t3. PURPLE  YELLOW\n";
    cout << "First Pair and Second Pair: ";
}

void print_selectUser()
{
    cout << "\n\nSelect user player:\n";
    cout << "1. RED   2. GREEN   3. PURPLE   4. CYAN   5. BLUE   6. YELLOW\n";
    cout << "User Player : ";
}

void print_option()
{
    gotoxy(61,9);
    cout << "====";
    gotoxy(60,10);
    cout << "|Save|";
    gotoxy(61,11);
    cout << "====";
    gotoxy(61,17);
    cout << "====";
    gotoxy(60,18);
    cout << "|Exit|";
    gotoxy(61,19);
    cout << "====";
}

void print_info(Board &checkerBoard, Coordinate *checker_ptr)
{
    if((*checker_ptr).getRow() == 0 && (*checker_ptr).getCol() == 0)
    {
        cout << "\n\nAvailable Move: -\n";
        cout << "Coordinate: -,-\n";
    }
    else
    {
        cout << "\n\nAvailable Move: " << SearchTree::getCount(checkerBoard) << endl;
        cout << "Coordinate: " << (*checker_ptr).getRow() << "," << (*checker_ptr).getCol() << endl;
    }
}

void print_winner(int player)
{
    gotoxy(22,3);

    switch(player)
    {
        case 0:
        set_color(12, 0);
        cout << "RED PLAYER WIN" << endl;
        set_color(15, 0);
        break;

        case 1:
        set_color(10, 0);
        cout << "GREEN PLAYER WIN" << endl;
        set_color(15, 0);
        break;

        case 2:
        set_color(5, 0);
        cout << "PURPLE PLAYER WIN" << endl;
        set_color(15, 0);
        break;

        case 3:
        set_color(11, 0);
        cout << "CYAN PLAYER WIN" << endl;
        set_color(15, 0);
        break;

        case 4:
        set_color(9, 0);
        cout << "BLUE PLAYER WIN" << endl;
        set_color(15, 0);
        break;

        case 5:
        set_color(14, 0);
        cout << "YELLOW PLAYER WIN" << endl;
        set_color(15, 0);
        break;
    }
}

/** Check whether there is a winner
    @return true or false */
bool check_winner(int player_turn, Board &checkerBoard, Coordinate coor[])
{
    bool winner = true;

    switch(player_turn)
    {
        case 0:
        for(int i=30; i<40; i++)
        {
            if(checkerBoard.get_boardColour(coor[i]) != 12)
            {
                winner = false;
                break;
            }
        }
        break;

        case 1:
        for(int i=40; i<50; i++)
        {
            if(checkerBoard.get_boardColour(coor[i]) != 10)
            {
                winner = false;
                break;
            }
        }
        break;

        case 2:
        for(int i=50; i<60; i++)
        {
            if(checkerBoard.get_boardColour(coor[i]) != 5)
            {
                winner = false;
                break;
            }
        }
        break;

        case 3:
        for(int i=0; i<10; i++)
        {
            if(checkerBoard.get_boardColour(coor[i]) != 11)
            {
                winner = false;
                break;
            }
        }
        break;

        case 4:
        for(int i=10; i<20; i++)
        {
            if(checkerBoard.get_boardColour(coor[i]) != 9)
            {
                winner = false;
                break;
            }
        }
        break;

        case 5:
        for(int i=20; i<30; i++)
        {
            if(checkerBoard.get_boardColour(coor[i]) != 14)
            {
                winner = false;
                break;
            }
        }
    }

    return winner;
}

/** Setup checker for a new game
    @param player select case
    @param array of players
    @param array of coordinate (save checker's coordinate) */
void set_checker(int playerSelect_case, Player players[], Coordinate coor[])
{
    //load file that contains of checker's position
    ifstream myfile;
    myfile.open("new.txt");

    int coordinate_set[120];
    int n;
    int i = 0;

    while(myfile >> n)
    {
        coordinate_set[i] = n;
        i++;
    }

    myfile.close();

    int j = 0;

    for(int i=0; i<120; i+=2)
    {
        coor[j].setRow(coordinate_set[i]);
        coor[j].setCol(coordinate_set[i+1]);
        j++;
    }

    Checker checkers[60];

    for(int i=0; i<60; i++)
    {
        checkers[i].setChecker(coor[i]);
    }

    //Initialize the player based on the select case
    switch(playerSelect_case)
    {
        case 0:
        for(int i=0; i<60; i++)
        {
            if(i>9 && i<20)
            {
                players[1].setPlayer(i%10, checkers[i]);
            }
            else if(i>19 && i<30)
            {
                players[2].setPlayer(i%10, checkers[i]);
            }
            else if(i>39 && i<50)
            {
                players[4].setPlayer(i%10, checkers[i]);
            }
            else if(i>49 && i<60)
            {
                players[5].setPlayer(i%10, checkers[i]);
            }
        }

        players[1].setColour(10);
        players[2].setColour(5);
        players[4].setColour(9);
        players[5].setColour(14);

        break;

        case 1:
        for(int i=0; i<60; i++)
        {
            if(i<10)
            {
                players[0].setPlayer(i%10, checkers[i]);
            }
            else if(i>19 && i<30)
            {
                players[2].setPlayer(i%10, checkers[i]);
            }
            else if(i>29 && i<40)
            {
                players[3].setPlayer(i%10, checkers[i]);
            }
            else if(i>49 && i<60)
            {
                players[5].setPlayer(i%10, checkers[i]);
            }
        }

        players[0].setColour(12);
        players[2].setColour(5);
        players[3].setColour(11);
        players[5].setColour(14);

        break;

        case 2:
        for(int i=0; i<60; i++)
        {
            if(i<10)
            {
                players[0].setPlayer(i%10, checkers[i]);
            }
            else if(i>9 && i<20)
            {
                players[1].setPlayer(i%10, checkers[i]);
            }
            else if(i>29 && i<40)
            {
                players[3].setPlayer(i%10, checkers[i]);
            }
            else if(i>39 && i<50)
            {
                players[4].setPlayer(i%10, checkers[i]);
            }
        }

        players[0].setColour(12);
        players[1].setColour(10);
        players[3].setColour(11);
        players[4].setColour(9);
    }
}

/** Load checker from save file
    All the parameters are passed by reference or array
    for initialization */
void load_checker(Player players[], Coordinate win_position[], int& playerSelect_case, int& user, int& comp1, int& comp2, int& comp3)
{
    //load file that contains of checker's position
    ifstream myfile;
    myfile.open("save.txt");

    myfile >> playerSelect_case >> user >> comp1 >> comp2 >> comp3;

    int coordinate_set[80];
    int n;
    int i = 0;

    while(myfile >> n)
    {
        coordinate_set[i] = n;
        i++;
    }

    Coordinate coor[40];
    int j = 0;

    for(int i=0; i<120; i+=2)
    {
        coor[j].setRow(coordinate_set[i]);
        coor[j].setCol(coordinate_set[i+1]);
        j++;
    }

    Checker checkers[40];

    for(int i=0; i<40; i++)
    {
        checkers[i].setChecker(coor[i]);
    }

    //load players last position
    for(int i=0; i<40; i++)
    {
        if(i<10)
        {
            players[user].setPlayer(i%10, checkers[i]);
        }
        else if(i>9 && i<20)
        {
            players[comp1].setPlayer(i%10, checkers[i]);
        }
        else if(i>19 && i<30)
        {
            players[comp2].setPlayer(i%10, checkers[i]);
        }
        else if(i>29 && i<40)
        {
            players[comp3].setPlayer(i%10, checkers[i]);
        }
    }

    switch(playerSelect_case)
    {
        case 0:
        players[1].setColour(10);
        players[2].setColour(5);
        players[4].setColour(9);
        players[5].setColour(14);
        break;

        case 1:
        players[0].setColour(12);
        players[2].setColour(5);
        players[3].setColour(11);
        players[5].setColour(14);
        break;

        case 2:
        players[0].setColour(12);
        players[1].setColour(10);
        players[3].setColour(11);
        players[4].setColour(9);
    }

    //load file for the goal position
    myfile.open("new.txt");

    int goal_coordinate[120];
    i = 0;

    while(myfile >> n)
    {
        goal_coordinate[i] = n;
        i++;
    }

    myfile.close();

    j = 0;

    for(int i=0; i<120; i+=2)
    {
        win_position[j].setRow(goal_coordinate[i]);
        win_position[j].setCol(goal_coordinate[i+1]);
        j++;
    }
}

/** Save all the players information and
    each checker's coordinate */
void save(Player players[], int playerSelect_case, int user, int comp1, int comp2, int comp3)
{
    ofstream myfile;
    myfile.open("save.txt");

    myfile << playerSelect_case << " " << user << " " << comp1 << " " << comp2 << " " << comp3 << " ";

    for(int j=0; j<10; j++)
    {
        myfile << players[user].getPlayerRow(j) << " " << players[user].getPlayerCol(j) << " ";
    }

    for(int j=0; j<10; j++)
    {
        myfile << players[comp1].getPlayerRow(j) << " " << players[comp1].getPlayerCol(j) << " ";
    }

    for(int j=0; j<10; j++)
    {
        myfile << players[comp2].getPlayerRow(j) << " " << players[comp2].getPlayerCol(j) << " ";
    }

    for(int j=0; j<10; j++)
    {
        myfile << players[comp3].getPlayerRow(j) << " " << players[comp3].getPlayerCol(j) << " ";
    }

    myfile.close();
}

/** Update the coordinate of checker after jumping
    @param direction (total 6 directions to move)
    @param coor (initial coordinate)
    @return updated coordinate */
Coordinate jump(int direction, Coordinate coor)
{
    if(direction == 0)
    {
        coor.setRow(coor.getRow() - 1);
        coor.setCol(coor.getCol() - 1);
    }
    else if(direction == 1)
    {
        coor.setRow(coor.getRow() - 1);
        coor.setCol(coor.getCol() + 1);
    }
    else if(direction == 2)
    {
        coor.setCol(coor.getCol() + 2);
    }
    else if(direction == 3)
    {
        coor.setRow(coor.getRow() + 1);
        coor.setCol(coor.getCol() + 1);
    }
    else if(direction == 4)
    {
        coor.setRow(coor.getRow() + 1);
        coor.setCol(coor.getCol() - 1);
    }
    else if(direction == 5)
    {
        coor.setCol(coor.getCol() - 2);
    }

    return coor;
}

/** @return coordinate of checker after jumping once */
Coordinate get_firstJump(int direction, Coordinate prev_coor, Board &checkerBoard)
{
    Coordinate i_coor;

    i_coor = jump(direction, prev_coor);

    if(checkerBoard.get_boardColour(i_coor) == 15 && checkerBoard.get_board(i_coor) == 'O' && i_coor.getCol() >= 0 && i_coor.getCol() <= 24
       && i_coor.getRow() >= 0 && i_coor.getRow() <= 16)
    {
        checkerBoard.set_availableMove(i_coor);
    }
    else
    {
        i_coor.setRow(0);
        i_coor.setCol(0);
    }

    return i_coor;
}

/** @return coordinate of checker after jumping twice */
Coordinate get_secondJump(int direction, Coordinate prev_coor, Board &checkerBoard)
{
    Coordinate i_coor, j_coor;

    i_coor = jump(direction, prev_coor);
    j_coor = jump(direction, i_coor);
    if(checkerBoard.get_boardColour(i_coor) != 15 &&
       checkerBoard.get_board(i_coor) == 'O' &&
       checkerBoard.get_boardColour(j_coor) == 15 &&
       checkerBoard.get_board(j_coor) == 'O' && j_coor.getCol() >= 0 && j_coor.getCol() <= 24
       && j_coor.getRow() >= 0 && j_coor.getRow() <= 16)
    {
        checkerBoard.set_availableMove(j_coor);
    }
    else
    {
        j_coor.setRow(0);
        j_coor.setCol(0);
    }

    return j_coor;
}

/** Mouse event for the user to interact with the game board */
void mouseEvent(bool &move, int user, Player players[], Board &checkerBoard, Coordinate* checker_ptr, int& checker_number, int store[])
{
    INPUT_RECORD rec;
    DWORD evk;
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(hIn, ENABLE_MOUSE_INPUT);
    int x_pos, y_pos, row_ptr, col_ptr;
    bool select = false;
    bool deselect = true;

    set_cursor(false);

    while(select == false)
    {
        if(ReadConsoleInput(hIn, &rec, 1, &evk) && rec.EventType == MOUSE_EVENT)
        {
            if(rec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED )
            {
                x_pos = rec.Event.MouseEvent.dwMousePosition.X;
                y_pos = rec.Event.MouseEvent.dwMousePosition.Y;
                col_ptr = x_pos - 16;
                row_ptr = y_pos - 5;

                checker_ptr->setRow(row_ptr);
                checker_ptr->setCol(col_ptr);

                //save button clicked
                if((x_pos == 61 || x_pos == 62 || x_pos == 63 || x_pos == 64) && y_pos == 10)
                {
                    save(players, store[0], store[1], store[2], store[3], store[4]);
                    exit(0);
                }

                //exit button clicked
                if((x_pos == 61 || x_pos == 62 || x_pos == 63 || x_pos == 64) && y_pos == 18)
                {
                    exit(0);
                }

                //console clicked
                for(int i=0; i<10; i++)
                {
                    if(players[user].getPlayerRow(i) == row_ptr && players[user].getPlayerCol(i) == col_ptr)
                    {
                        checker_number = i;
                        checkerBoard.reset_board();
                        SearchTree t;
                        t.insert(*checker_ptr, checkerBoard);
                        select = true;
                        deselect = false;
                        break;
                    }
                }

                if(checker_number >= 0 && checkerBoard.get_boardColour(*checker_ptr) == 15 && checkerBoard.get_board(*checker_ptr) == 'X')
                {
                    players[user].movePlayer(checker_number, *checker_ptr);
                    checker_number = -1;
                    checkerBoard.reset_board();
                    move = true;
                    select = true;
                }

                //set pointer to nothing when out of board
                if(deselect == true)
                {
                    checker_number = -1;
                    checker_ptr->setRow(0);
                    checker_ptr->setCol(0);
                    checkerBoard.reset_board();
                    select = true;
                }
            }
        }
    }
}

/** Find the best move of the computer player */
void computer_move(int comp, Board &checkerBoard, Player players[], Coordinate win_position[])
{
    TreeNode bestMove;
    List <TreeNode> list;
    int index;
    srand(time(0));

    int n[10] = {0,1,2,3,4,5,6,7,8,9};
    int start, end;

    //check whether the computer's checker is in the goal position
    //stop the checkers from moving elsewhere
    switch(comp)
    {
        case 0:
        start = 30;  end = 39;
        break;

        case 1:
        start = 40;  end = 49;
        break;

        case 2:
        start = 50;  end = 59;
        break;

        case 3:
        start = 0;  end = 9;
        break;

        case 4:
        start = 10;  end = 19;
        break;

        case 5:
        start = 20;  end = 29;
    }

    for(int i=start; i<=end; i++)
    {
        for(int j=0; j<10; j++)
        {
            if(n[j] != -1)
            {
                if(win_position[i].getRow() == players[comp].getPlayerRow(j) &&
                   win_position[i].getCol() == players[comp].getPlayerCol(j))
                {
                    n[j] = -1;
                    win_position[i].setRow(0);
                    win_position[i].setCol(0);
                    break;
                }
            }
        }

        if(win_position[i].getRow() != 0 && win_position[i].getCol() != 0)
        {
            break;
        }
    }


    int strategy;
    strategy = 1 + rand()%11;

    //choose the best move of each checker
    //random move one checker (70% chance)
    for(int i=0; i<10; i++)
    {
        if(n[i] != -1)
        {
            Coordinate *coor = new Coordinate();
            coor->setRow(players[comp].getPlayerRow(i));
            coor->setCol(players[comp].getPlayerCol(i));

            SearchTree *t = new SearchTree(comp, i);
            t->insert(*coor, checkerBoard);
            t->sortMove();

            for(int i=1; i<=t->getList().getSize(); i++)
            {
                list.push_back(t->getList().getItem(i));
            }
        }
        else
        {
            continue;
        }
    }

    //move the only one checker that nearest to the goal position (30% chance)
    if(strategy > 7)
    {
        list.bubbleSort();
        list.chooseBest();
    }

    if(list.getSize() == 1)
    {
        bestMove = list.getItem(1);
    }
    else
    {
        index = 1 + (rand()%(list.getSize()));
        bestMove = list.getItem(index);
    }

    players[comp].movePlayer(bestMove.get_checkerNumber(), bestMove.get_coor());
}





