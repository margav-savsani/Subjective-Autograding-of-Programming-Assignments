#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

class adjList{
  public:
    int object;
    adjList *next;

    adjList(int node){
      object = node;
      next = nullptr;
    }

    ~adjList() {;}
};

class Node{
 public:
  int value;
  adjList *adjacency;
  Node* parent;
  Node* leftChild;
  Node* rightChild;
};

void printBinaryTree(Node *root, const string& prefix, bool isLeft)
{
  if( root != nullptr )   {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    cout << root->value << endl;
    cout << endl;
    Node *curr = root;
    root = root->leftChild;
    // enter the next tree level - left and right branch
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->rightChild;
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
  else {
    cout << "NULL tree" << endl;
  }
}

class BST {
  private:
  Node *root;
  void recursiveDelete(Node *currNode) {
    if (currNode != nullptr) {
      Node *leftChild = currNode->leftChild;
      Node *rightChild = currNode->rightChild;
    
      delete currNode;
      recursiveDelete(leftChild);
      recursiveDelete(rightChild);
    }
    return;
  }

  public:

    BST(Node *newRoot){
      root = newRoot;
    }

    ~BST(){
      recursiveDelete(root);
    }
    
    bool insert(int val){
      try {
        if (root == nullptr){
          root->value = val;
          root->leftChild = nullptr;
          root->parent = nullptr;
          root->rightChild = nullptr;
          throw 1;
        }
        else {
          Node *z, *x, *y;
          x = root;
          y = nullptr;
          z->value = val;
          z->leftChild = nullptr;
          z->parent = nullptr;
          z->rightChild = nullptr;
          while(x != nullptr){
            y = x;
            if(z->value <= x->value){
              x = x->leftChild;
            }
            else if(z->value > x->value){
              x = x->rightChild;
            }
          }
          if (z->value > y->value){
            y->leftChild = z;
            z->parent = y;
            throw 1;
          }
        }
      }
      catch (int){ return true; }
      return false;
    }
  // Add your own field and members here
  void print() { printBinaryTree(root, "", false);}
  // Feel free to use the printBST function used earlier
};



class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;
  Node *nodes;

  // Add appropriate fields as necessary for your implementation
  
 public:
  int time2 = 0;
  int time1 = 0;
  adjList *connComp_num;
  int connComp_number;
  int *visited, *visited1, *i, *t1, *t2, *t3, *a, *d;
  BST **BSTree;
  int *numNod;

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
    visited1 = new int[numNodes];
    t1 = new int[numNodes];
    t2 = new int[numNodes];
    t3 = new int[numNodes];
    a = new int[numNodes];
    d = new int[numNodes];
    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
      nodes[i].adjacency = nullptr;
      visited[i] = 0;
      visited1[i] = 0;
      t1[i] = -1;
      t2[i] = -1;
      t3[i] = -1;
      a[i] = -1;
      d[i] = -1;
    }

    srand(time(0));
    int n1, n2;
    int countEdges = 0;
    
    while (countEdges < numEdges) {
      do {
	n1 = rand() % numNodes;
	n2 = rand() % numNodes;
      } while (n1 == n2);

    
      adjList *f = nodes[n1].adjacency;
      bool notpresent = true;
      while( (f != nullptr) && notpresent ){
        if (f->object == nodes[n2].value) { notpresent = false; }
        else { f = f->next; }
      }
      if (notpresent){
        adjList *in = nodes[n1].adjacency, *in1 = nodes[n2].adjacency;
        while( in != nullptr ){
          in = in->next;
        }
        in = new adjList(n2) ;
        while( in1 != nullptr ){
          in1 = in1->next;
        }
        in1 = new adjList(n1);
      }
      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile

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
  void connectedComp();
  void DFS(int i);
  void DFS2(int i, int j);
  void modifiedDFS();
  void printResults();
};

#endif
