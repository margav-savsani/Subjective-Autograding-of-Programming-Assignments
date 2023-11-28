#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <vector>
#include <stdlib.h>
#endif

bool BST::insert(int journey_code, int price){
  // Just in case the root is NULL
  if (root == nullptr) {root = new TreeNode(journey_code,price); root -> update_height(); return true;}

  TreeNode* node_to_insert = new TreeNode(journey_code,price);
  TreeNode* current_node = root;

  bool inserted = false;

  // This loop goes on until a location to insert the values is found
  // When a location is found, the insertion takes place via updating the parent-child pair
  // Note that this implementation has a failsafe in case someone tries to insert a duplicate Journey Code
  // Although we were assured that duplicate entries won't be inserted, there is no such thing as too safe😉
  // Note that this doubles the comparasion cost
  while (current_node != nullptr){
    if (BST_less_than(node_to_insert, current_node)){
      if (current_node -> left == nullptr) {BST_update_Parent_and_Child(node_to_insert, current_node, true); inserted = true; current_node = node_to_insert; break;}
      else {current_node = current_node -> left; continue;}
    }
    if (BST_more_than(node_to_insert, current_node)){
      if (current_node -> right == nullptr) {BST_update_Parent_and_Child(node_to_insert, current_node, false); inserted = true; current_node = node_to_insert; current_node = node_to_insert;break;}
      else {current_node = current_node -> right; continue;} 
    }
    break; // This break is only reached when we encounter a TreeNode which has the same Journey Code as the one we want to insert
  }

  // This loop updates the height of every node in the path from the root to the inserted TreeNode
  // Starting from the bottom is necessary, as only this can guarantee a correct update
  if (inserted) {current_node -> update_all_heights_in_path_to_root(); return true;}
    
  return false;
}

int BST::find(int journey_code){
  TreeNode* current_node = root; // Starting our checks at the root
  TreeNode* temp = new TreeNode(journey_code); // Arbitrary instance for comparasion

  while (current_node != nullptr){
    if (BST_less_than(current_node,temp)) current_node = current_node -> right;
    else if (BST_more_than(current_node,temp)) current_node = current_node -> left;
    else return current_node -> get_price(); 
  }

  return -1; // Arbitrary negative value is returned when no node with the supplied Journey Code is found
}

bool BST::remove(int journey_code){
    TreeNode* node_to_delete = root; // Starting our checks from the root
    TreeNode* temp = new TreeNode(journey_code); // Arbitrary instance for comparasion
    TreeNode* bottom_most_node = nullptr; // To be used as the starting point for height updates
    bool deleted = false; // A boolean to signify whether the deletion has occurred

    // Reach the node to delete
    // We can break from the loop in two ways: either we reach the node which has to be deleted, or reach an empty location, signifying that the given value is not present in the tree
    while (node_to_delete != nullptr){
        if (BST_less_than(temp, node_to_delete)) {node_to_delete = node_to_delete -> left; continue;}
        else if (BST_more_than(temp, node_to_delete)) {node_to_delete = node_to_delete -> right; continue;}
        break;
    }

    // Deletion, if the required node to delete is found
    if (node_to_delete != nullptr){

        // In case at least one of the child of the node to delete is NULL
        // The structure of the code also handles the case when the node_to_delete is a leaf
        if ((node_to_delete -> left == nullptr) || (node_to_delete -> right == nullptr)){

            // The deepest element whose height can be affected by the deletion is the parent of the node to be deleted in this case
            bottom_most_node = node_to_delete -> parent;

            // When the left child of the node to delete is NULL
            if (node_to_delete -> left == nullptr){

                // In case the root is to deleted, the root pointer has to be changed to point to the new root
                if (node_to_delete == root) root = root -> right;

                // This essentially removes the node_to_delete from in between its parent and child
                BST_update_Parent_and_Child(node_to_delete -> right, node_to_delete -> parent, (node_to_delete -> parent == nullptr) || (node_to_delete -> parent -> left == node_to_delete));

                // Freeing up the memory held by the node which has to be deleted
                delete node_to_delete;
                deleted = true;
            }

            // When the right child of the node to delete is NULL
            else {
                // In case the root is to deleted, the root pointer has to be changed to point to the new root
                if (node_to_delete == root) root = root -> left;

                // This essentially removes the node_to_delete from in between its parent and child
                BST_update_Parent_and_Child(node_to_delete -> left, node_to_delete -> parent, (node_to_delete -> parent == nullptr) || (node_to_delete -> parent -> left == node_to_delete));

                // Freeing up the memory held by the node which has to be deleted
                delete node_to_delete;
                deleted = true;
            }
        }

        // When the node to delete has two children
        else{
          
            // Reaching the successor of the node to delete
            TreeNode* probe = node_to_delete -> right;
            while (probe -> left != nullptr) probe = probe -> left;

            // Making a node which has the same Journey Code and Price as the successor of the node to be deleted
            TreeNode* replacement_node = new TreeNode(probe -> get_code(), probe -> get_price());

            // If node_to_delete is the root, then setting the replacment_node as the new root
            if (node_to_delete == root) root = replacement_node;
            
            // This essentially replaces the Journey Code and Price values in the node to delete with those of its successor
            BST_update_Parent_and_Child(replacement_node, node_to_delete -> parent, (node_to_delete -> parent != nullptr) && (node_to_delete -> parent -> left == node_to_delete));

            // Updating the pointers of the children of the deleted node to point to the replacement node
            BST_update_Parent_and_Child(node_to_delete -> left, replacement_node, true);
            BST_update_Parent_and_Child(node_to_delete -> right, replacement_node, false);

            // Removing the successor from its original position
            BST_update_Parent_and_Child(probe -> right, probe -> parent, probe -> parent -> left == probe);

            // Height changes will propagate from the root till the parent of the probe
            bottom_most_node = probe -> parent;

            // Freeing up the memory held by the node which has to be deleted
            delete node_to_delete;

            deleted = true;
        }

    }

    // Updating the height of every TreeNode whose height might have been affected by the deletion
    if (deleted) {bottom_most_node -> update_all_heights_in_path_to_root();}

    return deleted;
}