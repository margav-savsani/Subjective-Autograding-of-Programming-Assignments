#include "BST.h"

#include <iostream>
#include <stdlib.h>

// Recursively deletes all nodes in the binary tree rooted at currNode
void BST::recursiveDelete(TreeNode* currNode) {
    if (currNode != nullptr) {
        TreeNode* leftChild = currNode->left;
        TreeNode* rightChild = currNode->right;
    
        delete currNode;
        recursiveDelete(leftChild);
        recursiveDelete(rightChild);
    }
    return;
}

bool BST::BSTLessThan(TreeNode* leftArg, TreeNode*rightArg) {
    if ((leftArg != nullptr) && (rightArg != nullptr)) {
        bool result = (leftArg < rightArg);
        totalComparisonCost += perComparisonCost;
    }
    else {
        std::cerr << "Unexpected exceptional condition!\n";
        exit(-1);
    }
}
    
void BST::updateBSTParentChild(TreeNode* childNode, TreeNode* parentNode, bool isLeftChild)
{
    if ((childNode != nullptr) && (parentNode != nullptr)) {
        childNode->updateParentChild(parentNode, isLeftChild);
        totalParentChildUpdateCost += perParentChildUpdateCost;
    }
    else if ((childNode == nullptr) && (parentNode != nullptr)) {
        if (isLeftChild) {
parentNode->left = nullptr;
        }
        else {
parentNode->right = nullptr;
        }
        // No updating of totalParentChildUpdateCost needed here
    }
    else if ((childNode != nullptr) && (parentNode == nullptr)) {
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
BST::BST(int perCompCost, int perParntChldUpdCost)
    : root(nullptr), totalComparisonCost(0), totalParentChildUpdateCost(0), perComparisonCost(perCompCost), perParentChildUpdateCost(perParntChldUpdCost)
{
}

BST::BST(TreeNode* newRoot, int perCompCost, int perParntChldUpdCost)
    : root(newRoot), totalComparisonCost(0), totalParentChildUpdateCost(perCompCost), perParentChildUpdateCost(perParntChldUpdCost)
{
}
    
// Destructor
BST::~BST()
{
    recursiveDelete(root);
}

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

int BST::getComparisonCost()
{
    return totalComparisonCost;
}
int BST::getParentChildUpdateCost()
{
    return totalParentChildUpdateCost;
}
void BST::print()
{
    printBinaryTree(root, "", false); return;
}

