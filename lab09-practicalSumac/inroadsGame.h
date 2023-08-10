/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#pragma once
#include "./adts/graph.h"
#include "./adts/dictionary.h"
#include "./adts/edge.h"

using namespace std;

/**
 * An instance of this class represents a single game of Inroads.  An object of
 * type InroadsGame does not represent the user interface, but does represent
 * the idea of a game of Inroads, including the state of the board and all of
 * the information pertaining to the player.  It also includes the logic for
 * making moves in the game and enforces the game's rules.
 */
class InroadsGame {
  public:


    //constructor which takes in a pointer to the graph and a list of pairs
    //of vertex Positions
    InroadsGame(Graph<string, bool, int>* g,
                Dictionary<std::string, pair<int, int>>* vertexPositions);
    //destructor which deallocates dynamically allocated memory
    ~InroadsGame();
    //Input: A pair of two strings each of which is the vertex of the selected
    //road
    //Process: it checks if the move was valid, and if so, calculates the scores
    //output: returns 0 if the selected road was unimproved previously
    //        returns 1 if the selected road was already improved
    int updategraph(pair<string, string>  move);
    //returns current score
    int getScore();
    //returns current number of turns
    int getTurns();
    //returns the current message
    string getMessage();
    //this method returns a pointer to a graph which only has already improved
    //edges
    Graph<string,bool,int>* copy_maker();
    //calculates the score due to library
    //returns nothing
    void scoring_library_residential();
    //calculates the score due to store
    //returns nothing
    void scoring_store_residential();
    //calculates the score due to medical
    //returns nothing
    void scoring_medical_residential();

  private:


    Graph<string, bool, int>* graph;
    int score;
    int score_medical;
    int score_store;
    int score_library;
    int turns;
    string next_message;
    bool library_connected;
    bool store_connected;
    string library_location;
    Dictionary<string,string>* residential_location;
    Dictionary<string,string>* store_location;
    Dictionary<string,string>* improved_roads;
    Dictionary<string,string>* visited_locations;
    Dictionary<std::string, pair<int, int>>* locations;

};
