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
  else return root->getImbalance();
}

int BST::shortLength(int x,TreeNode* node)
{
    if (node == NULL)
        return 0;
 
    if (node->left == NULL && node->right == NULL)
    {
        return 1;
    }
    // Recur for left and right subtrees
    shortLength(x+1,node->left);
    shortLength(x+1,node->right);
    
}


bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  
  /*struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  
  while (currNode != nullptr) {
    if (currNode->JourneyCode < JourneyCode) {
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }
    else if (currNode->JourneyCode > JourneyCode) {
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
    else { // currNode->JourneyCode == JourneyCode
      return false;
    }*/
    if (root == nullptr)
    {
        root = new TreeNode(JourneyCode, price);
        root->shortestPathLength=0;
        root->longestPathLength=0;
        return true;
    }

    else
    {
        TreeNode *Root = root;
        while (true)
        {
            if (Root->JourneyCode == JourneyCode)
            {
                return false;
            }
            if (Root->JourneyCode < JourneyCode)
            {
                if (Root->right == NULL)
                {
                    //Root->longestPathLength++;
                    Root->right = new TreeNode(JourneyCode, price, nullptr, nullptr, Root);
                    Root->right->shortestPathLength = 0; 
                    Root->right->longestPathLength = 0;
                    return true;
                }
                else
                {
                    Root = Root->right;
                    continue;
                }
            }
            else
            {
                if (Root->left == NULL)
                {
                    //Root->longestPathLength++;
                    Root->left = new TreeNode(JourneyCode, price, nullptr, nullptr, Root);
                    Root->left->shortestPathLength=0;
                    Root->left->longestPathLength=0;
                    return true;
                }
                else
                {
                    Root = Root->left;
                    continue;
                }
            }
        }
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
    if (root == nullptr)
    {
        return false;
    }
    TreeNode *Root = root;
    while (true)
    {
        if (Root->price == price && Root->JourneyCode == JourneyCode)
        {
            return true;
        }
        else
        {
            if (Root->JourneyCode < JourneyCode)
            {
                if (Root->right == nullptr)
                {
                    //  delete[] Root;
                    return false;
                }
                else
                {
                    Root = Root->right;
                    continue;
                }
            }
            else
            {
                if (Root->left == nullptr)
                {
                    //  delete[] Root
                    return false;
                }
                else
                {
                    Root = Root->left;
                    continue;
                }
            }
        }
    }
  
  return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    TreeNode *Root = root;
    while (true)
    {
        if (Root == nullptr)
        {
            return false;
        }
        if (Root->JourneyCode == JourneyCode && Root->price == price)
        {
            if (Root == root)
            {
                if (Root->left == nullptr && Root->right == nullptr)
                {
                    root = nullptr;
                    return true;
                }
                else if (Root->left == nullptr)
                {
                    root = Root->right;
                    root->parent = nullptr;
                    delete[] Root;
                    return true;
                }
                else if (Root->right == nullptr)
                {
                    root = Root->left;
                    root->parent = nullptr;
                    delete[] Root;
                    return true;
                }
                else
                {
                    TreeNode *pred = Root;
                    pred = pred->left;
                    while (pred->right != nullptr)
                    {
                        pred = pred->right;
                    }
                    Root->JourneyCode = pred->JourneyCode;
                    Root->price = pred->price;
                    Root->left = pred->left;

                    if (pred->left != nullptr)
                    {
                        pred->parent->right = pred->left;
                        pred->left->parent = pred->parent;
                        delete[] pred;
                        return true;
                    }
                    else
                    {
                        delete[] pred;
                        return true;
                    }
                }
            }
            else if (Root->left == nullptr && Root->right == nullptr)
            {
                if (Root->parent->left == Root)
                {
                    Root->parent->left = nullptr;
                }
                else if (Root->parent->right == Root)
                {
                    Root->parent->right = nullptr;
                }
                delete[] Root;
                return true;
            }
            else if (Root->left == nullptr)
            {
                if (Root->parent->left == Root)
                {
                    Root->parent->left = Root->right;
                    Root->right->parent = Root->parent;
                    delete[] Root;
                    return true;
                }
                else if (Root->parent->right == Root)
                {
                    Root->parent->right = Root->right;
                    Root->right->parent = Root->parent;
                    delete[] Root;
                    return true;
                }
            }
            else if (Root->right == nullptr)
            {
                if (Root->parent->left == Root)
                {
                    Root->parent->left = Root->left;
                    Root->left->parent = Root->parent;
                    delete[] Root;
                    return true;
                }
                else if (Root->parent->right == Root)
                {
                    Root->parent->right = Root->left;
                    Root->left->parent = Root->parent;
                    delete[] Root;
                    return true;
                }
            }
            else
            {
                TreeNode *pred = Root->left;
                while (pred->right != nullptr)
                {
                    pred = pred->right;
                }
                Root->JourneyCode = pred->JourneyCode;
                Root->price = pred->price;
                Root->left = pred->left;
                if (pred->left != nullptr)
                {
                    pred->parent->right = pred->left;
                    // pred->left->parent=pred->parent;
                    delete[] pred;
                    return true;
                }
                else
                {
                    pred->parent->left = nullptr;
                    delete[] pred;
                    return true;
                }
            }
        }
        else if (Root->JourneyCode < JourneyCode)
        {
            Root = Root->right;
            continue;
        }
        else
        {
            Root = Root->left;
            continue;
        }
    }
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

