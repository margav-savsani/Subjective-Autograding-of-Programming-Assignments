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
        
        int path=0;
        TreeNode* ancestor = new_node->parent;
        while(ancestor != nullptr) {
            path++;
            ancestor->height = max(ancestor->height, path);
            ancestor = ancestor->parent;
        }
    }

    new_node->printInfo();
    if (new_node->parent != nullptr)
    new_node->parent->printInfo();
    return true;
}


int BST::find(int jrnyCode)
{
    TreeNode* dummy = new TreeNode(jrnyCode, 0);
    TreeNode* node = root;
    while(node != nullptr) {
        if(BSTLessThan(dummy, node))
            node = node->left;
        else if(BSTLessThan(node, dummy))
            node = node->right;
        else
            return 1;
    }
    return 0;
}

    // =====================================================
    // OPTIONAL: Implement "remove" only for bonus marks
    // =====================================================

    // Returns true on successful deletion of the entry in BST with
    // matching journey code. Returns false if it cannot find any such element.
    //
    // You may assume that no two elements in the BST have the same journey
    // code, and journey code is the key for insertion and finding in the BST.


TreeNode* BST::find(int JourneyCode, int price) {
    TreeNode* dummy = new TreeNode(JourneyCode, price);
    TreeNode* node = root;
    while(node != nullptr) {
        if(BSTLessThan(dummy, node))
            node = node->left;
        else if(BSTLessThan(node, dummy))
            node = node->right;
        else
            return node;
    }
    return nullptr;
}


bool BST::remove(int jrnyCode)
{
    TreeNode* dummy = new TreeNode(jrnyCode, 0);
    TreeNode* node = new TreeNode(0,0);
    node = find(jrnyCode, 0);

    if(!node)
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

    if (y!=node) {
        TreeNode* dum = y;
        dum->left = node->left;
        dum->right = node->right;
        dum->parent = node->parent;

        node = dum;
    }

    while(ancestor != nullptr) {
        if (ancestor->left == nullptr && ancestor->right == nullptr)
            ancestor->height = 0;

        else if (ancestor->left == nullptr)
            ancestor->height = ancestor->right->height + 1;

        else if (ancestor->right == nullptr)
            ancestor->height = ancestor->left->height + 1;
        
        else
            ancestor->height = max(ancestor->left->height, ancestor->right->height) + 1;
        
        ancestor = ancestor->parent;
    }
    return true;
}

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


