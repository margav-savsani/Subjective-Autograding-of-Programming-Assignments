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
// Prof. Garg's lectures           Our code
// ---------------------           --------
//   x                             currNode
//   y                             parentNode
//   z                             grandParent
//
// Recall also that z (grandParent) is the lowest node in the path from
// the root to the inserted node or to the deleted node (as the case may be)
// where the balance factor has either become < -1 or > 1.
// To find what x (currNode) and y (parentNode) should be, you need to
// recall Prof. Garg's lectures.
// These are slightly differently defined when inserting nodes and when
// deleting nodes

/*
        z
       / \
      y   T4
     / \
    x   T3
   / \
  T1  T2
*/
bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParent)
{
    TreeNode *greatGrandParent = grandParent->parent;
    bool isGPLeftChild = 0;
    if (greatGrandParent != nullptr)
    {
        if (greatGrandParent->left == grandParent) isGPLeftChild = true;
        else if (greatGrandParent->right == grandParent) isGPLeftChild = false;
        else 
        {
            cerr << "Unexpected condition encountered!" << endl;
            return false;
        }
        // y is at the top
        updateAVLParentChild(parentNode, greatGrandParent, isGPLeftChild);
    }
    else 
    {
        root = parentNode; 
        parentNode->parent = nullptr;
    }
    TreeNode *T3 = parentNode->right;
    // x is the left child of y
    updateAVLParentChild(currNode, parentNode, true);
    // z is the right child of y
    updateAVLParentChild(grandParent, parentNode, false);
    // T3 is the left child of z
    updateAVLParentChild(T3, grandParent, true);
    return true;
}
/*
        z                x             
       / \             /   \ 
      y   T4          y     z 
     / \             / \   / \
    T1  x           T1 T2 T3 T4
       / \     
      T2  T3  
*/
bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParent)
{
    TreeNode *greatGrandParent = grandParent->parent;
    bool isGPLeftChild = 0;
    if (greatGrandParent != nullptr)
    {
        if (greatGrandParent->left == grandParent) isGPLeftChild = true;
        else if (greatGrandParent->right == grandParent) isGPLeftChild = false;
        else 
        {
            cerr << "Unexpected condition encountered!" << endl;
            return false;
        }
        // x is at the top
        updateAVLParentChild(currNode, greatGrandParent, isGPLeftChild);
    }
    else 
    {
        root = currNode; 
        currNode->parent = nullptr;
    }
    // T2 and T3 are the children of x
    TreeNode *T2 = currNode->left;
    TreeNode *T3 = currNode->right;
    // y is the left child of x
    updateAVLParentChild(parentNode, currNode, true);
    // z is the right child of x
    updateAVLParentChild(grandParent, currNode, false);
    // T2 is the right child of y
    updateAVLParentChild(T2, parentNode, false);
    // T3 is the left child of z
    updateAVLParentChild(T3, grandParent, true);
    return true;
}
/*
        z                 x
       / \              /   \
      T1  y            z     y 
         / \          / \   / \
        x   T4       T1 T2 T3 T4
       / \         
      T2  T3          
*/
bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParent)
{
    TreeNode *greatGrandParent = grandParent->parent;
    bool isGPLeftChild = 0;
    if (greatGrandParent != nullptr)
    {
        if (greatGrandParent->left == grandParent) isGPLeftChild = true;
        else if (greatGrandParent->right == grandParent) isGPLeftChild = false;
        else 
        {
            cerr << "Unexpected condition encountered!" << endl;
            return false;
        }
        // x is at the top
        updateAVLParentChild(currNode, greatGrandParent, isGPLeftChild);
    }
    else 
    {
        root = currNode; 
        currNode->parent = nullptr;
    }
    // T2 and T3 are the children of x
    TreeNode * T2 = currNode->left;
    TreeNode * T3 = currNode->right;
    // z is the left child of x
    updateAVLParentChild(grandParent, currNode, true);
    // y is the right child of x
    updateAVLParentChild(parentNode, currNode, false);
    // T2 is the right child of z
    updateAVLParentChild(T2, grandParent, false);
    // T3 is the left child of y
    updateAVLParentChild(T3, parentNode, true);
    return true;
}
/*
    z
   / \
  T1  y
     / \
    T2  x
       / \
      T3  T4
*/
bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParent)
{
    TreeNode * greatGrandParent = grandParent->parent;
    bool isGPLeftChild = 0;
    if (greatGrandParent != nullptr)
    {
        if (greatGrandParent->left == grandParent) isGPLeftChild = true;   
        else if (greatGrandParent->right == grandParent) isGPLeftChild = false;
        else 
        {
            cerr << "Unexpected condition encountered!" << endl;
            return false;
        }
        // y is at the top
        updateAVLParentChild(parentNode, greatGrandParent, isGPLeftChild);
    }
    else 
    {
        root = parentNode; 
        parentNode->parent = nullptr;
    }
    TreeNode * T2 = parentNode->left;
    // x is the right child of y
    //updateAVLParentChild(currNode, parentNode, false);
    // T2 is the right child of z
    updateAVLParentChild(T2, grandParent, false);
    // z is the left child of y
    updateAVLParentChild(grandParent, parentNode, true);
    return true;
}

