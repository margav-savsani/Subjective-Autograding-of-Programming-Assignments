#include "AVL.h"

#include <iostream>
#include <stdlib.h>


bool AVLTree::rotate(TreeNode* currNode)
{
    TreeNode* parentNode;
    TreeNode* grandParentNode;
    if (currNode != nullptr && (parentNode = currNode->parent) != nullptr && (grandParentNode = parentNode->parent) != nullptr) {
        if ((currNode == parentNode->left) == (parentNode == grandParentNode->left)) {
            // LL or RR
            bool isLL = (currNode == parentNode->left);
            TreeNode* greatGrandParentNode = grandParentNode->parent;
            if (greatGrandParentNode != nullptr) {
                bool isGPLeftChid = (greatGrandParentNode->left == grandParentNode);
                updateAVLParentChild(parentNode, greatGrandParentNode, isGLLeftChild);
            }
            else {
                root = parentNode;
            }
            updateAVLParentChild(grandParentNode, parentNode, !isLL);

            TreeNode* midTree = (isLL ? parentNode->right : parentNode->left);
            updateAVLParentChild(midTree, grandParentNode, isLL);
            return true;
        }
        else {
            // LR or RL
            bool isLR = (currNode == parentNode->right);
            TreeNode* greatGrandParentNode = grandParentNode->parent;
            if (greatGrandParentNode != nullptr) {
                bool isGPLeftChid = (greatGrandParentNode->left == grandParentNode);
                updateAVLParentChild(parentNode, greatGrandParentNode, isGLLeftChild);
            }
            else {
                root = parentNode;
            }
            updateAVLParentChild(grandParentNode, currNode, !isLR);
            updateAVLParentChild(parentNode, currNode, isLR);

            TreeNode* midTree = (isLR ? currNode->right : currNode->Left);
            updateAVLParentChild(midTree, grandParentNode, isLR);
            return true;
        }
    }
    else {
        return false;
    }

bool AVLTree::rotateLeftLeft(TreeNode* currNode, TreeNode* parentNode, TreeNode* grandParentNode)
{
    return rotate(currNode);
}

bool AVLTree::rotateLeftRight(TreeNode* currNode, TreeNode* parentNode, TreeNode* grandParentNode)
{
    return rotate(currNode);
}

bool AVLTree::rotateRightLeft(TreeNode* currNode, TreeNode* parent, TreeNode* grandParent)
{
    return rotate(currNode);
}

bool AVLTree::rotateRightRight(TreeNode* currNode, TreeNode* parent, TreeNode* grandParent)
{
    return rotate(currNode);
}

void AVLTree::recursiveDelete(TreeNode* currNode)
{
    if (currNode != nullptr) {
        TreeNode* leftChild = currNode->left;
        TreeNode* rightChild = currNode->right;
    
        delete currNode;
        recursiveDelete(leftChild);
        recursiveDelete(rightChild);
    }
    return;
}
    
bool AVLTree::AVLLessThan(TreeNode* leftArg, TreeNode* rightArg)
{                                                                              
    if ((leftArg != nullptr) && (rightArg != nullptr)) {
        bool result = (*leftArg < *rightArg);
        totalComparisonCost += perComparisonCost;
    }
    else {
        std::cerr << "Unexpected exceptional condition!\n";
        exit(-1);
    }
}

void updateAVLParentChild(TreeNode* childNode, TreeNode* parentNode, bool isLeftChild)
{                                                                              
    if ((childNode != nullptr) && (parentNode != nullptr)) {
        if (childNode->parent != nullptr) {
            if (childNode->parent->left == childNode)
                childNode->parent->left = nullptr;
            else
                childNode->parent->right = nullptr;
        }
        childNode->updateParentChild(parentNode, isLeftChild);
        totalParentChildUpdateCost += perParentChildUpdateCost;
    }
    else if ((childNode == nullptr) && (parentNode != nullptr)) {
        std::cerr << "WARNING: updateAVLParentChild has childNode as nullptr\n";
        if (isLeftChild) {
            parentNode->left = nullptr;
        }
        else {
            parentNode->right = nullptr;
        }
        // No updating of totalParentChildUpdateCost needed here
    }
    else if ((childNode != nullptr) && (parentNode == nullptr)) {
        std::cerr << "WARNING: updateAVLParentChild has parentNode as nullptr\n";
        if (childNode->parent != nullptr) {
            if (childNode->parent->left == childNode)
                childNode->parent->left = nullptr;
            else
                childNode->parent->right = nullptr;
        }
        childNode->parent = nullptr;
        // No updating of totalParentChildUpdateCost needed here
    }
    else {
        // both childNode and parentNode are nullptr
        // Nothing to do really
        // No updating of totalParentChildUpdateCost needed here
        ;
    }
    return;
}

// Constructors
AVLTree(int perCompCost, int perParntChldUpdCost)
    : root(nullptr), totalComparisonCost(0), totalParentChildUpdateCost(0), perComparisonCost(perCompCost), perParentChildUpdateCost(perParntChldUpdCost)
{
}

AVLTree(TreeNode *newRoot, int perCompCost, int perParntChldUpdCost)
    : root(newRoot), totalComparisonCost(0), totalParentChildUpdateCost(0), perComparisonCost(perCompCost), perParentChildUpdateCost(perParntChldUpdCost)
{
}
    
// Destructor
~AVLTree()
{
    recursiveDelete(root);
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.
bool AVLTree::insert(int jrnyCode, int price)
{
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

    // You MUST use only AVLLessThan to compare two journey codes.    You
    // can create a new node containing the journey code to be inserted
    // and invoke AVLLessThan on the current node in the tree that you
    // are inspecting and the new node to do your comparison.

    // REMEMBER to update the heights of appropriate nodes in the tree
    // after an insertion.
    
    // We use "return true" below to enable compilation.    Change this as you
    // see fit.
    return true;
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
{
    // Implement find in AVL tree.
    // This is really no different from finding in a binary search tree.
    // This operation cannot cause any balance factor disturbances.

    // You MUST use only AVLLessThan to compare two journey codes.    You
    // can create a new node containing the journey code to be searched
    // (along with some arbitrary price) and invoke AVLLessThan on the
    // current node in the tree that you are inspecting and the new node
    // to do your comparison.

    // We use "return -1" below to enable compilation.    Change this as you
    // see fit.
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

    // You MUST use only AVLLessThan to compare two journey codes.    You
    // can create a new node containing the journey code to be searched
    // (along with some arbitrary price) and invoke AVLLessThan on the
    // current node in the tree that you are inspecting and the new node
    // to do your comparison.

    // REMEMBER to update the height of appropriate nodes in the tree
    // after a successful deletion.
    
    // We use "return true" below to enable compilation.    Change this as you
    // see fit.
    return true;
}

int getComparisonCost()
{
    return totalComparisonCost;
}

int getParentChildUpdateCost()
{
    return totalParentChildUpdateCost;
}

void print()
{
    printBinaryTree(root, "", false);
}

int getComparisonCost()
{
    return totalComparisonCost;
}

int getParentChildUpdateCost()
{
    return totalParentChildUpdateCost;
}

void print()
{
    printBinaryTree(root, "", false);
}
