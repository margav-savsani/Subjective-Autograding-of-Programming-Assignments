#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

struct TreeNode
{

  int value;
  TreeNode *left;   // Left Child of this Node (nullptr, if None)
  TreeNode *right;  // Right Child of this Node (nullptr, if None)
  TreeNode *parent; // The Parent Node, nullptr in case of Root

  // Constructors

  TreeNode() : value(0), left(nullptr), right(nullptr) {}
  TreeNode(int given) : value(given), left(nullptr), right(nullptr) {}
};

class BST
{
  public:
  TreeNode *root;

  BST() { root = nullptr; }

  BST(TreeNode *root)
  {
    this->root = root;
  }
  
  TreeNode *search(TreeNode *T, int value)
  {
    if (T == nullptr)
    {
      return nullptr;
    }
    if (T->value == value)
      return T;
    if (T->value < value)
    {
      return search(T->right, value);
    }
    else
      return search(T->left, value);
  }
  void insert(int value)
  {
    TreeNode *newnode = new TreeNode(value);
    newnode->parent = nullptr;
    if (root == nullptr)
    {
      root = new TreeNode(value);
      root->parent = nullptr;
      return;
    }
    TreeNode *T = root;
    TreeNode *temp;
    while (T != nullptr)
    {
      temp = T;
      if (value < T->value)
        T = T->left;
      else
        T = T->right;
    }
    if (value < temp->value)
    {
      temp->left = newnode;
      newnode->parent = temp;
      return;
    }
    else
    {
      temp->right = newnode;
      newnode->parent = temp;
      return;
    }
  }

  bool find(int value)
  {
    if (search(root, value) == nullptr)
      return false;
    else
    {
      return true;
    }
  }

  void printBST(const string &prefix, bool isLeft )
  {
    if (root != nullptr)
    {
      cout << prefix;

      cout << (isLeft ? "|--" : "|__");

      // print the value of the node
      cout << root->value << endl;
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

class Node
{
public:
  int value;
  int visit = 0;
  int color = 0;
  listOfObjects<Node *> *adj_lists;
  // insert other fields and methods as appropriate
};

class Graph
{
  int numNodes;
  int numEdges;
  fstream graphFile;
  Node *nodes;
  BST *AllTrees;
  bool *inCycle;
  // Add appropriate fields as necessary for your implementation

public:
  Graph(int nNodes, int nEdges, string gFileName)
  {
    numNodes = nNodes;
    numEdges = nEdges;
    AllTrees = new BST[nNodes];
    inCycle = new bool[nNodes];
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
      inCycle[i] = false;
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

      bool found = false;
      if (nodes[n1].adj_lists == nullptr)
      {
        nodes[n1].adj_lists = new listOfObjects<Node *>(&nodes[n2]);
      }
      else
      {
        listOfObjects<Node *> *store = nodes[n1].adj_lists;
        while (store != nullptr)
        {
          if (store->object == &nodes[n2])
          {
            found = true;
            break;
          }
          store = store->next;
        }
        if (found)
          continue;
        listOfObjects<Node *> *start = new listOfObjects<Node *>(&nodes[n2]);
        start->next = nodes[n1].adj_lists;
        nodes[n1].adj_lists->prev = start;
        nodes[n1].adj_lists = start;
      }

      if (nodes[n2].adj_lists == nullptr)
      {
        nodes[n2].adj_lists = new listOfObjects<Node *>(&nodes[n1]);
      }
      else
      {
        listOfObjects<Node *> *start = new listOfObjects<Node *>(&nodes[n1]);
        start->next = nodes[n2].adj_lists;
        nodes[n2].adj_lists->prev = start;
        nodes[n2].adj_lists = start;
      }
      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile

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
  BST *DFS(Node *v, BST *tree, Node *u);
};

#endif
