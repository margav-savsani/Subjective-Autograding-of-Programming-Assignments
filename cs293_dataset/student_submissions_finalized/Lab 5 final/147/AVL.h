#ifndef AVL_H
#define AVL_H

#include "Tree.h" // not really required since BST.h includes it already
#include "BST.h" // for AbstractBST

class AVLTree: public AbstractBST{
private:
    bool rotateLeftLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent);
    bool rotateLeftRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent);
    bool rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent);
    bool rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent);
public:
    // Constructor
    AVLTree(int perComparisonCost, int perParentChildUpdateCost, TreeNode *root=nullptr): 
    AbstractBST(perComparisonCost, perParentChildUpdateCost, root){}
  
    ~AVLTree(){} // AbstractBST's destructor handles memory deallocation

    // AVL insert.
    bool insert(int JourneyCode, int price);

    // Optional: Implement "remove" only for bonus marks
    bool remove(int JourneyCode);
};

#endif
