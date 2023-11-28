

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#define GRAPH_BST_H

class listOfObjects
{
public:
  int value;
  listOfObjects *next;
  listOfObjects *prev;

  // Constructor
  listOfObjects(int initValue)
  {
    value = initValue;
    next = prev = nullptr;
  }
  listOfObjects() { next = prev = nullptr; }

  // Destructor
  ~listOfObjects() { ; }
};
class Node
{
public:
  int value;
  Node *left;
  Node *right;

  Node(int val)
  {
    value = val;
    left = right = nullptr;
  }
  Node() {
    value = 0;
    left = right = nullptr;
  }

  // insert other fields and methods as appropriate
};

class BST
{
public:
  Node *root;

  BST(){
    root=nullptr;
  }

  void printBST(const string &prefix, bool isLeft = false)
  {

    if (root != nullptr)
    {
      cout << prefix;

      cout << (isLeft ? "|--" : "|__");

      // print the value of the node
      cout << root->value + 1 << endl;
      Node *curr = root;
      root = root->left;
      // enter the next tree level - left and right branch
      printBST(prefix + (isLeft ? "│   " : "    "), true);
      root = curr->right;
      printBST(prefix + (isLeft ? "│   " : "    "), false);
      root = curr;
    }
  }

  bool insert(int value)
  {
    Node *v = root;
    Node *p = nullptr;
    int flag = 0;
  
    while (v != nullptr)
    {
      flag = 1;

      if (v->value > value)
      {
        p = v;
        v = (v->left);
      }
      else
      {
        p = v;
        v = (v->right);
      }
    }
    v = new Node(value);
    if (p != nullptr)
    {
      if (p->value > value)
      {
        p->left = v;
      }
      else
      {
        p->right = v;
      }
    }
    if (flag == 0)
    {
      root = v;
    }

    return true;
  }

  // Add your own field and members here

  // Feel free to use the printBST function used earlier
};

class listOfBST
{
public:
  BST value;
  listOfBST *next;
  listOfBST *prev;

  // Constructor
  listOfBST(BST initValue)
  {
    value = initValue;
    next = prev = nullptr;
  }
  listOfBST() { next = prev = nullptr; }

  // Destructor
  ~listOfBST() { ; }
};

class Graph
{
  int numNodes;
  int numEdges;
  fstream graphFile;
  int *arrayvisited;
  int *parent1;
  int *parent2;
  // int *child1;
  // int *child2;
  // int *count;
  // int *recur1;
  // int *recur2;
  // int *recur;
  int *dept;
  int *backtrack;
  int depttime;
  bool*visit2;

  listOfObjects **Adjacencylist;

  listOfBST *Trees;

  Node *nodes;
  int connected;

  // Add appropriate fields as necessary for your implementation

public:
  Graph(int nNodes, int nEdges, string gFileName)
  {
    numNodes = nNodes;
    depttime=0;

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

    arrayvisited = new int[numNodes];
    parent1 = new int[numNodes];
    parent2 = new int[numNodes];
    
    dept=new int[numNodes];
    backtrack=new int[numNodes];
    visit2=new bool[numNodes];
    for (int i = 0; i < numNodes; i++)
    {
      arrayvisited[i] = 0;
      parent1[i] = -1;
      parent2[i] = -1;
      
      backtrack[i]=-1;
      dept[i]=-1;
      visit2[i]=false;
    }
    Adjacencylist = new listOfObjects *[numNodes];
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
        // cin>>n1;
        // cin>>n2;   
        n1 = rand() % numNodes;
        n2 = rand() % numNodes;
      } while (n1 == n2);

      

      listOfObjects *listn1 = Adjacencylist[n1];
      listOfObjects *prev;

      int alreadypresent = 0;
      int check=0;
      while (listn1 != nullptr)
      {
        
        prev = listn1;
        
        check=1;
        if (listn1->value == n2)
        {
          alreadypresent = 1;
          
        }
        listn1 = listn1->next;
      }
      if (alreadypresent == 0)
      {
       
        listOfObjects *element = new listOfObjects(n2);

        if (check!=0)
        {
          listn1 = element;
          prev->next = listn1;
          listn1->prev = prev;
        }
        else
        {
         
          Adjacencylist[n1] = new listOfObjects(n2);
        }
        
       

        listOfObjects *listn2 = Adjacencylist[n2];
        listOfObjects *prev2;
        int count=0;

        while (listn2 != nullptr)
        {
          count++;
         
          prev2 = listn2;
          listn2 = listn2->next;
        }

        listOfObjects *element2 = new listOfObjects(n1);

        if (count!=0)
        {
          
          listn2 = element2;
          
          prev2->next = listn2;
          listn2->prev = prev2;
        }
        else
        {
         
          Adjacencylist[n2] = new listOfObjects(n1);
        }
        if(Adjacencylist[n2]==nullptr){
         
        }
        graphFile << n1 + 1 << " " << n2 + 1 << endl;
        countEdges++;
      }
    }
    
    connected = 0;

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
  void DFS(Node node, int i, listOfBST *Tree, int t);

  void modifiedDFS();
  void printResults();
};

#endif
