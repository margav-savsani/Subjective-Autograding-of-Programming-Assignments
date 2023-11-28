// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include "tree.h"
using namespace std;



// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

TreeNode *getmaxnode(TreeNode *T)
{
    if (T->right == NULL)
        return T;
    else
        return getmaxnode(T->right);
}
TreeNode *BST::search(TreeNode *T, int price)
{
    if (T == NULL)
    {
        return NULL;
    }
    if (T->price == price)
        return T;
    if (T->price < price)
    {
        return search(T->right, price);
    }
    else
        return search(T->left, price);
}
TreeNode *BST::predecessor(TreeNode *T, int price)
{
    if (T == NULL)
        return NULL;
    if (T->price == price)
    {
        if (T->left == NULL)
            return NULL;
        else
            return getmaxnode(T->left);
    }
    else
    {
        if (price < T->price)
            return predecessor(T->left, price);
        else
            return predecessor(T->right, price);
    }
}

int BST::getImbalance()
{
  if (root == nullptr) return 0;
  else return root->getImbalance();
}

bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  
  struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  
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
    }

    // JourneyCode is not present in the BST.  We must now
    // insert an appropriate child of parentOfCurrNode.
    // Please implement this part yourself.
    //
    // Do not forget to update shortestPathLength and
    // longestPathLength of (possibly all) BST nodes in the
    // path from the root to the new node you are inserting
    

    return true;
}
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
   if (search(root, price) == NULL)
        return false;
    else
    {
        TreeNode *found = search(root, price);
        if (found->JourneyCode == JourneyCode)
            return true;
        else
            return false;
    }
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    if (!find(JourneyCode, price))
        return false;
    else
    {
        TreeNode *found = search(root, price);
        if (found == root)
        {
            if ((found->right == NULL) && (found->left == NULL))
            {
                root = NULL;
                found = new TreeNode;
                return true;
            }
            else if ((found->right == NULL) || (found->left == NULL))
            {
                if (found->left == NULL)
                {
                    root = found->right;
                    found->right->parent = NULL;
                    found = new TreeNode;
                    return true;
                }
                else
                {
                    root = found->left;
                    found->left->parent = NULL;
                    found = new TreeNode;
                    return true;
                }
            }
            else
            {
                TreeNode *temp = predecessor(root, found->price);
                if(temp->parent == found)
                {
                    temp->parent = NULL;
                    temp->right = found->right;
                    found->right->parent = temp;
                    root = temp;
                    found = new TreeNode;
                    return true;
                }
                else if (temp->left == NULL)
                {
                    root = temp;
                    temp->parent->right = NULL;
                    temp->parent = NULL;
                    found->right->parent = temp;
                    found->left->parent = temp;
                    temp->left = found->left;
                    temp->right = found->right;
                    found = new TreeNode;
                    return true;
                }
                else
                {
                    root = temp;
                    temp->parent->right = temp->left;
                    temp->left->parent = temp->parent;
                    temp->left = found->left;
                    found->left->parent = temp;
                    temp->parent = NULL;
                    temp->right = found->right;
                    found->right->parent = temp;
                    found = new TreeNode;
                    return true;
                }
            }
        }
        if ((found->right == NULL) && (found->left == NULL))
        {
            if (found == root)
            {
                root = new TreeNode;
                return true;
            }
            TreeNode *parent = found->parent;
            if (parent->right == found)
            {
                parent->right = NULL;
                found = new TreeNode;
                return true;
            }
            else
            {
                parent->left = NULL;
                found = new TreeNode;
                return true;
            }
        }
        else if ((found->right == NULL) || (found->left == NULL))
        {
            if (found->right == NULL)
            {
                TreeNode *temp = found->parent;
                if (temp->left == found)
                {
                    temp->left = found->left;
                    found->left->parent = temp;
                    found = new TreeNode;
                    return true;
                }
                else
                {
                    temp->right = found->left;
                    found->left->parent = temp;
                    found = new TreeNode;
                    return true;
                }
            }
            else
            {

                TreeNode *temp = found->parent;
                if (temp->left == found)
                {
                    temp->left = found->right;
                    found->right->parent = temp;
                    found = new TreeNode;
                    return true;
                }
                else
                {
                    temp->right = found->right;
                    found->right->parent = temp;
                    found = new TreeNode;
                    return true;
                }
            }
        }
        else
        {
            TreeNode *temp = predecessor(root, found->price);
            if (temp->left == NULL)
            {
                if (temp->parent != root)
                {
                    temp->parent->right = NULL;
                }
                else
                {
                    root = temp;
                }
                if (found->parent != NULL)
                {
                    if (found->parent->right == found)
                    {
                        found->parent->right = temp;
                    }
                    else
                    {
                        found->parent->left = temp;
                    }
                }
                temp->parent = found->parent;
                found->right->parent = temp;
                found->left->parent = temp;
                temp->left = found->left;
                temp->right = found->right;
                found = new TreeNode;
                return true;
            }
            else
            {
                if (temp->parent != found)
                {
                    temp->parent->right = temp->left;
                    temp->left->parent = temp->parent;
                    temp->left = found->left;
                    found->left->parent = temp;
                }
                if (found->parent != NULL)
                {
                    if (found->parent->right == found)
                    {
                        found->parent->right = temp;
                    }
                    else
                    {
                        found->parent->left = temp;
                    }
                }
                temp->right = found->right;
                found->right->parent = temp;
                temp->parent = found->parent;
                found = new TreeNode;
                return true;
            }
        }
    }
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

