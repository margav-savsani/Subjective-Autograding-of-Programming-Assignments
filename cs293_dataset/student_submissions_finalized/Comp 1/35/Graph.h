#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#include <vector>
using namespace std;
#endif


struct TreeNode{
  int value;          //value
  TreeNode *left;     // Left Child of this Node (NULL, if None)
  TreeNode *right;    // Right Child of this Node (NULL, if None)
  TreeNode *parent;   // The Parent Node, NULL in case of Root

  // Constructors
  
    TreeNode() : value(0), left(nullptr), right(nullptr) {}
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
    TreeNode(int val, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : value(val), left(leftChild), right(rightChild), parent(parent) {}
};

class BST {
  // Add your own field and members here
  TreeNode *root;
  public:
    // Constructors
    BST(){
      root = nullptr;
    };
    BST(TreeNode *root){
      this->root = root;
    };

    bool insert(int val) {  
      TreeNode * New = new TreeNode(val);
      New->parent = nullptr;
      TreeNode * y = nullptr;
      TreeNode * x = this->root;
      while(x != nullptr){
          y = x;
          if(val < x->value){
              x = x->left;
          }
          else {
              x = x->right;
          }
      }
      New->parent = y;
      if( y == nullptr){
          this->root = New;
      }
      else if(val < y->value){
          y->left = New;
      }
      // Same value elements will be added as the right child
      else {
          y->right = New;
      }
      return true;
    }

  // Feel free to use the printBST function used earlier
    void printBST(const string& prefix, bool isLeft=false){
      if( root != nullptr ){
        cout << prefix;
        cout << (isLeft ? "|--" : "|__" );
        // print the value of the node
        cout << root->value << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
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

  // insert other fields and methods as appropriate
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;

  // Add appropriate fields as necessary for your implementation
 public:

  vector<int>* AdjacencyList;
  vector<int>* UndirectedEdgeList;
  int** adjMat;
  int* visited;
  int NoOfConnectedComponents = 0;
  int NoOfNodesVisitedOnce;
  int NoOfNodesVisitedTwice = 0;
  int NoOfNodesInACycle = 0;
  vector<BST*> BSTrees;
  bool* presentInCycle;
  vector<Node> Stack;

  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    NoOfNodesVisitedOnce = nNodes;
    AdjacencyList = new vector<int>[nNodes];
    UndirectedEdgeList = new vector<int>[nNodes];
    adjMat = new int*[nNodes];
    visited = new int[nNodes];
    presentInCycle = new bool[nNodes];
    for(int i = 0;i < nNodes;i++) {
      presentInCycle[i] = false;
    }
    for(int i = 0;i < nNodes;i++) {
      adjMat[i] = new int[nNodes];
    } 
    for(int i = 0;i < nNodes;i++) {
      for(int j = 0;j < nNodes;j++) {
          adjMat[i][j] = 0;
       }
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
      if(adjMat[n1][n2] == 0 && adjMat[n2][n1] == 0){
        adjMat[n1][n2] = 1;
        adjMat[n2][n1] = 1;
        // This is for traversing in DFS by fixing the direction of the path
        // I am making them uni-directed later
        AdjacencyList[n1].push_back(n2);
        AdjacencyList[n2].push_back(n1);
        // This is for checking cycles 
        UndirectedEdgeList[n1].push_back(n2);
        UndirectedEdgeList[n2].push_back(n1);
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
    
    // Add appropriate code as necessary for your implementation
    delete[] nodes;
    for(int i = 0; i < numNodes;i++) {
      delete[] adjMat[i];
    }
    delete[] adjMat;
  }

  // Add appropriate method declarations as necessary for your implementation
  
  // I am dividing the entire graph into connected components in modifiedDFS and 
  // applying DFS to them for each connected in this func
  void DFS(Node N,BST* bst);

  void modifiedDFS();
  void printResults();
};

#endif
