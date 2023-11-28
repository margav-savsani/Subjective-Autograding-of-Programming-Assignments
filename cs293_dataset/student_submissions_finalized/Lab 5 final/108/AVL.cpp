#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

// Recall from Prof. Naveen Garg's lectures how the various rotations are
// applied to restore the balance factor at all nodes of an AVL tree
// to either 0, 1 or -1, after an insert or delete.
// The correspondence between the terminology in Prof. Garg's lectures and
// our terminology in this code is as follows:
//
// Prof. Garg's lectures             Our code
// ---------------------             --------
//     x                             currNode
//     y                             parentNode
//     z                             grandParentNode
//
// Recall also that z (grandParentNode) is the lowest node in the path from
// the root to the inserted node or to the deleted node (as the case may be)
// where the balance factor has either become < -1 or > 1.
// To find what x (currNode) and y (parentNode) should be, you need to
// recall Prof. Garg's lectures.
// These are slightly differently defined when inserting nodes and when
// deleting nodes

void AVLTree::rotateright(TreeNode* node) {
    TreeNode* lft = node->left;

    // Update the all the pointers appropriately
    if (node->parent) updateAVLParentChild(lft, node->parent, node->parent->left == node);
    else lft->parent = nullptr;
    updateAVLParentChild(lft->right, node, true);
    updateAVLParentChild(node, lft, false);

    // Update the heights
    update_height(node);
    update_height(lft);
    update_height(lft->parent);
}

void AVLTree::rotateleft(TreeNode* node) {
    TreeNode* rgt = node->right;

    // Update the all the pointers appropriately
    if (node->parent) updateAVLParentChild(rgt, node->parent, node->parent->left == node);
    else rgt->parent = nullptr;
    updateAVLParentChild(rgt->left, node, false);
    updateAVLParentChild(node, rgt, true);

    // Update the heights
    update_height(node);
    update_height(rgt);
    update_height(rgt->parent);
}

// Updates the height of node
void AVLTree::update_height(TreeNode* node) {
    if (node) node->height = 1 + max(node->left ? node->left->height:0, node->right ? node->right->height:0);
}

// Updates the tree to make sure it is balanced
// 
// Starts at node and keeps going upward till the root, 
// balancing (by rotating) any imbalanced node accordingly
void AVLTree::update(TreeNode* node) {
    while (node) {
        update_height(node);
        int imb { imbalance(node) };

        if (imb == 2) { // If the right subtree is larger then left rotate
            if (imbalance(node->right) == -1) rotateright(node->right); // Special 2 rotation case
            if (node == root) root = node->right;
            rotateleft(node);
        } else if (imb == -2) { // If the left subtree is larger then right rotate
            if (imbalance(node->left) == 1) rotateleft(node->left); // Special 2 rotation case
            if (node == root) root = node->left;
            rotateright(node);
        }
        node = node->parent;
    }
}

// Returns the imbalance of the tree
// Imbalance := height of right subtree - height of left subtree
int AVLTree::imbalance(TreeNode* node) {
    if (!node) return 0;
    return (node->right ? node->right->height:0) - (node->left ? node->left->height:0);
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int jrnyCode, int price) {
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

    // You MUST use only AVLLessThan to compare two journey codes. You
    // can create a new node containing the journey code to be inserted
    // and invoke AVLLessThan on the current node in the tree that you
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
        root->height = 1;
        return true;
    }

    // Insert at the right place
    TreeNode* cur { root };
    while (true) {
        if (AVLLessThan(cur, new_node)) {
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
    // Update the new tree so as to be balanced
    update(new_node);
    return true;
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::find(int jrnyCode) {
    // Implement find in AVL tree.
    // This is really no different from finding in a binary search tree.
    // This operation cannot cause any balance factor disturbances.

    // You MUST use only AVLLessThan to compare two journey codes. You
    // can create a new node containing the journey code to be searched
    // (along with some arbitrary price) and invoke AVLLessThan on the
    // current node in the tree that you are inspecting and the new node
    // to do your comparison.

    TreeNode dummy { jrnyCode, 0 };
    TreeNode* cur { root };
    while (true) {
        if (!cur) return false;

        if (cur->JourneyCode == jrnyCode) return true;

        if (AVLLessThan(cur, &dummy)) cur = cur->right;
        else cur = cur->left;
    }
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

bool AVLTree::remove(int jrnyCode) {
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

    // You MUST use only AVLLessThan to compare two journey codes. You
    // can create a new node containing the journey code to be searched
    // (along with some arbitrary price) and invoke AVLLessThan on the
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
                } else {
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

            // Update the new tree so as to be balanced
            update(node);
            return true;

        } else if (AVLLessThan(cur, &dummy)) cur = cur->right;
        else cur = cur->left;
    }


}

// Finds the max element in the tree rooted at Root
TreeNode* AVLTree::findmax(TreeNode* Root) {
    while (Root->right) Root = Root->right;
    return Root;
}