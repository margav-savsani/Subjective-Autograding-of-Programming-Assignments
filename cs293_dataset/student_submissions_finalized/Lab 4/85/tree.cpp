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

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  {
    while (s != NULL)
    {
        if (s->price == price)
        {
            
            
            return s;
        }
        else if (s->price > price)
        {
            return Search(s->left,  price);
        }
        else
        {
             return Search(s->right,  price);
        }
    }
    return NULL;
}
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
  
  return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
  {
    if (node == root)
        {
            if ((node->right == NULL) && (node->left == NULL))
            {
                root = NULL;
                node = new TreeNode;
                return true;
            }
            else if ((node->right == NULL) || (node->left == NULL))
            {
                if (node->left == NULL)
                {
                    node = node->right;
                    node->right->parent = NULL;
                    node = new TreeNode;
                    return true;
                }
                else
                {
                    root = node->left;
                    node->left->parent = NULL;
                    node = new TreeNode;
                    return true;
                }
            }
            else
            {
                TreeNode *t = pre(root, node->price);
                if(t->parent == node)
                {
                    t->parent = NULL;
                    t->right = node->right;
                    node->right->parent = t;
                    root = t;
                    node = new TreeNode;
                    return true;
                }
                else if (t->left == NULL)
                {
                    root = t;
                    t->parent->right = NULL;
                    t->parent = NULL;
                    node->right->parent = t;
                    node->left->parent = t;
                    t->left = node->left;
                    t->right = node->right;
                    node = new TreeNode;
                    return true;
                }
                else
                {
                    root = t;
                    t->parent->right = t->left;
                    t->left->parent = t->parent;
                    t->left = node->left;
                    node->left->parent = t;
                    node->parent = NULL;
                    t->right = node->right;
                    node->right->parent = t;
                    node = new TreeNode;
                    return true;
                }
            }
        }
    if (node == NULL)
    {
        return false;
    }
    if ((node->left == NULL) && (node->right == NULL))
    {
        
         if(node->parent->left == node){node->parent->left = NULL;root = new TreeNode;return true;}
        else {node->parent->right = NULL;root = new TreeNode;return true;}
    }
    if ((node->right == NULL) || (node->left == NULL))
        {
            if (node->right == NULL)
            {
                TreeNode *temp = node->parent;
                if (temp->left == node)
                {
                    temp->left = node->left;
                    node->left->parent = temp;
                    node = new TreeNode;
                    return true;
                }
                else
                {
                    temp->right = node->left;
                    node->left->parent = temp;
                    node = new TreeNode;
                    return true;
                }
            }
            else
            {

                TreeNode *temp = node->parent;
                if (temp->left == node)
                {
                    temp->left = node->right;
                    node->right->parent = temp;
                    node = new TreeNode;
                    return true;
                }
                else
                {
                    temp->right = node->right;
                    node->right->parent = temp;
                    node = new TreeNode;
                    return true;
                }
            }
        }
    TreeNode *P = new TreeNode;

    P = pre(node, price);
 if (P->left == NULL)
    {
        if (node->parent->left == node)
        {
            P->parent->right = NULL;
            P->right = node->right;
            node->parent->left = P;
            P->parent = node->parent; 
            node = new TreeNode;
            return true;
        }
        else
        {
            P->right = node->right;
            node->parent->right = P;
            P->parent = node->parent;
            node = new TreeNode;
            return true;
        }
    }
    if (P->left != NULL)
    {
        P->parent->right = P->left;
        P->left->parent = P->parent;
        if (node->parent->left == node)
        {
            P->right = node->right;
            node->parent->left = P;
            P->parent = node->parent;
            node = new TreeNode;
            return true;
        }
        else
        {
            P->right = node->right;
            node->parent->right = P;
            P->parent = node->parent;
            node = new TreeNode;
            return true;
        }
    }

    return true;
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

