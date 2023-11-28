#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include "vector"
using namespace std;
struct TreeNode{
    int val;	// Train Number
    TreeNode(int val){
      this->val= val;
      left = nullptr;
      right = nullptr;
      parent =nullptr;
    }
    TreeNode *left;	// Left Child of this Node (NULL, if None)
    TreeNode *right;	// Right Child of this Node (NULL, if None)
    TreeNode *parent;	// The Parent Node, NULL in case of Root
};

class BST {
  public:
TreeNode *root;
void printBST(const string &prefix, bool isLeft = false);
void insert(int alp);
};

  

class Node {
 public:
  int value;
  vector<int> adjacency;
  Node(){
    adjacency.resize(0);
  }
  // insert other fields and methods as appropriate
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;
  BST *tree;
  Node *nodes;
  
  // Add appropriate fields as necessary for your implementation
  
 public:
  int prints=0;
  int *visit_array;
  int node1;
  int node2;
  int node3=-1;
  int recursion =0;
  int cycle_length;
  bool cycle_found;
  vector<int>cycle;
  Graph(int nNodes, int nEdges, string gFileName) {
    
    numNodes = nNodes;
    numEdges = nEdges;
    srand(time(0));
    node1 = rand()%numNodes;
    node2 = node1;
    set_arr();
    
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
      nodes[i].adjacency.resize(0);
    }

    srand(time(0));
    int n1, n2;
    int countEdges = 0;
    
    while (countEdges < numEdges) {
      do {
  n1 = rand() % numNodes;

	n2 = rand() % numNodes;
      } 
      while (n1 == n2) ;
      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile
      int nos = nodes[n1].adjacency.size();
      bool present = false;
      for(int j =0;j<nos;j++){
          if(nodes[n1].adjacency[j] == n2+1){
            present = true;
            break;
          }
      }
        
     
      if(!present){ 
        nodes[n1].adjacency.push_back(n2+1);
        nodes[n2].adjacency.push_back(n1+1);
      
       graphFile << n1+1 << " " << n2+1 << endl;
      countEdges++;}
    }
    for(int i = 0;i<numNodes;i++){
      int a = nodes[i].adjacency.size();
    }
    // Add appropriate code as necessary for your implementation
  }
  // void print(){
  //   for(int i=0;i<numNodes;i++){
  //     int a = nodes[i].adjacency.size();
  //     cout<<"*******" <<endl;
  //   for(int j= 0;j<a;j++){
  //     cout<<nodes[i].adjacency[j] <<endl;
  //   }
  //   }
  // }
  void set_arr(){
    visit_array = new int[numNodes];
    for(int i=0;i<numNodes;i++){
      visit_array[i]=0;
    }
    visit_array[node2]=1;
  }
  void p(){
    for(int i=0;i<numNodes;i++){
      cout<<i<<"::"<<visit_array[i]<<endl;
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

  void modifiedDFS();
  void printResults();
};

#endif
