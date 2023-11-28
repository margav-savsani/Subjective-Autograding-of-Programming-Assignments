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
    if (currNode != NULL) {
      TreeNode *leftChild = currNode->left;
      TreeNode *rightChild = currNode->right;
    
      delete currNode;
      recursiveDelete(leftChild);
      recursiveDelete(rightChild);
    }
    return;
  }

  bool AVLLessThan(TreeNode* leftArg, TreeNode*rightArg) {
    bool result;
    if ((leftArg != NULL) && (rightArg != NULL)) {
      result = (leftArg->getJourneyCode() < rightArg->getJourneyCode());
      totalComparisonCost += perComparisonCost;
    }
    else {
      cerr << "Unexpected exceptional condition!" << endl;
      exit(-1);
    }
    return result;
  }




  void updateAVLParentChild(TreeNode *childNode, TreeNode *parentNode, bool isLeftChild)
  {
    if ((childNode != NULL) && (parentNode != NULL)) {
      childNode->updateParentChild(parentNode, isLeftChild);
      totalParentChildUpdateCost += perParentChildUpdateCost;
    }
    else if ((childNode == NULL) && (parentNode != NULL)) {
      if (isLeftChild) {
        parentNode->left = NULL;
      }
      else {
        parentNode->right = NULL;
      }
      // No updating of totalParentChildUpdateCost needed here
    }
    else if ((childNode != NULL) && (parentNode == NULL)) {
      childNode->parent = NULL;
      // No updating of totalParentChildUpdateCost needed here
    }
    else {
      // both childNode and parentNode are NULL
      // Nothing to do really
      // No updating of totalParentChildUpdateCost needed here
      ;
    }
    return;
  }
    



public:
  // Constructors
  AVLTree(int perCompCost, int perParntChldUpdCost) {
    root = NULL;
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
  ~AVLTree() {
    recursiveDelete(root);
  }

  bool insert(int jrnyCode, int price);
  int find(int jrnyCode);

  // Optional: Implement "remove" only for bonus marks
  
  bool remove(int jrnyCode);

  int getComparisonCost() { return totalComparisonCost; }
  int getParentChildUpdateCost() { return totalParentChildUpdateCost; }
  void print() { printBinaryTree(root, "", false); return;}
  void updateHeight(TreeNode* Parent);
  void printAVL(const string& , bool);
  TreeNode* getRoot();

  
};

#endif
