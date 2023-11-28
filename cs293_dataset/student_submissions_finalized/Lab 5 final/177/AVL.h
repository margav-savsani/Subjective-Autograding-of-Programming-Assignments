#ifndef AVL_H
#define AVL_H

#ifndef TREE_H
#include "Tree.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

using namespace std;

class AVLTree {

  private:

    TreeNode* root = nullptr;

    int total_comparison_cost = 0;
    int total_parent_child_update_cost = 0;
    int comparison_cost;
    int parent_child_update_cost;
    
    bool rotateLeftLeft(TreeNode* current_node);
    bool rotateLeftRight(TreeNode* current_node);
    bool rotateRightLeft(TreeNode* current_node);
    bool rotateRightRight(TreeNode* current_node);
    
    bool master_rotate(TreeNode* current_node);

    // Used in the destructor to delete/free every memory location occupied by TreeNodes
    void recursive_delete(TreeNode* current_node) {
      if (current_node != nullptr) {
        TreeNode *left_child = current_node->left;
        TreeNode *right_child = current_node->right;
      
        delete current_node;
        recursive_delete(left_child);
        recursive_delete(right_child);
      }
      return;
    }

    // Formulating comparison functions between TreeNodes
    // These functions also increment total_comparison_cost accordingly 
    bool AVL_less_than(TreeNode* leftArg, TreeNode *rightArg) {
      if ((leftArg != nullptr) && (rightArg != nullptr)) {total_comparison_cost += comparison_cost; return (*leftArg < *rightArg);}
      else {cerr << "Unexpected exceptional condition!" << endl; exit(-1);}
    }

    bool AVL_more_than(TreeNode* leftArg, TreeNode *rightArg) {
      if ((leftArg != nullptr) && (rightArg != nullptr)) {total_comparison_cost += comparison_cost; return (*leftArg > *rightArg);}
      else {cerr << "Unexpected exceptional condition!" << endl; exit(-1);}
    }

    // Set up a parent-child relation between two provided TreeNodes
    void AVL_update_Parent_and_Child(TreeNode *childNode, TreeNode *parentNode, bool isLeftChild){
      if ((childNode != nullptr) && (parentNode != nullptr)) {
        childNode -> update_Parent(parentNode, isLeftChild);
        total_parent_child_update_cost += parent_child_update_cost;
      }
      else if ((childNode == nullptr) && (parentNode != nullptr)) {
        if (isLeftChild) parentNode -> left = nullptr;
        else parentNode -> right = nullptr;
      }
      else if ((childNode != nullptr) && (parentNode == nullptr)) {
        childNode -> parent = nullptr;
      }
    }
      
  public:

    AVLTree(int perCompCost, int perParntChldUpdCost) {
      comparison_cost = perCompCost;
      parent_child_update_cost = perParntChldUpdCost;
    }
    
    AVLTree(TreeNode* newRoot, int perCompCost, int perParntChldUpdCost) {
      root = newRoot;
      comparison_cost = perCompCost;
      parent_child_update_cost = perParntChldUpdCost;
    }
      
    ~AVLTree() {recursive_delete(root);}

    bool insert(int jrnyCode, int price);
    int find(int jrnyCode);    
    bool remove(int jrnyCode);

    int getComparisonCost() {return total_comparison_cost;}
    int getParentChildUpdateCost() {return total_parent_child_update_cost;}
    void print() {root -> printBinaryTree("", false);}
};

#endif