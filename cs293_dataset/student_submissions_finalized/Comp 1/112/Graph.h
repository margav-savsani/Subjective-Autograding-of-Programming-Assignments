#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

// same old list implementation
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

// BST Node
struct TreeNode
{
  int value;        // Value
  TreeNode *left;   // Left Child of this Node (nullptr, if None)
  TreeNode *right;  // Right Child of this Node (nullptr, if None)
  TreeNode *parent; // The Parent Node, nullptr in case of Root

  // Constructors
  TreeNode(int vlue) : value(vlue), left(nullptr), right(nullptr), parent(nullptr) {}
  TreeNode(int vlue, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : value(vlue), left(leftChild), right(rightChild), parent(parent) {}
};

class BST
{
  TreeNode *root;

public:
  BST() { root = nullptr; }
  BST(TreeNode *root) { this->root = root; }

  // This function prints the BST using ASCII characters using the
  // format:
  //
  //   root
  //       |-- left subtree
  //       |__ right subtree
  //
  // where the left and right subtrees are printed recursively in
  // the same format.
  //
  // We have done this for you! Please see BST.cpp for details
  // You may use this for debugging purposes.
  void printBST(const string &prefix, bool isLeft)
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

  // Returns false, if given value is already present in the BST
  // Inserts the element and returns True otherwise
  bool insert(int value)
  {
    // Adding the first node
    if (root == nullptr)
    {
      root = new TreeNode(value);
      return true;
    }
    TreeNode *curr = root;
    while (true)
    {
      // Moving to the right, if value is greater
      if (value > curr->value)
      {
        if (curr->right != nullptr)
        {
          curr = curr->right;
        }
        else
        {
          curr->right = new TreeNode(value, nullptr, nullptr, curr);
          break;
        }
      }
      else
      {
        // moving to left if its smaller
        if (curr->left != nullptr)
        {
          curr = curr->left;
        }
        else
        {
          curr->left = new TreeNode(value, nullptr, nullptr, curr);
          break;
        }
      }
    }
    //  this->printBST("",false);
    return true;
  }
};

class Node
{
public:
  int value;
  bool inCycle;      // whether this node is in a cycle
  int numVisits;     // number of visits paid to this node so far
  bool *forbidden;   // some of its neighbours will be forbidden, since we can only revisit a node along directed tree edges
  int numNeighbours; // number of neighbours of this node

  Node()
  {
    value = -1; // a node should not finally have a value of -1. This is a warning sign for debugging
    inCycle = false;
    numVisits = 0;
    forbidden = nullptr;
    numNeighbours = 0;
  }
};

class Graph
{
  int numComp; // number of connected components
  int numNodes;
  int numEdges;
  listOfObjects<Node *> **adjacencyListArr; // adjacencyListArr[i] will give the neighbours of the ith node
  listOfObjects<BST *> *components;         // one tree for each component
  fstream graphFile;
  Node *nodes;

public:
  Graph(int nNodes, int nEdges, string gFileName)
  {
    // initializing to 0 or nullptr
    numComp = 0;
    components = nullptr;
    numNodes = nNodes;
    numEdges = nEdges;
    adjacencyListArr = new listOfObjects<Node *> *[nNodes]();
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
      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile

      bool connected; // if n1 and n2 are already connected, we need to choose a different pair (n1,n2)
      do
      {
        connected = false;
        n1 = rand() % numNodes;
        n2 = rand() % numNodes;
        listOfObjects<Node *> *n1Neighbour = adjacencyListArr[n1];
        while (n1Neighbour != nullptr) // checking if n2 is n1's neighbour
        {
          if (n1Neighbour->object->value - 1 == n2)
          {
            connected = true;
            break;
          }
          n1Neighbour = n1Neighbour->next;
        }

      } while (n1 == n2 || connected);

      // update n1's neighbour list
      if (adjacencyListArr[n1] == nullptr)
      {
        adjacencyListArr[n1] = new listOfObjects<Node *>(&(nodes[n2]));
      }
      else
      {
        adjacencyListArr[n1]->prev = new listOfObjects<Node *>(&(nodes[n2]));
        adjacencyListArr[n1]->prev->next = adjacencyListArr[n1];
        adjacencyListArr[n1] = adjacencyListArr[n1]->prev;
      }

      // update n2's neighbour list
      if (adjacencyListArr[n2] == nullptr)
      {
        adjacencyListArr[n2] = new listOfObjects<Node *>(&(nodes[n1]));
      }
      else
      {
        adjacencyListArr[n2]->prev = new listOfObjects<Node *>(&(nodes[n1]));
        adjacencyListArr[n2]->prev->next = adjacencyListArr[n2];
        adjacencyListArr[n2] = adjacencyListArr[n2]->prev;
      }
      nodes[n1].numNeighbours++;
      nodes[n2].numNeighbours++;
      graphFile << n1 + 1 << " " << n2 + 1 << endl;
      countEdges++;
    }
    for (int i = 0; i < numNodes; i++)
    {
      if (!(nodes[i].numNeighbours == 0))
      {
        nodes[i].forbidden = new bool[nodes[i].numNeighbours];
      }
      // initializing all to false
      for (int j = 0; j < nodes[i].numNeighbours; j++)
      {
        nodes[i].forbidden[j] = false; // not forbidden
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

  BST *myDFS(BST *myBST, int currNode, bool topLevelCall);
  void modifiedDFS();
  void printResults();
};

#endif
