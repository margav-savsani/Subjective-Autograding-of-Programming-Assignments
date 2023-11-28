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


  if (root == nullptr){

    root = new TreeNode(jrnyCode, price);
    root->height = 0;


  } else {
    
    struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;

    TreeNode* dummy = new TreeNode(jrnyCode, price);

    while (currNode != nullptr) {

        if (BST::BSTLessThan(currNode, dummy)) {
          parentOfCurrNode = currNode;
            currNode = currNode->right;
        }
        else if (BST::BSTLessThan(dummy, currNode)) {
            parentOfCurrNode = currNode;
            currNode = currNode->left;
        }
        else { 
            return false;
        }
    
    }
        
        currNode = dummy;
        dummy->parent = parentOfCurrNode;

    // Setting child of parent of dummy
    if (BSTLessThan(currNode, parentOfCurrNode)) {
        parentOfCurrNode->left = currNode;
    } else {
        parentOfCurrNode->right = currNode;
    }

    // Updating height of parent of dummy
    while (currNode != nullptr){
      currNode->height = h(currNode->left, currNode->right);
      currNode = currNode->parent;
    }

  }

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

  TreeNode *temp = root;

  TreeNode* dummy = new TreeNode(jrnyCode, 0);

  // It finds for the TreeNode till we reach the bottom
  while(temp != NULL){
    if(BSTEqualTo(temp, dummy)){
      return 1;
    }
    else if(BSTLessThan(dummy, temp)){
      temp = temp->left;
    }
    else{
      temp = temp->right;
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

  TreeNode *temp = root;
  TreeNode* dummy = new TreeNode(jrnyCode, 0);

    while(temp != NULL){

        if(BSTEqualTo(dummy, temp)){

            if (temp == root){
                if (temp->left == NULL && temp->right == NULL){
                    delete temp;
                    root = NULL;
                    return true;

                } else {

                    if (temp->left == NULL){
                        root = temp->right;
                        root->parent = NULL;
                       
                        delete temp;
                        return true;

                    } else if (temp->right == NULL){
                        root = temp->left;
                        root->parent = NULL;
                       
                        delete temp;
                        return true;

                    } else {
                        if (temp->right->left != NULL){

                            TreeNode *temp2 = temp->right->left;

                            while(temp2->left != NULL){
                                temp2 = temp2->left;
                            }

                            // root->JourneyCode = temp2->JourneyCode;
                            // root->price = temp2->price;

                            // To copy values of temp2 to root
                            Equate(root, temp2);


                            if(temp2->right != NULL){
                                temp2->parent->left = temp2->right;
                                temp2->right->parent = temp2->parent;
                            } else {
                                temp2->parent->left = NULL;
                            }

                            // root->height = h(root->left, root->right);
                            // temp2->parent->height = h(temp2->parent->left, temp2->parent->right);

                            TreeNode* dumm = temp2->parent;

                            while (dumm != NULL){
                              dumm->height = h(dumm->left, dumm->right);
                              dumm = dumm->parent;
                            }

                            delete temp2;
                            delete dumm;
                            return true;

                        } else {

                            temp->right->left = root->left;
                            temp->right->left->parent = temp->right;
                            root = temp->right;
                            root->parent = NULL;

                            root->height = h(root->left, root->right);

                            delete temp;
                            return true;
                        }
                    }

                }

            } else if(temp->left == NULL && temp->right == NULL){

                if(temp->parent->left == temp){
                    temp->parent->left = NULL;
                }
                else{
                    temp->parent->right = NULL;
                }

                // temp->parent->height = h(temp->parent->left, temp->parent->right);

                TreeNode* dumm = temp->parent;

                while (dumm != NULL){
                  dumm->height = h(dumm->left, dumm->right);
                  dumm = dumm->parent;
                }

                delete temp;
                delete dumm;
                return true;
            } else if(temp->left == NULL){

                if(temp->parent->left == temp){

                    temp->parent->left = temp->right;
                    temp->right->parent = temp->parent;

                }
                else{

                    temp->parent->right = temp->right;
                    temp->right->parent = temp->parent;

                }

                // temp->parent->height = h(temp->parent->left, temp->parent->right);

                TreeNode* dumm = temp->parent;

                while (dumm != NULL){
                  dumm->height = h(dumm->left, dumm->right);
                  dumm = dumm->parent;
                }

                    delete temp;
                    delete dumm;
                    return true;


            } else if(temp->right == NULL){

                if(temp->parent->left == temp){
                    temp->parent->left = temp->left;
                }
                else{
                    temp->parent->right = temp->left;
                }

                temp->left->parent = temp->parent;
                // temp->parent->height = h(temp->parent->left, temp->parent->right);
                
                TreeNode* dumm = temp->parent;

                while (dumm != NULL){
                  dumm->height = h(dumm->left, dumm->right);
                  dumm = dumm->parent;
                }

                delete temp;
                delete dumm;
                return true;
            } else {

                TreeNode *temp2 = temp->right;

                while(temp2->left != NULL){
                    temp2 = temp2->left;
                }

                // The next two lines will be done by Equate function given next
                // temp->JourneyCode = temp2->JourneyCode;
                // temp->price = temp2->price;
                Equate(temp, temp2);

                if (temp2->parent == temp){
                    if (temp2->right != NULL){
                        temp2->parent->right = temp2->right;
                        temp2->right->parent = temp2->parent;
                    } else {
                        temp2->parent->right = NULL;
                    }
                

                } else {

                    if (temp2->right != NULL){
                        temp2->parent->left = temp2->right;
                        temp2->right->parent = temp2->parent;
                    } else {
                        temp2->parent->left = NULL;
                    }

                }

                  // temp2->parent->height = h(temp2->parent->left, temp2->parent->right);
                  // temp->height = h(temp->left, temp->right);

                  TreeNode* dumm = temp2;

                  while (dumm != NULL){
                    dumm->height = h(dumm->left, dumm->right);
                    dumm = dumm->parent;
                  }

                delete temp2;
                delete dumm;
                return true;
            }

        // temp->price > price
        } else if(BSTLessThan(dummy, temp)){
            temp = temp->left;
        } else {
            temp = temp->right;

        }

    }

    return false;

}


