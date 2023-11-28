#ifndef BST_H
#define BST_H

#include "Tree.h"

#include <iostream>
#include <stdlib.h>

class BST {
  private:
    TreeNode *root;
    int totalComparisonCost;
    int totalParentChildUpdateCost;
    int perComparisonCost;
    int perParentChildUpdateCost;
    
    void recursiveDelete(TreeNode *currNode);

    bool BSTLessThan(TreeNode* leftArg, TreeNode*rightArg);
    
    void updateBSTParentChild(TreeNode *childNode, TreeNode *parentNode, bool isLeftChild); 
        
  public:
    // Constructors
    BST(int perCompCost, int perParntChldUpdCost);
    
    BST(TreeNode *newRoot, int perCompCost, int perParntChldUpdCost);
        
    // Destructor
    ~BST();

    bool insert(int jrnyCode, int price);
    int find(int jrnyCode);

    // Optional: Implement "remove" only for bonus marks
    
    bool remove(int jrnyCode);

    int getComparisonCost();
    int getParentChildUpdateCost();
    void print();
};

#endif
