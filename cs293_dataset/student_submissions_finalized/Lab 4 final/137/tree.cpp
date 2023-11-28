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
  
  if(root->JourneyCode == 0 && root->price == 0 && root->left == NULL && root->right == NULL)
    {
      root->JourneyCode = JourneyCode;
      root->price = price;
      root->longestPathLength = 0;
      root->shortestPathLength = 0;
      return true;
    }
    if(root->JourneyCode>=JourneyCode)
    {
      if(root->left == NULL)
      {
        root->left = new TreeNode(JourneyCode, price);
        root->left->parent = root;
        root->left->longestPathLength = 0;
        root->left->shortestPathLength = 0;
        if(root->right != NULL)
        {
          root->longestPathLength = 1 + max(root->left->longestPathLength, root->right->shortestPathLength);
          root->shortestPathLength = 1 + min(root->left->shortestPathLength, root->right->shortestPathLength);
        }
        else
        {
          root->longestPathLength = 1 + root->left->longestPathLength;
          root->shortestPathLength = 1;
        }
        return true;
      }
      else
      {
        root = root->left;
        bool ins = insert(JourneyCode,price);
        root = root->parent;
        if(root->right != NULL)
        {
          root->longestPathLength = 1 + max(root->left->longestPathLength, root->right->longestPathLength);
          root->shortestPathLength = 1 + min(root->left->shortestPathLength, root->right->shortestPathLength);
        }
        else
        {
          root->longestPathLength = 1 + root->left->longestPathLength;
          root->shortestPathLength = 1 + root->left->shortestPathLength;
        }
        return ins;
      }
    }
    else if(root->JourneyCode<JourneyCode)
    {
      if(root->right == NULL)
      {
        root->right = new TreeNode(JourneyCode, price);
        root->right->parent = root;
        root->right->longestPathLength = 0;
        root->right->shortestPathLength = 0;
        if(root->left != NULL)
        {
          root->longestPathLength = 1 + max(root->left->longestPathLength, root->right->longestPathLength); 
          root->shortestPathLength = 1 + min(root->right->shortestPathLength,root->left->shortestPathLength);
        }
        else
        {
          root->longestPathLength = 1 + root->right->longestPathLength;
          root->shortestPathLength = 1;
        }
        return true;
      }
      else
      {
        root = root->right;
        bool ins = insert(JourneyCode,price);
        root = root->parent;
        if(root->left != NULL)
        {
            root->longestPathLength = 1 + max(root->left->longestPathLength, root->right->longestPathLength);
            root->shortestPathLength = 1 + min(root->left->shortestPathLength, root->right->shortestPathLength);
        }
        else
        {
            root->longestPathLength = 1 + root->right->longestPathLength;
            root->shortestPathLength = 1 + root->right->shortestPathLength;
        }
        return ins;
      }
    }
    if(root->JourneyCode == JourneyCode && root->price == price)
    {
      return false;
    }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
  if(root->JourneyCode == JourneyCode && root->price == price)
    {
      return true; 
    }
  else
  {
    if(root->JourneyCode >= JourneyCode && root->left != NULL)
    {
      root = root->left;
      bool fin = find(JourneyCode, price);
      root = root->parent;
      return fin;
    }
    else if(root->JourneyCode<JourneyCode && root->right != NULL)
    {
      root = root->right;
      bool fin = find(JourneyCode, price);
      root = root->parent;
      return fin;
    }
  }
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
  struct TreeNode *x = new TreeNode(root->JourneyCode,root->price,root->left,root->right,root->parent);
  while(true)
  {
    if(x->JourneyCode > JourneyCode && x->left != NULL)
    {
      x = x->left;
      continue;
    }
    else if(x->JourneyCode < JourneyCode && x->right != NULL)
    {
      x = x->right;
      continue;
    }
    else if(x->price == price && x->JourneyCode == JourneyCode)
    {
      if(x->left == NULL && x->right == NULL)
    {
      if(x->parent == NULL)
      {
          delete root;
      }
      else
      {
        if(x == x->parent->left)
        {
            x->parent->left = NULL;
        }
        else
        {
            x->parent->right = NULL;
        }
      }
    }
    else if(x->left == NULL )
    {
      if(x->parent == NULL)
      {
        root = x->right;
      }
      else
      {
        if(x == x->parent->left)
        {
          x->parent->left = x->right;
          x->right->parent = x->parent;
        }
        else
        {
          x->parent->right = x->right;
          x->right->parent = x->parent;
        }
      }
    }
    else if(x->right == NULL)
    {
        if(x->parent == NULL)
        {
            root = x->left;
        }
        else
        {
            if(x == x->parent->left)
            {
              x->parent->left = x->left;
              x->left->parent = x->parent;
            }
            else
            {
              x->parent->right = x->left;
              x->left->parent = x->parent;
            }
        }
    }
    else
    {
        struct TreeNode *suc = new TreeNode(x->right->JourneyCode,x->right->price,x->right->left,x->right->right,x->right->parent);
        while(suc->left != NULL)
        {
          suc = suc->left;
        }
        if(suc->left == NULL && suc->right == NULL)
        {
            if(suc->parent == NULL)
            {
              delete root;
            }
            else
            {
                if(suc == suc->parent->left)
                {
                  suc->parent->left = NULL;
                }
                else
                {
                  suc->parent->right = NULL;
                }
            }
        }
        else if(suc->left == NULL )
        {
            if(suc->parent == NULL)
            {
                root = suc->right;
            }
            else
            {
                if(suc == suc->parent->left)
                {
                    suc->parent->left = suc->right;
                    suc->right->parent = suc->parent;
                }
                else
                {
                    suc->parent->right = suc->right;
                    suc->right->parent = suc->parent;
                }
            }
        }
        else if(suc->right == NULL)
        {
            if(suc->parent == NULL)
            {
                root = suc->left;
            }
            else
            {
                if(suc == suc->parent->left)
                {
                    suc->parent->left = suc->left;
                    suc->left->parent = suc->parent;
                }
                else
                {
                    suc->parent->right = suc->left;
                    suc->left->parent = suc->parent;
                }
            }
        }
        if(x->parent == NULL)
        {
            root = suc;
        }
        else
        {
            if(x == x->parent->left)
            {
                x->parent->left->JourneyCode = suc->JourneyCode;
                x->parent->left->price = suc->price;
            }
            else
            {
                x->parent->right->JourneyCode = suc->JourneyCode;
                x->parent->right->price = suc->price;
            }
        }
      }
      return true;
    }
    else
    {
      return false;
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

