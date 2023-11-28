#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

// To enable compilation. These functions are not used anywhere
bool rotateLeftLeft(TreeNode* current_node) {return false;}
bool rotateLeftRight(TreeNode* current_node) {return false;}
bool rotateRightLeft(TreeNode* current_node) {return false;}
bool rotateRightRight(TreeNode* current_node) {return false;}

bool AVLTree::master_rotate(TreeNode* current_node){

    // These are failsafes to prevent null pointer access
    TreeNode* parent_node = nullptr;
    TreeNode* grandparent_node = nullptr;
    if (current_node != nullptr) parent_node = current_node -> parent;
    if (parent_node != nullptr) grandparent_node = parent_node -> parent; 

    // The code will execute only if it is ensured that we are not accessing null pointers
    if (parent_node != nullptr && grandparent_node != nullptr){

        // Left_Left
        if((grandparent_node -> left == parent_node) && (parent_node -> left == current_node)){

            // Extracting the right child of parent_node, as it will be moved to a different parent during the rotation
            TreeNode* T3 = parent_node -> right;

            // Root is a special node; it is our access point for inserts and delete
            // However, it is possible that if the grandparent_node is the root itself, then we need to account for its changed position in the final tree configuration
            // In this case, the parent_node replaces the grandparent_node, so it is set as the root
            if (grandparent_node -> parent == nullptr) root = parent_node;

            // Had the grandparent been the root, then the great grandparent would have been null.
            // In that case, it would be illegal to use grandparent_node -> parent -> left
            // || has a short-circuit evaluation: the second conditional is evaluated only if the first condition is false
            // When the great_grandparent is null, we never go the conditional, thereby avoiding an error
            // Also, when the second argument in this function is null, then the third argument (the boolean) doesn't matter
            AVL_update_Parent_and_Child(parent_node, grandparent_node -> parent, (grandparent_node -> parent == nullptr) || (grandparent_node -> parent -> left == grandparent_node));
            
            AVL_update_Parent_and_Child(grandparent_node, parent_node, false);

            AVL_update_Parent_and_Child(T3, grandparent_node, true);

            // Now, we will update heights of all the nodes that might have been affected by the rotation
            // Note that in this case, the height of the current_node is intact, as no changes were made to its children.
            // The only changes in height will occur in the path from the grandparent_node to the root
            grandparent_node -> update_all_heights_in_path_to_root();
        }

        // Right_Right
        if((grandparent_node -> right == parent_node) && (parent_node -> right == current_node)){

            // Extracting the left child of parent_node, as it will be moved to a different parent during the rotation
            TreeNode* T2 = parent_node -> left;

            // Root is a special node; it is our access point for inserts and delete
            // However, it is possible that if the grandparent_node is the root itself, then we need to account for its changed position in the final tree configuration
            // In this case, the parent_node replaces the grandparent_node, so it is set as the root
            if (grandparent_node -> parent == nullptr) root = parent_node;

            // Had the grandparent been the root, then the great grandparent would have been null.
            // In that case, it would be illegal to use grandparent_node -> parent -> left
            // || has a short-circuit evaluation: the second conditional is evaluated only if the first condition is false
            // When the great_grandparent is null, we never go the conditional, thereby avoiding an error
            // Also, when the second argument in this function is null, then the third argument (the boolean) doesn't matter
            AVL_update_Parent_and_Child(parent_node, grandparent_node -> parent, (grandparent_node -> parent == nullptr) || (grandparent_node -> parent -> left == grandparent_node));
            
            AVL_update_Parent_and_Child(grandparent_node, parent_node, true);

            AVL_update_Parent_and_Child(T2, grandparent_node, false);

            // Now, we will update heights of all the nodes that might have been affected by the rotation
            // Note that in this case, the height of the current_node is intact, as no changes were made to its children.
            // The only changes in height will occur in the path from the grandparent_node to the root
            grandparent_node -> update_all_heights_in_path_to_root();
        }

        // Left_Right
        if((grandparent_node -> left == parent_node) && (parent_node -> right == current_node)){

            // Extracting the children of the current_node, as they will be relocated during the rotation
            TreeNode* T2 = current_node -> left;
            TreeNode* T3 = current_node -> right;

            // Root is a special node; it is our access point for inserts and delete
            // However, it is possible that if the grandparent_node is the root itself, then we need to account for its changed position in the final tree configuration
            // In this case, the current_node replaces the grandparent_node, so it is set as the root
            if (grandparent_node -> parent == nullptr) root = current_node;

            // Had the grandparent been the root, then the great grandparent would have been null.
            // In that case, it would be illegal to use grandparent_node -> parent -> left
            // || has a short-circuit evaluation: the second conditional is evaluated only if the first condition is false
            // When the great_grandparent is null, we never go the conditional, thereby avoiding an error
            // Also, when the second argument in this function is null, then the third argument (the boolean) doesn't matter
            AVL_update_Parent_and_Child(current_node, grandparent_node -> parent, (grandparent_node -> parent == nullptr) || (grandparent_node -> parent -> left == grandparent_node));
            
            AVL_update_Parent_and_Child(parent_node, current_node, true);

            AVL_update_Parent_and_Child(grandparent_node, current_node, false);

            AVL_update_Parent_and_Child(T2, parent_node, false);

            AVL_update_Parent_and_Child(T3, grandparent_node, true);

            // Now, we will update heights of all the nodes that might have been affected by the rotation
            // The changes in height will occur in current_node, its children (parent_node and grandparent_node) and in the nodes lying in the path from it to the root
            parent_node -> update_height();
            grandparent_node -> update_all_heights_in_path_to_root();
        }

        // Right_Left
        if((grandparent_node -> right == parent_node) && (parent_node -> left == current_node)){

            // Extracting the children of the current_node, as they will be relocated during the rotation
            TreeNode* T2 = current_node -> left;
            TreeNode* T3 = current_node -> right;

            // Root is a special node; it is our access point for inserts and delete
            // However, it is possible that if the grandparent_node is the root itself, then we need to account for its changed position in the final tree configuration
            // In this case, the current_node replaces the grandparent_node, so it is set as the root
            if (grandparent_node -> parent == nullptr) root = current_node;

            // Had the grandparent been the root, then the great grandparent would have been null.
            // In that case, it would be illegal to use grandparent_node -> parent -> left
            // || has a short-circuit evaluation: the second conditional is evaluated only if the first condition is false
            // When the great_grandparent is null, we never go the conditional, thereby avoiding an error
            // Also, when the second argument in this function is null, then the third argument (the boolean) doesn't matter
            AVL_update_Parent_and_Child(current_node, grandparent_node -> parent, (grandparent_node -> parent == nullptr) || (grandparent_node -> parent -> left == grandparent_node));
            
            AVL_update_Parent_and_Child(parent_node, current_node, false);

            AVL_update_Parent_and_Child(grandparent_node, current_node, true);

            AVL_update_Parent_and_Child(T2, grandparent_node, false);

            AVL_update_Parent_and_Child(T3, parent_node, true);

            // Now, we will update heights of all the nodes that might have been affected by the rotation
            // The changes in height will occur in current_node, its children (parent_node and grandparent_node) and in the nodes lying in the path from it to the root
            parent_node -> update_height();
            grandparent_node -> update_all_heights_in_path_to_root();
        } 

        return true;      
    }

    return false;
}

