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
  if(find(jrnyCode) != -1) return false;
    
    TreeNode* check = root, *toadd = new TreeNode(jrnyCode, price);
    if(check == nullptr){
        toadd->parent = check;
        root = toadd;
        update(toadd);
        return true;
    }
    while(true){
        if(BSTLessThan(toadd, check)){
            if(check->left != nullptr){
                check = check->left;
            }
            else{
                toadd->parent = check;
                check->left = toadd;
                update(toadd);
                return true;
            }
        }
        else{
            if(check->right != nullptr){
                check = check->right;
            }
            else{
                toadd->parent = check;
                check->right = toadd;
                update(toadd);
                return true;
            }
        }
    }

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
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
  
  TreeNode* currnode = root;
  TreeNode* temp = new TreeNode(jrnyCode, 1000);
  while(currnode != nullptr){
    if(BSTLessThan(temp, currnode)){
      // cout << currnode->getJourneycode() << " left\n";
      currnode = currnode->left;
    }
    else if(BSTLessThan(currnode, temp)){
      currnode = currnode->right;
      // cout << "right\n";s
    }
    else{
      // cout << currnode->getJourneycode() << " equal\n";
      return currnode->getPrice();
    }
  }

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
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

    TreeNode* node = findnode(jrnyCode);
    if(node == nullptr) return false;

    if(node->left == nullptr && node->right == nullptr){
        TreeNode* a = node->parent;
        if(a == nullptr){
            root = root->right;
        }
        else if(a->left == node){
            a->left = nullptr;
        }
        else{
            a->right = nullptr;
        }
        update(a);

        return true;
    }
    if(node->left == nullptr){
        TreeNode* a = node->parent;
        if(a == nullptr){
            root->right->parent = nullptr;
            root = root->right;
        }
        else if(a->left == node){
            node->right->parent = a;
            a->left = node->right;
        }
        else{
            node->right->parent = a;
            a->right = node->right;
        }
        update(a);

        return true;
    }
    if(node->right == nullptr){
        TreeNode* a = node->parent;
        if(a == nullptr){
            root->left->parent = nullptr;
            root = root->left;
        }
        else if(a->left == node){
            node->left->parent = a;
            a->left = node->left;
        }
        else{
            node->left->parent = a;
            a->right = node->left;
        }
        update(a);

        return true;
    }

    TreeNode* pred = node->left;
    while(pred->right != nullptr){
        pred = pred->right;
    }
    TreeNode temp = *pred;
    TreeNode* currNode = pred->parent;
    remove(pred->getJourneycode());
    temp.parent = node->parent;
    temp.right = node->right;
    temp.left = node->left;
    *node = temp;
    update(currNode);

  // REMEMBER to update the height of appropriate nodes in the tree
  // after a successful deletion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.

  return true;
}


