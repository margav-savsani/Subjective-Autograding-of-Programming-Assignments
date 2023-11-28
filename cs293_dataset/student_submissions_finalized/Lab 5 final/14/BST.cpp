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

void BST::updateheight(TreeNode* node)
{
  TreeNode* t = node->parent;
  while(t!=NULL)
  {
    t->height = max(height(t->left),height(t->right)) + 1;
    t = t->parent;
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
  
  TreeNode* newnode = new TreeNode(jrnyCode,price);
  TreeNode* r = root;
  TreeNode* n = NULL;
  bool done=false; 

  // if root is empty before the new node will tself become the root
  if(root == NULL)
  {
      //cout << "insert at root\n";
      root = newnode;
      root->parent = NULL;
      updateBSTParentChild(root,NULL,true);
      updateheight(newnode);
      return true;
  }

  //travel till a place is found to insert
  while(r!=NULL && !done)
  {
      n=r;
      if(BSTLessThan(newnode,r)) r=r->left;
      else r=r->right;
  }

  if(BSTLessThan(newnode,n) && !done)
  {
      n->left = newnode;
      updateBSTParentChild(newnode,r,true);
      updateheight(newnode);
      done=true;
  }

  else if(!done)
  {
      n->right=newnode;
      updateBSTParentChild(newnode,n,false);
      updateheight(newnode);
      done=true;
  }

  return done;
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

  TreeNode* needed=new TreeNode(jrnyCode,7); //kept the price randomly as 5
  TreeNode* r = root;
  int price;

  //if tree is empty
  if(root == NULL) return -1;

  while(true)
  {
    if(r==NULL) return -1;

    if(r->getjrnycode()==jrnyCode) return 7;
    
    //travel till it finds
    if(BSTLessThan(r,needed)) r=r->right;
    else if(BSTLessThan(needed,r)) r=r->left;
  }

  return price;
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


