/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include <iostream>
#include <string>
#include <utility>

#include "maze.h"
#include "mazeUtils.h"

using namespace std;

int main(int argc, char** argv) {
     //the first input is supposed to be a file and the second is supposed to be the search_type
    string filename=argv[1];
    string search_type=argv[2];
    List<Position*>* solution = nullptr;
    Maze* maze = nullptr;

    string breadth = "breadth";
    string depth = "depth";
    //if there are more than the 2 inputs allowed
    if(argc>3){
      throw runtime_error ("invalid number of inputs(2 arguments, please)");
      return 0;
    }
    //if the search_type is invalid
    if(search_type.compare(breadth)==0 && search_type.compare(depth)==0){
      throw runtime_error ("choose 'breadth' or 'depth'");
      return 0;
    }
    //try to load the map
    try {
      maze = loadMap(filename);
    }
    //while looking out for runtime_errors being thrown 
    catch (runtime_error e) {
      cout << " invalid filename" << endl;
      return 0;
    }
    //calls appopriate search function
    if (search_type == "breadth"){
       solution = maze->solveBreadthFirst();
    }
    else if(search_type == "depth"){
       solution = maze->solveDepthFirst();
    }
    //converts the solution list to a printable solution
    string rendered_answer = renderAnswer(maze, solution);
    cout << rendered_answer << endl;
    //cleans up the space
    delete solution;
    delete maze;


    return 0;
}
