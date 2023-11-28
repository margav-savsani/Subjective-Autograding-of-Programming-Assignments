#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif
int BST::Calculate_height(TreeNode *x)
{
    if (x == nullptr)
    {                                            //height of nullptr is 0
        return 0;
    }
    else
    {
        if (x->left == nullptr && x->right == nullptr)
        {
            return 1;
        }
        else if (x->left != nullptr && x->right == nullptr)
        {
            return 1 + Calculate_height(x->left);    //recursively calculating height 
        }
        else if (x->left == nullptr && x->right != nullptr)
        {
            return 1 + Calculate_height(x->right);
        }
        else
        {
            return 1 + max(Calculate_height(x->left), Calculate_height(x->right));
        }
    }
}

// Returns true on successful insertion in BST. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the BST

bool BST::insert(int jrnyCode, int price)
{
    TreeNode *res = new TreeNode(0, 0);
    TreeNode *y = nullptr;

    if (root == nullptr) // inserting at root
    {
        root = new TreeNode(jrnyCode, price);
        root->height = 1;

        return true;
    }

    else
    {

        TreeNode *x = root;
        /*if (check(JourneyCode, price, x)) // if a journey code is present , insertion failed
        {
            return false;
        }*/
        TreeNode *n1 = new TreeNode(jrnyCode, price);
        while (x != nullptr) // if prices are same insert at right
        {

            if (BSTLessThan(x, n1))
            {
                y = x;
                x = x->right;
            }
            else
            {
                y = x;
                x = x->left;
            }
        }
        if (BSTLessThan(n1, y))
        {
            // res->parent = y;
            // y->left = res;
            // res->JourneyCode = jrnyCode;
            // res->price = price;

            // res->updateParentChild(y,true);
            updateBSTParentChild(res, y, true);
            res->JourneyCode = jrnyCode;
            res->price = price;
            res->height = 1;
        }
        else
        {
            // res->parent = y;
            // y->right = res;

            updateBSTParentChild(res, y, false);
            res->height = 1;
            res->JourneyCode = jrnyCode;
            res->price = price;
        }
    }
    while (res->parent != nullptr)
    {
        int x;
        x = res->parent->height;
        if (Calculate_height(res->parent) == x) //finding a parent whose height remained the same after insertion 
        {
            break;
        }
        res->parent->height = Calculate_height(res->parent);
        res = res->parent;
    }

    //  cout<<Calculate_height(root)<<endl;
    // return true;

    return true;
}
// Implement insertion in BST

// You MUST use only BSTLessThan to compare two journey codes.  You
// can create a new node containing the journey code to be inserted
// and invoke BSTLessThan on the current node in the tree that you
// are inspecting and the new node to do your comparison.

// REMEMBER to update the heights of appropriate nodes in the tree
// after an insertion.

// We use "return true" below to enable compilation.  Change this as you
// see fit.

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
    TreeNode *x = root; 
    TreeNode *garb = new TreeNode(jrnyCode, 500); //creating a garbage pointer

    while (x != nullptr)
    {

        // // if (!(BSTLessThan(x,garb) && !BSTLessThan(garb,x)))
        // if(!(BSTLessThan(x,garb) ))
        // {
        //   cout<<"reached"<<endl;
        //   if(!(BSTLessThan(garb,x))){
        //     cout<<"YOU FOOL";
        //     return 1;}
        // }
        if (!(BSTLessThan(garb, x) || BSTLessThan(x, garb))) //equality check
        {
            /* code */
            return 1;
        }

        else if (BSTLessThan(garb, x))
        {
            x = x->left;
            // cout << "reaching" << endl;
        }
        else
        {
            x = x->right;
            // cout<<"reaching"<<endl;
        }
    }
    return -1;
}
TreeNode *BST::predecessor(TreeNode *z) // finding the largest number less than the given node
{

    if (z->left != nullptr)
    {
        TreeNode *t1 = z->left;
        while (t1->right != nullptr)
        {
            t1 = t1->right;
        }

        return t1;
    }
    if (z->parent == nullptr)
    {
        return nullptr;
    }
    TreeNode *t1 = z->parent;
    TreeNode *t2 = z;
    while (t1 != nullptr)
    {
        if (t1->right == t2)
        {
            return t1;
        }
        t2 = t1;
        t1 = t1->parent;
    }
    return nullptr;
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

    // return true;
    if (find(jrnyCode))
    {
        TreeNode *x = root;
        TreeNode *garb = new TreeNode(jrnyCode, 0);
        while (x != nullptr)
        {

            if (!(BSTLessThan(garb, x) || BSTLessThan(x, garb)))
            {
                if (x->left == nullptr && x->right == nullptr)
                {

                    TreeNode *Y = x->parent;
                    if (Y != nullptr)
                    {
                        if (x == Y->left)
                        {
                            Y->left = nullptr;
                        }
                        else if (x == Y->right)
                        {
                            Y->right = nullptr;
                        }
                    }
                    else
                    {
                        root = nullptr;
                    }
                }
                else if (x->right == nullptr)
                {
                    TreeNode *t = x->left;
                    if (x->parent != nullptr)
                    {
                        TreeNode *t2 = x->parent;
                        if (x == t2->left)
                        {
                            t->parent = t2;
                            t2->left = t;
                        }
                        else
                        {
                            t->parent = t2;
                            t2->right = t;
                        }
                    }
                    else
                    {

                        root = t;
                    }
                }
                else if (x->left == nullptr)
                {
                    TreeNode *t = x->right;
                    if (x->parent != nullptr)
                    {
                        TreeNode *t2 = x->parent;
                        if (x == t2->left)
                        {
                            t->parent = t2;
                            t2->left = t;
                        }
                        else
                        {
                            t->parent = t2;
                            t2->right = t;
                        }
                    }
                    else
                    {

                        root = t;
                    }
                }
                else
                {

                    TreeNode *p = predecessor(x);
                    x->JourneyCode = p->JourneyCode;
                    x->price = p->price;
                    if (p->left == nullptr && p->right == nullptr)
                    {
                        TreeNode *Y = p->parent;
                        if (p == Y->left)
                        {
                            Y->left = nullptr;
                        }
                        else if (p == Y->right)
                        {
                            Y->right = nullptr;
                        }
                    }
                    else
                    {
                        TreeNode *z = p->parent;
                        TreeNode *y = p->left;
                        if (z->right == p)
                        {
                            y->parent = z;
                            z->right = y;
                        }
                        else
                        {
                            y->parent = z;
                            z->left = y;
                        }
                    }
                }
                return true;
            }

            //
            if (BSTLessThan(garb, x))
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }
    }

    return false;
}
// }
