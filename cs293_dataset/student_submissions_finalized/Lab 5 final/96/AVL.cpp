#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

int getHeight(TreeNode* node){
  if(node->left==nullptr) return node->right->height+1;
  else if(node->right==nullptr) return node ->left->height+1;
  else return 1+max(node->left->height,node->right->height);
}
bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;

  TreeNode *T3 = parentNode->right;
  
  if(greatGrandParentNode==nullptr){

    root=parentNode;

    updateAVLParentChild(currNode, parentNode, true);

    updateAVLParentChild(grandParentNode, parentNode, false);

    updateAVLParentChild(T3, grandParentNode, true);

    parentNode->height=getHeight(parentNode);

    grandParentNode->height=getHeight(grandParentNode);

    return true;
  }

  bool isGPLeftChild;
  if (greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);

  updateAVLParentChild(currNode, parentNode, true);

  updateAVLParentChild(grandParentNode, parentNode, false);

  updateAVLParentChild(T3, grandParentNode, true);

  parentNode->height=getHeight(parentNode);

  grandParentNode->height=getHeight(grandParentNode);

  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{

  TreeNode *greatGrandParentNode = grandParentNode->parent;

  TreeNode *T2 = currNode->left;

  TreeNode *T3 = currNode->right;

  if(greatGrandParentNode==nullptr){
    
    root=currNode;

    updateAVLParentChild(parentNode, currNode, true);

    updateAVLParentChild(grandParentNode, currNode, false);

    updateAVLParentChild(T2, parentNode, false);

    updateAVLParentChild(T3, grandParentNode, true);

    currNode->height=getHeight(currNode);

    parentNode->height=getHeight(parentNode);

    grandParentNode->height=getHeight(grandParentNode);

    return true;
  }
  bool isGPLeftChild;
  if (greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

  updateAVLParentChild(parentNode, currNode, true);

  updateAVLParentChild(grandParentNode, currNode, false);

  updateAVLParentChild(T2, parentNode, false);

  updateAVLParentChild(T3, grandParentNode, true);

  currNode->height=getHeight(currNode);

  parentNode->height=getHeight(parentNode);

  grandParentNode->height=getHeight(grandParentNode);

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  TreeNode *greatGrandParentNode = grandParent->parent;

  TreeNode *T1 = grandParent->left;
  
  TreeNode *T2 = currNode->left;

  if(greatGrandParentNode==nullptr){
    
    root=currNode;
  
    updateAVLParentChild(grandParent, currNode, true);

    updateAVLParentChild(parent, currNode, false);

    updateAVLParentChild(T1, grandParent, true);
  
    updateAVLParentChild(T2, grandParent, false);

    currNode->height=getHeight(currNode);

    parent->height=getHeight(parent);

    grandParent->height=getHeight(grandParent);

    return true;
  }

  bool isGPLeftChild;
  if (greatGrandParentNode->left == grandParent) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParent) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

  updateAVLParentChild(grandParent, currNode, true);

  updateAVLParentChild(parent, currNode, false);

  updateAVLParentChild(T1, grandParent, true);
  
  updateAVLParentChild(T2, grandParent, false);

  currNode->height=getHeight(currNode);

  parent->height=getHeight(parent);

  grandParent->height=getHeight(grandParent);

  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  TreeNode *greatGrandParentNode = grandParent->parent;

  TreeNode *T2 = parent->left;

  if(greatGrandParentNode==nullptr){
    
    root=parent;

    updateAVLParentChild(currNode, parent, false);
  
    updateAVLParentChild(grandParent, parent, true);

    updateAVLParentChild(T2, grandParent, false);

    parent->height=getHeight(parent);

    grandParent->height=getHeight(grandParent);
    return true;
  }

  bool isGPLeftChild;
  if (greatGrandParentNode->left == grandParent) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParent) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  updateAVLParentChild(parent, greatGrandParentNode, isGPLeftChild);

  updateAVLParentChild(currNode, parent, false);
  
  updateAVLParentChild(grandParent, parent, true);

  updateAVLParentChild(T2, grandParent, false);

  parent->height=getHeight(parent);

  grandParent->height=getHeight(grandParent);

  return true;
}

//returns balance of a node
int balance(TreeNode* node){
  if(node->left==nullptr || node->right==nullptr) return 0;
  return node->left->height-node->right->height;
}

//returns true if childnode is left child of parent node,false otherwise
bool isLeftChild(TreeNode* childNode,TreeNode* parentNode){
  if(parentNode->left==childNode) return true;
  return false;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
bool AVLTree::insert(int jrnyCode, int price)
{
  //returns false if a node with given journey code already exists
  if(find(jrnyCode)!=-1) return false;

  TreeNode* node= new TreeNode(jrnyCode,price);

  //inserts the new node
  if(root==nullptr) root= node;
  else{
    TreeNode* curr=root;
    while(true){
      if(AVLLessThan(node,curr)){
        if(curr->left!=nullptr) curr=curr->left;
        else{
          updateAVLParentChild(node,curr,true);
          break;
        }
      }
      else{
        if(curr->right!=nullptr) curr=curr->right;
        else{
          updateAVLParentChild(node,curr,false);
          break;
        }
      }
    }

    // updates height for all nodes on the path from new inserted node to the root
    while(true){
      if(curr==nullptr) break;
      else{
        curr->height=getHeight(curr);
        curr=curr->parent;
      }
    }
    TreeNode* temp=node;
    // finds the first point of imbalance on the path from new inserted node to the root and use the appropriate rotation to get balanced tree. 
    while(true){
      if(temp==nullptr || temp->parent==nullptr || temp->parent->parent==nullptr) break;
      else{
        TreeNode* p=temp->parent;
        TreeNode* gp=p->parent;
        if(balance(gp)>1 && isLeftChild(temp,p)){
          rotateLeftLeft(temp,p,gp);
          break;
        }
        else if(balance(gp)>1 && !isLeftChild(temp,p)){
          rotateLeftRight(temp,p,gp);
          break;
        }
        else if(balance(gp)<-1 && isLeftChild(temp,p)){
          rotateRightLeft(temp,p,gp);
          break;
        }
        else if(balance(gp)<-1 && !isLeftChild(temp,p)){
          rotateRightRight(temp,p,gp);
          break;
        }
        else temp=p;
      }
    }
  }

  return true;
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.

int AVLTree::find(int jrnyCode)
{
  if(root==nullptr) return -1;
  TreeNode* node=new TreeNode(jrnyCode,1);
  TreeNode* curr=root;
  while(true){
    if(!AVLLessThan(node,curr) && !AVLLessThan(curr,node)) return curr->getPrice();
    else if(AVLLessThan(node,curr)){
      if(curr->left==nullptr) break;
      else curr=curr->left;
    }
    else{
      if(curr->right==nullptr) break;
      else curr=curr->right;
    }
  }

  return -1;
}


bool AVLTree::remove(int jrnyCode)
{
  return true;
}