bool AVLTree::insert(int journey_code, int price){

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
    if (AVL_less_than(node_to_insert, current_node)){
      if (current_node -> left == nullptr) {AVL_update_Parent_and_Child(node_to_insert, current_node, true); inserted = true; current_node = node_to_insert; break;}
      else {current_node = current_node -> left; continue;}
    }
    if (AVL_more_than(node_to_insert, current_node)){
      if (current_node -> right == nullptr) {AVL_update_Parent_and_Child(node_to_insert, current_node, false); inserted = true; current_node = node_to_insert; break;}
      else {current_node = current_node -> right; continue;} 
    }
    break; // This break is only reached when we encounter a TreeNode which has the same Journey Code as the one we want to insert
  }
   
  if(inserted){

    // This loop updates the height of every node in the path from the root to the inserted TreeNode
    // Starting from the bottom is necessary, as only this can guarantee a correct update
    while (current_node != nullptr) {current_node -> update_height(); current_node = current_node -> parent;}
    
    // Performing a rotation if imbalance is found
    if ((node_to_insert -> parent != nullptr) && (node_to_insert -> parent -> parent != nullptr) && (node_to_insert -> parent -> parent -> get_imbalance() > 1))   master_rotate(node_to_insert);

    return true;
  }
  return false;
}

