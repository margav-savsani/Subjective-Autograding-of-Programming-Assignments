#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

void BST::updateheights(TreeNode* node){
  while(node != NULL){
    if(node->left == NULL || node->right == NULL){                     // if either of the child is NULL, then height will                                                                       
      node->height++;                                                  // increase for sure
      node = node->parent;                                             // change node to it's parent
    }
    else{
      if(node->height == 1+max(node->left->height,node->right->height)) break;  //if the height doesn't change; break
      else{
        node->height++;                                                         //else incease the height
        node = node->parent;                                                    //change the node 
      } 
    }
  }
  return;
}

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
  TreeNode* new_node = new TreeNode(jrnyCode,price);    // node which is to be inserted 
  TreeNode* finder=NULL;                                // used to locate the parent of the node to be inserted 
  TreeNode* traveller = root;                           // used in finding the position and comparing with the new_node
  bool left;
  while(traveller != NULL){
    finder=traveller;
    if(BSTequalto(new_node,finder)) break;              // If the node is already present; break the loop.
    if(BSTLessThan(new_node, traveller)){
      traveller=traveller->left;
      left = 1;
    } else{
      traveller=traveller->right;
      left = 0;
    }    
  }
  if(traveller != NULL){                                 // traveller is NULL, return false
    return false;
  }
  if(finder == NULL){                                     // if finder is NULL, it means root is NULL; so new_node becomes root
    root=new_node;    
  } else if(left){                                       
    updateBSTParentChild(new_node,finder,1);             // update parent child
    if(finder->height == 0) {                            // if finder is a leaf; finder height changs to 1           
      updateheights(finder);                             // update the remaining ancestors of finder
    }                               
  } else{
    updateBSTParentChild(new_node,finder,0);
    if(finder->height == 0) {      
      updateheights(finder);
    }
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

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
  TreeNode* curr_node=new TreeNode(jrnyCode,0);              
  TreeNode* temp=root;
  while(temp != NULL){
    if(BSTequalto(curr_node,temp)){                                     //checks whther the nodes are equal or not
      return 0;
    } else if(BSTLessThan(curr_node,temp)){                              //standard process
      temp = temp->left;
    } else{
      temp = temp->right;
    }
  }
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


