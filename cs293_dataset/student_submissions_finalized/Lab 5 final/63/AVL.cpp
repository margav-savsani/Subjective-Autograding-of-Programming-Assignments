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
  bool isnull = 0;      // this is to handle the case when great-grandparent is a nullptr
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  if (greatGrandParentNode == nullptr){
    isnull = 1;
  }
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  bool isGPLeftChild = 0;
  if (!isnull){         // preventing pointer access when it is a nullptr
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

  // currNode = x; parentNode = y; grandParentNode = z;

/*
            z                                        y
           / \                                     /   \
          y  T4                                   x     z
         / \           ------->                  / \   / \
        x   T3                                  T1 T2 T3 T4
       / \  
      T1 T2 
*/
  
  TreeNode *T3 = parentNode->right;
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(currNode, parentNode, true);
  updateAVLParentChild(grandParentNode, parentNode, false);
  // if we are dealing with the root node, we must update it (when it changes)
  if (root == grandParentNode){
    root = parentNode;
  }
  updateAVLParentChild(T3, grandParentNode, true);
  grandParentNode->height -= 1;     // the height of grandParentNode ie z changes
  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  
  bool isnull = 0;        // this is to handle the case when great-grandparent is a nullptr
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  if (greatGrandParentNode == nullptr){
    isnull = 1;
  }
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  bool isGPLeftChild = 0;
  if (!isnull){           // preventing pointer access when it is a nullptr
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
  // currNode = x; parentNode = y; grandParentNode = z;

/*
            z                                        x
           / \                                     /   \
          y  T4                                   y     z
         / \            ------->                 / \   / \
       T1   x                                   T1 T2 T3 T4
           / \  
          T3 T2 
*/

  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;

  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(parentNode, currNode, true);
  updateAVLParentChild(grandParentNode, currNode, false);
  // if we are dealing with the root node, we must update it (when it changes)
  if (root == grandParentNode){
    root =currNode;
  }
  updateAVLParentChild(T2, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);
  // updating the heights of x, y and z
  currNode->height += 1;
  grandParentNode->height -= 1;
  parentNode->height -= 1;

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  bool isnull = 0;      // this is to handle the case when great-grandparent is a nullptr
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  if (greatGrandParentNode == nullptr){
    isnull = 1;
  }
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  bool isGPLeftChild = 0;
  if (!isnull){         // preventing pointer access when it is a nullptr
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

/*
            z                                        x
           / \                                     /   \
          T4  y                                   z     y
             / \        ------->                 / \   / \
            x   T1                              T4 T3 T2 T1
           / \  
          T3 T2 
*/
  TreeNode *T2 = currNode->right;
  TreeNode *T3 = currNode->left;
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(parentNode, currNode, false);
  updateAVLParentChild(grandParentNode, currNode, true);
  // if we are dealing with the root node, we must update it (when it changes)
  if (root == grandParentNode){
    root = currNode;
  }
  
  updateAVLParentChild(T2, parentNode, true);
  updateAVLParentChild(T3, grandParentNode, false);
  // updating the heights of x, y and z
  currNode->height += 1;
  grandParentNode->height -= 1;
  parentNode->height -= 1;
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // this is to handle the case when great-grandparent is a nullptr
  bool isnull = 0;
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  if (greatGrandParentNode == nullptr){
    isnull = 1;
  }
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  bool isGPLeftChild = 0;
  if (!isnull){        // preventing pointer access when it is a nullptr
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
/*
            z                                        y
           / \                                     /   \
          T4  y                                   z     x
             / \        ------->                 / \   / \
            T3  x                               T4 T3 T2 T1
               / \  
              T2 T1 
*/

  // Let T3 be the right child of parentNode (i.e. of y, using notation)
  TreeNode *T3 = parentNode->left;
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(currNode, parentNode, false);
  updateAVLParentChild(grandParentNode, parentNode, true);
  if (root == grandParentNode){
    root = parentNode;
  }
  updateAVLParentChild(T3, grandParentNode, false);
  grandParentNode->height -= 1;

  return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int jrnyCode, int price)
{
  TreeNode* comp = new TreeNode(jrnyCode, price);   // temporary object used for comparisions
  TreeNode * A = root;
  if (root == nullptr){
    root = new TreeNode(jrnyCode, price);
    return 1;
  }
  while (true){       // iteratively insert the element
    if (!AVLLessThan(A, comp) && !AVLLessThan(comp, A)){ // values in the node should be unique
      delete comp;
      return 0;
    }
    else if (AVLLessThan(A, comp)){
      if (A->right != nullptr){
        A = A->right;
        continue;
      }
      TreeNode * B = new TreeNode(jrnyCode, price);
      updateAVLParentChild(B, A, false);
      A = A->right;
      break;
    }
    else if (AVLLessThan(comp, A)){
      if (A->left != nullptr){
        A = A->left;
        continue;
      }
      TreeNode * B = new TreeNode(jrnyCode, price);
      updateAVLParentChild(B, A, true);
      A = A->left;
      break;
    }
  }
  delete comp;
  TreeNode *x = nullptr,*y = nullptr,*z = A;
  while(A->parent != nullptr){    // keep updating height and find the imbalance
    A = A->parent;
    x = y; 
    y = z;
    z = A;
    int hl = getheight(A, -1);
    int h = getheight(A, 0);
    int hr = getheight(A, 1);
    if (hr-hl >= 2 || hr-hl <= -2){   // handle the cases of imbalance
      bool gp = true;   // true if parent is left of grand parent
      bool pc = true;   // true if child is left of parent
      if (z->right == y){
        gp = false;
      }
      if (y->right == x){
        pc = false;
      }
      if (gp && pc){
        return rotateLeftLeft(x, y, z);
      }
      else if (gp && !pc){
        return rotateLeftRight(x, y, z);
      }
      else if (!gp && !pc){
        return rotateRightRight(x, y, z);
      }
      else if (!gp && pc){
        return rotateRightLeft(x, y, z);
      }
    }
    if (hr > hl){
      A->height = hr+1;
    }
    else {
      A->height = hl+1;
    }
  }
  return 1;
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
{
  TreeNode *A = root, *comp = new TreeNode(jrnyCode, 0);
  
  while (true){
    if (!(AVLLessThan(comp, A)) && !(AVLLessThan(A, comp))){
      return A->get_price();
    }
    else if (AVLLessThan(comp, A)){
      if (A->left == nullptr){
        return -1;
      }
      A = A->left;
      continue;
    }
    else if (AVLLessThan(A, comp)){
      if (A->right == nullptr){
        return -1;
      }
      A = A->right;
      continue;
    }
  }
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
  bool isleft = 0;
  TreeNode *A = root;
  TreeNode *comp = new TreeNode(jrnyCode, 0);
  while(true){
     if (!(AVLLessThan(comp, A)) && !(AVLLessThan(A, comp))){
      break;
    }
    else if (AVLLessThan(comp, A)){
      if (A->left == nullptr){
        return 0;
      }
      A = A->left;
      isleft = 1;
      continue;
    }
    else if (AVLLessThan(A, comp)){
      if (A->right == nullptr){
        return 0;
      }
      A = A->right;
      isleft = 0;
      continue;
    }
  }
  delete comp;
  // cout << A->get_code() << endl;
  TreeNode *B = A;
  TreeNode *C = nullptr;
  if (A->left == nullptr){
    while (B->right != nullptr){
      B = B->right;
    }
    if (B->left != nullptr){
      updateAVLParentChild(B->left, B->parent, false);
      C = B->left;
    }
    else { 
      // cout << "hi " << B->parent->get_code() << endl;
      updateAVLParentChild(nullptr, B->parent, true);
      // cout << "hi1 " << B->parent->left << endl;
      C = B->parent;
    }
  }
  else {
    while (B->left != nullptr){
      B = B->left;
      // cout << B << endl;
    }
    if (B->right != nullptr){
      updateAVLParentChild(B->left, B->parent, true);
      C = B->right;
    }
    else if (B->parent != nullptr){
      updateAVLParentChild(nullptr, B->parent, true);
      C = B->parent;
    }
  }
  //cout << C->left->get_code() << endl;
  // cout << B->get_code() << endl;
  // cout << A->get_code() << " " << B->get_code() << " " << C->get_code() << endl;
  // if (C->left != nullptr || C->right != nullptr){
    
  // }
  if (A == root){
    root = B;
    updateAVLParentChild(B, nullptr, true);
    updateAVLParentChild(A->left, B, true);
    updateAVLParentChild(A->right, B, false);
  }
  else if (A == B){
    // cout << "hi" << endl;
    updateAVLParentChild(nullptr, A->parent, isleft);
  }
  else if (A != B){
    updateAVLParentChild(B, A->parent, isleft);
    updateAVLParentChild(A->left, B, true);
    updateAVLParentChild(A->right, B, false);
    B->height = A->height;
  }
  delete A;
  A = C;
  //cout << C->left->get_code() << endl;
  if (A == nullptr){
    root = nullptr;
    return 1;
  }
  else if (A->parent == nullptr){
    int h = getheight(A, 0);
    int hl = getheight(A,-1);
    int hr = getheight(A, 1);
    A->height = hl+1;
    if (hr >hl){
      A->height = hr+1;
    }
  }
  TreeNode *x = nullptr,*y = nullptr,*z = C;
  while(A->parent != nullptr){    // keep updating height and find the imbalance
    A = A->parent;
    x = y; 
    y = z;
    z = A;
    int hl = getheight(A, -1);
    int h = getheight(A, 0);
    int hr = getheight(A, 1);
    if (hr-hl >= 2 || hr-hl <= -2){   // handle the cases of imbalance
      bool gp = true;   // true if parent is left of grand parent
      bool pc = true;   // true if child is left of parent
      if (z->right == y){
        gp = false;
      }
      if (y->right == x){
        pc = false;
      }
      if (gp && pc){
        A = y;
        rotateLeftLeft(x, y, z);
      }
      else if (gp && !pc){
        A = x;
        rotateLeftRight(x, y, z);
      }
      else if (!gp && !pc){
        A = y;
        rotateRightRight(x, y, z);
      }
      else if (!gp && pc){
        A = x;
        rotateRightLeft(x, y, z);
      }
    }
    if (hr > hl){
      A->height = hr+1;
    }
    else {
      A->height = hl+1;
    }
  }
  return 1;
}


