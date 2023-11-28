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

void BST::updateheight(TreeNode*z){
  TreeNode*y = z->parent;
    while(y!=nullptr){
        int temp;
        temp = y->height;
        if(y->left==nullptr && y->right==nullptr) y->height=1;
        else if(y->left!=nullptr && y->right==nullptr) y->height= y->left->height + 1;
        else if(y->right!=nullptr && y->left==nullptr) y->height= y->right->height + 1;
        else y->height = max(y->right->height,y->left->height)+1;
        if(temp == y->height) return;
        y = y->parent;
    }
}


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

  if(find(jrnyCode) != -1) return false;

  TreeNode *z = new TreeNode(jrnyCode,price);
  TreeNode* y = nullptr;
  TreeNode* x = root;
  while (x!=nullptr){
        y = x;
        if(BSTLessThan(z,x)) { x = x->left;}
        else x = x->right;
    }
  
    if (y == nullptr) root = z;
    else if (BSTLessThan(z,y)) {updateBSTParentChild(z,y,true);}
    else updateBSTParentChild(z,y,false);
    updateheight(z);
    


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

  //exactly similar to the AVL find (see AVL.cpp for explaination of the code)
  TreeNode *z = new TreeNode(jrnyCode,0);

  TreeNode* x = root;
    while (x != nullptr && (BSTLessThan(x,z) || BSTLessThan(z,x))){
        if (BSTLessThan(z,x))
            x = x->left;
        else{
            x = x->right;
        }
    }
    if (x == nullptr)
        return -1;
    else
        return x->getprice(); 

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

//returns the minimum journey code (required to find the successor of a given node)
TreeNode* BST::treenode_min(TreeNode *x){
    while(x->left != nullptr){
        x = x->left;
    }
    return x;
}

//returns the successor of the given node(requried to remove a treenode)
TreeNode* BST::successor(TreeNode* x){
    if (x->right != nullptr)
        return treenode_min(x->right);
    TreeNode* y = x->parent;    
    while (y != nullptr && x==y->right){
        x = y;
        y = x->parent;
    }
    return y;
}

//search is similar to find just that it returns the treenode instead of its price
TreeNode* BST::search(int JourneyCode){
  TreeNode *z = new TreeNode(JourneyCode,0);

  TreeNode* x = root;
    while (x != nullptr && (BSTLessThan(x,z) || BSTLessThan(z,x))){
        if (BSTLessThan(z,x))
            x = x->left;
        else{
            x = x->right;
        }
    }
    return x;
}


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

  TreeNode* z = search(jrnyCode);
    if(z == nullptr){ //if the given jrnycode does not exist return false
        return false;
    }
    //this if statement deals with the special case when the node to be removed is the root
    if(z == root){
        if(z->left == nullptr && z->right == nullptr){
            root = nullptr;
            return true;
        }
        else if(z->left != nullptr && z->right == nullptr){
            root = z->left;
            return true;
        }
        else if(z->left == nullptr && z->right != nullptr){
            root = z->right;
            return true;
        }
    }
    //When the node to be removed is a leaf(just set the parent's child pointer to null)
    if(z->left == nullptr && z->right == nullptr){
        TreeNode *y = z->parent;
        if(y->left == z){
            y->left = nullptr;
        }
        else y->right = nullptr;
        updateheight(z);
        
        return true;
    }
    //this else if condition covers the situation when the node to be removed has only one child
    else if(z->left == nullptr){
        TreeNode*y = z->parent;
        if(y->left == z){
            TreeNode*x = z->right;
            x->parent = y;
            y->left = x;
        }
        else{
            TreeNode*x = z->right;
            x->parent = y;
            y->right = x;
        }
        updateheight(z);
        
        return true;
    }
    else if(z->right == nullptr){
        TreeNode*y = z->parent;
        if(y->left == z){
            TreeNode*x = z->left;
            x->parent = y;
            y->left = x;
        }
        else{
            TreeNode*x = z->left;
            x->parent = y;
            y->right = x;
        }
        updateheight(z);
        
        return true;
    }
    //When the node to be removed has both childs
    //This just becomes a pointer game 
    //It is covered in 2 cases
    //The node names are appropriately chosen for explanation.
    else{
        TreeNode*successor_of_z = successor(z);
        TreeNode* parent_of_z = z->parent;
        TreeNode*child_of_successor=successor_of_z->right;
        TreeNode* parent_of_successor = successor_of_z->parent;
        bool is_left=true;
        if(parent_of_z->right == z) is_left=false;
        //case-1:when the successor of the node to be removed is the right child of the node
        if(z->right == successor_of_z){
          updateBSTParentChild(successor_of_z,parent_of_z,is_left);
          updateBSTParentChild(z->left,successor_of_z,true);
          updateheight(successor_of_z);
        }
        //case-2:otherwise
        else{
          updateBSTParentChild(child_of_successor,parent_of_successor,true);
          updateBSTParentChild(successor_of_z,parent_of_z,is_left);
          updateBSTParentChild(z->right,successor_of_z,false);
          updateBSTParentChild(z->left,successor_of_z,true);
          updateheight(parent_of_successor);
        }
        
        
        return true;
    }


  
}


