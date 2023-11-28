#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

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
  void check_for_cycles(int dest, bool* &is_cycle)
  {
    listOfObjects<int>* cycle = this;
    bool cyc = false;
    while(cycle != nullptr)
    {
      if(cycle->object == dest && cyc == false)
      {
        is_cycle[cycle->object] = true;
        cyc = true;
      }
      else if(cyc == true)
        is_cycle[cycle->object] = true;
      cycle = cycle->next;
    }
  }
  void insert_stack_elem(T dest)
  {
    listOfObjects<T>* iter_ls = this;
    while(iter_ls->next != nullptr)
      iter_ls = iter_ls->next;
    iter_ls->next = new listOfObjects<T>(dest);
    iter_ls->next->prev = iter_ls;
  }

  void remove_stack_elem()
  {
    listOfObjects<int>* iter_ls = this;
    while(iter_ls->next != nullptr)
      iter_ls = iter_ls->next;
    if(iter_ls->prev == nullptr)
      object = 0;
    else
    {
      iter_ls->prev->next = nullptr;
      iter_ls->prev = nullptr;
    }
  }

  // Destructor
  ~listOfObjects() { ; }
};

struct TreeNode
{
  int value;
  TreeNode *left;   // Left Child of this Node (NULL, if None)
  TreeNode *right;  // Right Child of this Node (NULL, if None)
  TreeNode *parent; // The Parent Node, NULL in case of Root

  // Constructors

  TreeNode() : value(0), left(nullptr), right(nullptr), parent(nullptr) {}
  TreeNode(int val) : value(val), left(nullptr), right(nullptr), parent(nullptr) {}
  TreeNode(int val, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : value(val), left(leftChild), right(rightChild), parent(parent) {}
};

class BST
{
public:
  TreeNode *root;
  BST()
  {
    root = new TreeNode();
    root->parent = nullptr;
  }
  BST(TreeNode *root)
  {
    this->root = root;
    this->root->parent = nullptr;
  }

  // Returns false, if given JourneyCode is already present in the BST
  // Inserts the element and returns True otherwise
  void insert(int val)
  {
    TreeNode *dummy = nullptr;
    TreeNode *start = root;
    if (root->value == 0) // start of BST
    {
      root->value = val;
      return;
    }
    while (start != nullptr) // Moving to end leaf
    {
      dummy = start;
      if ((start->value) > val)
        start = start->left;
      else
        start = start->right;
    }

    if (val < dummy->value) // insert at left
    {
      dummy->left = new TreeNode(val);
      dummy->left->parent = dummy;
    }
    else // insert at right
    {
      dummy->right = new TreeNode(val);
      dummy->right->parent = dummy;
    }
  }

  void printBST(TreeNode *start, const string &prefix, bool isLeft = false)
  {
    if( start != nullptr )   
    {
      cout << prefix;
      
      cout << (isLeft ? "|--" : "|__" );
      
      // print the value of the node
      cout << start->value << endl;
      TreeNode *curr = start;
      start = start->left;
      // enter the next tree level - left and right branch
      printBST(start, prefix + (isLeft ? "│   " : "    "), true);
      start = curr->right;
      printBST(start, prefix + (isLeft ? "│   " : "    "), false);
      start = curr;
    }
  }
};

class Node
{
public:
  int value;
  listOfObjects<int> *neighbour_list;
  listOfObjects<int> *current;
  Node()
  {
    neighbour_list = nullptr;
    current = nullptr;
  }
  Node(int val)
  {
    value = val;
    neighbour_list = nullptr;
    current = nullptr;
  }
  void insert_neighbour(int neighbour)
  {
    listOfObjects<int> *newnode = new listOfObjects<int>(neighbour);
    if (neighbour_list == nullptr)
    {
      neighbour_list = newnode;
      current = newnode;
    }
    else
    {
      current->next = newnode;
      newnode->prev = current;
      current = newnode;
    }
  }

  void delete_top()
  {
    current = current->prev;
    current->next->prev = nullptr;
    current->next = nullptr;
  }

  bool check_adjacency(int neighbour)
  {
    listOfObjects<int> *iter_list = neighbour_list;
    while (iter_list != nullptr)
    {
      if (iter_list->object == neighbour)
        return true;
      iter_list = iter_list->next;
    }
    return false;
  }

  // insert other fields and methods as appropriate
};


class Graph
{
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;
  int connected_components;
  int elem_once;
  int elem_twice;
  int node_cycle;
  BST* list_BSTs;
  int no_of_BSTs;

  // Add appropriate fields as necessary for your implementation

public:
  Graph(int nNodes, int nEdges, string gFileName)
  {
    numNodes = nNodes;
    numEdges = nEdges;
    connected_components = 0;
    list_BSTs = new BST[numNodes];
    no_of_BSTs = 0;
    graphFile.open(gFileName, ios::out);
    if (!graphFile.is_open())
    {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }

    graphFile << numNodes << endl;
    graphFile << numEdges << endl;

    nodes = new Node[numNodes+1];
    if (nodes == nullptr)
    {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i <= numNodes; i++)
    {
      nodes[i].value = i;
    }

    // srand(time(0));
    srand(0);
    int n1, n2;
    int countEdges = 0;

    while (countEdges < numEdges)
    {
      if(countEdges == numNodes * (numNodes - 1) / 2)
        break;
      n1 = rand() % numNodes + 1;
      n2 = rand() % numNodes + 1;
      if (n1 == n2)
        continue;
      if (nodes[n1].check_adjacency(n2))
        continue;
      else if (nodes[n2].check_adjacency(n1))
        continue;
      else
      {
        nodes[n1].insert_neighbour(n2);
        nodes[n2].insert_neighbour(n1);
      }

      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile

      graphFile << n1 << " --- " << n2 << endl;
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

  void DFS(int v, int from, int* &visited, int* &from_lst_1, int* &from_lst_2, bool* &is_cycle, listOfObjects<int>* &stack_imp);
  void DFS_normal(int v, int* &visited_array);
  void modifiedDFS();
  void printResults();
};

#endif
