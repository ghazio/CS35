#pragma once

#include "shape.h"

// TODO: Declare your Rectangle class here.
using namespace std;

class Rectangle: public Shape{
  private:
    int x;//xt row
    int y;//yth column
    int width;//width of the rectange
    int height;//height of the rectangle
    char symbol;//symbols
  public:
    Rectangle(int x, int y,int width, int height, char symbol);
    //draws the shape onto the grid
    void draw(Grid* grid);

};
