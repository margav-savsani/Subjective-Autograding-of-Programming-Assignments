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
    TreeNode *x = root;    
    TreeNode *y = x;
    if(root->JourneyCode==0){
        root->price = price;
        root->JourneyCode = JourneyCode;
        return true;        
    }
    TreeNode *z = new TreeNode(JourneyCode,price);
    int code=root->JourneyCode;
    while(x!=nullptr){ 
        if(BSTEqualTo(x,z))return false;
        if(BSTLessThan(x,z)){
            y=x;
            if(y->right==nullptr){
                x = z;
                updateBSTParentchild(y,x,false);
                break;
            }           
            x=y->right;                    
        }
        else{
            y=x;
            if(y->left==nullptr){
                x = z;
                updateBSTParentchild(y,x,true);
                break;
            } 
            x=y->left;            
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
  TreeNode *x = root;  
  TreeNode *y = x;
  TreeNode *z = new TreeNode(jrnyCode,0);
  while((!(BSTEqualTo(x,z)))&&(x!=NULL)){
        if(BSTLessThan(x,z)){
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
  if(BSTEqualTo(x,z))return true;
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
   if(!find(jrnycode))return false; 
    TreeNode *x = root;
    TreeNode *y = x;
    TreeNode *z = new TreeNode(jrnyCode,0);    
    while((!(BSTEqualTo(x,z)))&&(x!=NULL)){// goes to position of deleting node
        if(BSTLessThan(x,z)){
            y=x;
            x=y->right;            
        }
        else{
            y=x;
            x=y->left;            
        }
    }
    if((x->left==NULL)&&(x->right==NULL)){// case of having no children
        if(y->right==x)y->right=NULL;
        else y->left=NULL;
        return true;
       
    }
    if((x->left==NULL)&&(x->right!=NULL)){// case of having one child
        if(y->right==x)y->right=x->right;
        else if(y->left==x)y->left=x->right;
        else root=x->right; 
        return true; 
    }
    if((x->left!=NULL)&&(x->right==NULL)){// case of having one child
        if(y->right==x)y->right=x->left;
        else if(y->left==x) y->left=x->left;
        else root=x->left;
        return true;      
    }
    if((x->left!=NULL)&&(x->right!=NULL)){// case of having two children
        TreeNode *z = successor(*x);
        remove(z->JourneyCode,z->price);
        if(y->right==x)y->right=z;
        else if(y->left==x) y->left=z;
        else root=z;
        z->parent = x->parent;
        z->left = x->left;
        z->right = x->right;
        return true;
    }

  return false;
}


