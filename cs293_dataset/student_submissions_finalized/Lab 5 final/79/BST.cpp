#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

void BST::updateheight(TreeNode* node){
    if(node==NULL)return;
    int lh=0;
    if(node->left!=NULL)lh=1+node->left->height;
    int rh=0;
    if(node->right!=NULL)rh=1+node->right->height;
    node->height=max(lh,rh);
    updateheight(node->parent);
    return;
}


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
    TreeNode* node=new TreeNode(jrnyCode,price);
    TreeNode* current=root;
    if(root==NULL){
        root=node;
        return true;
    }
    
    while(true){
        if(BSTLessThan(node,current)){
            if(current->left==NULL){
                updateBSTParentChild(node,current,true);
                node->parent=current;
                updateheight(current);
                return true;
            }
            current=current->left;
            continue;
        }
        else if(BSTLessThan(current,node)){
            if(current->right==NULL){
                updateBSTParentChild(node,current,false);
                node->parent=current;
                updateheight(current);
                return true;
            }
            current=current->right;
            continue;
        }
        else {
            delete node;
            return false;
        }

    }
  return true;
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
  TreeNode* node=new TreeNode(jrnyCode,0);
  TreeNode* current=root;
  while(true){
        if(current==NULL)return -1;
        
        else if(BSTLessThan(current,node)){
            if(current->right==NULL)return -1;
            current=current->right;
        }
        else if(BSTLessThan(node,current)){
            if(current->left==NULL)return -1;
            current=current->left;
        }
        else {
            return current->price;
        }

  }
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
 /*TreeNode* current=root;
    TreeNode* parent=NULL;
    bool left=false;
    
    while(true){
        
        if(current==NULL)return false;   
        if(current->jrnyCode==jrnyCode){
            if(current->price==price){
                if(current==root){
                    
                    if(current->left==NULL && current->right==NULL){
                    
                    root=NULL;
                    return true;
                    }
                    
                    if(current->left==NULL){
                        root=current->right;
                        return true;
                    }
                    
                    if(current->right==NULL){
                        root=current->left;
                        return true;
                    }
                    

                }
                
                if(current->left==NULL && current->right==NULL){
                    
                    if(left)parent->left=NULL;
                    else parent->right=NULL;
                    updateLength(parent);
                    return true;
                }
                if(current->left==NULL){
                    if(left)parent->left=current->right;
                    else parent->right=current->right;
                    updateLength(parent);
                    return true;
                }
                if(current->right==NULL){ 
                    if(left)parent->left=current->left;
                    else parent->right=current->left;
                    updateLength(parent);
                    return true;
                }
                
                TreeNode* temp=current->left;
                
                if(temp->right==NULL){
                    
                    current->left=temp->left;
                    current->jrnyCode=temp->jrnyCode;
                    current->price=temp->price;
                    updateLength(current);
                    return true;
                }
                while(temp->right!=NULL)temp=temp->right;
                current->jrnyCode=temp->jrnyCode;
                current->price=temp->price;
                temp->parent->right=temp->left;
                updateLength(temp->parent);
                return true;
            

            }
            else{
                    current=current->left;
                    continue;
            }

        }
        if(current->jrnyCode>jrnyCode){
            if(current->left==NULL)return false;
            parent=current;
            current=current->left;
            left=true;
        }
        if(current->jrnyCode<jrnyCode){
            if(current->right==NULL)return false;
            parent=current;
            current=current->right;
            left=false;
        }

    }*/
  return true;
}


