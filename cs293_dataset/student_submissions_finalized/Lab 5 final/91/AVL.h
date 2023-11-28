#ifndef AVL_H
#define AVL_H

#include "Tree.h"

#include <iostream>
#include <stdlib.h>

class AVLTree {
  private:
    TreeNode* root;
    int totalComparisonCost;
    int totalParentChildUpdateCost;
    int perComparisonCost;
    int perParentChildUpdateCost;

    void updateHeights(TreeNode* t);

    // utility function for the below four
    bool rotate(TreeNode* currNode);

    bool rotateLeftLeft(TreeNode* currNode, TreeNode* parent, TreeNode* grandParent);
    bool rotateLeftRight(TreeNode* currNode, TreeNode* parent, TreeNode* grandParent);
    bool rotateRightLeft(TreeNode* currNode, TreeNode* parent, TreeNode* grandParent);
    bool rotateRightRight(TreeNode* currNode, TreeNode* parent, TreeNode* grandParent);

    // Recursively deletes all nodes in the binary tree rooted at currNode
    
    void recursiveDelete(TreeNode *currNode);
    bool AVLLessThan(TreeNode* leftArg, TreeNode*rightArg);
    void updateAVLParentChild(TreeNode *childNode, TreeNode *parentNode, bool isLeftChild);
        
  public:
    // Constructors
    AVLTree(int perCompCost, int perParntChldUpdCost); 
    AVLTree(TreeNode *newRoot, int perCompCost, int perParntChldUpdCost);
        
    // Destructor
    ~AVLTree();

    bool insert(int jrnyCode, int price);
    int find(int jrnyCode);

    // Optional: Implement "remove" only for bonus marks
    
    bool remove(int jrnyCode);

    int getComparisonCost() { return totalComparisonCost; }
    int getParentChildUpdateCost() { return totalParentChildUpdateCost; }
    void print() { printBinaryTree(root, "", false); return;}
};

#endif
