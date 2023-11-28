#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif


// Prof. Garg's lectures           Our code
//   x                             currNode
//   y                             parentNode
//   z                             grandParentNode

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{ 

  // Moreover, currNode is the left child of parentNode, and
  // parentNode is the left child of grandParentNode
  // That's why we are doing a rotateLeftLeft


  if(grandParentNode->parent!=nullptr){
    TreeNode *greatGrandParentNode = grandParentNode->parent;

    // First find if grandParentNode is the left or right child of
    // greatGrandParentNode

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
    
    // Let T3 be the right child of parentNode (i.e. of y, using notation
    // from Prof. Garg's lectures

    TreeNode *T3 = parentNode->right;
    updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
    updateAVLParentChild(currNode, parentNode, true);
    updateAVLParentChild(grandParentNode, parentNode, false);
    updateAVLParentChild(T3, grandParentNode, true);
  }
  else{
    TreeNode *T3 = parentNode->right;
    parentNode->parent=nullptr;
    root=parentNode;
    updateAVLParentChild(currNode, parentNode, true);
    updateAVLParentChild(grandParentNode, parentNode, false);
    updateAVLParentChild(T3, grandParentNode, true);
  }
  grandParentNode->height = grandParentNode->height -1;
  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Moreover, currNode is the right child of parentNode, and
  // parentNode is the left child of grandParentNode.  That's
  // why we are doing a rotateLeftRight

  if(grandParentNode->parent!=nullptr){
    TreeNode *greatGrandParentNode = grandParentNode->parent;

  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

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

    // Let T2 be the left child of currNode (i.e. of x)
    TreeNode *T2 = currNode->left;

    // Let T3 be the right child of currNode (i.e. of x)
    TreeNode *T3 = currNode->right;
    updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
    updateAVLParentChild(parentNode, currNode, true);
    updateAVLParentChild(grandParentNode, currNode, false);
    updateAVLParentChild(T2, parentNode, false);
    updateAVLParentChild(T3, grandParentNode, true);
  }
  else{
    TreeNode *T2 = currNode->left;
    TreeNode *T3 = currNode->right;
    currNode->parent=nullptr;
    root=currNode;
    updateAVLParentChild(parentNode, currNode, true);
    updateAVLParentChild(grandParentNode, currNode, false);
    updateAVLParentChild(T2, parentNode, false);
    updateAVLParentChild(T3, grandParentNode, true); 
  }
  currNode->height=currNode->height+1;
  parentNode->height = parentNode->height-1;
  grandParentNode->height = grandParentNode->height-1;
  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Moreover, currNode is the left child of parentNode, and
  // parentNode is the right child of grandParentNode.  That's
  // why we are doing a rotateRightLeft

  if(grandParent->parent!=nullptr){
  TreeNode *greatGrandParentNode = grandParent->parent;
  bool isGPLeftChild;

  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode


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
  // Let T2 be the right child of currNode (i.e. of x)
  TreeNode *T2 = currNode->right;

  // Let T3 be the left child of currNode (i.e. of x)
  TreeNode *T3 = currNode->left;
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(parent, currNode, false);
  updateAVLParentChild(grandParent, currNode, true);
  updateAVLParentChild(T2, parent, true);
  updateAVLParentChild(T3, grandParent, false);
  }
  else{
    TreeNode *T2 = currNode->right;
    TreeNode *T3 = currNode->left;
    currNode->parent=nullptr;
    root=currNode;
    updateAVLParentChild(parent, currNode, false);
    updateAVLParentChild(grandParent, currNode, true);
    updateAVLParentChild(T2, parent, true);
    updateAVLParentChild(T3, grandParent, false);
  }
  currNode->height=currNode->height+1;
  parent->height = parent->height-1;
  grandParent->height = grandParent->height-1;
  return true;  
  
  
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Moreover, currNode is the right child of parentNode, and
  // parentNode is the right child of grandParentNode
  // That's why we are doing a rotateRightRight

  if(grandParent->parent!=nullptr){
    TreeNode *greatGrandParentNode = grandParent->parent;

    // First find if grandParentNode is the left or right child of
    // greatGrandParentNode

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
    // Let T3 be the left child of parentNode (i.e. of y, using notation
    // from Prof. Garg's lectures
    TreeNode *T3 = parent->left;
    updateAVLParentChild(parent, greatGrandParentNode, isGPLeftChild);
    updateAVLParentChild(currNode, parent, false);
    updateAVLParentChild(grandParent, parent, true);
    updateAVLParentChild(T3, grandParent, false);
  }
  else{
    TreeNode *T3 = parent->left;
    parent->parent=nullptr;
    root=parent;
    updateAVLParentChild(currNode, parent, false);
    updateAVLParentChild(grandParent, parent, true);
    updateAVLParentChild(T3, grandParent, false);
  }
  grandParent->height = grandParent->height -1;
  return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int jrnyCode, int price)
{
  TreeNode *x,*z;
  x = this->root;
  if(x==nullptr){ 
    x = new TreeNode(jrnyCode,price); //node created with 
    root=x;
    root->height=0;
  }
  else{
    while(true){ 
      TreeNode *y;
      y = new TreeNode(jrnyCode,price); //node created to insert
      if(AVLLessThan(y,x)){ 
        if(x->left==nullptr){
          updateAVLParentChild(y,x,true);
          y->height=0;
          x = x->left;
          break;
        }
        else{
          x = x->left;
        }
      }   
      else if(AVLLessThan(x,y)){
        if(x->right==nullptr){
            updateAVLParentChild(y,x,false);
            y->height=0;
            x = x->right;
            break;
        }
        else{
            x = x->right;
        }
      }   
      else{
        return false;
      }
    }
  }
  
  z = x;
  bool balance = false; //checks if the tree is balanced or not
  while(true){
    if(z->parent!=nullptr){ //updating the height of the nodes till we get the imbalanced node
      if(!(z->parent->height == z->height + 1)){
      z->parent->height = z->parent->height + 1;
    }
    }
    else{
      balance =true;
      break;
    }
    if(z->parent!=nullptr){
      if(z->parent->parent==nullptr){
        balance = true;
      }
    }
    if(z->parent->parent!=nullptr){
      if(z->parent->parent->left!=nullptr && z->parent->parent->right!=nullptr){
        if(!(abs(z->parent->parent->left->height - z->parent->parent->right->height)==1 || z->parent->parent->left->height == z->parent->parent->right->height)){
          break;
        }
      }
      else{
        break;
      }
    }
    z = z->parent;
  }
  bool left1; //checking if z is left or right of its parent
  bool left2; //checking if parent of z is left or right of its parent
  if(!balance){
    if(z==z->parent->left){
      left1=true;
    }
    else{
      left1=false;
    }
    if(z->parent==z->parent->parent->left){
      left2=true;
    }
    else{
      left2=false;
    }
    if(left1 && left2){
      rotateLeftLeft(z,z->parent,z->parent->parent);
    }
    if(!left1 && left2){
      rotateLeftRight(z,z->parent,z->parent->parent);
    }
    if(left1 && !left2){
      rotateRightLeft(z,z->parent,z->parent->parent);
    }
    if(!left1 && !left2){
      rotateRightRight(z,z->parent,z->parent->parent);
    }

  }
  return true;
}


int AVLTree::find(int jrnyCode) //finding the node with journey code as jrnycode
{
  TreeNode *x;
  x = this->root;
  TreeNode *y;
  y = new TreeNode(jrnyCode,0);
  while(true){
    if(x==nullptr){
      break;
    }
    if(x->journeycode()==jrnyCode){
      return x->Price();
    }
    else if(AVLLessThan(y,x)){ 
      x = x->left;
    }
    else if(AVLLessThan(x,y)){
      x= x->right;
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


