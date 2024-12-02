/***********************************************
************CSCI-311-PROJECT-3-V-1011***********
************************************************
*******CODE-CHECKER-STARTING-ALIGNMENT**********
************************************************
*************CONTROL-NUMBER-XA-73***************
************************************************
**REPORT-GENERATION-MODE-AUTO_SYNC-EXCEPTION-2**
************************************************
*****************DATETIME-SYS*******************
************************************************/

// G1_EXCEPTION: Only produce your code as directed in Section A, B, C, and D1_EXCEPTION.
// G2_EXCEPTION: Do not write anything at the other places in this file.
// D1_EXCEPTION: Put you names here (on this line):______________________________________

/***********************************************
*************SECTION-A-HEADERS******************
************************************************/
// SECTION_A_START: put your header files here using the include directive.
// G3_EXCEPTION: You can also declare using standard namespace if you like, but do not use any global variable or method.

#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <vector>

// SECTION_A_END: Section A ends here.
/***********************************************
*************SECTION-A-HEADERS-END**************
************************************************/

/***********************************************
*************SECTION-B-CLASSES******************
************************************************/
// SECTION_B_START: put all your classes definitions here.

class Node {
 public:
  int id;
  bool is_charger;

  Node(int id, bool is_charger) : id(id), is_charger(is_charger) {};
  bool operator<(const Node& n) const { return id < n.id; }
};

class Graph {
 public:
  std::vector<Node> nodes;
  std::map<Node, std::map<Node, int>> graph;

  Graph() {
    nodes = std::vector<Node>();
    graph = std::map<Node, std::map<Node, int>>();
  }

  Graph(int num_nodes, int num_edges) {
    nodes = std::vector<Node>(num_nodes);
    graph = std::map<Node, std::map<Node, int>>();
  }

  void addEdge(Node u, Node v, int dist) {
    graph[u][v] = dist;
    graph[v][u] = dist;
  }
};

// SECTION_B_END: Section B ends here.
/***********************************************
*************SECTION-B-CLASSES-END**************
************************************************/

/***********************************************
*************SECTION-C-MAIN-FUNCTION************
************************************************/
// SECTION_C_START: write your main function here.

int main(int argc, char** argv) {
  int num_nodes, num_edges, max_range, initial_range = 0;
  std::cin >> num_nodes >> num_edges >> max_range >> initial_range;

  int start, end = 0;
  std::cin >> start >> end;

  std::vector<int> chargers(num_nodes);

  for (int i = 0; i < num_nodes; i++) {
    int id, is_charger = 0;
    std::cin >> id >> is_charger;
    chargers[id] = is_charger;
  }

  Graph graph(num_nodes, num_edges);

  for (int i = 0; i < num_edges; i++) {
    int u, v, dist = 0;
    std::cin >> u >> v >> dist;

    Node node_u(u, chargers[u]);
    Node node_v(v, chargers[v]);

    graph.addEdge(node_u, node_v, dist);
  }

  // // Structured binding C++17
  // for (auto& [node, edges] : graph) {
  //     std::cout << "Node " << node.id << " is a charger: " << node.charger << std::endl;
  //     for (auto& [edge, dist] : edges) {
  //         std::cout << "Edge to " << edge.id << " with distance " << dist << std::endl;
  //     }
  // }
}

// SECTION_C_END: Section C ends here.
/***********************************************
************SECTION-C-MAIN-FUNCTION-END*********
************************************************/

/***********************************************
**************PLAGIARISM-RTNG-PRTCL-C***********
****************GEN-AI-RTNG-PRTCL-K*************
*********LOOP-CS_SEC-CS_CHR-STU_R_R_RFR*********
*****************DICT-A-ENTRY-1011**************
***************ORI-KTIAN@CSUCHICO.EDU***********
************************************************/

/***********************************************
*********CODE-CHECKER-ENDING-ALIGNMENT**********
************************************************/