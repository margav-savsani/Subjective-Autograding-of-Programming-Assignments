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
void height_reset_ins2(TreeNode* To_be_ins ){
    while(To_be_ins!=NULL){
      if(To_be_ins->right!=NULL && To_be_ins->left!=NULL){
        if((To_be_ins->right)->height < (To_be_ins->left)->height )
          To_be_ins->height = (To_be_ins->left)->height +1;
        else  
          To_be_ins->height = (To_be_ins->right)->height +1;
      }

      else if(To_be_ins->right!=NULL || To_be_ins->left!=NULL){
        if(To_be_ins->right!=NULL){
          To_be_ins->height = (To_be_ins->right)->height +1;

        }
       else{
          To_be_ins->height = (To_be_ins->left)->height +1;

        }
      }
      else{

        To_be_ins->height = 0;
      }
      To_be_ins=To_be_ins->parent;
     
    }
    return;
}

bool BST::insert(int jrnyCode, int price)
{
    if(root==NULL){
        root=new TreeNode(jrnyCode,price);

        return true;
    }
    TreeNode* To_be_ins=new TreeNode(jrnyCode,price);
    class TreeNode *currNode = root, *parentOfCurrNode = NULL;
    while (currNode != NULL) {
        if (BSTLessThan(To_be_ins,currNode)) {
        parentOfCurrNode = currNode;
        currNode = currNode->right;
        }
        else if (BSTLessThan(currNode,To_be_ins )) {
        parentOfCurrNode = currNode;
        currNode = currNode->left;
        }
        else { 
        return false;
        }
    }
    

    To_be_ins->parent=parentOfCurrNode;
    if(BSTLessThan(parentOfCurrNode,To_be_ins ))
        updateBSTParentChild( To_be_ins,parentOfCurrNode,false);
    else  
        updateBSTParentChild( To_be_ins,parentOfCurrNode,true);
  height_reset_ins2(To_be_ins);


    

  // Implement insertion in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
  return true;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int JourneyCode)
{
  class TreeNode *currNode = root,*req=new TreeNode(JourneyCode,69);
  if(root==NULL){
    
    return -1;
  }
  while (currNode != NULL) {
    if (BSTLessThan(currNode,req)) {
    
      currNode = currNode->right;
    }
    else if (BSTLessThan(req ,currNode)) {
      
      currNode = currNode->left;
    }
    else { // currNode->JourneyCode == JourneyCode
      return 1;
    }
    
  }
  // Implement find in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

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


