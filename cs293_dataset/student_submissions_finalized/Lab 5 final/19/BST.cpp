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
int BST::maxDepth(TreeNode* a){
  if (a == NULL)
        return -1;
    else
    {
        /* compute the depth of each subtree */
        int lDepth = maxDepth(a->left);
        int rDepth = maxDepth(a->right);
     
        /* use the larger one */
        if (lDepth > rDepth)
            return(lDepth + 1);
        else return(rDepth + 1);
    }
}
bool BST::insert(int jrnyCode, int price)
{
  // Implement insertion in BST
  if (find(jrnyCode) != -1){
        return false;
  }
  TreeNode* temp;
  TreeNode* current = root;

  TreeNode* add = new TreeNode(jrnyCode, price);
  if(root == nullptr){
    root = add;
    return true;
  }
  while(current != nullptr){
    temp = current;
    if(BSTLessThan(add, current)){
      current = current->left;
    }
    else{
      current = current->right;
    }
  }
  add->parent = temp;
  if(BSTLessThan(add, temp)){
    //temp->left = add;
    updateBSTParentChild(add, temp, true);
    TreeNode* node = temp->left;
    while(node != nullptr){
      node->height = maxDepth(node);
      node = node->parent;
    }
  }
  else{
    //temp->right = add;
    updateBSTParentChild(add, temp, true);
    TreeNode* node = temp->right;
    while(node != nullptr){
      node->height = maxDepth(node);
      node = node->parent;
    }
  }
  return true;

}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode){
  TreeNode* x;
  TreeNode* y;
  x = root;
  y = new TreeNode(jrnyCode, 0);
  while (x != NULL && x->getjourney() != y->getjourney()){
    if(BSTLessThan(y, x)){     //add in case   || y->getjourney() == x->getjourney()
      x = x->left;
    }
    else{
      x = x->right;
    }
  }
  if(x == NULL){
    return -1;
  }
  else{
    return x->getprice();
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


