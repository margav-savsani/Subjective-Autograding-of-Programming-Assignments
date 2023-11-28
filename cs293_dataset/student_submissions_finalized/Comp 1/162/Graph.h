#ifndef GRAPH_BST_H
#define GRAPH_BST_H

// To convert vector to linked list later
//  To implement self implementation of stack
#include <vector>
#include <stack>

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

struct TreeNode
{
  int value;        // Journey code	// Price
  TreeNode *left;   // Left Child of this Node (NULL, if None)
  TreeNode *right;  // Right Child of this Node (NULL, if None)
  TreeNode *parent; // The Parent Node, NULL in case of Root

  TreeNode() : value(0), left(nullptr), right(nullptr) {}

  TreeNode(int value) : value(value), left(nullptr), right(nullptr) {}

  TreeNode(int value, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : value(value), left(leftChild), right(rightChild), parent(parent) {}
};

class BST
{

 



public:

 TreeNode *root;

  BST() { root = nullptr; }
  BST(TreeNode *curr_root) { root = curr_root; }

  // Implement your own destructor
  ~BST(){};

  // Returns false, if given value is already present in the BST
  // Inserts the element and returns True otherwise
  bool insert(int value)
  {   
      // printBST("",false);
     if(root == nullptr)
    {
        root = new TreeNode(value,nullptr,nullptr,nullptr);
    }
    TreeNode *currNode = root, *parentOfCurrNode = nullptr;

    while (currNode != nullptr)
    {
        if (currNode->value < value)
        {
            parentOfCurrNode = currNode;
            currNode = currNode->right;
        }
        else
        {
            parentOfCurrNode = currNode;
            currNode = currNode->left;
        }

    }
    if(value > parentOfCurrNode->value)
    {
        parentOfCurrNode->right = new TreeNode(value,nullptr,nullptr,parentOfCurrNode);
        return true;
    }
    else
    {
        parentOfCurrNode->left = new TreeNode(value,nullptr,nullptr,parentOfCurrNode);
        return true;
    }
  }

  void printBST(const string &prefix, bool isLeft)
  {
    if (root != nullptr)
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__");

        // print the value of the node
        cout << root->value<< endl;
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
  int *parents;
  int currentSize = 0;
  Node **adjacencyList;
  // insert other fields and methods as appropriate

  Node()
  {
    adjacencyList = nullptr;
    parents = new int[2];
    parents[0] = parents[1] = -1;
  }

  bool checkIfParent(int val)
  {
    return (parents[0] == val || parents[1] == val);
  }

  bool checkIfNeighbour(int val)
  {
    if (val == this->value)
      return false;
    for (int i = 0; i < currentSize; i++)
      if (adjacencyList[i]->value == val)
        return true;
    return false;
  }
};

class Graph
{
  int numNodes;
  int numEdges;
  std::fstream graphFile;

  int currentConnectedComp;

  int conComps = 0;
  int visOnce = 0;
  int visTwice = 0;
  int inCycle = 0;
  BST* BSTArray;
  int *visited;
  int *incycle;
  int *connectedComponents;
  Node *nodes;

  // Add appropriate fields as necessary for your implementation

public:
  Graph(int nNodes, int nEdges, std::string gFileName)
  {
    numNodes = nNodes;
    numEdges = nEdges;
    BSTArray = new BST[nNodes];

    
    visited = new int[nNodes];
    incycle = new int[nNodes];
    connectedComponents = new int[nNodes];
    for (int i = 0; i < nNodes; i++)
    {
      visited[i] = incycle[i] = connectedComponents[i] = 0;
      // BSTArray[i] = nullptr;
    }
    currentConnectedComp = 0;
    graphFile.open(gFileName, std::ios::out);
    if (!graphFile.is_open())
    {
      std::cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << std::endl;
      exit(-1);
    }

    graphFile << numNodes << std::endl;
    graphFile << numEdges << std::endl;

    nodes = new Node[numNodes];
    if (nodes == nullptr)
    {
      std::cerr << "Memory allocation failure." << std::endl;
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

      if (nodes[n1].checkIfNeighbour(nodes[n2].value))
        continue;
      if (nodes[n1].currentSize == 0)
      {
        nodes[n1].adjacencyList = new Node *[numEdges];
      }
      if (nodes[n2].currentSize == 0)
      {
        nodes[n2].adjacencyList = new Node *[numEdges];
      }
      nodes[n1].adjacencyList[nodes[n1].currentSize++] = &nodes[n2];
      nodes[n2].adjacencyList[nodes[n2].currentSize++] = &nodes[n1];

      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile

      graphFile << n1 << " " << n2 << std::endl;
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
  void modifiedDFS2(int node, int currenComp, BST* &BSTArray);
  void printResults();
};

#endif
