#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

// Recall from Prof. Naveen Garg's lectures how the various rotations are
// applied to restore the balance factor at all nodes of an AVL tree
// to either 0, 1 or -1, after an insert or delete.
// The correspondence between the terminology in Prof. Garg's lectures and
// our terminology in this code is as follows:
//
// Prof. Garg's lectures           Our code
// ---------------------           --------
//   x                             currNode
//   y                             parentNode
//   z                             grandParentNode
//
// Recall also that z (grandParentNode) is the lowest node in the path from
// the root to the inserted node or to the deleted node (as the case may be)
// where the balance factor has either become < -1 or > 1.
// To find what x (currNode) and y (parentNode) should be, you need to
// recall Prof. Garg's lectures.
// These are slightly differently defined when inserting nodes and when
// deleting nodes

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the left child of parentNode, and
  // parentNode is the left child of grandParentNode
  // That's why we are doing a rotateLeftLeft

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  TreeNode *T3 = parentNode->right;
  
  if(greatGrandParentNode != nullptr){
    bool isGPLeftChild;
    if (greatGrandParentNode->left == grandParentNode) {
      isGPLeftChild = true;
    }
    else if (greatGrandParentNode->right == grandParentNode) {
      isGPLeftChild = false;
    }
    else {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }
    updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  }else{
    this->root = parentNode;
    this->root->parent = nullptr;
  }
  
  updateAVLParentChild(currNode, parentNode, true); //FIXME: currNode is already the left child of parentNode
  updateAVLParentChild(grandParentNode, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);

  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the right child of parentNode, and
  // parentNode is the left child of grandParentNode.  That's
  // why we are doing a rotateLeftRight

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  if(greatGrandParentNode != nullptr){
    bool isGPLeftChild;
    if (greatGrandParentNode->left == grandParentNode){
      isGPLeftChild = true;
    }
    else if (greatGrandParentNode->right == grandParentNode){
      isGPLeftChild = false;
    }
    else{
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }

    updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  }else{
    this->root = currNode;
    this->root->parent = nullptr;
  }

  updateAVLParentChild(parentNode, currNode, true);
  updateAVLParentChild(grandParentNode, currNode, false);
  updateAVLParentChild(T2, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  TreeNode *T2 = currNode->right;
  TreeNode *T3 = currNode->left;

  if(greatGrandParentNode != nullptr){
    bool isGPLeftChild;
    if (greatGrandParentNode->left == grandParentNode) {
      isGPLeftChild = true;
    }
    else if (greatGrandParentNode->right == grandParentNode) {
      isGPLeftChild = false;
    }
    else {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }

    updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  }else{
    this->root = currNode;
    this->root->parent = nullptr;
  }

  updateAVLParentChild(parentNode, currNode, false);
  updateAVLParentChild(grandParentNode, currNode, true);
  updateAVLParentChild(T2, parentNode, true);
  updateAVLParentChild(T3, grandParentNode, false);

  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  TreeNode *T3 = parentNode->left;
  
  if(greatGrandParentNode != nullptr){
    bool isGPLeftChild;
    if (greatGrandParentNode->left == grandParentNode) {
      isGPLeftChild = true;
    }
    else if (greatGrandParentNode->right == grandParentNode) {
      isGPLeftChild = false;
    }
    else {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }

    updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  }else{
    this->root = parentNode;
    this->root->parent = nullptr;
  }

  updateAVLParentChild(currNode, parentNode, false); //FIXME: currNode is already the right child of parentNode
  updateAVLParentChild(grandParentNode, parentNode, true);
  updateAVLParentChild(T3, grandParentNode, false);

  return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int jrnyCode, int price)
{
  // Implement insertion in AVL tree followed by balance factor restoration
  // by properly identifying x, y, z as used in Prof. Garg's lectures
  // (equivalently, currNode, parentNode, grandParentNode in our code) and
  // invoking rotateLeftLeft, rotateLeftRight, rotateRightLeft and/or
  // rotateRightRight as appropriate.

  // It is your responsibility to find out the right x, y, z (or currNode,
  // parentNode, grandParentNode) following Prof. Garg's lectures
  //
  // Once you identify these correctly, simply invoking the appropriate
  // rotation should do the job.
  // You don't even need to invoke rotation twice for the double
  // rotations -- the way rotationLeftRight is implemented, and
  // rotationRightLeft should be implemented, you should be able to achieve
  // the effect of the double rotation using one invokation of the
  // appropriate member function.

  // You MUST use only AVLLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke AVLLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.

  if(this->findAndReturn(jrnyCode) != nullptr) return false;

  if(this->root == nullptr){
      this->root = new TreeNode(jrnyCode, price);
      return true;
  }

  TreeNode* cur_node = this->root;
  TreeNode* prev_node = nullptr;
  TreeNode* to_be_added = new TreeNode(jrnyCode, price);
  
  while(cur_node != nullptr){
      // if(price < cur_node->price){
      if(this->AVLLessThan(to_be_added, cur_node)){
          prev_node = cur_node;
          cur_node = prev_node->left;
      }else{
          prev_node = cur_node;
          cur_node = prev_node->right;
      }
  }

  // if(price < prev_node->price && prev_node->left == nullptr){
  if(this->AVLLessThan(to_be_added, prev_node) && prev_node->left == nullptr){
      to_be_added->updateParentChild(prev_node, true);
  }else if(prev_node->right == nullptr){
      to_be_added->updateParentChild(prev_node, false);
  }

  // this->updateHeights(cur_node);
  this->updateHeightsAndRebalance(to_be_added, true);
  return true;
}

