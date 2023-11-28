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
    if(root==NULL){// initial insert
        root = new TreeNode(jrnyCode,price);
        return true;        
    }
    TreeNode *x = root;    
    TreeNode *y = x;
    TreeNode *z = new TreeNode(jrnyCode,price);
    while(x!=nullptr){ 
        if(x->jrCode()==z->jrCode())return false;
        if(BSTLessThan(x,z)){
            y=x;
            if(y->right==nullptr){
                x = z;
                updateBSTParentChild(x,y,false);
                break;
            }           
            x=y->right;                    
        }
        else{
            y=x;
            if(y->left==nullptr){
                x = z;
                updateBSTParentChild(x,y,true);
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
  TreeNode *x = root;  
  TreeNode *y = x;
  TreeNode *z = new TreeNode(jrnyCode,0);
  while((!(x->jrCode()==z->jrCode()))&&(x!=NULL)){
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
  if(x->jrCode()==z->jrCode())return z->pri();
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

TreeNode* BST :: successor(TreeNode x){ // to find successor which is required while deleting an element
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

bool BST::remove(int jrnyCode)
{
    if(find(jrnyCode)<0)return false; 
    TreeNode *x = root;
    TreeNode *y = x;
    TreeNode *z = new TreeNode(jrnyCode,0);
    if(root->setheight(root)==0){
      root=NULL;
      return true;
    }
    while(!(x->jrCode()==jrnyCode)&&(x!=NULL)){// goes to position of deleting node
        if(BSTLessThan(x,z)){
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
        remove(z->jrCode());
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