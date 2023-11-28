#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
using namespace std;

//list class to store adjecent nodes of a vertex of graph
template <typename T> class list{
  public:
  T object;                         //adjecent node of a vertex of graph
  list<T> *next,*prev;

  list(T inval){
    object=inval;
    prev=next=nullptr;
  }

};

//class to create nodes for BST
class BSTNode{
public:
  int value;                          //value at node
  BSTNode *parent,*left,*right;
  
  //constructor
  BSTNode(int x){
    parent=left=right=nullptr;
    value=x;
  }

};

//BST class to create Binary Search Tree
class BST {
  // Add your own field and members here
  BSTNode *root;                              //root of tree

  public:

  //constructor
  BST(){}
  BST(BSTNode *root){
    this->root=root; 
  }

  //inserts a node corresponding to given value
  void insert(int val);

  //prints complete Binary search tree
  void printBST(const string& prefix, bool isLeft);

  // Feel free to use the printBST function used earlier
};


//node class to create nodes for graph
class Node {
 public:
  int value;                    //value stored at node
  list<Node*>* adjecency;       //adjecency list of a vertex in graph
  bool isInCycle;               //variable representing that it is present in a cycle or not

  //constructors
  Node(int val){
    value=val;
    adjecency=nullptr;
    isInCycle=false;
  }
  Node(){
    value=-999;
    isInCycle=false;
    adjecency=nullptr;
  }

  //member function to find whether a node is adjecent to another node
  bool isAdjecent(Node* node){
    list<Node*>*curr= adjecency;
    while(curr!=nullptr){                       //iterating over adjecency list
      if(curr->object==node)return true;
      curr=curr->next;
    }
    return false;
  }

  //inserts a node in adjecency list of a given node if it is not already present
  bool insertAdj(Node* node){
    if(isAdjecent(node))return false;                       //checking node is already present or not

    if(adjecency==nullptr){                             //null list case
      adjecency=new list<Node*>(node);
      return true;
    }

    list<Node*>*curr= adjecency;                      //adding to list
    while(curr->next!=nullptr){
      curr=curr->next;
    }
    curr->next=new list<Node*>(node);
    return true;
  }
  // insert other fields and methods as appropriate
};

//graph class to create graph
class Graph {
  int numNodes;                         //number of nodes in graph
  int numEdges;                         //number of edges in graph
  fstream graphFile;        

  int* visited;                         //visited array to store node is viseted or not while DFS
  int* parent;                          //parent array to store parent nodes of vertices in DFS
  Node *nodes;                          //array of nodes present  in graph

  list<BST>* BSTlist;                   //list to store BST created during DFS

  // Add appropriate fields as necessary for your implementation
  
 public:
  //constructor
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;

    //initializing parent and visited array
    visited=new int[numNodes];
    parent=new int[numNodes];
    for(int i=0;i<numNodes;i++){
      visited[i]=0;
      parent[i]=-1;
    }

    BSTlist=nullptr;
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

    //storing nodes in array
    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
    }

    srand(time(0));
    // srand(0);
    int n1, n2;
    int countEdges = 0;
    
    //generating edges for graph
    while (countEdges < numEdges) {
      do {
        n1 = rand() % numNodes;
        n2 = rand() % numNodes;
      } while (n1 == n2);

      // cin>>n1;
      // cin>>n2;

      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile

      //inserting adjecent nodes to adjecency list
      if(nodes[n1].insertAdj(&(nodes[n2]))){
        nodes[n2].insertAdj(&(nodes[n1]));
        graphFile << n1+1 << " " << n2+1 << endl;
        countEdges++;
      }
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

  //Does the modified form of DFS
  void DFS(int node,BST* tree);

  //checks that if any cycle possible between nodes
  bool isCycle(int child,int par);

  //calls DFS on all nodes and creates a tree of values for each connected components
  void modifiedDFS();

  //prints result asked to do
  void printResults();
};

#endif
