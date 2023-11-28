#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

class TreeNode {        // TreeNode class for BST node
public:
  int value;
  TreeNode * left;
  TreeNode * right;
  TreeNode * parent;

  TreeNode(int value = 0){
    this->value = value;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
  }
};

template <typename T> class list {
public:
  T val;
  list<T>* next;
  list(T val){
    this->val = val;
    this->next = nullptr;
  }
  list(){
    this->next = nullptr;
  }
};

class Stack{
public:
  int * node;           // storing the nodes
  int * first;          // index of first occurence of element; -1 if not present
  int * second;         // index of second occurence of element; -1 if not present
  list<int>** next;     // list of adjacent nodes that have to be visited
  int N;                // number of nodes in graph
  int n;                // current size of the Stack

  Stack(int num){         // constructor
    node = new int [2*num];
    first = new int [num];
    second = new int [num];
    next = new list<int>* [2*num];
    this->N = num;
    int n = 0;
    for (int i = 0; i < N; i++){
      node[2*i] = -1;
      node[2*i+1] = -1;
      next[2*i] = nullptr;
      next[2*i+1] = nullptr;
      first[i] = -1;
      second[i] = -1;
    }
  }

  bool insert(int I, list<int>* p){     // inserting into the Stack
    if (n == 2*N){
      cout << "Some error occured" << endl;
      return 0;
    }
    node[n] = I;
    next[n] = p;
    if (first[I] >= 0){
      second[I] = this->n;
    }
    else {
      first[I] = this->n;
    }
    this->n++;
    return 1;
  }

  bool pop(){     // pops the to of the Stack
    if (n == 0){
      return 0;
    }
    int k = node[n-1];
    node[n-1] = 0;
    if (second[k] >= 0){
      second[k] = -1;
    }
    else if (first[k] >= 0){
      first[k] = -1;
    }
    next[n-1] = nullptr;
    this->n--;
    return 1;
  }

  int instack(int I) {      // check whether the node is in Stack; returns the number of instances
    if (first[I] == -1){
      return 0;
    }
    else if (second[I] == -1){
      return 1;
    }
    return 2;
  }

  bool isempty(){   // checks whether the Stack is empty
    if (n > 0){
      return 0;
    }
    return 1;
  }

  ~Stack(){
    delete[] node;
    delete[] first;
    delete[] second;
    delete[] next;
  }
};

class BST {
public:
  TreeNode * root;
  BST(){
    root = nullptr;
  }
  
  bool insert(int val){
    if (root == nullptr){
      root = new TreeNode(val);
      return 1;
    }
    TreeNode * T = root;
    while (true){
      if (T->value >= val){
        if (T->left == nullptr){
          T->left = new TreeNode(val);
          T->left->parent = T;
          return 1;
        }
        T = T->left;
        continue;
      }
      else if (T->value < val){
        if (T->right == nullptr){
          T->right = new TreeNode(val);
          T->right->parent = T;
          return 1;
        }
        T = T->right;
        continue;
      }
    }
    return 0;
  }

  void printBST(const string& prefix, bool isLeft=false){
    if( root != nullptr ){
      cout << prefix;

      cout << (isLeft ? "|--" : "|__" );
      cout << root->value << endl;
      TreeNode *curr = root;
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
  list<int> * L;      // list of adjacent nodes
  
  Node(int value = 0){
    this->value = value;
    this->L = nullptr;
  }

  bool insert(int k){     // inserting to the list of adjacent nodes
    list<int> * l = this->L;

    while(l != nullptr){
      if (l->val == k){
        return 0;
      }
      l = l->next;
    }
    l = new list<int>(k);
    l->next = this->L;
    this->L = l;
    return 1;
  }

  ~Node(){
    while(L != nullptr){
      list<int> * l = L;
      L = L->next;
      delete l;
    }
  }
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;
  list<BST> * BSTlist;    // linked list of BSTs
  Node * nodes;           // nodes in the Graph
  int * parent1;          // parent node
  int * parent2;          // parent2 is the parent in the second trip 
  Stack * S;              // Stack to implement modified DFS
  int num_connected;      // number of connected components
  int visit2;             // number of nodes visited twice
  int cycles;             // number of nodes that are part of a cycle 
  bool * is_incycle;      // bool array of nodes that are part of cycle
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    parent1 = new int [numNodes];
    parent2 = new int [numNodes];
    is_incycle = new bool [numNodes];
    num_connected = 0; visit2 = 0; cycles = 0;
    S = new Stack(numNodes);
    for (int i = 0; i < numNodes; i++){
      parent1[i] = -1;
      parent2[i] = -1;
      is_incycle[i] = 0;
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
      if (nodes[n1].insert(n2) && nodes[n2].insert(n1)){
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
    delete S;
    delete[] parent1;
    delete[] parent2;
    delete[] is_incycle;
    list<BST> * B = BSTlist;
    while (B != nullptr){
      B = B->next;
      delete BSTlist;
      BSTlist = B;
    }
  }

  // Add appropriate method declarations as necessary for your implementation

  void modifiedDFS();
  void printResults();
  void resetVisits();
};

#endif
