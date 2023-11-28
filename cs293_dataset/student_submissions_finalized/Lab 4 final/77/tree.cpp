#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
#include "tree.h"

int BST::getImbalance()
{
    if (root == nullptr)
        return 0;
    // else return root->getImbalance();
    return (longestPath(root) - shortestPath(root));
}
int BST::longestPath(TreeNode *node)
{
    if (node->left == NULL && node->right == NULL)
    {
        return 0;
    }
    else if (node->left == NULL)
    {
        return (1 + longestPath(node->right));
    }
    else if (node->right == NULL)
    {
        return (1 + longestPath(node->left));
    }
    else
    {
        return (1 + max(longestPath(node->left), longestPath(node->right)));
    }
}
int BST::shortestPath(TreeNode *node)
{
    if (node->left == NULL && node->right == NULL)
    {
        return 0;
    }
    else if (node->left == NULL)
    {
        return 0;
    }
    else if (node->right == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + min(shortestPath(node->left), shortestPath(node->right));
    }
}
// Insertion: Copied from lab 3 as per instructions.
bool BST::insert(int JourneyCode, int price)
{
    TreeNode *temp = new TreeNode(JourneyCode, price);
    TreeNode *t = new TreeNode();
    t = root;
    if (root == NULL)
    {
        root = temp;
        return true;
    }
    else
    {
        while (t != NULL)
        {
            if (t->price == price && t->JourneyCode == JourneyCode)
            {
                return false;
            }
            else if (t->JourneyCode <= JourneyCode)
            {
                if (t->right == NULL)
                {
                    TreeNode *temp = new TreeNode(JourneyCode, price, NULL, NULL, t);
                    t->right = temp;
                    temp->parent = t;
                    t->right->left = NULL;
                    t->right->right = NULL;
                    return (true);
                }
                t = t->right;
            }
            else
            {
                if (t->JourneyCode > JourneyCode)
                {
                    if (t->left == NULL)
                    {
                        TreeNode *temp = new TreeNode(JourneyCode, price, NULL, NULL, t);
                        t->left = temp;
                        temp->parent = t;
                        t->left->left = NULL;
                        t->left->right = NULL;
                        return (true);
                    }
                    t = t->left;
                }
            }
        }
    }

    return false;
}
// FIND function: Copied from lab 3 as per instructions.
bool BST::find(int JourneyCode, int price)
{
    TreeNode *temp = new TreeNode();
    temp = root;
    while (temp != NULL)
    {
        if (temp->price == price && temp->JourneyCode == JourneyCode)
        {
            return true;
        }
        else if (temp->JourneyCode > JourneyCode)
        {
            temp = temp->left;
        }
        else
            temp = temp->right;
    }
    return false;
}
// Remove: Copied from lab 3 as per instructions.
bool BST::remove(int JourneyCode, int price)
{
    if (!find(JourneyCode, price))
    {
        return false;
    }
    TreeNode *x = new TreeNode();
    x = NULL;
    TreeNode *z = new TreeNode();
    z = root;
    while (z != NULL)
    {
        if (z->price == price && z->JourneyCode == JourneyCode)
        {
            break;
        }
        else if (z->JourneyCode > JourneyCode)
        {
            if (z->left != NULL)
                z = z->left;
        }
        else if (z->JourneyCode < JourneyCode)
        {
            if (z->right != NULL)
                z = z->right;
        }
    }

    if (z->left == NULL && z->right == NULL) // when leaf is deleted
    {
        if (z == root)
        {
            root = NULL;
            return true;
        }
        else if (z->parent->left == z)
        {
            z->parent->left = NULL;
            z->parent = NULL;
            return true;
        }
        else
        {
            z->parent->right = NULL;
            z->parent = NULL;
            return true;
        }
    }
    else if (z->left == NULL) // when delete element has only right child.
    {
        if (z == root)
        {
            z->right->parent = NULL;
            root = root->right;
            return true;
        }
        else if (z->parent->left == z)
        {
            z->right->parent = z->parent;
            z->parent->left = z->right;
            return true;
        }
        else
        {
            z->right->parent = z->parent;
            z->parent->right = z->right;
            return true;
        }
    }
    else if (z->right == NULL) // when delete element has only left child.
    {
        if (z == root)
        {
            z->left->parent = NULL;
            root = root->left;
            return true;
        }
        else if (z->parent->left == z)
        {
            z->left->parent = z->parent;
            z->parent->left = z->left;
            return true;
        }
        else
        {
            z->left->parent = z->parent;
            z->parent->right = z->left;
            return true;
        }
    }
    else
    {
        x = predecessor(z);       // predecessor
        if (x->parent->left == x) // when deleted element has 2 children
        {
            x->parent->left = x->left;
        }
        if (x->parent->right == x) // I exchanged predecessor values with delete element values.
        {                          // So works get easy :)
            x->parent->right = x->left;
        }
        if (x->left != NULL)
        {
            x->left->parent = x->parent;
        }

        z->JourneyCode = x->JourneyCode;
        z->price = x->price;
        return true;
    }
}
// predecessor: Copied from lab 3 as per instructions.
struct TreeNode *BST::predecessor(TreeNode *curr)
{ // find predecessor
    if (curr->left != NULL)
    {
        curr = curr->left;

        while (curr->right != NULL)
        {
            curr = curr->right;
        }
    }
    return curr;
}

// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
void BST::printBST(const string &prefix, bool isLeft = false)
{
    if (root != nullptr)
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__");

        // print the value of the node
        cout << root->JourneyCode << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST(prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST(prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::getBST(const string &prefix, bool isLeft = false)
{
    if (root != nullptr)
    {
        result.push_back(prefix);

        result.push_back(isLeft ? "|--" : "|__");

        // print the value of the node
        result.push_back(to_string(root->JourneyCode) + "\n");
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        getBST(prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        getBST(prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::clearResult()
{
    result.clear();
}

vector<string> BST::getResult()
{
    return result;
}
