#ifndef CHECKER_H
#define CHECKER_H
#include "Coordinate.hpp"

/** @class Checker
  * Create checkers for each player
  * Store the location of the checker */

class Checker
{
    private:
    Coordinate coor;

    public:
    Checker();
    void setChecker(Coordinate coor);
    void moveChecker(Coordinate coor);
    int getCheckerRow();
    int getCheckerCol();
};

#endif
