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

int BST::getImbalance()
{
  if (root == nullptr) return 0;
  else return root->getImbalance();
}
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
// void BST::shortestPath(TreeNode*t)
// {
//   if(t->left==NULL && t->right==NULL)
//   {
//     t->shortestPathLength=1;
//     return 1;
//   }

//   else if(t->left==NULL)
//   {
//     return 1+shortestPath(t->right);
//   }
//   else if(t->right==NULL)
//   {
//     return 1+shortestPath(t->left);
//   }
// }
bool BST::insert(int JourneyCode, int price) { 
    
    if(find(JourneyCode,price)){
        return false;
    }
    if(root==NULL)
    {
        root=new TreeNode(JourneyCode,price);
        root->parent=NULL;
      
        return true;
    }
    BST n;
    n.root=root;
    if(n.root->left ==NULL && n.root->right==NULL ){
        if(n.root->price>price){
            n.root->left=new TreeNode(JourneyCode,price);
            n.root->left->parent=n.root;
        }
        if(n.root->price<price){
            n.root->right=new TreeNode(JourneyCode,price);
            n.root->right->parent=n.root;
        }
        return true;
    }
    if(n.root->left ==NULL && n.root->right!=NULL ){
        if(n.root->price>price){
            n.root->left=new TreeNode(JourneyCode,price);
            n.root->left->parent=n.root;
            return true;}
            else {n.root=n.root->right;
                return n.insert(JourneyCode,price);}
        
        
    }
    if(n.root->left !=NULL && n.root->right==NULL ){
        if(n.root->price<price){
            n.root->right=new TreeNode(JourneyCode,price);
            n.root->right->parent=n.root;
            return true;}
            else{n.root=n.root->left;
            return n.insert(JourneyCode,price);}
    }
    
    if(n.root->price>price)
    {
        n.root=n.root->left;
        n.insert(JourneyCode,price);
    }
    if(n.root->price<price)
    {
        n.root=n.root->right;
        n.insert(JourneyCode,price);
    }
    return false; 
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

  return true;
}


