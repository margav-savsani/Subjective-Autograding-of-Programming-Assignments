#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#include <vector>
#endif


class Node {
 public:
  int value;
  vector<int> adj_nodes; // will store all the indices of adjacent nodes in the list.
  int visit = 0;
  bool back_trace = false;

};

struct parent{
  int parent1; // parent 1
  int parent2; // parent 2
  parent(){ // constructor
    parent1 = -1; parent2 = -1;
  }
  void insert(int a){ // inserting a as the parent
    if(parent1 == -1){
      parent1 = a;
    }
    else{
      parent2 = a;
    }
  }
};

class Graph {
  int numNodes;
  int numEdges;
  int connected;    // to get no. of connected components
  int visited_once; // no. of nodes visited once
  int visited_twice;// no. of nodes visited twice
  parent* parent_list;

  int no_of_nodes_in_cycle; //no_of_nodes_in_cycle
  vector<int> nodes_in_cycle; // to check for no. of nodes 
  vector<bool> nodes_bool; // to check fot no. of nodes in cycle
  fstream graphFile;

  Node *nodes;

  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    connected = 0;
    visited_once = 0;
    visited_twice = 0;

    parent_list = new parent[numNodes];
    for(int i =0; i<numNodes; i++){
      nodes_in_cycle.push_back(i); // inserting
      nodes_bool.push_back(true);  // inserting
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

    srand(0);
    int n1, n2;
    int countEdges = 0;
    
    while (countEdges < numEdges) {
      do {
	n1 = rand() % numNodes;
	n2 = rand() % numNodes;
      } while (n1 == n2);

      int check = 0;
      for (int i = 0; i < nodes[n1].adj_nodes.size(); i++){
        if (n2 == nodes[n1].adj_nodes[i])
          check = 1;
      }
      if (check != 1){
        nodes[n1].adj_nodes.push_back(n2);
        nodes[n2].adj_nodes.push_back(n1);

        graphFile << n1 + 1 << " " << n2 + 1 << endl;
        countEdges++;
      }
    }
  }

  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;
    // Add appropriate code as necessary for your implementation
  }

  void cycles();
  void DFS(int index);
  void modifiedDFS();
  void printResults();
};


//******************* BST ******************//
struct TreeNode
{
  int value;        // Price
  TreeNode *left;   // Left Child of this Node (NULL, if None)
  TreeNode *right;  // Right Child of this Node (NULL, if None)
  TreeNode *parent; // The Parent Node, NULL in case of Root
  int sizeOfTree = 1;
  // Constructors

  TreeNode() : value(0), left(nullptr), right(nullptr) {}
  TreeNode(int jrnyPrice) : value(jrnyPrice), left(nullptr), right(nullptr) {}
  TreeNode(int jrnyPrice, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : value(jrnyPrice), left(leftChild), right(rightChild), parent(parent) {}
};
class BST
{
  TreeNode *root;
  // Add your own field and members here

  // Feel free to use the printBST function used earlier
public:
  BST() { root = NULL; }
  BST(TreeNode *root) { this->root = root; }
  bool insert(int price)
  {
    // Adding the first node
    if (root == NULL)
    {
      root = new TreeNode(price, NULL, NULL, NULL);
      return true;
    }
    // Checking if similar node already exists

    TreeNode *curr = root;
    while (true)
    {
      curr->sizeOfTree++; // incrementing Size of subtree which is rooted at this node

      // Moving to the right, if price is greater
      if (price > curr->value)
      {
        if (curr->right != NULL)
        {
          curr = curr->right;
        }
        else
        {
          curr->right = new TreeNode(price, NULL, NULL, curr);
          break;
        }
      }
      else
      {
        // moving to left if its smaller
        if (curr->left != NULL)
        {
          curr = curr->left;
        }
        else
        {
          curr->left = new TreeNode(price, NULL, NULL, curr);
          break;
        }
      }
    }
    //  this->printBST("",false);
    return true;
  }

  void printBST(const string &prefix, bool isLeft = false)
  {
    if (root != nullptr)
    {
      cout << prefix;

      cout << (isLeft ? "|--" : "|__");

      // print the value of the node
      cout << '(' << root->value << ')' << endl;
      TreeNode *curr = root;
      root = root->left;
      // enter the next tree level - left and right branch
      printBST(prefix + (isLeft ? "│   " : "    "), true);
      root = curr->right;
      printBST(prefix + (isLeft ? "│   " : "    "), false);
      root = curr;
    }
  }
};




#endif
