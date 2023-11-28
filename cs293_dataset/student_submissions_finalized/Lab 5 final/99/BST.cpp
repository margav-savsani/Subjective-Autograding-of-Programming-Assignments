#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

bool BST::updatePathLengths(TreeNode * start)
{
    if (start == nullptr) return 1;
    while (start != nullptr)
    {
        start->updateHeight();
        start = start->parent;
    }
    return 1;
}

// Returns true on successful insertion in BST. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the BST

bool BST::insert(int jrnyCode, int price)
{
    if (find(jrnyCode) >= 0) return 0;
    TreeNode * newnode = new TreeNode(jrnyCode, price);
    if (root == nullptr) 
    {
        root = newnode;
        updateBSTParentChild(newnode, nullptr, true);
        return 1;
    }
    TreeNode * where = root;
    bool inserted = 0;
    while (inserted == 0)
    {
        if (BSTLessThan(where, newnode))
        {
            if (where->right == nullptr)
            {
                updateBSTParentChild(newnode, where, false);
                inserted = 1;
            }
            else where = where->right;
        }
        else 
        {
            if (where->left == nullptr)
            {
                updateBSTParentChild(newnode, where, true);
                inserted = 1;
            }
            else where = where->left;
        }
    }
    bool x = updatePathLengths(newnode);
    if (!x) return 0;
    return inserted;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
    TreeNode * newnode = new TreeNode(jrnyCode, 0);
    if (root == nullptr) return -1;
    TreeNode * spot = root;
    int found = -1;
    while (found == -1)
    {
        if (spot == nullptr) return -1;
        else
        {
            if (BSTLessThan(spot, newnode)) spot = spot->right;
            else if (BSTLessThan(newnode, spot)) spot = spot->left;
            else return spot->getprice();
        }
    }
    return found;
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in BST with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the BST have the same journey
// code, and journey code is the key for insertion and finding in the BST.

TreeNode * BST::minimum(TreeNode * start)
{
    if (start == nullptr) return nullptr;
    while (start->left != nullptr)
    {
        start = start->left;
    }
    return start;
}

TreeNode * BST::successor(TreeNode * x)
{
    if (x == nullptr) return nullptr;
    if (x->right != nullptr) return minimum(x->right);
    TreeNode * p = x->parent;
    if (x == p->left) return p;
    while (p != nullptr && x == p->right)
    {
        x = p;
        p = p->parent;
    }
    return p;
}

bool BST::remove(int jrnyCode)
{
    TreeNode * todelete = new TreeNode(jrnyCode, 0);
    TreeNode * spot = root;
    TreeNode * prnt = nullptr;
    bool deleted = 0;
    while (deleted == 0)
    {
        if (spot == nullptr) return 0;
        else if (BSTLessThan(spot, todelete))
        {
            prnt = spot;
            spot = spot->right;
        }
        else if (BSTLessThan(todelete, spot))
        {
            prnt = spot;
            spot = spot->left;
        }
        else
        {
            if (spot->left == nullptr && spot->right == nullptr)
            {
                if (spot == root) root = nullptr;
                else if (spot == prnt->left) prnt->left = nullptr;
                else prnt->right = nullptr;
                deleted = 1;
            }
            else if (spot->left == nullptr)
            {
                if (spot == root) root = spot->right;
                else if (spot == prnt->left) prnt->left = spot->right;
                else prnt->right = spot->right;
                deleted = 1;
            }
            else if (spot->right == nullptr)
            {
                if (spot == root) root = spot->left;
                else if (spot == prnt->left) prnt->left = spot->left;
                else prnt->right = spot->left;
                deleted = 1;
            }
            else
            {
                TreeNode * succ = successor(spot);
                remove(succ->getJourneyCode());
                if (spot == root) root = succ;
                else if (spot == prnt->left) prnt->left = succ;
                else prnt->right = succ;
                succ->left = spot->left;
                succ->right = spot->right;
                succ->updateHeight();
                deleted = 1;
            }
        }
    }
    if (prnt != nullptr) updatePathLengths(prnt);
    return deleted;
}


