#ifndef GRAPH_BST_H
#define GRAPH_BST_H
#include<vector>
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
// class listOfObjects {
//  public:
//   int object;
//   listOfObjects *next;
//   listOfObjects *prev;
  
//   // Constructor
//   listOfObjects(int initValue) {object = initValue; next = prev = nullptr;}
  
//   // Destructor
//   ~listOfObjects() {;}
// };
class TreeNode
{
public:
 int data;
 TreeNode *left;
 TreeNode *right;
 TreeNode *parent;
 TreeNode(int data){
  this->data=data;
  left=NULL;
  right=NULL;
  parent=NULL;
 }
  ~TreeNode();
};


class BST {

	// Feel free to add more private/public variables and/or functions
	// But do not modify the pre-existing function signatures
	// You'd be evaluated only on your ability to implement those
	// You don't need anything more than the root of your Tree!
	// The BST is ordered by prices and not train Numbers.

	TreeNode *root;

	// result variable is for testing purposes, Do not tamper with it!
	
public:
        // ************************************************************
        // Methods for Part I
  
	// Constructors!
	BST(){
    root=NULL;
  }
	BST(TreeNode *root){
    this->root=root;
  }
	
        // This function prints the BST using ASCII characters using the
        // format:
        //
        //   root
        //       |-- left subtree
        //       |__ right subtree
        //
        // where the left and right subtrees are printed recursively in
        // the same format.
        //
	// We have done this for you! Please see BST.cpp for details
	// You may use this for debugging purposes.
        //
	void printBST(const string& prefix, bool isLeft){
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << '('<< root->data<<','<<')' << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
  }
	
	
	// The three functions below are for evaluation purposes, Do not tamper with them!
	
	
	// Returns false, if given JourneyCode is already present in the BST
	// Inserts the element and returns True otherwise
	bool insert(int data){
    TreeNode *a=new TreeNode(data);
    TreeNode* p=find(data);
    if(p!=NULL){
      if(p->right==NULL){
        p->right=a;
        a->parent=p;
        return true;
      }
      else{
        a->parent=p;
        a->right=p->right;
        p->right->parent=a;
        p->right=a;
        return true;
      }
    }
    if(root == NULL){
        root = new TreeNode(data);
        return true;
    }
    
    TreeNode *curr = root;
    while(true){
        // incrementing Size of subtree which is rooted at this node

        // Moving to the right, if price is greater
        if(data > curr->data){
            if(curr->right!=NULL){
                curr = curr->right;
            }else{
              
                curr->right = a;
                a->parent=curr;
                break;
                
            }
        }else{
            // moving to left if its smaller
            if(curr->left!=NULL){
                curr = curr->left;
            }else{
                curr->left = a;
                a->parent=curr;
                break;
                
            }
        }
    }
  //  this->printBST("",false);
    return true;
  }


	// Return true, if the ticket with given attributes is found, false otherwise
	TreeNode* find(int data){
    if(root==NULL)return NULL;
    TreeNode* curr = root;
    while(true){
      
        if(curr->data==data){
            if(curr->data==data){
                return curr;
            }else return NULL;
        } else if(curr->data > data){
      
            if(curr->left==NULL){
                return NULL;
            }else{
                curr = curr->left;
            }
        }else{
            if(curr->right==NULL){
                return NULL;
            }else{
                curr = curr->right;
            }
        }
    }
    return NULL;
  }
	
	// Returns false, if JourneyCode isn't present
	// Deletes the corresponding entry and returns True otherwise
	
};

class Node {
 public:
//   listOfObjects *adjancy;
vector<int> adjancy;
vector<int> parent;
  int visited;
  int value;
Node(){
  this->visited=0;
}

  // insert other fields and methods as appropriate
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;

  Node *nodes;
  int visited_once;
  int visited_twice;
  int conn_component;
  int in_cycle;
  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    visited_once=0;
    visited_twice=0;
    conn_component=0;
    in_cycle=0;
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
      
      bool already=false;
      for(int i=0;i<nodes[n1].adjancy.size();i++){
        if(nodes[n1].adjancy[i]==n2+1){
          already=true;
        }
      }
      if(!already){
        nodes[n1].adjancy.push_back(n2+1);
     
        nodes[n2].adjancy.push_back(n1+1);
        graphFile << n1+1 << " " << n2+1 << endl;
        countEdges++;}
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

  void modifiedDFS();  
  void new_dfs(int a,BST *b); 
  void printResults();
};

#endif
