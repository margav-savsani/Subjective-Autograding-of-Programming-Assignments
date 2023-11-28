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


//********

//Increase height:
// This will take a treenode as an argument and checks the height of the 
//children, and takes the value of the highest height added with 1 as its height.

//********
void BST::increaseheightBST(TreeNode *node){
  
  if(node->right==NULL){
    node->height=node->left->height+1;
  }
  else if(node->left==NULL){
    node->height=node->right->height+1;
  }
  else if(node->right->height>=node->left->height){
    node->height=node->right->height +1 ;
  }
  else if(node->right->height<node->left->height){
    node->height=node->left->height +1 ;
  }
  
  if(node->parent != NULL){
    increaseheightBST(node->parent);
  }
}

bool BST::insert(int jrnyCode, int price)
{
  if( find(jrnyCode)!= -1){
            return false;
    }
         TreeNode *A=new TreeNode(jrnyCode,price);

         TreeNode *y=NULL;
         TreeNode *x=root;

         while(x!=NULL){
            y=x;
            if(BSTLessThan(A,x)){
                x=x->left;

            }
            else x=x->right;
         }
        
        if(y==NULL){
            root=A;
            root->parent=y;
            root->height=1;
        }
        else if(BSTLessThan(A,y)){
          y->left=A;
          y->left->updateParentChild(y,true);
          y->left->height=1;  
          increaseheightBST(y);    
         }
        else {
          y->right=A;
          y->right->updateParentChild(y,false);
          y->right->height=1;
          increaseheightBST(y);
        }
    return true;
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

int BST::find(int jrnyCode)
{
  TreeNode *A=new TreeNode(jrnyCode,0);
     TreeNode *x;
     x=root;
     while(x!=NULL && A->getJourneyCode()!=x->getJourneyCode()){
        if(BSTLessThan(A,x)){
            x=x->left;
        }
        else {x=x->right;}
     }
     if(x==NULL){
        return -1;
     }
     else {return x->getprice();}
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


