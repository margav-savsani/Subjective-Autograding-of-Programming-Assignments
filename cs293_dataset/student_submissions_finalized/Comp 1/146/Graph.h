#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

struct BSTNode {
  int vertex; //The value of the vertex

  // The nodes contained 
  BSTNode* left;
  BSTNode* right;
  BSTNode* parent;

  //Two constructors
  BSTNode() : vertex(0), left(NULL), right(NULL), parent(NULL) {}
  BSTNode(int vert) : vertex(vert), left(NULL), right(NULL), parent(NULL) {}
};

class BST {

  BSTNode* root; // The root

  

public: 

  BST() :  root(NULL) {}
  void insert(int val);
  void insert(int val, BSTNode* top);
  void printBST(const string& prefix, bool isLeft);
  

};

// SinglyLinkedList
template <typename T>
struct SLL {
  T v;
  SLL* next;
  SLL(T u): v(u), next(NULL) {}
  
};

class Node {
 public:
  int value;
  int numVisited;
  SLL<int>* currParents;
  bool isInCycle;
  bool inCall; //To indicate the time period where the recursive call of this node is still running 
  SLL<int>* adjList;

  Node(): value(0), adjList(NULL), numVisited(0), isInCycle(false), inCall(false) {}

};



class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;
  SLL<BST*>* BSTList;
  Node *nodes;
  int numConnectedComponents;

  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    BSTList = NULL;
    numConnectedComponents = 0;
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
      } while (n1 == n2);

      bool isEdgePresent=false;

      SLL<int>* temp = nodes[n1].adjList;
      while(temp != NULL){
        if(temp->v == n2+1) isEdgePresent = true;

        temp = temp->next;
      }
      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile
      if(isEdgePresent) continue;

      if(nodes[n1].adjList == NULL){
        nodes[n1].adjList = new SLL<int>(n2+1);
      }
      else {
        SLL<int>* temp = nodes[n1].adjList;
        while(temp->next != NULL){
          temp = temp->next;
        }
        temp->next = new SLL<int>(n2+1);
      }


      if(nodes[n2].adjList == NULL){
        nodes[n2].adjList = new SLL<int>(n1+1);
      }
      else {
        SLL<int>* temp = nodes[n2].adjList;
        while(temp->next != NULL){
          temp = temp->next;
        }
        temp->next = new SLL<int>(n1+1);
      }



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
    // Add appropriate code as necessary for your implementation
  }

  // Add appropriate method declarations as necessary for your implementation

  void modifiedDFS();
  void modifiedRecDFS(Node* v,int pv, BST* tree); // For recurrsive call 
  void printResults();
};

#endif
