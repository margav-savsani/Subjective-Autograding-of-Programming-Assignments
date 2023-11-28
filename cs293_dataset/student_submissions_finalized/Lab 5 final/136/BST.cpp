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
  TreeNode* z=new TreeNode(jrnyCode,price);
  if(root==nullptr){
      root=z;
      return true;
  }
  TreeNode* x=root;
  bool left=false;
  while (x!=nullptr){
    if(z==x){
        return false;
    }
    if(BSTLessThan(z,x)){
        if(x->left==nullptr){
            left=true;
            break;
        }
        x=x->left;
    }
    else{
        if(x->right==nullptr){
            break;
        }
        x=x->right;
    }
  }
  if(left){
      x->left=z;
      z->parent=x;
  }
  else{
      x->right=z;
      z->parent=x;
  }
  if(BSTLessThan(x,z)){
      x->right=z;
      z->parent=x;
  }
  else{
      x->left=z;
      z->parent=x;
  }
  //solving imbalances
  while(true)
  {
    if(z->parent==nullptr){
      break;
    }
    int height=z->height;
    if(height+1<=z->parent->height){
      break;
    }
    z->parent->height++;
    z=z->parent;
  }
  return true;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
  // Implement find in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.
  TreeNode* x;
  TreeNode* z=new TreeNode(jrnyCode,9999);
  x=root;
  while (x != nullptr){
    int a=x->compare(jrnyCode);
    if(a!=-1){
        return a;
    }
    else if (BSTLessThan(z,x)){
        x = x->left;
    }
    else{
        x=x->right;
    }
  } 
  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
  return -1;
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
  TreeNode* z;
  z=root;
  TreeNode* temp=new TreeNode(jrnyCode,999);
  TreeNode* par;
  while (z != nullptr){
      if(jrnyCode == z->getjrny()){
          break;
      }
      if (BSTLessThan(temp,z)){
          z = z->left;
      }
      else{
          z=z->right;
      }
  }
  if(z==nullptr){
      return false;
  }
  par=z->parent;
  if((z->left == nullptr)&&( z->right == nullptr)){
      if(z->parent->left==z){
          z->parent->left=nullptr;
      }
      else if(z->parent->right==z){
          z->parent->right=nullptr;
      }
  }
  else if(z->left == nullptr){
      if(z->parent->left==z){
          z->parent->left=z->right;
          z->right->parent=z->parent;
      }
      else{
          z->parent->right=z->right;
          z->right->parent=z->parent;
      }
  }
  else if( z->right == nullptr){
      if(z->parent->left==z){
          z->parent->left=z->left;
          z->left->parent=z->parent;
      }
      else{
          z->parent->right=z->left;
          z->left->parent=z->parent;
      }
  }
  else{
      TreeNode* y;
      y = TreeSuccessor(z);
      par=y->parent;
      z->setprice(y->getprice());
      z->setjrny(y->getjrny());
      if((y->left == nullptr)&&( y->right == nullptr)){
            if(y->parent->left==y){
                y->parent->left=nullptr;
            }
            else if(y->parent->right==y){
                y->parent->right=nullptr;
            }
        }
    else if(y->left == nullptr){
        if(y->parent->left==y){
            y->parent->left=y->right;
            y->right->parent=y->parent;
        }
        else{
            y->parent->right=y->right;
            y->right->parent=y->parent;
        }
    }
    else if( y->right == nullptr){
        if(y->parent->left==y){
            y->parent->left=y->left;
            y->left->parent=y->parent;
        }
        else{
            y->parent->right=y->left;
            y->left->parent=y->parent;

        }
    }
  }
  if((par->left==nullptr)&&(par->right==nullptr)){
    par->height--;
  }
  while(true)
  {
    if(par->parent==nullptr){
      break;
    }
    int height=par->height;
    if(height+1>=par->parent->height){
      break;
    }
    par->parent->height--;
    par=par->parent;
  }
  return true;
}