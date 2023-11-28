#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

class Node;
class LinkedList//created to store different lists like the predecessor and parent
{
public:
  LinkedList *next;
  LinkedList *prev;
  Node *Listnode;

  LinkedList()
  {
    next = nullptr;
    prev = nullptr;
  }
  LinkedList(Node *node)
  {
    next = nullptr;
    prev = nullptr;
    Listnode = node;
  }
};

class Node
{
public:
  int value;
  Node *left;
  Node *right;
  Node *parent;
  LinkedList *adjList, *tail;//adjacency list
  LinkedList *predecessors, *tailpredecessor;//stores the immediate neighbours
  LinkedList *backtrack, *tailbacktrack;//stores backtracking list
  int visited;
  Node() : value(0), left(nullptr), right(nullptr), parent(nullptr) { visited = 0; }
  Node(int nodevalue) : value(nodevalue), left(nullptr), right(nullptr), parent(nullptr) { visited = 0; }

  // insert other fields and methods as appropriate
};

class BST
{
  // Add your own field and members here
public:
  Node *root;
  int BSTindex;
  int numElems;

  BST(int index)
  {
    root = nullptr;
    BSTindex = index;
    numElems = 0;
  }
  // Feel free to use the printBST function used earlier
  void printBST(const string &prefix, bool isLeft);
  void insert(int value);
};

class Graph
{
  int numNodes;
  int numEdges;
  fstream graphFile;
  int countTrees;
  Node *nodes;
  BST **DFStree;

  // Add appropriate fields as necessary for your implementation

public:
  Graph(int nNodes, int nEdges, string gFileName)
  {
    numNodes = nNodes;
    numEdges = nEdges;
    countTrees = 0;
    DFStree = new BST *[numNodes];
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

      if (nodes[n1].adjList == nullptr) // storing values into the adjacency list of n1
      {
        nodes[n1].adjList = new LinkedList(&nodes[n2]); // first adjacent value
        nodes[n1].tail = nodes[n1].adjList;
      }
      else
      {
        int count = 0;
        LinkedList *curr = nodes[n1].adjList;
        while (curr != nullptr) // for storing next adjacent values, we need to check if the element is already present in the adjacency list
        {
          if (curr->Listnode->value == n2 + 1)
          {
            count = 1;
            break;
          }
          curr = curr->next;
        }
        if (count == 0) // if the new element is unique , we insert it into the LinkedList
        {
          nodes[n1].tail->next = new LinkedList(&nodes[n2]);
          nodes[n1].tail->next->prev = nodes[n1].tail;
          nodes[n1].tail = nodes[n1].tail->next;
        }
      }

      if (nodes[n2].adjList == nullptr)
      {
        nodes[n2].adjList = new LinkedList(&nodes[n1]);
        nodes[n2].tail = nodes[n2].adjList;
        graphFile << n1 + 1 << " " << n2 + 1 << endl;
        countEdges++;
      }
      else
      {
        int count = 0;
        LinkedList *curr = nodes[n2].adjList;
        while (curr != nullptr)// for storing next adjacent values, we need to check if the element is already present in the adjacency list
        {
          if (curr->Listnode->value == n1 + 1)
          {
            count = 1;
            break;
          }
          curr = curr->next;
        }
        if (count == 0) // if the new element is unique , we insert it into the LinkedList
        {
          nodes[n2].tail->next = new LinkedList(&nodes[n1]);

          nodes[n2].tail->next->prev = nodes[n2].tail;
          nodes[n2].tail = nodes[n2].tail->next;
          graphFile << n1 + 1 << " " << n2 + 1 << endl;
          countEdges++;
        }
      }
    }
  }

  // Add appropriate code as necessary for your implementation

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
  void modifiedRecursiveDFS(Node *node);
  void printResults();
  int calculateOnevisits();
  bool member(Node *node, LinkedList *list);
  int calculatecycle();
  
};

#endif
