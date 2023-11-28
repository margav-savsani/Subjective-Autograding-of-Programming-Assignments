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


// global variable
// work as a bool
// stores 0 for false
// stores 1 for true
int value = 0;

bool BST::insert(int jrnyCode, int price)
{
    // Implement insertion in BST
    
    // storing the data of node which has to be inserted in node 'NEW'
    TreeNode *NEW = new TreeNode(jrnyCode,price);

    // storing the root in the ins_l(insert to left)
    TreeNode *ins_l = root;
    
    // creating a new node which is used to find the node
    // where we have to insert the node
    TreeNode *ins_r = nullptr;
    
    // after completing the loop, data of the node where
    // we have to insert the new node is stored in the
    // ins_r
    while(ins_l!=nullptr)
    {
        ins_r = ins_l;
        if(BSTEqualTo(NEW,ins_l)) break;
        if(BSTLessThan(NEW,ins_l)) ins_l = ins_l->left;
        else ins_l = ins_l->right;
    }
    
    // if the ins_r found to be nullptr, than that means
    // tree is empty, so root becomes our inserting node, i.e. NEW
    if(ins_r==nullptr)
    {
        root = NEW;
        return true;
    }
    
    // inserting the new node to the left of the ins_r
    if(BSTLessThan(NEW,ins_r))
    {
        ins_r->left=NEW;
        updateBSTParentChild(NEW, ins_r, true);
    }
    
    // inserting the new node to the right of the ins_r
    else
    {
        ins_r->right = NEW;
        updateBSTParentChild(NEW, ins_r, false);
    }

    // storing the data of the parent of the inserting node
    TreeNode *for_height = ins_r;

    // for storing the height of each node in their private variable height
    while(for_height!=nullptr)
    {
        for_height->update_the_height();
        for_height = for_height->parent;
    }
    return true;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
    // Implement find in BST tree
    
    // create a new node containing the journey code to be searched
    TreeNode *to_find = new TreeNode(jrnyCode,10101);
    
    // storing our root in ins_l(insert in left)
    TreeNode *ins_l = root;

    // using while loop to check whether our to_find node
    // is there in BST Tree or not
    while(!BSTEqualTo(to_find,ins_l)){
        if(BSTLessThan(to_find,ins_l))
        {
            ins_l = ins_l->left;
            
            // defined in BST.cpp setting is to 0, i.e. false,
            // reflecting left subtree
            if(ins_l==nullptr) break;
        }
        // else it goes to the right subtree
        else
        {
            ins_l = ins_l->right;
            
            // defined in BST.cpp setting is to 1, i.e. true,
            // reflecting left subtree
            if(ins_l==nullptr) break;
        }
    }
    
    // if our node is not present then returns -1
    if(ins_l==nullptr) return -1;
    
    // value of price is returned from the get_price function defined in Tree.h,
    // which returns the price of the node
    // if node is present then returning its price
    else return ins_l->get_price();
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
    // You MUST use only BSTLessThan to compare two journey codes.  You
    // can create a new node containing the journey code to be searched
    // (along with some arbitrary price) and invoke BSTLessThan on the
    // current node in the tree that you are inspecting and the new node
    // to do your comparison.

    // REMEMBER to update the height of appropriate nodes in the tree
    // after a successful deletion.
  
    // We use "return true" below to enable compilation.  Change this as you
    // see fit.
}
