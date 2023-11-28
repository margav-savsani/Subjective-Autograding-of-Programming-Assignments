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
  void insert(T t){
    listOfObjects<T> *ptr = this;
    while(ptr->next != nullptr){
      ptr = ptr->next;
    }
    ptr->next = new listOfObjects(t);
  }
};

struct TreeNode
{
  int value;        // value
  TreeNode *left;   // Left Child of this Node (NULL, if None)
  TreeNode *right;  // Right Child of this Node (NULL, if None)
  TreeNode *parent; // The Parent Node, NULL in case of Root

  // Constructors

  TreeNode() : value(0), left(nullptr), right(nullptr) {}
  TreeNode(int jrnyvalue) : value(jrnyvalue), left(nullptr), right(nullptr) {}
  TreeNode(int jrnyvalue, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : value(jrnyvalue), left(leftChild), right(rightChild), parent(parent) {}
};

class BST
{
  // Add your own field and members here
  // Feel free to use the printBST function used earlier
  TreeNode *root;

public:
  BST()
  {
    root = nullptr;
  }
  BST(TreeNode *root)
  {
    this->root = root;
    (this->root)->parent = nullptr;
  }

  // Returns false, if given JourneyCode is already present in the BST
  // nodeerts the element and returns  True otherwise
  bool insert(int value)
  {

    TreeNode *father = nullptr;
    TreeNode *son = root;
    // IMPORTANT- We have to create a new node(dynamic) each and every time to get a different address. If we donot add new, then the node created gets the same address as of root. To overcome this, always create a new node.
    TreeNode *node = new TreeNode(value);

    while (son != nullptr)
    {
      father = son;

      if (node->value < father->value)
      {
        son = father->left;
      }
      else
      {
        son = father->right;
      }
    }

    node->parent = father;
    if (father == nullptr)
    {
      root = node;
    }
    else if (node->value < father->value)
    {
      father->left = node;
    }
    else
    {
      father->right = node;
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
      cout << root->value << endl;
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
  listOfObjects<Node> *adjNodes = nullptr;
public:
  int value;
  // insert other fields and methods as appropriate
  Node(){};
  Node(int v)
  {
    value = v;
  }
  bool updateAdjacency(Node n)
  {
    listOfObjects<Node> *ptr = adjNodes;
    listOfObjects<Node> *adj_vert = new listOfObjects<Node>(n);
    if (ptr == nullptr)
    {
      adjNodes = adj_vert;
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
  void printAdjacency(){
    listOfObjects<Node> *ptr = adjNodes;
    while(ptr!= nullptr){
      cout<<ptr->object.value<<" ";
      ptr = ptr->next;
    }
    cout<<endl;
  }
  listOfObjects<Node> *getAdjNodes(){
    return adjNodes;
  }
};

class Edge
{
  public:
  Node n1;
  Node n2;
  Edge(Node n1, Node n2){
    this->n1 = n1;
    this->n2 = n2;
  }
  Edge(){};
  bool isEqual(Edge edge2)
  {
    if ((this->n1.value == edge2.n1.value && this->n2.value == edge2.n2.value) || (this->n1.value == edge2.n2.value && this->n2.value == edge2.n1.value))
      return true;
    else
      return false;
  }
};

class Graph
{
  int numNodes;
  int numEdges;
  fstream graphFile;
  int *visited_times;
  int *arr_times;
  // int *isinCycle;
  Node *nodes;
  int numComponents;
  int numCycles;
  // Add appropriate fields as necessary for your implementation

public:
  Graph(int nNodes, int nEdges, string gFileName)
  {
    numNodes = nNodes;
    numEdges = nEdges;
    visited_times = new int[numNodes];
    arr_times = new int[numNodes];
    // isinCycle = new int[numNodes];
    numComponents = 0;
    numCycles=0;
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
      if (!nodes[n1].updateAdjacency(nodes[n2]))
        continue;
      nodes[n2].updateAdjacency(nodes[n1]);

      graphFile << n1 + 1 << " " << n2 + 1 << endl;
      countEdges++;
    }
    for (int i = 0; i < numNodes; i++)
    {
      visited_times[i] = 0;
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
  void printResults();
  void DFS(Node v, Node pv, BST *T, listOfObjects<Edge> *edgeList);
};

#endif
