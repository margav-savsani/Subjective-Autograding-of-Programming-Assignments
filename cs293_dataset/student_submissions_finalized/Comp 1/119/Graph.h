#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

// -------------------------- linkedListNode and linkedList --------------------------

template <typename T>
class linkedListNode
{
public:
  T value;
  linkedListNode<T> *prev = NULL, *next = NULL;
};

template <typename T>
class linkedList
{
public:
  linkedListNode<T> *head = NULL, *tail = NULL;

  void insert(linkedListNode<T> *v)
  {
    if (head == NULL)
      head = tail = v;
    else
    {
      tail->next = v;
      v->prev = tail;

      tail = v;
    }
  }
};

// -------------------------- BST, GRAPH, and NODE --------------------------

class Node
{
public:
  int value;
  int visits = 0;
  Node *BSTleft = NULL, *BSTright = NULL;

  Node *previous = NULL;

  linkedList<int> adjNodeIndexes;
};

class BST
{
public:
  Node *root = NULL;
  void insert(Node *x);
  void printBST(Node *root, const string &prefix, bool isLeft);
};

bool linkedListUniqueInsertCheck(linkedList<int> x, int y)
{
  linkedListNode<int> *temp = x.head;
  while (temp != NULL)
  {
    if (temp->value == y)
      return 0;
    temp = temp->next;
  }
  return 1;
}

class Graph
{
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;

public:
  linkedList<BST *> BSTtrees;

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
      linkedListNode<int> *one = new linkedListNode<int>;
      linkedListNode<int> *two = new linkedListNode<int>;
      while (true)
      {
        do
        {
          n1 = rand() % numNodes;
          n2 = rand() % numNodes;
        } while (n1 == n2);

        if (linkedListUniqueInsertCheck(nodes[n1].adjNodeIndexes, n2) &&
            linkedListUniqueInsertCheck(nodes[n2].adjNodeIndexes, n1))
        {
          one->value = n1;
          two->value = n2;
          break;
        }
      }

      nodes[n1].adjNodeIndexes.insert(two);
      nodes[n2].adjNodeIndexes.insert(one);

      graphFile << n1 + 1 << " " << n2 + 1 << endl;
      countEdges++;
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

  void modifiedDFS();
  void printResults();
  void connectedCompDFS(Node *v, Node *p, BST *tree);
};

#endif
