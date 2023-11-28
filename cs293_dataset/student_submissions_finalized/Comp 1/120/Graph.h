#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <vector>

struct TreeNode{
    int v;
    int sizeOfTree = 1;
    TreeNode *left;	// Left Child of this Node (NULL, if None)
    TreeNode *right;	// Right Child of this Node (NULL, if None)
    TreeNode *parent;	// The Parent Node, NULL in case of Root
    // Constructors
    TreeNode() : v(0), left(nullptr), right(nullptr) {}
    TreeNode(int jrnyCode) : v(jrnyCode), left(nullptr), right(nullptr) {}
    TreeNode(int jrnyCode, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : v(jrnyCode), left(leftChild), right(rightChild), parent(parent) {}
};

class BST {
  // Add your own field and members here
  // Feel free to use the printBST function used earlier
  TreeNode *root;
public:
  BST(){
    root=nullptr;
  }
  BST(TreeNode *root){this->root = root; }
  bool insert(int given) { 
    // Adding the first node
    if(root == NULL){
        root = new TreeNode(given,NULL,NULL,NULL);
        return true;
    }
    // Checking if similar node already exists
    TreeNode *curr = root;
    while(true){
        curr->sizeOfTree++; // incrementing Size of subtree which is rooted at this node

        // Moving to the right, if price is greater
        if(given > curr->v){
            if(curr->right!=NULL){
                curr = curr->right;
            }else{
                curr->right = new TreeNode(given,NULL,NULL,curr);
                break;
                
            }
        }else{
            // moving to left if its smaller
            if(curr->left!=NULL){
                curr = curr->left;
            }else{
                curr->left = new TreeNode(given,NULL,NULL,curr);
                break;
                
            }
        }
    }
  //  this->printBST("",false);
    return true;
  }
  void printBST(const string& prefix, bool isLeft=false)
  {
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->v << endl;
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
  int a=0;
  // insert other fields and methods as appropriate
};

class Graph {
  int numNodes;
  int numEdges;
  int connected =0 ;
  fstream graphFile;

  Node *nodes;
  int *numoftimes;
  bool *visited;
  int *adj;
  int *dum;
  vector<BST> out;
  bool *cycle;

  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    const int n = nNodes;
    adj = new int[nNodes*nNodes];
    numoftimes = new int[nNodes];
    dum = new int[nNodes*nNodes];
    cycle = new bool[nNodes];
    for(int i=0;i<nNodes;i++){
      numoftimes[i]=0;
      cycle[i]=false;
    }
    for(int i=0;i < nNodes*nNodes ; i++){
      adj[i]=0;dum[i]=0;
    }
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
      if(adj[(n1*nNodes) + n2]==1 ){
        continue;
      }
      else{
        adj[(n1*nNodes) + n2] =dum[(n1*nNodes) + n2]=1;
        adj[(n2*nNodes) + n1] =dum[(n2*nNodes) + n1]=1;
      }
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

  void modifiedDFS();
  BST mDFS(int i,int p,BST t);
  void printResults();
};

#endif
