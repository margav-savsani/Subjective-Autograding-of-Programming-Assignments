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
    TreeNode* x = root;
    TreeNode* y = nullptr;
    TreeNode* temp = new TreeNode(jrnyCode, price);

    // when tree is empty, new element added is the root itself
    if(root == nullptr){
        root = temp;
        return true;
    }


    // in any other case
    while(true){
        if(x == nullptr){
            x = new TreeNode(jrnyCode, price);
            updateBSTParentChild(x, y, *x < *y);

            TreeNode* p = x;
            while(y != nullptr){
              if(y->left == nullptr || y->right == nullptr){
                y->height = p->height + 1;
              }
              else{
                y->height = max(p->height + 1, y->height);
              }

              p = y;
              y = p->parent;
            }
            return true;
        
        } else {
            if(*x < *temp){
                y = x;
                x = x->right;   // moves right, if element has greater price than current node
            } else if (*temp < *x){
                y = x;
                x = x->left;    // moves left, if element has smaller price than current node
            } else {
            return false;   // returns false when same journey code
            }
        }
    }
    


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
  
  TreeNode *x = root;
  TreeNode *temp = new TreeNode(jrnyCode, -1);

    while(true){
        if(x == nullptr){
            return -1;   // returns false if no element is found  
        } else {
            if(BSTLessThan(x, temp)){
                x = x->right;
            } else if(BSTLessThan(temp, x)){
                x = x->left;
            } else {
              return 1;
            }
        }
    }

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


