#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
using namespace std;

class Node
{
public:
  int value;
  // insert other fields and methods as appropriate
  // Adjacency list storing neighbours
  int *neighbours;

  // Constructor
  Node() { value = -1; }
  void setSize(int size)
  {
    neighbours = new int[size];
    for (int i = 0; i < size; i++)
    {
      neighbours[i] = 0;
    }
  }
  // Add neighbours to this node
  bool addNeighbours(int node)
  {
    if (neighbours[node] == 1)
    {
      return false;
    }
    else
    {
      neighbours[node] = 1;
      return true;
    }
  }

  void printNeighbours(int size)
  {
    for (int i = 0; i < size; i++)
    {
      cout << neighbours[i] << " ";
    }
    cout << endl;
  }
};

struct TreeNode
{
  Node node;
  TreeNode *left;   // Left Child of this Node (NULL, if None)
  TreeNode *right;  // Right Child of this Node (NULL, if None)
  TreeNode *parent; // The Parent Node, NULL in case of Root
  TreeNode() : node(), left(nullptr), right(nullptr) {}
  TreeNode(Node root) : node(root), left(nullptr), right(nullptr) {}
  TreeNode(Node root, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : node(root), left(leftChild), right(rightChild), parent(parent) {}
};

class BST
{
public:
  TreeNode *root;
  // Add your own field and members here
  // Feel free to use the printBST function used earlier
  BST() { root = nullptr; }
  BST(TreeNode *curr_root) { root = curr_root; }
  ~BST(){};

  bool insert(Node node)
  {
    TreeNode *nodeToInsert = new TreeNode(node);
    if (nodeToInsert == NULL)
    {
      cerr << "Memory allocation failure." << endl;
      return false;
    }
    TreeNode *curr = root;
    TreeNode *parent_curr = nullptr;

    if (root == nullptr)
    {
      root = nodeToInsert;
      return true;
    }
    else
    {
      while (curr != nullptr)
      {
        if (curr->node.value > nodeToInsert->node.value)
        {
          parent_curr = curr;
          curr = curr->left;
        }
        else if (curr->node.value < nodeToInsert->node.value)
        {
          parent_curr = curr;
          curr = curr->right;
        }
        else
        {
          break;
        }
      }
    }

    if (curr == nullptr)
    {
      nodeToInsert->parent = parent_curr;
      if (nodeToInsert->node.value < parent_curr->node.value)
      {
        parent_curr->left = nodeToInsert;
      }
      else if (nodeToInsert->node.value > parent_curr->node.value)
      {
        parent_curr->right = nodeToInsert;
      }
      else
      {
        cerr << "Unexpected branch taken!" << endl;
        return false;
      }
    }
    else
    {
      nodeToInsert->right = curr->right;
      curr->right = nodeToInsert;
      if (nodeToInsert->right != nullptr)
      {
        nodeToInsert->right->parent = nodeToInsert;
      }
      nodeToInsert->parent = curr;
    }
    return true;
  }

  void printBST(const string &prefix, bool isLeft = false)
  {
    if (root != nullptr)
    {
      cout << prefix;

      cout << (isLeft ? "|--" : "|__");

      // print the value of the node
      cout << root->node.value << endl;
      TreeNode *curr = root;
      root = root->left;
      // enter the next tree level - left and right branch
      // Are there any other siblings to the right?
      bool rightSiblingPresent = (isLeft && (curr->parent->right != nullptr));
      printBST(prefix + (rightSiblingPresent ? "│   " : "    "), true);
      root = curr->right;
      printBST(prefix + (rightSiblingPresent ? "│   " : "    "), false);
      root = curr;
      // cout << "================================================================" << endl;
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

class Graph
{
public:
  int numNodes;
  int numEdges;
  fstream graphFile;
  int *visits;
  Node *nodes;
  int count;
  listOfObjects<BST *> *trees;
  bool *cycle;

  // Add appropriate fields as necessary for your implementation

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
    for (int i = 0; i < numNodes; i++)
    {
      nodes[i].setSize(numNodes);
    }
    cycle = new bool[numNodes];
    for (int i = 0; i < numNodes; i++)
    {
      cycle[i] = false;
    }
    visits = new int[numNodes];
    if (nodes == nullptr)
    {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++)
    {
      nodes[i].value = i + 1;
      visits[i] = 0;
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

      bool there1 = nodes[n1].addNeighbours(n2);
      bool there2 = nodes[n2].addNeighbours(n1);
      if (there1 || there2)
      {
        graphFile << n1 + 1 << " " << n2 + 1 << endl;
        countEdges++;
      }
    }

    // Add appropriate code as necessary for your implementation
    // for (int i = 0; i < numNodes; i++)
    // {
    //   nodes[i].printNeighbours(numNodes);
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

  // Add appropriate method declarations as necessary for your implementation

  void modifiedDFS();
  void printResults();
  bool DFS(Node node, BST *tree, Node p_node);
};

#endif
