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

void BST::insert(int jrnyCode, int price)
{
   
    if(find(JourneyCode)){return false;}
    else{
         root = insertion(root,JourneyCode,price);
         return true;
    }
}
TreeNode* BST::insertion(TreeNode* x,int JourneyCode,int price){
     if (x == NULL) {
        TreeNode* z = new TreeNode(JourneyCode,price);
        return z;
    }
    if (x -> price > price) {
        x -> left = insertion(x -> left, JourneyCode,price);
    }
    else {
        x -> right = insertion(x -> right , JourneyCode,price);
    }
    return x;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
  // Implement find in BST
 TreeNode* P;
    if(root==nullptr){return false;}
    else if(jrnyCode<root->jrnyCode){
         P=root->left;
         BST Q(P);
         return Q.find(JourneyCode,price);
      }
    else if(price>root->price){
         P=root->right;
         BST Q(P);
         return Q.find(JourneyCode,price);
      }
    else {return true;}
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


