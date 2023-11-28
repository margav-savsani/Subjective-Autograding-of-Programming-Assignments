#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

// Recall from Prof. Naveen Garg's lectures how the various rotations are
// applied to restore the balance factor at all nodes of an AVL tree
// to either 0, 1 or -1, after an insert or delete.
// The correspondence between the terminology in Prof. Garg's lectures and
// our terminology in this code is as follows:
//
// Prof. Garg's lectures           Our code
// ---------------------           --------
//   x                             currNode
//   y                             parentNode
//   z                             grandParentNode
//
// Recall also that z (grandParentNode) is the lowest node in the path from
// the root to the inserted node or to the deleted node (as the case may be)
// where the balance factor has either become < -1 or > 1.
// To find what x (currNode) and y (parentNode) should be, you need to
// recall Prof. Garg's lectures.
// These are slightly differently defined when inserting nodes and when
// deleting nodes

// rotation left-left
bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  if(grandParentNode!=root){
    TreeNode *greatGrandParentNode = grandParentNode->parent;
    bool isGPLeftChild;
    if (greatGrandParentNode->left == grandParentNode) {
      isGPLeftChild = true;
    }
    else if (greatGrandParentNode->right == grandParentNode) {
      isGPLeftChild = false;
    }
    else {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }
    updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  }
  else {root=parentNode;}  
  TreeNode *T3 = parentNode->right;
  updateAVLParentChild(grandParentNode, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);
  return true;
}

// rotation left-right
bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  if(grandParentNode!=root){
    TreeNode *greatGrandParentNode = grandParentNode->parent;
    bool isGPLeftChild;
    if (greatGrandParentNode->left == grandParentNode) {
      isGPLeftChild = true;
    }
    else if (greatGrandParentNode->right == grandParentNode) {
      isGPLeftChild = false;
    }
    else {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }
    updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  }  
  else{root=currNode;}
  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;
  updateAVLParentChild(parentNode, currNode, true);
  updateAVLParentChild(grandParentNode, currNode, false);
  updateAVLParentChild(T2, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);
  return true;
}

// rotation right-left 
// implemented similar to rotateLeftRight just mirror image of it
bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Implement this yourself
  if(grandParent!=root){
    TreeNode *greatGrandParentNode = grandParent->parent;
    bool isGPLeftChild;
    if (greatGrandParentNode->left == grandParent) {
      isGPLeftChild = true;
    }
    else if (greatGrandParentNode->right == grandParent) {
      isGPLeftChild = false;
    }
    else {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }
    updateAVLParentChild(currNode,greatGrandParentNode,isGPLeftChild);
  }
  else{root=currNode;}
  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;
  updateAVLParentChild(grandParent,currNode,true);
  updateAVLParentChild(parent,currNode,false);
  updateAVLParentChild(T2,grandParent,false);
  updateAVLParentChild(T3,parent,true);  
  return true;
}

// rotation right-right
// implemented similar to rotateLeftLeft just mirror image of it
bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Implement this yourself
  if(grandParent!=root){
    TreeNode *greatGrandParentNode = grandParent->parent;
    bool isGPLeftChild;
    if (greatGrandParentNode->left == grandParent) {
      isGPLeftChild = true;
    }
    else if (greatGrandParentNode->right == grandParent) {
      isGPLeftChild = false;
    }
    else {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }
    updateAVLParentChild(parent,greatGrandParentNode,isGPLeftChild);
  }
  else{root = parent;}
  TreeNode *T3 = parent->left;
  updateAVLParentChild(grandParent,parent,true);
  updateAVLParentChild(T3,grandParent,false);
  return true;
}

