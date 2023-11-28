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
int BST::getheight(TreeNode *currnode){
   if(currnode == nullptr){
     return -1 ;
   }
   if((currnode->left==nullptr)&&(currnode->right==nullptr)){
    return 0 ;
   }
   
   int left_height = getheight(currnode->left);
   int right_height = getheight(currnode->right);

   if(currnode->left != nullptr){
    (currnode->left)->height = left_height ;
   }
   if(currnode->right != nullptr){
    (currnode->right)->height = right_height ;
   }
    return (1+max(left_height,right_height));
   
}

bool BST::insert(int jrnyCode, int price)
{  
   TreeNode* a;
   a = new TreeNode(jrnyCode,price);
   TreeNode* c;
   TreeNode* b;
   b = nullptr;
   c = root ;
  while(c != nullptr){
      b = c;
      if(BSTLessThan(a,c)){
        c = c->left ;
      }
      else if(BSTLessThan(c,a)){
        c = c->right ;
      }
      else{
        return false ;
      }
    }
    a->parent = b ;
    if(b == nullptr){
      root = a; 
    }
    else if(BSTLessThan(a,b)) {
      updateBSTParentChild(a,b,true);
      root->height = getheight(root);
    }
    else if(BSTLessThan(b,a)){
      updateBSTParentChild(a,b,false);
      root->height = getheight(root);
    }
  return true ; 


  // Implement insertion in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
 //  return true; commented !!*/
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{  
  
    TreeNode* d ;
    d = root ;
    TreeNode* e ;
    e = new TreeNode(jrnyCode,0);
    while( d != nullptr &&  (BSTLessThan(d,e) || BSTLessThan(e,d)) ){
       if(BSTLessThan(e,d)){
         d = d->left ;
       }
       else if(BSTLessThan(d,e)){ d = d->right ;}
    }
    if(d == nullptr){return -1 ;}
    else return 1 ;
    
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



