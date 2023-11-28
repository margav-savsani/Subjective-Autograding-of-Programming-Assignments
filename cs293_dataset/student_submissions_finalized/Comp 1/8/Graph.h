#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

class Node {
 public:
  int value;
  int visited;
  Node* parent;
  Node* left;
  Node* right; 

  Node(int value,Node* parent, Node* left, Node* right)
  {
    this->value = value;
    this->left = left;
    this->right = right;
    this->parent = parent;
  }

  Node(int value)
  {
    this->value = value;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
  }

  Node(){
    this->value = -1;
    this->visited = 0;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
  }
  // insert other fields and methods as appropriate
};

class BST {
  // Add your own field and members here
  public:
  BST(){
    root = nullptr;
  }


  Node* root;

  void insert(Node* node){
    if(root == nullptr){
      root = node;
    } 

    else{
      Node* ptr1 = root;
      Node* ptr2 = root;

      while (ptr1 != nullptr)
      {
        ptr2 = ptr1;
        if(ptr1 -> value > node -> value){
          ptr1 = ptr1 -> left;
        }

        else {
          ptr1 = ptr1 -> right;
        }
      }

      if (ptr2 -> value > node -> value)
      {
        ptr2 -> left = node;
      }

      else {
        ptr2 -> right = node;
      }
    }
  } 

  // Feel free to use the printBST function used earlier
};


class Graph {
  int numNodes;
  int numEdges;
  int** adj;
  fstream graphFile;
  int* visited;

  BST** treeList ;

  Node *nodes;

  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    visited = new int[numEdges];

    treeList = new BST*[numNodes];

    for(int i = 0; i < numEdges; i++){
      visited[i] = 0;
      treeList[i] = new BST();
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
      nodes[i].value = i;
    }

    srand(time(0));
    int n1, n2;
    int countEdges = 0;
  // adjacency list
    adj = new int*[numNodes];
    for (int i = 0; i < numNodes; i++){
      adj[i] = new int[numNodes];
    }

    for (int i = 0; i < numNodes; i++){
      for (int j = 0; j < numNodes; j++){
        adj[i][j] == 0;
      }
    }
    
    while (countEdges < numEdges) {
      // srand(69);
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

      adj[n1][n2] = 1;
      adj[n2][n1] = 1;

      graphFile << n1+1 << " " << n2+1 << endl;
      countEdges++;

    }

    // for (int i = 0; i < numNodes; i++){
    //   cout << i << "-";
    //   for (int j = 0; j < numNodes; j++){
    //     cout<< adj[i][j] << " ";
    //   }
    //   cout << endl;
    // }
    // Add appropriate code as necessary for your implementation
  }

  Node* getNode(int n){
    return &nodes[n]; 
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
  void printBinaryTree(Node *root, const string& prefix, bool isLeft);
  void printResults();
  void specialDFS(int node, BST* tree, int del= -1);
};

#endif
