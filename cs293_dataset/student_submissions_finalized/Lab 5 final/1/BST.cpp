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
  //make the node to be inserted
  TreeNode *to_insert = new TreeNode(jrnyCode, price);
  //if new tree, make this the root.
  if(root == NULL){root = to_insert; return true;}
  TreeNode *curr = root;
  //move according to the code until a nullptr leaf found.
  //update parent child there, return true.
  while(true){
    if(BSTLessThan(to_insert, curr)){
      if(curr->left == NULL){
        updateBSTParentChild(to_insert, curr, true);
        break;
      }
      curr = curr->left;
    }
    else if(BSTLessThan(curr, to_insert)){
      if(curr->right == NULL){
        updateBSTParentChild(to_insert, curr, false);
        break;
      }
      curr = curr->right;
    }
    else return false;
  }
  //to update the heights of the nodes on the path from the new location to the root.
  while(curr != NULL){
    int x = curr->left != NULL ? curr->left->height : -1;
    int y = curr->right != NULL ? curr->right->height : -1;
    curr->height = max(x, y) + 1;
    curr = curr->parent;
  }
  return true;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
  TreeNode *temp = new TreeNode(jrnyCode, 0);
  TreeNode *curr = root;
  //move according to the code, until the code found or a nullptr encountered.
  while(true){
    if(BSTLessThan(temp, curr)) curr = curr->left;
    else if(BSTLessThan(curr, temp)) curr = curr->right;
    else{ 
      delete temp;
      return curr->price;
    }
    if(curr == NULL) break;
  }
  delete temp;
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
  if(find(jrnyCode) < 0) return false;
  TreeNode *temp = new TreeNode(jrnyCode, 0);
  //pair doesn't exist
  TreeNode *node = root;
  //find the node to be removed
  while(true){
      if(BSTLessThan(temp, node)) node = node->left;
      else if(BSTLessThan(node, temp)) node = node->right;
      else break;
  }
  delete temp;
  //updating the heights
  //is a leaf
  //make appropriate parent's child pointer NULL
  if(node->left == NULL && node->right == NULL){
      if(node == root){
          delete root;
          root = NULL; //empty tree now
          return true;
      }
      bool isLeft;
      if(node->parent->left == node) isLeft = true;
      else isLeft = false;
      updateBSTParentChild(NULL, node->parent, isLeft);
      TreeNode *curr = node->parent;
      //update the heights of the above nodes.
      while(curr != NULL){
          int x = curr->left != NULL ? curr->left->height : -1;
          int y = curr->right != NULL ? curr->right->height : -1;
          curr->height = max(x, y) + 1;
          curr = curr->parent;
        }
      delete node;
      return true;
  }
  //if only one of the node's subtrees is non-empty, make its parent point to it.
  //if node is root, set the sub-tree's root as root
  if(node->right == NULL){
    if(node == root){
      root = node->left;
      root->parent = NULL;
      node->left = NULL;
      delete node;
      return true;
    }
    bool isLeft;
    if(node->parent->left == node) isLeft = true;
    else isLeft = false;
    updateBSTParentChild(node->left, node->parent, isLeft);
    TreeNode *curr = node->parent;
    while(curr != NULL){
      int x = curr->left != NULL ? curr->left->height : -1;
      int y = curr->right != NULL ? curr->right->height : -1;
      curr->height = max(x, y) + 1;
      curr = curr->parent;
    }
    delete node;
    return true;
  }
  if(node->left == NULL){
    if(node == root){
      cout << "yay" << endl;
      root = node->right;
      root->parent = NULL;
      node->right = NULL;
      delete node;
      return true;
    }
    bool isLeft;
    if(node->parent->left == node) isLeft = true;
    else isLeft = false;
    updateBSTParentChild(node->right, node->parent, isLeft);
    TreeNode *curr = node->parent;
    while(curr != NULL){
      int x = curr->left != NULL ? curr->left->height : -1;
      int y = curr->right != NULL ? curr->right->height : -1;
      curr->height = max(x, y) + 1;
      curr = curr->parent;
    }
    delete node;
    return true;
  }
  //find the successor, (leftmost of right subtree (non-empty))
  TreeNode *succ = node->right;
  while(succ->left != NULL) succ = succ->left;
  //copy the values of the successor
  int price_succ = succ->price;
  int code_succ = succ->JourneyCode;
  //remove the successor node
  //cases based on if it has a parent (of whom it is a left child)
  //or if it is the right child of the node itself
  TreeNode *curr = succ->parent;
  if(succ->left == NULL && succ->right == NULL){
    if(node->right == succ){
      updateBSTParentChild(NULL, node, false);
    }
    else updateBSTParentChild(NULL, succ->parent, true);
    delete succ;
  }
  else{
    if(node->right == succ){
      updateBSTParentChild(succ->right, node, false);
    }
    else{
      updateBSTParentChild(succ->right, succ->parent, true);
    }
    delete succ;
  }
  while(curr != NULL){
    int x = curr->left != NULL ? curr->left->height : -1;
    int y = curr->right != NULL ? curr->right->height : -1;
    curr->height = max(x, y) + 1;
    curr = curr->parent;
  }
  //a less efficient way to do it
  //remove(code_succ, price_succ);
  //replace node with the successor
  node->price = price_succ;
  node->JourneyCode = code_succ;
  return true;
}


