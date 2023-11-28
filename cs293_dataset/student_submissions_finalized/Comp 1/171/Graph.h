#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

struct TreeNode{
    int val;
    TreeNode *left;	// Left Child of this Node (NULL, if None)
    TreeNode *right;	// Right Child of this Node (NULL, if None)
    TreeNode *parent;	// The Parent Node, NULL in case of Root

    // Constructors
  
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int a) : val(a), left(nullptr), right(nullptr) {}
    TreeNode(int a, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : val(a), left(leftChild), right(rightChild), parent(parent) {}
};

class BST {
 public:
  TreeNode *root;

  BST(){ 
    this->root=nullptr; 
  }
	BST(TreeNode *root){ this->root=root; }
  bool insert(int val){
    TreeNode *z;
    z = new TreeNode(val);
    
    TreeNode *y = nullptr;
    TreeNode *x = root;
    while(x!=nullptr){
      y=x;
      if(val<x->val)
        x = x->left;
      else
        x  = x->right;
    }
    z->parent = y;
    if(y==nullptr)
      root = z;
    else {
      if(val<y->val)
        y->left = z;
      else 
        y->right = z;
    }
    
    return true;  
  }
  void printBST(const string& prefix, bool isLeft=false){
    if( root != nullptr ){
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->val << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}
  // Add your own field and members here

  // Feel free to use the printBST function used earlier
};

class Node {
 public:
  int value;
  int adjacentNodes[20];
  BST b;
  Node(){
    for(int i=0;i<20;i++){
      adjacentNodes[i]=-1;
    }
  }
  // insert other fields and methods as appropriate
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;
  int *visited;
  Node *nodes;
  int cyc;
  int *a1,*a2,*a3;
  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    cyc=0;
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
    a1 = new int[numNodes];
    a2 = new int[numNodes];
    a3 = new int[numNodes];
    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }
    
    for (int i = 0; i < numNodes; i++){
      visited[i]=0;
      a1[i]=0;
      a2[i]=0;
      a3[i]=0;
      nodes[i].value = i+1;
    }
    srand(time(0));
    int n1, n2;
    int countEdges = 0;
    
    while(countEdges < numEdges){
      do{
	      n1 = rand() % numNodes;
        n2 = rand() % numNodes;
      }while (n1 == n2);
      
      int bo = 0,i,j;
      for(i=0;nodes[n1].adjacentNodes[i]!=-1;i++){
        if(nodes[n1].adjacentNodes[i]==n2)
          bo = 1;
      }
      
      if(bo==0){
        for(j=0;nodes[n2].adjacentNodes[j]!=-1;j++){
          continue;
        }
        nodes[n1].adjacentNodes[i] = n2;
        nodes[n2].adjacentNodes[j] = n1;
        countEdges++;
        graphFile << n1+1 << " " << n2+1 << endl;
      }
      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile
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
  int conncomp=0;
  void modifiedDFS();
  void DFS(Node n,BST b,int par);
  void printResults();
};

#endif