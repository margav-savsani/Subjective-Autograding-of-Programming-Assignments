#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
using namespace std;
#include "std_headers.h"
#endif
// code that is given from the solutions in Lab3
// I have modified some parts so that it fits .
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
  int **adjlist;  // adjacency matrix for the given Graph
  int **tempadj;  // used this for repeating twice in DFS
  int **counting; // used for counting no of nodes that is present atleast once
  int *visited;   // for storing no of times it is visited and used in DFS
  fstream graphFile;
  int starting = 0;

  Node *nodes;

  // Add appropriate fields as necessary for your implementation

public:
  Graph(int nNodes, int nEdges, string gFileName)
  {
    numNodes = nNodes;
    numEdges = nEdges;
    adjlist = new int *[nNodes];
    visited = new int[nNodes];
    counting = new int *[nNodes];
    for (int i = 0; i < nNodes; i++)
    {
      visited[i] = 0;
      adjlist[i] = new int[nNodes];
      counting[i] = new int[nNodes];
      for (int j = 0; j < nNodes; j++)
      {
        adjlist[i][j] = 0;
        counting[i][j] = 0;
      }
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

      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile
      if (adjlist[n1][n2] == 0)
      {
        adjlist[n1][n2] = 1;
        adjlist[n2][n1] = 1;
        countEdges++;
        graphFile << n1 + 1 << " " << n2 + 1 << endl;
      }
    }
    tempadj = adjlist;

    for (int i = 0; i < numNodes; i++)
    {
      for (int j = 0; j < numNodes; j++)
      {
        counting[i][j] = adjlist[i][j];
        tempadj[i][j] = adjlist[i][j];
      }
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
    for (int i = 0; i < numNodes; i++)
    {
      delete[] adjlist[i];
    }
    delete[] adjlist;
    for (int i = 0; i < numNodes; i++)
    {
      delete[] tempadj[i];
    }
    delete[] tempadj;
    delete visited;
    // Add appropriate code as necessary for your implementation
  }

  // Add appropriate method declarations as necessary for your implementation
  void connectedcomponents();
  void modifiedDFS();
  void printResults();
  int noofcyclicnodes(int number);
};

#endif
