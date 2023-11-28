#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif


// Returns true on successful insertion in BST. Returns false otherwise.

bool BST::insert(int jrnyCode, int price)
{

  if(find(jrnyCode)!=-1) return false;

  TreeNode* node= new TreeNode(jrnyCode,price);

  if(root==nullptr) root= node;
  else{
    TreeNode* curr=root;

    //inserts the new node
    while(true){
      if(BSTLessThan(node,curr)){
        if(curr->left!=nullptr) curr=curr->left;
        else{
          updateBSTParentChild(node,curr,true);
          break;
        }
      }
      else{
        if(curr->right!=nullptr) curr=curr->right;
        else{
          updateBSTParentChild(node,curr,false);
          break;
        }
      }
    }

    //updates the height of all nodes which lie on the path from new inserted node to root
    while(true){
      if(curr==nullptr) break;
      else{
        if(curr->left==nullptr) curr->height=curr->right->height+1;
        else if(curr->right==nullptr) curr->height=curr->left->height+1;
        else curr->height=1+max(curr->left->height,curr->right->height);
        curr=curr->parent;
      }
    }
  }

  return true;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.

int BST::find(int jrnyCode)
{ 
  if(root==nullptr) return -1;
  // Implement find in BST
  TreeNode* node=new TreeNode(jrnyCode,1);
  TreeNode* curr=root;
  while(true){
    if(!BSTLessThan(node,curr) && !BSTLessThan(curr,node)) return curr->getPrice();
    else if(BSTLessThan(node,curr)){
      if(curr->left==nullptr) break;
      else curr=curr->left;
    }
    else{
      if(curr->right==nullptr) break;
      else curr=curr->right;
    }
  }
  
  return -1;
}


bool BST::remove(int jrnyCode)
{

  return true;
}


