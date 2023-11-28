#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

int *visited; // visited array
int cnt = 0; // num of connected components

struct TreeNode{
    int price;		// Price
    TreeNode *left;	// Left Child of this Node (NULL, if None)
    TreeNode *right;	// Right Child of this Node (NULL, if None)
    TreeNode *parent;	// The Parent Node, NULL in case of Root

    // Constructors
  
    TreeNode() : price(0), left(nullptr), right(nullptr) {}
    TreeNode(int jrnyPrice) : price(jrnyPrice), left(nullptr), right(nullptr) {}
    TreeNode(int jrnyPrice, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : price(jrnyPrice), left(leftChild), right(rightChild), parent(parent) {}
};


class BST{
	TreeNode *root;
public:
	BST();
	BST(TreeNode *root);
	void printBST(const string& prefix, bool isLeft);
	bool insert(int price);
};

template<typename T> class list {
 public:
  T object;
  list<T> *next;
  list<T> *prev;
  
  // Constructor
  list(T initValue) {object = initValue; next = prev = nullptr;}
  
  // Destructor
  ~list() {;}
};

list<BST> *all = nullptr;

class Node {
 public:
  int value;
  bool in_cycle = false;
  list<Node> *adj_head = nullptr,*adj_tail = nullptr;
  Node() {}
  Node(int i) {
    value = i;
  }
  void insert(Node n){
      if(adj_head==nullptr){
        adj_head = new list<Node> (n);
        return;
      }
      list<Node> *tmp = adj_head;
      while(adj_head->next!=nullptr) {
        adj_head = adj_head->next;
      }
      adj_head->next = new list<Node> (n);
      adj_head->next->prev = adj_head;
      adj_head = tmp;
      //cout << "node = "<<value<<" adj item = "<<n.value<<endl;
  }
  // insert other fields and methods as appropriate
};

list<Node> *stack = nullptr;

bool find(list<Node> *adj, Node n){
  while (adj!=nullptr){
    if((adj->object).value == n.value) {
      return 1;
    }
    adj = adj->next;
  }
  return 0;
}

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;
  
 public:
  BST my_BST;
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
    visited = new int [numNodes];
    for(int i=0;i<numNodes;i++){
      visited[i]=0;
    }
    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1; // assigning the values to the nodes
    }

    srand(time(0));
    int n1, n2;
    int countEdges = 0;
    
    while (countEdges < numEdges) { // creating a edge b/w n1 and n2
      do {
	n1 = rand() % numNodes;
	n2 = rand() % numNodes;
      } while (n1 == n2);


      if(find(nodes[n1].adj_head,nodes[n2]) || find(nodes[n2].adj_head,nodes[n1])) {
        continue;
      }

      nodes[n1].insert(Node(nodes[n2].value));
      // cout <<"============"<<endl;
      nodes[n2].insert(Node(nodes[n1].value));
     
      // completed adding a new edge b/w the given two vertices
      graphFile << "new edge b/w " <<  n1+1 << " " << n2+1 << endl;
      countEdges++;
    }

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
  bool st_find(int);
  void my_DFS(Node,Node);
  void printResults();
};

#endif
