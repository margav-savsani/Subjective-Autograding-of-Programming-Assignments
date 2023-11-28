#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

template <typename T> class list{
 public:
  T object;
  list<T> *next;
  
  // Constructor
  list(T initValue) {object = initValue; next = nullptr;}
  //This function deletes an object
  void del(T value){
    list<T> *q = next;
    if(q == nullptr){ return ;}
    if(q->object == value){
      next = next->next;
      return;
    }
    list<T> *s = q->next;
    while(s != nullptr){
      if(s->object == value){
        q->next = s->next;
        return;
      }
      q = s;
      s = s->next;
    }
}
  //  This function searches for the object
  bool search(T value){
    list<T> *r = this;
    while(r != nullptr){
      if(r->object == value){
        return true;
      }
      r = r->next;
    }
    return false;
  }

  
  // Destructor
  ~list() {;}
};

struct TreeNode{
    int index;	// Train Number		// Price
    TreeNode *left;	// Left Child of this Node (NULL, if None)
    TreeNode *right;	// Right Child of this Node (NULL, if None)
    TreeNode *parent;	// The Parent Node, NULL in case of Root

    // Constructors
  
    TreeNode() : index(0), left(nullptr), right(nullptr),parent(nullptr) {}
    TreeNode(int value) : index(value), left(nullptr), right(nullptr),parent(nullptr){}
};


class BST {
  TreeNode *root;
  public:
    
    BST(){
      root = new TreeNode();
    }
    BST(TreeNode *r){  root = r; }

    void insert(int value);

    TreeNode * getroot(){ return root; }

  // Add your own field and members here
  // Feel free to use the printBST function used earlier
};

class Node {
 public:
  int value;
  // insert other fields and methods as appropriate
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;
  list<int>**adjacent;
  Node *nodes;
  int * times;
  list<BST*> *results = new list<BST*>(new BST());

  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    adjacent = new list<int>*[numNodes];
    times =  new int[numNodes];
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
      times[i] = 0;
    }

    srand(time(0));
    int n1, n2;
    int countEdges = 0;
    for(int i = 0;i<numNodes;i++){
      adjacent[i] = new list<int>(-1);
    }
    while (countEdges < numEdges) {
      do {
	n1 = rand() % numNodes;
	n2 = rand() % numNodes;
      } while (n1 == n2);
      //To check whether the edge is already present
      if(!adjacent[n1]->search(n2)){
        //Adding to the first list
        list<int>* r1 = adjacent[n1];
        while(r1->next != nullptr){
          r1 = r1->next;
        }
        r1->next = new list<int>(n2);
        //Adding to the second list
        list<int>* r2 = adjacent[n2];
        while(r2->next != nullptr){
          r2 = r2->next;
        }
        r2->next = new list<int>(n1);
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
  void DFS(int n,BST *r);
  void modifiedDFS();
  void printResults();
};

#endif
