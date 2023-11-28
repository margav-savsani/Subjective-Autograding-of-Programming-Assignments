#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

// AKSHAT SINGH
// ROLL NO. 2100020013
// LAB 5
// Returns true on successful insertion in BST. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the BST

bool BST::insert(int jrnyCode, int price)
{
  TreeNode *v = root;
    TreeNode *p = nullptr;
    int flag=0;
    TreeNode *temp;
    temp=new TreeNode(jrnyCode, price);         // CREATING A NODE FOR COMPARISION
    while (v != nullptr)
    {
        flag=1;
            if (BSTLessThan(temp, v)) // IF TEMP NODE LESS THAN COMPARISION NODE, COMPARE WITH LEFT CHILD OF COMP NODE
            {
                p = v;
                v = (v->left);
            }
            else
            {
                p = v; // COMPARE WITH RIGHT CHILD
               
                v = (v->right);
                
            }
    }
    v=new TreeNode(jrnyCode, price);
    if(p!=nullptr){
        if(BSTLessThan(v, p)){               // IF PARENT IS GREATER THEN MAKE IT THE LEFT CHILD OF PARENT
          updateBSTParentChild(v, p, true);
            
        }
        else{

         updateBSTParentChild(v, p, false);
        }
    }
    if(flag==0){
        root=v;
    }

    v->height=0;      // ASSIGNING THE HEIGHT OF LEAF AS ZERO
    while(v!= nullptr){
      if(v->parent!=nullptr){
        if(v->parent->left!=nullptr && v->parent->right!=nullptr){        // IF BOTH CHILD ARE NOT NULL POINTERS, WE WE TAKE MAX HEIGHT +1
          v->parent->height=(max(v->parent->left->height,v->parent->right->height)+1);
          v=v->parent;
        }
        else if(v->parent->left!=nullptr){                 // IF ONE IS NULL, TAKE THE OTHER HEIGHT +1
          v->parent->height=(v->parent->left->height+1);
          v=v->parent;
        }
        else{
          v->parent->height=(v->parent->right->height+1);
          v=v->parent;
        }
      }
      else{
        break;
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
  return true;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
  TreeNode *v = root;
  TreeNode *temp;
  temp=new TreeNode(jrnyCode,99999);                  // MAKING A TEMP NODE
    while (v != nullptr)
    {
        if (!(BSTLessThan(v,temp)) && !(BSTLessThan(temp,v)))     // IF TEMP IS NEITHER >V NOR <V THEN IT IS EQUAL
        {
            return v->getprice();
        }
        else if (BSTLessThan(temp,v))           // IF LESS THAN V, WE TAKE LEFT CHILD
        {
            if(v->left!=nullptr){
                v = (v->left);
            }
            else{
                return -1;
            }
        }
        else
        {
            if(v->right!=nullptr){
                v = (v->right);;
            }
            else{
                return -1;
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