void AVLTree::updateHeightsAndRebalance(TreeNode* node, bool fix_one){
  if(node == nullptr) return;

  TreeNode* z = this->updateHeights(node);
  TreeNode* y = this->getTallerChild(z);
  TreeNode* x = this->getTallerChild(y);
  TreeNode* final_top;

  if(x != nullptr){
    if(this->isLeftChild(y)){
      if(this->isLeftChild(x)){
        this->rotateLeftLeft(x,y,z);
        final_top=y;
      }else{
        this->rotateLeftRight(x,y,z);
        final_top=x;
      }
    }else{
      if(this->isLeftChild(x)){ 
        this->rotateRightLeft(x,y,z);
        final_top=x;
      }
      else{
        this->rotateRightRight(x,y,z);
        final_top=y;
      }
    } 

    this->updateNodeHeight(final_top->right);
    this->updateNodeHeight(final_top->left);
    this->updateNodeHeight(final_top);
  }

  if(fix_one) this->updateHeights(final_top->parent, false);
  else this->updateHeightsAndRebalance(final_top->parent);
}

/**
 * @brief Updates the heights of nodes on the path from node to root, and also optionally reports any imbalance
 * In case of an imbalance, it stops updating heights right there and returns the node at which imbalance is found 
 * 
 * @param node The node from which heights are to be updated, moving upwards
 * @param report_imbalance Optional variable to indicate whether or not to stop at an imbalance and return the imbalance node
 * @return TreeNode* imbalance_node, the node at which imbalance was found, nullptr otherwise
 */
TreeNode* AVLTree::updateHeights(TreeNode* node, bool report_imbalance){
  if(node == nullptr) return nullptr;

  int old_height = node->height;
  // int h1,h2;
  // h1=h2=0;

  // node->height = 0;

  // if(node->left!=nullptr){
  //   h1 = node->left->height;
  //   if(h1+1 > node->height) node->height = h1+1;
  // }
  // if(node->right!=nullptr){
  //   h2 = node->right->height;
  //   if(h2+1 > node->height) node->height = h2+1;
  // }

  // if(abs(h1-h2) > 1 && report_imbalance) return node;

  bool imb = this->updateNodeHeight(node);
  if(imb && report_imbalance) return node;

  if(old_height == node->height && old_height != 0) return nullptr;
  else return this->updateHeights(node->parent, report_imbalance);
}

bool AVLTree::updateNodeHeight(TreeNode* node){
  int h1,h2;h1=h2=-1;
  node->height = 0;

  if(node->left!=nullptr){
    h1 = node->left->height;
    if(h1+1 > node->height) node->height = h1+1;
  }
  if(node->right!=nullptr){
    h2 = node->right->height;
    if(h2+1 > node->height) node->height = h2+1;
  }

  return abs(h1-h2) > 1;
}

