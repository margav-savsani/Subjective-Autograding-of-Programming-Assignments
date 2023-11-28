#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <bits/stdc++.h>

class BST {
  // Add your own field and members here
  public:

  BST* parent;
  BST* left_child;
  BST* right_child;
  long long int satellite;

  BST(long long int sat = 0){
    parent = NULL;
    left_child = NULL;
    right_child = NULL;
    satellite = sat;
  }

  void insert(long long int d){
    if(d >= satellite){
      if(right_child == NULL){
        right_child = new BST(d);
        return;
      }
      right_child->insert(d);
    }
    else{
      if(left_child == NULL){
        left_child = new BST(d);
        return;
      }
      left_child->insert(d);
    }
  }

  void printBST(const std::string &prefix, bool isLeft){
    cout << prefix;
    cout << (isLeft ? "|--" : "|__" );
    cout << satellite << endl;
    if(left_child != NULL){
      left_child->printBST(prefix + (isLeft ? "│   " : "    "),true);
    }
    if(right_child != NULL){
      right_child->printBST(prefix + (isLeft ? "│   " : "    "),false);     
    }
  }
  // Feel free to use the printBST function used earlier
};

class Node {
 public:
  int value;

  vector<Node*> adjacency; // adjacency list

  bool visitonce;
  int parent_1;
  bool visitwice;
  int parent_2;

  Node(int val = 0){
    value = val;
    visitonce = false;
    visitwice = false;
    parent_1 = 0;
    parent_2 = 0;
  }

  void add_adjacent(Node *n){
    adjacency.push_back(n);
  }
  // insert other fields and methods as appropriate
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;

  BST** component_trees;
  int num_comp;
  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    component_trees = new BST*[nNodes];
    num_comp = 0;
    numNodes = nNodes;
    numEdges = nEdges;
    graphFile.open(gFileName, ios::out);
    if (!graphFile.is_open()) {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }

    graphFile << numNodes << endl;
    graphFile << numEdges << endl;

    nodes = new Node[numNodes];
    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
    }

    srand(time(0));
    int n1, n2;
    int countEdges = 0;
    
    while (countEdges < numEdges) {
      do {
	n1 = rand() % numNodes;
	n2 = rand() % numNodes;
      // cin >> n1;
      // cin >> n2;
      } while (n1 == n2);

      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to

      // graphFile
      if(
        find(nodes[n1].adjacency.begin(), nodes[n1].adjacency.end(), &nodes[n2]) == nodes[n1].adjacency.end()){
        nodes[n1].add_adjacent(&nodes[n2]);
        nodes[n2].add_adjacent(&nodes[n1]);
        graphFile << n1+1 << " " << n2+1 << endl;
        countEdges++;
      }

    }

    // Add appropriate code as necessary for your implementation
  }
      
  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;
    // Add appropriate code as necessary for your implementation
  }

  // Add appropriate method declarations as necessary for your implementation
  void DFS(Node &n, BST* my_tree);
  void modifiedDFS();
  void printResults();
};

#endif
