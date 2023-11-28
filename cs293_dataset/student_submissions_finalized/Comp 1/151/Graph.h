#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <vector>
#include <map>
#include <set>

struct BSTNode{
    int value;
    BSTNode *left;	// Left Child of this Node (NULL, if None)
    BSTNode *right;	// Right Child of this Node (NULL, if None)
    BSTNode *parent;	// The Parent Node, NULL in case of Root
    int sizeOfTree = 1;
    // Constructors
  
    BSTNode() : value(0), left(nullptr), right(nullptr) {}
    BSTNode(int v) : value(v), left(nullptr), right(nullptr) {}
    BSTNode(int v, BSTNode *leftChild, BSTNode *rightChild, BSTNode *parent) : value(v), left(leftChild), right(rightChild), parent(parent) {}
};


class BST{
public:
	BSTNode *root;


	// Constructors!
	BST();
	BST(BSTNode *root);

	void printBST(const string& prefix, bool isLeft)
	{
      if( root != nullptr )
      {
          cout << prefix;

          cout << (isLeft ? "|--" : "|__" );

          // print the value of the node
          cout << '('<< root->value << ')' << endl;
          BSTNode *curr = root;
          root = root->left;
          // enter the next tree level - left and right branch
          printBST( prefix + (isLeft ? "│   " : "    "), true);
          root = curr->right;
          printBST( prefix + (isLeft ? "│   " : "    "), false);
          root = curr;
      }
  }

	// Returns false, if given JourneyCode is already present in the BST
	// Inserts the element and returns True otherwise
	bool insert(int value) { 
    // Adding the first node
    if(root == NULL){
        root = new BSTNode(value);
        return true;
    }

    BSTNode *curr = root;
    while(true){
        curr->sizeOfTree++; // incrementing Size of subtree which is rooted at this node

        // Moving to the right, if price is greater
        if(value > curr->value){
            if(curr->right!=NULL){
                curr = curr->right;
            }else{
                curr->right = new BSTNode(value,NULL,NULL,curr);
                break;
                
            }
        }else{
            // moving to left if its smaller
            if(curr->left!=NULL){
                curr = curr->left;
            }else{
                curr->left = new BSTNode(value,NULL,NULL,curr);
                break;
            }
        }
    }
    return true;
  } 
  
	// Return true, if the ticket with given attributes is found, false otherwise
	bool find(int value){
	  if(root==NULL)return false;
    BSTNode* curr = root;
    while(true){
      
        if(curr->value==value){
            return true;
        } else if(curr->value > value){
      
            if(curr->left==NULL){
                return false;
            }else{
                curr = curr->left;
            }
        }else{
            if(curr->right==NULL){
                return false;
            }else{
                curr = curr->right;
            }
        }
    }
    return false;
  }

};



class Node {
 public:
  int value;
  int visited;
  // insert other fields and methods as appropriate

  vector<int> adj;

};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;

  // Add appropriate fields as necessary for your implementation
  
  vector<BST* > trees;

  int numConnectedComp;
  int numNodesVisitedOnce;
  int numNodesVisitedTwice;
  int numNodesInCycle;
  bool *marked;
  set<int> badvalues;

 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;

    marked = new bool[numNodes];

    numConnectedComp = 0;
    numNodesVisitedOnce = 0;
    numNodesVisitedTwice = 0;
    numNodesInCycle = 0;

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
      nodes[i].visited = 0;
    }

    srand(4);
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

      bool edgeExists = false;

      for(auto i : nodes[n1].adj){
        if(i == n2){
          edgeExists = true;
          break;
        }
      }

      if(!edgeExists){
        for(auto i : nodes[n2].adj){
          if(i == n1){
            edgeExists = true;
            break;
          }
        }
      }

      if(!edgeExists){
        nodes[n1].adj.push_back(n2);
        nodes[n2].adj.push_back(n1);
      }

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
  void DFSrecursive(Node &n, int parent, BST* tree);
  void printResults();
};

#endif
