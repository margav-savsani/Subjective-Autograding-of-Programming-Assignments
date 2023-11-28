#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <stdio.h>
#include <stdlib.h>
using namespace std;

class BSTNode {
 public:
  int value;

  // insert other fields and methods as appropriate
  BSTNode* left;
  BSTNode* right;
  BSTNode* parent;

  BSTNode(int val){
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    value = val;
  }

};

template <typename T> class NewVector{
  T* array;
  int cap;

public:
  NewVector(){
    array = nullptr;
    cap = 0;
  }
  void push_back(T val){
    if(cap==0){
      array = new T[1];
      array[0] = val;
      cap = 1;
      return;
    }
    else{
      cap++;
      array = (T*) realloc(array, cap*sizeof(T));
      array[cap-1] = val;
      return;
    }
  }
  T pop(){
    if(cap==0) return nullptr;
    else if(cap == 1){
      cap = 0;
      array = nullptr;
    }
    else{
      T store = array[cap - 1];
      cap--;
      array = (T*) realloc(array, cap*sizeof(T));
      return store;
    }
    return nullptr;;
  }

  T return_max(){
    return array[cap-1];
  }
  int vector_size(){
    return cap;
  }
  T get_value_at_index(int val){
    if(0 <= val && val < cap) return array[val];
    else return nullptr;
  }
  int get_index_of_value(T val){
    for(int i = 0; i<cap; i++) if(array[i]==val) return i;
    return -1;
  }
};

class BST {
  // Add your own field and members here
  BSTNode* root;
public:
  BST(){root = nullptr;}
  BST(int val){root = new BSTNode(val);}

  void insert(int val){
    BSTNode *ins_l = root;
    BSTNode *ins_r = nullptr;
    
    while(ins_l!=nullptr){
      ins_r = ins_l;
      if(val < ins_l->value) ins_l = ins_l->left;
      else ins_l = ins_l->right;
    }

    if(ins_r==nullptr){
      root = new BSTNode(val);
    }
    else{
      if(val < ins_r->value){
        ins_r->left = new BSTNode(val);
        ins_r->left->parent = ins_r;
      }
      else{
        ins_r->right = new BSTNode(val);
        ins_r->right->parent = ins_r;
      }
    }
  }

  void printBST(const string& prefix, bool isLeft=false){
    if(root != nullptr){
      cout << prefix << (isLeft ? "|--" : "|__" );
      cout << root->value << endl;
      BSTNode *curr = root;
      root = root->left;
      printBST(prefix + (isLeft ? "│   " : "    "), true);
      root = curr->right;
      printBST(prefix + (isLeft ? "│   " : "    "), false);
      root = curr;
    }
  }
  // Feel free to use the printBST function used earlier
};

class Node {
 public:
  int value;

  // insert other fields and methods as appropriate
  NewVector<Node*> adj;
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;
  NewVector<BST*> main_tree;
  int* visited;

  // Add appropriate fields as necessary for your implementation
  
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

      bool tmp1 = false, tmp2 = false;
      if(nodes[n1].adj.get_index_of_value(&nodes[n2]) == -1){
        nodes[n1].adj.push_back(&nodes[n2]);
        tmp1 = true;
      }
      if(nodes[n2].adj.get_index_of_value(&nodes[n1]) == -1){
        nodes[n2].adj.push_back(&nodes[n1]);
        tmp2 = true;
      }

      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile
      if(tmp1 == false && tmp2 == false) continue;
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
  void printResults();
};

#endif
