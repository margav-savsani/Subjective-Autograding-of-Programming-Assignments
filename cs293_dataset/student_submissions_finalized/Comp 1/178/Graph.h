#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif


struct TreeNode
{
    // member vars
    int data;
    TreeNode* left;
    TreeNode* right;
    // constructor
    TreeNode() : data(0), left(nullptr), right(nullptr) {}
    TreeNode(int data): data(data), left(nullptr), right(nullptr) {}
};

class BST {
  TreeNode *root;

public:  
  BST();
	BST(TreeNode *root);
  void insert(int data);
  void printBST(const string& prefix, bool isLeft=false);
  // Add your own field and members here

  // Feel free to use the printBST function used earlier
};

class Node {
 public:
  int value;
  int visited = 0;
  
  // insert other fields and methods as appropriate
};
class TREE{
  public:
  BST *tree;
  TREE *next;
  TREE(){tree = new BST(); next = NULL;}
 };
class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;
  int**adj;
  Node *nodes ;
  int *present, *color , *par;
  TREE *tail = NULL; 
  TREE *head = NULL;
  // Add appropriate fields as necessary for your implementation
  
 public:
    
    int no_connected= 0;
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
    present = new int[numNodes];
    color = new int[numNodes];
    par = new int[numNodes];
    nodes = new Node[numNodes];
    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
      present[i] = 0;
      color[i]  = 0;
      
    }

    srand(time(0));
    int n1, n2;
    int countEdges = 0;
    adj = new int *[numNodes];
    for ( int i=0;i<numNodes; i++){
      adj[i] = new int[numNodes]; 
      for(int j=0;j<numNodes;j++){
        adj[i][j] = 0;
      }
    }

    while (countEdges < numEdges) {
      do {
	    n1 = rand() % numNodes;
	    n2 = rand() % numNodes;
      }while (n1 == n2);
    if(adj[n1][n2]==0){
      adj[n1][n2]=1;
      adj[n2][n1]=1;
      graphFile << n1+1 << " " << n2+1 << endl;
      countEdges++;
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
  void Cycle(int vertex,int prev_vertex);
  void DFS(int vertex, int prev_vertex);
  void modifiedDFS();
  void printResults();
  
};

#endif
