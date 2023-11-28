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
  TreeNode nodeInsert(jrnyCode,price);
  nodeInsert.height=0;

  //if tree is empty, root is inserted
  if(!root){
    root=new TreeNode(nodeInsert);
    updateBSTParentChild(root,nullptr,true);
    return true;
  }

  TreeNode* parentIns=nullptr;
  TreeNode* temp=root;

  //finding the place to insert the node
  while(temp){
    parentIns=temp;
    if(BSTLessThan(&nodeInsert,temp)){
        temp=temp->left;
    }
    else{
        temp=temp->right;
    }
  }

  //decciding whether it is a left or right child
  if (BSTLessThan(parentIns,&nodeInsert)){
    temp=new TreeNode(nodeInsert);
    updateBSTParentChild(temp,parentIns,false);
  }
  else{
    temp=new TreeNode(nodeInsert);
    updateBSTParentChild(temp,parentIns,true);
  }

  // The insert is done, now we update the heights

  while(parentIns){
    int lheight,rheight;
    if(!parentIns->left){
      lheight=-1;
    }
    else{
      lheight=parentIns->left->height;
    }
    if(!parentIns->right){
      rheight=-1;
    }
    else{
      rheight=parentIns->right->height;
    }

    if(lheight>rheight){
      parentIns->height=lheight+1;
    }
    else{
      parentIns->height=rheight+1;
    }
    parentIns=parentIns->parent;
  }
  return true;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
  TreeNode* match=new TreeNode(jrnyCode,0);

  if(!root){
    return -1;
  }
  
  if(!(BSTLessThan(match,root)) && !(BSTLessThan(root,match))){
    return 1;
  }

  TreeNode* temp=root;
  int found;
  if(BSTLessThan(root,match)){
    root=root->right;
    found=find(jrnyCode);
  }
  else{
    root=root->left;
    found=find(jrnyCode);
  }
  root=temp;
  return found;
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


