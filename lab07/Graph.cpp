// CSCI 311 lab 7
// Graph class skeleton cpp file
// change name to "Graph.cpp"

#include "Graph.h"
#include <limits.h>
#include <iostream>
#include <queue>

// do not change the headers above
// implement the functions below, but do not add new functions

Graph::Graph() { nodes = {}; }

void Graph::printAdjList() {
  for (auto node : nodes) {
    std::cout << node->id << ": ";
    for (auto neighbor : node->neighbors) {
      std::cout << neighbor->id << " ";
    }
    std::cout << std::endl;
  }
}

bool Graph::isNeighbor(int u, int v) {
  for (auto neighbor : nodes[u]->neighbors) {
    if (neighbor->id == v) {
      return true;
    }
  }

  return false;
}

void Graph::DFS() {
  for (auto& node : nodes) {
    node->visited = false;
    node->predecessor = nullptr;
    node->discovered = -1;
    node->finished = -1;
  }

  int time = 0;

  for (auto& node : nodes) {
    if (!node->visited) {
      time = DFSVisit(node->id, time);
    }
  }
}

int Graph::DFSVisit(int s, int time) {
  time++;
  nodes[s]->discovered = time;
  nodes[s]->visited = true;

  for (auto& neighbor : nodes[s]->neighbors) {
    int idx = neighbor->id;
    if (!nodes[idx]->visited) {
      nodes[idx]->predecessor = nodes[s];
      time = DFSVisit(idx, time);
    }
  }

  time++;
  nodes[s]->finished = time;

  return time;
}

void Graph::BFS(int s) {
  for (auto& node : nodes) {
    node->dist = INT_MAX;
    node->visited = false;
    node->predecessor = nullptr;
  }

  nodes[s]->dist = 0;
  nodes[s]->visited = true;

  auto queue = std::queue<int>();
  queue.push(s);

  while (!queue.empty()) {
    int idx = queue.front();
    queue.pop();

    for (auto& neighbor : nodes[idx]->neighbors) {
      if (!neighbor->visited) {
        neighbor->dist = nodes[idx]->dist + 1;
        neighbor->visited = true;
        neighbor->predecessor = nodes[idx];
        queue.push(neighbor->id);
      }
    }
  }

}

std::vector<int> Graph::distancesFrom(int s) {
  auto distances = std::vector<int>();
  BFS(s);

  for (auto& node : nodes) {
    distances.push_back(node->dist);
  }

  return distances;
}
