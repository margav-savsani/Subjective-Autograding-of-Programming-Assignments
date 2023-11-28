#ifndef GRAPH_BST_H
#define GRAPH_BST_H
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
using namespace std;

struct TreeNode{
  int NodeValue;
  TreeNode* left;
  TreeNode *right;
  TreeNode *parent;
  TreeNode(){
    NodeValue = 0;
    left = nullptr;
    right = nullptr;
  }
  TreeNode(int x,TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent){
    NodeValue = x;
    left = leftChild;
    right = rightChild;
    this->parent = parent;
  }
};


class BST {
  // Add your own field and members here

  // Feel free to use the printBST function used earlier
  
  public:
  TreeNode *root;
  BST(){
    root = nullptr;
  }
  void insert(int x, TreeNode* n);
  void printBST1(TreeNode * root,const string& prefix, bool isLeft);
  void printBST(TreeNode *node);
};


class Node {
 public:
  int value;
  Node **adjacentNodes;
  int adjacentNodesCount;
  int visitedCount;

  // insert other fields and methods as appropriate
};

class Graph {
  int connectedComponents;
  int nodesVisitedOnce;
  int nodesVisitedTwice;
  int numNodes;
  int numEdges;
  fstream graphFile;
  BST **BSTtrees;
  int BSTCount;
  Node *nodes;

  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
  
    numNodes = nNodes;
    numEdges = nEdges;
    BSTtrees = new BST*[numNodes];
    BSTCount = 0;
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
      nodes[i].adjacentNodes = new Node*[numNodes];
      nodes[i].adjacentNodesCount = 0;
      nodes[i].visitedCount = 0;
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

    
    bool edgeFound = false;
    for(int i=0;i<=nodes[n1].adjacentNodesCount;i++){
      if(nodes[n1].adjacentNodes[i]->value==nodes[n2].value){
        edgeFound = true;
      }
    }
    if(!(edgeFound)){
      *(nodes[n1].adjacentNodes[nodes[n1].adjacentNodesCount])=nodes[n2];
      nodes[n1].adjacentNodesCount++;
      *(nodes[n2].adjacentNodes[nodes[n2].adjacentNodesCount])=nodes[n1];
      nodes[n2].adjacentNodesCount++;
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
  int indexOfUnvisitedNode();
  void modifiedDFSNodeParameter(Node *n, BST* Tree);
  void modifiedDFS();
  void printResults();
  
};

#endif
