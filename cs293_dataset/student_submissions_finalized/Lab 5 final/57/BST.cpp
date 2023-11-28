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
{if(root==nullptr){root=new TreeNode(jrnyCode,price);return true;}
    

   TreeNode *y ;y= new TreeNode(0,0);
   TreeNode *x=root;
   TreeNode *jnode= new TreeNode(jrnyCode,price);
   
   
   while (x != NULL)
    { // Find till there is a place to fill.
        y = x;
        if (BSTLessThan(jnode,x))
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    jnode->parent = y; // Alloting the parent of z as y.

    // ALLOTING THE CHILD OF Y TO Z.
    if (BSTLessThan(jnode,y))

    {updateBSTParentChild(jnode, y, true);
        
    }
    else
    {updateBSTParentChild(jnode, y, false);
        
    }
    preorder(jnode);
    return true;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{ struct TreeNode *current =root;
 TreeNode *temp = new TreeNode(jrnyCode,0);
   if(root==nullptr){return 0;}
   while(current!=nullptr){
    if(!(BSTLessThan(current,temp))&&!(BSTLessThan(temp,current))){return current->getprice();}

    if(BSTLessThan(temp,current)){
        current=current->left;}
     else{current=current->right;}
    }
   return -1;
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


