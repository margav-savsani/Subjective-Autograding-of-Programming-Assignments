#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
using namespace std;

template <typename T> class list{ // a template class for linked list implementation
 public:
  T value;
  list *next;
  list(){
    value = nullptr;
    next = nullptr;
  }
};

class Node { // the same Node class is used both for BST as well as for the graph
 public:
  int value;
  Node *parent; // parent, left, right are for BST
  Node *left;
  Node *right;
  int *adj_list; // adjacency list and index is for the Graph
  int index;
  Node(){
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    index = 0;
  }
};

class BST{ // the BST class
 public:
	Node *root;
	BST(){
    root = nullptr;
  }
	void printBST(const string& prefix, bool isLeft=false){ // the printBST function copied from previous labs
      if( root != nullptr ){
          cout << prefix;
          cout << (isLeft ? "|--" : "|__" );
          cout << root->value << endl;
          Node *curr = root;
          root = root->left;
          printBST( prefix + (isLeft ? "│   " : "    "), true);
          root = curr->right;
          printBST( prefix + (isLeft ? "│   " : "    "), false);
          root = curr;
      }
  }
	void insert(int value){ // the insert function copied from previous labs
    Node *tmp = root;
    Node *parent = nullptr;
    bool dir;
    while (tmp != nullptr){
        if (tmp->value >= value){ // go left if same value
            parent = tmp;
            tmp = tmp->left;
            dir = true;
        }
        else{
            parent = tmp;
            tmp = tmp->right;
            dir = false;
        }
    }
    if (parent != nullptr){
        if (dir){
            parent->left = new Node();
            parent->left->value = value;
            parent->left->parent = parent;
        }
        else{
            parent->right = new Node();
            parent->right->value = value;
            parent->right->parent = parent;
        }
    }
    else{
        root = new Node();
        root->value = value;
    }
    return;
  }
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;
  int *visited; // the visited array
  int *ba_tr; // to determine whether we have backtracked from an edge or not
  int *pt; // the parent array, stores the parent of the corresponding node
  int conn_comp; // number of connected components
  list<BST *> *trees; // list of BST trees
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    conn_comp = 0;
    graphFile.open(gFileName, ios::out);
    if (!graphFile.is_open()) {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }

    graphFile << numNodes << endl;
    graphFile << numEdges << endl;
    // initialising the various members of the Graph class
    nodes = new Node[numNodes];
    visited = new int[numNodes];
    ba_tr = new int[numNodes];
    pt = new int[numNodes];
    trees = new list<BST *>();
    if (nodes == nullptr || visited == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }
    // initialising the various members of the Graph class
    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
      visited[i] = 0;
      nodes[i].adj_list = new int[numNodes];
      ba_tr[i] = 0;
      pt[i] = -1;
    }

    srand(time(0));
    int n1, n2;
    int countEdges = 0;
    
    while (countEdges < numEdges) {
      do {
	n1 = rand() % numNodes;
	n2 = rand() % numNodes;
      } while (n1 == n2);

      bool present = false;
      for (int i = 0; i < nodes[n1].index; i++){
        if (nodes[n1].adj_list[i] == nodes[n2].value){ // if edge always present, rechoose the vertices
          present = true;
          break;
        }
      }
      if (present){
        continue;
      }
      else{ // if edge not present, add it in both the adjacency lists
        nodes[n1].adj_list[nodes[n1].index] = nodes[n2].value;
        nodes[n1].index ++;
        nodes[n2].adj_list[nodes[n2].index] = nodes[n1].value;
        nodes[n2].index ++;
      }

      graphFile << n1+1 << " " << n2+1 << endl;
      countEdges++;
    }
  }
      
  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;
  }

  void modifiedDFS();
  void printResults();
};

#endif
