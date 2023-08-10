#include "point.h"
#include <string>

using namespace std;


 Point::Point(int x,int y,char symbol){
    this->x=x;
    this->y=y;
    this->symbol=symbol;
}
void Point::draw(Grid* grid){

  grid->placeSymbol(this->x,this->y,this->symbol);

}
