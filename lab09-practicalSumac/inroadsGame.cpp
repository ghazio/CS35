/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/
#include "inroadsGame.h"
#include "./adts/stlHashTable.h"
#include "./adts/dictionary.h"
#include "./adts/edge.h"
#include "graphAlgorithms.h"
#include "adjacencyListUndirectedGraph.h"
#include "adjacencyListGraph.h"
#include <string.h>
#include <stdio.h>

using namespace std;

// TODO: implement your InroadsGame class constructor and methods here

InroadsGame::InroadsGame(Graph<string, bool, int>* g,
            Dictionary<std::string, pair<int, int>>* vertexPositions){

              this->graph=g;
              this-> turns = 1;
              this-> score = 0;
              this->library_connected=0;
              this->library_location="";
              this->next_message="";
              this->score_store = 0;
              this->score_medical = 0;
              this->score_library = 0;
              this->improved_roads=new STLHashTable<string,string>();
              this->store_location=new STLHashTable<string,string>();
              this->residential_location = new STLHashTable<string,string>();
              vector<Edge<string, bool, int>> all_edges=g->getEdges();
              this->visited_locations = new STLHashTable<string,string>();
              this->locations=vertexPositions;
            }

InroadsGame::~InroadsGame(){
  //delete all the dynamically allocated fields
  delete this->improved_roads;
  delete this->residential_location;
  delete this->store_location;
  delete this->visited_locations;
}

Graph<string,bool,int>* InroadsGame::copy_maker(){

  Graph<string,bool,int>* copied_graph=new AdjacencyListUndirectedGraph<string,bool,int>();
  vector<string> all_vertices=this->graph->getVertices();
  vector<Edge<string, bool, int>> all_edges=this->graph->getEdges();


  //for all vertices of original graph
  for(int i=0;i<all_vertices.size();i++){
    //if that vertex has been visited already
    if(this->visited_locations->contains(all_vertices[i])){
      //insert that vertex into our graph copy
      copied_graph->insertVertex(all_vertices[i]);
    }
  }

  //for each edge of the original graph
  for(int i=0;i<all_edges.size();i++){
    //if both the source and the destination of that edge have been visited
    //and the road has been improved
    if(this->visited_locations->contains(all_edges[i].getDestination())
       &&this->visited_locations->contains(all_edges[i].getSource())
       &&this->improved_roads->contains(all_edges[i].getSource()
       +all_edges[i].getDestination())) {
      //add that edge into the copy of the graph
        copied_graph->insertEdge(all_edges[i].getSource(),all_edges[i].getDestination(),
        all_edges[i].getLabel(),all_edges[i].getWeight());

   }
  }
  //return the copied graph containing only all the visited vertices and edges
  return copied_graph;
}


int InroadsGame::updategraph(pair<string,string> pair_input){

  string vertex1=pair_input.first;
  string vertex2=pair_input.second;


  //if the vertex1 is residential
  if(vertex1[0]=='R'){
    //we wrote this because it was crashing otherwise
    if(this->residential_location->isEmpty()){
      this->residential_location->insert(vertex1,vertex1);
    }
    //if the vertex is not already visited,
    if(!this->residential_location->contains(vertex1)){
      //store the vertex into the hashtable of residential locations
      this->residential_location->insert(vertex1,vertex1);
    }
  }

  //same process as above but for the second vertex
  if(vertex2[0]=='R'){
    if(this->residential_location->isEmpty()){
      this->residential_location->insert(vertex2,vertex2);
    }
    if(!this->residential_location->contains(vertex2)){
    this->residential_location->insert(vertex2,vertex2);
    }
  }

  //if the vertex is library
  if(vertex1[0] == 'L'){
    //set the library is connected and store the location of the library
    this->library_connected=1;
    this->library_location=vertex1;

  }
  //if the second vertex is library
  if(vertex2[0]=='L'){
    //set the library flag to connected and store the location of the library
    this->library_connected=1;
    this->library_location=vertex2;
  }

  //if the vertex is a store
  if(vertex1[0]=='S'){
    //if the hashtable is empty, then insert it directly
    if(this->store_location->isEmpty()){
      this->store_location->insert(vertex1,vertex1);
    }
    //if the hashtable does not contain the vertex already, then store it
    if(!this->store_location->contains(vertex1)){

      this->store_location->insert(vertex1,vertex1);
    }
  }
  //same as above but for vertex 2
  if(vertex2[0]=='S'){
    if(this->store_location->isEmpty()){
      this->store_location->insert(vertex2,vertex2);
    }
    if(!this->store_location->contains(vertex2)){
    this->store_location->insert(vertex2,vertex2);
    }
  }

  //if vertex 1 is not already visited, then store it
  if(!this->visited_locations->contains(vertex1)){
    this->visited_locations->insert(vertex1,vertex1);
  }
  //if vertex 2 is not visited already, then store it
  if(!this->visited_locations->contains(vertex2)){
    this->visited_locations->insert(vertex2,vertex2);
  }

  //we get the edge that contains the two vertices as source and destination
  Edge<string, bool, int> input_edge= this->graph->getEdge(vertex1,vertex2);

  string vectors_edge=input_edge.getSource()+input_edge.getDestination();

  //if the edge is already imrpoved, then we return 0
  if(this->improved_roads->contains(vectors_edge)){
    return 1;
  }
  //otherwise we go on and store the edge into the imrpoved roads hashtable
  //we also update the label of the edge
  string source=input_edge.getSource();
  string destination=input_edge.getDestination();
  int weight=this->graph->getEdge(source,destination).getWeight();

  this->graph->removeEdge(source,destination);
  this->graph->insertEdge(source,destination,1,weight);

  this->improved_roads->insert(vectors_edge,vectors_edge);

  //if library has been connected to something
  if(this->library_connected==1){
    //call the function to score up score due to library
    this->scoring_library_residential();
  }

  //call the function to score up score due to store
  this->scoring_store_residential();
  //call the function to score up score due to medical
  this->scoring_medical_residential();
  //increase the number of turns
  this->turns ++;
  //return 0 to let our main know that the information
  return 0;
}



