// CSCI 311 lab 7
// Graph class skeleton cpp file
// change name to "Graph.cpp"


#include <iostream>
#include "Graph.h"
#include <queue>
#include <limits.h>

//do not change the headers above
//implement the functions below, but do not add new functions


Graph::Graph(){
  nodes = {};
}

void Graph::printAdjList(){
  for (auto node : nodes) {
    std::cout << node->id << ": ";
    for (auto neighbor : node->neighbors) {
      std::cout << neighbor->id << " ";
    }
    std::cout << std::endl;
  }
}

bool Graph::isNeighbor(int u, int v){
  for (auto node : nodes) {
    if (node->id == u) {
      for (auto neighbor : node->neighbors) {
        if (neighbor->id == v) {
          return true;
        }
      }
    }
  }

  return false;
}

void Graph::DFS(){
}

int Graph::DFSVisit(int s, int time){
  return time;
}

void Graph::BFS(int s){
}

std::vector<int> Graph::distancesFrom(int s){
}