// insert function
bool AVLTree::insert(int jrnyCode, int price)
{
    if(root==NULL){// intial condition
        root = new TreeNode(jrnyCode,price);
        return true;        
    }
    TreeNode *x = root;    
    TreeNode *y = x;
    TreeNode *z = new TreeNode(jrnyCode,price);
    while(x!=nullptr){ 
        if(x->jrCode()==z->jrCode())return false;
        if(AVLLessThan(x,z)){
            y=x;
            if(y->right==nullptr){
                x = z;
                updateAVLParentChild(x,y,false);
                break;
            }           
            x=y->right;                    
        }
        else{
            y=x;
            if(y->left==nullptr){
                x = z;
                updateAVLParentChild(x,y,true);
                break;
            } 
            x=y->left;            
        }
    }
    if((y->parent)!=NULL){
      TreeNode *grandParent = y->parent;
      while(grandParent->balance()){
        if(grandParent==root)break;
        x=y;
        y=grandParent;         
        grandParent=y->parent;
      }
      if(!(grandParent->balance())){
        if((grandParent->left==y)&&(y->left==x)) rotateLeftLeft(x,y,grandParent);
        else if((grandParent->left==y)&&(y->left!=x)) rotateLeftRight(x,y,grandParent);
        else if((grandParent->left!=y)&&(y->left==x)) rotateRightLeft(x,y,grandParent);
        else rotateRightRight(x,y,grandParent);
      }
    }  
    return true;
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.
int AVLTree::find(int jrnyCode)
{
  TreeNode *x = root;  
  TreeNode *y = x;
  TreeNode *z = new TreeNode(jrnyCode,0);
  while((!(x->jrCode()==z->jrCode()))&&(x!=NULL)){
        if(AVLLessThan(x,z)){
            y=x;
            if(y->right==NULL)break;
            x=y->right;           
        }
        else{
            y=x;
            if(y->left==NULL)break;
            x=y->left;            
        }
  }
  if(x->jrCode()==z->jrCode())return z->pri();
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
TreeNode* AVLTree :: successor(TreeNode x){ // to find successor which is required while deleting an element
    if(x.right!=NULL){
        TreeNode *z = x.right;
        TreeNode *k = z;
        while(true){
            k=z;
            if(k->left == nullptr) break;
            z=k->left;
        }
        return k; 
    }
    TreeNode *y = x.parent;
    while((y!=NULL)&&(x.jrCode()==(y->right)->jrCode())){
        x=*y;
        y=y->parent;
    }   
    return y;
}

bool AVLTree::remove(int jrnyCode)
{
  if(find(jrnyCode)<0)return false; 
    TreeNode *x = root;
    TreeNode *y = x;// later y is used to store the address of parent of x
    TreeNode *z = new TreeNode(jrnyCode,0);
    if(root->setheight(root)==0){
      root=NULL;
      return true;
    }
    while(!(x->jrCode()==jrnyCode)&&(x!=NULL)){// goes to position of deleting node
        if(AVLLessThan(x,z)){
            y=x;
            x=y->right;            
        }
        else{
            y=x;
            x=x->left;            
        }
    }
    if((x->left==NULL)&&(x->right==NULL)){// case of having no children
        if(y->right==x)y->right=NULL;
        else y->left=NULL;
    }
    if((x->left==NULL)&&(x->right!=NULL)){// case of having one child
        if(y->right==x)y->right=x->right;
        else if(y->left==x)y->left=x->right;
        else {
          root=x->right;
          y=root;
        } 
    }
    if((x->left!=NULL)&&(x->right==NULL)){// case of having one child
        if(y->right==x)y->right=x->left;
        else if(y->left==x) y->left=x->left;
        else {
          root=x->left;
          y=root;
        }  
    }
    if((x->left!=NULL)&&(x->right!=NULL)){// case of having two children
        TreeNode *z = successor(*x);
        remove(z->jrCode());
        if(y->right==x)y->right=z;
        else if(y->left==x) y->left=z;
        else {
          root=z;
          y=root;
        }  
        z->parent = x->parent;
        z->left = x->left;
        z->right = x->right;
    }    
  return true;
}


