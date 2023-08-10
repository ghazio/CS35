#include "verticalLine.h"
#include <string>

using namespace std;
// TODO: Define your VerticalLine methods here.

VerticalLine::VerticalLine(int x, int y,int length, char symbol){
  this->x=x;
  this->y=y;
  this->length=length;
  this->symbol=symbol;
}

void VerticalLine::draw(Grid* grid){

  //this will fill up the symbols for the line
  for(int i=0;i<length;i++){
    grid->placeSymbol(this->x,(this->y)+i,this->symbol);

    }
};
