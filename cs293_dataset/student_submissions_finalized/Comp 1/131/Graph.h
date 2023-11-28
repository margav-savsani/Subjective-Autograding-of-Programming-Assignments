#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#include <vector>
#endif

class TreeNode{
  public:
  int price;
  TreeNode *left;	// Left Child of this Node (NULL, if None)
  TreeNode *right;	// Right Child of this Node (NULL, if None)
  TreeNode *parent;	// The Parent Node, NULL in case of Root
  int sizeOfTree = 1;
    // Constructors
  
    TreeNode() : price(0), left(nullptr), right(nullptr) {}
    TreeNode( int jrnyPrice) : price(jrnyPrice), left(nullptr), right(nullptr) {}
    TreeNode( int jrnyPrice,TreeNode *leftChild, TreeNode *rightChild,TreeNode *parent) : price(jrnyPrice),  left(leftChild), right(rightChild), parent(parent) {}

  // insert other fields and methods as appropriate
};
class BST {
	TreeNode *root;

	// result variable is for testing purposes, Do not tamper with it!
	vector<string> result;

public:
        // ************************************************************
        // Methods for Part I
  
	// Constructors!
	BST();
	BST(TreeNode *root);
	
        // This function prints the BST using ASCII characters using the
        // format:
        //
        //   root
        //       |-- left subtree
        //       |__ right subtree
        //
        // where the left and right subtrees are printed recursively in
        // the same format.
        //
	// We have done this for you! Please see BST.cpp for details
	// You may use this for debugging purposes.
        //
	void printBST(const string& prefix, bool isLeft);
	
	
	// The three functions below are for evaluation purposes, Do not tamper with them!
	void getBST(const string& prefix, bool isLeft);
	void clearResult();
	vector<string> getResult();
	
	// Returns false, if given JourneyCode is already present in the BST
	// Inserts the element and returns True otherwise
	bool insert( int price);

  ~BST(){
    delete root;
  }

  // Add your own field and members here

  // Feel free to use the printBST function used earlier
};

class adjacent  {
 public:
  int value;
  adjacent *next;
  adjacent *prev;
  
  // Constructor
  adjacent (int initValue) {value = initValue; next = prev = nullptr;}
  
  // Destructor
  ~adjacent() {;}
};
class Node {
 public:
  int value;
  adjacent* adjacencylist;
  adjacent * backtrack ;
  Node (){adjacencylist = nullptr;backtrack = nullptr;}};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;

  // Add appropriate fields as necessary for your implementation
  
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

    int i=0;
    
    while (countEdges < numEdges) {
      do {
	n1 = rand() % numNodes;
	n2 = rand() % numNodes;
      } while (n1 == n2);
      adjacent *tolist =nodes[n1].adjacencylist;
      bool already= false;
      while(tolist!= nullptr){
        if (tolist->value == n2+1){
          countEdges --;
          already = true;
          break;
        }
        tolist = tolist->next;
      }
      if (already== false){
        adjacent * newneighbour =  new adjacent(n1+1);
        newneighbour->next=nodes[n2].adjacencylist;
        nodes[n2].adjacencylist =newneighbour;
        adjacent * newneighbour1 =  new adjacent(n2+1);
        newneighbour1->next=nodes[n1].adjacencylist;
        nodes[n1].adjacencylist =newneighbour1;

      }

      
      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile

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
  void printResults();
  void DFS(Node & node,BST *b1,int parent, bool & yescycle);
  void DFS2(Node & node ,int parent , BST *b1);
};

#endif
