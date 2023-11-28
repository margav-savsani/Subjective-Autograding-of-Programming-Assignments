#ifndef BST_H
#define BST_H
#include <cmath>

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
  
  // Constructors: There are 3 variants of the constructor given below.
  // Please make sure you understand what each of these variants do.
  // Ask your TA or the instructor if you have a doubt.
  
  TreeNode() : price(0), JourneyCode(0), left(nullptr), right(nullptr), parent(nullptr) {shortestPathLength = 0; longestPathLength = 0;}
  TreeNode(int jrnyCode, int jrnyPrice) : price(jrnyPrice), JourneyCode(jrnyCode), left(nullptr), right(nullptr), parent(nullptr) {shortestPathLength = 0; longestPathLength = 0;}
  TreeNode(int jrnyCode, int jrnyPrice, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : price(jrnyPrice), JourneyCode(jrnyCode), left(leftChild), right(rightChild), parent(parent) {shortestPathLength = 0; longestPathLength = 0;}

        void updateParents(){       //update all the parents 
                if(parent != nullptr){     
                        if(parent->right == nullptr || parent->left == nullptr){  //if either of left or right is NULL, just increment teh path lengths by 1 from the child  
                                parent->shortestPathLength = shortestPathLength+1;
                                parent->longestPathLength = longestPathLength+1;
                                parent->updateParents();
                        }
                        else if(parent->right != nullptr && parent->left != nullptr){   //if both children exist
                                int temp1 = parent->shortestPathLength;
                                int temp2 = parent->longestPathLength;
                                if(parent->right == this){  //if it is the right element, find the min path length by comparing it with the left child
                                        parent->shortestPathLength = min(shortestPathLength+1, (parent->left)->shortestPathLength+1);
                                        parent->longestPathLength = max(longestPathLength+1, (parent->left)->longestPathLength+1);
                                }
                                else{   //if it is the left element, find the min path length by comparing it with the right child
                                        parent->shortestPathLength = min(shortestPathLength+1, (parent->right)->shortestPathLength+1);
                                        parent->longestPathLength = max(longestPathLength+1, (parent->right)->longestPathLength+1);
                                }
                                if(parent->shortestPathLength != temp1 || parent->longestPathLength != temp2){
                                        parent->updateParents();
                                }
                        }
                }
        }

  void leftChild(TreeNode* child){
      left = child;
      if(child != NULL){
              child->parent = this;
      }
  }

  void rightChild(TreeNode* child){
      right = child;
      if(child != NULL){
              child->parent = this;
      }
  }

  void exchange(TreeNode* node){
      if(parent != NULL){
              if(parent->right == this){
                      if(node != NULL){
                              parent->rightChild(node); 
                      }
                      else{
                              parent->right = NULL;
                      }
                      
                      //cout << "Leaf node - right child of parent deleted" << endl; 
              }
              else if(parent->left == this){
                      
                      if(node != NULL){
                              parent->leftChild(node);    
                                                          
                      }
                      else{
                              parent->left = NULL;
                      }
                      
                      //cout << "Leaf node - left child of parent deleted" << endl;
              }
      }
      else{
              node->parent = NULL;
      }
      
  }

  int getImbalance()
  {
    // Returns how imbalanced the paths starting from this node to the
    // leaves are.  A case of perfect balance would result in the
    // longest and shortest path lengths being equal, so their difference
    // will be 0 (i.e. 0 imbalance).
    // Think about when would we have a case of large imbalance.

    //return (longestPathLength - shortestPathLength);
    if(right == NULL && left == NULL){
        return 0;
    }
    else if(right == NULL || left == NULL){   //if one of the child is null, return only the longest length, reasonable as we are calculating imbalance
        return longestPathLength;
    }
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
  int N;
  
public:
  // ************************************************************
  // Methods for Part I
  
  // Constructors!
  BST();
  BST(TreeNode *curr_root);

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

#endif
  
