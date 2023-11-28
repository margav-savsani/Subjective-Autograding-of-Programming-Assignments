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
bool isLeft(TreeNode* parent, TreeNode* child);
int noOfChildren(TreeNode* node) {
    if (node->left == nullptr && node->right == nullptr) return 0;
    else if (node->left != nullptr && node->right == nullptr) return 1;
    else if (node->left == nullptr && node->right != nullptr) return 1;
    else if (node->left != nullptr && node->right != nullptr) return 2;
    return -1;
}
bool isLeft(TreeNode* parent, TreeNode* child) { 
    if(parent -> left == nullptr) return false;

    else if(parent -> right == nullptr) return true;

    else if (parent -> left == child)
    {
        return true;
    }

    else if (parent -> right == child)
    {
        return false;
    }
    return false; 
}

TreeNode *treeMin(TreeNode* rootNode) {
    TreeNode * ptr = rootNode;
    while (ptr -> left != nullptr)
    {
        ptr = ptr -> left;
    }
    
    return ptr;
}

TreeNode* successor(TreeNode* node) {
    TreeNode* ptr1 = node;
    TreeNode* ptr2 = ptr1 -> parent;
    if (node -> right != nullptr)
    {
        return treeMin(node -> right);   
    }

    else {
        while (!(ptr2 -> left == ptr1))
        {
            if(ptr2 == nullptr) break;
            ptr1 = ptr2;
            ptr2 = ptr2 -> parent;
        }
        
        if (ptr2 != nullptr)
        {
            return ptr2;
        }

        return nullptr;
        
    }
    
}

void joinNodes(TreeNode* parent, TreeNode* child, bool left = true){
    if(left == true){
        parent -> left = child;
        child -> parent = parent;
    }    

    else {
        parent -> right = child;
        child -> parent = parent;
    }
}

void joinNodes2(TreeNode* node, TreeNode* Succ) {
    // making ptr form parent of the successor to the successor null
    if(isLeft(Succ->parent,Succ)) Succ->parent->left = nullptr;
    else Succ->parent->right = nullptr;

    if(Succ -> right != nullptr) joinNodes(Succ->right,Succ->parent,true);
    joinNodes(node->parent,Succ,isLeft(node->parent,node));
    Succ -> left = node -> left;
    Succ -> right = node -> right;
    Succ -> parent = node -> parent;

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
  TreeNode *tobeInserted = new TreeNode(jrnyCode,price);
  TreeNode *ptr = root;
  TreeNode *ptr2 = nullptr;
    
    //cout << "inserting" << endl;
    while (ptr != nullptr)
    {
        //cout << "stuck" << endl;
       if (BSTLessThan(tobeInserted,ptr))
       {
            ptr2 = ptr;
            ptr  = ptr -> left;
       }

       else if (ptr -> getJourneyCode() == jrnyCode)
       {
        return false;
       }
       

       else
       {
            ptr2 = ptr;
            ptr = ptr -> right;
       }
    }

    TreeNode *node = new TreeNode(jrnyCode,price);
    //if tree do not ahs a node
    if (ptr2 == nullptr)
    {
        root = node;
    }
    
    // if node was there before
    else if(ptr2 -> getJourneyCode() > jrnyCode) {
        ptr2 -> left = node;
        node -> parent = ptr2;
    }

    else
    {
        ptr2 -> right = node;
        node -> parent = ptr2;
    }
    // updateTreeData(node);
  return true;
}

void BST::updateTreeData(TreeNode* node){
    if(node == root) return;

    if(node -> parent -> height < node -> height + 1) {
        node -> parent -> height = node -> height +1;
    }

    updateTreeData(node->parent); 
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
  TreeNode *tobeFound = new TreeNode(jrnyCode,0);
  TreeNode *ptr = root;
  while (ptr != nullptr)
    {
       if (ptr->getJourneyCode() == jrnyCode)
       {
        return true;
       }

       else if (BSTLessThan(tobeFound,ptr))
       {
            ptr  = ptr -> left;
       }

       

       else
       {
            ptr = ptr -> right;
       }
    
        
    }
    
    return false;
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


