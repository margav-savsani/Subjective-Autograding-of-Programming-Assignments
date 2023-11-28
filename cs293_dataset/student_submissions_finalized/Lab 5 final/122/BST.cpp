#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif
void BST::hd(TreeNode*m){
  if (m==root){
    return;
  }
  else if(m->parent->height >= m->height +1){
    return;
  }
  else{
    m->parent->height +=1;
    hd(m->parent);
  }
}
int BST::fi(TreeNode*r,TreeNode* s){

  
if(r ==nullptr){ 
  cout << "li";
return -1;}
if (!(BSTLessThan(r,s)||BSTLessThan(s,r))) {
            cout << "hello";
            return r->reprise();}
if (BSTLessThan(r,s)) {
    if (r -> right == nullptr){
          return -1;
                }
                TreeNode *pt = r -> right;
                return fi(r->right,s);
            } else {if (r -> left == nullptr) {
                    return -1;
                }
                
                TreeNode *pt = r -> left;
                 return fi(r->left,s);
            }
        }
bool BST::function(TreeNode* ptr, TreeNode*r){

   if(ptr==nullptr){
    cout << "hi";
    root = new TreeNode(0,0);
    root = r;
    hd(root);
    return true;  }
else
{
  if(BSTLessThan(ptr,r)){
      if (ptr -> right == nullptr) {
        ptr->right = new TreeNode(0,0);
        ptr->right = r;
        r->parent= ptr;
        hd(r);
        return true;
            }
      TreeNode *pt = ptr -> right;
      return  function(pt,r);
  }
   else {
            if (ptr -> left == nullptr) {
            ptr ->left= new TreeNode(0,0);
            ptr->left= r; 
            r->parent = ptr;
            hd(r);
            return true;  
            }
            TreeNode *pt = ptr -> left;
            return  function(pt,r);
        }
}
}


// Returns true on successful insertion in BST. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the BST


bool BST::insert(int jrnyCode, int price)
{
TreeNode * val ;
val = new TreeNode(jrnyCode,price);
bool flag = function(root,val);

//hd(val);
  // Implement insertion in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
  return flag;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
  
  TreeNode* d = new TreeNode(jrnyCode,0);
  int falg= fi(root,d);
  if(falg == -1){
  return -1;
}
else return falg;
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


