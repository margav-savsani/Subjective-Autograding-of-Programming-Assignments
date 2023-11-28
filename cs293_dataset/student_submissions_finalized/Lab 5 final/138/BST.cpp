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
    TreeNode* to= new TreeNode(jrnyCode,price);//this is the node to be searched
    TreeNode * parent_ptr;
    TreeNode * child_ptr;
    child_ptr=root;
    parent_ptr=NULL;
    //loops continues till node is found
    while(child_ptr!=NULL){
        if(*child_ptr=*to){
          totalComparisonCost += perComparisonCost;
            //if the node is found,return false as the node is already present
            return false;
        }
        totalComparisonCost += perComparisonCost;
        //traverse the tree to find the node
        parent_ptr=child_ptr;
        if(BSTLessThan(to,child_ptr)){
            //if the price is left move to left
            child_ptr=child_ptr->left;
        }
        else{
            //if the price is more, move to right
            child_ptr=child_ptr->right;
        }
    }
    //attatching the node to the tree
    //comparing its price with the price of the parent node and accordingly joining it in the BST
    //if the price is equal, I have added it to the left
    if(parent_ptr==NULL){
        root=to;
        totalParentChildUpdateCost+=perParentChildUpdateCost;
    }
    else{
        to->parent=parent_ptr;
        if(BSTLessThan(to,parent_ptr)){
            parent_ptr->left=to;
            totalParentChildUpdateCost+=perParentChildUpdateCost;
        }

        else{
            parent_ptr->right=to;
            totalParentChildUpdateCost+=perParentChildUpdateCost;
        }
    }

    //setting the heights
    
    while(to!=NULL){
      //if parent ptr is NULL
      if(parent_ptr==NULL){
         //setting the height of the root
         if(to->left==NULL){
          to->height+=1;
          break;
         }
         else if(to->right==NULL){
          to->height+=1;
          break;
         }
         else{
         to->height=max((to->left)->height+1,(to->right)->height+1);
         break;
         }
      }
      //parent_ptr is not NULL
      else{
      //if right child is to
      if(parent_ptr->right==to){
        // only one child
        if(parent_ptr->left==NULL){
          parent_ptr->height+=1;
        }
        else{
          //if two children
           parent_ptr->height=max((parent_ptr->left)->height+1,(parent_ptr->right)->height+1);
        }
      }
      else{
        // if left child is to
          if(parent_ptr->right==NULL){
            parent_ptr->height+=1;
          }
          else{
            parent_ptr->height=max((parent_ptr->left)->height+1,(parent_ptr->right)->height+1);
          }
      }
      }
      to=parent_ptr;
      parent_ptr=parent_ptr->parent;
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

  TreeNode * roo;
  roo=root;
  TreeNode * to_find=new TreeNode(jrnyCode,0);

  while(roo!=NULL){
    if(*to_find=*roo){//if the price match, return the price 
      totalComparisonCost += perComparisonCost;
      return roo->get_price();
    }
    totalComparisonCost += perComparisonCost;
    if(BSTLessThan(to_find,roo)){//else traverse the tree
      roo=roo->left;
    }
    else{
      roo=roo->right;//else traverse the tree
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

  return true;
}


