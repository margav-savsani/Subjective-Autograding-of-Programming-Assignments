#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include <vector>
using namespace std;
class Node
{
public:
  int value;
  Node *left;
  Node *right;
  Node *parent;
  vector<int> adjacencyList;
  int st_pos[2];
  Node()
  {
    value = -1;
    left = NULL;
    right = NULL;
    parent = NULL;
    st_pos[0]=-1;
    st_pos[1]=-1;
  }
  Node(int val)
  {
    value = val;
    left = NULL;
    right = NULL;
    parent = NULL;
    st_pos[0]=-1;
    st_pos[1]=-1;
  }
  // insert other fields and methods as appropriate
};
class BST
{
  Node *root;

public:
  BST()
  {
    root = NULL;
  }
  bool insert(int val)
  {
    Node *newnode = new Node(val);
    Node *x = root;
    Node *y = NULL;
    bool left;
    if (x == NULL)
    {
      root = newnode;
      return true;
    }
    while (x != NULL)
    {
      y = x;
      if (val < y->value)
      {
        x = x->left;
        left = true;
      }
      else
      {
        x = x->right;
        left = false;
      }
    }

    if (left)
    {
      y->left = newnode;
    }
    else
    {
      y->right = newnode;
    }
    newnode->parent = y;
    return true;
  }
  void printBST(const string &prefix, bool isLeft = false)
  {
    if (root != nullptr)
    {
      cout << prefix;

      cout << (isLeft ? "|--" : "|__");

      // print the value of the node
      cout << root->value << endl;
      Node *curr = root;
      root = root->left;
      // enter the next tree level - left and right branch
      printBST(prefix + (isLeft ? "│   " : "    "), true);
      root = curr->right;
      printBST(prefix + (isLeft ? "│   " : "    "), false);
      root = curr;
    }
  }
};

class Graph
{
  int numNodes;
  int numEdges;
  fstream graphFile;
  int times;
  int *visited;
  bool *cycle;
  int *arrTime;
  int *instack;
  vector<BST *> trees;
  vector<int> stack;
  Node *nodes;
  bool **edges;

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
    visited= new int[numNodes];
    instack= new int[numNodes];
    cycle = new bool[numNodes];
    edges=new bool*[numNodes];
    for (int i = 0; i < numNodes; i++)
    {
      visited[i] = 0;
      cycle[i] = false;
      instack[i]=0;
      edges[i]=new bool[numNodes];
    }
    for(int i=0;i<numNodes;i++){
      for(int j=0;j<numNodes;j++){
        edges[i][j]=false;
      }
    }
    arrTime = new int[numNodes];
    times = 0;
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
      bool match=false;
      for (auto n : nodes[n1].adjacencyList)
      {
        if (n+1== nodes[n2].value)
        {
          match=true;
        }
      }
     if(!match)
       {
        nodes[n1].adjacencyList.push_back(n2);
        nodes[n2].adjacencyList.push_back(n1);
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
    }
    // cout<< nodes[n1].adjacencyList[0].value<<endl;
    // cout<< nodes[n2].adjacencyList[0].value<<endl;
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
  void DFS(Node node, BST *b,int parent);
  void printResults();
};

#endif
