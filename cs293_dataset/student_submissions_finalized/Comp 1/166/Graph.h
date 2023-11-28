#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#include <bits/stdc++.h>
using namespace std;
#endif

class TreeNode{
  public:
  int value; //value stored
  TreeNode *parent;
  TreeNode *left;
  TreeNode *right;

  TreeNode() : value(0), parent(nullptr), left(nullptr), right(nullptr){}

  TreeNode(int val) : value(val), parent(nullptr), left(nullptr), right(nullptr){}
 
  TreeNode(int val, TreeNode *left, TreeNode *right, TreeNode *parent) : value(val), left(left), right(right), parent(parent){} //constructors

};

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

class BST {
  TreeNode *root;
  
  public:

  BST(){root=nullptr;};
  BST(TreeNode *curr_root); //constructors
    
  void insert(int value){
    if(root==nullptr){
      root=new TreeNode(value);
      return;
    }                  //if root is nullptr
    TreeNode *curr = root;
    while(true){
      if(value<=curr->value){
        if(curr->right==nullptr){
          curr->right = new TreeNode(value,nullptr,nullptr,curr);
          return;
        }
        else{
          curr=curr->right;
        }
      }
      else{
        if(value>curr->value){
          if(curr->left==nullptr){
            curr->left = new TreeNode(value,nullptr,nullptr,curr);
            return;
          }
          else{
            curr=curr->left;
          }
        }
      }
    }
  }
  void printBST(const string& prefix, bool isLeft=false)
  {
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->value << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
	// Are there any other siblings to the right?
	bool rightSiblingPresent = (isLeft && (curr->parent->right != nullptr));
        printBST( prefix + (rightSiblingPresent ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (rightSiblingPresent ? "│   " : "    "), false);
        root = curr;
    }
  }
  
};

class Node {
 public:
  int value;     //value stored
  int visits;    //number of visits made to that node while dfs

  Node(){};
  Node(int a){value=a;}
  listOfObjects<Node *> *elist; //adjancency list
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;
  int totn=0; //total vertices
  int v1=0;  //vertices with single visit
  int v2=0;  //vertices with 2 visits
  int comp=0; //number of components
  listOfObjects<BST *> *blist;  //list to store the BSTs which are to be printed

  Node *nodes;

  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
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
      createedge(&nodes[n1],&nodes[n2]);
      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile

      graphFile << n1+1 << " " << n2+1 << endl;
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

  bool createedge(Node *n1,Node *n2){
    Node *t1;
    t1=n1;
    Node *t2;
    t2=n2;
    bool got=true;  //bool is true if edge is not present previously
    listOfObjects<Node *> *uwu;
    uwu=n1->elist;  //adjacency list of node n1
    while(uwu!=nullptr){
      if(uwu->object==n2){
        got=false;
      }
      uwu=uwu->next;
    }
    listOfObjects<Node *> *owo;
    owo=n2->elist;  //adjancency list of node n2
    while(owo!=nullptr){
      if(owo->object==n1){
        got=false;
      }
      owo=owo->next;
    }  //searching if the edge is already present by checking the adjancency list 
    if(got){  //if the edge is not present
      if(t1->elist==nullptr){
      listOfObjects<Node *> *tempu;
      tempu = new listOfObjects<Node *>(new Node(-1));
      tempu->object=n2;
      tempu->next=nullptr;
      tempu->prev=nullptr;
      t1->elist=tempu;
    }  
    else{
      listOfObjects<Node *> *tut;
      tut = new listOfObjects<Node *>(new Node(-1));
      tut=t1->elist;
      while(tut->next!=nullptr){
        tut=tut->next;
      } //going till the tail
      listOfObjects<Node *> *tempu;
      tempu = new listOfObjects<Node *>(new Node(-1));
      tempu->object=n2;
      tempu->next=nullptr;
      tempu->prev=tut;
      tut->next=tempu;
    }
    if(t2->elist==nullptr){
      listOfObjects<Node *> *tempu;
      tempu = new listOfObjects<Node *>(new Node(-1));
      tempu->object=n1;
      tempu->next=nullptr;
      tempu->prev=nullptr;
      t2->elist=tempu;
    }
    else{
      listOfObjects<Node *> *tut;
      tut = new listOfObjects<Node *>(new Node(-1));
      tut=t2->elist;
      while(tut->next!=nullptr){
        tut=tut->next;
      } //going to the tail
      listOfObjects<Node *> *tempu;
      tempu = new listOfObjects<Node *>(new Node(-1));
      tempu->object=n1;
      tempu->next=nullptr;
      tempu->prev=tut;
      tut->next=tempu;
    }
    } //adding to the adjacency lists
    return true;
  }

  // Add appropriate method declarations as necessary for your implementation

  void modifiedDFS();
  void printResults();
};

#endif
