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
  // Implement insertion in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.

  //new tree
  if (root == nullptr)
  {
    root = new TreeNode(jrnyCode, price);
    return true;
  }

  else{
    TreeNode* ins_node = new TreeNode(jrnyCode, price);  //node to be inserted
    TreeNode * Root= root; //node which will traverse in the tree to find the correct spot for ins_node
    
    while(true){
      if((BSTLessThan(Root,ins_node))==true){
        if(Root->right==nullptr){
          updateBSTParentChild(ins_node,Root,false);
          break;
        }
        else{
          Root = Root->right;
          continue;
        }
      }
      else if((BSTLessThan(ins_node,Root))==true){
        if(Root->left==nullptr){
          updateBSTParentChild(ins_node,Root,true);
        }
        else{
          Root = Root->left;
          continue;
        }
      }
      else{
        break;
      }
    }
  traverseUp(ins_node);  //insert normally then upadte the values of heights with the function traverseUp
  return true;
  }
}

//this function by taking in the inserted node as parameter moves up the tree and updates the heights of all nodes
//which came in its path while entering from root and had caused the increase
void BST::traverseUp(TreeNode* node)
{
  if(node==nullptr){
    return;
  }
  TreeNode* node_traversing = node;
  while(true){
    if(node_traversing->parent==nullptr){  //equivalent to it bring the root of the tree
      break;
    }
    else{
      if(node_traversing->parent->left==node_traversing){
        if((node_traversing->parent->right==nullptr)||(node_traversing->parent->right->height < node_traversing->parent->left->height)){
          node_traversing->parent->height++;
          node_traversing=node_traversing->parent;
          continue;
        }
        else{
          break;
        }
      }
      else if(node_traversing->parent->right==node_traversing){
        if((node_traversing->parent->left==nullptr)||(node_traversing->parent->left->height < node_traversing->parent->right->height)){
          node_traversing->parent->height++;
          node_traversing=node_traversing->parent;
          continue;
        }
        else{
          break;
        }
      }
    }
  }
  return;
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

  if(root == nullptr){
    return -1;
  }

  TreeNode * find_node = new TreeNode(jrnyCode,-1);
  TreeNode * Root = root; 
  while (true)
  {
    if((BSTLessThan(Root,find_node))==true){
      if(Root->right == nullptr)
      {
        return -1;
      }
      else{
        Root = Root->right;
        continue;
      }
    }
    else if((BSTLessThan(find_node,Root))==true){
      if(Root->left == nullptr){
        return -1;
      }
      else{
        Root = Root->left;
        continue;
      }
    }
    else{  //since we don not have a equal to function so i first checked less than then greater than and if both were false then both are equal
      return Root->giveNodePrice();
    }
  }
  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
  //return -1;
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




