#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif


template <typename T> class listOfObjects {
 public:
  T object;
  listOfObjects<T> *next;
  listOfObjects<T> *prev;
  
  // Constructor
  listOfObjects(T initValue) {object = initValue; next = prev = nullptr;}
  
  // Destructor
  ~listOfObjects() {;}

};


class Node {
 public:
  int value;
  listOfObjects<Node*> *adjacencyList;
  Node* left;
  Node* right;
  Node* parent;

  //default constructor
  Node(){
    adjacencyList = nullptr;
    left = right = parent = nullptr;
  }
  Node(int value){
    this->value = value;
    adjacencyList = nullptr;
    left = right = parent = nullptr;
  }

  bool updateAdjList(Node* node){
    //returns true on successful addition
    //else returns false
    listOfObjects<Node*>* storeList = adjacencyList;
    listOfObjects<Node*>* lastNode = nullptr;
    bool edgeExists = false;
    while(adjacencyList != nullptr){
      if(adjacencyList->object->value == node->value){
        edgeExists = true;
        break;
      }
      lastNode = adjacencyList;
      adjacencyList = adjacencyList->next;
    }
    adjacencyList = storeList;
    if(!edgeExists){
        if(lastNode == nullptr){
        adjacencyList = new listOfObjects(node);
      }
      else{
        lastNode->next = new listOfObjects(node);
      }
      return true;
    }
    return false;
  }
  // insert other fields and methods as appropriate
};

class BST {
  // Add your own field and members here
  Node* root;
  // Feel free to use the printBST function used earlier
 public:
  BST(){
    root = nullptr;
  }
  bool insert(Node* node2b);
  void printBST(const string& prefix, bool isLeft);
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;
  int* visited;
  int* parentArray;
  int connectedComp;
  listOfObjects<BST*>* linkListOfBSTs;

  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    connectedComp = 0;    //updated on running modifiedBFS
    linkListOfBSTs = nullptr;

    graphFile.open(gFileName, ios::out);
    if (!graphFile.is_open()) {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }

    graphFile << numNodes << endl;
    graphFile << numEdges << endl;

    nodes = new Node[numNodes];
    visited = new int[numNodes];
    parentArray = new int[numNodes];

    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
      visited[i] = 0;
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
      
      bool edgeExists = !nodes[n1].updateAdjList(&nodes[n2]);
      if(!edgeExists){
        nodes[n2].updateAdjList(&nodes[n1]);
        graphFile << n1+1 << " " << n2+1 << endl;
        countEdges++;
      }
      if(countEdges == (numNodes*(numNodes-1))/2){
        break;
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
  void DFS(Node* node, BST* tree, int parent);
  void modifiedDFS();
  void printResults();
};

#endif
