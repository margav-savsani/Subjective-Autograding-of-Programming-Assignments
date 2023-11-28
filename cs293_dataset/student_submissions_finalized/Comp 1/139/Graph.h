#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <list>
#include <vector>

struct TreeNode
{
  int value;        // value
  TreeNode *left;   // Left Child of this Node (NULL, if None)
  TreeNode *right;  // Right Child of this Node (NULL, if None)
  TreeNode *parent; // The Parent Node, NULL in case of Root

  // Constructors

  TreeNode() : value(0), left(nullptr), right(nullptr) {}
  TreeNode(int value) : value(value), left(nullptr), right(nullptr) {}
  TreeNode(int value, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : value(value), left(leftChild), right(rightChild), parent(parent) {}
};

class BST
{
  TreeNode *root;
  int *A;
  // result variable is for testing purposes, Do not tamper with it!
  vector<string> result;

public:
  BST() {}
  BST(TreeNode *root)
  {
    this->root = root;
  };
  void printBST(const string &prefix, bool isLeft);
  void getBST(const string &prefix, bool isLeft);
  void clearResult();
  vector<string> getResult();
  bool insert(int value);
};

class Node
{
public:
  int value, visits;
  list<Node *> adj, a; // a-original list of all adjacent nodes, adj-copy of a used for manuplation.
  int color;           // used for other DFS(Cycles) function.
  Node *parent;        // used for other DFS(Cycles) function.
  Node()
  {
    color = 0;
    visits = 0;
  }
  // inserts the respective node into both arrays.
  void insert_adj(Node *node)
  {
    adj.push_back(node);
    a.push_back(node);
  }

  // checks whether the node is already
  bool check(Node *node)
  {
    bool found = false;
    for (auto const &i : adj)
    {
      if (i->value == node->value)
      {
        found = true;
        break;
      }
    }
    return found;
  }
};

class Graph
{
  list<BST *> trees; // list of trees
  int numNodes, numEdges, conn;
  fstream graphFile;
  Node *nodes;
  vector<list<Node *>> cycles; // cycles list

public:
  Graph(int nNodes, int nEdges, string gFileName)
  {
    conn = 0;
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

      // checking if already the neighbouring nodes present or not.
      if (nodes[n1].check(&nodes[n2]))
        continue;

      // else, proceeding by adding both into respective adjacent lists
      nodes[n1].insert_adj(&nodes[n2]);
      nodes[n2].insert_adj(&nodes[n1]);

      graphFile
          << n1 + 1 << " " << n2 + 1 << endl;
      countEdges++;
    }
    // for (int i = 0; i < numNodes; i++)
    // {
    //   cout << nodes[i].value << "->";
    //   for (auto const &i : nodes[i].adj)
    //   {
    //     std::cout << i->value << ", ";
    //   }
    //   cout << endl;
    // }
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

  void modifiedDFS();
  int computeCycles(int &cyclenumber);                     // for computing no.of nodes present in cycles
  void Cycles(Node *node, Node *parent, int &cyclenumber); // A second DFS function which runs on other parameters of Node class
  void printResults();                                     // for printing results
};

#endif
