#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4


class Node{
  public:
  int value;
   Node *left;	// Left Child of this Node (NULL, if None)
    Node *right;	// Right Child of this Node (NULL, if None)
    Node *parent;	// The Parent Node, NULL in case of Root

    // Constructors
  
  Node() : value(-1), left(nullptr), right(nullptr) {}
  Node(int value) : value(value), left(nullptr), right(nullptr) {}
  Node(int value, Node *leftChild, Node *rightChild, Node *parent) : value(value), left(leftChild), right(rightChild), parent(parent) {}
};

class BST{
public:
Node* root;
BST(){root = NULL; }
BST(Node *root){this->root = root; }


bool insert(int value) { 
    // Adding the first node
    if(root == NULL){
        root = new Node(value,NULL,NULL,NULL);
        return true;
    }
    Node *curr = root;
    while(true){
         
        // Moving to the right, if price is greater
        if(value >= curr->value){
            if(curr->right!=NULL){
                curr = curr->right;
            }
            else{
                curr->right = new Node(value,NULL,NULL,curr);
                break;    
            }
        }else{
            // moving to left if its smaller
            if(curr->left!=NULL){
                curr = curr->left;
            }else{
                curr->left = new Node(value,NULL,NULL,curr);
                break;
                
            }
        }
    }
  //this->printBST("",false);
    return true;

}


void printBST(const string& prefix, bool isLeft=false)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << '('<< root->value<<')' << endl;
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
  public:
  int *visit; //count of visit
  int *parent;  //to store parent indices before calling dfs
  int* cycle;  // to calculate which nodes are in cylce
  int numNodes;
  int numEdges;
  fstream graphFile;
  int* arr;
  BST* T;
  int nconnected=0; 
  int nvis1=0;
  int nvis2=0;
  
  Node *nodes;

  // Add appropriate fields as necessary for your implementation
  
 
  Graph(int nNodes, int nEdges, string gFileName) {
    cycle=new int[nNodes];
    visit=new int[nNodes];
    parent=new int[nNodes];
    T=new BST[nNodes];
    arr=new int[nNodes];
    for(int i=0; i<nNodes;i++){
      arr[i]=0;
    }
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
      }
      while (n1 == n2);
      Node *x1=nodes[n1].right;
      Node *x2=nodes[n2].right;
      while(x1!=nullptr){
        if (x1->value==n2+1){
          break;
        }
        x1=x1->right;
      }
      if (x1!=nullptr){continue;}
      x1=&nodes[n1];
      x2=&nodes[n2];
      while(x1->right!=nullptr){
        x1=x1->right;
      }
      Node* N2=new Node(n2+1);
      x1->right=N2;
      N2->left=x1;
      while(x2->right!=nullptr){
        x2=x2->right;
      }
      Node* N1=new Node(n1+1);
      x2->right=N1;
      N1->left=x2;


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

  // Add appropriate method declarations as necessary for your implementation
  void DFSCycle(int u, int parentindex, int* visit, int* parent, int* cycle); 
  void DFS(int k,BST *T,Node* pi);
  void modifiedDFS();
  void printResults();
};

#endif
