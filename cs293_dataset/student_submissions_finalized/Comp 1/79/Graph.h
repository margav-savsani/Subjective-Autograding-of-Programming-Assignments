#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <vector>

using namespace std;

class BST {
  // Add your own field and members here
  public:
    int data;
    BST *left, *right;


    // Default constructor.
    BST();

    // Parameterized constructor.
    BST(int);

    // Insert function.
    BST* Insert(BST*, int);

    // Print function
    void printInfo();
    void printBinaryTree(BST *root, const string& prefix, bool isLeft);


  // Feel free to use the printBST function used earlier
};

// Default Constructor definition.
BST ::BST()
	: data(0)
	, left(NULL)
	, right(NULL)
{
}

// Parameterized Constructor definition.
BST ::BST(int value)
{
	data = value;
	left = right = NULL;
}

// Insert function definition.
BST* BST ::Insert(BST* root, int value)
{
	if (!root) {
		// Insert the first node, if root is NULL.
		return new BST(value);
	}

	// Insert data.
	if (value > root->data) {
		// Insert right node data, if the 'value'
		// to be inserted is greater than 'root' node data.

		// Process right nodes.
		root->right = Insert(root->right, value);
	}
	else{
		// Insert left node data, if the 'value'
		// to be inserted is smaller than or equal to 'root' node data.

		// Process left nodes.
		root->left = Insert(root->left, value);
	}

	// Return 'root' node, after insertion.
	return root;
}

void BST :: printBinaryTree(BST *root, const string& prefix, bool isLeft)
{
  if( root != nullptr ){
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    root->printInfo();
    cout << endl;
    BST *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
}

void BST :: printInfo(){
    cout<<data+1<<endl;
}

class Graph {
  int numNodes;
  int numEdges;
  int numberOfConnectedComponents = 0;
  int oneVisitCount = 0;
  int twoVisitCount = 0;
  fstream graphFile;

  BST *root = new BST;
  BST *nodes;
  int *Visited;
  vector<int> *Adj;
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

    nodes = new BST[numNodes];
    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++) {
      nodes[i].data = i+1;
    }

    srand(time(0));
    int n1, n2;
    int countEdges = 0;

    Adj = new vector<int>[numEdges]; 
    Visited = new int[numNodes];
    while (countEdges < numEdges) {
      do {
        n1 = rand() % numNodes;
        n2 = rand() % numNodes;
      } while (n1 == n2);

      bool edgeExists = false;
      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile

      for(int i = 0; i < Adj[n1].size(); i++) {
        if (Adj[n1][i] == n2){ 
          edgeExists = true;
          break;
        }
      }
      if(!edgeExists){
        Adj[n1].push_back(n2);
        Adj[n2].push_back(n1);

        graphFile << n1+1 << " " << n2+1 << endl;
        countEdges++;
      }
    }

    // Add appropriate code as necessary for your implementation
  }

  // Add appropriate method declarations as necessary for your implementation
  void VisitCount();
  void modifiedDFS();
  void myDFS(int i);
  void printResults();
};

#endif
