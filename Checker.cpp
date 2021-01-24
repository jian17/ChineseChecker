#include "Checker.hpp"

Checker::Checker()
{

}

void Checker::setChecker(Coordinate coor)
{
    this->coor = coor;
}

void Checker::moveChecker(Coordinate coor)
{
    this->coor = coor;
}

int Checker::getCheckerRow()
{
    return coor.getRow();
}

int Checker::getCheckerCol()
{
    return coor.getCol();
}
