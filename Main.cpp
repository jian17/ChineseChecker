#include <iostream>
#include <windows.h>
#include <conio.h>

#include "Board.hpp"
#include "Coordinate.hpp"
#include "Checker.hpp"
#include "Function.hpp"
#include "Player.hpp"
#include "SearchTree.hpp"
#include "TreeNode.hpp"
#include "List.hpp"
using namespace std;

int main()
{
    Board CheckerBoard;
    int const size = 6;
    Player players[size];
    Coordinate coor[60];
    Coordinate win_position[60];

    int menu;
    int first_pair, second_pair;
    int user, comp1, comp2, comp3;
    int playerSelect_case;
    int checker_number = -1;
    Coordinate *checker_ptr = new Coordinate();

    set_ConsoleSize(80,30);
    CheckerBoard.reset_board();

    for(;;)
    {
        print_menu();
        cin >> menu;

        if(cin.fail()) {
            cin.clear();
            cin.sync();
            continue;
        }

        if(menu == 1 || menu == 2)
        {
            break;
        }
        else if(menu == 3)
        {
            exit(0);
        }
    }

    if(menu == 1)
    {
        for(;;)
        {
            try
            {
                print_select();
                cin >> first_pair >> second_pair;

                if(first_pair == second_pair || first_pair < 1 || first_pair > 3 ||
                   second_pair < 1 || second_pair > 3 )
                {
                    throw first_pair;
                    if(cin.fail())
                        throw first_pair;
                }
                else
                {
                    if(first_pair != 1 && second_pair != 1)
                    {
                        playerSelect_case = 0;
                    }
                    else if(first_pair != 2 && second_pair != 2)
                    {
                        playerSelect_case = 1;
                    }
                    else if(first_pair != 3 && second_pair != 3)
                    {
                        playerSelect_case = 2;
                    }

                    break;
                }
            }
            catch(int e)
            {
                cin.clear();
                cin.sync();
                cout << "Invalid number of pair !!\n\n";
                system("pause");
            }
        }

        for(;;)
        {
            try
            {
                print_selectUser();
                cin >> user;

                if(cin.fail()) {
                    throw user;
                }

                user--;

                if(playerSelect_case == 0)
                {
                    if(user == 0 || user == 3)
                    {
                        throw user;
                    }
                    else
                    {
                        break;
                    }
                }
                else if(playerSelect_case == 1)
                {
                    if(user == 1 || user == 4)
                    {
                        throw user;
                    }
                    else
                    {
                        break;
                    }

                }
                else if(playerSelect_case == 2)
                {
                    if(user == 2 || user == 5)
                    {
                        throw user;
                    }
                    else
                    {
                        break;
                    }

                }

            }
            catch(int e)
            {
                cin.clear();
                cin.sync();
                cout << "Invalid number of user player !!\n\n";
                system("pause");
            }
        }

        int n[4];

        if(playerSelect_case == 0)
        {
            n = {1,2,4,5};
        }
        else if(playerSelect_case == 1)
        {
            n = {0,2,3,5};
        }
        else if(playerSelect_case == 2)
        {
            n = {0,1,3,4};
        }

        for(int i=0; i<4; i++)
        {
            if(user == n[i])
            {
                comp1 = n[(i+1)%4];
                comp2 = n[(i+2)%4];
                comp3 = n[(i+3)%4];
                break;
            }
        }

        set_checker(playerSelect_case, players, coor);
        memcpy(win_position, coor, sizeof(coor));
    }
    else if(menu == 2)
    {
        load_checker(players, win_position, playerSelect_case, user, comp1, comp2, comp3);
    }

    int store[5];
    {
        store[0] = playerSelect_case;
        store[1] = user;
        store[2] = comp1;
        store[3] = comp2;
        store[4] = comp3;
    }

    for(;;)
    {
        bool move = false;

        while(move == false)
        {
            CheckerBoard.update_board(players);
            CheckerBoard.print_board(checker_ptr);
            print_info(CheckerBoard, checker_ptr);
            print_option();
            mouseEvent(move, user, players, CheckerBoard, checker_ptr, checker_number, store);
        }

        CheckerBoard.update_board(players);
        CheckerBoard.print_board(checker_ptr);

        if(check_winner(user, CheckerBoard, coor) == true)
        {
            print_winner(user);
            break;
        }


        computer_move(comp1, CheckerBoard, players, win_position);
        CheckerBoard.reset_board();
        CheckerBoard.update_board(players);
        CheckerBoard.print_board(checker_ptr);
        cout << comp1;
        if(check_winner(comp1, CheckerBoard, coor) == true)
        {
            print_winner(comp1);
            break;
        }

        computer_move(comp2, CheckerBoard, players, win_position);
        CheckerBoard.reset_board();
        CheckerBoard.update_board(players);
        CheckerBoard.print_board(checker_ptr);

        if(check_winner(comp2, CheckerBoard, coor) == true)
        {
            print_winner(comp2);
            break;
        }

        computer_move(comp3, CheckerBoard, players, win_position);
        CheckerBoard.reset_board();
        CheckerBoard.update_board(players);
        CheckerBoard.print_board(checker_ptr);

        if(check_winner(comp3, CheckerBoard, coor) == true)
        {
            print_winner(comp3);
            break;
        }
    }
}
