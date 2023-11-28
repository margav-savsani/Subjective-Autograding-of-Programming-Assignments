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

TreeNode* BST::find_tree(TreeNode* x,int JourneyCode) {
        TreeNode* tmp =new TreeNode(JourneyCode,1); // 1 is arbitarty price value
        
        if(x == NULL) {
            return NULL;
        }
        bool x_lt = BSTLessThan(x,tmp); // using less_than function to satisfy our needs 
        bool x_gt = BSTLessThan(tmp,x); 
        if(!x_lt && !x_gt) { // == is !> and !<
            return x;
        }
        if(x_gt) {
            return find_tree(x->left,JourneyCode); // recursive search in left tree
        }
        else {
            return find_tree(x->right,JourneyCode); // recursive search in right tree
        }
        return NULL;
}

int BST::find(int jrnyCode)
{
  if(find_tree(root,jrnyCode)==NULL) return 0; // if we dont find a node with the required Journeycode.
  return 1;
}

bool BST::insert(int jrnyCode, int price)
{
    TreeNode *x,*y,*z;
    y=NULL;
    x=root; // A pointer pointed to root node.
    z=new TreeNode(jrnyCode,price); // Creating a new node with given parameters
    while(x!=NULL) {
      y=x;
      if(BSTLessThan(z,x)){
        x= x->left;
      }
      else x= x->right;
    }
      z->parent = y;
      if(y==NULL) {
        root=z;  // Insertion of first node into the tree
        return true;
      }
      else {
        if(BSTLessThan(z,y)) y->left=z;
        else y->right = z;
      }

        bool isleft = BSTLessThan(z,y);
        updateBSTParentChild(z,y,isleft); 
        z->height=0; // intialising to 0
        while(z->parent!=NULL) {
          bool is_left = BSTLessThan(z,z->parent); // checking the status of the z wrto parent
          if(is_left) {
            if((z->parent)->right!=NULL) {
               ((z->parent)->height) = max(((z->parent)->right)->height,((z->parent)->left)->height)+1; // it is obvious that this is one more than the child height
            }
            else {
              (z->parent)->height = 1+ (z->parent->left)->height; // if right child is NULL
            }
          }
          if(!is_left) {
            if((z->parent)->left!=NULL) {
               ((z->parent)->height) = max(((z->parent)->right)->height,((z->parent)->left)->height)+1;
            }
            else {
              (z->parent)->height = 1+ (z->parent->right)->height; // if left child is NULL
            }
          }         
          z = z->parent; // moving up the tree 
        }
  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
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


