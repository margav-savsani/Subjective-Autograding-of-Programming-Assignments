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

int BST::getImbalance()
{
    root->shortestPathLength = getshortpath(root);
    root->longestPathLength = getlongpath(root);
    return root->getImbalance();
}

int BST::getshortpath(TreeNode *node)
{
    if (node->right == nullptr || node->left == nullptr) return 0;
    else return (1 + min(getshortpath(node->left),getshortpath(node->right)));
}

int BST::getlongpath(TreeNode *node)
{
    if (node->right == nullptr && node->left == nullptr) return 0;
    else if (node->left == nullptr) return (1 + getlongpath(node->right));
    else if (node->right == nullptr) return (1 + getlongpath(node->left));
    else return (1 + max(getlongpath(node->left),getlongpath(node->right)));
}

bool BST::insert(int JourneyCode, int price)
{
  TreeNode *active;
    active = root;                                          // here active changes for every for loop according to price values
    for (int i = 0; i >= 0; i++)
    {
        if (active->JourneyCode == 0)                       // for the initial root case
        {
            active->JourneyCode = JourneyCode;
            active->price = price;
            return true;
        }

        if (active->JourneyCode == JourneyCode)             // inserts the element
            return false;

        if (active->price < price)                          // pushes active to right
        {
            if (active->right == nullptr)
            {
                active->right = new TreeNode(0, 0, nullptr, nullptr, active);
                active->right->parent = active;
            }
            active = active->right;
        }
        else                                                // pushes active to left
        {
            if (active->left == nullptr)
            {
                active->left = new TreeNode(0, 0, nullptr, nullptr, active);
                active->left->parent = active;
            }
            active = active->left;
        }
    }
    return false;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  TreeNode *active;
    active = root;
    for (int i = 0; i >= 0; i++)
    {
        if (active->JourneyCode == JourneyCode)             // returns true if found
            return true;

        if (active->price < price)
        {
            if (active->right == nullptr)
            {
                return false;
            }
            else
                active = active->right;
        }
        else
        {
            if (active->left == nullptr)
            {
                return false;
            }
            else
                active = active->left;
        }
    }

    return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
  TreeNode *active;
    TreeNode *temp;
    active = root;                                          // the function of active here is same as in insert

    for (int i = 0; i >= 0; i++)
    {
        if (active->JourneyCode == JourneyCode)
        {
            if (active->left == nullptr && active->right == nullptr) // no sub nodes case
            {
                if (active->parent == nullptr)
                {
                    active->JourneyCode = 0;
                    active->price = 0;
                    return true;
                }
                else if (active->parent->right == active) // del of root case
                {
                    active->parent->right = nullptr;
                    return true;
                }
                else
                {
                    active->parent->left = nullptr;
                    return true;
                }

                return true;
            }
            else if (active->left == nullptr)               // only right sub node case
            {
                if (active->parent == nullptr)
                {
                    root = active->right;
                    root->parent = nullptr;
                    return true;
                }
                else
                {
                    if (active->parent->right == active)    // both nodes case
                    {
                        active->parent->right = active->right;
                        active->right->parent = active->parent;
                        return true;
                    }
                    else
                    {
                        active->parent->left = active->right;
                        active->right->parent = active->parent;
                        return true;
                    }
                }
            }
            else if (active->right == nullptr)
            {
                if (active->parent == nullptr)
                {
                    root = active->left;
                    root->parent = nullptr;
                    return true;
                }
                else
                {
                    if (active->parent->right == active)
                    {
                        active->parent->right = active->left;
                        active->left->parent = active->parent;
                        return true;
                    }
                    else
                    {
                        active->parent->left = active->left;
                        active->left->parent = active->parent;
                        return true;
                    }
                }
            }
            else
            {
                if (active->parent == nullptr)                  // root del case in both nodes case
                {
                    temp = active->right;
                    while (true)
                    {
                        if (temp->left == nullptr)
                        {
                            temp->left = new TreeNode(active->left->JourneyCode, active->left->price, active->left->left, active->left->right, temp);
                            root = active->right;
                            root->parent = nullptr;
                            return true;
                        }
                        temp = temp->left;
                    }
                }
                else                                            // non root case
                {
                    temp = active->right;
                    while (true)
                    {
                        if (temp->left == nullptr)
                        {
                            temp->left = new TreeNode(active->left->JourneyCode, active->left->price, active->left->left, active->left->right, temp);
                            break;
                        }
                        temp = temp->left;
                    }
                    if (active->parent->right == active)
                    {
                        active->parent->right = active->right;
                        active->right->parent = active->parent;
                        return true;
                    }
                    else
                    {
                        active->parent->left = active->right;
                        active->right->parent = active->parent;
                        return true;
                    }
                }
            }
        }

        if (active->price < price)                              // this loop has similiar function as in insert
        {
            if (active->right == nullptr)
            {
                return false;
            }
            else
                active = active->right;
        }
        else
        {
            if (active->left == nullptr)
            {
                return false;
            }
            else
                active = active->left;
        }
    }

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

