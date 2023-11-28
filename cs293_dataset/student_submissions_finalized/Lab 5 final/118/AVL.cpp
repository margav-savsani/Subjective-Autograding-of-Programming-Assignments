#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

bool AVLTree::height_up(TreeNode* curr){
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

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  //To check whether the grandparent is a left or right child
  if(greatGrandParentNode == nullptr){
    root=parentNode;
    root->parent=nullptr;
  }
  else if (greatGrandParentNode->left == grandParentNode) {
    //To link the parent and the greatgrandparent
    updateAVLParentChild(parentNode, greatGrandParentNode, true);
  }
  else {
    //To link the parent and the greatgrandparent
    updateAVLParentChild(parentNode, greatGrandParentNode, false);
  }
  //To store the right child of parent
  TreeNode *T3 = parentNode->right;
  //To link the parent and the grandparent
  updateAVLParentChild(grandParentNode, parentNode, false);
  //To link the right child of parent and grandparent
  updateAVLParentChild(T3, grandParentNode, true);

  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  //To check whether the grandparent is a left or right child
  if(greatGrandParentNode == nullptr){
    root = currNode;
    root->parent=nullptr;
  }
  else if (greatGrandParentNode->left == grandParentNode) {
    updateAVLParentChild(currNode, greatGrandParentNode, true);
  }
  else {
    updateAVLParentChild(currNode, greatGrandParentNode, false);
  }

  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;

  updateAVLParentChild(parentNode, currNode, true);
  updateAVLParentChild(grandParentNode, currNode, false);
  updateAVLParentChild(T2, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  //To check whether the grandparent is a left or right child
  if(greatGrandParentNode == nullptr){
    root = currNode;
    root->parent=nullptr;
  }
  else if (greatGrandParentNode->left == grandParentNode) {
    updateAVLParentChild(currNode, greatGrandParentNode, true);
  }
  else {
    updateAVLParentChild(currNode, greatGrandParentNode, false);
  }

  TreeNode *T2 = currNode->right;
  TreeNode *T3 = currNode->left;

  updateAVLParentChild(parentNode, currNode, false);
  updateAVLParentChild(grandParentNode, currNode, true);
  updateAVLParentChild(T2, parentNode, true);
  updateAVLParentChild(T3, grandParentNode, false);

  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  //To check whether the grandparent is a left or right child
  if(greatGrandParentNode == nullptr){
    root=parentNode;
    root->parent=nullptr;
  }
  else if (greatGrandParentNode->left == grandParentNode) {
    //To link the parent and the greatgrandparent
    updateAVLParentChild(parentNode, greatGrandParentNode, true);
  }
  else{
    //To link the parent and the greatgrandparent
    updateAVLParentChild(parentNode, greatGrandParentNode, false);
  }
  //To store the left child of parent
  TreeNode *T3 = parentNode->left;
  //To link the parent and the grandparent
  updateAVLParentChild(grandParentNode, parentNode, true);
  //To link the left child of parent and the grandparent
  updateAVLParentChild(T3, grandParentNode, false);

  return true;
}

void AVLTree::AVLheightAdd(int h, TreeNode* curr, TreeNode* parentNode){
  bool imb=true;
  TreeNode *currNode;
  while(imb){
    if(curr==nullptr || curr->height>h)
      imb=false;
    else{
      if(imbalance(curr)<2){
        h++;
        curr->height=h;
        currNode=parentNode;
        parentNode=curr;
        curr=curr->parent;
      }
      else{
        imb=false;
        if(AVLLessThan(parentNode,curr)){
          if(AVLLessThan(currNode,parentNode)){
            rotateLeftLeft(currNode,parentNode,curr);
            height_up(curr);
            height_up(parentNode);
          }
          else{
            rotateLeftRight(currNode,parentNode,curr);
            height_up(curr);
            height_up(parentNode);
            height_up(currNode);
          }
        }
        else{
          if(AVLLessThan(currNode,parentNode)){
            rotateRightLeft(currNode,parentNode,curr);
            height_up(curr);
            height_up(parentNode);
            height_up(currNode);
          }
          else{
            rotateRightRight(currNode,parentNode,curr);
            height_up(curr);
            height_up(parentNode);
          }
        }
      }
    }
  }
}

bool AVLTree::insert(int jrnyCode, int price){
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
    if(AVLLessThan(newN,curr)){
      if(curr->left==nullptr){
        curr->left=newN;
        curr->left->parent=curr;
        AVLheightAdd(0, curr, curr->left);
        return true;
      }
      curr=curr->left;
    }
    else if(AVLLessThan(curr,newN)){
      if(curr->right==nullptr){
        curr->right=newN;
        curr->right->parent=curr;
        AVLheightAdd(0, curr, curr->right);
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

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode){
  TreeNode *curr=root;
  //whike loop to find the entry with the given journeycode
  //If such a entry is found, the price is returned
  TreeNode* newN= new TreeNode(jrnyCode,0);
  while(curr!=nullptr){
    if(!AVLLessThan(curr,newN) && !AVLLessThan(newN,curr)){
      return curr->price_return();
    }
    else if(AVLLessThan(newN,curr))
      curr=curr->left;
    else
      curr=curr->right;
  }
  return -1; 
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in AVL tree with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the AVL tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

void AVLTree::recHeight(TreeNode* curr){
  if(curr==nullptr){
    return;
  }
  else if(height_up(curr) || imbalance(curr)>1){if(curr==curr) cout<<curr->price_return()<<" "<<imbalance(curr)<<endl;
    if(imbalance(curr)>1){
      if(curr->left!=nullptr && curr->left->height+1==curr->height){
        if(curr->left->left!=nullptr && curr->left->left->height+2==curr->height){
          rotateLeftLeft(curr->left->left,curr->left,curr);
          height_up(curr);
          height_up(curr->parent);
        }
        else{
          rotateLeftRight(curr->left->right,curr->left,curr);
          height_up(curr);
          height_up(curr->parent->left);
          height_up(curr->parent);
        }
      }
      else{
        if(curr->right->right!=nullptr && curr->right->right->height+2==curr->height){
          rotateRightRight(curr->right->right,curr->right,curr);
          height_up(curr);
          height_up(curr->parent);
        }
        else{
          rotateRightLeft(curr->right->left,curr->right,curr);
          height_up(curr);
          height_up(curr->parent->right);
          height_up(curr->parent);
        }
      }
      recHeight(curr->parent->parent);
    }
    else
      recHeight(curr->parent);
  }
}

void AVLTree::delete_node(TreeNode *node){
  TreeNode **parent_ptr; //To store the pointer to the varaible which stores the address of the node we want to delete
  //Checks whether the node to be deleted is the root
  //If true, creates a temporary parent to the root and calls the function again
  if(node->parent==nullptr){
    TreeNode *root_parent, *root_child;
    root_parent=new TreeNode(root->JourneyCode_return()-1,0);
    root_child=new TreeNode(root->JourneyCode_return()-2,0);
    root_parent->right=root;
    root_parent->left=root_child;
    root_child->height=root->height;
    root->parent=root_parent;
    delete_node(root);
    root=root_parent->right;
    if(root!=nullptr)
      root->parent=nullptr;
    delete root_parent;
    delete root_child;
    return;
  }
  //To find the pointer to the variable which stores the address of the node we want to delete
  if(AVLLessThan(node->parent,node)) 
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
bool AVLTree::remove(int JourneyCode) { 
  TreeNode *curr=root;
  TreeNode *temp=new TreeNode(JourneyCode,1);
  //while loop to find the node to be deleted
  //After finding the node, it calls delete_node() to delete it
  while(curr!=nullptr){
    if(AVLLessThan(temp,curr)){
      curr=curr->left;
    }
    else if(AVLLessThan(curr,temp)){
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