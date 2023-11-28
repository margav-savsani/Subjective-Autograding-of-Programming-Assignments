#ifndef GRAPH_BST_H
#define GRAPH_BST_H
using namespace std;

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
struct TreeNode{
    int value;	// Value   
    TreeNode *left;	// Left Child of this Node (NULL, if None)
    TreeNode *right;	// Right Child of this Node (NULL, if None)
    TreeNode *parent;	// The Parent Node, NULL in case of Root
    TreeNode() : value(-1), left(nullptr), right(nullptr) {}
    TreeNode(int Value) :value(Value), left(nullptr), right(nullptr),parent(nullptr) {}   
};

class BST {
  TreeNode *root;
  public:
    BST(){
      root = nullptr;     
    }
    bool insert(int Value) { 
      TreeNode *x = root;    
      TreeNode *y = x;
      if(root==NULL){
        root = new TreeNode(Value);
        return true;
      }
      int money=root->value;
      while(x!=nullptr){ 
        if(money<Value){
            y=x;
            if(y->right==nullptr){
                x = new TreeNode(Value);
                y->right = x;
                break;
            }           
            x=y->right;
            money=x->value;             
        }
        else{
            y=x;
            if(y->left==nullptr){
                x = new TreeNode(Value);
                y->left = x;
                break;
            } 
            x=y->left;
            money=x->value;
        }
      }  
      return true;
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

class listOfObjects {
 public:
  int object;
  listOfObjects *next;
  listOfObjects *prev;
  listOfObjects(int initValue) {object = initValue; next = prev = nullptr;}
  ~listOfObjects() {;}
};

class Node {
 public:
  int value;
  listOfObjects*adjacent;  
  // insert other fields and methods as appropriate
};
bool present(int val,listOfObjects*curr){
  if(curr == nullptr)return false;
  if(curr->object == val)return true;
  return present(val,curr->next);
}
class Graph {
  int numNodes;
  int numEdges;
  int connected_components;
  fstream graphFile;
  Node *nodes;
  BST *Tree;
  int *visited; 
  int *cyc;
  int *adj;
  int *parent;
  // Add appropriate fields as necessary for your implementation  
 public:  
  Graph(int nNodes, int nEdges, string gFileName) {
    connected_components = 0;
    Tree = new BST();
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
    visited = new int[numNodes];
    cyc = new int[numNodes];
    adj = new int[numNodes*numNodes];
    parent = new int[numNodes*numNodes];
    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }
    for (int i = 0; i < numNodes; i++) {
      for (int j = 0; j < numNodes; j++) {
        adj[i*numNodes+j] = 0;
        parent[i*numNodes+j] = 0;
    }

    }

    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
      visited[i] = 0;
      cyc[i] = 0;
    }

    srand(time(0));
    int n1, n2;
    int countEdges = 0;
    while (countEdges < numEdges) {
      do {
	      n1 = rand() % numNodes;
	      n2 = rand() % numNodes;
      } while ((n1 == n2)||present(n2,nodes[n1].adjacent));

      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile
      bool present = false;
      if(nodes[n1].adjacent == nullptr){
        nodes[n1].adjacent = new listOfObjects(n2);
        graphFile << n1+1 << " " << n2+1 << endl;
        countEdges++;
      }
      else{
        listOfObjects *curr = nodes[n1].adjacent;
        while(curr->next!=nullptr){
          curr = curr->next;
        }
        curr->next = new listOfObjects(n2);
        graphFile << n1+1 << " " << n2+1 << endl;
        countEdges++;
      }  
      if(nodes[n2].adjacent==NULL){
          nodes[n2].adjacent = new listOfObjects(n1);       
        }
      else{
        listOfObjects *curr = nodes[n2].adjacent;
        while(curr->next!=nullptr){
          curr = curr->next;
        }
        curr->next = new listOfObjects(n1);
        (curr->next)->prev = curr;            
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
  void DFS(int val);
  void cycles(int val,int initial,bool &present);
  void modifiedDFS();
  void printResults();
};

#endif