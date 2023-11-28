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
int BST::getHeight(TreeNode* x) {
  if(x->left==nullptr&&x->right==nullptr) return 0;
  else if (x->left==nullptr&&x->right!=nullptr)
  {
    x->height= x->right->height+1;
    return x->height;
  }
  else if(x->left!=nullptr&&x->right==nullptr){
    x->height=x->left->height+1;
    return x->height;
  }
  else{
    x->height= max(getHeight(x->left),getHeight(x->right))+1;
    return x->height;
  }
}
bool BST::Insert(int jrnyCode, int price, TreeNode* x){
  if(x==nullptr) {
    x->JourneyCode=jrnyCode;
    x->price=price;
    x->height=0;
  }
  TreeNode *t;
  t->JourneyCode=jrnyCode;
  t->price=price;
  if(!(BSTLessThan(t,x))&&!(BSTLessThan(x,t))) {
    return false;
  }
  else if(BSTLessThan(t,x)) {
            if(x->left==nullptr) {
                x->left->JourneyCode=jrnyCode;
                x->left->price=price;
                x->left->left=nullptr;
                x->left->right=nullptr;
                x->left->parent=x;
                x->left->height=0;
                x->height=getHeight(x);
                return true;
            }
            else{

              BST leftTree(x->left,1,1);
              
              return leftTree.Insert(jrnyCode,price,x->left);
            }
   }
    else  {
            if(x->right==nullptr) {
                x->right->JourneyCode=jrnyCode;
                x->right->price=price;
                x->right->right=nullptr;
                x->right->left=nullptr;
                x->right->parent=x;
                x->right->height=0;
                x->height=getHeight(x);
                return true;
                }
                else{
                   BST rightTree(x->right,1,1);
                   
                   return rightTree.Insert(jrnyCode,price,x->right);
        }
    }


}
bool BST::insert(int jrnyCode, int price)
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

  return Insert(jrnyCode,price,root);
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST
int BST::Find( int jrnyCode,TreeNode *x) {
  if(x==nullptr) return -1;
    TreeNode *t;
    t->JourneyCode=jrnyCode;
    t->price=0;
    if(!(BSTLessThan(t,x))&&!(BSTLessThan(x,t))){
      return x->price;
    }
    else if (BSTLessThan(x,t))
    {
    
      BST rightBST(x->right,1,1);
      
      return rightBST.Find(jrnyCode,x->right);
      
    }
    else{
      
      BST leftBST(x->left,1,1);
      
      return leftBST.Find(jrnyCode,x->left);
    }
}
int BST::find(int jrnyCode)
{
  // Implement find in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
  return Find(jrnyCode,root);
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


