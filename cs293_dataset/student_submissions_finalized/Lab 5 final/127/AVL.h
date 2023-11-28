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

  void myRotateLeftLeft(TreeNode* currNode, TreeNode* parent, TreeNode* grandParent) {

    int temp_height=parent->height_right;
    parent->height_right=std::max(grandParent->height_right, parent->height_right)+1;
    grandParent->height_left=temp_height;

    TreeNode* great_grandParent=grandParent->parent;
    TreeNode* temp_node=parent->right;
    parent->right=grandParent;
    grandParent->left=temp_node;
    if(temp_node!=nullptr) temp_node->parent=grandParent;
    grandParent->parent=parent;

    if(great_grandParent==nullptr) {
      root=parent;
      parent->parent=nullptr;
    }
    else if(great_grandParent->right==grandParent) {
      great_grandParent->right=parent;
      parent->parent=great_grandParent;
    }
    else {
      great_grandParent->left=parent;
      parent->parent=great_grandParent;
    }
    totalParentChildUpdateCost += 3*perParentChildUpdateCost;
  }

    void myRotateRightRight(TreeNode* currNode, TreeNode* parent, TreeNode* grandParent) {

    int temp_height=parent->height_left;
    parent->height_left=std::max(grandParent->height_left, parent->height_left)+1;
    grandParent->height_right=temp_height;

    TreeNode* great_grandParent=grandParent->parent;
    TreeNode* temp_node=parent->left;
    parent->left=grandParent;
    grandParent->right=temp_node;
    if(temp_node!=nullptr) temp_node->parent=grandParent;
    grandParent->parent=parent;

    if(great_grandParent==nullptr) {
      root=parent;
      parent->parent=nullptr;
    }
    else if(great_grandParent->right==grandParent) {
      great_grandParent->right=parent;
      parent->parent=great_grandParent;
    }
    else {
      great_grandParent->left=parent;
      parent->parent=great_grandParent;
    }
    totalParentChildUpdateCost += 3*perParentChildUpdateCost;
  }

  void myRotateLeftRight(TreeNode* currNode, TreeNode* parent, TreeNode* grandParent) {
    myRotateRightRight(currNode->left, currNode, parent);
    myRotateLeftLeft(parent, currNode, grandParent);
  }

  void myRotateRightLeft(TreeNode* currNode, TreeNode* parent, TreeNode* grandParent) {
    myRotateLeftLeft(currNode->left, currNode, parent);
    myRotateRightRight(parent, currNode, grandParent);
  }


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
      bool result = (leftArg->JourneyCode < rightArg->JourneyCode);
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
};

#endif
