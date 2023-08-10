#pragma once

#include "shape.h"



using namespace std;

class VerticalLine: public Shape{
  private:
    int x;//xth col
    int y;//yth row
    int length;//number of points to be converted
    char symbol;
  public:
    //this is the constructer
    VerticalLine(int x, int y,int length, char symbol);
    //draws the shape onto the grid
    void draw(Grid* grid);

};
