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

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.

  TreeNode *present = NULL;  //declare a null TreeNode
  TreeNode *search = root;   //root of the tree
   // TreeNode *given;           //node for the given values
   // given->JourneyCode = JourneyCode;  //assign passed journeycode and price to "given" treenode
    //given->price = price;

  TreeNode *given = new TreeNode(jrnyCode,price);
     
    while(search != NULL){   // while root of the tree is not null, repeat the loop. finally "search" will give the correct insertion position for the "given" node.
        present = search;    // stores parent of "search" in "present"
        if(given < search){     //if price of root is greater than the given price
            search = search->left;            //go to the left subtree
        }
        else{                                 //if price of root is less than the given price
            search = search->right;           //go to the right subtree
        }
    }

    given->parent = present;    // make "present" the parent node of the given node. 

    if(present == NULL){   //if "present" is still NULL means our root of the tree was NULL
        root = given;      //store the "given" node into root.
        return true;       // insertion complete
    }
    else if(given < present){   //if "present" is not NULL and given price is less than the parent's price
        present->left = given;                // the "given" node will be left node of the parent.
        return true;                          // inserton complete
    }
    else if(present < given){    //else the "given" node will be right node of the parent.
        present->right = given;               
        return true;    
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

   TreeNode *current_root = root;  //store root in TreeNode "current_root"
   TreeNode *now = new TreeNode(jrnyCode, 1);

    while(current_root!=NULL && current_root->getJourneyCode()!=jrnyCode){ //loop till current_root does not contain the given data
        if(current_root < now){
            current_root =  current_root->right;  //if given price is greater than price in current_root, store pointer of current_root->right into current_root 
        }
        else{
            current_root =  current_root->left;  // else store pointer of current_root->left into current_root
        }
    }
    if(current_root==NULL) return -1;  // after looping if current_root is again NULL, then ticket not present and return false

    else if(current_root->getJourneyCode()==jrnyCode){  // else ticket is present and return true
        return current_root->getPrice();
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


