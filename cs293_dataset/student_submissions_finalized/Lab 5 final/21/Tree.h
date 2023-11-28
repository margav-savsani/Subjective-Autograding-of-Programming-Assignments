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
private:
  int JourneyCode; // Journey code: This is the key for BST and AVL tree
  int price;       // Price
public:
  TreeNode* left;  // Pointer to left child  (NULL, if no left child)
  TreeNode* right; // Pointer to right child (NULL, if no right child)
  TreeNode* parent;// Parent of this node (NULL, if no parent)
  int height;      // Height of the tree rooted at this node.  A leaf
                   // has height 0. 
  
  // Constructor:
  TreeNode(int jrnyCode, int jrnyPrice)
  {
    JourneyCode = jrnyCode;
    price = jrnyPrice;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    height = 0;
  }


  // Destructor: Define this as per your requirements
  ~TreeNode() {}

  // Print information about tree node on cout
  void printInfo()
  {
    cout << "[JC: " << JourneyCode <<", P: "<< price <<", H: " << height << "]";
  }
  
  // Overloaded < operator for comparing two TreeNode(s) based on JourneyCode
  bool operator < (TreeNode const &node)
  {
    if (JourneyCode < node.JourneyCode) return true;
    else return false;
  }

  // makes this node the left/right child of the parent node depending on the value of isLeftChild
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
      parent = parentNode;
      return false;
    }
  }

  //returns the balance of this node (difference in height of left and right child )
  int balance(){
  if (left != NULL && right != NULL) return abs(left->height - right->height);
  else if (left == NULL && right != NULL) return right->height + 1;
  else if (left != NULL && right == NULL) return left->height + 1;
  else return 0; 
  }

  //returns the price. We had to define this function since price is a private member and it needs to be returned in 
  //the  find function
  int getPrice(){
    return price;
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
  }
}



#endif
