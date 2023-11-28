#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#include <cmath>
#endif

int path(TreeNode* head)                       // This function updates height of each node from root when called.
{
    if (head == NULL) return -1;             
    if (head->left == NULL && head->right == NULL) return 0;  //This isa leaf node case and height of it should be 0.
    int left_height = path(head->left);
 
    int right_height = path(head->right);

    if(head->left != NULL) head->left->height = left_height;   // updating height of each of the left and right nodes. 
    if(head->right != NULL) head->right->height = right_height;
    
    return  1 + max(left_height, right_height); // height is longest between left and right sub-trees.
}

TreeNode *BST::search(TreeNode *T, int JourneyCode)  // This function returns the address of node with given JourneyCode.
{
    TreeNode *temp = new TreeNode(JourneyCode,0);
    if (T == nullptr)
    {
        return nullptr;                 // search until not found
    }
    if (BSTLessThan(T, temp))
    {
        return search(T->right, JourneyCode); // if JourneyCode > currentnode, search in right sub-tree.
    }
    else if (BSTLessThan(temp, T))
    {
        return search(T->left, JourneyCode); // vice-verse
    }
    else
        return T; // If JourneyCodes are equal return the address of currentnode.  
}
// Returns true on successful insertion in BST. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the BST

bool BST::insert(int jrnyCode, int price)
{
    TreeNode *newnode = new TreeNode(jrnyCode, price);  // create a node to be inserted.
    if (search(root, jrnyCode) != nullptr)
    {
        return false;       // search whether the inserting node already exists in the Tree.
    }
    else
    {
        if (root == nullptr)
        {
            root = new TreeNode(jrnyCode, price);   // If we are inserting first element
            root->height = 0;                       // Insert and update height to 0.
            return true;
        }
        else
        {
            TreeNode *T = root;  // check from root
            TreeNode *temp;      // from preserving the node at which insertion takes place.
            while (T != nullptr)
            {
                temp = T;
                if (BSTLessThan(newnode, T))
                {
                    T = T->left;
                }
                else
                {
                    T = T->right;
                }
            }
            if (BSTLessThan(newnode,temp))      // If JourneyCode of inserting node < JourneyCode of its parent
            {
                updateBSTParentChild(newnode, temp, true); // update child and parent to the left.
                
                root->height = path(root);  // update heights accordingly for each node.
                return true;
            }
            else
            {
                updateBSTParentChild(newnode, temp, false);
                
                root->height = path(root); // vice-versa.
                return true;
            }
        }
    }
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
    TreeNode *getnode = search(root, jrnyCode); // search for a node with given JourneyCode.
    if (getnode != nullptr)
    {
        return getnode->getprice();  // now return the price of node we got.
    }
    else
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