bool AVLTree::updatePathLengths(TreeNode * start)
{
    if (start == nullptr) return 1;
    while (start != nullptr)
    {
        start->updateHeight();
        start = start->parent;
    }
    return 1;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::restoreBalance(TreeNode * where)
{
    if (where == nullptr) return 0;
    if (where->imbalance() < -1)
    {
        // rotate rightright
        if ((where->right)->left == nullptr)
        {
            TreeNode * grandparent = where;
            TreeNode * parent = where->right;
            TreeNode * currnode = (where->right)->right;
            rotateRightRight(currnode, parent, grandparent);
            grandparent->updateHeight();
            currnode->updateHeight();
            updatePathLengths(parent);
            return 1;
        }
        // rotate rightleft
        else if ((where->right)->right == nullptr)
        {
            TreeNode * grandparent = where;
            TreeNode * parent = where->right;
            TreeNode * currnode = (where->right)->left;
            rotateRightLeft(currnode, parent, grandparent);
            grandparent->updateHeight();
            parent->updateHeight();
            updatePathLengths(currnode);
            return 1;
        }
        // rotate rightright
        else if (((where->right)->left)->height <= ((where->right)->right)->height)
        {
            TreeNode * grandparent = where;
            TreeNode * parent = where->right;
            TreeNode * currnode = (where->right)->right;
            rotateRightRight(currnode, parent, grandparent);
            grandparent->updateHeight();
            currnode->updateHeight();
            updatePathLengths(parent);
            return 1;
        }
        // rotate rightleft
        else if (((where->right)->right)->height < ((where->right)->left)->height)
        {
            TreeNode * grandparent = where;
            TreeNode * parent = where->right;
            TreeNode * currnode = (where->right)->left;
            rotateRightLeft(currnode, parent, grandparent);
            grandparent->updateHeight();
            parent->updateHeight();
            updatePathLengths(currnode);
            return 1;
        }
    }
    else if (where->imbalance() > 1)
    {
        // rotate leftright
        if ((where->left)->left == nullptr)
        {
            TreeNode * grandparent = where;
            TreeNode * parent = where->left;
            TreeNode * currnode = (where->left)->right;
            rotateLeftRight(currnode, parent, grandparent);
            parent->updateHeight();
            grandparent->updateHeight();
            updatePathLengths(currnode);
            return 1;
        }
        // rotate leftleft
        else if ((where->left)->right == nullptr)
        {
            TreeNode * grandparent = where;
            TreeNode * parent = where->left;
            TreeNode * currnode = (where->left)->left;
            rotateLeftLeft(currnode, parent, grandparent);
            currnode->updateHeight();
            grandparent->updateHeight();
            updatePathLengths(parent);
            return 1;
        }
        // rotate leftright
        else if (((where->left)->left)->height < ((where->left)->right)->height)
        {
            TreeNode * grandparent = where;
            TreeNode * parent = where->left;
            TreeNode * currnode = (where->left)->right;
            rotateLeftRight(currnode, parent, grandparent);
            parent->updateHeight();
            grandparent->updateHeight();
            updatePathLengths(currnode);
            return 1;
        }
        // rotate leftleft
        else if (((where->left)->right)->height <= ((where->left)->left)->height)
        {
            TreeNode * grandparent = where;
            TreeNode * parent = where->left;
            TreeNode * currnode = (where->left)->left;
            rotateLeftLeft(currnode, parent, grandparent);
            currnode->updateHeight();
            grandparent->updateHeight();
            updatePathLengths(parent);
            return 1;
        }
    }
    return 0;
}

bool AVLTree::insert(int jrnyCode, int price)
{
    if (find(jrnyCode) >= 0) return 0;
    TreeNode * newnode = new TreeNode(jrnyCode, price);
    if (root == nullptr)
    {
        root = newnode;
        updateAVLParentChild(newnode, nullptr, true);
        return 1;
    }
    TreeNode * where = root;
    bool inserted = 0;
    while (inserted == 0 && where != nullptr)
    {
        if (AVLLessThan(where, newnode))
        {
            if (where->right == nullptr)
            {
                updateAVLParentChild(newnode, where, false);
                inserted = 1;
            }
            else where = where->right;
        }
        else
        {
            if (where->left == nullptr)
            {
                updateAVLParentChild(newnode, where, true);
                inserted = 1;
            }
            else where = where->left;
        }
    }
    bool x = updatePathLengths(newnode);
    if (!x) return 0;
    while (where != nullptr)
    {
        if (restoreBalance(where)) break;
        else where = where->parent;
    }
    return inserted;
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
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
            if (AVLLessThan(spot, newnode)) spot = spot->right;
            else if (AVLLessThan(newnode, spot)) spot = spot->left;
            else return spot->getprice();
        }
    }
    return found;
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================
// Returns true on successful deletion of the entry in AVL tree with
// matching journey code. Returns false if it cannot find any such element.
// You may assume that no two elements in the AVL tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.
TreeNode * AVLTree::minimum(TreeNode * start)
{
    if (start == nullptr) return nullptr;
    while (start->left != nullptr)
    {
        start = start->left;
    }
    return start;
}

