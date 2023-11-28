#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
struct TreeNode{
    // Train Number
    int value1;		// Price
    TreeNode *left;	// Left Child of this Node (NULL, if None)
    TreeNode *right;	// Right Child of this Node (NULL, if None)
    TreeNode *parent;	// The Parent Node, NULL in case of Root

    // Constructors
  
    TreeNode() : value1(0),  left(nullptr), right(nullptr) {}
    TreeNode(int sum) : value1(sum), left(nullptr), right(nullptr) {}
    TreeNode(int sum, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : value1(sum), left(leftChild), right(rightChild), parent(parent) {}
};

class BST {
  public:
    TreeNode* root;
    BST(){
      root=nullptr;
    }
    BST(TreeNode *root1){
       root=root1; 
    }
   bool insert( int add) { 
    // Adding the first node
    if(root == NULL){
        root = new TreeNode(add,NULL,NULL,NULL);
        return true;
    }
    // Checking if similar node already exists
    TreeNode *curr = root;
    while(true){
   // incrementing Size of subtree which is rooted at this node

        // Moving to the right, if price is greater
        if(add > curr->value1){
            if(curr->right!=NULL){
                curr = curr->right;
            }else{
                curr->right = new TreeNode(add,NULL,NULL,curr);
                break;
                
            }
        }else{
            // moving to left if its smaller
            if(curr->left!=NULL){
                curr = curr->left;
            }else{
                curr->left = new TreeNode(add,NULL,NULL,curr);
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
        cout << root->value1 << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}


  // Add your own field and members here

  // Feel free to use the printBST function used earlier
};

class Node {
 public:
  int value;
  int visited=0;
  int parent=-1;
  int cycle=0;
  // insert other fields and methods as appropriate
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

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;
  int* store;//This is the adjacency matrix used to store the edges between the nodes.
  int* store1;
  int* edges;
  int connected=0;//This indicates the number of connected components
  // Add appropriate fields as necessary for your implementation
  
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
    store=new int[numNodes*numNodes];
    edges=new int[numNodes*numNodes];//This is used to store the number of times the edge between the given two noides has been traversed.
    store1=new int[numNodes*numNodes];
    nodes = new Node[numNodes];
    for(int i=0;i<numNodes*numNodes;i++){
      store[i]=0;
    }
    for(int p=0;p<numNodes*numNodes;p++){
      store1[p]=0;
    }
    for(int h=0;h<numNodes*numNodes;h++){
      edges[h]=0;
    }
    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
    }

    srand(0);
    int n1, n2;
    int countEdges = 0;
    
    while (countEdges < numEdges) {
      do {
	n1 = rand() % numNodes;
	n2 = rand() % numNodes;
      } while (n1 == n2);
    if(store[(numNodes)*n1+n2]==0){//This helps to identify the presence of the edge.
      store[(numNodes)*n1+n2]=1;
      store[(numNodes)*n2+n1]=1;
      store1[(numNodes)*n1+n2]=1;
      store1[(numNodes)*n2+n1]=1;
      
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

  void modifiedDFS();
  void printResults();
  void DFS(Node v,int num,int check,BST*a);
};

#endif
