#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <list>
using namespace std;

template <typename T> // list of objects which were given in previous labs .
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

class BSTNode  // newly defined class for BST Nodes .
{
public:
  int value;  // value stored in BST Node .
  BSTNode *left;  // pointer which points left to a Node .
  BSTNode *right;  // pointer which points right to a Node .
  BSTNode *parent;  // pointer to the parent of the Node .
  BSTNode()  // constructor 
  {
    value = 0;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
  }
  BSTNode(int val)  // constructor 
  {
    value = val;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
  }
  ~BSTNode(){};  // destructor 
};

class BST
{
public:
  BSTNode *root;  // root of the BST tree .
  int height;

  BST() { root = nullptr; }
  BST(BSTNode *curr_root) { root = curr_root; }
  ~BST(){}; // destructor

  bool insert(int val)  // insert function for the BST tree taken from previous labs .
  {

    BSTNode *new_node;
    new_node = new BSTNode(val);
    BSTNode *node1;
    BSTNode *node2;
    node1 = root;
    node2 = nullptr;
    while (node1 != nullptr)
    {
      node2 = node1;
      // if (val == node1->value)
      // {
      //   return false;
      // }
      if (val < node1->value)
      {
        node1 = node1->left;
      }
      else
        node1 = node1->right;
    }

    new_node->parent = node2;
    if (node2 == nullptr)
    {
      root = new_node;
    }
    else if (val < node2->value)
    {
      node2->left = new_node;
    }
    else
    {
      node2->right = new_node;
    }
    return true;
  }
  void printBST(const string &prefix, bool isLeft = false) // print BST function taken from previous labs .
  {
    if (root != nullptr)
    {
      std::cout << prefix;

      std::cout << (isLeft ? "|--" : "|__");

      // print the value of the node
      std::cout << root->value << std::endl;
      BSTNode *curr = root;
      root = root->left;
      // enter the next tree level - left and right branch
      printBST(prefix + (isLeft ? "│   " : "    "), true);
      root = curr->right;
      printBST(prefix + (isLeft ? "│   " : "    "), false);
      root = curr;
    }
  }

  // Add your own field and members here

  // Feel free to use the printBST function used earlier
};

class Node
{
public:
  int value; // value stored in the graph node .
  int degree;
  int num_visited; // this equals number of times the code got visited in DFS search .
  Node()  // constructor .
  {
    value = 0;
    degree = 0;
    num_visited = 0;
  }
  Node(int val)  // constructor .
  {
    value = val;
    degree = 0;
    num_visited = 0;
  }

public:
  listOfObjects<Node *> *adjacencynodes; // stores all the nodes adresses adjacent to the given node .
  // insert other fields and methods as appropriate
  ~Node(){}; // destructor 
};

class Graph
{
  int numNodes;  // number of nodes in the graph .
  int numEdges;  // number of edges in the graph .
  int num_connected_components; // number of connected components present in the cycle .
  fstream graphFile;

  Node *nodes;

  // Add appropriate fields as necessary for your implementation

public:
  Graph(int nNodes, int nEdges, string gFileName)
  {
    numNodes = nNodes;
    numEdges = nEdges;
    num_connected_components = 0;
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



      // checking whether the edge was present already or not .
      listOfObjects<Node *> *dummy1;
      listOfObjects<Node *> *dummy2;
      dummy1 = nodes[n1].adjacencynodes; 
      dummy2 = nodes[n2].adjacencynodes;
      if ((dummy1 != nullptr) && (dummy2 != nullptr))   // adding the edges between nodes[n1] and nodes[n2] .
      {
        while (dummy1 != nullptr)
        {
          if (dummy1->object->value != nodes[n2].value)  // if the edge was not already present then edge gets added .
          {
            listOfObjects<Node *> *newNode1 = new listOfObjects<Node *>(&nodes[n2]);
            newNode1->next = nodes[n1].adjacencynodes;
            nodes[n1].adjacencynodes = newNode1;
            listOfObjects<Node *> *newNode2 = new listOfObjects<Node *>(&nodes[n1]);
            newNode2->next = nodes[n2].adjacencynodes;
            nodes[n2].adjacencynodes = newNode2;
            graphFile << n1 + 1 << " " << n2 + 1 << endl;
            countEdges++;
            break;
          }
          dummy1 = dummy1->next;
        }
      }
      else  // adding the edges between nodes[n1] and nodes[n2] .
      {
        listOfObjects<Node *> *newNode1 = new listOfObjects<Node *>(&nodes[n2]);
        newNode1->next = nodes[n1].adjacencynodes;
        nodes[n1].adjacencynodes = newNode1;
        listOfObjects<Node *> *newNode2 = new listOfObjects<Node *>(&nodes[n1]);
        newNode2->next = nodes[n2].adjacencynodes;
        nodes[n2].adjacencynodes = newNode2;
        graphFile << n1 + 1 << " " << n2 + 1 << endl;
        countEdges++;
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
    // Add appropriate code as necessary for your implementation
  }
  Node *findNode(int val)  // this function selects a random node as our source to start DFS .
  {
    for (int i = 0; i < numNodes; i++)
    {
      if (nodes[i].value == val)
      {
        return &nodes[i];
      }
    }
  }

  listOfObjects<BST *> *Trees;

  // Add appropriate method declarations as necessary for your implementation

  void newDFS(Node *node, BST *Tree);
  void modifiedDFS();
  void printResults();
};

#endif
