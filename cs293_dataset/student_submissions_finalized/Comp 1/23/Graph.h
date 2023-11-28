#ifndef GRAPH_BST_H
#define GRAPH_BST_H
#ifndef STD_HEADERS_H
#include "std_headers.h"
#include <list>
#include <vector>
#include <algorithm>
using namespace std;
#endif
template <typename T> class listOfObjects {
 public:
  T object;
  listOfObjects<T> *next;
  listOfObjects<T> *prev;
  listOfObjects(T initValue) {object = initValue; next = prev = nullptr;}
  ~listOfObjects() {;}
};
struct TreeNode{
    int price;		
    TreeNode *left;	
    TreeNode *right;
    TreeNode *parent;
  
    TreeNode() : price(0),left(nullptr), right(nullptr) {}
    TreeNode(int jrnyPrice) : price(jrnyPrice), left(nullptr), right(nullptr) {}
    TreeNode(int jrnyPrice, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : price(jrnyPrice), left(leftChild), right(rightChild), parent(parent) {}
};
class BST {
  public:
  TreeNode *root;
  vector<string> result;
  BST(){ 
    root=NULL;
  }
  BST(TreeNode *root){
    this->root=root; 
  }
  void insert(int price) {
    TreeNode *y=NULL;
    TreeNode *x=root;
    TreeNode *z;
    z=new TreeNode();
    z->price=price;
    while(x!=NULL){
        y=x;
        if(price<x->price) x=x->left;
        else x=x->right;}
    z->parent=y;
    z->left=NULL;
    z->right=NULL;
    if(y==NULL) root=z;
    else if (z->price<y->price) y->left=z;
    else y->right=z;
    }
  void printBST(const string& prefix, bool isLeft=false)
{
    if( root != nullptr )
    {
      cout << prefix;
      cout << (isLeft ? "|--" : "|__" );
      cout << root->price << endl;
      TreeNode *curr = root;
      root = root->left;
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
  listOfObjects<int>* adjacentnodes;
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;

  // Add appropriate fields as necessary for your implementation
  
 public:
  int count = 1;
  int connected;
  int* visited;
  int* visited1;
  int* pathpattern[2];
  vector<BST*> trees;
  vector<int> cyclics;
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    visited = new int[numNodes];
    visited1 = new int[numNodes];
    pathpattern[0] = new int[numNodes];
    pathpattern[1] = new int[numNodes];
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
    bool exist = false;
    if(nodes[n1].adjacentnodes == NULL && nodes[n2].adjacentnodes == NULL){
      nodes[n1].adjacentnodes = new listOfObjects<int>(n2);
      nodes[n2].adjacentnodes = new listOfObjects<int>(n1);
      graphFile << n1+1 << " " << n2+1 << endl;
      countEdges++;
      continue;
    }
    if(nodes[n1].adjacentnodes == NULL ) nodes[n1].adjacentnodes = new listOfObjects<int>(n2);
    if( nodes[n2].adjacentnodes == NULL) nodes[n2].adjacentnodes = new listOfObjects<int>(n1);
    listOfObjects<int>* nex1 = nodes[n1].adjacentnodes;
    listOfObjects<int>* new1 = nex1; 
    listOfObjects<int>* nex2 = nodes[n2].adjacentnodes;
    listOfObjects<int>* new2 = nex2; 
    while(nex1 != NULL){
      if(nex1->object == n2) break;
      nex1 = nex1->next;
    }
    while(nex2 != NULL){
      if(nex2->object == n1) break;
      nex2 = nex2->next;
    }
    while(new1->next != NULL){
      new1 = new1->next;
    }
    while(new2->next != NULL){
      new2 = new2->next;
    }
    if(nex1 == NULL && nex2 == NULL){
      new1->next = new listOfObjects<int> (n2);
      new1->next->prev = new1;
      new2->next = new listOfObjects<int> (n1);
      new2->next->prev = new2;
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
  void DFS(Node a,BST* tree);
  void modifiedDFS();
  void printResults();
  void DFSnaive(Node a);
  int Cycles();
};

#endif
