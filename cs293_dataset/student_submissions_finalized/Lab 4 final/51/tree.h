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
  int price;		
  int path_len;
  TreeNode *left;	// Left Child of this Node (NULL, if None)
  TreeNode *right;	// Right Child of this Node (NULL, if None)
  TreeNode *parent;	// The Parent Node, NULL in case of Root
  int shortestPathLength=0; // Length of shortest path from this node to a leaf
                          // where a nullptr leaf contributes a path of length 0
  int longestPathLength=0; // Length of longest path from this node to a leaf
                         // where a nullptr leaf contributes a path of length 0
  
  // Constructors: There are 3 variants of the constructor given below.
  // Please make sure you understand what each of these variants do.
  // Ask your TA or the instructor if you have a doubt.
  
  TreeNode() : price(0), JourneyCode(0), left(nullptr), right(nullptr) {}
  
  TreeNode(int jrnyCode, int jrnyPrice) : price(jrnyPrice), JourneyCode(jrnyCode), left(nullptr), right(nullptr) {}
  
  TreeNode(int jrnyCode, int jrnyPrice, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : price(jrnyPrice), JourneyCode(jrnyCode), left(leftChild), right(rightChild), parent(parent) {}
  
  int get_height(TreeNode *a){
    if(a == NULL){return 0;}
    else if( a->right == NULL && a->left== NULL){
      return 1;}
    int left_height = get_height(a->left);   
    int right_height = get_height(a->right);
    return max(left_height,right_height)+1;
    }
  
  int min_height(TreeNode *a){
    if(a == NULL){return 0;}
    else if( a->right == NULL && a->left== NULL){
      return 1;}
    int left_height = min_height(a->left);   
    int right_height = min_height(a->right);
    return min(left_height,right_height)+1;
    }
  int getImbalance()
  { shortestPathLength = min(min_height(left),min_height(right))+1;
    longestPathLength = max(get_height(left),get_height(right))+1;
    // Returns how imbalanced the paths starting from this node to the
    // leaves are.  A case of perfect balance would result in the
    // longest and shortest path lengths being equal, so their difference
    // will be 0 (i.e. 0 imbalance).
    // Think about when would we have a case of large imbalance.

    return (longestPathLength - shortestPathLength);
  }
    
};

// class BST given below is a slight modification of what it was in
// lab 3.  A few new fields have been introduced, and some member functions
// have been removed, since they are no longer needed for the current
// assignment.

// Note however that unlike in lab 3 where you had to build the BST using
// ordering of prices, this time we will build the BST using ordering of
// journey codes.

class BST{
  // Feel free to add more private/public variables and/or functions
  // But do not modify the pre-existing function signatures
  
  
  TreeNode *dummy2;// Price
  TreeNode *dummy3;
  // result variable is for testing purposes, Do not tamper with it!
  vector<string> result;
  
public:
  // ************************************************************
  // Methods for Part I
  TreeNode *root;
  // Constructors!
  BST() {root = nullptr;
          dummy3 =root;
          dummy2 =root; }
  BST(TreeNode *curr_root) {root = curr_root; dummy2 = root ; dummy3 =root;}

  // Implement your own destructor
  ~BST() {};
  
  // Returns false, if given JourneyCode is already present in the BST
  // Inserts the element and returns True otherwise
  bool insert(int JourneyCode, int price);
    
  // Return true, if the ticket with given attributes is found, false otherwise
  bool find(int JourneyCode, int price);
    
  // Returns false, if JourneyCode isn't present
  // Deletes the corresponding entry and returns True otherwise
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
  
