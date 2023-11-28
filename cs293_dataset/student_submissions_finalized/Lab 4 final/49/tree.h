#ifndef BST_H
#define BST_H
#endif

// Header file for defining a Binary Search Tree
// Reuse the binary Search Tree implemented in lab 3 as much as possible

// struct TreeNode given below is almost the same as was given to you
// in lab 3. The only exception is the addition of shortestPathLength
// and longestPathLength fields along with a member function getImbalance.
// Read the comments in the structure definition to understand the meanings
// of these.
//

struct TreeNode{
  int JourneyCode;	// Journey code
  int price;		// Price
  TreeNode *left;	// Left Child of this Node (NULL, if None)
  TreeNode *right;	// Right Child of this Node (NULL, if None)
  TreeNode *parent;	// The Parent Node, NULL in case of Root
  int shortestPathLength; // Length of shortest path from this node to a leaf
                          // where a nullptr leaf contributes a path of length 0
  int longestPathLength; // Length of longest path from this node to a leaf
                         // where a nullptr leaf contributes a path of length 0
  
  TreeNode() : price(0), JourneyCode(0), left(nullptr), right(nullptr) {}
  
  TreeNode(int jrnyCode, int jrnyPrice) : price(jrnyPrice), JourneyCode(jrnyCode), left(nullptr), right(nullptr) {}
  
  TreeNode(int jrnyCode, int jrnyPrice, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : price(jrnyPrice), JourneyCode(jrnyCode), left(leftChild), right(rightChild), parent(parent) {}

  int setshort(TreeNode *v){             // function which returns shortestpath
    int s=0;                             // uses a recursive way to find shortestPath
    if((v->left!=NULL&&v->right==NULL)){
      s++;
      s+=setshort(v->left);
      
    } 
    if((v->left==NULL&&v->right!=NULL)){
      s++;
      s+=setshort(v->right);
    }       
    if((v->left!=NULL&&v->right!=NULL)){
      s++;
      int l = s+setshort(v->left);
      int r = s+setshort(v->right);
      if(l<r)s = l;
      else s = r;
    }
    return s;    
  }
  int setlong(TreeNode *v){               // function which returns longestpath
    int l=0;                              // uses a recursive way to find longestPath
    if((v->left!=NULL&&v->right==NULL)){
      l++;
      l+=setlong(v->left);
      
    } 
    if((v->left==NULL&&v->right!=NULL)){
      l++;
      l+=setlong(v->right);
    }       
    if((v->left!=NULL&&v->right!=NULL)){
      l++;
      int le = l+setlong(v->left);
      int r = l+setlong(v->right);
      if(le>r)l = le;
      else l = r;
    }
    return l;
  }
  
  int getImbalance()
  {
    // Returns how imbalanced the paths starting from this node to the
    // leaves are.  A case of perfect balance would result in the
    // longest and shortest path lengths being equal, so their difference
    // will be 0 (i.e. 0 imbalance).
    // Think about when would we have a case of large imbalance.
    TreeNode *v = new TreeNode(JourneyCode,price,left,right,parent);// copies characters of our TreeNode to find shortestPath and longestPath
    shortestPathLength = setshort(v);
    longestPathLength = setlong(v);
    return (longestPathLength - shortestPathLength);
  }
  
    
};

class BST{
  
  TreeNode *root;
  
  vector<string> result;
  
public:
  // ************************************************************
  // Methods for Part I
  
  // Constructors!
  BST() {root = nullptr; }
  BST(TreeNode *curr_root) {root = curr_root;}

  // Implement your own destructor
  ~BST() {};
 
  bool insert(int JourneyCode, int price);
    
  // Return true, if the ticket with given attributes is found, false otherwise
  bool find(int JourneyCode, int price);
    
  // Returns false, if JourneyCode isn't present
  // Deletes the corresponding entry and returns True otherwise
  TreeNode * successor(TreeNode x);
  bool remove(int JourneyCode, int price);
  
  // Returns the imbalance of the root node of the BST
  int getImbalance();

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
  void printBST(const string& prefix, bool isLeft);
  
  
  // The three functions below are for evaluation purposes, Do not tamper with them!
  void getBST(const string& prefix, bool isLeft);
  void clearResult();
  vector<string> getResult();
  
};
  
