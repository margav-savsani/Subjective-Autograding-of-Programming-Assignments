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

  bool BSTEqualTo(TreeNode* leftArg, TreeNode*rightArg) {
    if ((leftArg != nullptr) && (rightArg != nullptr)) {
      bool result = (*leftArg == *rightArg);
      totalComparisonCost += perComparisonCost;
      return result;
    }
    else {
      cerr << "Unexpected exceptional condition!" << endl;
      exit(-1);
    }

  }

  // To save values of temp2 into temp1
  void Equate(TreeNode* temp1, TreeNode* temp2){
    temp1->updateNodefromNode(temp2);
  }

  // Updates the height based on the height of the children, takes care even if either or both of its children is null
  int h(TreeNode *node1, TreeNode *node2) {
    if (node1 == nullptr && node2 == nullptr) {
      return 0;
    } else if (node1 == nullptr && node2 != nullptr) {
      return node2->height + 1;
    } else if (node2 == nullptr && node1 != nullptr) {
      return node1->height + 1;
    } else {
      return max(node1->height, node2->height) + 1;
    }
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

  bool insert(int jrnyCode, int price);
  int find(int jrnyCode);

  // Optional: Implement "remove" only for bonus marks
  
  bool remove(int jrnyCode);

  int getComparisonCost() { return totalComparisonCost; }
  int getParentChildUpdateCost() { return totalParentChildUpdateCost; }
  void print() { printBinaryTree(root, "", false); return;}
};

#endif
