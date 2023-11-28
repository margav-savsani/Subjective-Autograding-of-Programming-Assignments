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
{TreeNode *a = root;
    TreeNode *parent = NULL;
    TreeNode *q = new TreeNode(jrnyCode, price);
    while (a != NULL)
    {
        if (BSTLessThan(a,q))
        {
            parent = a;
            a = (a->right);
        }
        else if (BSTLessThan(q,a))
        {
            parent = a;
            a = (a->left);
        }
        
        else
            return false;
    }

    q->parent = parent;
    if (parent == NULL)
    {  
        this->root = q;
        q->height=0;
      
    }
    else if (BSTLessThan(parent,q))
    {   
        parent->right = q;
    while(parent!=NULL){
        if(parent->left!=NULL&&parent->right!=NULL){
            parent->height=1+max(parent->right->height,parent->left->height);     
        }
        else{
            if(parent->left==NULL){
            parent->height=parent->right->height+1;}
            else{
                parent->height=parent->left->height+1;
            }
        }
        parent=parent->parent;
    }       
    }
    else
    {parent->left = q; 
    while(parent!=NULL){
        if(parent->right!=NULL&&parent->left!=NULL){
        
            parent->height=1+max(parent->right->height,parent->left->height);
             
        }
       
        else{
            if(parent->left==NULL){
            parent->height=parent->right->height+1;}
            else{
                parent->height=parent->left->height+1;
            }
          
        }
        
    parent=parent->parent;
     
    }
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
  
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{TreeNode *find_node = root;
TreeNode *b=new TreeNode(jrnyCode,0);
    while (find_node != NULL)
    {
        if (BSTLessThan(find_node,b))
        {
            find_node = find_node->right;
        }
        else if (BSTLessThan(b,find_node))
        {
            find_node = find_node->left;
        }
        else 
        {
            return 1;
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
  return 0;
}
bool BST::remove(int jrnyCode){
    return true;
}
// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in BST with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the BST have the same journey
// code, and journey code is the key for insertion and finding in the BST.




