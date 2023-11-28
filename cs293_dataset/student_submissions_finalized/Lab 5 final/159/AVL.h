#ifndef AVL_H
#define AVL_H

#ifndef TREE_H
#include "Tree.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

class AVLTree {
private:
  TreeNode *root;
  int totalComparisonCost;
  int totalParentChildUpdateCost;
  int perComparisonCost;
  int perParentChildUpdateCost;
  
  bool rotateLeftLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent);
  bool rotateLeftRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent);
  bool rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent);
  bool rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent);

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

  bool AVLLessThan(TreeNode* leftArg, TreeNode*rightArg) {
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
  //this is my operator for greter than and while using it also it will add to 
  //total comparisions cost
  bool AVLGreaterThan(TreeNode* leftArg, TreeNode*rightArg) {
    if ((leftArg != nullptr) && (rightArg != nullptr)) {
      bool result = (*leftArg > *rightArg);
      totalComparisonCost += perComparisonCost;
      return result;
    }
    else {
      cerr << "Unexpected exceptional condition!" << endl;
      exit(-1);
    }
  }

  void updateAVLParentChild(TreeNode *childNode, TreeNode *parentNode, bool isLeftChild)
  {
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
    }
    else {
      // both childNode and parentNode are nullptr
      // Nothing to do really
      // No updating of totalParentChildUpdateCost needed here
      ;
    }
    return;
  }
  //for every insert this function is called.it updates height for every node in tree
    void updateheight(TreeNode *r) {

if (r == nullptr) {
    return;
}
updateheight(r->left);
updateheight(r->right);

int leftHeight = 0;
int rightHeight = 0;

if (r->left != nullptr) {
    leftHeight = r->left->height;
}

if (r->right != nullptr) {
    rightHeight = r->right->height;
}

r->height = max(leftHeight, rightHeight) + 1;
return;
}
    
public:
  // Constructors
  AVLTree(int perCompCost, int perParntChldUpdCost) {
    root = nullptr;
    totalComparisonCost = 0;
    totalParentChildUpdateCost = 0;
    perComparisonCost = perCompCost;
    perParentChildUpdateCost = perParntChldUpdCost;
  }
  
  AVLTree(TreeNode *newRoot, int perCompCost, int perParntChldUpdCost) {
    root = newRoot;
    totalComparisonCost = 0;
    totalParentChildUpdateCost = 0;
    perComparisonCost = perCompCost;
    perParentChildUpdateCost = perParntChldUpdCost;
  }
    
  // Destructor
  //~AVLTree() {
    //recursiveDelete(root);
 // }

  bool insert(int jrnyCode, int price);
  int find(int jrnyCode);
  //getimbalancenode function returns imbalance node created on inserting certain node
  //and also it returns 1st imbalance node(1st ancestor node) as we move up from inserted node
  TreeNode* getimbalancenode(TreeNode* r);
  //checkbalance function for a node it returns true if it is balanced at that node 
  //else return false
  bool checkbalance(TreeNode* r);
  //makebalance function is called whenever we inserted an element it balances tree if imbalance 
  //found using rotate functions
  void makebalance(TreeNode* r);

  // Optional: Implement "remove" only for bonus marks
  
  bool remove(int jrnyCode);

  int getComparisonCost() { return totalComparisonCost; }
  int getParentChildUpdateCost() { return totalParentChildUpdateCost; }
  void print() { printBinaryTree(root, "", false); return;}
};

#endif
