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
  TreeNode *v = root;
    TreeNode *p = nullptr;
    int flag=0;
    TreeNode *p;
    TreeNode *temp;
    temp=new TreeNode(jrnyCode, price);
    while (v != nullptr)
    {
        flag=1;
            if (BSTLessThan(temp, v))
            {
                p = v;
                v = (v->left);
            }
            else
            {
                p = v;
                v = (v->right);
            }
    }
    v=new TreeNode(jrnyCode, price);
    v->parent=p;
    if(p!=nullptr){
        if(BSTLessThan(temp, p)){
        p->left=v;

        }
        else{
         p->right=v;


    }
    }
    if(flag==0){
        root=v;
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
  return true;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
  TreeNode *v = root;
  TreeNode *p = nullptr;
  TreeNode *temp;
  temp=new TreeNode(jrnyCode,99999);
    while (v != nullptr)
    {
        if (!(BSTLessThan(v,temp)) && !(BSTLessThan(v,root)))
        {
            return v->price;
        }
        else if (BSTLessThan(v,temp))
        {
            p = v;
            if(v->left!=nullptr){
                v = (v->left);
            }
            else{
                return false;
            }
        }
        else
        {
            p = v;
            if(v->right!=nullptr){
                v = (v->right);;
            }
            else{
                return false;
            }

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