TreeNode * AVLTree::successor(TreeNode * x)
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

bool AVLTree::remove(int jrnyCode)
{
    if (find(jrnyCode) == -1) return 0;
    TreeNode * todelete = new TreeNode(jrnyCode, 0);
    TreeNode * spot = root;
    TreeNode * prnt = nullptr;
    bool deleted = 0;
    while (deleted == 0)
    {
        if (AVLLessThan(spot, todelete))
        {
            prnt = spot;
            spot = spot->right;
        }
        else if (AVLLessThan(todelete, spot))
        {
            prnt = spot;
            spot = spot->left;
        }
        else
        {
            if (spot->left == nullptr && spot->right == nullptr)
            {
                if (spot == root) root = nullptr;
                else if (spot == prnt->left) updateAVLParentChild(nullptr, prnt, true);
                else updateAVLParentChild(nullptr, prnt, false);
                if (prnt != nullptr) prnt->updateHeight();
                deleted = 1;
            }
            else if (spot->left == nullptr)
            {
                if (spot == root) {root = spot->right; updateAVLParentChild(spot->right, nullptr, true);}
                else if (spot == prnt->left) prnt->left = spot->right;
                else prnt->right = spot->right;
                if (prnt != nullptr) prnt->updateHeight();
                deleted = 1;
            }
            else if (spot->right == nullptr)
            {
                if (spot == root) {root = spot->left; updateAVLParentChild(spot->left, nullptr, true);}
                else if (spot == prnt->left) updateAVLParentChild(spot->left, prnt, true);
                else updateAVLParentChild(spot->left, prnt, false);
                if (prnt != nullptr) prnt->updateHeight();
                deleted = 1;
            }
            else
            {
                TreeNode * succ = successor(spot);
                remove(succ->getJourneyCode());
                if (spot == root) {root = succ; updateAVLParentChild(succ, nullptr, true);}
                else if (spot == prnt->left) updateAVLParentChild(succ, prnt, true);
                else updateAVLParentChild(succ, prnt, false);
                updateAVLParentChild(spot->left, succ, true);
                updateAVLParentChild(spot->right, succ, false);
                succ->left = spot->left;
                succ->right = spot->right;
                succ->updateHeight();
                deleted = 1;
            }
        }
    }
    while (prnt != nullptr)
    {
        restoreBalance(prnt);
        prnt = prnt->parent;
    }
    return deleted;
}