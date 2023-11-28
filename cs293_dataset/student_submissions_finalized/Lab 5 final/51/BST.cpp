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

  TreeNode *curr =root;
  TreeNode *dummy;
  dummy= new TreeNode(jrnyCode,price);
  if(root == NULL)
  {
    root =new TreeNode(jrnyCode,price);
    return true;
  }
  if(find(jrnyCode) != -1)
  { cout<<"1"<<endl;
    return false;
  }
  else{ 

  cout<< root<<"1" <<dummy <<endl;
  if(BSTLessThan(root,dummy))
  { cout << "h2" << endl;
    if(root->right == NULL){
      cout<<"h1"<<endl;
      root->right = new TreeNode(jrnyCode,price);
     return true;}
    else{
      root = root->right;
      insert(jrnyCode,price);
    }
  }
  
  else if(!BSTLessThan(root,dummy)){
    cout<<"h3"<<endl;
    
    if(root->left == NULL){
      root->left = new TreeNode(jrnyCode,price);
    return true;}
    else{
      root = root->left;
      insert(jrnyCode,price);
    }

  }
  root =curr;
  
  }
  // Implement insertion in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
  return true;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{  TreeNode* curr = root;
   TreeNode* dummy1;
   dummy1 = new TreeNode(jrnyCode,123);
   if(root != NULL) { 
   if(!BSTLessThan(root,dummy1) && !BSTLessThan(dummy1,root)){
          return root->getprice();
   }
   else if(!BSTLessThan(root,dummy1))
        { root = root->left;
          find(jrnyCode);}
   else if(BSTLessThan(root,dummy1))
        { root = root->right;
          find(jrnyCode);}
   }
   root = curr; 
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


