#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

struct TreeNode
{
  int value;
  TreeNode *left;   // Left Child of this Node (NULL, if None)
  TreeNode *right;  // Right Child of this Node (NULL, if None)
  TreeNode *parent; // The Parent Node, NULL in case of Root
  // Constructors
  TreeNode() : value(0), left(nullptr), right(nullptr) {}
  TreeNode(int Value) : value(Value), left(nullptr), right(nullptr) {}
  TreeNode(int Value, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : value(Value), left(leftChild), right(rightChild), parent(parent) {}
};

class BST
{
public:
  TreeNode *root;

  // Constructors!
  BST() { root = NULL; };
  BST(TreeNode *root) { this->root = root; }

  void printBST(const string &prefix, bool isLeft);

  void insert(int value);
};

class Node
{
public:
  int value;
  int neighbours;
  Node **adjacent;
  int visited;
  int cycle = 0;
  int parent1;
  int parent2;
  // insert other fields and methods as appropriate
  Node()
  {
    value = 0;
  }
  Node(int v)
  {
    value = v;
    neighbours = 0;
    visited = 0;
    cycle = 0;
    parent1 = -1;
    parent2 = -1;
  }
};

class Graph
{
  int numNodes;
  int numEdges;
  fstream graphFile;

  int cyclicNodes;
  int once;
  int twice;

  int connected = 0;
  int *visited;
  Node *presentStack;
  int sizeStack;
  int *cyclic;
  int *countStack;

  BST *Trees;

  Node *nodes;

  // Add appropriate fields as necessary for your implementation

public:
  Graph(int nNodes, int nEdges, string gFileName)
  {
    numNodes = nNodes;
    numEdges = nEdges;
    once = 0;
    twice = 0;
    cyclicNodes = 0;
    visited = new int[nNodes];
    cyclic = new int[nNodes];
    countStack = new int[nNodes];
    for (int i =0; i<nNodes;i++){
      visited[i]=0;
      cyclic[i]=0;
      countStack[i]=0;
    }
    presentStack = new Node[2*nNodes];
    sizeStack = 0;
    
    Trees = new BST[nNodes];
    graphFile.open(gFileName, ios::out);
    if (!graphFile.is_open())
    {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }

    graphFile << numNodes << endl;
    graphFile << numEdges << endl;

    nodes = new Node[numNodes];
    if (nodes == nullptr)
    {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++)
    {
      nodes[i] = Node(i + 1);
      nodes[i].adjacent = new Node*[nNodes];
    }

    srand(0);
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
      int already = 0;
      for (int i = 0; i < nodes[n1].neighbours; i++)
      {
        if (nodes[n2].value == nodes[n1].adjacent[i]->value)
        {
          already = 1;
        }
      }
      if (already)
      {
        continue;
      }

      // cout<<"Inserting"<<n1+1<<n2+1<<endl;
      nodes[n1].adjacent[nodes[n1].neighbours] = &nodes[n2];
      nodes[n2].adjacent[nodes[n2].neighbours] = &nodes[n1];
      nodes[n1].neighbours++;
      nodes[n2].neighbours++;

      graphFile << n1 + 1 << " --- " << n2 + 1 << endl;
      countEdges++;
    }

    // Add appropriate code as necessary for your implementation
  }

  ~Graph()
  {
    if (graphFile.is_open())
    {
      graphFile.close();
    }
    delete[] nodes;
    // Add appropriate code as necessary for your implementation
  }

  // Add appropriate method declarations as necessary for your implementation

  void modifiedDFS();
  void printResults();
  void DFS(int current, Node* nodes);
};

#endif