int InroadsGame::getScore(){
  //returns the current score of the game
  return this->score;
}

int InroadsGame::getTurns(){
  //returns the current number of turns
  return this->turns;
}

string InroadsGame::getMessage(){
  //makes up the appropriate message
  string message=string("Your score this turn is :\n ") + string(" +") + to_string(this->score_library)
                + string(" from the library\n + ")   + to_string(this->score_store)
                + string(" from the store\n + ") + to_string(this->score_medical) + string(" from the medical\n")+
                  string("Total points this turn:")+to_string(this->score_library+this->score_store+this->score_medical);

  //returns the message
  return message;
}


void InroadsGame::scoring_library_residential(){

  int points_to_add=0;
  bool add_points = false;

  vector<string> visited_locations = this->visited_locations->getKeys();
  //call the copy maker to get a graph containing only the edges that have been
  //connected
  Graph<string,bool,int>* copy_improvedgraph=this->copy_maker();


  //for each of the visited vertices
  for(int i =0; i<visited_locations.size();i++){
    //if the visited location is a residential one
    if((visited_locations[i])[0]=='R'){
      //call the reacheable DFS on the library and the current residential vertex
      //under consideration
      add_points = reachableDFS(this->library_location,visited_locations[i],copy_improvedgraph);
      //if we know that the residential is connected to the library,
      if(add_points == true){
        //then we add 15 points
        points_to_add = points_to_add + 15;
      }
    }
  }
  //store the scores as appropriate and delete the graph
  this->score = this->score + points_to_add;
  this->score_library=points_to_add;
  delete copy_improvedgraph;
}



void InroadsGame::scoring_store_residential(){

  int points_to_add=0;
  vector<string> path;
  vector<string> visited_locations = this->visited_locations->getKeys();
  //we get the graph containing all the imrpoved roads only
  Graph<string,bool,int>* copy_improvedgraph=this->copy_maker();
  vector<string> store_locations=this->store_location->getKeys();

  //for each of the visited locations
  for(int i =0; i<this->visited_locations->getSize();i++){

    //if the vertex is residential
    if(visited_locations[i][0]=='R'){
      //then for each of the store locations
      for(int j=0;j<store_locations.size();j++){
        //try to run the program which might throw a runtime error
        try  {
          //find the shortest path between the residential location and the store location
          path = shortestLengthPathBFS(visited_locations[i],store_locations[j],copy_improvedgraph);

          //if the path is less than 3, then calculate the path
          if(path.size()-1<3){
            points_to_add = points_to_add + 10;
            }
          }
          //if there is a runtime error, then catch it and do nothing
          //because we dont care about a residential location that is
          //not connected to a store
          catch(runtime_error e){

          }
      }
    }
  }
  //store the appropriate store and delete the graph
  this->score_store=points_to_add;
  this->score = this->score + points_to_add;
  delete copy_improvedgraph;

}



void InroadsGame::scoring_medical_residential(){
  int points_to_add=0;
  Graph<string,bool,int>* copy_improvedgraph=this->copy_maker();
  Dictionary<string,int>* path;

  vector<string> visited_locations = this->visited_locations->getKeys();

  for(int i =0; i<this->visited_locations->getSize();i++){
    //we only check for connections between residential vertices and graphs

    if(visited_locations[i][0]=='M'){
        path = singleSourceShortestPath(visited_locations[i],copy_improvedgraph);
        vector<pair<string,int>> items=path->getItems();

        for(int j=0;j<items.size();j++){
          if(items[j].first[0]=='R'){
            points_to_add= points_to_add + 420/items[j].second;
          }
        }
        delete path;
    }
  }
  this->score_medical=points_to_add;
  this->score = this->score + points_to_add;
  delete copy_improvedgraph;

}
