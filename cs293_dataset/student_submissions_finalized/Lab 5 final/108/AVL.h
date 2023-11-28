#ifndef AVL_H
#define AVL_H

#ifndef TREE_H
#include "Tree.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

class AVLTree {
private:
    TreeNode *root;
    int totalComparisonCost;
    int totalParentChildUpdateCost;
    int perComparisonCost;
    int perParentChildUpdateCost;
    
    // bool rotateLeftLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent);
    // bool rotateLeftRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent);
    // bool rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent);
    // bool rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent);

    void rotateright(TreeNode* node);
    void rotateleft(TreeNode* node);
    void update (TreeNode* Root);
    void update_height(TreeNode* node);

    // Recursively deletes all nodes in the binary tree rooted at currNode
    
    void recursiveDelete(TreeNode *currNode) {
        if (currNode != nullptr) {
            TreeNode *leftChild = currNode->left;
            TreeNode *rightChild = currNode->right;
          
            delete currNode;
            recursiveDelete(leftChild);
            recursiveDelete(rightChild);
        }
        return;
    }

    bool AVLLessThan(TreeNode* leftArg, TreeNode* rightArg) {
        if ((leftArg != nullptr) && (rightArg != nullptr)) {
            totalComparisonCost += perComparisonCost;
            return leftArg->JourneyCode < rightArg->JourneyCode;
        } else {
            cerr << "Unexpected exceptional condition!" << endl;
            exit(-1);
        }
    }

    void updateAVLParentChild(TreeNode *childNode, TreeNode *parentNode, bool isLeftChild)
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

public:
    // Constructors
    AVLTree(int perCompCost, int perParntChldUpdCost) {
        root = nullptr;
        totalComparisonCost = 0;
        totalParentChildUpdateCost = 0;
        perComparisonCost = perCompCost;
        perParentChildUpdateCost = perParntChldUpdCost;
    }
    
    AVLTree(TreeNode *newRoot, int perCompCost, int perParntChldUpdCost) {
        root = newRoot;
        totalComparisonCost = 0;
        totalParentChildUpdateCost = 0;
        perComparisonCost = perCompCost;
        perParentChildUpdateCost = perParntChldUpdCost;
    }
      
    // Destructor
    ~AVLTree() {
        recursiveDelete(root);
    }

    int imbalance (TreeNode* node);
    bool insert(int jrnyCode, int price);
    bool find(int jrnyCode);
    bool remove(int jrnyCode);
    TreeNode* findmax(TreeNode* Root);
    int getComparisonCost() { return totalComparisonCost; }
    int getParentChildUpdateCost() { return totalParentChildUpdateCost; }
    void print() { printBinaryTree(root, "", false); return;}
};

#endif