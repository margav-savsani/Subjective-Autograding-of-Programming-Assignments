#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
//Singly Linked List Object of Typename T
template <typename T> class listOfObjects {
 public:
  T object; //object
  listOfObjects<T> *next; //pointer to next element
  // Constructor
  listOfObjects(T initValue) {object = initValue; next = nullptr;}
  // Destructor
  ~listOfObjects() {;}
};

//Defines the BST TreeNode
struct TreeNode{
    int value;		// Value
    TreeNode *left;	// Left Child of this Node (nullptr, if None)
    TreeNode *right;	// Right Child of this Node (nullptr, if None)
    TreeNode *parent;	// The Parent Node, nullptr in case of Root
    // Constructors
    TreeNode() : value(0),left(nullptr), right(nullptr) {}
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
    TreeNode(int val, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : value(val), left(leftChild), right(rightChild), parent(parent) {}
};

//BST
class BST {
  public:
    TreeNode *root;
    //Constructors
    BST(){root = nullptr; }
    BST(TreeNode *root){this->root = root; }
    // Inserts the node with the value in the BST
    void insert(int value) { 
      // Adding the first node
      if(root == nullptr){
        root = new TreeNode(value,nullptr,nullptr,nullptr);
        return;
      }
      TreeNode *curr = root;
      while(true){
        // Moving to the right, if value is greater
        if(value > curr->value){
            if(curr->right!=nullptr){
                curr = curr->right;
            }else{
                curr->right = new TreeNode(value,nullptr,nullptr,curr);
                break;              
            }
        }
        else{
            // moving to left if it is smaller
            if(curr->left!=nullptr){
                curr = curr->left;
            }else{
                curr->left = new TreeNode(value,nullptr,nullptr,curr);
                break;
            }
        }
      }
      return;
    }

    //Prints the BST like a Tree
    void printBST(const string& prefix, bool isLeft=false)
    {
        if( root != nullptr )
        {
            cout << prefix;
            cout << (isLeft ? "|--" : "|__" );
            // print the value of the node
            cout << '('<< root->value<<')' << endl;
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

//Graph Node
class Node {
 public:
  int value;  //Value of the node
  listOfObjects<Node*> *adjnodes; //Adjacency List of neighbours
  int visits; //No. of times the node gets visited during DFS
  int parent1;  //Value of the node through which it is traversed the first time during modified DFS
  int parent2;  //Value of the node through which it is traversed the second time during modified DFS
  int firstbacktrack; //Stores the iteration value when the first backtrack occured on it
  int secondarrival;  //Stores the iteration value when the node was traversed second time
  bool cycle; //Stores whether it occurs in a cycle or not
  //Constuctor 1
  Node(){
    value=0;
    adjnodes=nullptr;
    visits=0;
    cycle=false;
    firstbacktrack=-1;
    secondarrival=-1;
    parent1=-1;
    parent2=-1;
  }
  //Constructor 2
  Node(int val){
    value=val;
    adjnodes=nullptr;
    visits=0;
    cycle=false;
    firstbacktrack=-1;
    secondarrival=-1;
    parent1=-1;
    parent2=-1;
  }
  //Adds the neighbour n to the current node
  void addNeighbour(Node* n){
    if(adjnodes==nullptr){
      adjnodes= new listOfObjects<Node*>(n);
      return; 
    }
    listOfObjects<Node*> *curr;
    curr=adjnodes;
    while (curr->next!=nullptr)
    {
      curr=curr->next;
    }
    curr->next= new listOfObjects<Node*>(n);
    return;
  }
  //Checks whether n is a neighbour of current node or not
  //Returns true if it is and false otherwise
  bool isNeighbour(Node n){
    if (adjnodes==nullptr) return false;
    listOfObjects<Node*> *curr;
    curr=adjnodes;
    while(curr!=nullptr){
      if(curr->object->value==n.value){
        return true;
      }
      curr=curr->next;
    }
    return false;
  }
};

//Graph Data Structure
class Graph {
 public:
  int numNodes; //Number of Nodes
  int numEdges; //Number of Edges
  int numCycle; //Number of nodes present in atleast one cycle
  int numTwice; //Number of nodes visited twice during modified DFS
  int numOnce; //Number of nodes visited once during modified DFS
  int numComponents;  //Number of connected components in the graph
  fstream graphFile;  //Graph File
  Node *nodes;  //Array of Nodes of Graph
  listOfObjects<BST*> *BSTList; //List of BSTs generated during DFS
  //Constructor
  Graph(int nNodes, int nEdges, string gFileName) {
    //Setting Values
    numNodes = nNodes;
    numEdges = nEdges;
    numCycle=0;
    numTwice=0;
    numOnce=0;
    numComponents=0;
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
    //Assigning values to nodes
    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
    }
    srand(time(0));
    //Generating Distinct Edges
    int n1, n2;
    int countEdges = 0;
    while (countEdges < numEdges) {
      do {
	      n1 = rand() % numNodes;
	      n2 = rand() % numNodes;
      } while (n1 == n2);
      if(nodes[n1].isNeighbour(nodes[n2])){
        continue;
      }
      nodes[n1].addNeighbour(&nodes[n2]);
      nodes[n2].addNeighbour(&nodes[n1]);
      graphFile << n1+1 << " " << n2+1 << endl;
      countEdges++;
    }
  }     
  //Destructor
  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;
  }
  //Does Recursuve DFS on node n
  void DFS(Node* n, BST* bst);
  //Does DFS for every component and Creates all BSTs
  void modifiedDFS();
  //Prints the output information about graph
  void printResults();
};
#endif