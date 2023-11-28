#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

template <typename T> class linkedListNode {
 public:
  T data;
  linkedListNode<T> *next;
  linkedListNode<T> *prev;
  
  // Constructor
  linkedListNode(T initValue) {data = initValue; next = prev = nullptr;}
  
  // Destructor
  ~linkedListNode() {;}
};

struct TreeNode{
  int value;
  TreeNode* left;
  TreeNode* right;

  TreeNode(int value){
    this->value = value;
    left = nullptr;
    right = nullptr;
  }
};

class BST {
  // Add your own field and members here
  TreeNode* root; // Root of tree

 public:
  BST(){
    root = nullptr;
  }

  BST(TreeNode* root){
    this->root = root;
  }

  // Function to insert (val) into BST
  void insert(int val){
    if(root == nullptr){
      root = new TreeNode(val);
      return;
    }

    TreeNode* cnode = root;
    TreeNode* pnode = nullptr;
    while(cnode != nullptr){
      if(val < cnode->value){
        pnode = cnode;
        cnode = cnode->left;
      } else{
        pnode = cnode;
        cnode = cnode->right;
      }
    }
    if(val < pnode->value){
      pnode->left = new TreeNode(val);
    } else{
      pnode->right = new TreeNode(val);
    }
  }

  // Feel free to use the printBST function used earlier
  void printBST(const string& prefix, bool isLeft=false){
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << '('<< root->value<<')' << endl;
        TreeNode *curr = root;
        root = root->left;
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
  int value;

  // insert other fields and methods as appropriate
  int visitedCount = 0; // Number of times node is visited
  int dfs_parents[2] = {-1, -1}; // Parents of node; -1 if none
  linkedListNode<int>* adjacencyListHead = nullptr; // Adjaceny list
  int numTimesOnPath = 0; // Number of times node is in current path
  bool isCycleNode = false; // Is the node part of a cycle?
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;

  // Add appropriate fields as necessary for your implementation
  int numConnectedComponents = 0; // Number of connected components in the graph
  linkedListNode<BST>* components = nullptr; // A BST for each component; list of such BSTs
  linkedListNode<int>* path = nullptr; // Current path from source to current node in DFS

  void modifiedDFSHelper(int currNodeIdx); // Modified DFS Helper function
  
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

      bool insertable = true; // If edge can be inserted
      linkedListNode<int>* cllnode = nodes[n1].adjacencyListHead;
      while(cllnode != nullptr){
        if(cllnode->data == n2){ // If edge from same node to itself
          insertable = false;
          break;
        }
        cllnode = cllnode->next;
      }

      if(insertable){
        // Insert new node into head of adjacency list
        if(nodes[n1].adjacencyListHead == nullptr){
          nodes[n1].adjacencyListHead = new linkedListNode(n2);
        } else{
          linkedListNode<int>* newNode = new linkedListNode(n2);
          newNode->next = nodes[n1].adjacencyListHead;
          nodes[n1].adjacencyListHead->prev = newNode;
          nodes[n1].adjacencyListHead = newNode;
        }

        // Insert new node into head of adjacency list
        if(nodes[n2].adjacencyListHead == nullptr){
          nodes[n2].adjacencyListHead = new linkedListNode(n1);
        } else{
          linkedListNode<int>* newNode = new linkedListNode(n1);
          newNode->next = nodes[n2].adjacencyListHead;
          nodes[n2].adjacencyListHead->prev = newNode;
          nodes[n2].adjacencyListHead = newNode;
        }

        graphFile << n1+1 << " " << n2+1 << endl;
        countEdges++;
      }
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
};

#endif
