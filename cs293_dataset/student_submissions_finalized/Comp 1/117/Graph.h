#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

//list, copied from previous labs
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
//Node for the binary search tree
class BSTNode{
  public:
    int value;
    BSTNode*left, *right, *parent;
    BSTNode(int value){
      this->value = value;
      left = nullptr;
      right = nullptr;
      parent = nullptr;
    }
};
//BST itself
class BST
{
public:
  BSTNode *root;
  BST(){
    root = nullptr;
  }
  BST(BSTNode* root){
    this->root = root;
  }
  void insert(int value);//inserting a value
  void printBST(const string&prefix, bool isleft = true);//printing the BST

  // Add your own field and members here

  // Feel free to use the printBST function used earlier
};
//Stores an edge, basically indices ofnodes
class Edge{
  public:
    int node1, node2;
    bool backtracked;//backtrackes, used in dfs
    Edge(){}
    Edge(int node1, int node2){
      this->node1 = node1;
      this->node2 = node2;
    }
      
};
//Node for Graph
class Node
{
public:
  int value;
  listOfObjects<Node *> *head, *tail; // For graph, adcacency list
  listOfObjects<Edge *> *edgehead, *edgetail;//modern adjacency list, storing pointers to edges
  Node()
  {
    head = nullptr;
    tail = nullptr;
    edgehead = nullptr;
    edgetail = nullptr;
  }

  bool existsEdge(Node *adc);//Checking if an edge already exists
  void insertEdge(Node *adjacentNode, Edge* adjacentEdge);//Inserting an edge
  // insert other fields and methods as appropriate
};

//Main class
class Graph
{
  int numNodes;
  int numEdges;
  fstream graphFile;

  int *visited;//array for storing times visited
  Node *nodes;//nodes array
  listOfObjects<Edge*> * edgeList, *tail;//edgelist
  int * parents[2];//storing parents in DFS
  int connectedComps, visitedonce, visitedtwice, cyclicnodes;//storing data
  listOfObjects<BST*> *bsts, *endbsts;

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
    //initialising stuff
    nodes = new Node[numNodes];
    visited = new int[numNodes];
    parents[0] = new int[numNodes];
    parents[1] = new int[numNodes];
    visitedonce = 0;
    visitedtwice = 0;
    connectedComps = 0;
    cyclicnodes = 0;
    bsts = nullptr;
    endbsts = nullptr;
    
    if (nodes == nullptr)
    {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++)
    {
      nodes[i].value = i + 1;
    }
    // adding edges
    srand(time(0));
    int n1, n2;
    int countEdges = 0;
    while (countEdges < numEdges)
    {
      do
      {
        n1 = rand() % numNodes;
        n2 = rand() % numNodes;
      } while (n1 == n2);// not same nodes as endpoint

      if (!nodes[n1].existsEdge(&nodes[n2]))// checking if not already present in graph
      {

        Edge* newedge = new Edge(n1,n2);
        if(edgeList == nullptr){
          
          edgeList = new listOfObjects<Edge*>(newedge);
          tail = edgeList;
        }
        else{
          tail->next = new listOfObjects<Edge*>(newedge);
          tail->next->prev = tail;
          tail = tail->next;
        }
        nodes[n1].insertEdge(&nodes[n2],tail->object);
        nodes[n2].insertEdge(&nodes[n1],tail->object);
        // Create an undirected edge from n1 to n2 and store in appropriate
        // adjacency list(s).  If an undirected edge from n1 to n2 (or
        // equivalently from n2 to n1) already exists, you shouldn't add
        // an edge.  Only if such an undirected edge didn't exist earlier,
        // should you add the edge and increment countEdges; otherwise,
        // do not increment countEdges;
        // Every time an edge is created, we also add that information to
        // graphFile

        graphFile << n1 + 1 << " " << n2 + 1 << endl;// couting the edges to graphFile
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

  // Add appropriate method declarations as necessary for your implementation

  void modifiedDFS();
  void recursiveModDFS(int node, BST* bst);// recursive DFS
  void printResults();
};

#endif
