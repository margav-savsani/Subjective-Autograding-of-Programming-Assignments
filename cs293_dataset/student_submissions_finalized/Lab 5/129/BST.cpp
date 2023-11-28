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
int  Calculate_height(TreeNode *x){
    if(x == nullptr){
      return 0;
    }
    else{
      if(x->left == nullptr && x->right == nullptr){
        return 1;
      }
      else if(x->left!=nullptr && x->right == nullptr){
        return Calculate_height(x->left);
      }
      else if(x->left==nullptr && x->right != nullptr){
        return Calculate_height(x->right);
      }
      else{
        return max(Calculate_height(x->left), Calculate_height(x->right));
      }
    }
  }
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
  TreeNode *res = new TreeNode(0,0);
    TreeNode *y = nullptr;

    if (root == nullptr) // inserting at root
    {
        root = new TreeNode(jrnyCode, price);

        return true;
    }

    else
    {

        TreeNode *x = root;
        /*if (check(JourneyCode, price, x)) // if a journey code is present , insertion failed
        {
            return false;
        }*/
        TreeNode *n1= new TreeNode(jrnyCode,price);
        while (x != nullptr) // if prices are same insert at right
        {

            if (BSTLessThan(x,n1))
            {
                y = x;
                x = x->right;
            }
            else 
            {
                y = x;
                x = x->left;
            }
        }
        if (BSTLessThan(n1,y))
        {
            res->parent = y;
            y->left = res;
            res->JourneyCode = jrnyCode;
            res->price = price;
            
            
        }
        else
        {
            res->parent = y;
            y->right = res;
            res->JourneyCode = jrnyCode;
            res->price = price;
        }
        
    }
           Calculate_height(root);
    //return true;
  
  return true;
}

// Return True, if the ticket with given attributes is found, false otherwise


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
  TreeNode *x = root;
  TreeNode* garb=new TreeNode(jrnyCode,0);

    while (x != nullptr)
    {

        if (!(BSTLessThan(x,garb) && !BSTLessThan(garb,x)))
        {
            return jrnyCode;
        }
        if (BSTLessThan(garb,x))
        {
            x = x->left;
        }
        else
        {
            x = x->right;
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


