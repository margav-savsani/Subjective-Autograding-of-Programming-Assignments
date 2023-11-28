#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

// Nodes for BST
struct BST_nodes
{

  int value;
  BST_nodes *left;   // Left Child of this Node (NULL, if None)
  BST_nodes *right;  // Right Child of this Node (NULL, if None)
  BST_nodes *parent; // Parent of child

  // Constructor for the node
  BST_nodes(int val)
  {
    value = val;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
  }
};

// BST tree class, same as done in lab3 (almost)
class BST
{
  // storing the root
  BST_nodes *root;

public:
  // constructors
  BST()
  {
    root = NULL;
  }

  // parametrised constructor
  BST(BST_nodes *root)
  {
    this->root = root;
  }

  bool insert(int val)
  {
    // Now we know that it surely isn't present
    // Firstly finding the location where we need it to be there, and then adding(inserting at that location)
    BST_nodes *finder, *parent = NULL;
    finder = root;
    while (finder != NULL)
    {
      parent = finder;
      if (finder->value >= val)
      {
        finder = finder->left;
      }
      else if (finder->value < val)
      {
        finder = finder->right;
      }
    }

    // Handling the case of same value but different journey code too, by putting that in the left tree
    BST_nodes *element = new BST_nodes(val);
    if (parent != NULL)
    {
      element->parent = parent;
      if (parent->value >= val)
      {
        parent->left = element;
      }
      else
      {
        parent->right = element;
      }
    }
    else
    {
      root = element;
      element->parent = NULL;
    }
    return true;
  }

  // Print function of BST
  void printBST(const string &prefix, bool isLeft)
  {
    if (root != nullptr)
    {
      cout << prefix;

      cout << (isLeft ? "|--" : "|__");

      // print the value of the node
      cout << root->value << endl;
      BST_nodes *curr = root;
      root = root->left;
      // enter the next tree level - left and right branch
      printBST(prefix + (isLeft ? "│   " : "    "), true);
      root = curr->right;
      printBST(prefix + (isLeft ? "│   " : "    "), false);
      root = curr;
    }
  }

  // Feel free to use the printBST function used earlier
};

// Class that will node of the list that will store numerous BSTs
struct listofBST
{
  BST *elem;
  listofBST *next;
  listofBST *prev;
  listofBST()
  {
    next = nullptr;
    prev = nullptr;
    elem = new BST();
  }
};

// This class will be used to make node for the stack
struct stackss
{
  stackss *next;
  stackss *prev;
  int idx;

  stackss(int id)
  {
    idx = id;
    next = nullptr;
    prev = nullptr;
  }
};

// Node that will be used in my adjacency list
class adj_node
{
public:
  adj_node *next;
  adj_node *prev;
  int idx_val;

  adj_node(int val, adj_node *nx = nullptr, adj_node *pv = nullptr)
  {
    idx_val = val;
    next = nx;
    prev = pv;
  }
};

class Node
{
public:
  int value;

  // insert other fields and methods as appropriate
  adj_node *adjs;
  adj_node *last;

  int in_stack;
  int p1;
  int p2;
};

class Graph
{
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;

  // Add appropriate fields as necessary for your implementation
  int connected;
  int visited_once;
  int visited_twice;
  int in_cycle;

  listofBST *treesstart = nullptr;
  listofBST *treesend = nullptr;

  // Count number of times a node is visited
  int *visited;

  // To make sure each connected component is dealed with
  int *conn_comp;

  // To count the number of nodes as part of a cycle
  bool *cycle;

  stackss *stk;

public:
  Graph(int nNodes, int nEdges, string gFileName)
  {
    visited = new int[nNodes];
    conn_comp = new int[nNodes];
    cycle = new bool[nNodes];
    stk = nullptr;

    // Initialising them
    for (int i = 0; i < nNodes; i++)
    {
      visited[i] = 0;
      conn_comp[i] = -1;
      cycle[i] = 0;
    }

    // Initialising the connected
    connected = 0;

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
      // Added this here
      nodes[i].in_stack = 0;

      nodes[i].p1 = -1;
      nodes[i].p2 = -1;
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

      // Checking if the edge already exists or not
      adj_node *iter = nodes[n1].adjs;
      while (iter != nullptr)
      {
        if (iter->idx_val == n2)
        {
          break;
        }
        iter = iter->next;
      }
      if (iter != nullptr)
        continue;

      // Adding the elements in the adjacency list
      adj_node *temp1 = new adj_node(n2);
      if (nodes[n1].last == nullptr)
      {
        nodes[n1].adjs = temp1;
        nodes[n1].last = temp1;
      }
      else
      {
        // Making sure connections are properly made of next and previous
        nodes[n1].last->next = temp1;
        temp1->prev = nodes[n1].last;
        nodes[n1].last = temp1;
      }

      adj_node *temp2 = new adj_node(n1);
      if (nodes[n2].last == nullptr)
      {
        nodes[n2].adjs = temp2;
        nodes[n2].last = temp2;
      }
      else
      {
        nodes[n2].last->next = temp2;
        temp2->prev = nodes[n2].last;
        nodes[n2].last = temp2;
      }

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
  void myDFS(int parent, int curr, BST &tree);
};

#endif
