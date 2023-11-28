#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

struct TreeNode{
  int value;		// value
  TreeNode *left;	// Left Child of this Node (NULL, if None)
  TreeNode *right;	// Right Child of this Node (NULL, if None)
  TreeNode *parent;	// The Parent Node, NULL in case of Root
  // Constructors
  TreeNode() : value(0), left(nullptr), right(nullptr) {}
  TreeNode(int jrnyvalue) : value(jrnyvalue), left(nullptr), right(nullptr) {}
  TreeNode(int jrnyvalue, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : value(jrnyvalue), left(leftChild), right(rightChild), parent(parent) {}
};

class BST {
  public:
  TreeNode *root;
  BST(){ this->root=nullptr; }
  BST(TreeNode *root){ this->root=root; }
  
  bool insert(int value) {
    TreeNode * z = new TreeNode(value);
    TreeNode * y = nullptr;
    TreeNode * x = root;
    while(x!=nullptr){
      y = x;
      if( x->value <= value) x = x->right;
      else x = x->left;
    }
    z->parent = y;
    if( y == nullptr) {
      root = z;
    }
    else if( y->value <= value) y->right = z;
      else y->left = z;
    return true;
  }

  // printBST function used earlier
  void printBST(const string& prefix, bool isLeft=false){
    if( root != nullptr ){
      cout << prefix;
      
      cout << (isLeft ? "|--" : "|__" );

      // print the value of the node
      cout << root->value << endl;
      TreeNode *curr = root;
      // enter the next tree level - left and right branch
      root = curr->left;
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
  int *adjlist;
  // constructor
  Node(){
    value = -1;
    adjlist = new int[19];
    for (int i = 0; i < 19; i++) {
      adjlist[i] = -1;
    }   
  }
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;
  Node *nodes;
  int numComp;
  BST *Comp = new BST[numNodes];
  int *a;
  int *b;
  int *c;
  int *visited;
  
 public:
  //constructor
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
    visited = new int[numNodes];
    a = new int[numNodes];
    b = new int[numNodes];
    c = new int[numNodes];
    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }
    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
      visited[i] = 0;
      a[i] = 0;
      b[i] = 0;
      c[i] = 0;
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
      
      int a = 0;
      int found = 0;
      while(nodes[n1].adjlist[a] > -1){
        if(nodes[n1].adjlist[a] == n2){
          found = 1;
          break;
        }
        a++;
      }
      nodes[n1].adjlist[a] = n2;
      if(found == 1)continue;
      int b = 0;
      while(nodes[n2].adjlist[b] > -1){
        b++;
      }
      nodes[n2].adjlist[b] = n1;
      graphFile << n1+1 << " " << n2+1 << endl;
      countEdges++;
    }
    
    numComp = 0;
  }
      
  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;
    delete[] Comp;
  }

  void DFS(int p, Node n, BST &b);
  void modifiedDFS();
  void printResults();
};

#endif