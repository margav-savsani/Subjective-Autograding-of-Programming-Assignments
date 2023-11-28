#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

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

class TreeNode{
 public:
  int value;
  TreeNode *left,*right,*parent;

  TreeNode(int v){
    value = v;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
  }
};

class BST {
  // Add your own field and members here

  // Feel free to use the printBST function used earlier
  TreeNode *root;

 public:
  BST(){
    root = nullptr;
  }

  void insert(int x){
    if(root==nullptr){
      root = new TreeNode(x);
      return;
    }

    TreeNode *currNode = root,*parentOfCurrNode = nullptr;

    while(currNode!=nullptr){
      if(x >= currNode->value){
        parentOfCurrNode = currNode;
        currNode = currNode->right;
      }

      else{
        parentOfCurrNode = currNode;
        currNode = currNode->left;
      }
    }

    if(x < parentOfCurrNode->value){
      currNode = new TreeNode(x);
      currNode->parent = parentOfCurrNode;
      parentOfCurrNode->left = currNode;
    }

    else{
      currNode = new TreeNode(x);
      currNode->parent = parentOfCurrNode;
      parentOfCurrNode->right = currNode;
    }

    return;
  }

  void printBST(const string& prefix, bool isLeft=false){
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->value << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
  }

};

class Node {
 public:
  int value;
  listOfObjects<int> *adjlist;

  // insert other fields and methods as appropriate
  Node(){
    adjlist = nullptr;
  }

};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;
  int *visited;
  int *parent;
  int *dummy;
  int *incycle;
  int *dumpar;
  listOfObjects<BST*> *bsts;

  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {

    if(nEdges > nNodes*(nNodes-1)/2){
      cerr << "Too many edges . Aborting ..." << endl;
      exit(-1);
    }

    numNodes = nNodes;
    numEdges = nEdges;
    visited = new int[numNodes];
    parent = new int[numNodes];
    dummy = new int[numNodes];
    incycle = new int[numNodes];
    dumpar = new int[numNodes];
    BST *a = new BST();
    bsts = new listOfObjects<BST*>(a);

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
      visited[i] = 0;
      parent[i] = 0;
      dummy[i] = 0;
      incycle[i] = 0;
      dumpar[i] = -1;
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

      if(nodes[n1].adjlist==nullptr){
        nodes[n1].adjlist = new listOfObjects<int>(n2);

        if(nodes[n2].adjlist==nullptr){
          nodes[n2].adjlist = new listOfObjects<int>(n1);
        }

        else{
          listOfObjects<int> *p = nodes[n2].adjlist;

          while(p->next!=nullptr){
            p = p->next;
          }

          listOfObjects<int> *q = new listOfObjects<int>(n1);
          p->next = q;
          q->prev = p;
        }
      }

      else{
        listOfObjects<int> *p = nodes[n1].adjlist;

        int k = 0;

        while(p!=nullptr){
          if(p->object == n2){
            k = 1;
            break;
          }
          p = p->next;
        }

        if(k==1){continue;}

        p = nodes[n1].adjlist;
        while(p->next!=nullptr){
          p = p->next;
        }

        listOfObjects<int> *m = new listOfObjects<int>(n2);
        p->next = m;
        m->prev = p;

        listOfObjects<int> *q = nodes[n2].adjlist;
        if(q==nullptr){
          nodes[n2].adjlist = new listOfObjects<int>(n1);
        }

        else{
          while(q->next!=nullptr){
            q = q->next;
          }

          listOfObjects<int> *n = new listOfObjects<int>(n1);
          q->next = n;
          n->prev = q;
        }
      }

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

  void modifiedDFS(int s=0);
  void printResults();
  void DFS(int index);
};

#endif
