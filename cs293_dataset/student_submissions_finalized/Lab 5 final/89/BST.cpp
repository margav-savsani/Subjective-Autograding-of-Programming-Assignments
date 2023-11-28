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

  TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  TreeNode *Node=new TreeNode(jrnyCode,price);
  
  while (currNode != nullptr) {
  
       if (BSTLessThan(currNode, Node)) {
          parentOfCurrNode = currNode;
          currNode = currNode->right;
         }
    
       else if (BSTLessThan(Node, currNode)) {
           parentOfCurrNode = currNode;
           currNode = currNode->left;
         }
    
       else {     // currNode->JourneyCode == JourneyCode
          return false;
         }  
    }
     Node->parent=parentOfCurrNode;
     TreeNode* y; 
     
     if(parentOfCurrNode==NULL)
        {
           root=Node;
           y=root;
          }
     else if (BSTLessThan(Node, parentOfCurrNode))
         {
           parentOfCurrNode->left=Node;
           y=parentOfCurrNode->left;
           }
     else 
       {
          parentOfCurrNode->right=Node;
          y=parentOfCurrNode->right;
        }   
    
     while(y->parent != NULL && (y->parent)->height < 1+y->height)
       {
         (y->parent)->height=y->height+1;
          y=y->parent;
        }   
 
   return true;   
   
}

  // Implement insertion in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.


// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
      
     TreeNode *Node=new TreeNode(jrnyCode, 10);
        TreeNode* X=root; 
        while(true){
        if(X==NULL) return -1;
        else if((X->getJourneyCode()==jrnyCode)) return X->getprice();
        else
           { 
              if(BSTLessThan(Node, X)) X=X->left;  
              else X=X->right;
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


