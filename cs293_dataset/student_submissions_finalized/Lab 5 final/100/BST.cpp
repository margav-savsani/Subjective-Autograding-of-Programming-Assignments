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
  //first created new node with given JourneyCode and price. then searches the position 
  //in tree where it should be added and adds there by making pointers to point appropriatly
  TreeNode *newnode=new TreeNode(jrnyCode,price);
  struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  while (currNode != nullptr) {
    if (BSTLessThan(currNode,newnode)) {
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }
    else if (BSTLessThan(newnode,currNode)) {
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
    else { // currNode->JourneyCode == JourneyCode
      return false;
    }
  }
  
  if(parentOfCurrNode==nullptr)root=newnode;
  else if(BSTLessThan(newnode,parentOfCurrNode))updateBSTParentChild(newnode,parentOfCurrNode,true);
  else updateBSTParentChild(newnode,parentOfCurrNode,false);

  TreeNode* curr=newnode;

  //updating heights of each whose heights can be altered after insertion of new node
  do{
    if(curr==nullptr)break;
    if(curr->left==nullptr && curr->right==nullptr)curr->height=1;
    else if(curr->left==nullptr){
      curr->height=1+curr->right->height;
    }
    else if(curr->right==nullptr){
      curr->height=1+curr->left->height;
      
    }
    else{
      curr->height=1+max(curr->left->height,curr->right->height);
    }
    curr=curr->parent;
  }while(curr!=nullptr);
  return true;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
  //simply iterating over tree to find element in it
  TreeNode* temp=new TreeNode(jrnyCode,0);
  TreeNode *x =root;
    while(x!=NULL){
      if(BSTLessThan(temp,x)) x=x->left;
      else if(BSTLessThan(x,temp))x=x->right;
      else return 1;
    }
  return -1;
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

//updates height of subtree rooted on given node after deleting a node from tree
int updateHeight(TreeNode* node){
  if(node==nullptr)return 0;
  int lheight=updateHeight(node->left);
  int rhieght=updateHeight(node->right);
  node->height=1+max(lheight,rhieght);
  return node->height;
}

// Returns true on successful deletion of the entry in BST with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the BST have the same journey
// code, and journey code is the key for insertion and finding in the BST.
bool BST::remove(int jrnyCode)
{
  //first getting node corresponding to given JourneyCode in tree using getnode function
  //and proceeds further if node is not null else returns false
  TreeNode* z=getNode(jrnyCode);
  if(z==NULL)return false;
  TreeNode* y,*x;
  if(z->left==NULL || z->right==NULL)y=z;
  //finds successor of the node which is going to be deleted
  else y=successor(z);
  if(y->left!=NULL)x=y->left;
  else x=y->right;
  if(x!=NULL)x->parent=y->parent;
  if(y->parent==NULL)root=x;
  else if(y==y->parent->left)y->parent->left=x;
  else y->parent->right=x;
  //copies data from successor node to given node and deletes that node
  if(y!=z){
    z->changeData(y);
  }
  //updating heights after deleting node
  if(root!=nullptr)
    root->height=updateHeight(root);
  return true;
}


