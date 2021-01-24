#ifndef PLAYER_H
#define PLAYER_H

#include "Checker.hpp"

/** @class Player
  * Create different players */

class Player
{
    private:
    int colour_code;
    Checker player[10];
    bool exist;

    public:
    Player();
    bool isExist();
    void setPlayer(int checker, Checker c);
    void setColour(int colour_code);
    void movePlayer(int i, Coordinate coor);
    int getPlayerRow(int i);
    int getPlayerCol(int i);
    int getColour();
};

#endif

