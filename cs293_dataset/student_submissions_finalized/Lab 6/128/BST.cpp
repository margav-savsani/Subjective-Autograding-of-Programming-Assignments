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

bool BST::insert(int JourneyCode, int price)
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
    TreeNode* treenode = new TreeNode(JourneyCode, price);

    if (root == NULL){
        root = treenode;
        //root->shortestPathLength = 0;
        return true;
    }

    if (BSTLessThan(treenode, root)){

        if(root->left == NULL){
            updateBSTParentChild(treenode, root, true);
            //treenode->shortestPathLength = 0;

            if(root->right == NULL){
                //root->shortestPathLength = 0;
                root->longestPathLength = 1+root->left->longestPathLength;
            }
            else{
                //root->shortestPathLength = 1+min(root->left->shortestPathLength, root->right->shortestPathLength);
                root->longestPathLength = 1+max(root->left->longestPathLength, root->right->longestPathLength);
            }
            return true;
        }

        else {
            BST left_child(root->left, perComparisonCost, perParentChildUpdateCost);
            bool inserted = left_child.insert(JourneyCode, price);

            totalComparisonCost += left_child.totalComparisonCost;
            totalParentChildUpdateCost += left_child.totalParentChildUpdateCost;

            if(inserted){
                if(root->right == NULL){
                    //root->shortestPathLength = 0;
                    root->longestPathLength = 1+root->left->longestPathLength;
                }
                else{
                    //root->shortestPathLength = 1+min(root->left->shortestPathLength, root->right->shortestPathLength);
                    root->longestPathLength = 1+max(root->left->longestPathLength, root->right->longestPathLength);
                }
            }
            return inserted;
        }


    }

    else if (BSTLessThan(root , treenode)){

        if(root->right == NULL){
            updateBSTParentChild(treenode, root, false);

            if(root->left == NULL){
                //root->shortestPathLength = 0;
                root->longestPathLength = 1+root->right->longestPathLength;
            }
            else{
                //root->shortestPathLength = 1+min(root->left->shortestPathLength, root->right->shortestPathLength);
                root->longestPathLength = 1+max(root->left->longestPathLength, root->right->longestPathLength);
            }

            return true;
        }

        else {
            BST right(root->right, perComparisonCost, perParentChildUpdateCost);
            bool inserted = right.insert(JourneyCode, price);  
            totalComparisonCost += right.totalComparisonCost;
            totalParentChildUpdateCost += right.totalParentChildUpdateCost;

            if(inserted){
                if(root->left == NULL){
                    //root->shortestPathLength = 1;
                    root->longestPathLength = 1+root->right->longestPathLength;

                }

                else{
                    //root->shortestPathLength = 1+min(root->left->shortestPathLength, root->right->shortestPathLength);
                    root->longestPathLength = 1+max(root->left->longestPathLength, root->right->longestPathLength);
                }
            }
            return inserted;
        }
    }
    return false;
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
    if (root == NULL){
        return -1;
    }        


    if(root->JourneyCode == jrnyCode){    
        return 1;
    }

    TreeNode* treenode = new TreeNode(jrnyCode, 0);
    bool less = BSTLessThan(treenode, root);
    

    if (!less){
        BST right(root->right, perComparisonCost, perParentChildUpdateCost);
        int found = right.find(jrnyCode);
        int to_add = right.getComparisonCost();

        totalComparisonCost += to_add;
        return (found>0) ? 1 : -1;
    }

    else{
        BST left(root->left,  perComparisonCost, perParentChildUpdateCost);
        int found = left.find(jrnyCode);
        int to_add = left.getComparisonCost();
        if(to_add == -1){to_add = 0;}
        totalComparisonCost += to_add;
        return (found>0) ? 1 : -1;
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


