#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif



bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
//This function is the rotate left left case, i.e. parent is left of grandparent and current is left of parent
{
    TreeNode *greatGrandParentNode = grandParentNode->parent;

    bool isGPLeftChild;
    if (greatGrandParentNode != nullptr)
    {
        if (greatGrandParentNode->left == grandParentNode)
        {
            isGPLeftChild = true;
        }
        else if (greatGrandParentNode->right == grandParentNode)
        {
            isGPLeftChild = false;
        }
        else
        {
            cerr << "Unexpected condition encountered!" << endl;
            return false;
        }
    }
    else
    {
        root = parentNode;
    }
    
    TreeNode *T3 = parentNode->right;

    updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);

    updateAVLParentChild(currNode, parentNode, true);

    updateAVLParentChild(grandParentNode, parentNode, false);

    updateAVLParentChild(T3, grandParentNode, true);

    
    return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
//This function is the rotate left left case, i.e. parent is left of grandparent and current is right of parent
{
    
    TreeNode *greatGrandParentNode = grandParentNode->parent;

    bool isGPLeftChild;
    if (greatGrandParentNode != nullptr)
    {
        if (greatGrandParentNode->left == grandParentNode)
        {
            isGPLeftChild = true;
        }
        else if (greatGrandParentNode->right == grandParentNode)
        {
            isGPLeftChild = false;
        }
        else
        {
            cerr << "Unexpected condition encountered!" << endl;
            return false;
        }
    }
    else 
    {
        root = currNode;
    }
    TreeNode *T2 = currNode->left;

    TreeNode *T3 = currNode->right;

    updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

    updateAVLParentChild(parentNode, currNode, true);

    updateAVLParentChild(grandParentNode, currNode, false);

    updateAVLParentChild(T2, parentNode, false);

    updateAVLParentChild(T3, grandParentNode, true);

    return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
//This function is the rotate right left case, i.e. parent is right of grandparent and current is left of parent
{
    TreeNode *greatGrandParentNode = grandParentNode->parent;

    bool isGPLeftChild;
    if (greatGrandParentNode != nullptr)
    {
        if (greatGrandParentNode->left == grandParentNode)
        {
            isGPLeftChild = true;
        }
        else if (greatGrandParentNode->right == grandParentNode)
        {
            isGPLeftChild = false;
        }
        else
        {
            cerr << "Unexpected condition encountered!" << endl;
            return false;
        }
    }
    else 
    {
        root = currNode;
    }
    TreeNode *T3 = currNode->left;

    TreeNode *T2 = currNode->right;

    updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

    updateAVLParentChild(parentNode, currNode, false);

    updateAVLParentChild(grandParentNode, currNode, true);

    updateAVLParentChild(T2, parentNode, true);

    updateAVLParentChild(T3, grandParentNode, false);

    return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
//This function is the rotate right right case, i.e. parent is right of grandparent and current is right of parent
{
    TreeNode *greatGrandParentNode = grandParentNode->parent;


    bool isGPLeftChild;
    if (greatGrandParentNode != nullptr)
    {
        
        if (greatGrandParentNode->left == grandParentNode)
        {
            isGPLeftChild = true;
        }
        else if (greatGrandParentNode->right == grandParentNode)
        {
            isGPLeftChild = false;
        }
        else
        {
            cerr << "Unexpected condition encountered!" << endl;
            return false;
        }
    }
    else
    {
        root = parentNode;
    }
    
    TreeNode *T3 = parentNode->left;

    updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);

    updateAVLParentChild(currNode, parentNode, false);

    updateAVLParentChild(grandParentNode, parentNode, true);

    updateAVLParentChild(T3, grandParentNode, false);

    
    return true;
}


bool Check_Height_Balanced(TreeNode *Node)
//This Function checks the Height balance of Node Assuming It's child are Height Balanced
{
    int left, right;
    if (Node->left == nullptr) left = -1;
    else left = Node->left->height;

    if (Node->right == nullptr) right = -1;
    else right = Node->right->height;

    return (abs(left - right) < 2);
}

//Returns Maximum of a and b
int MAXIM(int a, int b)
{
    if (a > b) return a;
    else return b;
}

// Returns Height even for nullptr Node
int Height(TreeNode *Node)
{
    if (Node == nullptr) return -1;
    else return Node->height;
}


void Update_Height(AVLTree *TREE, TreeNode *Present_Node)
//It updates height of every Node which is ansestor of the added node
//It is done recursively, not iteratively
{
    if (Check_Height_Balanced(Present_Node))
    {
        if (Height(Present_Node) == MAXIM(Height(Present_Node->right), Height(Present_Node->left)) + 1) return;
        else 
        {
            Present_Node->height = MAXIM(Height(Present_Node->left), Height(Present_Node->right)) + 1;
            if (Present_Node->parent == nullptr) return;
            else 
            {
                Update_Height(TREE, Present_Node->parent);
                return ;
            }
        }
    }
    else 
    {
        bool first_left = (Height(Present_Node->left) > Height(Present_Node->right));
        bool second_left;
        if (first_left)
        {
            second_left = (Height(Present_Node->left->left) > Height(Present_Node->left->right));
        }
        else 
        {
            second_left = (Height(Present_Node->right->left) > Height(Present_Node->right->right));
        }
        TreeNode *grandParentNode = Present_Node;
        TreeNode *ParentNode, *CurrNode;
        if (first_left)
        {
            ParentNode = grandParentNode->left;
            if (second_left) 
            {
                CurrNode = ParentNode->left;
                TREE->rotateLeftLeft(CurrNode, ParentNode, grandParentNode);
            }
            else
            {
                CurrNode = ParentNode->right;
                TREE->rotateLeftRight(CurrNode, ParentNode, grandParentNode);
            }
        }
        else 
        {
            ParentNode = grandParentNode->right;
            if (second_left) 
            {
                CurrNode = ParentNode->left;
                TREE->rotateRightLeft(CurrNode, ParentNode, grandParentNode);
            }
            else
            {
                CurrNode = ParentNode->right;
                TREE->rotateRightRight(CurrNode, ParentNode, grandParentNode);
            }
        }
        Update_Height(TREE, grandParentNode);
        Update_Height(TREE, ParentNode);
        Update_Height(TREE, CurrNode);
    }
}

bool AVLTree::insert(int jrnyCode, int price)
//Inserting an element iteratively
{
    if (root == nullptr)
    {
        root = new TreeNode(jrnyCode, price);
    }
    else 
    {
        TreeNode *Present = root;
        TreeNode *A;
        A = new TreeNode(jrnyCode, price);
        
        while(true)
        {
            if (AVLLessThan(Present, A))
            {
                if (Present->right == nullptr)
                {
                    Present->right = A;
                    A->parent = Present;
                    Update_Height(this, Present);
                    //Updating Height recursively
                    return true;
                }
                else Present = Present->right;
            }
            else if (AVLLessThan(A, Present))
            {
                if (Present->left == nullptr)
                {
                    Present->left = A;
                    A->parent = Present;
                    Update_Height(this, Present);
                    return true;
                }
                else Present = Present->left;
            }
            else return false;
        }
    }
    return true;
}


int AVLTree::find(int jrnyCode)
//Finding element iteratively
{
    TreeNode a(jrnyCode, 0);
    TreeNode *Present = root;
    while (Present != nullptr)
    {
        if (AVLLessThan(Present, &a))
        {
            Present = Present->right;
        }
        else if (AVLLessThan(&a, Present))
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

// Returns true on successful deletion of the entry in AVL tree with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the AVL tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::remove(int jrnyCode)
{
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

    // You MUST use only AVLLessThan to compare two journey codes.  You
    // can create a new node containing the journey code to be searched
    // (along with some arbitrary price) and invoke AVLLessThan on the
    // current node in the tree that you are inspecting and the new node
    // to do your comparison.

    // REMEMBER to update the height of appropriate nodes in the tree
    // after a successful deletion.

    // We use "return true" below to enable compilation.  Change this as you
    // see fit.
    return true;
}
