#include <iostream>
#include <stdexcept>

#include "picture.h"

using namespace std;


/*
this is the constructer, and it initializes the variables in Picture.
*/
Picture::Picture() {
    //since we start out with no shape
    this->numberOfShapes=0;
    //we are assuming no more than 50 shapes will be added.
    this->shapes=new Shape*[50];

}

/*
Input:This method takes in nothing
Method:deletes every thing being pointed to by data here
Output:nothing
*/

Picture::~Picture() {

    for (int i =0;i<numberOfShapes;i++){
      delete this->shapes[i];
    }
    delete[] this->shapes;

}
/*
Input:This method takes in nothing
Method:It makes a grid object from grid class, draws shapes onto it by going
through the shapes arrray of pointers, then converts the grid into a string.
Output:It returns a string which represents the grid
*/
string Picture::toString() {
    Grid* new_grid= new Grid();
    for(int i=0;i<this->numberOfShapes;i++){
      shapes[i]->draw(new_grid);
    }
    string resultant_string=new_grid->toString();
    delete new_grid;

    return resultant_string;
}
/*
Input:nothing
Method:this method prints the string which is representing the grid
Output:nothing
*/
void Picture::print() {
    cout << this->toString() << endl;
}

/*
Input:Pointer to a shape
Method:It adds the shape to the array of pointer to shapes and then it
      increases the number of shapes variable by one since we have one more
      shape being stored now.
Output:nothing
*/

void Picture::addShape(Shape* shape) {
    //nth new shape's pointer is stored at the n-1 position in the array, hence
    //we update it after we store a new shape.
    this->shapes[this->numberOfShapes]=shape;
    this->numberOfShapes++;
}
