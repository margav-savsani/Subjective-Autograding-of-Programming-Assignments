#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif


class Node {
 public:
  int value;
  //int times;
  Node *left;
  Node *right;
  Node* parent;
  Node *next;

  Node(){};
  // Node(int val){
  //   value = val;
  // }

  Node(int val, Node* l=nullptr, Node *r=nullptr , Node *p=nullptr){
    value = val;
    left = l;
    right = r;
    parent =p;
    //times = 1;
  }
  // insert other fields and methods as appropriate
};


class BST {
  // Add your own field and members here

  // Feel free to use the printBST function used earlier 
  public:
    Node *root;
    BST *next;
    BST(){
      root = nullptr;
    }
    BST(Node *r){
      root = r;
    }
    void insert(int val);
    void printBST(const string& prefix, bool isLeft);
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;
  //int inCycle=0;
  bool* inCycle;
  int cnt = 0 ;
  Node *nodes;
  int *visited ;
  BST * bst= new BST();
  int *parent_node ;
  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    visited = new int[numNodes];
    parent_node = new int[numNodes];
    inCycle = new bool[numNodes];
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
      visited[i]=0;
      inCycle[i]=false;
      parent_node[i]=0;
    }

    srand(time(0));
    int n1, n2;
    int countEdges = 0;
    
    while (countEdges < numEdges) {
      do {
	      n1 = rand() % numNodes;
	      n2 = rand() % numNodes;
      } while (n1 == n2);
      Node *trav = &nodes[n1];
      bool found = false;
      while(trav->next!=nullptr){
        if(trav->next->value == n2+1){
          found = true;
          break;
        }
        trav = trav->next;
      }
      
      if(found == true){
        continue;
      }

      else{
        trav->next = new Node(n2+1);
        Node *temp = &nodes[n2];
        while(temp->next != nullptr){
          temp = temp->next;
        }
        temp->next = new Node(n1+1);
      }
      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile
      //cout<<n1+1<<" "<<n2+1<<endl;
      //cout<<'a';
      //cout<<"sdjh";
      graphFile << n1+1 << " " << n2+1 << endl;
     // cout<<"b\n";
      countEdges++;

    }
    // Add appropriate code as necessary for your implementation
    // for(int i=0;i<nNodes;i++){
    //    Node *x = &nodes[i];
    //    cout<<x->value<<endl;
    //    while(x->next!=nullptr){
    //      cout<<x->next->value<<" ";
    //      x= x->next;
    //    }
    //    cout<<"\n";
    //  }
  }
      
  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;
    // Add appropriate code as necessary for your implementation
  }

  // Add appropriate method declarations as necessary for your implementation
  void recModDFS(int v, BST *b);
  void modifiedDFS();
  void printResults();
};

#endif

    // for(int i=0;i<nNodes;i++){
    //   Node *x = &nodes[i];
    //   cout<<x->value<<endl;
    //   while(x->next!=nullptr){
    //     cout<<x->next->value<<endl;
    //     x= x->next;
    //   }
    //   cout<<"\n";
    // }