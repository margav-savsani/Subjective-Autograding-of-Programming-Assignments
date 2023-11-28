#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif


// Returns true on successful insertion in BST. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the BST

bool BST::insert(int jrnyCode, int price)
{
  // Implement insertion in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
  if(this->findAndReturn(jrnyCode) != nullptr) return false;

  if(this->root == nullptr){
      this->root = makeLeaf(jrnyCode, price, nullptr);
      return true;
  }

  TreeNode* cur_node = this->root;
  TreeNode* prev_node = nullptr;
  TreeNode* to_be_added = new TreeNode(jrnyCode, price);
  
  while(cur_node != nullptr){
      // if(price < cur_node->price){
      if(this->BSTLessThan(to_be_added, cur_node)){
          prev_node = cur_node;
          cur_node = prev_node->left;
      }else{
          prev_node = cur_node;
          cur_node = prev_node->right;
      }
  }

  // if(price < prev_node->price && prev_node->left == nullptr){
  if(this->BSTLessThan(to_be_added, prev_node) && prev_node->left == nullptr){
      cur_node = makeLeaf(jrnyCode, price, prev_node);
      prev_node->left = cur_node;
  }else if(prev_node->right == nullptr){
      cur_node = makeLeaf(jrnyCode, price, prev_node);
      prev_node->right = cur_node;
  }

  this->updateHeights(cur_node);
  return true;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
  // Implement find in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
  TreeNode* target = this->findAndReturn(jrnyCode);
  if(target == nullptr) return -1;  
  return target->getPrice();
}

TreeNode* BST::findAndReturn(int code){
    TreeNode *cur_node = this->root, *to_find = new TreeNode(code, 0);

    while(cur_node != nullptr){
        if(cur_node->getJourneyCode() == code) return cur_node;

        if(this->BSTLessThan(new TreeNode(code,0), cur_node)) cur_node = cur_node->left;
        else cur_node = cur_node->right;
    }

    return nullptr;
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in BST with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the BST have the same journey
// code, and journey code is the key for insertion and finding in the BST.


/**
 * @brief Removes the node in the BST with journey code `jrnyCode`
 * 
 * @param jrnyCode The code to be removed from the BST.
 * @return true, if the node was successfully removed
 * @return false, otherwise
 */
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

  return this->removeNode(this->findAndReturn(jrnyCode));
}
bool BST::removeNode(TreeNode* cur_node){
    if(cur_node == nullptr) return false;

    if(cur_node->right == nullptr && cur_node->left==nullptr){
        if(this->isLeftChild(cur_node)) cur_node->parent->left = nullptr;
        else cur_node->parent->right = nullptr;
        this->updateHeights(cur_node->parent);

        delete cur_node;
    }else if(cur_node->right == nullptr){
        cur_node->left->parent = cur_node->parent;

        if(this->isLeftChild(cur_node)) cur_node->parent->left = cur_node->left;
        else cur_node->parent->right = cur_node->left;
        this->updateHeights(cur_node->parent);

        delete cur_node;
    }else if(cur_node->left == nullptr){
        cur_node->right->parent = cur_node->parent;

        if(this->isLeftChild(cur_node)) cur_node->parent->left = cur_node->right;
        else cur_node->parent->right = cur_node->right;
        this->updateHeights(cur_node->parent);

        delete cur_node;
    }else{
        TreeNode* successor = this->minNode(cur_node->right);
        cur_node->setPrice(successor->getPrice());
        cur_node->setJourneyCode(successor->getJourneyCode());
        // cur_node->price = successor->price;
        // cur_node->JourneyCode = successor->JourneyCode;

        return this->removeNode(successor);
    }

    return true;
}

/**
 * @brief Updates the height of all nodes in the path from `target` to `root`
 * 
 * @param target The node whose height is to be re-calculated
 */
void BST::updateHeights(TreeNode* target){
  if(target==nullptr) return;

  target->height = 0;

  if(target->left!=nullptr && target->left->height+1 > target->height) target->height = target->left->height+1;
  if(target->right!=nullptr && target->right->height+1 > target->height) target->height = target->right->height+1;

  this->updateHeights(target->parent);

  return;
}

/**
 * @brief Makes a leaf node given a parent node
 * 
 * @param JourneyCode The journey code to be stored at the node
 * @param price The price to be stored at the node
 * @param parent The desired parent of the node
 * @return TreeNode*, a pointer to the leaf node just created
 */
TreeNode* BST::makeLeaf(int JourneyCode, int price, TreeNode* parent){
    TreeNode* res = new TreeNode(JourneyCode, price);
    res->parent = parent;

    return res;
}

/**
 * @brief Checks if `node` is the left child of it's parent. 
 * 
 * @param node The node to be checked
 * @return true, if the node is the left child of it's parent.
 * @return false, if the node has no parent, or is the right child of it's parent.
 */
bool BST::isLeftChild(TreeNode* node){
    if(node->parent == nullptr) return false;
    return (node->parent->left == node);
}

/**
 * @brief Finds the leftmost (and thus the least in defined ordering) node in the BST 
 * 
 * @param sub_root The root of the sub-tree which is to be searched
 * @return TreeNode* the leftmost node in the sub-BST
 */
TreeNode* BST::minNode(TreeNode* sub_root){
    if(sub_root == nullptr) return nullptr;

    TreeNode* res = sub_root;
    while(res->left != nullptr) res = res->left;

    return res;
}

// int main(){
// }