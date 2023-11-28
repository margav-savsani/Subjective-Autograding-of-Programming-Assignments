#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

TreeNode *parent(TreeNode *x,int jrnyCode,int price){
    x->height=1;
    if(x->JourneyCode> j ) {
              
             if(x->left == nullptr){return x;}
             else { return parent(x->left,j,price);}  
         } 
         
         else if(x->JourneyCode <j){
             
             if(x->right == nullptr){return x;}
             else {return parent(x->right,j,price);}
         }  
         
         else{
              if(x->left==nullptr){ return x;}
              else if(x->right==nullptr) {return x;}
              else {return parent(x->right,j,price);}
         }
}

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
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
  
   TreeNode *T3 = parentNode->right;
  
  updateAVLParentChild(grandParentNode, parentNode, false);

  updateAVLParentChild(T3, grandParentNode, true);

  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
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
  
  updateAVLParentChild(currNode, parentNode, false);
  
   TreeNode *T3 = parentNode->left;
   
  updateAVLParentChild(grandParentNode, parentNode, true);
  
  updateAVLParentChild(T3, grandParentNode, false);
  
  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{

  TreeNode *greatGrandParentNode = grandParentNode->parent;

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
  
  TreeNode *T2 = currNode->left;
  
  TreeNode *T3 = currNode->right;

  updateAVLParentChild(T2, parentNode, false);

  updateAVLParentChild(T3, grandParentNode, true);

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;

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
  
  updateAVLParentChild(parentNode, currNode, false);
  
  updateAVLParentChild(grandParentNode, currNode, true);
  
  TreeNode *T2 = currNode->left;
  
  TreeNode *T3 = currNode->right;
  
  updateAVLParentChild(T3, parentNode, true);

  updateAVLParentChild(T2, grandParentNode, false);
  
  return true;
}


// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int jrnyCode, int price)
{
  

  // You MUST use only AVLLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke AVLLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  if( root =nullptr){
  root = new TreeNode();
  root->JourneyCode=jrnyCode;
  root->price=price; root->left=nullptr;root->right=nullptr;
   }
   else{ 
       
       TreeNode* n = parent(root,jrnyCode,price);
       
       if(n->JourneyCode>jrnyCode) { 
            
            n->left=new TreeNode();
            (n->left)->price=price;(n->left)->JourneyCode=JourneyCode;
            (n->left)->parent=n; (n->left)->height=0;
           
       }
       else {n->right=new TreeNode();(n->right)->price=price;(n->right)->JourneyCode=jrnyCode;
            (n->right)->parent=n;(n->right)->height=0;
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


