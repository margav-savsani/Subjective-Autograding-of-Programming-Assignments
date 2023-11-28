#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include <string>
#include <vector>

#define PRE_ORDER -1
#define PRE_ORDER -1
#define PRE_ORDER -1

using namespace std;

// A Doubly linked list
template <typename T>
class linkedlist
{
public:
    T object;
    T index; // Tells whose list is this.
    linkedlist<T> *next;
    linkedlist<T> *prev;

    // Constructor
    linkedlist(T initValue)
    {
        object = initValue;
        next = prev = nullptr;
    }
    linkedlist()
    {
        // In the Default constructor specify the value of T as -1.
        next = prev = nullptr;
    }
    // Function to insert into a linked list
    void insert_ll(T a)
    {
        // i.e we are inserting into list for the first time
        if (this->object == -1)
        {
            this->object = a;
            return;
        }
        linkedlist<T> *iterator = this;
        // Untill we reach the end of the list
        while (iterator->next != NULL)
        {
            iterator = iterator->next;
        }
        iterator->next = new linkedlist(a);
    }
    // Find whether the object is present in the list or not
    bool find_ll(T a)
    {
        linkedlist<T> *iterator = this;
        if (iterator->object == -1) // If nothing is inserted
        {
            return false;
        }
        while (iterator != NULL)
        {
            if (iterator->object == a)
            {
                return true;
            }
            iterator = iterator->next;
        }
        return false;
    }
    // Destructor
    ~linkedlist() { ; }
};

struct TreeNode
{
    int value;        // Price
    TreeNode *left;   // Left Child of this Node (NULL, if None)
    TreeNode *right;  // Right Child of this Node (NULL, if None)
    TreeNode *parent; // The Parent Node, NULL in case of Root

    TreeNode() : value(0), left(nullptr), right(nullptr) {}
    TreeNode(int gnode) : value(gnode), left(nullptr), right(nullptr) {}
    TreeNode(int gnode, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : value(gnode), left(leftChild), right(rightChild), parent(parent) {}
};

class BST
{
    TreeNode *root;

public:
    BST()
    { // Initialising the tree
        this->root = new TreeNode;
        this->root = NULL;
    }

    BST(TreeNode *root)
    { // Initialising the tree
        this->root = new TreeNode;
        this->root = root;
    }

    bool insert(int value)
    {
        TreeNode *y = NULL;                // Parent before whom the new node has to be inserted.
        TreeNode *x = this->root;          // initialising the x by root.
        TreeNode *z = new TreeNode(value); // New node to be inserted in the tree.
        if (x == NULL)
        { // If the root pointer is null then add the given node to root node itself.
            this->root = new TreeNode;
            this->root->value = value;
            return true;
        }
        while (x != NULL)
        { // Find till there is a place to fill.
            y = x;
            if ((x->value) > value)
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }
        z->parent = y; // Alloting the parent of z as y.

        // ALLOTING THE CHILD OF Y TO Z.
        if (z->value < y->value)
        {
            y->left = z;
            return true;
        }
        else
        {
            y->right = z;
            return true;
        }
        return false; // case when the value is equal and insertion cannot be done
    }

    bool find(int value)
    {
        TreeNode *x = root; // STARTING FROM ROOT NODE
        while (x != NULL && (x->value != value))
        {
            // SEARCH TILL THE EXACT STATION IS FOUND
            // OR WE REACH A NULL.
            if (value < (x->value))
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }
        if (x == NULL)
        { // IF NO SUCH NODE
            return false;
        }
        else
        { // TRUE IF NODE IS FOUND.
            return true;
        }
    }

    // Adapted from Adrian Schneider's code on StackOverflow
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

// The Node of the Graph
class Node
{
public:
    // The value that is present in the Node.
    int value;

    // The parents of this Node, this would store all the parents of this Node.
    int parents[2];

    // The total number of parents of this Node.
    int totalparents;

    // Inserting the parent of this Node into the structure of the Node
    void insert_parent(int x)
    {
        parents[totalparents] = x;
        totalparents++;
    }
    Node()
    {
        // Dummy initialisation of the parent variables.
        totalparents = 0;
        parents[0] = -1;
        parents[1] = -1;
    }
};

class Graph
{
  int numNodes;
  int numEdges;

  int connectedcomp;
  fstream graphFile;

  // The array of the Nodes
  Node *nodes;

  // Visited Array
  // (It will store the number of times a Node is visited in the DFS search)
  int *visits;

  // The adjacency list of the Nodes 
  linkedlist<int> *adjacenylist;

  // The array stores whether an element is in a cycle or not.
  int *isinacycle;

public:
  Graph(int nNodes, int nEdges, string gFileName)
  {
    numNodes = nNodes;
    numEdges = nEdges;
    connectedcomp = 0;
    graphFile.open(gFileName, ios::out);
    if (!graphFile.is_open())
    {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }

    graphFile << numNodes << endl;
    graphFile << numEdges << endl;

    nodes = new Node[numNodes];

    // Assigning memory to the adjaceny list
    adjacenylist = new linkedlist<int>[numNodes];
    for (int i = 0; i < numNodes; i++)
    {
      // Initialising all the values by -1
      adjacenylist[i].object = -1;
      adjacenylist[i].index = (i + 1);
    }
    // Assigning a new memory to visits Array
    visits = new int[numNodes];

    // Initialising the Visits
    for (int i = 0; i < numNodes; i++)
    {
      visits[i] = 0;
    }

    if (nodes == nullptr)
    {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++)
    {
      nodes[i].value = i + 1;
    }

    isinacycle = new int[numNodes];

    for (int i = 0; i < numNodes; i++)
    { // Initialising all the values as false
      isinacycle[i] = 0;
    }
    srand(time(0));
    int n1, n2;
    int countEdges = 0;

    while (countEdges < numEdges)
    {
      while (true)
      {
        n1 = rand() % numNodes;
        n2 = rand() % numNodes;
        if (n1 == n2)
          continue;
        else
          break;
      }

      // If there is already an edge present, i.e
      // effectively one node in adjacency of the other.
      if (adjacenylist[n1].find_ll(n2) || adjacenylist[n2].find_ll(n1))
      {
        continue;
      }
      // Finally we will get two such nodes that are not connected.

      // Adding an edge is the same as inserting either one in the adjacency of the other.
      adjacenylist[n1].insert_ll(n2);
      adjacenylist[n2].insert_ll(n1);

      graphFile << n1 + 1 << " " << n2 + 1 << endl;
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
  void DFS(int sourceNode, BST &t);
  void printResults();
};

#endif
