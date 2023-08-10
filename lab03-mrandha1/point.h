#pragma once

#include "shape.h"
using namespace std;

class Point: public Shape{


  private:
    int x;//xth col
    int y;//yth row
    char  symbol;//symbol to be changed to

  public:

    Point(int x,int y,char symbol);
    //draws the shape onto the grid
    void draw(Grid* grid);



 };
