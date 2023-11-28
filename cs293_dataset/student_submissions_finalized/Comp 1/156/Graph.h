#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

template <typename T> class listOfObjects {
 public:
  T object;
  listOfObjects<T> *next;
  
  // Constructor
  listOfObjects(T initValue) {object = initValue; next = nullptr;}
  
  // Destructor
  ~listOfObjects() {;}
};

struct DFSEdge{
  int from;
  int to;

  DFSEdge(){
    from = -1;
    to = -1;
  }

  void set(int from, int to){
    this->from = from;
    this->to = to;
  }
};

class BSTNode {
  public:
    int value;
    BSTNode *left;
    BSTNode *right;
    BSTNode *parent;

  BSTNode(){
    value = 0;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
  }

  BSTNode(int value){
    this->value = value;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
  }

  BSTNode(int value, BSTNode *left, BSTNode *right, BSTNode *parent){
    this->value = value;
    this->left = left;
    this->right = right;
    this->parent = parent;
  }
};

class BST {
  // Add your own field and members here
  BSTNode *root;
  //number of entries added 
  int N;
  // Feel free to use the printBST function used earlier

public:
  
  BST(){
    root = nullptr;
    N=0;  
  }
  
  BST(BSTNode *root){
    this->root=root;
    N=1;
  }

  bool insert(int value){
    if(N==0){
        root = new BSTNode(value);
        N++;
    }
    else{
        BSTNode *x;
        BSTNode *y;
        x = root;
        y = nullptr;
        while(x!=nullptr){
            y = x;
            if(value>y->value){
                x = x->right;
            }
            else{
                x = x->left;
            }
        }
        if(value > (y->value)){
            //need to pass y as well else how would you access parent of a child in remove function!!!
            //not setting parent here was giving segfault while running delete function 
            //that took me 3 hrs to debug :)
            y->right = new BSTNode(value,nullptr,nullptr,y);
        }
        else{
            y->left = new BSTNode(value,nullptr,nullptr,y);
        }
    }
    return true;
  }

  // Adapted from Adrian Schneider's code on StackOverflow
  void printBST(const string& prefix, bool isLeft=false)
  {
    if(root != nullptr )
    {
      cout << prefix;
      cout << (isLeft ? "|--" : "|__" );
      // print the value of the node
      cout << root->value << endl;
      BSTNode *curr = root;
      root = root->left;
      // enter the next tree level - left and right branch
      printBST( prefix + (isLeft ? "│   " : "    "), true);
      root = curr->right;
      printBST( prefix + (isLeft ? "│   " : "    "), false);
      root = curr;
    }
  }
};

class Node {
 public:
  int value;
  int visited;
  bool backtracked;
  int num_adj;
  listOfObjects<Node> *adj;
  listOfObjects<Node> *DFS_Parent;

  Node(){
    value = 0;
    visited = 0;
    num_adj = 0;
    adj = nullptr;
    DFS_Parent = nullptr;
    backtracked = false;
  }

  void add_to_adj(Node adj_node){
    if(adj==nullptr){
      adj = new listOfObjects<Node>(adj_node);
    }
    else{
      listOfObjects<Node> *x = adj;
      while(x->next!=nullptr){
        x = x->next;
      }
      x->next = new listOfObjects<Node>(adj_node);
    }
    num_adj++;
  }
};

class Graph {
  int numNodes;
  int numEdges;
  int numConnected;
  int numNodesInCycle;
  int numVisitedOnce;
  int numVisitedTwice;
  fstream graphFile;

  Node *nodes;
  Node *parent;
  listOfObjects<BST> *Trees;

 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numConnected = 0;
    numVisitedOnce = 0;
    numVisitedTwice = 0;
    numNodesInCycle = 0;
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

      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile

      // A modification that can be made here is that check which of n1 and n2 have
      // lower num_adj and run this loop on that node
      // also check that countEdges is less than the maximum number of edges possible 
      bool already_present = false;
      listOfObjects<Node> *x = nodes[n1].adj;

      while(x!=nullptr){
        if(x->object.value == nodes[n2].value){
          already_present = true;
          break;
        }
        x = x->next;
      }

      if(!already_present){
        nodes[n1].add_to_adj(nodes[n2]);
        nodes[n2].add_to_adj(nodes[n1]);
        graphFile << n1+1 << " " << n2+1 << endl;
        countEdges++;
      }
    }
  }
      
  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;
    // Add appropriate code as necessary for your implementation
  }

  // Add appropriate method declarations as necessary for your implementation
  void DFSConnected(Node &node, listOfObjects<DFSEdge> *EdgeList, BST *tree);
  void modifiedDFS();
  void printResults();

};

#endif
