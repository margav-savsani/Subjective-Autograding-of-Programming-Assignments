#ifndef GRAPH_BST_H
#define GRAPH_BST_H
#include <vector>

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
using namespace std;

class BSTNode  //node for BST
{
public:
  int value;  //value for node
  BSTNode *left;
  BSTNode *right;
  BSTNode *parent;

  BSTNode()   //constructor 1
  {
    value = 0;
    left = right = parent = nullptr;
  }
  BSTNode(int value)  //constructor 2
  {
    this->value = value;
    left = right = parent = nullptr;
  }
};

class BST   //class for BST
{
  BSTNode *root;

public:
  BST()
  {
    root = nullptr;
  }
  BST(BSTNode *root)
  {
    this->root = root;
  }

  void insert(int val)
  {
    BSTNode *node = new BSTNode(val);
    if (root == NULL)  //if root is null
    {
      root = node;
      return;
    }
    BSTNode *prev = NULL;  // previous pointers
    BSTNode *temp = root;
    while (temp != NULL)
    {
      if (temp->value >= val)  //Insert in the left sub tree
      {
        prev = temp;
        temp = temp->left;
      }
      else if (temp->value < val)  //Insert in the right sub tree
      {
        prev = temp;
        temp = temp->right;
      }
    }
    if (prev->value >= val)  //updating the parent
    {
      prev->left = node;
      node->parent = prev;
      return;
    }
    else  
    {
      prev->right = node;
      node->parent = prev;
      return;
    }
  }
  void printBST(const string &prefix, bool isLeft = false) //From lab3
  {
    if (root != nullptr)
    {
      cout << prefix;

      cout << (isLeft ? "|--" : "|__");

      cout << root->value << endl;
      BSTNode *curr = root;
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
  int parent;
  vector<Node *> a; // for storing adjacency lists

  Node() // constructors
  {
    value = -1;
    parent = -1;
  }
  Node(int val)
  {
    value = val;
    parent = -1;
  }
  bool ispresent(int n)  //is present in the adjacency list
  {
    for (int i = 0; i < a.size(); i++)
    {
      if (a[i]->value - 1 == n)

        return true;
    }
    return false;
  }
};

class Graph
{
  int numNodes;
  int numEdges;
  int counter;
  fstream graphFile;
  int *count_visited;  // for counting number of times it is visited
  int *component;      // number of components
  vector<BST *> trees; // All the trees
  int *arrtime;        // arrival times
  int *parents;        // array of parent
  bool *incycle;        // array to represent if the element is present in the cycle

  Node *nodes;  //array of nodes;

public:
  Graph(int nNodes, int nEdges, string gFileName)
  {
    numNodes = nNodes;
    numEdges = nEdges;
    counter = 0;
    count_visited = new int[numNodes]; // new declaration
    component = new int[numNodes];
    arrtime = new int[numNodes];
    parents = new int[numNodes];
    incycle = new bool[numNodes];

    for (int i = 0; i < numNodes; i++)   //initialisations of the member variables
    {
      count_visited[i] = 0;
      component[i] = 0;
      parents[i] = -1;
      arrtime[i] = -1;
      incycle[i] = false;
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

    srand(0);
    int n1, n2;
    int countEdges = 0;

    while (countEdges < numEdges)
    {
      n1 = rand() % numNodes;
      n2 = rand() % numNodes;
      if (n1 != n2 && !nodes[n1].ispresent(n2))
      {
        nodes[n1].a.push_back(&nodes[n2]);
        nodes[n2].a.push_back(&nodes[n1]);

        graphFile << n1 + 1 << " " << n2 + 1 << endl;
        countEdges++;
      }
    }
  }

  ~Graph()
  {
    if (graphFile.is_open())
    {
      graphFile.close();
    }
    delete[] nodes;
  }

  void DFS(int v, int c, BST *tree); //new function to implement modified DFS 

  void modifiedDFS();
  void printResults();
};

#endif
