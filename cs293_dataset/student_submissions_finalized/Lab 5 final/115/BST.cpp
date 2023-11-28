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
  TreeNode* a=new TreeNode(jrnyCode,price);
    if(root==NULL)// if root is initially null, then adding directly at the root
    {
        root= a;
    }
    TreeNode* A=root;
    TreeNode* B=new TreeNode(0,0);
    B->JourneyCode=jrnyCode;
    B->price=price;
    B->left=NULL;
    B->right=NULL;
    while(true)//finding the place for element and then adding there
    {
        if(BSTLessThan(a,A))//if price is less than root, go to right and add there
        {
            if(A->left==NULL)//if left is null, just add there
            {
            B->parent=A;
            A->left=B;
            return true;  
            }
            A=A->left;
            continue;
        }
        else if(BSTLessThan(A,a))//if price is more than root, go to left amd add there
        {
            if(A->right==NULL)//if right is null, just add there
            {
            B->parent=A;
            A->right=B;
            return true;  
            }
            A=A->right;
            continue;
        }
        else
        {
                return false;
        }
    }
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
    TreeNode* dum=new TreeNode(jrnyCode,0);
    TreeNode* A=root;
    while(true)
    {
        if(A==NULL)// if root of the subtree is null then return false
        {
            return -1;
        }
        if(BSTLessThan(dum,A))//changing the point of view of root
        {
            A=A->left;
            continue;
        }
        else if(BSTLessThan(A,dum))
        {//moving to the right subtree
            A=A->right;
            continue;
        }
        else
        {
          return A->price;
        }
    }
  return -1;
}

  // Implement find in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.

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


