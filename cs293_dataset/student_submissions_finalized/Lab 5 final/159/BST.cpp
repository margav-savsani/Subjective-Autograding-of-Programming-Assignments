#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif


// Returns true on successful insertion in \BST. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the BST

bool BST::insert(int jrnyCode, int price)
{ TreeNode* z=new TreeNode(jrnyCode,price);
  if(root == nullptr){
        root = z;
        updateheight(root);
        return true;
    }
    if(find(jrnyCode)!= -1){
      return false;}
      else{
    TreeNode *x = root;
    while(true){
        if(BSTLessThan(z,x)){
            if(x->left!=nullptr){
                x = x->left;
        }else{
                updateBSTParentChild(z,x,true);
                updateheight(root);
                break;    
            }
        }else{
            if(x->right!=nullptr){
                x = x->right;
            }else{
                updateBSTParentChild(z,x,false);
                updateheight(root);
                break;               
            }
        }
    }}
    return true;
  // Implement insertion in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the xent node in the tree that you
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

int BST::find(int jrnyCode)
{ TreeNode* z =new TreeNode(jrnyCode,0); 
  if(root==nullptr)return -1;
    TreeNode* x = root;
    while(true){     
        if(BSTGreaterThan(x,z)){     
            if(x->left==nullptr){
                return -1;
            }else{
                x = x->left;
            }
        }else if(BSTLessThan(x,z)){
            if(x->right==nullptr){
               return -1;
            }else{
                x = x->right;
            }
        }
        else{
            return x->getprice();
        }
    }
  // Implement find in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // xent node in the tree that you are inspecting and the new node
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


