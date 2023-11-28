#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif


// Template class to support list
template <typename T> class listOfObjects {
 public:
  T object;
  listOfObjects<T> *next;
  listOfObjects<T> *prev;
  listOfObjects(T initValue) {object = initValue; next = prev = nullptr;}
  ~listOfObjects() {;}
};


// Node for BST
class Treenode {
public:
  int nodeValue;
  Treenode *left;
  Treenode *right;
  Treenode *parent;
  Treenode(int nV){
    nodeValue = nV;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
  }
};


class BST {
  // Add your own field and members here
  Treenode *root;
public:
  void insert(int nV);
  void printBST(const string& prefix, bool isLeft);
  // Feel free to use the printBST function used earlier
  BST(){root = nullptr;}
};

class Node {
 public:
  int value;
  int idx;
  // index of its parent in the traversal
  int pindx;
  int cnt;
  // Whether the node is ina cycle
  bool inCycle;
  // Adjacency list of a node
  listOfObjects<Node> *adj;
  listOfObjects<Node> *tail;
  // insert other fields and methods as appropriate
  Node(){
    adj=nullptr;
    tail=nullptr;
  }
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;
  int coun;
  Node *nodes;
  // To keep track of number of times a node is visited
  int *visited;
  bool *cntvisit;
  // List of BST trees 
  listOfObjects<BST *> *bsl;

  // Add appropriate fields as necessary for your implementation
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    coun =0;
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
      nodes[i].idx = i;
      nodes[i].inCycle =false;
      nodes[i].pindx =-1;
      nodes[i].cnt =-1;
    }

    //visited array
    visited = new int[numNodes];
    for(int i=0; i < numNodes; i++){
      visited[i]=0;
    }
    cntvisit = new bool[numNodes];
    for(int i = 0; i < numNodes; i++){
      cntvisit[i] = false;
    }

    bsl = nullptr;
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

      //Adding an edge appropriately
      if(edgePresent(n1,n2))continue;
      addEdge(n1,n2);
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

  bool edgePresent(int n1, int n2);
  void removeEdge(int n1, int n2);
  void addEdge(int n1, int n2);
  void dfs(int n, BST *btree,int b);
  void modifiedDFS();
  void printResults();
};

#endif
