#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

struct TreeNode{
    int value;		// Price
    TreeNode *left;	// Left Child of this Node (NULL, if None)
    TreeNode *right;	// Right Child of this Node (NULL, if None)
    TreeNode *parent;	// The Parent Node, NULL in case of Root

    // Constructors
  
    TreeNode() :value(0), left(nullptr), right(nullptr) {}
    TreeNode(int v) : value(v), left(nullptr), right(nullptr) {}
    TreeNode(int v, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : value(v), left(leftChild), right(rightChild), parent(parent) {}
};

class BST {
  // Add your own field and members here

  // Feel free to use the printBST function used earlier
  TreeNode *root;

  public:
    BST();
    BST(TreeNode *root);
    void insert(int value);
    void printBST(const string& prefix, bool isLeft);
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


class Node {
 public:
  int value;
  int visited_count;
  listOfObjects<Node>* adj;
  // insert other fields and methods as appropriate
  Node(){
    value=0;
    visited_count=0;
  }
  Node(int val){
    value=val;
    visited_count=0;
  }
};

bool find(int value, listOfObjects<Node>* adj){
  listOfObjects<Node>* tmp=adj;
  while(tmp!=nullptr){
    if(tmp->object.value == value){
      return true;
    }
    tmp=tmp->prev;
  }
  return false;
}

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;
  int cycles;
  Node *nodes;

  // Add appropriate fields as necessary for your implementation
  // listOfObjects<Node>* *adjlist;

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
    if(numEdges<=2){cycles=0;}
    else{
      cycles = numNodes/2 + rand()%(numEdges/2);
    }
    nodes = new Node[numNodes];
    // cout<<"Hi1"<<endl;
    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }
    // cout<<"Hi2"<<endl;
    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
    }

    // adjlist = new listOfObjects<Node>*[numNodes];
    // for (int i=0; i<numNodes; i++){
    //   adjlist[i]->object = nodes[i];
    // }
    // cout<<"Hi2"<<endl;
    srand(time(0));
    int n1, n2;
    int countEdges = 0;
    
    while (countEdges < numEdges) {
      do {
        n1 = rand() % numNodes;
        n2 = rand() % numNodes;
      } while (n1 == n2);

      // Node node1 = ;
      // Node node2 = nodes[n2];

      listOfObjects<Node>* tmp1 = nodes[n1].adj;
      // cout<<"Hi2"<<endl;
      if(find(n2+1, nodes[n1].adj)){continue;}

      if(tmp1 == nullptr){
        tmp1 = new listOfObjects<Node> (Node(n2+1));
      }
      else {
        tmp1->next = new listOfObjects<Node> (Node(n2+1));
        tmp1->next->prev = tmp1;
        tmp1 = tmp1->next;
      }
      nodes[n1].adj = tmp1;


      listOfObjects<Node>* tmp2 = nodes[n2].adj;
      if(find(n1+1, nodes[n2].adj)){continue;}

      if(tmp2 == nullptr){
        tmp2 = new listOfObjects<Node> (Node(n1+1));
      }
      else {
        tmp2->next = new listOfObjects<Node> (Node(n1+1));
        tmp2->next->prev = tmp2;
        tmp2 = tmp2->next;
      }
      nodes[n2].adj = tmp2;

      graphFile << n1+1 <<"  "<<n2+1<<endl;
      countEdges++;
      
    }

  }
      
  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    // cout<<"Hi4"<<endl;
    delete[] nodes;
    // cout<<"Hi5"<<endl;
    // Add appropriate code as necessary for your implementation
  }
  
  listOfObjects<BST*>*bstlist;
  int connected_comps=0;
  // Add appropriate method declarations as necessary for your implementation
  void DFS(Node n,Node p, BST* b);
  void modifiedDFS();
  void printResults();
};

#endif
