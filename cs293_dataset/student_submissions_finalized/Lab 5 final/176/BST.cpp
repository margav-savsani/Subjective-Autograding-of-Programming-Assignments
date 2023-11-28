#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif


bool BST::insert(int jrnyCode, int price)
{
    if(find(jrnyCode))        // cant insert if already present
        return false;

    TreeNode *new_node, *null_node, *parent;
    new_node = new TreeNode(jrnyCode, price);
    if(root == nullptr)
        root = new_node;    // inserting the first node of empty tree
    else {                  
        parent = nullptr;
        null_node = root;
        while(null_node != nullptr) {       // finding the position for new node to be inserted
            parent = null_node;
            if(BSTLessThan(new_node, null_node))
                null_node = null_node->left;
            else
                null_node = null_node->right;
        }
        if(BSTLessThan(new_node, parent))
            parent->left = new_node;
        else
            parent->right = new_node;
        new_node->parent = parent;

        // possible disturbances in height occur along the route from deleted node to root
        TreeNode* ancestor = new_node->parent;
        while(ancestor != nullptr) {
            updateHeight(ancestor);
            ancestor = ancestor->parent;
        }
    }
    return true;
}

// returns 1 if found, 0 if not found

int BST::find(int jrnyCode)
{
    TreeNode* dummy = new TreeNode(jrnyCode, 0);       // holds the value of JourneyCode to compare between two TreeNodes
                                                       // since JourneyCode is a private variable and can be compared only by a function
    TreeNode* node = root;
    while(node != nullptr) {
        if(BSTLessThan(dummy, node))
            node = node->left;
        else if(BSTLessThan(node, dummy))
            node = node->right;
        else
            return 1;       // node found
    }
    return 0;               // node not found
}

// updates the height of the passed node based on the heights of its children

bool BST::updateHeight(TreeNode* node)
{
    if(node->left == nullptr && node->right == nullptr)     // no children so height 0
        node->height = 0;
    else if(node->left == nullptr)                          // height is 1 more then the height of non-null child
        node->height = 1 + node->right->height;
    else if(node->right == nullptr)                         // height is 1 more then the height of non-null child
        node->height = 1 + node->left->height;
    else
        node->height = 1 + max(node->left->height, node->right->height);    // height is 1 more then the max of heights of both children
    return true;
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
    TreeNode* node;
    node = find(jrnyCode, 0);   // finding with JourneyCode only

    if(!node)       // node to be deleted not present
        return false;

    TreeNode *x,*y;
    if (node->left == nullptr || node->right == nullptr)  y = node;
    else    y = successor(node);

    TreeNode* ancestor = y->parent;

    if (y->left != nullptr)     x = y->left;
    else                        x = y->right;

    if (x!=nullptr)    x->parent = y->parent;

    if (y->parent == nullptr)       root = x;
    else if (y == y->parent->left)  y->parent->left = x;
    else                            y->parent->right = x;

    if (y!=node) {              // copying entries of node into y with the help of dummy varialbe
        TreeNode dum = *y;      // since TreeNode has private variables
        dum.parent = node->parent;
        dum.right = node->right;
        dum.left = node->left;
        *node = dum;
    }

    // possible disturbances in height occur along the route from deleted node to root
    while(ancestor != nullptr) {
        updateHeight(ancestor);
        ancestor = ancestor->parent;
    }
    return true;
}

// finds a node based on JourneyCode and returns the pointer to it, if found
TreeNode* BST::find(int JourneyCode, int price) {           // dummy price to distinguish with other find function
    TreeNode* dummy = new TreeNode(JourneyCode, price);     // holds the value of JourneyCode to compare between two TreeNodes
                                                            // since JourneyCode is a private variable and can be compared only by a function
    TreeNode* node = root;                                  
    while(node != nullptr) {
        if(BSTLessThan(dummy, node))
            node = node->left;
        else if(BSTLessThan(node, dummy))
            node = node->right;
        else
            return node;        // node found
    }
    return nullptr;             // node not found
}

// returns the pointer to the successor of the passed node
// used when deleting a node with two non-null children

TreeNode* BST::successor(TreeNode* node) {
    TreeNode* suc = node;
    if (node->right != nullptr) {
        suc = suc->right;
        while (suc->left != nullptr) 
        suc = suc->left;
        return suc;
    }
    else {
        suc = node->parent;
        while (suc!=nullptr && node==suc->right) {
            node = suc;
            suc = suc->parent;
        }
        return suc;
    }
}


