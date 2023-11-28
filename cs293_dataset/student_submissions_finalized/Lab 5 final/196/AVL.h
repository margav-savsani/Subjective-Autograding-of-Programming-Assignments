#ifndef AVL_H
#define AVL_H

#ifndef TREE_H
#include "Tree.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif
int max(int a, int b){
  if(a>b){
    return a;
  }
  else{
    return b;
  }
}
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
  //Updates the height of arg node depending on the height of its children 
  void updateheight(TreeNode *node){
    if(node==nullptr){
      return;
    }
    if(node->left==nullptr && node->right==nullptr){
      node->height=0;
    }
    else if(node->left==nullptr){
      node->height=node->right->height+1;
    }
    else if(node->right==nullptr){
      node->height=node->left->height+1;
    }
    else{
      node->height=max(node->left->height,node->right->height)+1;
    }
  }
  //Returns true if imbalance is found at the arg node
  //Otherwise returns false
  bool checkimbalance(TreeNode *node){
    if(node->left!=nullptr && node->right!=nullptr){
      if(node->left->height-node->right->height==1){
        return false;
      }
      else if(node->right->height-node->left->height==1){
        return false;
      }
      else if(node->left->height==node->right->height){
        return false;
      }
      return true;
    }
    else if(node->left==nullptr){
      if(node->right->height==0){
        return false;
      }
      return true;
    }
    else if(node->right==nullptr){
      if(node->left->height==0){
        return false;
      }
      return true;
    }
    return false;
  }
  //Checks for which type of rotation is to be performed
  //given curr parent and grandparent node
  int checkrotation(TreeNode *grandParentNode, TreeNode *parentNode, TreeNode *curr){
    if(grandParentNode->left==parentNode){
      if(parentNode->left==curr){
        return 1; //LeftLeft=1
      }
      else if(parentNode->right==curr){
        return 2;  //LeftRight=2
      }
      else{
        return 0; //If some error occurs
      }
    }
    else if(grandParentNode->right==parentNode){
      if(parentNode->right==curr){
        return 3;  //RightRight=3
      }
      else if(parentNode->left==curr){
        return 4; //RightLeft=4
      }
      else{
        return 0; //if some error occurs
      }
    }
    return 0; //if some error occurs
  }
  //returns true if leftarg-journeycode<rightarg-journeycode
  //also adds the comparison cost
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
  //updates given args as child and parent depending on bool
  //bool specifies whether to make it a left child or not
  //Also updates pointer update cost
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
  //Prints the AVL
  void print() { printBinaryTree(root, "", false); return;}
};

#endif
