#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  // First find if grandParentNode is the left or right child of greatGrandParentNode
  bool isGPLeftChild;
  
  // Exception if greatGrandParentNode is nullptr
  if(greatGrandParentNode==nullptr){
    isGPLeftChild=false;
  }
  //Assign if its left or right child
  else{
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

  // Let T3 be the right child of parentNode
  TreeNode *T3 = parentNode->right;

  //Changing pointers according to algorithm
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(currNode, parentNode, true);
  updateAVLParentChild(grandParentNode, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);

  //Return true because rotation has been performed
  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;

  // First find if grandParentNode is the left or right child of greatGrandParentNode
  bool isGPLeftChild;

  // Exception if greatGrandParentNode is nullptr
  if(greatGrandParentNode==nullptr){
    isGPLeftChild=false;
  }
  //Assign if its left or right child
  else{
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
  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;

  // Updating the pointers according to algorithm
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(parentNode, currNode, true);
  updateAVLParentChild(grandParentNode, currNode, false);
  updateAVLParentChild(T2, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{

  // First find if grandParentNode is the left or right child of greatGrandParentNode
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  // Check if left child
  bool isGPLeftChild;

  // Exception if greatGrandParentNode is nullptr
  if(greatGrandParentNode==nullptr){
    isGPLeftChild=false;
  }
  //Assign if its left or right child
  else{
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

  //Store the left and right child of current node
  TreeNode *T2 = currNode->right;
  TreeNode *T3 = currNode->left;

  //Updating the pointers according to algorithm
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(parentNode, currNode, false);
  updateAVLParentChild(grandParentNode, currNode, true);
  updateAVLParentChild(T2, parentNode, true);
  updateAVLParentChild(T3, grandParentNode, false);

  //return true;
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  
  // First find if grandParentNode is the left or right child of greatGrandParentNode
  TreeNode *greatGrandParentNode = grandParentNode->parent;

  // Check if left child
  bool isGPLeftChild;
  if(greatGrandParentNode==nullptr){
    isGPLeftChild=false;
  }
  // Exception if greatGrandParentNode is nullptr
  else{
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

  //Store the left child of T3
  TreeNode *T3 = parentNode->left;

  //Updating the pointers according to algorithm
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(currNode, parentNode, false);
  updateAVLParentChild(grandParentNode, parentNode, true);
  updateAVLParentChild(T3, grandParentNode, false);

  //Return true because successful rotation
  return true;
}

//Returns true if inserted successfully, false otherwise
bool AVLTree::insert(int jrnyCode, int price)
{
  //Exceptional case if AVL Tree is empty
  TreeNode *temp = new TreeNode(jrnyCode,price);
  if ( root==nullptr ) {
    root = temp;
    root->height=1;
    return true;
  }

  //Define variables and run while loop to find place of insertion
  TreeNode *node = new TreeNode(jrnyCode,price);
  TreeNode *y = root;
  TreeNode *x = root;
  bool leftChild = false;
  while(x!=nullptr){
    y = x;
    if (AVLLessThan(node,x)){
      leftChild=true;
      x=x->left;
    }
    else if (AVLLessThan(x,node)){
      leftChild=false;
      x=x->right;
    }
    else{
      return false;
    }
  }
  //Insert the node as a child  of y
  updateAVLParentChild(node, y, leftChild);
  
  //Exceptional case if parent of node is root
  if (y->parent==nullptr){
    updateHeight(node);
    return true;
  }

  //Move upwards to resolve imbalance
  TreeNode *curr = node;
  TreeNode *parr = y;
  TreeNode *gpar = y->parent;
  curr->height=1;
  if (parr->height==2){
    return true;
  }
  else{
    parr->height = 2;
  }
  while(gpar!=nullptr){
    //Some dummy variables to make logic easier
    int l, r, h;
    if (gpar->left==nullptr){
      l = 0;
    }
    else {
      l = gpar->left->height;
    }

    if (gpar->right==nullptr){
      r = 0;
    }
    else {
      r = gpar->right->height;
    }
    h = gpar->height;

    //No balancing needed
    if ( l==r ){
      return true;
    }
    //Balance the tree here
    else if ( l-r==2 || r-l==2 ){
      bool is_chachu;
      bool is_chhotu;
      if ( gpar->left == parr ){
        is_chachu = true;
      }
      else{
        is_chachu = false;
      }

      if ( parr->left == curr ){
        is_chhotu = true;
      }
      else{
        is_chhotu = false;
      }
      if ( is_chachu && is_chhotu ){
        bool b = (gpar->parent==nullptr);
        rotateLeftLeft(curr,parr,gpar);
        if(b){root=parr;}
        updateHeight(curr);
        updateHeight(gpar);
      }
      else if ( is_chachu && !is_chhotu ){
        bool b = (gpar->parent==nullptr);
        rotateLeftRight(curr,parr,gpar);
        if(b){root = curr;}
        updateHeight(parr);
        updateHeight(gpar);
      }
      else if ( !is_chachu && is_chhotu){
        bool b = (gpar->parent==nullptr);
        rotateRightLeft(curr,parr,gpar);
        if(b){root = curr;}
        updateHeight(parr);
        updateHeight(gpar);
      }
      else{
        bool b = (gpar->parent==nullptr);
        rotateRightRight(curr,parr,gpar);
        if(b){root=parr;}
        updateHeight(curr);
        updateHeight(gpar);
      }

      return true;
    }
    //Balancing not required, but tree height change can cause imbalance upwards
    else if (l-r==1 || r-l==1){
      gpar->height = gpar->height+1;
      curr = parr;
      parr = gpar;
      gpar = gpar->parent;
    }
  }
  return true;
}

//Small function to updateheights of all ancestors of the leaf
bool AVLTree::updateHeight(TreeNode* leaf){
  TreeNode *head = leaf;
  while(head!=nullptr){
    int left, right;
    if(head->left!=nullptr){
      left = head->left->height;
    }
    else{
      left = 0;
    }

    if ( head->right!=nullptr){
      right = head->right->height;
    }
    else{
      right = 0;
    }

    if(left>right){
      head->height=1+left;
    }
    else{
      head->height=1+right;
    }
    head = head->parent;
  }
  return true;
}


//Returns price on finding, -1 otherwise
int AVLTree::find(int jrnyCode)
{
  if (root==nullptr){
    return -1;
  }
  TreeNode *temp = new TreeNode(jrnyCode,0);
  TreeNode*x = root;
  while(x!=nullptr){
    if ( AVLLessThan(temp,x) ){
      x = x->left;
    }
    else if (AVLLessThan(x,temp)) {
      x = x->right;
    }
    else{
      return x->get_price();
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


