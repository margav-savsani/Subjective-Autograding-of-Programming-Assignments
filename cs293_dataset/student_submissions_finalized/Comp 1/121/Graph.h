#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
using namespace std;

template <typename T> class list{
  public:
  T object;
  list<T> *prev, *next ;

  list(T initvalue){
    object = initvalue;
    next = prev = nullptr;
  }
};

class Node {
 public:
  int value;
  int time= 99000;
  list<Node*> * adjacency = nullptr; //for Graph
  list<Node*> * tailAdjacency = nullptr;
  list<Node*> * parents = nullptr;
  list<Node*> * tailparents = nullptr;
  Node* left= nullptr, *right=nullptr;  //for BST - left and right are trivial  
  // Node* next =nullptr; Node*prev = nullptr; //for linked list
  
  // insert other fields and methods as appropriate
  Node* isAdjacent(Node a){ //returns true if the given node is present in adjacency list
    if (adjacency==nullptr){
      return nullptr;
    }
    list<Node*>* curr = adjacency;
    while(curr!=nullptr){
      if(curr->object->value==a.value){
        return curr->object;
      }
      curr = curr->next;
    }
    return nullptr;
  }
  bool isParent(Node a){ //returns true if the given node is present in adjacency list
    if (parents==nullptr){
      return false;
    }
    list<Node*>* curr = parents;
    while(curr!=nullptr){
      if(curr->object->value==a.value){
        return true;
      }
      curr = curr->next;
    }
    return false;
  }

  bool insertAdj(Node* a){
    if (adjacency==nullptr){
      adjacency = new list<Node*>(a);
      tailAdjacency = adjacency;
      return true;
    }
    else if(isAdjacent(*a)){
      return false;
    }
    else{
      tailAdjacency->next = new list<Node*> (a);
      tailAdjacency->next->prev = tailAdjacency;
      tailAdjacency = tailAdjacency->next;
      return true;
    }
    return false;
  }
  bool insertParent(Node* a){
    if (parents==nullptr){
      parents = new list<Node*>(a);
      tailparents = parents;
      return true;
    }
    else if(isParent(*a)){
      return false;
    }
    else{
      tailparents->next = new list<Node*> (a);
      tailparents->next->prev = tailparents;
      tailparents = tailparents->next;
      return true;
    }
    return false;
  }
};

class BST {
  public:
  // Add your own field and members here
  Node *root;

  BST(int a){
    root = new Node();
    root->value=a;
    return;
  }
  // BST(){
  //   root = nullptr;
  // }
  void insert(int b){
    Node* curr = root;
    if(root==nullptr){
      root=new Node();
      root->value=b;
    }
    // if(b <= curr->value){
    //   curr->
    // }
    // bool isready=false;
    bool isleft;
    while(true){
      if(b<=curr->value){
        if(curr->left==nullptr){
          // isready = true;
          isleft = true;
          break;
        }
        else{
          curr = curr->left;
        }
      }
      else if(b > curr->value){
        if(curr->right == nullptr){
          // isready=true;
          isleft = false;
          break;
        }
        else{
          curr = curr->right;
        }
      }
    }
    if (isleft){
      curr->left = new Node();
      curr->left->value = b;
    }
    else{
      curr->right = new Node();
      curr->right->value = b;
    }
  }
  // Feel free to use the printBST function used earlier
  void printBinaryTree(Node *root, const string& prefix, bool isLeft, fstream *file){
    if( root != nullptr )   {
      cout << prefix;
      
      cout << (isLeft ? "|--" : "|__" );
      
      // print the value of the node
      cout<<root->value<<endl;
      // cout << endl;
      Node *curr = root;
      root = root->left;
      // enter the next tree level - left and right branch
      printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), true, file);
      root = curr->right;
      printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), false, file);
      root = curr;
    }
    else {
      cout<<prefix;
      cout<<endl;
    }
  }
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;
  bool * iscircle;
  
  int t=0;
  Node *nodes;
  int * visited;
  int numConComp=0; 

  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    iscircle = new bool[nNodes];
    //initializing the visited array
    visited = new int[numNodes];
    for (int i=0; i<numNodes; i++){
      visited[i] = 0;
      iscircle[i] = false;
    }
    graphFile.open(gFileName, ios::out);
    if (numEdges > (numNodes*(numNodes-1))/2 ) {
      cerr << "This many edges are not possible"<< endl;
      return;
    }
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
      nodes[i].value = i+1;   //value in ith node is i+1 
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
      if (nodes[n1].isAdjacent(nodes[n2])){
        continue;
      }
      nodes[n1].insertAdj(&(nodes[n2]));
      nodes[n2].insertAdj(&(nodes[n1]));
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

  // Add appropriate method declarations as necessary for your implementation
  void modifiedDFS();
  void printResults();
  void DFS(int v, int parent, BST* dfsbst);
};

#endif
