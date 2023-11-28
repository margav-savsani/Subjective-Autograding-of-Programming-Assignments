#include <vector>
#include <string>
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
  unsigned int JourneyCode;	// Journey code
  unsigned int price;		// Price
  TreeNode *left;	// Left Child of this Node (NULL, if None)
  TreeNode *right;	// Right Child of this Node (NULL, if None)
  TreeNode *parent;	// The Parent Node, NULL in case of Root
  int shortestPathLength; // Length of shortest path from this node to a leaf
                          // where a nullptr leaf contributes a path of length 0
  int longestPathLength; // Length of longest path from this node to a leaf
                         // where a nullptr leaf contributes a path of length 0
  
  // Constructors: There are 3 variants of the constructor given below.
  // Please make sure you understand what each of these variants do.
  // Ask your TA or the instructor if you have a doubt.
  
  TreeNode() : price(0), JourneyCode(0), left(nullptr), right(nullptr) , shortestPathLength(0) , longestPathLength(0) {}
  
  TreeNode(unsigned int jrnyCode, unsigned int jrnyPrice) : price(jrnyPrice), JourneyCode(jrnyCode), left(nullptr), right(nullptr) , shortestPathLength(0) , longestPathLength(0) {}
  
  TreeNode(unsigned int jrnyCode, unsigned int jrnyPrice, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : price(jrnyPrice), JourneyCode(jrnyCode), left(leftChild), right(rightChild), parent(parent) , shortestPathLength(0) , longestPathLength(0) {}

  int getImbalance()
  {
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
  
  TreeNode *root;
  
  // result variable is for testing purposes, Do not tamper with it!
  vector<string> result;
  
public:
  // ************************************************************
  // Methods for Part I
  
  // Constructors!
  BST();
  BST(TreeNode *root);

  // Implement your own destructor
  ~BST() {};
  
  // Returns false, if given JourneyCode is already present in the BST
  // Inserts the element and returns True otherwise
  bool insert(unsigned int JourneyCode, unsigned int price);
    
  // Return true, if the ticket with given attributes is found, false otherwise
  bool find(unsigned int JourneyCode, unsigned int price);
    
  // Returns false, if JourneyCode isn't present
  // Deletes the corresponding entry and returns True otherwise
  bool remove(unsigned int JourneyCode, unsigned int price);

  // Returns the imbalance of the root node of the BST
  int getImbalance();

  // To search for a node and return that Node
  struct TreeNode *searchNode(unsigned int JourneyCode, unsigned int price);

  // Returns the successor of the given Node
  struct TreeNode *successor(TreeNode *v);

  // Returns the node with minimum price
  struct TreeNode *minNode(TreeNode *v);

  // Returns the minimum price
  unsigned int getMinimum();

  // Retuns the root of BST
  TreeNode *getRoot();

  // Updates the shortest and longest path lengths of all the ancestors
  // of the new Node while Inserting it
  void updatePathLength(TreeNode *father);

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

