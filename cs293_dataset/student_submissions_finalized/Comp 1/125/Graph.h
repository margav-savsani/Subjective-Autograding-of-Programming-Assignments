#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
struct TreeNode{
  int value;
  TreeNode *left;	// Left Child of this Node (NULL, if None)
  TreeNode *right;	// Right Child of this Node (NULL, if None)
  TreeNode *parent;	// The Parent Node, NULL in case of Root
  
  TreeNode() : value(0), left(nullptr), right(nullptr) {}
  TreeNode(int val) : value(val),  left(nullptr), right(nullptr) {}
  TreeNode(int val, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : value(val), left(leftChild), right(rightChild), parent(parent) {}    
};

class BST {
  public:
    TreeNode *root;
    bool insert(int val);
    bool find(int val);
    void printBST(const string& prefix, bool isLeft, fstream& graphFile);
    BST(){
      root = NULL;
    }
};

class Node;
class listOfNodes{
  public:
    bool allowed;
    listOfNodes* head;
    Node* node;
    listOfNodes* next;
    listOfNodes* prev;
    listOfNodes(Node* x, listOfNodes* hd){
      allowed = true;
      next = prev = NULL;
      head = hd;
      node = x;
    }
};

class Node {
 public:
  int value;
  listOfNodes* adjacent_edges;
  Node(){
    adjacent_edges = NULL;
  }
  bool insert(Node *x){
    if(adjacent_edges==NULL){
      adjacent_edges = new listOfNodes(x, NULL);
      adjacent_edges->head = new listOfNodes(x, NULL);
      return true;
    }
    listOfNodes* y = adjacent_edges->head;
    while(y!=NULL){
      if(y->node->value==x->value) return false;
      y = y->next;
    }
    adjacent_edges->next = new listOfNodes(x, adjacent_edges->head);
    adjacent_edges->next->prev = adjacent_edges;
    if(adjacent_edges->prev==NULL){
      adjacent_edges->head->next = adjacent_edges->next;
    }
    adjacent_edges = adjacent_edges->next;
    return true;
  }
  void del(int val){
    listOfNodes* x = adjacent_edges->head;
    while(x != NULL){
      if(x->node->value==val){
        x->allowed = false;
        break;
      }
      x = x->next;
    }
  }
};

class Graph {
  int numNodes;
  int numEdges;
  int* visited;
  int connectedComponents;
  int* one_visits;
  int* two_visits;
  BST* bst_roots;
  fstream graphFile;

  Node *nodes;
  
  public:
  Graph(int nNodes, int nEdges, string gFileName) {
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
      nodes[i].value = i;
    }

    visited = new int[numNodes];
    one_visits = new int[numNodes+1];
    two_visits = new int[numNodes+1];
    bst_roots = new BST[numNodes];

    srand(time(NULL));
    int n1, n2;
    int countEdges = 0;
    
    while (countEdges < numEdges) {
      do {
        n1 = rand() % numNodes;
        n2 = rand() % numNodes;
      } while (n1 == n2);

      if(!nodes[n1].insert(&nodes[n2])) continue;
      nodes[n2].insert(&nodes[n1]);
      graphFile << n1+1 << " " << n2+1 << endl;
      countEdges++;
    }
  }
      
  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;
    delete[] visited;
    delete[] one_visits;
    delete[] two_visits;
    delete[] bst_roots;
  }

  void modifiedDFS();
  void modDFS(Node *x, int previous, BST *bst);
  void printResults();
};

#endif
