#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include<string>
//Declaration to avoid compilation errors
class Node;

//Represent the nodes adjacent to a node in the graph
class AdjacencyList {
  public:
    Node* node;
    AdjacencyList* next;
    AdjacencyList(Node *s) : node(s), next(nullptr) {};
    AdjacencyList(Node *s, AdjacencyList *n) : node(s) , next(n) {};
};

//Represents node of a graph
class Node {
 public:
  //Value renamed to price to match with BST node
  int price;

  //Node as a Graph Node variables
  AdjacencyList *adjList;
  int visisted_times = 0;
  int nParents = 0;
  Node *parent1 = nullptr;
  Node *parent2 = nullptr;
  int currPath = 0;
  bool isCyclic = false;

  Node() : price(0), adjList(nullptr) {};
  Node(int jrnyPrice) : price(jrnyPrice), adjList(nullptr) {};
  Node(int jrnyPrice, Node *leftChild, Node *rightChild, Node *parent) : price(jrnyPrice), adjList(nullptr) {};
};

//Represents node of a Binary Search Tree
class BSTNode{
  public:
    int price;
    BSTNode *left;
    BSTNode *right;
    BSTNode *parent;
  
    BSTNode(int p):price(p), left(nullptr) , right(nullptr) , parent(nullptr) {};
};

//Represents a Binary Search Tree
class BST {
  public:
  BSTNode *root;
  BST(): root(nullptr){};
  BST(BSTNode *root);

  //Insert function into the BST  
  bool insert(int price){
    if ( root == nullptr ){
      root = new BSTNode(price);
      return true;
    }
    BSTNode *inserter = root;
    while(true){
      if ( price > inserter->price ){
        if ( inserter->right == nullptr ){
          inserter->right = new BSTNode(price);
          inserter->right->parent = inserter;
          break;
        }
        else{inserter = inserter->right;}
      }
      else {
        if ( inserter->left == nullptr ){
          inserter->left = new BSTNode(price);
          inserter->left->parent = inserter;
          break;
        }
        else{inserter = inserter->left;}
      }
    }
    return true;
  };

  void printBST(const string& prefix, bool isLeft=false);
  // Feel free to use the printBST function used earlier
};

//Insert function is used to insert a node into the adjacency list of the source node
bool Insert(Node *source, Node *adj){
  if ( source->adjList == nullptr ){
    source->adjList = new AdjacencyList(adj);
    return true;
  }
  else{
    AdjacencyList* prev = source->adjList;
    AdjacencyList* ahead = source->adjList->next;
    while(ahead!=nullptr){
      prev = ahead;
      ahead = ahead->next;
    }
    prev->next = new AdjacencyList(adj);
    return true;
  }
  return false;
}

//Represents a node of linked list containing pointer to a node of graph
class IntNode{
  public:
  Node* value;
  IntNode *next;
  IntNode *prev;
  IntNode(Node* vae) : value(vae), next(nullptr) , prev(nullptr){};
  IntNode(Node* vae, IntNode * n, IntNode * p) : value(vae) , next(n) , prev(p) {};
};

//Represents a linked list of IntNode
class IntNodeList{
  public:
  IntNode *root;
  IntNode *last;
  IntNodeList(Node *value){
    Insert(value);
  }
  void Insert(Node* value){
    if ( root == nullptr ){
      root = new IntNode(value);
      last = root;
    }
    else{
      last->next = new IntNode(value, nullptr, last);
      last = last->next;
    }
  };
  void Delete(){
    if (last->prev == nullptr ){
      root = nullptr;
      last = nullptr;
    }
    else{
      last = last->prev;
      last->next = nullptr;
    }
  }
  void Print(){
    IntNode * iter = root;
    while (iter!=nullptr ){
      cout << iter->value->price << "-" ;
      iter = iter->next;
    }
    cout << endl;
  }
};

//Represents Graph
class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;
  //Like adjacencyMatrix, so that whethere two nodes are adj can be found out really quickly
  bool **adjacencyLists;

  // Add appropriate fields as necessary for your implementation
  int connectedComponents;
  int visitOnceNodes;
  int visitTwiceNodes;
  int cyclicNodes;
  BST* Trees;

 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    connectedComponents = 0;
    visitOnceNodes = 0;
    visitTwiceNodes = 0;
    cyclicNodes = 0;
    Trees = new BST [nNodes];
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
      nodes[i].price = i+1;
    }
    adjacencyLists = new bool*[numNodes];
    
    for ( int i = 0 ; i < numNodes ; i++ ){
      adjacencyLists[i] = new bool[numNodes];
    }

    srand(0);
    int n1, n2;
    int countEdges = 0;
    
    while (countEdges < numEdges) {
      do {
	n1 = rand() % numNodes;
	n2 = rand() % numNodes;
      } while (n1 == n2);

      //Case to not crete an edge
      if(adjacencyLists[n1][n2]){
        continue;
      }

      //Case to create an edge
      adjacencyLists[n1][n2] = 1;
      adjacencyLists[n2][n1] = 1;
      
      //Insert functions for linked list
      Insert(&nodes[n1], &nodes[n2]);
      Insert(&nodes[n2], &nodes[n1]);

      graphFile << n1+1 << " " << n2+1 << endl;
      countEdges++;
    }

    // Add appropriate code as necessary for your implementation
  }
      
  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;
    for ( int i = 0 ; i  < numNodes ; i++ ){
      delete[] adjacencyLists[i];
    }
    // Add appropriate code as necessary for your implementation
  }

  // Add appropriate method declarations as necessary for your implementation

  void modifiedDFS();
  void printResults();
  void DFS(Node *source, Node *parent , BST *component, IntNodeList *currlist);
};

#endif
