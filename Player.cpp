#include "Player.hpp"

Player::Player()
{
    exist = false;
}

bool Player::isExist()
{
    return exist;
}

void Player::setPlayer(int checker, Checker c)
{
    player[checker] = c;
    exist = true;
}

void Player::setColour(int colour_code)
{
    this->colour_code = colour_code;
}

void Player::movePlayer(int i, Coordinate coor)
{
    player[i].moveChecker(coor);
}

int Player::getPlayerRow(int i)
{
    return player[i].getCheckerRow();
}

int Player::getPlayerCol(int i)
{
    return player[i].getCheckerCol();
}

int Player::getColour()
{
    return colour_code;
}


