#include "rectangle.h"
#include "grid.h"





Rectangle::Rectangle(int x, int y,int width,int height, char symbol){
 this->x=x;
 this->y=y;
 this->width=width;
 this->height=height;
 this->symbol=symbol;
}

void Rectangle::draw(Grid* grid){

  for(int j=0;j<height;j++){
    for(int i=0;i<width;i++){
      grid->placeSymbol((this->x+i),(this->y+j),this->symbol);
      }
    }
  };
