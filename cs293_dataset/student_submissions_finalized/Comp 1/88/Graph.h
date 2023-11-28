#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

template <typename T> class listOfObjects { // linked list data structure
 public:
  T object;
  listOfObjects<T> *next;
  listOfObjects<T> *prev;
  
  // Constructor
  listOfObjects(T initValue) {object = initValue; next = prev = nullptr;}
  
  // Destructor
  ~listOfObjects() {;}
};

class BSTNode {
  public:
  int value;
  BSTNode *left;
  BSTNode *right;
  BSTNode *parent;
  BSTNode(int val){
    value=val;
    left=right=parent=nullptr;
  }
  BSTNode(int val, BSTNode *l, BSTNode *r, BSTNode *p){
    value=val;
    left=l;
    right=r;
    parent=p;
  }
  void printInfo(){
    cout<<value;
  }
};

class BST {
  public:
  BSTNode *root;

  BST(){
    root = nullptr;
  }
  void insert(int val){ // insertion operation for BST
    if(root==nullptr){
      root = new BSTNode(val);
    }
    else{
      BSTNode *currNode = root, *prevNode = nullptr;
      while(currNode != nullptr){
        prevNode = currNode;
        if(val<currNode->value){
          currNode=currNode->left;
        }
        else{
          currNode=currNode->right;
        }
      }
      if(val<prevNode->value){
        prevNode->left = new BSTNode(val, nullptr, nullptr, prevNode);
      }
      else{
        prevNode->right = new BSTNode(val, nullptr, nullptr, prevNode);
      }
    }
  }
  void printBinaryTree(BSTNode *root, const string& prefix, bool isLeft)
  { // taken from previous lab
    if( root != nullptr )   {
      cout << prefix;
      
      cout << (isLeft ? "|--" : "|__" );
      
      // print the value of the node
      root->printInfo();
      cout << endl;
      BSTNode *curr = root;
      root = root->left;
      // enter the next tree level - left and right branch
      printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), true);
      root = curr->right;
      printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), false);
      root = curr;
    }
  }
};

class Node {
 public:
  int value;
  listOfObjects<Node *> *adjacent;
  Node(){
    adjacent = nullptr;
  }
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;
  int conns, nodes_once, nodes_twice, nodes_cycle; // output parameters
  listOfObjects<BST *> *all_trees; // all binary trees
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    conns=nodes_once=nodes_twice=nodes_cycle=0;
    all_trees = nullptr;
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

      // check if edge already stored
      listOfObjects<Node *> *currAdjacentNode = nodes[n1].adjacent;
      bool found=false;
      while(currAdjacentNode != nullptr){
        if(currAdjacentNode->object->value == n2+1){
          found=true;
        }
        currAdjacentNode = currAdjacentNode->next;
      }
      if(!found){ // stores each node in adjacency list of the the other node
        listOfObjects<Node *> *temp = nodes[n1].adjacent;
        nodes[n1].adjacent = new listOfObjects<Node *>(nodes+n2);
        if(temp != nullptr){
          nodes[n1].adjacent->next = temp;
          temp->prev = nodes[n1].adjacent;
        }
        temp = nodes[n2].adjacent;
        nodes[n2].adjacent = new listOfObjects<Node *>(nodes+n1);
        if(temp != nullptr){
          nodes[n2].adjacent->next = temp;
          temp->prev = nodes[n2].adjacent;
        }
        graphFile << n1+1 << " " << n2+1 << endl;
        countEdges++;
      }
    }

    // Add appropriate code as necessary for your implementation
    // FOR DEBUGGING ONLY
    // for (int i=0;i<numNodes;i++){
    //   listOfObjects<Node *> *currAdjacentNode = nodes[i].adjacent;
    //   while(currAdjacentNode != nullptr){
    //     cout<<currAdjacentNode->object->value<<" ";
    //     currAdjacentNode = currAdjacentNode->next;
    //   }
    //   cout<<endl;
    // }
  }
      
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
