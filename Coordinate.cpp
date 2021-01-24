#include <iostream>
#include "Coordinate.hpp"
using namespace std;

Coordinate::Coordinate()
{
    col = 0;
    row = 0;
}

Coordinate::~Coordinate()
{

}

Coordinate::Coordinate(int y, int x)
{
    col = x;
    row = y;
}

void Coordinate::setCol(int x)
{
    col = x;
}


void Coordinate::setRow(int y)
{
    row = y;
}

int Coordinate::getCol()
{
    return col;
}

int Coordinate::getRow()
{
    return row;
}
