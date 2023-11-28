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

  // updates hight of all ancestors of currNode
  void update(TreeNode* currNode){
    while(currNode != nullptr){
      if(currNode->left == nullptr && currNode->right == nullptr){
        currNode->height = 1;
      }
      else if(currNode->left != nullptr && currNode->right == nullptr){
        currNode->height = currNode->left->height + 1;
      }
      else if(currNode->left == nullptr && currNode->right != nullptr){
        currNode->height = currNode->right->height + 1;
      }
      else{
        currNode->height = max(currNode->left->height, currNode->right->height)+1;
      }
      currNode = currNode->parent;
    }
  }
  
  TreeNode* findnode(int JourneyCode){
    struct TreeNode *currNode = root;
    TreeNode* temp = new TreeNode(JourneyCode, 1000);
    while (currNode != nullptr) {
      if (AVLLessThan(currNode, temp)) {
        currNode = currNode->right;
      }
      else if (AVLLessThan(temp, currNode)){
        currNode = currNode->left;
      }
      else { // currNode->JourneyCode == JourneyCode
        break;
      }
    }

    return currNode;
  }

  // Is balanced
  bool IsBalanced(TreeNode* currNode){
    if(currNode->left==nullptr && currNode->right==nullptr){
      return 1;
    }
    else if(currNode->left!=nullptr && currNode->right==nullptr){
      return currNode->left->height < 2;
    }
    else if(currNode->left==nullptr && currNode->right!=nullptr){
      return currNode->right->height < 2;
    }
    else{
      return abs(currNode->left->height - currNode->right->height) < 2;
    }
  }

  // get 1st imbalance
  TreeNode* firstImbalance(TreeNode* currNode){
    TreeNode* parentNode = currNode->parent;
    if(parentNode == nullptr) return nullptr;
    TreeNode* GrandparentNode = parentNode->parent;

    while(GrandparentNode != nullptr){
      if(!IsBalanced(GrandparentNode)){
        // cout << "1st imbalance " << GrandparentNode->getJourneycode() << "\n";
        break;
      }
      currNode = parentNode;
      parentNode = GrandparentNode;
      GrandparentNode = GrandparentNode->parent;
    }

    if(GrandparentNode == nullptr) return nullptr;
    else return currNode;
  }

  // Balances the tree
  bool balance(TreeNode *currNode){
    TreeNode* parentNode = currNode->parent;
    TreeNode* grandParentNode = parentNode->parent;
    bool cpleft=0, pgleft=0;
    if(parentNode->left == currNode) cpleft = 1;
    if(grandParentNode->left == parentNode) pgleft = 1;
    if(pgleft && cpleft) return rotateLeftLeft(currNode, parentNode, grandParentNode);
    if(pgleft && !cpleft) return rotateLeftRight(currNode, parentNode, grandParentNode);
    if(!pgleft && cpleft) return rotateRightLeft(currNode, parentNode, grandParentNode);
    if(!pgleft && !cpleft) return rotateRightRight(currNode, parentNode, grandParentNode);
    return true;
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
