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
  TreeNode *to_ins = new TreeNode(jrnyCode,price);
 
  if(N==0){
    updateBSTParentChild(to_ins,nullptr,true);
    root = to_ins;
    N=1;
  }

  else{
    TreeNode *x,*y;
    x=root;
    y=nullptr;
    while(x!=nullptr){
      y=x;
      if(BSTLessThan(to_ins,x)==true){
        x=x->left;
      }
      else if(BSTLessThan(x,to_ins)){
        x=x->right;
      }
      else{
        return false;
      }
    }

    if(BSTLessThan(to_ins,y)){
      updateBSTParentChild(to_ins,y,true);
    }
    else{
      updateBSTParentChild(to_ins,y,false);
    }
    //updating heights after insertion
    y->update_heights();
  }

  return true;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
  TreeNode *to_find = new TreeNode(jrnyCode,0);
  TreeNode *x=root;
  while(x!=nullptr){
    if(BSTLessThan(to_find,x)){
      x = x->left;
    }
    else if(BSTLessThan(x,to_find)){
      x = x->right;
    }
    else{
      return x->getprice();
    }
  }
  
  return -1;
}

bool BST::remove(int jrnyCode)
{
  return true;
}


