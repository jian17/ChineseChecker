#ifndef FUNCTION_H
#define FUNCTION_H

#include "Board.hpp"
#include "Player.hpp"
#include "Checker.hpp"
#include "Coordinate.hpp"
#include "SearchTree.hpp"
#include "List.hpp"

/** Function list that can use in all class & main */

void gotoxy ( int x, int y );
void set_cursor(bool visible);
void set_color(int foreground_color, int background_color);
void set_ConsoleSize(int width, int height);
void print_menu();
void print_select();
void print_selectUser();
void print_option();
void print_info(Board &checkerBoard, Coordinate *checker_ptr);
void print_winner(int player);
bool check_winner(int player_turn, Board &checkerBoard, Coordinate coor[]);
void set_checker(int playerSelect_case, Player players[], Coordinate coor[]);
void load_checker(Player players[], Coordinate win_position[], int& playerSelect_case, int& user, int& comp1, int& comp2, int& comp3);
void save(Player players[], int playerSelect_case, int user, int comp1, int comp2, int comp3);
Coordinate jump(int direction, Coordinate coor);
Coordinate get_firstJump(int direction, Coordinate prev_coor, Board &checkerBoard);
Coordinate get_secondJump(int direction, Coordinate prev_coor, Board &checkerBoard);
void mouseEvent(bool &move, int user, Player players[], Board &checkerBoard, Coordinate* checker_ptr, int& checker_number, int store[]);
void computer_move(int comp, Board &checkerBoard, Player players[], Coordinate win_position[]);

#endif
