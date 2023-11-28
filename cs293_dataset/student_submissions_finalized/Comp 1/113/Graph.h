#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

struct DLLNode{
  int value;
  DLLNode *prev;
  DLLNode *next; 
  DLLNode(int v){
    value = v;
    prev = nullptr;
    next = nullptr;
  }
};


class DLL{
  public:
  DLLNode *head;
  DLLNode *tail;
  
    DLL(){
      head = nullptr;
      tail = nullptr;
    }
    void insert(int x){
      DLLNode *node = new DLLNode(x);
      if (head == nullptr){
        head = new DLLNode(x);
        tail = head;
        return;
      }
      DLLNode *tailtemp=tail;
      tail = new DLLNode(x);
      tailtemp->next = tail;
      tail->prev = tailtemp;
    }

    void pop(){
      if (tail->prev){
        DLLNode *d=tail;
        tail = tail->prev;
        tail->next=nullptr;
        delete d;
      }
      else{
        delete tail;
        tail=nullptr;
        head=nullptr;
      }
    }

    bool next(int x, int y){
      DLLNode *d = tail;
      while (d != nullptr){
        if (d->value == x){
          if (d->next){
            if (d->next->value == y){
              return true;
            }
          }
        }
        d = d->prev;
      }
      return false;
    }

    bool isin(int x){
      DLLNode *d = head;
      while (d != nullptr){
        if (d->value == x){
          return true;
        }
        d = d->next;
      }
      return false;
    }

    DLLNode * getptr(int x){
      DLLNode *d = tail;
      while (d != nullptr){
        if (d->value == x){
          return d;
        }
        d = d->prev;
      }
      return nullptr;
    }

};

class BST {
  // Add your own field and members here
  public:
    int value;
    BST *left;
    BST *right;
    BST *parent;

    BST(int value) : value(value) {
      // value = v;
      left = nullptr;
      right = nullptr;
      parent = nullptr;
    }

    void insert(int x){
      if (x > value){
        if (right){
          right->insert(x);
        }
        else{
          right = new BST(x);
          right->parent = this;
        }
      }
      else{
        if (left){
          left->insert(x);
        }
        else{
          left = new BST(x);
          left->parent = this;
        }
      }
      return;
    }

    void printBST(const string& prefix, bool isLeft = false){
      cout << prefix;

      cout << (isLeft ? "|--" : "|__" );

      // print the value of the node
      cout << value << endl;
      
      // enter the next tree level - left and right branch
      if (left != nullptr){
        left->printBST( prefix + (isLeft ? "│   " : "    "), true);
      }
      if (right != nullptr){
        right->printBST( prefix + (isLeft ? "│   " : "    "), false);
      }
      return;
    }
  // Feel free to use the printBST function used earlier
};

class Node {
 public:
  int value;
  DLL adjacent;
  Node(){
    value = -1;
  }
  Node(int x){
    value = x;
  }

  bool addEdge(int x){
    if (adjacent.isin(x)){
      return false;
    }
    adjacent.insert(x);
    return true;
  }
  // insert other fields and methods as appropriate
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;
  int *visited;
  bool *incycle;
  int *parent;
  char *color;
  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    visited = new int[numNodes];
    incycle = new bool[numNodes];
    parent = new int[numNodes];
    color = new char[numNodes];

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
      color[i]='w';
      visited[i] = 0;
      incycle[i] = false;
      parent[i] = 0;
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
      if (!nodes[n1].addEdge(n2+1)){
        continue;
      }
      else{
        nodes[n2].addEdge(n1+1);
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
    delete[] visited;
    // Add appropriate code as necessary for your implementation
  }

  // Add appropriate method declarations as necessary for your implementation
  void doDFS(int x,BST *b);
  void DoDFS(int x);
  void modifiedDFS();
  void printResults();
};

#endif
