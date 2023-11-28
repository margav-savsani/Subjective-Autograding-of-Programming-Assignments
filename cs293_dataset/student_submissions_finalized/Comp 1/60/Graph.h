#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

class BSTNode
{
public:
  int value;
  BSTNode *leftNode, *rightNode;

  BSTNode(int val)
  {
    value = val;
    leftNode = NULL;
    rightNode = NULL;
  }
};

class BST
{
public:
  BSTNode *root;

  BST()
  {
    root = NULL;
  }

  void insert(int val)
  {
    if (root == NULL)
    {
      root = new BSTNode(val);
    }
    else
    {
      BSTNode *temp = root;
      while (true)
      {
        if (val < temp->value) //left insertion
        {
          if (temp->leftNode != NULL)
          {
            temp = temp->leftNode;
          }
          else
          {
            temp->leftNode = new BSTNode(val);
            break;
          }
        }
        else if (val >= temp->value) //right insertion
        {
          if (temp->rightNode != NULL)
          {
            temp = temp->rightNode;
          }
          else
          {
            temp->rightNode = new BSTNode(val);
            break;
          }
        }
        break;
      }
    }
  }
  void printBinaryTree(BSTNode *root, const string &prefix, bool isLeft)
  {
    if (root != nullptr)
    {
      cout << prefix;

      cout << (isLeft ? "|--" : "|__");

      // print the value of the node
      cout << root->value;
      cout << endl;
      BSTNode *curr = root;
      root = root->leftNode;
      // enter the next tree level - left and right branch
      printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), true);
      root = curr->rightNode;
      printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), false);
      root = curr;
    }
    else
    {
      cout << "NULL tree" << endl;
    }
  }
};

class Node
{
public:
  int value;

  // insert other fields and methods as appropriate
};

class Graph
{
  int numNodes;
  int numEdges;
  int numComp;
  int numOnce;
  int numTwice;
  int numNodes_Cycle;
  fstream graphFile;
  int *adjacencyMatrix;
  int *visited;
  BST * Tree;
  Node *nodes;

  // Add appropriate fields as necessary for your implementation

public:
  Graph(int nNodes, int nEdges, string gFileName)
  {
    numNodes = nNodes;
    numEdges = nEdges;
    numComp = 0; //number of connected components
    numOnce = 0; //number of once visited
    numTwice = 0; //number of twice visited
    numNodes_Cycle = 0;
    Tree = new BST();
    adjacencyMatrix = new int[nNodes * nNodes];
    visited = new int[nNodes];
    int N = nNodes;
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
      {
        adjacencyMatrix[i * N + j] = 0;
      }
      visited[i] = 0;
    }
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
      if (adjacencyMatrix[n1 * N + n2] == 1)
      {
        continue;
      }
      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that valuermation to
      // graphFile

      adjacencyMatrix[n1 * N + n2] = 1;
      adjacencyMatrix[n2 * N + n1] = 1;
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
  void DFS(int v);
};

#endif
