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

  //new node is created that will be used for insertion
  TreeNode* z= new TreeNode(jrnyCode, price);
  
  //if root is a nullptr, that is tree is uninitialized, we set the value of root
  if(root==nullptr){
    root=z;
  }
  else{
    //else, we can simply insert in left or right tree depending on value of treenode
    //inserting on left :
    if (BSTLessThan(z, root)){
      //if left node exists, we insert new node there, else we create a new left node
      if(root->left!=nullptr){
        BST* left_BST = new BST(root->left,perComparisonCost, perParentChildUpdateCost);
        left_BST->insert(jrnyCode, price);
        totalComparisonCost+=left_BST->getComparisonCost();
        totalParentChildUpdateCost+=left_BST->getParentChildUpdateCost();
      }
      else{
        updateBSTParentChild(z,root,true);
      }
    }
    //inserting on the right
    else{
      if(BSTLessThan(root,z)){
        //if right node exists, we insert new node there, else we create a new right node
        if(root->right!=nullptr){
          BST* right_BST = new BST(root->right,perComparisonCost, perParentChildUpdateCost);
          right_BST->insert(jrnyCode, price);
          totalComparisonCost+=right_BST->getComparisonCost();
          totalParentChildUpdateCost+=right_BST->getParentChildUpdateCost();
        }      
        else{
          updateBSTParentChild(z,root,false);
        }
      }
      else{  //node to be inserted already exists
        return false;
      }
    }
  }
  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  //Updating height in all the nodes
  TreeNode* curr_parent = z->parent; //parent (or ancestor) that we are updating height of
  int curr_height = 0; //height difference between this node and the current parent
  //run a loop that goes upto the root
  bool cont=true;
  while (curr_parent!=nullptr && cont){ 
    curr_height++;
    cont=curr_parent->insertUpdateHeight(curr_height);
    curr_parent=curr_parent->parent;
  }
  //finally, curr_height stores height of root of tree (= the height of tree)

  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
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
  TreeNode* z = new TreeNode(jrnyCode,-5);  
  //price is kept -5 so that we know if we accidentally return z's price (basically for debugging purpose)
  if (BSTLessThan(z,root)){  //if z is less than root then we find in left subtree
    if (root->left!=nullptr){
      BST* left_BST = new BST(root->left, perComparisonCost, perParentChildUpdateCost);
      return left_BST->find(jrnyCode);
    }
    else{
      return -1;
    }
  }
  else{  //now, it can be equal or greater than the current node
    if(BSTLessThan(root,z)){   //if z is in right subtree
      if (root->right!=nullptr){   //if right child exists
        BST* right_BST = new BST(root->right, perComparisonCost, perParentChildUpdateCost);
        return right_BST->find(jrnyCode);
      }
      else{  //else
        return -1;
      }
    }
    else{ //this means root is equal to z
      return root->getPrice();
    }
  }
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