TreeNode* AVLTree::getTallerChild(TreeNode* node){
  if(node == nullptr) return nullptr;

  if(node->left == nullptr) return node->right;
  if(node->right == nullptr) return node->left;

  return (node->left->height > node->right->height) ? node->left : node->right;
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
{
  // Implement find in AVL tree.
  // This is really no different from finding in a binary search tree.
  // This operation cannot cause any balance factor disturbances.

  // You MUST use only AVLLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke AVLLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
  TreeNode* target = this->findAndReturn(jrnyCode);
  if(target == nullptr) return -1;  
  return target->getPrice();
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in AVL tree with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the AVL tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::remove(int jrnyCode)
{
  // Implement deletion in AVL tree followed by balance factor restoration
  // by properly identifying x, y, z as used in Prof. Garg's lectures
  // (equivalently, currNode, parentNode, grandParentNode in our code) and
  // invoking rotateLeftLeft, rotateLeftRight, rotateRightLeft and/or
  // rotateRightRight as appropriate.

  // It is your responsibility to find out the right x, y, z (or currNode,
  // parentNode, grandParentNode) following Prof. Garg's lectures
  //
  // Once you identify these correctly, simply invoking the appropriate
  // rotation(s) should do the job.
  // You don't even need to invoke rotation twice for the double
  // rotations -- the way rotationLeftRight is implemented, and
  // rotationRightLeft should be implemented, you should be able to achieve
  // the effect of the double rotation using one invokation of the
  // appropriate member function.

  // You MUST use only AVLLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke AVLLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // REMEMBER to update the height of appropriate nodes in the tree
  // after a successful deletion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
  return this->removeNode(this->findAndReturn(jrnyCode));
  // return true;
}
bool AVLTree::removeNode(TreeNode* cur_node){
    if(cur_node == nullptr) return false;

    if(cur_node->right == nullptr && cur_node->left==nullptr){
        if(this->isLeftChild(cur_node)) cur_node->parent->left = nullptr;
        else cur_node->parent->right = nullptr;
        // this->updateHeights(cur_node->parent);
        this->updateHeightsAndRebalance(cur_node->parent);

        delete cur_node;
    }else if(cur_node->right == nullptr){
        cur_node->left->parent = cur_node->parent;

        if(this->isLeftChild(cur_node)) cur_node->parent->left = cur_node->left;
        else cur_node->parent->right = cur_node->left;
        // this->updateHeights(cur_node->parent);
        this->updateHeightsAndRebalance(cur_node->parent);

        delete cur_node;
    }else if(cur_node->left == nullptr){
        cur_node->right->parent = cur_node->parent;

        if(this->isLeftChild(cur_node)) cur_node->parent->left = cur_node->right;
        else cur_node->parent->right = cur_node->right;
        // this->updateHeights(cur_node->parent);
        this->updateHeightsAndRebalance(cur_node->parent);

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

TreeNode* AVLTree::findAndReturn(int code){
    TreeNode *cur_node = this->root, *to_find = new TreeNode(code, 0);

    while(cur_node != nullptr){
        if(cur_node->getJourneyCode() == code) return cur_node;

        if(this->AVLLessThan(to_find, cur_node)) cur_node = cur_node->left;
        else cur_node = cur_node->right;
    }

    return nullptr;
}

/**
 * @brief Finds the leftmost (and thus the least in defined ordering) node in the BST 
 * 
 * @param sub_root The root of the sub-tree which is to be searched
 * @return TreeNode* the leftmost node in the sub-BST
 */
TreeNode* AVLTree::minNode(TreeNode* sub_root){
    if(sub_root == nullptr) return nullptr;

    TreeNode* res = sub_root;
    while(res->left != nullptr) res = res->left;

    return res;
}

/**
 * @brief Checks if `node` is the left child of it's parent. 
 * 
 * @param node The node to be checked
 * @return true, if the node is the left child of it's parent.
 * @return false, if the node has no parent, or is the right child of it's parent.
 */
bool AVLTree::isLeftChild(TreeNode* node){
    if(node->parent == nullptr) return false;
    return (node->parent->left == node);
}