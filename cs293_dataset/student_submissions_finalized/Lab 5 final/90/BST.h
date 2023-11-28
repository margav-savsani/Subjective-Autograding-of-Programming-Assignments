#ifndef BST_H
#define BST_H

#ifndef TREE_H
#include "Tree.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

using namespace std;

class BST{
private:
  TreeNode *root;
  int totalComparisonCost;
  int totalParentChildUpdateCost;
  int perComparisonCost;
  int perParentChildUpdateCost;
  
  // Recursively deletes all nodes in the binary tree rooted at currNode
  void recursiveDelete(TreeNode *currNode) {
    if (currNode != nullptr) {
      TreeNode *leftChild = currNode->left;
      TreeNode *rightChild = currNode->right;
    
      delete currNode;
      recursiveDelete(leftChild);
      recursiveDelete(rightChild);
    }
    return;
  }

  // Checks if the pointers to the nodes leftArg and rightArg
  // are such that journey code of the node corresponding
  // to pointer leftArg is less than that corresponding to 
  // pointer rightArg
  bool BSTLessThan(TreeNode* leftArg, TreeNode *rightArg) {
    if ((leftArg != nullptr) && (rightArg != nullptr)) {
      bool result = (*leftArg < *rightArg);
      totalComparisonCost += perComparisonCost;
      return result;
    }
    else {
      cerr << "Unexpected exceptional condition!" << endl;
      exit(-1);
    }
  }
  
  // This updates the parent pointer of the childNode and 
  // either left or right child(decided by the boolean isLeftChild)
  // of the parentNode
  void updateBSTParentChild(TreeNode *childNode, TreeNode *parentNode, bool isLeftChild){
    if ((childNode != nullptr) && (parentNode != nullptr)) {
      childNode->updateParentChild(parentNode, isLeftChild);
      totalParentChildUpdateCost += perParentChildUpdateCost;
    }
    else if ((childNode == nullptr) && (parentNode != nullptr)) {
      if (isLeftChild) {
	      parentNode->left = nullptr;
      }
      else {
	      parentNode->right = nullptr;
      }
      // No updating of totalParentChildUpdateCost needed here
    }
    else if ((childNode != nullptr) && (parentNode == nullptr)) {
      childNode->parent = nullptr;
      // No updating of totalParentChildUpdateCost needed here

      //This serves to be a very important inclusion.
      //The only node which has no parent Node is the root
      //In case we encounter an update, where the parentNode is nullptr
      //In that case the childNode must represent the root.
      //Hence the root is updated to childNode
      root = childNode; 
    }
    else {
      // both childNode and parentNode are nullptr
      // Nothing to do really
      // No updating of totalParentChildUpdateCost needed here
      ;
    }
    return;
  }
    
public:
  // Constructors
  BST(int perCompCost, int perParntChldUpdCost) {
    root = nullptr;
    totalComparisonCost = 0;
    totalParentChildUpdateCost = 0;
    perComparisonCost = perCompCost;
    perParentChildUpdateCost = perParntChldUpdCost;
  }
  
  BST(TreeNode *newRoot, int perCompCost, int perParntChldUpdCost) {
    root = newRoot;
    totalComparisonCost = 0;
    totalParentChildUpdateCost = 0;
    perComparisonCost = perCompCost;
    perParentChildUpdateCost = perParntChldUpdCost;
  }
    
  // Destructor
  ~BST() {
    recursiveDelete(root);
  }

  //Returns true on a successful insertion into the BST
  bool insert(int jrnyCode, int price);

  //Returns the price of the node with journey code given
  //as parameter. If no such node found, then this returns
  //-1
  int find(int jrnyCode);

  //Updates the heights of all nodes, starting from
  //the node given as a parameter and climbing all the way
  //till the root
  void updateHeights(TreeNode* parentOfCurrNode);

  // Optional: Implement "remove" only for bonus marks
  
  bool remove(int jrnyCode);

  int getComparisonCost() { return totalComparisonCost; }
  int getParentChildUpdateCost() { return totalParentChildUpdateCost; }
  void print() { printBinaryTree(root, "", false); return;}
};

#endif
