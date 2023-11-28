//Assuming that the journey codes entered aren't unique
#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

void BST::heightAdd(int h, TreeNode* curr){
  if (curr==nullptr){
    return;
  }
  else if(curr->height<h+1){
    curr->height=h+1;
    heightAdd(curr->height, curr->parent);
  }
}

bool BST::height_up(TreeNode* curr){
  int h=-1;
  if(curr->left!=nullptr)
    h=curr->left->height;
  if(curr->right!=nullptr && curr->right->height>h)
    h=curr->right->height;
  h++;
  if(h!=curr->height){
    curr->height=h;
    return true;
  }
  else
    return false;
}

void BST::recHeight(TreeNode* curr){
  if(curr==nullptr){
    return;
  }
  else if(height_up(curr)){
    recHeight(curr->parent);
  }
}

// Returns true on successful insertion in BST. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the BST

bool BST::insert(int jrnyCode, int price){
  //To check if the root is a nullptr
  if(root==nullptr){
    root=new TreeNode(jrnyCode, price);
    root->parent=nullptr;
    return true;
  } 
  TreeNode *curr=root;
  TreeNode *newN=new TreeNode(jrnyCode, price);
  //while loop to find the location of insertion
  while(true){
    if(BSTLessThan(newN,curr)){
      if(curr->left==nullptr){
        curr->left=newN;
        curr->left->parent=curr;
        heightAdd(0, curr);
        return true;
      }
      curr=curr->left;
    }
    else if(BSTLessThan(curr,newN)){
      if(curr->right==nullptr){
        curr->right=newN;
        curr->right->parent=curr;
        heightAdd(0, curr);
        return true;
      }
      curr=curr->right;
    }
    else{
      delete newN;
      return false;
    }
  }
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode){
  TreeNode *curr=root;
  //whike loop to find the entry with the given journeycode
  //If such a entry is found, the price is returned
  TreeNode* newN= new TreeNode(jrnyCode,0);
  while(curr!=nullptr){
    if(!BSTLessThan(curr,newN) && !BSTLessThan(newN,curr)){
      return curr->price_return();
    }
    else if(BSTLessThan(newN,curr))
      curr=curr->left;
    else
      curr=curr->right;
  }
  return -1; 
}

void BST::delete_node(TreeNode *node){
  TreeNode **parent_ptr; //To store the pointer to the varaible which stores the address of the node we want to delete
  //Checks whether the node to be deleted is the root
  //If true, creates a temporary parent to the root and calls the function again
  if(node->parent==nullptr){
    TreeNode *root_parent;
    root_parent=new TreeNode(root->JourneyCode_return()-1,0);
    root_parent->right=root;
    root->parent=root_parent;
    delete_node(root);
    root=root_parent->right;
    if(root!=nullptr)
      root->parent=nullptr;
    delete root_parent;
    return;
  }
  //To find the pointer to the variable which stores the address of the node we weant to delete
  if(BSTLessThan(node->parent,node)) 
    parent_ptr=&(node->parent->right);
  else
    parent_ptr=&(node->parent->left);
  //Deletes the node directly as it has no children
  if(node->left==nullptr && node->right==nullptr){
    *parent_ptr=nullptr;
    recHeight(node->parent);
    delete node;
  }
  //Deletes the node and puts its left child in its position
  else if(node->right==nullptr){
    *parent_ptr=node->left;
    node->left->parent=node->parent;
    recHeight(node->parent);
    delete node;
  }
  //Deletes the node and puts its right child in its position
  else if(node->left==nullptr){
    *parent_ptr=node->right;
    node->right->parent=node->parent;
    recHeight(node->parent);
    delete node;
  }
  //Deletes the node, find the node in its left subtree with the maximum JC and then putis it in its position
  else{
    TreeNode *curr=node->left;
    //Checks whether the root of the left subtree is the node with the maximum JC
    if(curr->right==nullptr){
      curr->right=node->right;
      if(node->right!=nullptr)
        node->right->parent=curr;
      curr->parent=node->parent;
      *parent_ptr=curr;
      recHeight(curr);
      delete node;
    }
    else{
      curr=curr->right;
      while(curr->right!=nullptr)
        curr=curr->right;
      *parent_ptr=curr;
      TreeNode* temp=curr->parent;
      curr->parent->right=curr->left;
      if(curr->left!=nullptr)
        curr->left->parent=curr->parent;
      curr->parent=node->parent;
      curr->right=node->right;
      node->right->parent=curr;
      curr->left=node->left;
      node->left->parent=curr;
      recHeight(temp);
      delete node;
    }
  }
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode) { 
  TreeNode *curr=root;
  TreeNode *temp=new TreeNode(JourneyCode,1);
  //while loop to find the node to be deleted
  //After finding the node, it calls delete_node() to delete it
  while(curr!=nullptr){
    if(BSTLessThan(temp,curr)){
      curr=curr->left;
    }
    else if(BSTLessThan(curr,temp)){
      curr=curr->right;
    }
    else{
      delete_node(curr);
      delete temp;
      return true;
    }
  }
  delete temp;
  return false; 
}