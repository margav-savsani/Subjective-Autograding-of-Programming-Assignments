// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "tree.h"


// tried to make destructor, but was giving seg faults, so removed it 
// BST::~BST()
// {
//   deleteBST(root);
// }
// void BST::deleteBST(TreeNode* x){
//   if(x == nullptr)
//     return;
//   else{
//     if(x-> left != nullptr)
//       deleteBST(x->left);
//     if(x-> right != nullptr)
//       deleteBST(x->right);
//     delete [] x;
//   }
// }


//finds imbalance in the tree
int BST::getImbalance()
{
  if (root == NULL) return 0;
  else{
    updateLengths(root);
    return root->getImbalance();
  }
}

//Default constructor
BST::BST()
{
  root = nullptr;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{

  TreeNode* z = new TreeNode;
    z->JourneyCode = JourneyCode;
    z->price = price; 
    TreeNode* y = nullptr, *x = root;
    while(x != nullptr){
        y = x;
        if (z->JourneyCode < x->JourneyCode)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;

    if(y == nullptr){
        root = new TreeNode;
        root->JourneyCode = z->JourneyCode;
        root->price = z->price;
        delete [] z;
        return true;
    }
    else if(y->JourneyCode == z->JourneyCode && y->price == z->price)
        return false;
    else if(z->JourneyCode < y->JourneyCode){
        y->left = z;
        return true;
    }
    else{
        y->right = z;
        return true;
    }

  // JourneyCode is not present in the BST.  We must now
  // insert an appropriate child of parentOfCurrNode.
  // Please implement this part yourself.
  //
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to the new node you are inserting
  
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
   TreeNode* x = root;
    while(x != nullptr && x->JourneyCode != JourneyCode){
        if(JourneyCode < x->JourneyCode)
            x = x->left;
        else
            x = x->right;
    }
    if(x != nullptr && price == x->price){
        return true;
    }
    else
        return false;
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
    
   TreeNode* x = root;

    //finds where the node to be deleted is in the tree
    while(x != NULL && price != x->price){
        if(price < x->price)
            x = x->left;
        else
            x = x->right;
    }

    // if node not found, reutrns false
    if(x == NULL || x->JourneyCode != JourneyCode)
        return false;

    //if node is a child, simply remove the pointer to it from its parent, and delete the child
    if(x->left == NULL && x->right == NULL){
        if(x->parent == NULL){
            root = NULL;
            return true;
        }
        else{
            if(x->parent->left != NULL){
                if(x->parent->left->JourneyCode == x->JourneyCode)
                    x->parent->left = NULL;
                else
                    x->parent->right = NULL;
            }
            else
                x->parent->right = NULL;
        }
    }
    // if the node has two children
    else if(x->left != NULL && x->right != NULL){
        TreeNode* y = getMaximum(x->left);
        int tempJourneyCode = y->JourneyCode;
        int tempPrice = y->price;
        remove(tempJourneyCode, tempPrice);
        x->JourneyCode = tempJourneyCode;
        x->price = tempPrice;
    }
    // if the node has only a left child
    else if(x->left != NULL){
        if(x->parent == NULL){
            root = x->left;
            root->parent = NULL;
        }
        else{
            x->left->parent = x->parent;
            if(x->parent->left != NULL){
                if(x->parent->left->JourneyCode == x->JourneyCode)
                    x->parent->left = x->left;
                else
                    x->parent->right = x->left;   
            }
            else
                x->parent->right = x->left;
        }
        x->left = NULL;
        x->right = NULL;
        x->parent = NULL;
    }
    // if the node has only a right child
    else if(x->right != NULL){
        if(x->parent == NULL){
            root = x->right;
            root->parent = NULL;
        }
        else{
            x->right->parent = x->parent;
            if(x->parent->left != NULL){
                if(x->parent->left->JourneyCode == x->JourneyCode){
                    x->parent->left = x->right;
                }
                else
                    x->parent->right = x->right;
            }
            else{
                x->parent->right = x->right;
            }
        }
        x->left = NULL;
        x->right = NULL;
        x->parent = NULL;
    }
    return true;
}

// finds maximum in the BST
TreeNode* BST::getMaximum(TreeNode* y)
{
    while (y->right != nullptr)
        y = y->right;
    return y;
}

void BST::updateLengths(TreeNode* x)
{
  if(x == nullptr)
    return;
  else
  {
        x->shortestPathLength = shortestLength(x);
        x->longestPathLength = longestLength(x);
        updateLengths(x->left);
        updateLengths(x->right);
  }
  return;
}

int BST::shortestLength(TreeNode* x)
{
  if(x->left == nullptr && x->right == nullptr)
    return 1;
  else if(x->left == nullptr)
    return 1+shortestLength(x->right);
  else if(x->right == nullptr)
    return 1+shortestLength(x->left);
  else
    return (1 + min(shortestLength(x->left), shortestLength(x->right)));
}

int BST::longestLength(TreeNode* x)
{
  if(x == nullptr)
    return 0;
  else
    return (1 + max(longestLength(x->left), longestLength(x->right)));
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

