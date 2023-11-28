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

bool BST::insert(int JourneyCode, int price)
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
  
  TreeNode* tempch = new TreeNode(JourneyCode, price);   //node that is going to be inserted
  if(root != NULL){              
      TreeNode* trav = root;
      while(true){    //traverse the tree iteratively to insert
        if(BSTEqualTo(trav, tempch)){    //if element is already present, reject insertion
          return false;
        }
        else if(BSTLessThan(tempch, trav)){       //insert in the left subtree
          if(trav->left == nullptr){
            updateBSTParentChild(tempch, trav, true);     //create a parent child relation between the nodes
            tempch->updateParents();    //update the heights of the ancestors
            break;    
          }
          else{
            trav = trav->left;
          }
        }
        else{
          if(trav->right == nullptr){
            updateBSTParentChild(tempch, trav, false);     //create a parent child relation between the nodes
            tempch->updateParents();             //update the heights of the ancestors
            break;
          }
          else{
            trav = trav->right;
          }
        }
      }
  }
  else{    //if root is NULL, insert the root element and set its parent to NULL
      root = tempch;        
      root->parent = NULL;
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

  if(root != nullptr){      //traverse the tree iteratively to find
    TreeNode* tempch = new TreeNode(jrnyCode, 0);
    TreeNode* trav = root;
    while(true){
      if(trav == nullptr){     //nothing to find, break
        return -1;
      }
      if(BSTEqualTo(tempch, trav)){     //element found
        return trav->getPrice();
      }
      else if(BSTLessThan(tempch, trav)){    //check in the left subtree
        trav = trav->left;
      }
      else{    //check in the right subtree
        trav = trav->right;
      }
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


