#ifndef GRAPH_BST_H
#define GRAPH_BST_H

// #ifndef STD_HEADERS_H
#include "std_headers.h"
using namespace std;
// #endif

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
  int value; //The value of stored in the node
  int visited;// How many times it is visited
  int arrtime; //First time of Arrival in the node
  bool inCycle; // If it is present in cycle
  Node *dfsparent; //The original parent of the node(meaning when the node was first encountered)
  listOfObjects<Node *> *adjacency_list; //The adjacency list
  listOfObjects<Node *> *tail_list;
  Node *left;	// Left Child of this Node (NULL, if None)
  Node *right;	// Right Child of this Node (NULL, if None)
  Node *parent;	// The Parent Node, NULL in case of Roo

  Node(){
    //Initialising the parameters
    value = -1;
    arrtime = 0;
    inCycle = false;
    adjacency_list = nullptr;
    visited = 0;
    left=nullptr;
    right = nullptr;
    parent = nullptr;
    dfsparent = nullptr;
  }
  
};

class BST {
  // Add your own field and members here
  Node* root; //The root of the binary search tree

public:
  BST(Node *root){this->root = root;}

  bool insert(Node *new_node) { 
    Node* y = nullptr;
    Node* x = root;
    while (x!=nullptr){
        y = x;
        // if (JourneyCode == x->JourneyCode && price == x->price) return false;
        if(new_node->value < x->value) x = x->left;
        else x = x->right;
    }
    Node *z = new Node();
    z->value = new_node->value;
    z->parent = y;
    if (y == nullptr) root = z;
    else if (z->value < y->value) y->left = z;
    else y->right = z;
    return true;
  }

  void printBST(const string& prefix, bool isLeft=false)
  { //using previous printBST
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->value << endl;
        Node *curr = root;
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

class Graph {
  int numNodes;
  int numEdges;
  int timecounter;
  int numConnectedComp;
  fstream graphFile;
  // fstream inputdata;
  listOfObjects<BST *> *trees;
  listOfObjects<BST *> *tail_trees;

  Node *nodes;

  // Add appropriate fields as necessary for your implementation
  
 public:

  bool visit(int n1, int n2){
    listOfObjects<Node *> *curNode = nodes[n1].adjacency_list;
    while(curNode!=nullptr){
      if(curNode->object->value == n2+1) return true;
      curNode = curNode->next;
    }
    return false;
  }

  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    timecounter = 0;
    numEdges = nEdges;
    numConnectedComp = 0;
    trees = nullptr;
    tail_trees = nullptr;
    graphFile.open(gFileName, ios::out);
    // inputdata.open("data");
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
      // string word;
      // while(inputdata >> word){
      //   n1 = stoi(word)-1;
      //   inputdata >> word;
      //   n2 = stoi(word)-1;
      // Do this if 

      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile
      if(!visit(n1, n2)){

      listOfObjects<Node *> *newlistobject1 = new listOfObjects<Node *>(&nodes[n1]);
      listOfObjects<Node *> *newlistobject2 = new listOfObjects<Node *>(&nodes[n2]);

      if(nodes[n1].adjacency_list == nullptr){
        nodes[n1].adjacency_list = newlistobject2;
        nodes[n1].tail_list = newlistobject2;
      }
      else{
        nodes[n1].tail_list->next = newlistobject2;
        newlistobject2->prev = nodes[n1].tail_list;
        nodes[n1].tail_list = nodes[n1].tail_list->next;
      }
 
      if(nodes[n2].adjacency_list == nullptr){
        nodes[n2].adjacency_list = newlistobject1;
        nodes[n2].tail_list = newlistobject1;
      }
      else{
        nodes[n2].tail_list->next = newlistobject1;
        newlistobject1->prev = nodes[n2].tail_list;
        nodes[n2].tail_list = nodes[n2].tail_list->next;
      }

      graphFile << n1+1 << " " << n2+1 << endl;
      countEdges++;
    }
    }
  }

  void DFS(Node* currentNode,Node* parent, int &recursionLevel, listOfObjects<BST *>* tail_trees);
      
  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;
    // Add appropriate code as necessary for your implementation
  }

  // Add appropriate method declarations as necessary for your implementation

  void modifiedDFS();
  void printResults();
};

#endif
