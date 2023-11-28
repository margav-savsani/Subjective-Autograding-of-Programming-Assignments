#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

// Recall from Prof. Naveen Garg's lectures how the various rotations are
// applied to restore the balance factor at all nodes of an AVL tree
// to either 0, 1 or -1, after an insert or delete.
// The correspondence between the terminology in Prof. Garg's lectures and
// our terminology in this code is as follows:
//
// Prof. Garg's lectures           Our code
// ---------------------           --------
//   x                             currNode
//   y                             parentNode
//   z                             grandParentNode
//
// Recall also that z (grandParentNode) is the lowest node in the path from
// the root to the inserted node or to the deleted node (as the case may be)
// where the balance factor has either become < -1 or > 1.
// To find what x (currNode) and y (parentNode) should be, you need to
// recall Prof. Garg's lectures.
// These are slightly differently defined when inserting nodes and when
// deleting nodes

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  bool isGPLeftChild;
  if(greatGrandParentNode!=nullptr){
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
  }
  else{
    isGPLeftChild=false;
    root=parentNode;
  }
  TreeNode *T3 = parentNode->right;
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(currNode, parentNode, true);
  updateAVLParentChild(grandParentNode, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);
  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  bool isGPLeftChild;
  if(greatGrandParentNode!=nullptr){
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
  }
  else{
    isGPLeftChild=true;
    root=currNode;
  }
  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(parentNode, currNode, true);
  updateAVLParentChild(grandParentNode, currNode, false);
  updateAVLParentChild(T2, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);
  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  TreeNode *greatGrandParentNode = grandParent->parent;
  bool isGPLeftChild;
    if(greatGrandParentNode!=nullptr){
    if (greatGrandParentNode->right == grandParent) {
      isGPLeftChild = false;
    }
    else if (greatGrandParentNode->left == grandParent) {
      isGPLeftChild = true;
    }
    else {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }
  }
  else{
    isGPLeftChild=false;
    root=currNode;
  }
  TreeNode *T2 = currNode->right;
  TreeNode *T3 = currNode->left;
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(parent, currNode, false);
  updateAVLParentChild(grandParent, currNode, true);
  updateAVLParentChild(T2, parent, true);
  updateAVLParentChild(T3, grandParent, false);
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  TreeNode *greatGrandParentNode = grandParent->parent;
  bool isGPLeftChild;
  if(greatGrandParentNode!=nullptr){
    if (greatGrandParentNode->right == grandParent) {
      isGPLeftChild = false;
    }
    else if (greatGrandParentNode->left == grandParent) {
      isGPLeftChild = true;
    }
    else {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }
  }
  else{
    isGPLeftChild=true;
    root=parent;
  }
  TreeNode *T3 = parent->left;
  updateAVLParentChild(parent, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(currNode, parent, false);
  updateAVLParentChild(grandParent, parent, true);
  updateAVLParentChild(T3, grandParent, false);
  return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int jrnyCode, int price)
{
  // Implement insertion in AVL tree followed by balance factor restoration
  // by properly identifying x, y, z as used in Prof. Garg's lectures
  // (equivalently, currNode, parentNode, grandParentNode in our code) and
  // invoking rotateLeftLeft, rotateLeftRight, rotateRightLeft and/or
  // rotateRightRight as appropriate.

  // It is your responsibility to find out the right x, y, z (or currNode,
  // parentNode, grandParentNode) following Prof. Garg's lectures
  //
  // Once you identify these correctly, simply invoking the appropriate
  // rotation should do the job.
  // You don't even need to invoke rotation twice for the double
  // rotations -- the way rotationLeftRight is implemented, and
  // rotationRightLeft should be implemented, you should be able to achieve
  // the effect of the double rotation using one invokation of the
  // appropriate member function.

  // You MUST use only AVLLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke AVLLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.

  if(find(jrnyCode) != -1)return false;
  TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  TreeNode *newnode = new TreeNode(jrnyCode,price);

  while (currNode != nullptr) {
    if (AVLLessThan(currNode, newnode)) {
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }
    else if (AVLLessThan(newnode, currNode)) {
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
    else { // currNode->JourneyCode == JourneyCode
      return false;
    }
  } 
  if(root == nullptr){
      root = new TreeNode(jrnyCode,price);
  }
  else if (AVLLessThan(newnode, parentOfCurrNode)){
    updateAVLParentChild(newnode,parentOfCurrNode,true);
    currNode=newnode;
  }
  else{ 
    updateAVLParentChild(newnode,parentOfCurrNode,false);
    currNode=newnode;
  }
  updateHtTree(currNode);
  
  bool res;
  //if(currNode == root)return true;
  //else{
    if(currNode!= nullptr && parentOfCurrNode != nullptr && parentOfCurrNode->parent != nullptr){
    
        //TreeNode *x = currNode;
        //TreeNode *y = parentOfCurrNode;
        TreeNode *z = parentOfCurrNode->parent;
        int cnt;
          while(z->parent != nullptr){
            cnt=-1;
            if(getBalance(z) > 1 || getBalance(z) < -1){
              bool isleft1;
              bool isleft2;
              if(z->left ==parentOfCurrNode) isleft1=true;
              else isleft1=false;
              if(parentOfCurrNode->left == currNode) isleft2=true;
              else isleft2=false;
              if(isleft1==true && isleft2==true && getBalance(z)>1)
                res = rotateLeftLeft(currNode,parentOfCurrNode,z);
              else if(isleft1==true && isleft2==false && getBalance(z)>1)
                res = rotateLeftRight(currNode,parentOfCurrNode,z);
              else if(isleft1==false && isleft2==false && getBalance(z)<-1)
                res = rotateRightRight(currNode,parentOfCurrNode,z);
              else
                res = rotateRightLeft(currNode,parentOfCurrNode,z);
              
              cnt =1;
            }
            if(cnt==1){
              //updateHtTree(currNode); 
              //updateHtTree(parentOfCurrNode); 
              updateHtTree(z);
              
            }
            currNode = parentOfCurrNode;
            parentOfCurrNode = z;
            z = z->parent;
          }
    }
  //}
  
  return true; 
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
{
  // Implement find in AVL tree.
  // This is really no different from finding in a binary search tree.
  // This operation cannot cause any balance factor disturbances.

  // You MUST use only AVLLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke AVLLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
  
  TreeNode *currNode = root, *parentOfCurrNode = nullptr;
    TreeNode *newnode = new TreeNode(jrnyCode,0);
    while (currNode != nullptr) {
        if (AVLLessThan(currNode, newnode)) {
            parentOfCurrNode = currNode;
            currNode = currNode->right;
        }
        else if (AVLLessThan(newnode, currNode)) {
            parentOfCurrNode = currNode;
            currNode = currNode->left;
        }
        else { // currNode->JourneyCode == JourneyCode
            return currNode->getP();
        }
    } 
    return -1;
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in AVL tree with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the AVL tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::remove(int jrnyCode)
{
  // Implement deletion in AVL tree followed by balance factor restoration
  // by properly identifying x, y, z as used in Prof. Garg's lectures
  // (equivalently, currNode, parentNode, grandParentNode in our code) and
  // invoking rotateLeftLeft, rotateLeftRight, rotateRightLeft and/or
  // rotateRightRight as appropriate.

  // It is your responsibility to find out the right x, y, z (or currNode,
  // parentNode, grandParentNode) following Prof. Garg's lectures
  //
  // Once you identify these correctly, simply invoking the appropriate
  // rotation(s) should do the job.
  // You don't even need to invoke rotation twice for the double
  // rotations -- the way rotationLeftRight is implemented, and
  // rotationRightLeft should be implemented, you should be able to achieve
  // the effect of the double rotation using one invokation of the
  // appropriate member function.

  // You MUST use only AVLLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke AVLLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // REMEMBER to update the height of appropriate nodes in the tree
  // after a successful deletion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
  return true;
}


