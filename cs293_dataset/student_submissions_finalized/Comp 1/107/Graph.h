#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

class BSTNode{
  public:
    // attributes for BSTNode
    int value;  
    BSTNode *parent;
    BSTNode *right;
    BSTNode *left;

    // constructors for BSTNode
    BSTNode(int value)
    {
      this->value=value;
      parent=nullptr;
      right=nullptr;
      left=nullptr;
    }
    BSTNode(int value, BSTNode *parent)
    {
      this->value=value;
      this->parent=parent;
      right=nullptr;
      left=nullptr;
    }
};

class BST {
  // Add your own field and members here
  public:
    // root
    BSTNode* root;

    // constructors for BST
    BST()
    {
      root=nullptr;
    }

    BST(BSTNode *root)
    {
      this->root=root;
    }

    void insert(int value)
    {
      if(root==nullptr) // Set root
      {
        root=new BSTNode(value);
        return;
      }
      BSTNode *curr=root;
      while(true) // Find position to insert
      {
        if(curr->value>value) // left insert
        {
          if(curr->left==nullptr)
          {
            BSTNode* newNode= new BSTNode(value, curr);
            curr->left=newNode;
            break;
          }
          curr=curr->left;
        }
        else  // right insert
        {
          if(curr->right==nullptr)
          {
            BSTNode* newNode= new BSTNode(value, curr);
            curr->right=newNode;
            break;
          }
          curr=curr->right;
        }
      }
      return;
    }

    // Print BST function
    void printBST(const string& prefix, bool isLeft=false)
    {
        if( root != nullptr )
        {
            cout << prefix;

            cout << (isLeft ? "|--" : "|__" );

            // print the value of the node
            cout << root->value << endl;
            BSTNode *curr = root;
            root = root->left;
            // enter the next tree level - left and right branch
            printBST( prefix + (isLeft ? "│   " : "    "), true);
            root = curr->right;
            printBST( prefix + (isLeft ? "│   " : "    "), false);
            root = curr;
        }
    }

  // Feel free to use the printBST function used earlier
};

// listOfObjects
template <typename T> class listOfObjects {
 public:
  T object;
  listOfObjects<T> *next;
  listOfObjects<T> *prev;
  
  // Constructor
  listOfObjects(T initValue) {object = initValue; next = prev = nullptr;}
  
  // Destructor
  ~listOfObjects() {;}
};


class Node {
 public:
  int value;  // value
  int arrTime;  // arrival time
  bool inCycle; // whether in cycle
  bool isRoot; // whether is root of some DFS tree
  listOfObjects<Node*> *adjacencyStart; // aadjacency list
  Node *parent; // parent of node in DFS tree
  int visited;  // number of times visited

  // Constructor of Node
  Node()
  {
    arrTime=-1;
    adjacencyStart=nullptr;
    parent=nullptr;
    visited=0;
    isRoot=false;
    inCycle=false;
  }
};

class Graph {
  int numNodes; // number of nodes
  int numEdges; // number of edges
  int components; // number of components
  int once; // number of nodes visited once
  int twice;  // number of nodes visited twice
  int cycle;  // number of nodes in cycle
  int counter;  // time counter
  listOfObjects<BST*> *allBSTs; // BST for components
  fstream graphFile;  // graph file

  Node *nodes;  // nodes

  // Add appropriate fields as necessary for your implementation
  
 public:
  // Constructor for graph
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    components=0;
    once=0;
    twice=0;
    cycle=0;
    counter=0;
    allBSTs=nullptr;
    graphFile.open(gFileName, ios::out);

    if (!graphFile.is_open()) {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }

    graphFile << numNodes << endl;
    graphFile << numEdges << endl;

    nodes = new Node[numNodes];
    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
    }

    srand(time(0));
    int n1, n2;
    int countEdges = 0;
    
    while (countEdges < numEdges) {
      do {
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

      graphFile << n1+1 << " " << n2+1 << endl;
      if(nodes[n1].adjacencyStart==nullptr) // No check required for checking whether n1 and n2 are adjacent
      {
        nodes[n1].adjacencyStart=new listOfObjects<Node*>(&nodes[n2]);
      }
      else
      {
        listOfObjects<Node*> *tillNow=nodes[n1].adjacencyStart; // adjacent nodes of n1
        bool alreadyPresent=false;  // Check if already an edge between n1 and n2
        while(tillNow->next!=nullptr)
        {
          if(tillNow->object==&nodes[n2]) // if any of adjacent element except last is n2
          { 
            // already present
            alreadyPresent=true;
            break;
          }
          tillNow=tillNow->next;
        }
        if(tillNow->object==&nodes[n2]) // if last element is n2
        {
          alreadyPresent=true;
        }
        if(alreadyPresent)
        { 
          continue;
        }
        listOfObjects<Node*> *newNode=new listOfObjects<Node*>(&nodes[n2]);
        tillNow->next=newNode;
        newNode->prev=tillNow;
      }
      // No need to check n1 in adjacency list of n2
      if(nodes[n2].adjacencyStart==nullptr)
      {
        nodes[n2].adjacencyStart=new listOfObjects<Node*>(&nodes[n1]);
      }
      else
      {
        listOfObjects<Node*> *tillNow=nodes[n2].adjacencyStart;
        while(tillNow->next!=nullptr)
        {
          tillNow=tillNow->next;
        }
        listOfObjects<Node*> *newNode=new listOfObjects<Node*>(&nodes[n1]);
        tillNow->next=newNode;
        newNode->prev=tillNow;
      }
      countEdges++;
    }

    // Add appropriate code as necessary for your implementation
  }
      
  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;
    // Add appropriate code as necessary for your implementation
  }

  // Add appropriate method declarations as necessary for your implementation

  void modifiedDFSComponent(Node *start, Node* parent, BST *bst);
  void modifiedDFS();
  void printResults();
};

#endif
