#include "grid.h"
#include "shape.h"
#include "point.h"
#include "horizontalLine.h"
#include "verticalLine.h"
#include "rectangle.h"
#include <iostream>

using namespace std;

void test1() {
    cout << "===== Test 1 =====" << endl;
    // Create grid
    Grid* grid = new Grid();
    // Place symbols
    grid->placeSymbol(4, 3, 'A');
    grid->placeSymbol(3, 4, 'B');
    grid->placeSymbol(5, 5, 'C');
    // Print grid
    grid->print();
    // Free memory
    delete grid;
}

void test2() {
    cout << "===== Test 2 =====" << endl;
    // Create grid
    Grid* grid = new Grid();
    // Create shape
    Shape* myShape = new Rectangle(1, 2, 5, 3, '@');
    // Draw shape
    myShape->draw(grid);
    grid->print();
    // Free memory
    delete myShape;
    delete grid;
}

void test3() {
    cout << "===== Test 3 =====" << endl;
    // Create grid
    Grid* grid = new Grid();
    // Create shapes
    int length = 3;
    Shape** shapes = new Shape*[3];
    shapes[0] = new Rectangle(0, 0, 7, 7, '$');
    shapes[1] = new Rectangle(1, 1, 6, 4, '-');
    shapes[2] = new Rectangle(3, 2, 4, 3, '&');
    // Draw shapes
    for (int i = 0; i < 3; i++) {
        shapes[i]->draw(grid);
    }
    grid->print();
    // Free memory
    for (int i = 0; i < 3; i++) {
        delete shapes[i];
    }
    delete[] shapes;
    delete grid;
}

void test4() {
    cout << "===== Test 4 =====" << endl;
    // Create grid
    Grid* grid = new Grid();
    // Create shapes
    int length = 12;
    Shape** shapes = new Shape*[length];
    shapes[0] = new Point(0, 0, 'O');
    shapes[1] = new Point(0, 9, 'O');
    shapes[2] = new Point(9, 0, 'O');
    shapes[3] = new Point(9, 9, 'O');
    shapes[4] = new VerticalLine(0, 1, 8, '|');
    shapes[5] = new VerticalLine(9, 1, 8, '|');
    shapes[6] = new HorizontalLine(1, 0, 8, '~');
    shapes[7] = new HorizontalLine(1, 9, 8, '~');
    shapes[8] = new Rectangle(1, 1, 8, 8, '+');
    shapes[9] = new Rectangle(2, 2, 6, 6, '@');
    shapes[10] = new Rectangle(3, 3, 4, 4, '+');
    shapes[11] = new Rectangle(4, 4, 2, 2, '@');
    // Draw shapes
    for (int i = 0; i < length; i++) {
        shapes[i]->draw(grid);
    }
    grid->print();
    // Free memory
    for (int i = 0; i < length; i++) {
        delete shapes[i];
    }
    delete[] shapes;
    delete grid;
}

int main() {
    // Example test cases
    test1();
    test2();
    test3();
    test4();
}
