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
    if (root == nullptr)
    {
        root = new TreeNode(jrnyCode, price);
        root->parent = nullptr;
        return true;
    }
    TreeNode *currNode = root, *parentOfCurrNode = nullptr;
    TreeNode *naya = new TreeNode(jrnyCode, price);
    while (currNode != nullptr)
    {
        if (BSTLessThan(currNode, naya))
        {
            parentOfCurrNode = currNode;
            currNode = currNode->right;
        }
        else if (BSTLessThan(naya, currNode))
        {
            parentOfCurrNode = currNode;
            currNode = currNode->left;
        }
        else
        {
            return false;
        }
    }

    if (BSTLessThan(naya, parentOfCurrNode))
    {
        // parentOfCurrNode->left = naya;
        // naya->parent = parentOfCurrNode;
        updateBSTParentChild(naya, parentOfCurrNode, true);
    }
    else
    {
        // parentOfCurrNode->right = naya;
        // naya->parent = parentOfCurrNode;
        updateBSTParentChild(naya, parentOfCurrNode, false);
    }

    int curr_height = 1;

    while (parentOfCurrNode != nullptr)
    {
        if (parentOfCurrNode->height < curr_height)
        {
            parentOfCurrNode->height = curr_height;
            curr_height++;
            parentOfCurrNode = parentOfCurrNode->parent;
        }
        else
            break;
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

    if (root == NULL)
    {
        return -1;
    }
    TreeNode *k = root;
    TreeNode *To_search_for = new TreeNode(jrnyCode, 0);
    while (k != nullptr)
    {

        if (BSTLessThan(To_search_for, k))
        {
            k = k->left;
        }
        else if (BSTLessThan(k, To_search_for))
        {

            k = k->right;
        }
        else
        {
            return 1;
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
bool BST::remove(int jrnyCode)
{

    if (root == nullptr)
    {
        return false;
    }
    TreeNode *k = root;
    TreeNode *dummy = new TreeNode(jrnyCode, 0);
    while (k != nullptr)
    {
        if ((!BSTLessThan(dummy, k)) && (!BSTLessThan(k, dummy)))
        {
            break;
        }
        if (BSTLessThan(k, dummy))
        {
            k = k->right;
        }
        if (BSTLessThan(dummy, k))
        {
            k = k->left;
        }
    }
    if (k == nullptr)
    {
        return false;
    }
    TreeNode *y, *x;
    x = new TreeNode(0,0);
    y = new TreeNode(0,0);
    if (k->left == nullptr || k->right == nullptr)
    {
        y = k;
    }
    else
    {
        y = minforsuccessor(k->right);
    }
    if (y->left != nullptr)
    {
        x = y->left;
    }
    else
    {
        x = y->right;
    }
    if (x != nullptr)
    {
        x->parent = y->parent;
    }
    if (y->parent == nullptr)
    {
        root = x;
    }
    else if (y->parent->left == y)
    {
        y->parent->left = x;
    }
    else
    {
        y->parent->right = x;
    }
    if (y != k)
    {
        k->update(y);
    }
    return true;
}
TreeNode *BST::minforsuccessor(TreeNode *N)
{
    while (N->left != nullptr)
    {
        N = N->left;
    }
    return N;
}
