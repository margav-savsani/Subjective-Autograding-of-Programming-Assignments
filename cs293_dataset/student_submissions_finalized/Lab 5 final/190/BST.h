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





// const int PRE_ORDER = 0;
// const int IN_ORDER = 1;
// const int POST_ORDER = 2;











class BST {
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

  bool BSTLessThan(TreeNode* leftArg, TreeNode*rightArg) {
    bool result;
    if ((leftArg != nullptr) && (rightArg != nullptr)) {
      result = (leftArg->getJourneyCode() < rightArg->getJourneyCode());
      totalComparisonCost += perComparisonCost;
    }
    else {
      cerr << "Unexpected exceptional condition!" << endl;
      exit(-1);
    }
    return result;
  }
  
  void updateBSTParentChild(TreeNode *childNode, TreeNode *parentNode, bool isLeftChild)
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
    
public:
  // Constructors
  BST(int perCompCost, int perParntChldUpdCost) {
    root = NULL;
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

  bool insert(int JourneyCode, int price);
  int find(int JourneyCode);

  // Optional: Implement "remove" only for bonus marks
  
  bool remove(int jrnyCode);

  int getComparisonCost() { return totalComparisonCost; }
  int getParentChildUpdateCost() { return totalParentChildUpdateCost; }
  void print() { printBinaryTree(root, "", false); return;}


  // Extra functions
  // // void traverse(int typeOfTraversal);
  // // void preOrderTraverse(TreeNode *x);
  // // void inOrderTraverse(TreeNode *x);
  // // void postOrderTraverse(TreeNode *x);

  TreeNode* TreeSuccessor(TreeNode *x);
  TreeNode* TreeMinimum(TreeNode *x);
  TreeNode* getRoot();
  void printBST(const string& , bool);
  void updateHeight(TreeNode* Parent);
};

#endif
