#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include<vector>
#include<map>

class BST {
  // Add your own field and members here
private:
  // Feel free to use the printBST function used earlier
  int* value;
  BST* left;
  BST* right;
  BST* parent;

  void printTREE(BST* root, const string& prefix, bool isLeft)
  {
    if(root != nullptr){
      cout << prefix;

      cout << (isLeft ? "|--" : "|__" );
      
      // print the value of the node
      root->printInfo();
      cout << endl;
      BST *curr = root;
      root = root->left;
      // enter the next tree level - left and right branch
      printTREE(root, prefix + (isLeft ? "│   " : "    "), true);
      root = curr->right;
      printTREE(root, prefix + (isLeft ? "│   " : "    "), false);
      root = curr;
    }
  }

public:
  BST(){
    value = nullptr;
    left = right = parent = nullptr;
  }
  BST(int a){
    value = new int(a);
    left = right = parent = nullptr;
  }

  void insert(int a){
    if(value == nullptr){
      value = new int(a);
      return;
    }
    BST* root = this;
    BST* prev = nullptr;
    while(root != nullptr){
      prev = root;
      if(a<*root->value){
        root = root->left;
      }
      else{
        root = root->right;
      }
    }
    if(a < *prev->value){
      prev->left = new BST(a);
      prev->left->parent = prev;
    }
    else{
      prev->right = new BST(a);
      prev->right->parent = prev;
    }
  }

  void printInfo(){
    cout << *value;
  }
  
  void printBST(){
    printTREE(this, "", false);
  }

};

class Node {
 public:
  int value;
  int timesVisited = 0;
  bool fullyvisited = 0;
  // insert other fields and methods as appropriate
  vector<int> adjecencyList;

  bool findAdj(int a){
    for(int i=0; i<adjecencyList.size(); i++){
      if(adjecencyList[i] == a) return true;
    }
    return false;
  }

  int numEdges(){
    return adjecencyList.size();
  }

};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;

  int nComponents;
  Node *nodes;
  map<string, bool> edges;

  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    nComponents = 0;
    // edges = new Edge[nEdges*2];
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
    // srand(0);

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

      if(!nodes[n1].findAdj(n2)){
        edges[to_string(n1)+ "->"+ to_string(n2)] = 0;
        edges[to_string(n2)+ "->"+ to_string(n1)] = 0;
        // cout << edges[countEdges].name <<"\n";
        nodes[n1].adjecencyList.push_back(n2);
        nodes[n2].adjecencyList.push_back(n1);
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
  void modDFS(int node);

  void modifiedDFS();
  void printResults();
};

#endif
