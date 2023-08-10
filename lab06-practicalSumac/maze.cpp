/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include <stdexcept>

/* ADTs */
#include "adts/list.h"
#include "adts/orderedCollection.h"
#include "adts/queue.h"
#include "adts/stack.h"

/* Implementations of above ADTs */
#include "adts/stlList.h"
#include "linkedQueue.h"
#include "linkedStack.h"
#include <iostream>

#include "maze.h"

using namespace std;

Maze::Maze(int width, int height) {
    this->width=width;
    this->height=height;
    this->positions= new Position**[width];
    for(int i=0;i<width;i++){
      this->positions[i]= new Position*[height];
      for(int j=0;j<height;j++){
        this->positions[i][j]= new Position(i,j);
      }
    }
}

Maze::~Maze() {
  for(int i=0;i<width;i++){

   for(int j=0;j<height;j++){
     delete this->positions[i][j];
    }
    delete[] this->positions[i];
   }
  delete[] this->positions;

}
int Maze::getWidth() {
    return this->width;
}

int Maze::getHeight() {
    return this->height;
}

bool Maze::isWall(int x, int y) {
    if(positions[x][y]->isWall()){
      return 1;
    }
    else{
      return 0;
    }
}

void Maze::setWall(int x, int y) {
    positions[x][y]->setWall();
}

List<Position*>* Maze::solveBreadthFirst() {
  LinkedQueue<Position*>* exploration = new LinkedQueue<Position*>();
  List<Position*>* solution_path = solve(exploration);
  delete exploration;
  return solution_path;
}

List<Position*>* Maze::solveDepthFirst() {
    LinkedStack<Position*>* exploration = new LinkedStack<Position*>();
    List<Position*>* solution_path = solve(exploration);
    delete exploration;
    return solution_path;
}

List<Position*>* Maze::solve(OrderedCollection<Position*>* exploration) {
    exploration->insert(this->positions[0][0]);

    this->positions[0][0]->setVisited();
    Position* current_position= nullptr;
    List<Position*>* solution_path = nullptr;

    while(exploration->getSize()!=0){
      current_position=exploration->remove();
      if (current_position==this->positions[this->getWidth()-1][this->getHeight()-1]){
          Position* position_holder = current_position;
          List<Position*>* solution_path= new STLList<Position*>();
          solution_path->insertFirst(position_holder);
          while(position_holder!=this->positions[0][0]){
            solution_path->insertFirst(position_holder->getPrevious());
            position_holder=position_holder->getPrevious();
           }

          return solution_path;
      }
      List<Position*>* neighbors = getNeighbors(current_position);
      int num_neighbors = neighbors->getSize();
      for(int i=0; i<num_neighbors;i++){
        if(neighbors->get(i)->isVisited() != 1){
          neighbors->get(i)->setVisited();
          neighbors->get(i)->setPrevious(current_position);
          if(neighbors->get(i)->isWall()!=1){
              exploration->insert(neighbors->get(i));
          }
        }
      }
      delete neighbors;
    }
    return nullptr;
}

List<Position*>* Maze::getNeighbors(Position* position) {
    int x=position->getX();
    int y=position->getY();
    List<Position*>* neighbors= new STLList<Position*>;

    if(y-1>=0){
      neighbors->insertLast(this->positions[x][y-1]);
    }
    if(x-1>=0){
    neighbors->insertLast(this->positions[x-1][y]);
    }
    if(x+1<this->getWidth()){
      neighbors->insertLast(this->positions[x+1][y]);
    }

    if(y+1<this->getHeight()){
      neighbors->insertLast(this->positions[x][y+1]);
    }

    return neighbors;

}
