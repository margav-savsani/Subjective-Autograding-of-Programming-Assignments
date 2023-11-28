#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

class BSTNode{
  public:
  int value;
  BSTNode* left;
  BSTNode* right;
  BSTNode(int value){
    this->value=value;
  }
};

class BST {
  // Add your own field and members here
  BSTNode* root;
  public:
  void insert(int value){
    if(root==nullptr){
      root= new BSTNode(value);
    }
    BSTNode* curr=root;
    while(curr!=nullptr){
      if(curr->value>value){
        if(curr->left!=nullptr) curr=curr->left;
        else {
          curr->left=new BSTNode(value);
          return;
        }
      } 
      else{
        if(curr->right!=nullptr) curr=curr->right;
        else {
          curr->right=new BSTNode(value);
          return;
        }
      }
    }
  }
  void printBinaryTree(BSTNode *root, const string &prefix, bool isLeft)
  {
    if (root != nullptr)
    {
      cout << prefix;

      cout << (isLeft ? "|--" : "|__");

      // print the value of the node
      cout <<root->value<< endl;
      BSTNode *curr = root;
      root = root->left;
      // enter the next tree level - left and right branch
      printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), true);
      root = curr->right;
      printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), false);
      root = curr;
    }
    else
    {
      cout << "NULL tree" << endl;
    }
  }
  void print() { 
    printBinaryTree(root, "", false);
    return;
  }

  // Feel free to use the printBST function used earlier
};

class Node {
 public:
  int value;
  bool* adjacency;
  int visited;
  bool* parent;
  bool backtracked;
  // insert other fields and methods as appropriate
  Node(){}
  Node(int value){
    this->value=value;
  }
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;
  int connected;
  BST* Tree;
  Node *nodes;

  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    Tree=new BST[numNodes];
    connected=0;
    graphFile.open(gFileName, ios::out);
    if (!graphFile.is_open()) {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }
    if(numEdges>(numNodes*(numNodes-1)/2)){
      cerr << "No of edges is not feasible" << endl;
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
      nodes[i].adjacency=new bool[numNodes];
      for(int j=0; j<numNodes; j++){
        nodes[i].adjacency[j]=false;
      }
      nodes[i].visited=0;
      for(int j=0;j<numNodes;j++){
        nodes[i].parent=new bool[numNodes];
        nodes[i].parent[j]=false;
      }
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
      if(!nodes[n1].adjacency[n2]){
          nodes[n1].adjacency[n2]=true;
          nodes[n2].adjacency[n1]=true;
          graphFile << n1+1 << " " << n2+1 << endl;
          countEdges++;
      }
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

  void DFS(int value);
  void modifiedDFS();
  void printResults();
};

#endif
