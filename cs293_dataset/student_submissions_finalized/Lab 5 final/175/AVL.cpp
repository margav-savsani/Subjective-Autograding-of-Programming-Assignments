#ifndef AVL_H
#include "AVL.h"
#include <bits/stdc++.h>
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
  bool isGPLeftChild = true;
  if (greatGrandParentNode != nullptr){
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
      root = parentNode;
  }
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  TreeNode *T3 = parentNode->right;
  updateAVLParentChild(T3, grandParentNode, true);
  updateAVLParentChild(currNode, parentNode, true);
  updateAVLParentChild(grandParentNode, parentNode, false);

  

  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  bool isGPLeftChild = true;
  if (greatGrandParentNode != nullptr){
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
      root = currNode;
  }
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;
  updateAVLParentChild(T2, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);
  updateAVLParentChild(parentNode, currNode, true);
  updateAVLParentChild(grandParentNode, currNode, false);

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  bool isGPLeftChild;
  if (greatGrandParentNode != nullptr){
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
      root = currNode;
  }
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;
  updateAVLParentChild(T3, parentNode, true);
  updateAVLParentChild(T2, grandParentNode, false);
  updateAVLParentChild(parentNode, currNode, false);
  updateAVLParentChild(grandParentNode, currNode, true);
  
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  bool isGPLeftChild = true;
  if (greatGrandParentNode != nullptr){
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
      root = parentNode;
  }
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  TreeNode *T3 = parentNode->left;
  updateAVLParentChild(T3, grandParentNode, false);
  updateAVLParentChild(currNode, parentNode, false);
  updateAVLParentChild(grandParentNode, parentNode, true);
  
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

  TreeNode *foo = new TreeNode(jrnyCode, 0);
  TreeNode *tmp = root;
  TreeNode *parent = nullptr;
  bool dir;       // 'dir' gives the direction of traversing which is used in line 50
  while (tmp != nullptr){
      if (AVLLessThan(foo, tmp)){
          parent = tmp;
          tmp = tmp->left;
          dir = true;
      }
      else if (AVLLessThan(tmp, foo)){
          parent = tmp;
          tmp = tmp->right;
          dir = false;
      }
      else{
          return false;
      }
  }
  if (parent != nullptr){ // the 'non-root' case
      if (dir){
          parent->left = new TreeNode(jrnyCode, price, nullptr, nullptr, parent, 0);
          tmp = parent->left;
      }
      else{
          parent->right = new TreeNode(jrnyCode, price, nullptr, nullptr, parent, 0);
          tmp = parent->right;
      }
  }
  else{ // the 'root' case
      root = new TreeNode(jrnyCode, price, nullptr, nullptr, nullptr, 0);
      return true;
  }

  // updation of heights
  TreeNode *child = nullptr;
  while (tmp != nullptr && tmp->parent != nullptr){
      parent = tmp->parent;
      if (parent->left == nullptr || parent->right == nullptr){
          if (tmp->height == 0){
              parent->height = 1;
              child = tmp;
              tmp = parent;         
          }
          else{
              if (parent->left == tmp && tmp->left == child){
                  rotateLeftLeft(child, tmp, parent);
                  parent->height = child->height;
                  child = tmp;
                  tmp = tmp->parent;
              }
              else if (parent->left == tmp && tmp->right == child){
                  rotateLeftRight(child, tmp, parent);
                  tmp->height -= 1;
                  child->height += 1;
                  parent->height = child->height - 1;
                  tmp = child->parent;
              }
              else if (parent->right == tmp && tmp->left == child){
                  rotateRightLeft(child, tmp, parent);
                  tmp->height -= 1;
                  child->height += 1;
                  parent->height = child->height - 1;
                  tmp = child->parent;
              }
              else{
                  rotateRightRight(child, tmp, parent);
                  parent->height = child->height;
                  child = tmp;
                  tmp = tmp->parent;
              }    
          }
      }
      else{
          if (abs(parent->left->height - parent->right->height) <= 1){
              parent->height = 1 + max(parent->left->height, parent->right->height);
              tmp = parent;
              child = tmp;           
          }
          else{
              if (parent->left == tmp && tmp->left == child){
                  rotateLeftLeft(child, tmp, parent);
                  parent->height = child->height;
                  child = tmp;
                  tmp = tmp->parent;
              }
              else if (parent->left == tmp && tmp->right == child){
                  rotateLeftRight(child, tmp, parent);
                  tmp->height -= 1;
                  child->height += 1;
                  parent->height = child->height - 1;
                  tmp = child->parent;
              }
              else if (parent->right == tmp && tmp->left == child){
                  rotateRightLeft(child, tmp, parent);
                  tmp->height -= 1;
                  child->height += 1;
                  parent->height = child->height - 1;
                  tmp = child->parent;
              }
              else{
                  rotateRightRight(child, tmp, parent);
                  parent->height = child->height;
                  child = tmp;
                  tmp = tmp->parent;
              }  
          }
      }
  }
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

    TreeNode *foo = new TreeNode(jrnyCode, 0);
    TreeNode *tmp = root;
    while (tmp != nullptr){
        if (AVLLessThan(tmp, foo)){
            tmp = tmp->right;
        }
        else if (AVLLessThan(foo, tmp)){
            tmp = tmp->left;
        }
        else{
            return tmp->price;
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


