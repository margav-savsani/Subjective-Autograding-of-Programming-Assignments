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
  TreeNode* c;
        c=new TreeNode(jrnyCode,price);
        if(find(jrnyCode)!=-1){
           return false;
           }
        else{
         if(root==nullptr){
            root=c;
            return true;
            }
         else{
             TreeNode* d=root;
             TreeNode* e=nullptr;
             while(d!=nullptr){
                e=d;
                if(BSTLessThan(c,d)){
                   d=d->left;
                   }
                 else{
                   d=d->right;
                   }
                }
             if(e==nullptr){
                root=c;
                return true;
                }
       
                else if(BSTLessThan(c,e)){
                    updateBSTParentChild(c,e,true);
                    while(e!=nullptr){
                        height(e);
                        e=e->parent;
                    }
                    return true;
                    }
                else{
                  updateBSTParentChild(c,e,false);
                  while(e!=nullptr){
                    height(e);
                    e=e->parent;
                  }
                  return true;
                  }         
           }
         }
  // Implement insertion in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST
void BST::height(TreeNode*y){
     if(y->left==nullptr && y->right!=nullptr){
        y->height=1+y->right->height;
        return;
     }
     else if(y->right==nullptr && y->left!=nullptr){
        y->height=1+y->left->height;
        return;
     }
     else if(y->right!=nullptr && y->left!=nullptr){
        if(y->right->height>y->left->height){
            y->height=1+y->right->height;
            return;
        }
        else{
            y->height=1+y->left->height;
            return;
        }
     }
}

int BST::find(int jrnyCode)
{
    if(root==nullptr){
       return -1;
       }
     else{
        TreeNode c(jrnyCode,0);
       TreeNode* x=root;
       while(x!=nullptr){
         if(BSTEqual(x,&c)){
           return x->getprice();
           }
         else{
           if(BSTLessThan(&c,x)){
             x=x->left;
             }
           else{
             x=x->right;
             }
           }
         }
       return -1;
      }
  // Implement find in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
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


