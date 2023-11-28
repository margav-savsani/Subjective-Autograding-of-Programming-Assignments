#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

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
  Node* parent;
  Node* left;
  Node* right;
  Node() : value(0){}
  Node(int value){
    this->value = value;
    parent = NULL; 
    left = NULL;
    right = NULL;
  }
  // insert other fields and methods as appropriate
};

class BST {
  // Add your own field and members here
  Node* root;
  // Feel free to use the printBST function used earlier
public:
  BST(){
    root = NULL;
  }
  BST(Node* root){
    this->root = root;
  }
  bool insert(int value){
    Node* node = new Node(value);
    Node *y, *x;
    y=NULL;
    x=root;
    bool k=false;
    while(x!=NULL){
        y=x;
        if(value< x->value){
            x=x->left;
        }
        else x=x->right;
    }

    node->parent=y;
    if(y==NULL){
        root=node;
    }
    else if(node->value<y->value){
        y->left=node;
    }
    else y->right=node;
    return true;
  }

  void printBST(const string& prefix, bool isLeft=false){
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
};

class Graph {
  int numNodes;
  int numEdges;
  int numConnComp;
  fstream graphFile;

  Node *nodes;

  listOfObjects<int>* *adjList;
  int* visited;

  listOfObjects<BST>* treeList;
  int* InaCycle;
  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numConnComp=0;
    numNodes = nNodes;
    numEdges = nEdges;
    adjList = new listOfObjects<int>*[nNodes];
    visited = new int[nNodes];
    InaCycle = new int[nNodes];
    for(int i=0; i<nNodes; i++){
      adjList[i] = new listOfObjects<int>(-1);
      visited[i] = 0;
      InaCycle[i]=0;
    }
    treeList = new listOfObjects<BST>(BST());
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
      listOfObjects<int>* node1list = adjList[n1];
      listOfObjects<int>* node2list = adjList[n2];
      bool exists=false;
      while(node1list!=NULL){
        if(node1list->object==n2){
          exists=true;
          break;
        }
        node1list = node1list->next;
      }
      if(!exists){
        while(node2list!=NULL){
          if(node2list->object==n1){
            exists=true;
            break;
          }
          node2list = node2list->next;
        }
      }
      if(!exists){
        graphFile << n1+1 << " " << n2+1 << endl;
        countEdges++;
        listOfObjects<int>* node1list = adjList[n1];
        listOfObjects<int>* node2list = adjList[n2];
        while(node1list->next!=NULL){
          node1list = node1list->next;
        }
        while(node2list->next!=NULL){
          node2list = node2list->next;
        }
        node1list->next = new listOfObjects<int>(n2);
        node2list->next = new listOfObjects<int>(n1);
      }
      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile
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

  void doDFS(int currNode, listOfObjects<BST> *tList, int parent, listOfObjects<int>* listSofar, listOfObjects<int>* listSofarend);
  void modifiedDFS();
  void printResults();
};

#endif
