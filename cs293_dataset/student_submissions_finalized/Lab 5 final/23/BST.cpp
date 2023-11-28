#ifndef BST_H
#include "BST.h"
#include "Tree.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif


// Returns true on successful insertion in BST. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the BST
bool BST::insert(int jrnyCode, int price)
{          if (find(jrnyCode)!=-1){return false;}
           
           TreeNode *y=NULL;
           TreeNode *x=root;
           TreeNode *z;
           
           z=new TreeNode(jrnyCode,price);
          
           while(x!=NULL){
               y=x;
               
               if(BSTLessThan(z,x)){x=x->left;}
               else{ x=x->right;}
                     }
                     
           z->left=NULL;
           z->right=NULL;
            
           if(y==NULL) root=z,z->parent=y;
           else if (BSTLessThan(z,y))updateBSTParentChild(z,y,true);
           else updateBSTParentChild(z,y,false);
           assignheight(root);
           return true;}
           
  // Implement insertion in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.


// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{         TreeNode *x;
          TreeNode *z;
          x=root;
          z=search(x,jrnyCode);
          if(z==NULL) return -1;
          else return 1;
  // Implement find in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // We use "return -1" below to enable compilation.
}
TreeNode* BST::search(TreeNode *d,int JourneyCode){
          TreeNode *x=d;
          TreeNode *z;
          z=new TreeNode(JourneyCode,0);
          if (x==NULL) return NULL;
          if(x->jrnyCode()==JourneyCode){
                      return x;}
          if(BSTLessThan(z,x)) return search(x->left,JourneyCode);
          else return search(x->right,JourneyCode);
          }
int  BST::height(TreeNode *x){
          if(x->right == NULL && x->left == NULL) return 1;
          else if(x->right == NULL && x->left != NULL) return height(x->left)+1;
          else if(x->left == NULL && x->right != NULL) return height(x->right)+1;
          else return max(height(x->left),height(x->right))+1;
          }
void  BST::assignheight(TreeNode *x){
           x->height=height(x);
           if(x->right!=NULL)assignheight(x->right);
           if(x->left!=NULL)assignheight(x->left);         
           return;
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


