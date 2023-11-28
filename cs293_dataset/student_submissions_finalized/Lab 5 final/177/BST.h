#ifndef BST_H
#define BST_H

#ifndef TREE_H
#include "Tree.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

using namespace std;

class BST {

  private:

    TreeNode* root = nullptr;

    int total_comparison_cost = 0;
    int total_parent_child_update_cost = 0;
    int comparison_cost;
    int parent_child_update_cost;
    
    // Used in the destructor to delete/free every memory location occupied by TreeNodes
    void recursive_delete(TreeNode* current_node) {
      if (current_node != nullptr) {

        // The left and right child pointers are stored first as they are inaccessible after deleting the parent
        TreeNode *left_child = current_node->left;
        TreeNode *right_child = current_node->right;
      
        // Deletion process
        delete current_node;
        recursive_delete(left_child);
        recursive_delete(right_child);
      }
    }

    // Formulating comparison functions between TreeNodes
    // These functions also increment total_comparison_cost accordingly 
    bool BST_less_than(TreeNode* leftArg, TreeNode *rightArg) {
      if ((leftArg != nullptr) && (rightArg != nullptr)) {total_comparison_cost += comparison_cost; return (*leftArg < *rightArg);}
      else {cerr << "Unexpected exceptional condition!" << endl; exit(-1);}
    }

    bool BST_more_than(TreeNode* leftArg, TreeNode *rightArg) {
      if ((leftArg != nullptr) && (rightArg != nullptr)) {total_comparison_cost += comparison_cost; return (*leftArg > *rightArg);}
      else {cerr << "Unexpected exceptional condition!" << endl; exit(-1);}
    }
    
    // Set up a parent-child relation between two provided TreeNodes
    void BST_update_Parent_and_Child(TreeNode *child_node, TreeNode *parent_node, bool is_left_child){
      if ((child_node != nullptr) && (parent_node != nullptr)) {
        child_node -> update_Parent(parent_node, is_left_child);
        total_parent_child_update_cost += parent_child_update_cost;
      }
      else if ((child_node == nullptr) && (parent_node != nullptr)) {
        if (is_left_child) parent_node -> left = nullptr;
        else parent_node -> right = nullptr;
      }
      else if ((child_node != nullptr) && (parent_node == nullptr)) {
        child_node -> parent = nullptr;
      }
    }
    
  public:

    BST(int comp_cost_, int parent_child_update_cost_) {
      comparison_cost = comp_cost_;
      parent_child_update_cost = parent_child_update_cost_;
    }
    
    BST(TreeNode* new_root, int comp_cost_, int parent_child_update_cost_) {
      root = new_root;
      comparison_cost = comp_cost_;
      parent_child_update_cost = parent_child_update_cost_;
    }

    ~BST() {recursive_delete(root);}

    bool insert(int journey_code, int price);
    int find(int journey_code);  
    bool remove(int journey_code);

    int getComparisonCost() {return total_comparison_cost;}
    int getParentChildUpdateCost() {return total_parent_child_update_cost;}
    void print() {root -> printBinaryTree("", false);}
};

#endif