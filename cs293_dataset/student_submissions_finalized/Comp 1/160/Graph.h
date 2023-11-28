#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
// this is node for tree of BST
struct TreeNode
{
  int value;
  TreeNode *left;   // left child
  TreeNode *right;  // right child
  TreeNode *parent; // parent of node
  TreeNode(int x)
  { // constructor
    value = x;
    left = right = parent = nullptr;
  }
  TreeNode()
  { // constructor
    value = 0;
    left = right = parent = nullptr;
  }
};

class BST
{
  // Add your own field and members here

  TreeNode *root; // root of tree

public:
  BST()
  { // constructor
    root = nullptr;
  }
  bool insert(int value);
  void printBST(const string &prefix, bool isLeft = false);
  // Feel free to use the printBST function used earlier
};

class connected
{ // this is class to store BSTs as linked list
public:
  BST *tree;
  connected *next;
  connected()
  { // constructor
    tree = new BST();
    next = nullptr;
  }
};
class Node
{ // this is node for graph
public:
  int value;                // value contained in the node
  int visitcount = 0;       // contains the number of visits a node does in DFS
  bool present_cycle = 0;   // tells whether it is part of a cycle or not
  int colour = 0;           // using color for determining part of cycle or not
  int previous = 0;         // contains the parent node value if traversed in normal dfs way
  int *adjacency = nullptr; // contains adjacency list of this node according to graph
  int *path = nullptr;      // contains the path occured in modified bfs from the given node
  // insert other fields and methods as appropriate
};

class Graph
{
  int numNodes;
  int numEdges;
  fstream graphFile;
  Node *nodes;
  int connected_component = 0; // determine the number of connected components
  // Add appropriate fields as necessary for your implementation
  connected *start = nullptr; // for easy navigation for storing trees in linked list
  connected *end = nullptr;

public:
  Graph(int nNodes, int nEdges, string gFileName)
  {
    numNodes = nNodes;
    numEdges = nEdges;
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
      nodes[i].value = i + 1;
      nodes[i].adjacency = new int[numNodes];
      nodes[i].path = new int[numNodes];
    }

    srand(time(0));
    int n1 = 0, n2 = 0;
    int countEdges = 0;

    while (countEdges < numEdges)
    {
      do
      {
        n1 = rand() % numNodes;
        n2 = rand() % numNodes;
      } while (n1 == n2 || nodes[n1].adjacency[n2] == 1);

      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile
      nodes[n1].adjacency[n2] = 1;
      nodes[n2].adjacency[n1] = 1;
      graphFile << n1 + 1 << " " << n2 + 1 << endl;
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
  void DFS(int vertex, BST *tree, int prev);
  void cycle(int vertex, int prev);
};

#endif
