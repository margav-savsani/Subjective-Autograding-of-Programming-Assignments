#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
class TreeNode{

	public:
	int value; // value of the treeNode.
	TreeNode* left; // left node.
	TreeNode* right; // right node.
	TreeNode( int val){ // constructor.
		
		value = val;
		left = nullptr;
		right = nullptr;
	}
};

class BST {

  TreeNode* root;// root of the tree.
  
  public:
 
  BST() {// constructor.
  
  	root = nullptr;
  }
  void insert( int value){ // insert the value into the tree.
  	
  	TreeNode* leaf = new TreeNode( value ); // node to insert.
  	if ( root == nullptr)	{ // first element.
  		
  		root = leaf;// if root is nullptr.
  		return;
  	} 	 	  	  	
  	TreeNode* tree = root; // if it is not nullptr, then search for place.
  	while( true ){ // go to the loop.
  		
  		if ( tree->value >= value ) { // if the value is less or equal, then add it on left(assumption that if it is equal, add it on left). 
  			
  			if ( tree->left == nullptr) { // if left is null directly add.
  				tree->left = leaf;
 				return;
  			}  			 			
  			tree = tree->left;// recursion.
  		}
  		else { // if it is greater, than add it on the right 
  		
  			if ( tree->right == nullptr) { // if right is null directly add.
  				tree->right = leaf;
  				return;
  			}  
  			tree = tree->right;	 		
  		}
  	}
  	return;
  	
  }
  
  void printBST(const string& prefix, bool isLeft=false){// print the BST
  
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->value << endl;
        TreeNode *curr = root;
        root = curr->left;
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
  int value;// value of the node.
  int no_of_times_visited = 0;// every time you insert increment the value by 1.// max it has to be once.
  // insert other fields and methods as appropriate
};


class ConnectedTrees{// stores BST Trees.

  public:
	BST *tree;// BST tree.
	ConnectedTrees *next;// next BST pointer.
	ConnectedTrees( ){// constructor.		
		tree = new BST();
		next = nullptr;
	}
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;
  Node *nodes;
  int no_of_connected_graphs = 0; // counting number of connected graphs.
  int** adj;// to store adjacency list as a matrix.
  int* present_in_cycle;// it is 0 if it is not present in any cycle, else 1.
  int currnode = 0;// position of the current node, while we are doing modified DFS.
  // to store different BSTs.
  ConnectedTrees *head = nullptr;// head pointer
  ConnectedTrees *tail = nullptr;// tail pointer, to make addition easy.
  int* stage_of_vertices;// while counting whether it is present in cycle or not, 0 if it is not visited, 1 if it is partially visited, 2 if it is completely visited.
  int* parent_array;// which stores parent of the ith index.
  public:
  
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    present_in_cycle = new int[numNodes];
    stage_of_vertices = new int[numNodes];
    parent_array = new int[numNodes];
    graphFile.open(gFileName, ios::out);
    // adjacency array.
    adj = new int*[nNodes];
    for ( int i=0; i<numNodes; i++){ // no edges are added at.
    	adj[i] = new int[nNodes];
    	for( int j=0; j< numNodes; j++){
    		
    		adj[i][j] = 0;
    	}
    }
    		
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
    // initializing all the pointers.
    for (int i = 0; i < numNodes; i++) {
      present_in_cycle[i] = 0;
      stage_of_vertices[i] = 0;
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
      
      if ( adj[n1][n2] == 0){
      		
      		adj[n1][n2] = 1;// created an undirected edge
      		adj[n2][n1] = 1;// created an undirected edge
      		graphFile << n1+1 << " " << n2+1 << endl; // add it into file
      		countEdges++; // increment only when you add an edge.
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

  void modifiedDFS();
  void printResults();
  // new functions.
  void DFS( int currentnode, int prev_node);// to do Modified DFS.
  void cycles(int curr, int parent);// to count number of vertices in a cycle.
};

#endif
