#ifndef TREE_H
#define TREE_H

#ifndef STD_HEADERS
#define STD_HEADERS
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#endif

using namespace std;

class TreeNode {
public : 
    int JourneyCode;	// Train Number
    int price;		// Price
    TreeNode *left;	// Left Child of this Node (NULL, if None)
    TreeNode *right;	// Right Child of this Node (NULL, if None)
    TreeNode *parent;	// The Parent Node, NULL in case of Root
    
    int height; // HEIGHT OF THE NODE -- implement this. 

   // Constructors
  
    TreeNode() : price(0), JourneyCode(0), left(nullptr), right(nullptr) {
        // this constructor allocates memory only for the root  (upon usage of new)
        // allocation of memory for children is the job of insert function. 
        this->parent = nullptr;
    }
    TreeNode(int jrnyCode, int jrnyPrice) : price(jrnyPrice), JourneyCode(jrnyCode), left(nullptr), right(nullptr) {
        // this constructor again allocates memory only for root. (upon usage of new)
    }
    TreeNode(int jrnyCode, int jrnyPrice, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : price(jrnyPrice), JourneyCode(jrnyCode), left(leftChild), right(rightChild), parent(parent) {
        // this constructor also allocates memory only for root. (upon usage of new)
    }
  // Destructor: Define this as per your requirements
  ~TreeNode() {}

  // Print information about tree node on cout
  void printInfo()
  {
    cout << "[JC: " << JourneyCode << ", P: " << price << ", H: " << height << "]";
  }
  
  // Overloaded < operator
  // Usage: tree_node1 < tree_node2
  // Returns true if tree_node1.JourneyCode < tree_node2.JourneyCode
  // Returns false otherwise.
  //
  // Note that since JourneyCode is a private member of TreeNode,
  // we can't directly use tree_node1.JourneyCode < tree_node2.JourneyCode
  // from outside this class.
  
  bool operator < (TreeNode const &node)
  {
    if (JourneyCode < node.JourneyCode) return true;
    else return false;
  }

  // Makes current node the left child of parentNode if
  // isLeftChild is set to true; otherwise, it makes current node
  // the right child of parentNode.  In either case, the function
  // returns true.
  //
  // If parentNode is NULL, the function returns false.
  //
  // Note that if parentNode already had a left child, say x, and if
  // you are setting current node to be the new left child of
  // parentNode, then x will no longer be the left child of parentNode.
  // In fact, unless you save a pointer to x, you may no longer be able
  // to access x at all by walking down the tree from its root.
  // A similar observation applies if parentNode already had a right child,
  // and you are setting current node to be the new right child of
  // parentNode.
  
  bool updateParentChild(TreeNode *parentNode, bool isLeftChild)
  {
    if (parentNode != nullptr) {
      parent = parentNode;
      if (isLeftChild) {
	parentNode->left = this;
      }
      else {
	parentNode->right = this;
      }
      return true;
    }
    else {
      return false;
    }
  }
};

// The following function is effectively the same as printBST used in
// earlier labs.  The only difference is that this is not a member
// function of any class, and hence the root must be explicitly supplied
// as a parameter

void printBinaryTree(TreeNode *root, const string& prefix, bool isLeft)
{
  if( root != nullptr )   {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    root->printInfo();
    cout << endl;
    TreeNode *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
  else {
    cout << "NULL tree" << endl;
  }
}

#endif
