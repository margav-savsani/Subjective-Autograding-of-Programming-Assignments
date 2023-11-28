#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include<string>
template <typename T> class listOfObjects {
 public:
  T object;
  listOfObjects<T> *next;
  // Lab 7 specific
  listOfObjects<T> *prev;
  // End lab 7 specific
  // Constructor
  // Lab 7 specific
  // Modified to initialize prev, compared to constructor in lab 6
  listOfObjects(T initValue) {object = initValue; next = prev = nullptr;}
  // End lab 7 specific
  // Destructor
  ~listOfObjects() {;}
};
struct TreeNode{
    int JourneyCode;	// Train Number
    TreeNode *left;	// Left Child of this Node (NULL, if None)
    TreeNode *right;	// Right Child of this Node (NULL, if None)
    TreeNode *parent;	// The Parent Node, NULL in case of Root
  
    TreeNode() :JourneyCode(0), left(nullptr), right(nullptr) {}
    TreeNode(int jrnyCode) :JourneyCode(jrnyCode), left(nullptr), right(nullptr) {}
    TreeNode(int jrnyCode,TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : JourneyCode(jrnyCode), left(leftChild), right(rightChild), parent(parent) {}
};
class BST {
  TreeNode *root;
  public:
  BST();
	BST(TreeNode *root);
	void printBST(const string& prefix, bool isLeft);
	bool insert(int JourneyCode);
};

class Node {
 public:
  int value;

  // insert other fields and methods as appropriate
};

class Graph {
  int numNodes;
  int numEdges;
  int noc;
  fstream graphFile;

  Node *nodes;
  int *visited;
  int **adjacencylist;
  int **bridge;
  listOfObjects<BST *>*alltrees;
  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    noc=0;
    numNodes = nNodes;
    numEdges = nEdges;
    adjacencylist=new int*[nNodes];
    for(int i=0;i<nNodes;i++){
      adjacencylist[i]=new int[nNodes];
    }
    for(int i=0;i<nNodes;i++){
      for(int j=0;j<nNodes;j++){
        adjacencylist[i][j]=0;
      }
    }
    bridge=new int*[nNodes];
    for(int i=0;i<nNodes;i++){
      bridge[i]=new int[nNodes];
    }
    for(int i=0;i<nNodes;i++){
      for(int j=0;j<nNodes;j++){
        bridge[i][j]=0;
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
      bool present = false;
      if(adjacencylist[n1][n2] == 1){
        present=true;
      }
      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile
      if(!present){
        adjacencylist[n1][n2]=1;
        adjacencylist[n2][n1]=1;
        graphFile << n1+1 << " " << n2+1 << endl;
        countEdges++;
      }
    }

    // Add appropriate code as necessary for your implementation
    visited=new int[numNodes];
    for(int i=0;i<numNodes;i++){
      visited[i]=0;
    }
    alltrees=nullptr;
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
  BST* DFS(int s,BST *tree,int parent[]);
  void checkbridge(int u,bool visited[],int disc[],int low[],int parent[]);
};

#endif
