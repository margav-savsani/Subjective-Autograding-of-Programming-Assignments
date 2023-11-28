#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
using namespace std;

// Linked List
template <typename T> class listOfObjects {
 public:
  T object;
  listOfObjects<T> *next;
  
  // Constructor
  listOfObjects(){object = nullptr; next = nullptr;}
  listOfObjects(T initValue) {object = initValue; next = nullptr;}
  
  // Destructor
  ~listOfObjects(){;}
};

// BST Node
class TreeNode{
  public:
  int value;
  TreeNode* left;
  TreeNode* right;

  TreeNode(){value = -1; left = nullptr; right = nullptr;}
  TreeNode(int v){value = v; left = nullptr; right = nullptr;}
};

// BST class
class BST {
  public:
  TreeNode *root;

  BST(){
    root = nullptr;
  }

  bool insert(int value)
  {
    // New node for insertion
    TreeNode *newNode = new TreeNode(value);

    TreeNode *currNode = root;
    TreeNode *parentOfCurrNode = nullptr;
    while (currNode != nullptr)
    {
      if (currNode->value < newNode->value)
      {
        parentOfCurrNode = currNode;
        currNode = currNode->right;
      }
      else
      {
        parentOfCurrNode = currNode;
        currNode = currNode->left;
      }
    }

    if (parentOfCurrNode == nullptr){
      root = newNode;
        return true;
    }
    else{
      if (newNode->value > parentOfCurrNode->value){
        parentOfCurrNode->right = newNode; 
      }
      else{
        parentOfCurrNode->left = newNode; 
      }
    }

    return true;
  }

  // BST print function
  void printBinaryTree(TreeNode *root, const string& prefix, bool isLeft)
  {
    if( root != nullptr )   {
      cout << prefix;
      
      cout << (isLeft ? "|--" : "|__" );
      
      // print the value of the node
      cout << root->value;
      cout << endl;
      TreeNode *curr = root;
      root = root->left;
      // enter the next tree level - left and right branch
      printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), true);
      root = curr->right;
      printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), false);
      root = curr;
    }
    else {
      cout << prefix;
      cout << (isLeft ? "|--" : "|__" );
      cout << "NULL tree" << endl;
    }
  }

};

// Graph node class
class Node {
 public:
  int value;
  listOfObjects<Node*>* adjacencyList;
  listOfObjects<Node*>* blockList;

  Node(){
    value = -1;
    adjacencyList = nullptr;
    blockList = nullptr;
  }

  // Insert Node pointer in adjacency list of current node
  void insert_adj(Node* p){
    listOfObjects<Node*>* l = new listOfObjects<Node*>(p);
    l->next = adjacencyList;
    this->adjacencyList = l;
  }

  // Insert Node pointer in block list of current node
  // This list would contain 1 or 2 parents of current node and the node
  void insert_block(Node* p){
    listOfObjects<Node*>* l = new listOfObjects<Node*>(p);
    l->next = blockList;
    this->blockList = l;
  }
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;

  int* visited;
  int numConnected;
  listOfObjects<BST*>* trees;

 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;

    visited = new int[nNodes];
    for (int i = 0; i < nNodes; i++){
      visited[i] = 0;
    }

    numConnected = 0;
    trees = nullptr;

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
    // int edges[2*6] = {0,1,1,2,2,0,2,3,3,4,4,2};
    while (countEdges < numEdges) {
      do {
        n1 = rand() % numNodes;
        n2 = rand() % numNodes;
        // n1 = edges[2*countEdges];
        // n2 = edges[2*countEdges+1];
      } while (n1 == n2);

      listOfObjects<Node*>* curr = nodes[n1].adjacencyList;
      bool found = 0;
      while(curr != nullptr){
        if(curr->object->value == n2+1){
          found = 1;
          break;
        }
        curr = curr->next;
      }
      if(found) continue;

      nodes[n1].insert_adj(&nodes[n2]);
      nodes[n2].insert_adj(&nodes[n1]);

      graphFile << n1+1 << " " << n2+1 << endl;
      countEdges++;
    }
  }
      
  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;
  }

  void DFSRecurse(int v, BST* tree);

  void modifiedDFS();
  void printResults();

};

#endif
