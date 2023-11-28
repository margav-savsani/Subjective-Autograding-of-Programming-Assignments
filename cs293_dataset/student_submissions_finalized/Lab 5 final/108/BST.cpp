#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

void BST::update_height(TreeNode* node) {
    while(node) {
        node->height = 1 + max(node->left ? node->left->height : 0, node->right? node->right->height : 0);
        node = node->parent;
    }
}

// Returns true on successful insertion in BST. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the BST

bool BST::insert(int jrnyCode, int price) {
    // Implement insertion in BST

    // You MUST use only BSTLessThan to compare two journey codes. You
    // can create a new node containing the journey code to be inserted
    // and invoke BSTLessThan on the current node in the tree that you
    // are inspecting and the new node to do your comparison.

    // REMEMBER to update the heights of appropriate nodes in the tree
    // after an insertion.
    
    if (find(jrnyCode)) return false;

    // Create the new node
    TreeNode* new_node = new TreeNode { jrnyCode, price };
    new_node->parent = nullptr;

    // Inserting at the root
    if (!root) {
        root = new_node;
        return true;
    }

    // Insert at the right place
    TreeNode* cur { root };
    while (true) {
        if (BSTLessThan(cur, new_node)) {
            if (cur->right) cur = cur->right;
            else {
                cur->right = new_node;
                break;
            }
        } else {
            if (cur->left) cur = cur->left;
            else {
                cur->left = new_node;
                break;
            }
        }
    }

    new_node->parent = cur;
    update_height(new_node);
    return true;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

bool BST::find(int jrnyCode) {
    // Implement find in BST

    // You MUST use only BSTLessThan to compare two journey codes. You
    // can create a new node containing the journey code to be searched
    // (along with some arbitrary price) and invoke BSTLessThan on the
    // current node in the tree that you are inspecting and the new node
    // to do your comparison.

    TreeNode dummy {jrnyCode, 0};
    TreeNode* cur { root };
    while (true) {
        if (!cur) return false;

        if (cur->JourneyCode == jrnyCode) return true;

        if (BSTLessThan(cur, &dummy)) cur = cur->right;
        else cur = cur->left;
    }
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in BST with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the BST have the same journey
// code, and journey code is the key for insertion and finding in the BST.

bool BST::remove(int jrnyCode) {
    // Implement deletion in BST
    
    // You MUST use only BSTLessThan to compare two journey codes. You
    // can create a new node containing the journey code to be searched
    // (along with some arbitrary price) and invoke BSTLessThan on the
    // current node in the tree that you are inspecting and the new node
    // to do your comparison.

    // REMEMBER to update the height of appropriate nodes in the tree
    // after a successful deletion.
    
    if (!find(jrnyCode)) return false;

    TreeNode* cur { root };
    TreeNode dummy {jrnyCode, 0};

    while (true) {
        if (jrnyCode == cur->JourneyCode) {
            TreeNode* node { nullptr };
            if (!(cur->left) && !(cur->right)) {
                node = cur->parent;
                // Deleting at the leaf
                if (cur == root) root = nullptr;
                else {
                    if (cur->parent->left == cur) cur->parent->left = nullptr;
                    else cur->parent->right = nullptr;
                }

            } else if (!(cur->left) || !(cur->right)) {
                node = cur->parent;
                // Deleting node with one child
                TreeNode* next = cur->left ? cur->left : cur->right;
                next->parent = cur->parent;
                if (cur != root) {
                    if (cur->parent->left == cur) cur->parent->left = next;
                    else cur->parent->right = next;
                }
                else {
                    root = next;
                    root->parent = nullptr;
                }

            } else {
                // Deleting node with two children
                TreeNode* next = findmax(cur->left);  // Node to be inserted at the deleted node's place
                node = (next == cur->left ? next : next->parent);

                // Update pointers from the node
                swap(next->parent, cur->parent);
                swap(next->right, cur->right);
                swap(next->left, cur->left);
                
                // Update pointers to the node
                next->right->parent = next;
                if (next->parent) {
                    if (next->parent->left == cur) next->parent->left = next;
                    else next->parent->right = next;
                }
                else root = next;

                if (next != next->left) {
                    next->left->parent = next;
                    cur->parent->right = cur->left;
                    if (cur->left) cur->left->parent = cur->parent;
                } else {
                    next->left = cur->left;
                    if (next->left) next->left->parent = next;
                }
            }

            update_height(node);
            return true;

        } else if (BSTLessThan(cur, &dummy)) cur = cur->right;
        else cur = cur->left;
    }
}

// Finds the max element in the tree rooted at Root
TreeNode* BST::findmax(TreeNode* Root) {
    while (Root->right) Root = Root->right;
    return Root;
}