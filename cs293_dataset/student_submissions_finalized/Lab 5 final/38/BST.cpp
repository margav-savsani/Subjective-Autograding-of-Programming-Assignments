#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

int maxim(int a, int b)
{
    if (a > b) return a;
    else return b;
}

//Updates Height recursively
void Update_Height(TreeNode* Main_Node)
{
    if (Main_Node->left == nullptr)
    {
        if (Main_Node->right == nullptr)
        {
            if (Main_Node->height == 0) return;
            else 
            {
                Main_Node->height = 0;
                if (Main_Node->parent == nullptr) return;
                else Update_Height(Main_Node->parent);
            }
        }
        else
        {
            if (Main_Node->height == Main_Node->right->height + 1) return;
            else 
            {
                Main_Node->height = Main_Node->right->height + 1;
                if (Main_Node->parent == nullptr) return;
                else Update_Height(Main_Node->parent);
            }
        }
    }
    else
    {
        if (Main_Node->right == nullptr)
        {
            if (Main_Node->height = Main_Node->left->height + 1) return;
            else 
            {
                Main_Node->height = Main_Node->left->height + 1;
                if (Main_Node->parent == nullptr) return;
                else Update_Height(Main_Node->parent);
            }
        }
        else 
        {
            if (Main_Node->height == maxim(Main_Node->left->height, Main_Node->right->height) + 1) return;
            else 
            {
                Main_Node->height = maxim(Main_Node->left->height, Main_Node->right->height) + 1;
                if (Main_Node->parent == nullptr) return;
                else Update_Height(Main_Node->parent);
            }
        }
    }
}


bool BST::insert(int jrnyCode, int price)
{
    // Inserting Node iteratively
    
    TreeNode *A;
    A = new TreeNode(jrnyCode, price);
    TreeNode *Current_Node = root;
    if (Current_Node == nullptr) root = A;
    else 
    {
        while(true)
        {
            if (BSTLessThan(Current_Node, A))
            {
                if (Current_Node->right == nullptr)
                {
                    Current_Node->right = A;
                    A->parent = Current_Node;
                    Update_Height(Current_Node);
                    return true;
                }
                else 
                {
                    Current_Node = Current_Node->right;
                }
            }
            else if (BSTLessThan(A, Current_Node))
            {
                if (Current_Node->left == nullptr)
                {
                    Current_Node->left = A;
                    A->parent = Current_Node;
                    Update_Height(Current_Node);
                    return true;
                }
                else Current_Node = Current_Node->left;
            }
            else return false;
        }
    }

    
    return true;
}

int BST::find(int jrnyCode)
//Finding node iteratively
{
    TreeNode a(jrnyCode, 0);
    TreeNode *Present = root;
    while(Present != nullptr)
    {
        if (BSTLessThan(Present, &a))
        {
            Present = Present->right;
        }
        else if (BSTLessThan(&a, Present))
        {
            Present = Present->left;
        }
        else return Present->getPrice();
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
