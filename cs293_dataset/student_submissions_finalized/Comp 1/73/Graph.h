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
struct TreeNode{
    int val;	// Train Number
    TreeNode *left;	// Left Child of this Node (NULL, if None)
    TreeNode *right;	// Right Child of this Node (NULL, if None)
    TreeNode *parent;	// The Parent Node, NULL in case of Root
    int sizeOfTree = 1;
    // Constructors
  
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
    TreeNode(int v, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : val(v), left(leftChild), right(rightChild), parent(parent) {}
};
class BST {
  // Add your own field and members here

  // Feel free to use the printBST function used earlier
  TreeNode *root;
  public:
  BST(){root = NULL; }
  BST(TreeNode *root){this->root = root; }
  bool insert(int val) 
  { 
    // Adding the first node
    if(root == NULL){
        root = new TreeNode(val,NULL,NULL,NULL);
        return true;
    }
    // Checking if similar node already exists
    TreeNode *curr = root;
    while(true){
        curr->sizeOfTree++; // incrementing Size of subtree which is rooted at this node

        // Moving to the right, if price is greater
        if(val > curr->val){
            if(curr->right!=NULL){
                curr = curr->right;
            }else{
                curr->right = new TreeNode(val,NULL,NULL,curr);
                break;
                
            }
        }else{
            // moving to left if its smaller
            if(curr->left!=NULL){
                curr = curr->left;
            }
            else{
                curr->left = new TreeNode(val,NULL,NULL,curr);
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
          cout << '('<< root->val<<')' << endl;
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
  int value;  //val
  listOfObjects<int> *adj;  //adj list
  int visited;  //num of times visited
  Node()
  {
    adj=nullptr;
    visited=0;
    value=-1;
  }
  // insert other fields and methods as appropriate
};

class Graph {
  int numNodes;
  int numEdges;
  int numconnected;
  int numcycle;
  int num1; //num of once
  int num2; //num of twice
  fstream graphFile;
  Node *nodes;
  listOfObjects<BST> *trees;
  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    numconnected=0;
    numcycle=0;
    num1=0;
    num2=0;
    graphFile.open(gFileName, ios::out);
    if (!graphFile.is_open()) {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }

    graphFile << numNodes << endl;
    graphFile << numEdges << endl;
    nodes = new Node[numNodes];
    trees=nullptr;
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
      bool is_present=false;
      if (nodes[n1].adj == nullptr)
       nodes[n1].adj=new listOfObjects<int>(n2);
      else
      {
        listOfObjects<int> *sample=nodes[n1].adj,*sample1;
        while(sample != nullptr)
        {
          if (sample->object==n2)
          {
            is_present=true;//if edge is already present
            break;
          }
          sample1=sample;
          sample=sample->next;
        }
        if (! is_present)
        {
          sample1->next=new listOfObjects<int> (n2);
          sample1->next->prev=sample1;
        }
      }
      if (nodes[n2].adj == nullptr)
        nodes[n2].adj=new listOfObjects<int>(n1);
      else
      {
        listOfObjects<int> *sample=nodes[n2].adj;
        while(sample->next != nullptr)
        {
          sample=sample->next;
        }
        if (! is_present)
        {
          sample->next=new listOfObjects<int> (n1);
          sample->next->prev=sample;
        }
      }
      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile
      if (! is_present)
      {
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
  void DFS(int v1,BST* t,int v,bool *back,listOfObjects<int> *stc);
};

#endif
//by saran 210050036