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

  TreeNode* nd = new TreeNode(jrnyCode, price);

  // if an empty tree then create a root node
    if(root == nullptr){
        root = nd;
        return true;
    }

    TreeNode *ptr = root;

    // search for required node
    while(true){

        // return false if already present
        if( (!BSTLessThan(nd, ptr)) && (!BSTLessThan(ptr, nd)) ){
            return false;
        }

        // go left if required key is less than or equal
        if(BSTLessThan(nd, ptr) && ptr->left != nullptr){
            ptr = ptr->left;
        }
        // go right if required key is strictly more
        else if(BSTLessThan(ptr, nd) && ptr->right != nullptr){
            ptr = ptr->right;
        }
        // insert to left 
        else if(BSTLessThan(nd, ptr) && ptr->left == nullptr){
            ptr->left = nd;
            ptr->left->parent = ptr;
            return true;
        }
        // insert to right
        else if(BSTLessThan(ptr, nd) && ptr->right == nullptr){
            ptr->right = nd;
            ptr->right->parent = ptr;
            return true;
        }
    }
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

  TreeNode* nd = new TreeNode(jrnyCode, 0);

  TreeNode *ptr = root;

    // same code as in insert
    while(true){
        if(ptr == nullptr){
            delete nd;
            return -1;
        }
        else if( (!BSTLessThan(nd, ptr)) && (!BSTLessThan(ptr, nd)) ){
            delete nd;
            return ptr->getJourneyCode();
        }
        else if(BSTLessThan(nd, ptr)){
            ptr = ptr->left;
        }
        else{
            ptr = ptr->right;
        }
    }
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

  TreeNode *nd = new TreeNode(jrnyCode, 0);

  TreeNode *ptr = root;

    // get the pointer to node that we have to delete
    while(true){
        if(ptr == nullptr){
          delete nd;
          return false;
        }
        else if( (!BSTLessThan(nd, ptr)) && (!BSTLessThan(ptr, nd)) ){
            break;
        }
        else if(BSTLessThan(nd, ptr)){
            ptr = ptr->left;
        }
        else{
            ptr = ptr->right;
        }
    }

    // if the node we want to delete is root node
    if(ptr == root){

        // if root node is a leaf
        if(ptr->left == nullptr && ptr->right == nullptr){
            delete root;
            root = nullptr;
            delete nd;
            return true;
        }

        // if left child of root node is empty
        else if(ptr->left == nullptr && ptr->right != nullptr){
            TreeNode *p = ptr->right;
            delete root;
            root = p;
            root->parent = nullptr;
            delete nd;
            return true;
        }

        // if right child of root node is empty
        else if(ptr->left != nullptr && ptr->right == nullptr){
            TreeNode *p = ptr->left;
            delete root;
            root = p;
            root->parent == nullptr;
            delete nd;
            return true;
        }

        // if root node has both children
        else{
            TreeNode *xd = ptr->left;

            while(true){
                if(xd->right == nullptr){
                    break;
                }
                else{
                    xd = xd->right;
                }
            }

            int reqJourneyCode = xd->getJourneyCode();
            int reqPrice = xd->getPrice();

            remove(reqJourneyCode);

            ptr->setJourneyCode(reqJourneyCode);
            ptr->setPrice(reqPrice);

            delete nd;
            return true;
        }
    }


    // for nodes which are not root nodes

    TreeNode *prnt = ptr->parent;
    TreeNode **prntToChild;


    if(prnt->left != nullptr){
        if( (!BSTLessThan(ptr, ptr->left)) && (!(BSTLessThan(ptr->left, ptr))) ){
            prntToChild = &(prnt->left);
        }
    }

    if(prnt->right != nullptr){
        if( (!BSTLessThan(ptr, ptr->right)) && (!(BSTLessThan(ptr->right, ptr))) ){
            prntToChild = &(prnt->right);
        }
    }

    // if node is a leaf
    if(ptr->left== nullptr && ptr->right == nullptr){
        delete *prntToChild;
        *prntToChild = nullptr;
        delete nd;
        return true;
    }

    // only left child empty
    else if(ptr->left == nullptr){
        TreeNode *temp = ptr->right;

        delete *prntToChild;
        *prntToChild = temp;
        temp->parent = prnt;
        delete nd;
        return true;
    }

    // only right child empty
    else if(ptr->right == nullptr){
        TreeNode *temp = ptr->left;

        delete *prntToChild;
        *prntToChild = temp;
        temp->parent = prnt;
        delete nd;
        return true;
    }

    // node has both children
    else{
        TreeNode *xd = ptr->left;

        while(true){
            if(xd->right == nullptr){
                break;
            }
            else{
                xd = xd->right;
            }
        }

        int reqJourneyCode = xd->getJourneyCode();
        int reqPrice = xd->getPrice();

        remove(reqJourneyCode);

        ptr->setJourneyCode(reqJourneyCode);
        ptr->setPrice(reqPrice);

        delete nd;
        return true;
    }

}


