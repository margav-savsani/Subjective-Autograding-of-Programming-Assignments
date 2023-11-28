// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "tree.h"

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

int BST::getImbalance()
{
  if (root == nullptr) return 0;
  else if (root->left == nullptr){
    return root->longestPathLength;
  }
  else return root->getImbalance();
}

bool BST::insert(int JourneyCode, int price) { // time : O(h), h is height of the tree
    /* this has been iteratively written. If two journeys have the same price,
    we go to the right subtree */
    TreeNode * A = this->root;
    bool b = 0;
    while (true){
        if (root == nullptr){
            root = new TreeNode(JourneyCode, price);
            A = root;
            b = 1;
            break;
        }
        if (A->parent == nullptr && A->JourneyCode == 0 && A->price == 0){
            A->JourneyCode = JourneyCode;
            A->price = price;
            b = 1;
            break;
        }
        if (A->JourneyCode == JourneyCode && A->price != price){
            return 0;
        }

        if (JourneyCode >= A->JourneyCode && A->right != nullptr){
            A = A->right;
            continue;
        }
        else if (JourneyCode < A->JourneyCode && A->left != nullptr){
            A = A->left;
            continue;
        }
        else if (JourneyCode < A->JourneyCode && A->left == nullptr){
            A->left = new TreeNode(JourneyCode, price);
            A->left->parent = A;
            A = A->left;
            b = 1;
            break;
        }
        else if (JourneyCode >= A->JourneyCode && A->right == nullptr){
            A->right = new TreeNode(JourneyCode, price);
            A->right->parent = A;
            A = A->right;
            b = 1;
            break;
        }
    }
    
    if (b){
        update_minmax(A);
        return 1;
    }

    return false;
}

void BST::update_minmax(TreeNode * N){
    TreeNode * A = N;
    while (A->parent != nullptr){
        int mindistl = -1;
        int maxdistl = -1;
        bool b1 = 0;
        bool b2 = 0;
        int maxdistr = -1;
        int mindistr = -1;
        if (A->parent->right != nullptr){
            maxdistr = A->parent->right->longestPathLength;
            mindistr = A->parent->right->shortestPathLength;
        }
        if (A->parent->left != nullptr){
            maxdistl = A->parent->left->longestPathLength;
            mindistl = A->parent->left->shortestPathLength;
        }
        // cout << maxdistl << " " << maxdistr << endl;
        // cout << mindistl << " " << mindistr << endl;
        if (maxdistl >= maxdistr){
            A->parent->longestPathLength = maxdistl+1;
        }
        else{
            A->parent->longestPathLength = maxdistr+1;
        }
        if (mindistl <= mindistr){
            A->parent->shortestPathLength = mindistl+1;
        }
        else{
            A->parent->shortestPathLength= mindistr+1;
        }
        // cout << "HI: " << A->JourneyCode << " " << A->shortestPathLength << " " << A->longestPathLength << endl;
        A =  A->parent;
    }
    // cout << "HI: " << A->JourneyCode << " " << A->shortestPathLength << " " << A->longestPathLength << endl;
}

bool BST::find(int JourneyCode, int price) { // time: O(h), h is height of the tree
    /* this has been iteratively written. If two journeys have the same price,
    we go to the right subtree */ 
    TreeNode * A = this->root;
    while(true){
        if (A->JourneyCode == JourneyCode){
            if (A->price == price){
                return 1;
            }
            return 0;
        }
        else if(A->JourneyCode > JourneyCode){
            if (A->left == nullptr){
                return 0;
            }
            A = A->left;
            continue;
        }
        else if(A->JourneyCode < JourneyCode){
            if (A->right == nullptr){
                return 0;
            }
            A = A->right;
            continue;
        }
    }
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // Recall from CS 213 lectures about the various ways in which the
  // BST can be restructured when a node is deleted. You can implement
  // any of these alternatives.
  //
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to nodes whose position in the BST is affected
  // by the remove.
    
  return false;
}

// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
void BST::printBST(const string& prefix, bool isLeft=false)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->JourneyCode << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::getBST(const string& prefix,  bool isLeft=false)
{
    if( root != nullptr )
    {
        result.push_back(prefix);

        result.push_back(isLeft ? "|--" : "|__" );

        // print the value of the node
        result.push_back(to_string(root->JourneyCode) + "\n");
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        getBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        getBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::clearResult(){
    result.clear();
}

vector<string> BST::getResult(){
    return result;
}
