#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

/*
pending
  BST object in graph class
  bst class
  dfs
  print
*/

template <typename T>
class listOfObjects
{
public:
  T object;
  listOfObjects<T> *next;
  listOfObjects<T> *prev;

  // Constructor
  listOfObjects(T initValue)
  {
    object = initValue;
    next = prev = nullptr;
  }

  // Destructor
  ~listOfObjects() { ; }
};

struct BSTNode
{
  int value;
  BSTNode *left;   // Left Child of this Node (NULL, if None)
  BSTNode *right;  // Right Child of this Node (NULL, if None)
  BSTNode *parent; // The Parent Node, NULL in case of Root

  // Constructors

  BSTNode() : value(0), left(nullptr), right(nullptr) {}
  BSTNode(int val) : value(val), left(nullptr), right(nullptr) {}
  BSTNode(int val, BSTNode *leftChild, BSTNode *rightChild, BSTNode *parent) : value(val), left(leftChild), right(rightChild), parent(parent) {}
};

class BST
{
public:
  // Add your own field and members here
  BSTNode *root;
  // Feel free to use the printBST function used earlier
  BST(BSTNode *root)
  {
    this->root = root;
  }

  bool insert(int val)
  {
    if (root == nullptr)
    {
      root = new BSTNode(val);
      return true;
    }

    BSTNode *temp = root;

    while (true)
    {
      if (val <= temp->value)
      {
        if (temp->left == nullptr)
        {
          temp->left = new BSTNode(val);
          temp->left->parent = temp;
          return true;
        }
        else
        {
          temp = temp->left;
          continue;
        }
      }
      else
      {
        if (temp->right == nullptr)
        {
          temp->right = new BSTNode(val);
          temp->right->parent = temp;
          return true;
        }
        else
        {
          temp = temp->right;
          continue;
        }
      }
    }
  }

  void printBST(const string &prefix, bool isLeft = false)
  {
    if (root != nullptr)
    {
      cout << prefix;

      cout << (isLeft ? "|--" : "|__");

      // print the value of the node
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
  int visit;  // used in DFS or tree
  Node *next; // used in DFS or tree
  bool connectedcompenent;
  listOfObjects<Node *> *adjacencylist; // used in constructing graph  and in DFS
  listOfObjects<Node *> *tailofadjlist; // used in constructing graph
  int arr[2] = {0, 0};
  int dep[2] = {0, 0};

  Node()
  {
    visit = 0;
    next = nullptr;
    connectedcompenent = false;
    adjacencylist = nullptr;
    tailofadjlist = nullptr;
  }
  void add_adjnode(Node *adj)
  {
    if (adjacencylist == nullptr)
    {
      adjacencylist = new listOfObjects<Node *>(adj);
      tailofadjlist = adjacencylist;
    }
    else
    {
      tailofadjlist->next = new listOfObjects<Node *>(adj);
      tailofadjlist = tailofadjlist->next;
    }
  }

  // insert other fields and methods as appropriate
};

class Graph
{
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;
  listOfObjects<BST *> *Trees;
  // Add appropriate fields as necessary for your implementation

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
      listOfObjects<Node *> *list = nodes[n1].adjacencylist;
      bool edgeexist = 0;
      while (list != nullptr)
      {
        if (list->object->value == n2 + 1)
        {
          edgeexist = true;
        }
        list = list->next;
      }
      if (edgeexist)
      {
        continue;
      }
      else
      {
        nodes[n1].add_adjnode(nodes + n2);
        nodes[n2].add_adjnode(nodes + n1);
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
  int DFS(int init, BST *tree, int parent, int timestamp);
  void printResults();
};

#endif
