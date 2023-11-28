#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

struct BSTNode{
  int value;
  BSTNode* left;
  BSTNode* right;
  BSTNode(int value, BSTNode* left, BSTNode* right){
    this->value = value;
    this->right = right;
    this->left = left;
  }
};

class BST {
  // Add your own field and members here
  BSTNode* root;
  public:
    BST(){
      root = nullptr;
    }
  
    void insert( int value){
      BSTNode* temp = root;
      BSTNode* track = temp;
      if (root == nullptr){
        root = new BSTNode(value, nullptr, nullptr);
        return;
      }
      while(temp != nullptr){
        if(value > temp->value) {temp = temp->right; track = temp;}
        else {temp = temp->left; track = temp;}
      }
      temp = new BSTNode(value, nullptr, nullptr);
      if (temp->value > track->value) track->right = temp;
      else track->left = temp;
    }
    // Feel free to use the printBST function used earlier
};

class Node {
 public:
  int value;
  // insert other fields and methods as appropriate
  int numAdj=0;
  int* adjInd = new int;
  // Node *adjNodes;
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;
  int* visitedArr1 = new int;
  int* visitedArr2 = new int;
  int* parentInd = new int;
  BST* tree = new BST();
  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;

    for(int i=0; i<nNodes; i++){
      visitedArr1[i] = 0;
      visitedArr2[i] = 0;
      parentInd[i] = -1;
    }

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
      } while (n1 == n2);

      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile

      bool add = true;
      for (int i=0; i< nodes[n1].numAdj; i++){
        if (nodes[n1].adjInd[i] == n2) {add=false; break;}
      }

      if (add){
        nodes[n1].adjInd[nodes[n1].numAdj] = n2;
        nodes[n1].numAdj++;
        nodes[n2].adjInd[nodes[n2].numAdj] = n1;
        nodes[n2].numAdj++;
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

  void modifiedDFS();
  void printResults();
};

#endif
