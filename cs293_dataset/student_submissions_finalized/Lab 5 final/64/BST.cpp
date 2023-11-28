#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif


// int BST::updateheight(TreeNode* node){
//   if(node==nullptr){
//     return 0;
//   }
//   if(node->left==nullptr && node->right==nullptr){
//     node->height=0;
//     return 0;
//   }
//   if(node->left==nullptr && node->right!=nullptr){
//     node->height = 1 + updateheight(node->right);
//   }
//   if(node->right==nullptr && node->left!=nullptr){
//     node->height = 1 + updateheight(node->left);
//   }
//   if(node->left!= nullptr && node->right!=nullptr){
//     node->height = 1 + max(updateheight(node->left), updateheight(node->right));
//   }
//   return node->height;
// }

void BST::updateheight(TreeNode* node){
  if(node==nullptr){
    return;
  }
  if(node->left==nullptr && node->right==nullptr){
    node->height=0;
  }else{
    if(node->left==nullptr){
      node->height=1+node->right->height;
    }else if(node->right==nullptr){
      node->height=1+node->left->height;
    }else if(node->left!=nullptr && node->right!=nullptr){
      node->height = 1+max(node->left->height, node->right->height);
    }
  }
  updateheight(node->parent);
}


// Returns true on successful insertion in BST. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the BST

bool BST::insert(int jrnyCode, int price)
{
  // Implement insertion in BST

  // You MUST use only BSTLessThan to compare two journey codes. You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  TreeNode* node_insert = new TreeNode(jrnyCode, price);
  if(find(jrnyCode)!=-1){
    return false;
  }
  TreeNode* y = nullptr;
  TreeNode* x= root;
  while(x!=nullptr){
    y=x;
    if(BSTLessThan(node_insert, x)){
      x=x->left;
    }else if(BSTLessThan(x,node_insert)){
      x=x->right;
    }else{
      return false;
    }
  }
  if(y==nullptr){
    root=node_insert;
    return true;
  }else if(BSTLessThan(y,node_insert)){
    updateBSTParentChild(node_insert, y, 0);
    updateheight(node_insert);
    return true;
  }else if(BSTLessThan(node_insert,y)){
    updateBSTParentChild(node_insert, y, 1);
    cout<<"hello"<<endl;
    updateheight(node_insert);
    return true;
  }else{
    return false;
  }

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
{
  // Implement find in BST
  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.
  TreeNode* x = new TreeNode(jrnyCode, -1);
  TreeNode* node = root;
  while(node!=nullptr && ( BSTLessThan(x,node) || BSTLessThan(node, x) )){
    if(BSTLessThan(node, x)){
      node=node->right;
    }else if(BSTLessThan(x, node)){
      node=node->left;
    }
  }
  
  if(node==nullptr){
    return -1;
  }else if( !(BSTLessThan(x,node)) && !(BSTLessThan(node,x))){
    return node->getprice();
  }else{
    return -1;
  }
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


