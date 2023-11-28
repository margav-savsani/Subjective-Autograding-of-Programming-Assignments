#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

int BST::height( TreeNode*node){
if(node == NULL)
return 0;
else if((node->left==NULL)&&(node->right==NULL)){
  return 0;}
else return ((max(height(node->left),height(node->right))) + 1);
}

void BST:: update(TreeNode*t){
  TreeNode*x;
  TreeNode*y;
  t->height = height(t);
  x=t->left;
  y=t->right;
  if(x!=NULL)
  {update(x);}
  if(y!=NULL){
  update(y);}

}

// Returns true on successful insertion in BST. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the BST
bool BST::insert(int jrnyCode, int price){
   if(find(jrnyCode)==1) return false;

   TreeNode *z;
    if (root==NULL){
        
       z=new TreeNode(jrnyCode,price);
       root=z;
        return true;

    }
    
    TreeNode *x = new TreeNode(jrnyCode,price);
    TreeNode *y;
    TreeNode *t =root;
    
     while(t!=NULL){
    
 if(BSTLessThan(x, t)){
        y=t;
        t=t->left;}
    else if(BSTLessThan(t,x)){
        y=t ;
        t=t->right;}
        else{return false;}
    }
     if(BSTLessThan(x, y)) y->left = x;
    else y->right =  x;
    update(root);
    return true;


  
  // Implement insertion in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
 
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST


int BST::find2(TreeNode*root,int jrnyCode){
    if(root==NULL){return -1;}
    TreeNode*t=root;
    TreeNode*x=new TreeNode(jrnyCode,1);
    if(BSTLessThan(x,t))return find2(t->left,jrnyCode);
    if(BSTLessThan(t,x))return find2(t->right,jrnyCode);
    if((!BSTLessThan(x, t))&&(!BSTLessThan(t,x))) return  t->getprice();;
    
       return t->getprice(); ; }
      

int BST::find(int jrnyCode)
{
  return find2(root,jrnyCode);
  
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
{/*
   TreeNode* curr = root;
    bool last = false;
     TreeNode*x=new TreeNode(jrnyCode,1);
    // finding the  node to be deleted
    while(true){
        curr->sizeOfTree--; // Decrement size of subtree for each parent node!
        if((!BSTLessThan(x, curr))&&(!BSTLessThan(curr,x))){
            break;
        }else if(BSTLessThan(x,curr)){
            curr = curr->left;
            last = true;
        }else{
            curr = curr->right;
            last = false;
        }
    }
    // If it has no left child, just replace the node with its right child!
    if(curr->left==NULL){
    
        if(curr->parent!=NULL){
            if(last){
                curr->parent->left = curr->right;
            }else{
                curr->parent->right = curr->right;
            }
            if(curr->right!=NULL){
                curr->right->parent = curr->parent;
            }
            delete curr;
        }else{
            root = curr->right;
            delete curr;  
        }
    }else if(curr->right==NULL){
        //   If it has no right child, just replace it with left child
        if(curr->parent!=NULL){
            if(last){
                curr->parent->left = curr->left;
            }else{
                curr->parent->right = curr->left;
            }
            curr->left->parent = curr->parent;
            
            delete curr;
        }else{
            root = curr->left;
            delete curr;     
        }
    }else{
        // If its has both left and right children

        TreeNode *todel = curr; // Marking the node which is to be deleted
        
        // Find its predecessor
        curr = curr->left;
        last = false;
        
        
        while(curr->right!=NULL){
            
            curr->sizeOfTree--;
            curr = curr->right;
            last = true;
        }
          todel = curr ; 
        // Swap the node with its predecessor
        // todel->JourneyCode = curr->JourneyCode;
        // todel->price = curr->price;
        if(!last){
            curr->parent->left = curr->left;
        }else{
            curr->parent->right = curr->left;
        }
        if(curr->left!=NULL)curr->left->parent = curr->parent;
        
        // Delete the node which previously represented the predecessor
        delete curr;
        
    }*/
  
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


