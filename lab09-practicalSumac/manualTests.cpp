/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include <string>
#include "./adts/graph.h"
#include "adjacencyListUndirectedGraph.h"
#include "graphAlgorithms.h"

using namespace std;

template <typename V, typename E, typename W,
          template <class, class, class> class G = AdjacencyListUndirectedGraph>
Graph<V, E, W>* makeGraph(vector<V> vertices, vector<Edge<V, E, W>> edges) {
    Graph<V, E, W>* graph = new G<V, E, W>();
    for (int i = 0; i < vertices.size(); i++) {
        graph->insertVertex(vertices.at(i));
    }
    for (int i = 0; i < edges.size(); i++) {
        Edge<V, E, W> edge = edges.at(i);
        graph->insertEdge(edge.getSource(), edge.getDestination(),
                          edge.getLabel(), edge.getWeight());
    }
    return graph;
}

int main(int argc, char** argv) {
    Graph<string, bool, int>* graph =
        makeGraph<string, bool, int>({"1", "2", "3"}, {
                                                          {"1", "2", true, 1},
                                                          {"1", "3", true, 1},
                                                          {"2", "3", true, 1},
                                                      });
    vector<string> path = {"1", "3"};
    vector<string> path_returned=
                   shortestLengthPathBFS(string("1"), string("3"), graph);
    cout<<path[0]<<"  "<<path_returned[0]<<endl;


    // path = {"1", "2"};
    // checkEqualPath(path,
    //                shortestLengthPathBFS(string("1"), string("2"), graph));
    delete graph;
}