int AVLTree::find(int journey_code){
  TreeNode* current_node = root; // Starting our checks at the root
  TreeNode* temp = new TreeNode(journey_code); // Arbitrary instance for comparasion

  while (current_node != nullptr){
    if (AVL_less_than(current_node,temp)) current_node = current_node -> right;
    else if (AVL_more_than(current_node,temp)) current_node = current_node -> left;
    else return current_node -> get_price(); 
  }

  return -1; // Arbitrary negative value is returned when no node with the supplied Journey Code is found
}

bool AVLTree::remove(int journey_code){

    TreeNode* node_to_delete = root; // Starting our checks from the root
    TreeNode* temp = new TreeNode(journey_code); // Arbitrary instance for comparasion
    TreeNode* bottom_most_node = nullptr; // To be used as the starting point for height updates
    bool deleted = false; // A boolean to signify whether the deletion has occurred

    // Reach the node to delete
    // We can break from the loop in two ways: either we reach the node which has to be deleted, or reach an empty location, signifying that the given value is not present in the tree
    while (node_to_delete != nullptr){
        if (AVL_less_than(temp, node_to_delete)) {node_to_delete = node_to_delete -> left; continue;}
        else if (AVL_more_than(temp, node_to_delete)) {node_to_delete = node_to_delete -> right; continue;}
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

                // In case the root is to deleted, the root pointer has to be chnaged to point to the new root
                if (node_to_delete == root) root = root -> right;

                // This essentially removes the node_to_delete from in between its parent and child
                AVL_update_Parent_and_Child(node_to_delete -> right, node_to_delete -> parent, (node_to_delete -> parent == nullptr) || (node_to_delete -> parent -> left == node_to_delete));

                // Freeing up the memory held by the node which has to be deleted
                delete node_to_delete;
                deleted = true;
            }

            // When the right child of the node to delete is NULL
            else {
                // In case the root is to deleted, the root pointer has to be chnaged to point to the new root
                if (node_to_delete == root) root = root -> left;

                // This essentially removes the node_to_delete from in between its parent and child
                AVL_update_Parent_and_Child(node_to_delete -> left, node_to_delete -> parent, (node_to_delete -> parent == nullptr) || (node_to_delete -> parent -> left == node_to_delete));

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
            AVL_update_Parent_and_Child(replacement_node, node_to_delete -> parent, (node_to_delete -> parent != nullptr) && (node_to_delete -> parent -> left == node_to_delete));

            // Updating the pointers of the children of the deleted node to point to the replacement node
            AVL_update_Parent_and_Child(node_to_delete -> left, replacement_node, true);
            AVL_update_Parent_and_Child(node_to_delete -> right, replacement_node, false);

            // Removing the successor from its original position
            AVL_update_Parent_and_Child(probe -> right, probe -> parent, probe -> parent -> left == probe);

            // Height changes will propagate from the root till the parent of the probe
            bottom_most_node = probe -> parent;

            // Freeing up the memory held by the node which has to be deleted
            delete node_to_delete;

            deleted = true;
        }

    }

    if (deleted) {
      // Updating the height of every TreeNode whose height might have been affected by the deletion
      bottom_most_node -> update_all_heights_in_path_to_root();

      // Correcting balance in (possibly) affected node
      TreeNode* current_node = bottom_most_node;
      if ((current_node -> parent != nullptr) && (current_node -> parent -> parent != nullptr) && (current_node -> parent -> parent -> get_imbalance() > 1)) master_rotate(current_node);    
    }

    return deleted;
}