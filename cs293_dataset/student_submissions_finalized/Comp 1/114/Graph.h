#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <vector>

struct TreeNode{
    // int JourneyCode;	// Train Number
    int value;		// Price
    TreeNode *left;	// Left Child of this Node (NULL, if None)
    TreeNode *right;	// Right Child of this Node (NULL, if None)
    TreeNode *parent;	// The Parent Node, NULL in case of Root
  
    // TreeNode() : price(0), JourneyCode(0), left(nullptr), right(nullptr) {}
    TreeNode(int val) : value(val), left(nullptr), right(nullptr), parent(nullptr) {}
    // TreeNode(int jrnyCode, int jrnyPrice, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : price(jrnyPrice), JourneyCode(jrnyCode), left(leftChild), right(rightChild), parent(parent) {}
};

class BST{

	TreeNode *root;

public:

	BST();
	BST(TreeNode *root);

	void printBST(const string& prefix, bool isLeft);
	bool insert(int value);

};

BST::BST() {
  root = nullptr;
}

BST::BST(TreeNode* root) {
  this->root = root;
}

// Adapted from Adrian Schneider's code on StackOverflow
void BST::printBST(const string& prefix, bool isLeft=false)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->value << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr;
        root = root->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    } 
}


// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int value) { 
    
    if(root == NULL){
        root = new TreeNode(value);
        return true;
    }
    else{
        TreeNode *temp = root;
        while(temp != NULL){

            if(temp->value > value){
                if(temp->left == NULL){
                    temp->left = new TreeNode(value);
                    
                    temp->left->parent = temp;

                    return true;
                }
                else{
                    temp = temp->left;
                }
            }
            else{
                if(temp->right == NULL){
                    temp->right = new TreeNode(value);

                    temp->right->parent = temp;

                    return true;
                }
                else{
                    temp = temp->right;
                }
            }
        }
    }
    
    return false;
}

class Node {
 public:

  // Value of node
  int value;

  // adjacency list of Node
  vector<Node*> adjancency;

  Node() {
    value = 0;
  }
  
  bool operator == (Node n2) {
    if (value == n2.value) {
      return true;
    }
  }

};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;

  vector<BST*> Trees;
  int noofComponents;
  int noofNodesinCycle;

  // Track of visited once or twice
  int* visited;
  // Track of visited once
  int* visitedonce;
  // Track of parents of all visited nodes
  int** parents;
  // arrival time according to Naveen sir's slides
  int* arrTime;
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    graphFile.open(gFileName, ios::out);
    if (!graphFile.is_open()) {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }

  int noofComponents = 0;
  int noofNodesinCycle = 0;

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

        bool proceed = true;

        // check if edge already exists
        for(int i = 0; i < nodes[n1].adjancency.size(); i++) {
          if (nodes[n1].adjancency[i]->value == nodes[n2].value) {
            proceed = false;
            break;
          }
        }

        if (proceed) {
          // check if edge already exists
          for(int i = 0; i < nodes[n2].adjancency.size(); i++) {
            if (nodes[n2].adjancency[i]->value == nodes[n1].value) {
              proceed = false;
              break;
            }
          }

          if (proceed) {
            // add nodes to each adjacency lists
            nodes[n1].adjancency.push_back(&nodes[n2]);
            nodes[n2].adjancency.push_back(&nodes[n1]);
            graphFile << n1+1 << " " << n2+1 << endl;
            countEdges++;
          }
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

    visited = new int[numNodes];
    visitedonce = new int[numNodes];
    arrTime = new int[numNodes];
    parents = new int*[numNodes];

    for (int i = 0; i < numNodes; i++) {
      visited[i] = 0;
    }


    for (int i = 0; i < numNodes; i++) {
      visitedonce[i] = 0;
    }

    for (int i = 0; i < numNodes; i++) {
      parents[i] = new int[2];
      parents[i][0] = 0;
      parents[i][1] = 0;
    }

    for (int i = 0; i < numNodes; i++) {
      arrTime[i] = numNodes+1;
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
