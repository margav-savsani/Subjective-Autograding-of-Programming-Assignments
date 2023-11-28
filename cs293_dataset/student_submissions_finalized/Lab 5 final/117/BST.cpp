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
  if(root== NULL){// if empty tree
        root = new TreeNode(jrnyCode, price);
        return true;
    }

  else bool ans = insertRecursive(jrnyCode, price, root);// called a recursive function

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
  return true;
}

// same element is inserted in the 
bool BST::insertRecursive(int JourneyCode, int price, TreeNode* myroot){
    TreeNode* insert = new TreeNode(JourneyCode,price);// to use the given BSTlessthan function
    if(!BSTLessThan(myroot,insert) && !BSTLessThan(insert,myroot)){// if same journey code present, returns false
        
        delete(insert);
        return false;
    }
    else if(BSTLessThan(insert,myroot)){// is price of insert is less, node inserted in left subtree
        if(myroot->left == NULL){
            updateBSTParentChild(myroot, insert, true);
            updateHeight(insert);
            return true;
        }
        else return insertRecursive(JourneyCode, price, myroot->left);
    }
    else {// if price of given insert is greater then or equal to the price at a node, the new node will be inserted in the right tree. Note: node with same price is inserted in the right tree
        if(myroot->right == NULL){// if right is null, insert the node
            updateBSTParentChild(myroot, insert, false);
            updateHeight(insert);
            return true;
        }
        else return insertRecursive(JourneyCode, price, myroot->right);// else call recursively
    }
}

void BST::updateHeight(TreeNode* mynode){
  bool heightUpdated = 1 ;
  while(mynode->parent != NULL || !heightUpdated){
    mynode = mynode->parent;
    if(mynode->left == NULL || mynode->right == NULL){
      mynode->height + 1;
    } 
    else{
      int newheight = max(mynode->right->height,mynode->left->height)+1;
      if(newheight == mynode->height){
        heightUpdated = 0;
      }
    }  
  }

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


