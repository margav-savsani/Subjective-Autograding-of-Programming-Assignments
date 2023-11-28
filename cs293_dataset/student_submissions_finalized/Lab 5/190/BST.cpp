#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif









// Returns true on successful insertion in BST. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the BST

bool BST::insert(int JourneyCode, int price)
{
  // Implement insertion in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.


  if(find(JourneyCode)){
      return false;
  }
  if(root == NULL){
      root = new TreeNode();
      root->JourneyCode = JourneyCode;
      root->price = price;
      return true;
  }
  TreeNode *z = new TreeNode();
  z->price = price;
  z->JourneyCode = JourneyCode;

  TreeNode *y = new TreeNode();
  y = NULL;
  TreeNode *x = new TreeNode();
  x = root;

  while(x != NULL){
      y = x;

      // if(z->JourneyCode   <   x->JourneyCode){
      if(BSTLessThan(z, x)){
          x = x->left;
      }
      else{
          x = x->right;
      }
  }

  z->parent = y;
  if(y == NULL){
      root = z;
  }
  // else if(z->JourneyCode < y->JourneyCode){
  else if(BSTLessThan(z,y)){
      y->left = z;
  }
  else{
      y->right = z;
  }
  return true;
}












// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int JourneyCode)
{
  // Implement find in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.

  TreeNode *z = new TreeNode(JourneyCode, 0);

  TreeNode *x = root;

  // while( x != NULL && x->JourneyCode != JourneyCode){
  while( x != NULL && (BSTLessThan(z,x) || BSTLessThan(x,z))){
      // if( JourneyCode   <   x->JourneyCode){
      if(BSTLessThan(z,x)){
          x = x->left;
      }
      else {
          x = x->right;
      }
  }

  if(x == NULL){
      return -1;
  }
  // Fact that you reached here is proof that x is the right match!
  return x->getPrice();  
}








// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in BST with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the BST have the same journey
// code, and journey code is the key for insertion and finding in the BST.

bool BST::remove(int jrnyCode)
{
  // Implement deletion in BST
  
  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // REMEMBER to update the height of appropriate nodes in the tree
  // after a successful deletion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.


  return true;
}










// My Functions

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal == PRE_ORDER){
        preOrderTraverse(root);
    }
    else if(typeOfTraversal == IN_ORDER){
        inOrderTraverse(root);
    }
    else if(typeOfTraversal == POST_ORDER){
        postOrderTraverse(root);
    }
    return;
}

void BST::preOrderTraverse(TreeNode *x){
    if(x == NULL) return;

    cout << x->JourneyCode << endl;
    preOrderTraverse(x->left);
    preOrderTraverse(x->right);

    return;        
    
}
void BST::inOrderTraverse(TreeNode *x){
    if(x == NULL) return;

    preOrderTraverse(x->left);
    cout << x->JourneyCode << endl;
    preOrderTraverse(x->right);

    return;   
}
void BST::postOrderTraverse(TreeNode *x){
    if(x == NULL) return;

    preOrderTraverse(x->left);
    preOrderTraverse(x->right);
    cout << x->JourneyCode << endl;

    return;   
}


// Returns the price of the cheapest journey
int BST::getMinimum() {
    return TreeMinimum(root)->price;    
 
}

TreeNode* BST::TreeSuccessor(TreeNode *x){
    if( x->right != NULL ) {
        TreeMinimum(x->right);
    } 

    TreeNode *y;
    y = x->parent;

    while(  y != NULL    &&    x == y->right ){
        x = y;
        y = y->parent;
    }

    return y;

}

TreeNode* BST::TreeMinimum(TreeNode *x){
    while( x->left != NULL ){
        x = x->left;
    }

    return x;
}







