#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"

#endif
using namespace std;

template <typename T> class listOfObjects {
 public:
  T object;
  listOfObjects<T> *next;
  listOfObjects<T> *prev;
  
  // Constructor
  listOfObjects(T initValue) {object = initValue; next = prev = nullptr;}
  listOfObjects() {;}
  // Destructor
  ~listOfObjects() {;}
};
// class for BST node
// bst attribures
class BSTNode
{
public:
  int value;
  BSTNode *left;
  BSTNode *right;
  // constructors
  BSTNode(int value)
  {
    left = nullptr;
    right = nullptr;
    this->value = value;
  }
  BSTNode(){
    left = nullptr;
    right = nullptr;
  }
  // insert other fields and methods as appropriate
};
class BST
{
 

public:
// root of tree
  BSTNode *root;
  BST(int value)
  {
    root = new BSTNode(value);
  }
  BST()
  {
    root = nullptr;
  }
  void insert( int value)
  {
    BSTNode *x = root;
    BSTNode *y = root;
    if (root == nullptr)
    {
      root = new BSTNode(value);
      return;
    }
    else
    {
      while (x != nullptr)
      {
        // if less then left
        if (x->value <= value)
        {
          y = x;
          x = x->right;
         
        }
        else
        {
            y = x;
          x = x->left;
          
        }
      }
      // adding new 
      if (y->value > value)
      {
        y->left = new BSTNode(value);
      }
      else
      {
        y->right = new BSTNode(value);
      }
      return;
    }
  }

  // printing the BST
  void printBST(const string &prefix, bool isLeft = false)
  {
    if (root != nullptr)
    {
      std::cout << prefix;

      std::cout << (isLeft ? "|--" : "|__");

      // print the value of the node
      cout << root->value<< endl;
      BSTNode *curr = root;
      root = curr->left;
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
  int value;
  int arrival;
  int iscycle;
  int visited;
  Node* parent1;
  listOfObjects<Node*>* a;
  Node(){
     visited=0;
     value=-2;
     arrival=-1;
     iscycle=0;
     parent1=nullptr;
     a = new listOfObjects<Node*>(this);
  }
  void visit(){
     visited++;
  }  
  // insert other fields and methods as appropriate
};


class Graph
{
  int numNodes;
  int numEdges;
  fstream graphFile;
  int number_one;
  int component;
  int number_two;
  int arrival;
  listOfObjects<BST*>* myBST = nullptr;
  Node *nodes;

  // Add appropriate fields as necessary for your implementation

public:
  Graph(int nNodes, int nEdges, string gFileName)
  {
    component=0;
    number_one=0;
    number_two=0;
    arrival=0;
    numNodes = nNodes;
    numEdges = nEdges;
    myBST=nullptr;
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
        n1=rand()%numNodes;
        n2=rand()%numNodes;
      } while (n1 == n2);
      bool already_add= false;
      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile
      // if n1>n2 swap wlog
      if (n1>n2){
        swap(n1,n2);
      }
      // adding the element in adjacency list of n1 and n2
      listOfObjects<Node*>* a = nodes[n1].a;
          while (a->next != nullptr)
      {
        if (a->next->object->value == nodes[n2].value){
            already_add=true;
           
             break;
        }
        if (already_add){
          break;
        }
        a=a->next;
      }
      if(!already_add){
       listOfObjects<Node*> *a2 = nodes[n2].a;
      while (a2->next != nullptr)
      {
        a2=a2->next;
      }
      a->next = new listOfObjects<Node*>(&nodes[n2]);
      a2->next = new listOfObjects<Node*>(&nodes[n1]);

      graphFile << n1 + 1 << " " << n2 + 1 << endl;
      countEdges++;
      }
  
    // Add appropriate code as necessary for your implementation
  }
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
  void visit(Node* a,Node* b,BST*c);
};

#endif
