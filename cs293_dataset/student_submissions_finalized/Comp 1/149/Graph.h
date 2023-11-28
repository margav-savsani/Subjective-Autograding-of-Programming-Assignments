#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

/// @brief ususal listOfObjects.. hardly need explanation after using it 171 times..
/// @tparam T object in the list of objects
template <typename T>
class listOfObjects
{
public:
  T object;
  listOfObjects<T> *next;
  listOfObjects<T> *prev;

  listOfObjects(T initValue)
  {
    object = initValue;
    next = prev = nullptr;
  }
  ~listOfObjects() { ; }
};

/// @brief Node for storing both node in the graph and node in the BST
class Node
{
public:
  int value; // value in the node
  int time = 0; //arrivel time of the node
  Node *left; // left for the BST
  Node *right; //right for the BST
  Node *parent; // parent in the BST
  Node *pred; // parent or predecessor in the DFS
  listOfObjects<Node *> *adjacency; // adjacency list of the points
  int adjacencyCounter = 0; // counter for the adjaceny list
  int visited; // visited ... 0,1,2
  bool cycle = false; // boolean for whether the node is present in the cycle or not
  
  /// @brief empty constructor for the node
  Node()
  {
    adjacency = nullptr;
  }

  /// @brief constructor with an argument for the node
  /// @param i value to be inserted in the node
  Node(int i)
  {
    value = i;
    right = nullptr;
    left = nullptr;
    parent = nullptr;
    adjacency = nullptr;
    pred = nullptr;
  }
};

/// @brief class for the BST
class BST
{
public:
  BST *next; // BST is implemented as a linked list
  Node *root; // root of the BST

  /// @brief default empty constructor for the BST
  BST()
  {
    root = nullptr;
    next = nullptr;
  }
  /// @brief another constructor for the BST
  /// @param t pointer to the root of the BST
  BST(Node *t)
  {
    root = t;
    next = nullptr;
  }

  /// @brief The printBST function which was with us all along.. through highs and lows... just kidding!!
  /// @param prefix still not able to figure out how are we using this prefix
  /// @param isLeft self explanatory :]
  void printBST(const string &prefix, bool isLeft = false)
  {
    if (root != nullptr)
    {
      cout << prefix;

      cout << (isLeft ? "|--" : "|__");
      cout << root->value << endl;
      Node *curr = root;
      root = root->left;
      printBST(prefix + (isLeft ? "│   " : "    "), true);
      root = curr->right;
      printBST(prefix + (isLeft ? "│   " : "    "), false);
      root = curr;
    }
  }
};

/// @brief Graph class
class Graph
{
  BST *B; // linked list for the BST
  int numNodes; // number of nodes in the graph
  int numEdges; // number of edges int he graph
  fstream graphFile; // grapffile whre the edges are stored to take alook at
  Node *nodes; // nodes in the graph later to initaialised as an array
  int components = 0; // no. of connected components in the graph

public:

  /// @brief constructor of the graph, takes in random values for the nodes of the graph
  /// @param nNodes number of nodes in the graph
  /// @param nEdges number of edges in the graph
  /// @param gFileName file for the output
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

      // when both nodes, adjacency list is empty
      if (nodes[n1].adjacencyCounter == 0 and nodes[n2].adjacencyCounter == 0)
      {
        graphFile << n1 + 1 << " " << n2 + 1 << endl;
        countEdges++;
        nodes[n1].adjacency = new listOfObjects<Node *>(&nodes[n2]);
        nodes[n2].adjacency = new listOfObjects<Node *>(&nodes[n1]);
        nodes[n1].adjacencyCounter++;
        nodes[n2].adjacencyCounter++;
      }
      // when one of the nodes , adjacency list is empty
      else if (nodes[n1].adjacencyCounter == 0)
      {
        graphFile << n1 + 1 << " " << n2 + 1 << endl;
        countEdges++;
        nodes[n1].adjacency = new listOfObjects<Node *>(&nodes[n2]);
        listOfObjects<Node *> *currnode = nodes[n2].adjacency;
        while (currnode->next != nullptr)
        {
          currnode = currnode->next;
        }
        currnode->next = new listOfObjects<Node *>(&nodes[n1]);
        nodes[n1].adjacencyCounter++;
        nodes[n2].adjacencyCounter++;
      }
      // when one of the nodes , adjacency list is empty
      else if (nodes[n2].adjacencyCounter == 0)
      {
        graphFile << n1 + 1 << " " << n2 + 1 << endl;
        countEdges++;
        nodes[n2].adjacency = new listOfObjects<Node *>(&nodes[n1]);
        listOfObjects<Node *> *currnode = nodes[n1].adjacency;
        while (currnode->next != nullptr)
        {
          currnode = currnode->next;
        }
        currnode->next = new listOfObjects<Node *>(&nodes[n2]);
        nodes[n1].adjacencyCounter++;
        nodes[n2].adjacencyCounter++;
      }
      // when both are not wmpty, check whether the node already exists, then insert in it
      else
      {
        bool a = false;
        listOfObjects<Node *> *currnode = nodes[n1].adjacency;
        while (currnode != nullptr)
        {
          if (currnode->object->value == nodes[n2].value)
          {
            a = true;
            break;
          }
          currnode = currnode->next;
        }
        if (!a)
        {
          currnode = nodes[n1].adjacency;
          while (currnode->next != nullptr)
          {
            currnode = currnode->next;
          }
          currnode->next = new listOfObjects<Node *>(&nodes[n2]);
          currnode = nodes[n2].adjacency;
          while (currnode->next != nullptr)
          {
            currnode = currnode->next;
          }
          currnode->next = new listOfObjects<Node *>(&nodes[n1]);
          graphFile << n1 + 1 << " " << n2 + 1 << endl;
          countEdges++;
          nodes[n1].adjacencyCounter++;
          nodes[n2].adjacencyCounter++;
        }
      }
    }
  }

  /// destructor fot the graph
  ~Graph()
  {
    if (graphFile.is_open())
    {
      graphFile.close();
    }
    delete[] nodes;
  }
  /// @brief DFS implementation in the modified way, also accounts for the arrival time, cycles etc..
  /// @param n node on which DFS is called
  /// @param root root of the BST in which node is to be inserted
  void DFS(Node *n, Node *root);
  /// @brief first function called for DFS, make sures that every node is visited. creates new component for the nodes which remains unvisited.
  void modifiedDFS();
  /// @brief function to print the final results.
  void printResults();
};

#endif
