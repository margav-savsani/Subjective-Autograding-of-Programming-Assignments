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
  listOfObjects(){};
  listOfObjects(T initValue)
  {
    object = initValue;
    next = prev = nullptr;
  }

  // Destructor
  ~listOfObjects() { ; }
  void insert(T t)
  {
    listOfObjects<T> *ptr = this;
    if(ptr == nullptr) return;
    while (ptr->next != nullptr)
    {
      ptr = ptr->next;
    }
    ptr->next = new listOfObjects(t);
  }
};

class Node
{

public:
  listOfObjects<Node> *outadjNodes = nullptr; // edge going out from the given node,outadjacent nodes,
  listOfObjects<Node> *inadjNodes = nullptr;  // edge coming in from the given node,inadjacent nodes
  int value;
  Node(){};
  Node(int v)
  {
    value = v;
  }
  bool updateInAdjacency(Node n)
  {
    listOfObjects<Node> *ptr = inadjNodes;
    listOfObjects<Node> *adj_vert = new listOfObjects<Node>(n);
    if (ptr == nullptr)
    {
      inadjNodes = adj_vert;
      return true;
    }
    while (ptr->next != nullptr)
    {
      if (ptr->object.value == n.value)
        return false;
      ptr = ptr->next;
    }
    if (ptr->object.value == n.value)
      return false;
    ptr->next = adj_vert;
    return true;
  }
  bool updateOutAdjacency(Node n)
  {
    listOfObjects<Node> *ptr = outadjNodes;
    listOfObjects<Node> *adj_vert = new listOfObjects<Node>(n);
    if (ptr == nullptr)
    {
      outadjNodes = adj_vert;
      return true;
    }
    while (ptr->next != nullptr)
    {
      if (ptr->object.value == n.value)
        return false;
      ptr = ptr->next;
    }
    if (ptr->object.value == n.value)
      return false;
    ptr->next = adj_vert;
    return true;
  }
  void printOutAdjacency()
  {
    listOfObjects<Node> *ptr = outadjNodes;
    while (ptr != nullptr)
    {
      cout << ptr->object.value << " ";
      ptr = ptr->next;
    }
    cout << endl;
  }
  void printInAdjacency()
  {
    listOfObjects<Node> *ptr = inadjNodes;
    while (ptr != nullptr)
    {
      cout << ptr->object.value << " ";
      ptr = ptr->next;
    }
    cout << endl;
  }
};

class Edge
{
public:
  Node n1;
  Node n2;
  Edge(Node n1, Node n2)
  {
    this->n1 = n1;
    this->n2 = n2;
  }
  Edge(){};
  bool isEqual(Edge edge2)
  {
    if ((this->n1.value == edge2.n1.value && this->n2.value == edge2.n2.value))
      return true;
    else
      return false;
  }
  void printEdge(ofstream& gFile)
  {
    gFile << "(" << n1.value << ", " << n2.value << ")";
  }
};

class Graph
{
  int numNodes;
  Node *nodes;
  listOfObjects<Edge> *similarNodes;
  listOfObjects<Edge> *edgeList;
  int *isSourceNode;
  ofstream gFile;
public:
  Graph(int nNodes)
  {
    numNodes = nNodes;
    nodes = new Node[numNodes];
    isSourceNode = new int[numNodes];
    int step = 0;
    gFile = ofstream("outGraph.txt");
    if (nodes == nullptr)
    {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++)
    {
      nodes[i].value = i + 1;
    }
    while (step < 2)
    {
      int a, b;
      cin >> a >> b;
      if (a == -1 && b == -1)
      {
        step++;
        continue;
      }
      else if (step == 0)
      {
        nodes[a - 1].updateOutAdjacency(nodes[b - 1]);
        nodes[b - 1].updateInAdjacency(nodes[a - 1]);
        if (edgeList != nullptr)
        {
          edgeList->insert(Edge(nodes[a - 1], nodes[b - 1]));
        }
        else
        {
          edgeList = new listOfObjects<Edge>(Edge(nodes[a - 1], nodes[b - 1]));
        }
      }
      else if (step == 1)
      {
        listOfObjects<Edge> *ptr = similarNodes;
        listOfObjects<Edge> *pair = new listOfObjects<Edge>(Edge(nodes[a - 1], nodes[b - 1]));
        if (similarNodes == nullptr)
        {
          similarNodes = pair;
        }
        else
        {
          while (ptr->next != nullptr)
          {
            ptr = ptr->next;
          }
          ptr->next = pair;
        }
      }
    }
  }
  ~Graph()
  {
    delete[] nodes;
    gFile.close();
  }
  // Add appropriate method declarations as necessary for your implementation
  void printSourceNodes();
  void updateSimilarity();
  void printSimilarNodes();
  bool checkSimilarity(Node n1, Node n2);
  void printCollapsedGraph();
};

#endif
