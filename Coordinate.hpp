#ifndef COORDINATE_H
#define COORDINATE_H

/** @class Coordinate
  * Act as a point to show location */

class Coordinate
{
    private:
    int row;
    int col;

    public:
    Coordinate();
    ~Coordinate();
    Coordinate(int y, int x);
    void setCol(int x);
    void setRow(int y);
    int getCol();
    int getRow();
};

#endif
