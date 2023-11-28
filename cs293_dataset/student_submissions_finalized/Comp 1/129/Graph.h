#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
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
struct TreeNode
{
  // Journey code
  int value;        // Price
  TreeNode *left;   // Left Child of this Node (NULL, if None)
  TreeNode *right;  // Right Child of this Node (NULL, if None)
  TreeNode *parent; // The Parent Node, NULL in case of Root

  // Constructors: There are 3 variants of the constructor given below.
  // Please make sure you understand what each of these variants do.
  // Ask your TA or the instructor if you have a doubt.

  TreeNode() : value(0), left(nullptr), right(nullptr), parent(nullptr) {}

  TreeNode(int price) : value(price), left(nullptr), right(nullptr), parent(nullptr) {}

  TreeNode(int price, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : value(price), left(leftChild), right(rightChild), parent(parent) {}
};

// Add your own field and members here

// Feel free to use the printBST function used earlier

class Node
{
public:
  int value;

  listOfObjects<int> *adjacenthead;
  listOfObjects<int> *adjacenttail;

  // Node *predecessor;

  Node()
  {
    value = 0;

    adjacenthead = nullptr;
    adjacenttail = nullptr;
  }
  Node(int value)
  {
    this->value = value;

    adjacenthead = nullptr;
    adjacenttail = nullptr;
  }

  // insert other fields and methods as appropriate
};
class BST
{
public:
  BST *next;
  TreeNode *root;
  BST()
  {
    root = nullptr;
    next = nullptr;
  }
  BST(TreeNode *root)
  {
    this->root = root;
    next = nullptr;
  }
  void printBST(const string &prefix, bool isLeft = false)
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
  bool insert(int value) // inserting a node
  {

    // Node *y = new Node;
    // y->left=nullptr
    TreeNode *res = new TreeNode;
    TreeNode *y = nullptr;

    if (root == nullptr) // inserting at root
    {
      root = new TreeNode(value);

      return true;
    }

    else
    {

      TreeNode *x = root;
      // if (c value, x)) // if a journey code is present , insertion failed
      // {
      //   return false;
      // }
      while (x != nullptr) // if prices are same insert at right
      {

        if (value >= x->value)
        {
          y = x;
          x = x->right;
        }
        else if (value < x->value)
        {
          y = x;
          x = x->left;
        }
      }
      if (value < y->value)
      {
        res->parent = y;
        y->left = res;

        res->value = value;
      }
      else
      {
        res->parent = y;
        y->right = res;

        res->value = value;
      }
    }

    return true;
  }
};

class Graph
{
public:
  int numNodes;
  int numEdges;
  fstream graphFile;
  BST *head;
  BST *tail;
  int ans1;
  int *predecessor;
  Node *nodes;
  int *time_arr;
  int time1;
  bool *incycle;
  int *visited;

  // Add appropriate fields as necessary for your implementation

  Graph(int nNodes, int nEdges, string gFileName)
  {
    time1 = 0;
    ans1 = 0;
    numNodes = nNodes;
    numEdges = nEdges;
    graphFile.open(gFileName, ios::out);
    head = nullptr;
    tail = nullptr;
    if (!graphFile.is_open())
    {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }

    graphFile << numNodes << endl;
    graphFile << numEdges << endl;

    nodes = new Node[numNodes];
    predecessor = new int[numNodes];
    time_arr = new int[numNodes];
    incycle = new bool[numNodes];
    visited = new int[numNodes];

    if (nodes == nullptr)
    {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++)
    {
      nodes[i].value = i + 1;
      predecessor[i] = -1;
      time_arr[i] = -1;
      visited[i] = 0;
      incycle[i] = false;
    }

    srand(time(0));

    int n1, n2;
    int countEdges = 0;

    while (countEdges < numEdges)
    {
      do
      {
        // cin>>n1>>n2;
        // n1--;
        // n2--;
        n1 = rand() % numNodes;
        n2 = rand() % numNodes;
      } while (n1 == n2);
      bool a = false;
      listOfObjects<int> *garb = nodes[n1].adjacenthead;
      while (garb != nullptr)
      {
        if (garb->object == n2)
        {
          a = true;

          break;
        }
        garb = garb->next;
      }

      if (!a)
      {
        if (nodes[n1].adjacenthead == nullptr && nodes[n2].adjacenthead == nullptr)
        {
          nodes[n1].adjacenthead = new listOfObjects<int>(n2);
          nodes[n1].adjacenttail = nodes[n1].adjacenthead;
          nodes[n2].adjacenthead = new listOfObjects<int>(n1);
          nodes[n2].adjacenttail = nodes[n2].adjacenthead;
        }
        else if (nodes[n1].adjacenthead != nullptr && nodes[n2].adjacenthead == nullptr)
        {
          nodes[n1].adjacenttail->next = new listOfObjects<int>(n2);
          nodes[n1].adjacenttail = nodes[n1].adjacenttail->next;
          nodes[n2].adjacenthead = new listOfObjects<int>(n1);
          nodes[n2].adjacenttail = nodes[n2].adjacenthead;
        }
        else if (nodes[n1].adjacenthead == nullptr && nodes[n2].adjacenthead != nullptr)
        {
          nodes[n1].adjacenthead = new listOfObjects<int>(n2);
          nodes[n1].adjacenttail = nodes[n1].adjacenthead;
          nodes[n2].adjacenttail->next = new listOfObjects<int>(n1);
          nodes[n2].adjacenttail = nodes[n2].adjacenttail->next;
        }
        else
        {
          nodes[n1].adjacenttail->next = new listOfObjects<int>(n2);
          nodes[n1].adjacenttail = nodes[n1].adjacenttail->next;
          nodes[n2].adjacenttail->next = new listOfObjects<int>(n1);
          nodes[n2].adjacenttail = nodes[n2].adjacenttail->next;
        }

        graphFile << n1 + 1 << " " << n2 + 1 << endl;
        // graphFile << countEdges << endl;
        countEdges++;
      }

      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile
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

  void myDFS(Node node, BST *tree);
  bool check_ancestor(int x1,int x2);
  int lca(int x1, int x2);

  void modifiedDFS();
  void printResults();
};

#endif
