#include "BST.h"

void BST::updateHeights(TreeNode* t)
{
    if (t == nullptr)
        return;
    int prevHeight = t->height;
    if (t->left != nullptr && t->right != nullptr)
        t->height = std::max(t->left->height, t->right->height) + 1;
    else if (t->left == nullptr && t->right == nullptr)
        t->height = 0;
    else if (t->right == nullptr)
        t->height = t->left->height + 1;
    else
        t->height = t->right->height + 1;
    if (prevHeight == 0 || prevHeight != t->height)
        updateHeights(t->parent);
}

// Returns true on successful insertion in BST. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the BST

bool BST::insert(int jrnyCode, int price)
{
    TreeNode* new_node = new TreeNode(jrnyCode, price);
    if (root != nullptr) {
        TreeNode* t = nullptr;
        TreeNode* t_child = root;
        
        while (t_child != nullptr) {
            t = t_child; 
            if (BSTLessThan(new_node, t_child))
                t_child = t_child->left;
            else
                t_child = t_child->right;
        }

        updateBSTParentChild(new_node, t, BSTLessThan(new_node, t));
        /*
        if (BSTLessThan(new_node, t))
            t->left = new_node;
        else
            t->right = new_node;
        new_node->parent = t;
        */
    }
    else {
        root = new_node;
    }
    updateHeights(new_node);
    return true;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
    TreeNode* t = nullptr;
    TreeNode* t_child = root;

    TreeNode* sought_node = new TreeNode(jrnyCode, 0);
    while (t_child != nullptr) {
        t = t_child;
        if (BSTLessThan(sought_node, t_child))
            t_child = t_child->left;
        else {
            if (jrnyCode == t_child->JourneyCode)
                return t_child->price;
            t_child = t_child->right;
        }
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
