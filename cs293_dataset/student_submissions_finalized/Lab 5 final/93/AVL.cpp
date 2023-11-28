#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

int TreeNode::insert_in_tree(int val, int price){    
    //inserts a value in the binary search tree at the appropriate location
    //this does not move any of the existing elements
    //Insertion happens in the whole tree
    //returns 10*(number of comparisons that happen during insertion)+(number of parent-child updates)
    int num_comp = 0, num_updates = 1;
    TreeNode* temp = this;
    while(temp->parent){
        temp = temp->parent;   
    }
    temp = temp->insert_in_subtree(val, price, num_comp); //store the location of the new node in temp
    //update heights in the tree
    temp->update_heights_of_ancestors();
    temp = temp->find_grandchild_of_unbalanced_ancestor(); //store the address of the first unbalanced ancestor in temp
    if(!temp) return 10*num_comp+num_updates;
    // std::cout<<temp->JourneyCode<<std::endl;
    int dir1, dir2;
    if(temp->parent->left == temp)
        dir2 = LEFT;
    else dir2 = RIGHT;
    if(temp->parent->parent->left == temp->parent)
        dir1 = LEFT;
    else dir1 = RIGHT;
    if(dir1==dir2){
        num_updates += rotate(temp->parent->parent, dir1, dir2);
        temp->parent->right->update_height(); 
        temp->parent->left->update_height();
        temp->parent->update_heights_of_ancestors();  
    }
    else if(dir1==LEFT){
        num_updates += rotate(temp->parent->parent, LEFT, RIGHT);
        temp->right->update_height();
        temp->left->update_height();
        temp->update_heights_of_ancestors();
    }
    else{
        num_updates += rotate(temp->parent->parent, RIGHT, LEFT);
        temp->right->update_height();
        temp->left->update_height();
        temp->update_heights_of_ancestors();
    }
    return 10*num_comp+num_updates;//since the number of updates is always less than 6, we can use this scheme to pass both
} 


bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
    currNode->rotate(grandParentNode, LEFT, LEFT);
    currNode->update_height();
    grandParentNode->update_height();
    parentNode->update_height();
    return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
    currNode->rotate(grandParentNode, LEFT, RIGHT);
    currNode->update_height();
    parentNode->update_height();
    grandParentNode->update_height();
    return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
    currNode->rotate(grandParent, RIGHT, LEFT);
    currNode->update_height();
    parent->update_height();
    grandParent->update_height();
    return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
    currNode->rotate(grandParent, RIGHT, RIGHT);
    currNode->update_height();
    parent->update_height();
    grandParent->update_height();
    return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int jrnyCode, int price)
{
    // Implement insertion in AVL tree followed by balance factor restoration
    // by properly identifying x, y, z as used in Prof. Garg's lectures
    // (equivalently, currNode, parentNode, grandParentNode in our code) and
    // invoking rotateLeftLeft, rotateLeftRight, rotateRightLeft and/or
    // rotateRightRight as appropriate.

    // It is your responsibility to find out the right x, y, z (or currNode,
    // parentNode, grandParentNode) following Prof. Garg's lectures
    //
    // Once you identify these correctly, simply invoking the appropriate
    // rotation should do the job.
    // You don't even need to invoke rotation twice for the double
    // rotations -- the way rotationLeftRight is implemented, and
    // rotationRightLeft should be implemented, you should be able to achieve
    // the effect of the double rotation using one invokation of the
    // appropriate member function.

    // You MUST use only AVLLessThan to compare two journey codes.  You
    // can create a new node containing the journey code to be inserted
    // and invoke AVLLessThan on the current node in the tree that you
    // are inspecting and the new node to do your comparison.

    // REMEMBER to update the heights of appropriate nodes in the tree
    // after an insertion.
    
    // We use "return true" below to enable compilation.  Change this as you
    // see fit.
    if(root == NULL){
        root = new TreeNode(jrnyCode, price);
        totalComparisonCost += perComparisonCost;
        return true;
    }
    int num_comp = (root->insert_in_tree(jrnyCode, price));
    int num_update = num_comp%10;
    num_comp/=10;
    totalComparisonCost += perComparisonCost*num_comp;
    totalParentChildUpdateCost += perParentChildUpdateCost*num_update;
    while(root->parent)
        root = root->parent;  
    return true;
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
{
  // Implement find in AVL tree.
  // This is really no different from finding in a binary search tree.
  // This operation cannot cause any balance factor disturbances.

  // You MUST use only AVLLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke AVLLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
    TreeNode* dummy = new TreeNode{jrnyCode, 0};   
    TreeNode* temp1{root};
    while(temp1){
        if(AVLEqualTo(dummy, temp1))
            return temp1->price;
        else if(AVLLessThan(dummy, temp1))
            temp1 = temp1->left;
        else
            temp1 = temp1->right;
    }
    return -1;
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in AVL tree with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the AVL tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::remove(int jrnyCode)
{
  // Implement deletion in AVL tree followed by balance factor restoration
  // by properly identifying x, y, z as used in Prof. Garg's lectures
  // (equivalently, currNode, parentNode, grandParentNode in our code) and
  // invoking rotateLeftLeft, rotateLeftRight, rotateRightLeft and/or
  // rotateRightRight as appropriate.

  // It is your responsibility to find out the right x, y, z (or currNode,
  // parentNode, grandParentNode) following Prof. Garg's lectures
  //
  // Once you identify these correctly, simply invoking the appropriate
  // rotation(s) should do the job.
  // You don't even need to invoke rotation twice for the double
  // rotations -- the way rotationLeftRight is implemented, and
  // rotationRightLeft should be implemented, you should be able to achieve
  // the effect of the double rotation using one invokation of the
  // appropriate member function.

  // You MUST use only AVLLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke AVLLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // REMEMBER to update the height of appropriate nodes in the tree
  // after a successful deletion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
  return true;
}


