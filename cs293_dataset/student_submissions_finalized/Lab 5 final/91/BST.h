#ifndef BST_H
#define BST_H

#include "Tree.h"

#include <iostream>
#include <stdlib.h>

class BST {
  private:
    TreeNode* root;
    int totalComparisonCost;
    int totalParentChildUpdateCost;
    int perComparisonCost;
    int perParentChildUpdateCost;
    
    // Recursively deletes all nodes in the binary tree rooted at currNode
    
    void recursiveDelete(TreeNode* currNode)
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

    bool BSTLessThan(TreeNode* leftArg, TreeNode* rightArg)
    {
        if ((leftArg != nullptr) && (rightArg != nullptr)) {
            bool result = (*leftArg <* rightArg);
            totalComparisonCost += perComparisonCost;
            return result;
        }
        else {
            std::cerr << "Unexpected exceptional condition!\n";
            exit(-1);
        }
    }
    
    void updateBSTParentChild(TreeNode* childNode, TreeNode* parentNode, bool isLeftChild)
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

    void updateHeights(TreeNode* t);
        
  public:
    // Constructors
    BST(int perCompCost, int perParntChldUpdCost)
    {
        root = nullptr;
        totalComparisonCost = 0;
        totalParentChildUpdateCost = 0;
        perComparisonCost = perCompCost;
        perParentChildUpdateCost = perParntChldUpdCost;
    }
    
    BST(TreeNode* newRoot, int perCompCost, int perParntChldUpdCost)
    {
        root = newRoot;
        totalComparisonCost = 0;
        totalParentChildUpdateCost = 0;
        perComparisonCost = perCompCost;
        perParentChildUpdateCost = perParntChldUpdCost;
    }
        
    // Destructor
    ~BST()
    {
        recursiveDelete(root);
    }

    bool insert(int jrnyCode, int price);
    int find(int jrnyCode);

    // Optional: Implement "remove" only for bonus marks
    
    bool remove(int jrnyCode);

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
};

#endif
