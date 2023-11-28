#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;


class BST {
  // Add your own field and members here
  public:
    int key;
    BST *left;
    BST *right;

  //Default Constructor and parametrised with key of root
  BST(){
    key = 0;
    left = NULL;
    right = NULL;
  };
  BST(int k){
    key = k;
    left = NULL;
    right = NULL;
  };

  //insert function to bst with arguments tree and value key
  BST* BSTInsert(BST *t , int k ){
    if(!t){
      // cout<<"0"<<endl;
      return new BST(k);
    }
    
      if (t->key >= k){
        // cout<<"hi"<<endl;
        t->left = BSTInsert(t->left , k);
      }
      else if(t->key < k){
        // cout<<"by"<<endl;
        t->right = BSTInsert(t->right,k);
      }
    return t;
  }

  // "--"means to left and "__" means to right of node in bst
  void BSTPrint(BST *t ,const string& prefix,bool isLeft=false){
    if( t != nullptr )
    { 
        cout<<prefix;
        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << t->key << endl;
        BST *curr = t;
        t = t->left;
        // enter the next tree level - left and right branches
        BSTPrint(t, prefix + (isLeft ? "│   " : "    "), true);
        t = curr->right;
        BSTPrint(t, prefix +(isLeft ? "│   " : "    "), false);
        t = curr;
    }
  }

// Feel free to use the printBST function used earlier
};

class Node {
 public:
  int value;
  // insert other fields and methods as appropriate for graphs
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;
  int *adjmat;
  int *visited;
  int *color;
  int *parentmat;
  int *parentcyc;
  
  
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

    adjmat = new int[nNodes*nNodes];
    visited = new int[nNodes];
    color = new int[nNodes];
    parentmat = new int[nNodes*nNodes];
    parentcyc = new int[nNodes*nNodes];
    for (int i=0;i<numNodes;i++){
      visited[i] = 0;
      color[i] = 0;
    }
    for (int i = 0; i < nNodes; i++) {
      for (int j = 0; j < nNodes; j++) {
          *(adjmat + i * nNodes + j) = 0;
          *(parentmat + i * nNodes + j) = 0;
          *(parentcyc + i * nNodes + j) = 0;
      }
    }
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

      if(*(adjmat + n1 * nNodes + n2) == 0){
        *(adjmat + n1 * nNodes + n2) = 1;
        *(adjmat + n2 * nNodes + n1) = 1;

        graphFile << n1+1 << " " << n2+1 << endl;
        countEdges++;}
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
  int func(int ind,int indnew,int& num);
  void DFS(int v,BST *t );
  void DFS_per_component(int c,Node*src);
  void modifiedDFS();
  void printResults();
};

#endif
