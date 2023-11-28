// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
#include "tree.h"
#include <cmath>


 

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

int path(TreeNode* head, int select)
{
    if (head == NULL) return 0;
    if (head->left == NULL && head->right == NULL) return 1;
    int left_height = path(head->left, select);
 
    int right_height = path(head->right, select);

    if(select == 0)
    {
      if(head->left != NULL) head->left->shortestPathLength = left_height;
      if(head->right != NULL) head->right->shortestPathLength = right_height;
    }
    else 
    {
      if(head->left != NULL) head->left->longestPathLength = left_height;
      if(head->right != NULL) head->right->longestPathLength = right_height;
    }
    if(select == 0)
    {
      if(head->left == NULL) {return 1 + path(head->right,0);}
      else if(head->right == NULL) {return 1 + path(head->left,0);}
      return  1 + min(left_height, right_height);
    }
    else
    {
      return  1 + max(left_height, right_height);
    }
}
 

TreeNode *getmaxnode(TreeNode *T)
{
    if (T->right == NULL)
        return T;
    else
        return getmaxnode(T->right);
}
TreeNode *BST::search(TreeNode *T, int JourneyCode)
{
    if (T == NULL)
    {
        return NULL;
    }
    if (T->JourneyCode == JourneyCode)
        return T;
    if (T->JourneyCode < JourneyCode)
    {
        return search(T->right, JourneyCode);
    }
    else
        return search(T->left, JourneyCode);
}
TreeNode *BST::predecessor(TreeNode *T, int JourneyCode)
{
    if (T == NULL)
        return NULL;
    if (T->JourneyCode == JourneyCode)
    {
        if (T->left == NULL)
            return NULL;
        else
            return getmaxnode(T->left);
    }
    else
    {
        if (JourneyCode < T->JourneyCode)
            return predecessor(T->left, JourneyCode);
        else
            return predecessor(T->right, JourneyCode);
    }
}

int BST::getImbalance()
{
  if (root == NULL) return 0;
  else return root->getImbalance();
}

bool BST::insert(int JourneyCode, int price)
{
  if (search(root, JourneyCode) != NULL)
    {
        return false;
    } 
    else
    {
        TreeNode *newnode = new TreeNode;
        newnode->JourneyCode = JourneyCode;
        newnode->price = price;
        newnode->parent = NULL;
        newnode->left = NULL;
        newnode->right = NULL;
        if (root == NULL)
        {
            root = new TreeNode;
            root->parent = NULL;
            root->JourneyCode = JourneyCode;
            root->price = price;
            root->longestPathLength = 0; root->shortestPathLength = 0;
            return true;
        }
        TreeNode *T = root;
        TreeNode *temp = new TreeNode;
        int left_h,right_h;
        while (T != NULL)
        {
            temp = T;
            if (JourneyCode < T->JourneyCode)
                T = T->left;
            else
                T = T->right;
        }
        if (JourneyCode < temp->JourneyCode)
        {
            temp->left = newnode;
            newnode->parent = temp;
            root->shortestPathLength = path(root,0);
            root->longestPathLength = path(root,1);
            return true;
        }
        else
        {
            temp->right = newnode;
            newnode->parent = temp;
            root->shortestPathLength = path(root,0);
            root->longestPathLength = path(root,1);
            return true;
        }
    }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
   if (search(root, JourneyCode) == NULL)
        return false;
    else
    {
        TreeNode *found = search(root, JourneyCode);
        if (found->price == price)
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
        TreeNode *found = search(root, JourneyCode);
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
                    root->shortestPathLength = path(root,0);
                    root->longestPathLength = path(root,1);
                    return true;
                }
                else
                {
                    root = found->left;
                    found->left->parent = NULL;
                    found = new TreeNode;
                    root->shortestPathLength = path(root,0);
                    root->longestPathLength = path(root,1);
                    return true;
                }
            }
            else
            {
                TreeNode *temp = predecessor(root, found->JourneyCode);
                if(temp->parent == found)
                {
                    temp->parent = NULL;
                    temp->right = found->right;
                    found->right->parent = temp;
                    root = temp;
                    found = new TreeNode;
                    root->shortestPathLength = path(root,0);
                    root->longestPathLength = path(root,1);
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
                    root->shortestPathLength = path(root,0);
                    root->longestPathLength = path(root,1);
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
                    root->shortestPathLength = path(root,0);
                    root->longestPathLength = path(root,1);
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
                root->shortestPathLength = path(root,0);
                root->longestPathLength = path(root,1);
                return true;
            }
            else
            {
                parent->left = NULL;
                found = new TreeNode;
                root->shortestPathLength = path(root,0);
                root->longestPathLength = path(root,1);
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
                    root->shortestPathLength = path(root,0);
                    root->longestPathLength = path(root,1);
                    return true;
                }
                else
                {
                    temp->right = found->left;
                    found->left->parent = temp;
                    found = new TreeNode;
                    root->shortestPathLength = path(root,0);
                    root->longestPathLength = path(root,1);
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
                    root->shortestPathLength = path(root,0);
                    root->longestPathLength = path(root,1);
                    return true;
                }
                else
                {
                    temp->right = found->right;
                    found->right->parent = temp;
                    found = new TreeNode;
                    root->shortestPathLength = path(root,0);
                    root->longestPathLength = path(root,1);
                    return true;
                }
            }
        }
        else
        {
            TreeNode *temp = predecessor(root, found->JourneyCode);
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
                root->shortestPathLength = path(root,0);
                root->longestPathLength = path(root,1);
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
                root->shortestPathLength = path(root,0);
                root->longestPathLength = path(root,1);
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

