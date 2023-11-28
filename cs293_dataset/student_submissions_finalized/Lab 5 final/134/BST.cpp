#ifndef BST_H
#include "BST.h"
#include "Tree.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

void BST::updateHeightBST(TreeNode* currNode)
{
  if(currNode==NULL) return;
  TreeNode* parNode=currNode->parent;
  if(parNode!=NULL){
    int lChHeight=-1, rChHeight=-1; // These are bydefault values incase the node is(are) null ptrs
    if(parNode->left!=0) lChHeight=parNode->left->height;
    if(parNode->right!=0) rChHeight=parNode->right->height;
    if(parNode->height==max(lChHeight, rChHeight)+1){
      return; //i.e. isleft or isright but its change doesn't change the height to its parent 
    }
    else{
      parNode->height ++ ; //otherwise increment the height of parent
      updateHeightBST(parNode); //and do the same for its parent
    }
  }
  return;
}

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
  TreeNode* insertNode = new TreeNode(JourneyCode, price);
  TreeNode* varParent = NULL;
  TreeNode* varCurrent = root;
  while(varCurrent != NULL){
      //int x = varCurrent->getJourneyCode();
        if( BSTLessThan (varCurrent, insertNode)){
            varParent = varCurrent;
            varCurrent = varCurrent->right;
            //std::cout << "y";
        }
        else if( BSTLessThan (insertNode, varCurrent)){
                varParent = varCurrent;
                varCurrent = varCurrent->left;
              //  std::cout << "x";
        }
        else{
            return false;
        }
    }

    if(varParent == NULL){
        root = insertNode;
        root->height = 0;
        return true;
    }

    if(BSTLessThan(varParent, insertNode)){
      updateBSTParentChild(insertNode, varParent, false);
        //varParent->right = new TreeNode(JourneyCode, price, NULL, NULL, varParent);
        //varCurrent = varParent->right;
    }
    else{
      updateBSTParentChild(insertNode, varParent, true);
        //varParent->left = new TreeNode(JourneyCode, price, NULL, NULL, varParent);
        //varCurrent = varParent->left;
    }
    insertNode->height=0;
    updateHeightBST(insertNode); //updates recursively
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
    TreeNode* reqNode = new TreeNode(jrnyCode, 0); //0 is some rand journey code
    TreeNode* var = root;
    while(var != NULL){
        if(BSTLessThan(var, reqNode))
            var = var->right;
        else if(BSTLessThan(reqNode, var))
            var = var->left;
        else
          return var->getPrice();
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


