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
// D1_EXCEPTION: Put you names here (on this line): Colin Jamison

/***********************************************
*************SECTION-A-HEADERS******************
************************************************/
// SECTION_A_START: put your header files here using the include directive.
// G3_EXCEPTION: You can also declare using standard namespace if you like, but do not use any global variable or method.

#include <iostream>
#include <limits>
#include <memory>
#include <queue>
#include <stdexcept>
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
  int distance;
  int fuel;
  int version;
  bool is_charger;
  std::vector<Node> history;
  std::shared_ptr<Node> parent;

  Node() {
    id = -1;
    distance = std::numeric_limits<int>::max();
    fuel = -1;
    version = 0;
    is_charger = false;
  }
  Node(int id, bool is_charger) : id(id), is_charger(is_charger) {
    distance = std::numeric_limits<int>::max();
    fuel = -1;
    version = 0;
    parent = nullptr;
  }

  bool operator<(const Node& n) const {
    if (distance == n.distance) return id < n.id;
    return distance < n.distance;
  }
  bool operator>(const Node& n) const { return n.id < id; }
  bool operator==(const Node& n) const { return id == n.id && version == n.version; }
};

class Path {
 public:
  std::vector<Node> nodes;
  int total_distance = 0;
  int start_id, end_id = -1;

  Path() {}

  void add_node(Node node, int distance) {
    nodes.push_back(node);
    total_distance += distance;
  }

  friend std::ostream& operator<<(std::ostream& os, const Path& path) {
    os << path.total_distance << ": ";
    for (auto& node : path.nodes) {
      if (node.id == path.start_id || node.id == path.end_id || node.is_charger) {
        os << node.id << " ";
      }
    }
    os << std::endl;
    return os;
  }
};

class Graph {
  std::vector<Node> nodes;
  std::vector<std::vector<int>> adj_matrix;
  int max_charge, initial_charge = -1;
  int start_id, end_id = -1;

 public:
  Graph(int num_nodes) {
    nodes.resize(num_nodes);
    adj_matrix.resize(num_nodes, std::vector<int>(num_nodes, -1));
  }

  void add_node(int id, bool is_charger) {
    if (id >= nodes.size()) {
      nodes.resize(id + 1);
    }
    nodes[id] = Node(id, is_charger);
  }

  void add_edge(int u, int v, int weight) {
    if (u >= adj_matrix.size() || v >= adj_matrix.size()) {
      throw std::out_of_range("Node id out of range");
    }

    adj_matrix[u][v] = weight;
    adj_matrix[v][u] = weight;
  }

  bool is_neighbor(int u, int v) const { return adj_matrix[u][v] >= 0; }

  static Graph initialize() {
    int num_nodes, num_edges, max_charge, initial_charge = 0;
    std::cin >> num_nodes >> num_edges >> max_charge >> initial_charge;

    int start_id, end_id = 0;
    std::cin >> start_id >> end_id;

    Graph graph(num_nodes);
    graph.max_charge = max_charge;
    graph.initial_charge = initial_charge;
    graph.start_id = start_id;
    graph.end_id = end_id;

    for (int i = 0; i < num_nodes; i++) {
      bool is_charger = false;
      int id = 0;
      std::cin >> id >> is_charger;
      graph.nodes[id] = Node(id, is_charger);
    }

    for (int i = 0; i < num_edges; i++) {
      int u, v, weight = 0;
      std::cin >> u >> v >> weight;
      graph.add_edge(u, v, weight);
    }

    return graph;
  }

  bool verify_path(const Path& path) {
    if (path.nodes.empty()) return false;

    int fuel = initial_charge;
    for (int i = 0; i < path.nodes.size() - 1; i++) {
      Node u = path.nodes[i];
      Node v = path.nodes[i + 1];
      if (!is_neighbor(u.id, v.id)) return false;

      fuel -= adj_matrix[u.id][v.id];
      if (fuel < 0) return false;
      if (v.is_charger) fuel = max_charge;
    }

    return true;
  }

  friend std::ostream& operator<<(std::ostream& os, const Graph& g) {
    for (auto& node : g.nodes) {
      os << "Node: " << node.id << " Charger: " << node.is_charger << std::endl;
      for (int i = 0; i < g.adj_matrix.size(); i++) {
        if (g.is_neighbor(node.id, i)) {
          os << "  Neighbor: " << i << " Weight: " << g.adj_matrix[node.id][i] << std::endl;
        }
      }
    }
    return os;
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
  Graph graph = Graph::initialize();
  std::cout << graph << std::endl;
  Path path;
  path.add_node(Node(0, true), 0);
  path.add_node(Node(2, false), 49);
  path.add_node(Node(4, true), 27);
  path.add_node(Node(7, true), 57);
  std::cout << path << std::endl;

  std::cout << graph.verify_path(path) << std::endl;
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