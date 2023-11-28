#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include<vector>
using namespace std;

// TreeNode is used to make nodes of BST
struct TreeNode{
  int data;
  TreeNode *parent;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int value): data(value), left(NULL), right(NULL) {}     
};

// Class BST implements Binary Search Tree
class BST {
  // Add your own field and members here
public:
  TreeNode *root; // Root of the BST
  BST();    // Constructor
	BST(TreeNode *root);  // Constructor
  void printBST(const string& prefix, bool isLeft); // PrintBST function copied from lab3
  TreeNode* insert( TreeNode* root ,int data);      // Insert function
  // Feel free to use the printBST function used earlier
};


class Node {
 public:
  int value;
  // insert other fields and methods as appropriate
  vector<int> adjacent;   // This is adjcent list of node 
  // Node
  Node(){
    adjacent.resize(1);
  }
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;
  vector<BST*> trees2;
  Node *nodes;
  vector <int>vis;// keep trach of how many time visited
  vector <int>par;// keep track of parent
  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    vis.resize(nNodes);
    par.resize(nNodes);
    numNodes = nNodes;
    numEdges = nEdges;
    trees2.resize(1);
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
        bool already_exists=false;
        for(int i=0;i<nodes[n1].adjacent.size();i++){
          if(nodes[n1].adjacent[i]==n2+1){
            already_exists=true;
          }
        }
        if(!already_exists){
          nodes[n1].adjacent.push_back(n2+1);
          nodes[n2].adjacent.push_back(n1+1);
        }
        else{
          continue;
        }
        //return ;
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
  
  void DFS2(BST *b,int u, int p);
  void modifiedDFS();
  void printResults();
};

#endif
