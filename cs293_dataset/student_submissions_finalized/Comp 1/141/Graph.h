#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <cassert>

class BSTNode {
public :   
  int value; 
  BSTNode* left; 
  BSTNode* right; 

  BSTNode(int v) {
    this->value = v; 
    this->left = nullptr; 
    this->right = nullptr;
  }

  void printInfo() {
    std::cout << value;
  }

};

class BST
{
  
  
  public : 
    BSTNode* root; // memory for the root is allocated in the constructor. 
    BST();
    BST (int start);
    void insert(int x);
    void printBST();
    void printBinaryTree(BSTNode *root, const string& prefix, bool isLeft);
    bool BSTLessThan(BSTNode* node1, BSTNode* node2);
};

class Node
{
public:
  // Assumption : Default value is set to 0 
  int value;

  // adjacency list 
  Node* adjacency; 
  int adjcount;
  int curcount;
  int count;
  int* parents;
  int curparents;
  bool cyclic;

  Node(){this->value = 0;}

  void addadjacent(Node node) {
    
    // Assumption : Responsible use of this function -> adds only if not present earlier
    // So blindly add it here. 

    adjacency[curcount] = node;
    curcount++;
    assert(curcount <= adjcount);
  }

  void addparent(int parent) {
    parents[curparents] = parent;
    curparents++;
  }

  bool checkparent(int parent) {
    bool flag = false;
    for (int i = 0; i < curparents; i++) {
      if (parents[i] == parent) {
        flag = true;
        break;
      }
    }

    return flag;
  }

  bool operator== (Node n) {
    if (this->value == n.value) {return true;}
    else return false;
  }
};

class Graph
{
  int numNodes;
  int numEdges;
  fstream graphFile;
  Node *nodes;
  BST* trees;
  int totaltrees;
  int treecount;

public:
  Graph(int nNodes, int nEdges, string gFileName)
  {
    treecount = 0;
    totaltrees = 1;
    numNodes = nNodes;
    numEdges = nEdges;
    // trees initialised at the end of the function.

    graphFile.open(gFileName, ios::out);
    if (!graphFile.is_open())
    {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }

    graphFile << numNodes << endl;
    graphFile << numEdges << endl;

    nodes = new Node [numNodes] ;
    if (nodes == nullptr)
    {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++)
    {
      nodes[i].value = i+1;
      nodes[i].curcount = 0;
      nodes[i].adjcount = numNodes;
      nodes[i].adjacency = new Node[numNodes];
      nodes[i].count = 0;
      nodes[i].parents = new int[numNodes];
      nodes[i].curparents = 0;
      nodes[i].cyclic = 1;
      
    }

    srand(time(0));
    int n1, n2;
    int countEdges = 0;

    while (countEdges < numEdges)
    {
      do
      {
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

      bool flag = false;
      for (int i = 0; i < nodes[n1].curcount; i++) {
        if (nodes[n1].adjacency[i] == nodes[n2]) {
          flag = true;
        }
      }

      if (!flag) {
        nodes[n1].addadjacent(nodes[n2]);
        nodes[n2].addadjacent(nodes[n1]);
      }
      else continue;

      graphFile << n1 + 1 << " " << n2 + 1 << endl;
      countEdges++;
    }

    // Allocated space for BST here. 
    trees = new BST[numNodes];

  }

  ~Graph()
  {
    if (graphFile.is_open())
    {
      graphFile.close();
    }
    // deleting the adjacency as well as the nodes.
    for (int i = 0; i < numNodes; i++) {
      delete[] nodes->adjacency;
    }
    delete[] nodes;
  }

  // Add appropriate method declarations as necessary for your implementation

  void modifiedDFS();
  void printResults();
  int computecycles();
  void DFSvisit(int idx);
};

#endif
