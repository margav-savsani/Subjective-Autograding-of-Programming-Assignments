#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include<vector>
using namespace std;

class Treenode{
  public:
  int value;
  Treenode*left=NULL;
  Treenode*right=NULL;
  Treenode(int v){
    value=v;
  }
};


class BST {
  public:
  Treenode* root=NULL;
  void insert(int a){
    if(root==NULL){
      root=new Treenode(a);
      return;}
    Treenode*curr=root;
    while(true){
      if(a>=curr->value){
        if(curr->right==NULL){
          curr->right=new Treenode(a);
          break;}
        else curr=curr->right;
      }
      else{
        if(curr->left==NULL){
          curr->left=new Treenode(a);
          break;}
        else curr=curr->left;
      }
    }
  }
  void printBST(const string& prefix, bool isLeft=false)
 {
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->value << endl;
        Treenode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "|   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "|   " : "    "), false);
        root = curr;
    }
}
};


class list{
  public:
  int value;
  list* next;
  list(int v){
    value=v;
    next=NULL;
  }
};
class Node {
 public:
  int value;
  list* edge=NULL;
  // insert other fields and methods as appropriate
};

class Graph {
  int numNodes;
  int numEdges;
  int* visit;
  fstream graphFile;
  int cyclenodes=0;
  int once=0;
  int twice=0;
  int conncomp=0;
  bool* cycle;
  vector<BST> bst;
  Node *nodes;

  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    visit=new int[nNodes];
    for(int i=0;i<numNodes;i++)visit[i]=0;

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
      bool exists =false;
      list* e=nodes[n1].edge;
      while(e!=NULL){
        if(e->value==n2+1)exists=true;
        e=e->next;
      }
      if(exists)continue;
      
      list* n1e=new list(n2+1);
      n1e->next=nodes[n1].edge;
      nodes[n1].edge=n1e;
      list * n2e=new list(n1+1);
      n2e->next=nodes[n2].edge;
      nodes[n2].edge=n2e;
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
  void DFSpart2(int a);
  void printResults();
};

#endif
