#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "tree.h"

bool BST::updatePathLengths(TreeNode * start)
{
    if (start == nullptr) return 1;
    TreeNode * prnt = start->parent;
    while (prnt != nullptr)
    {
        if (prnt->left == nullptr)
        {
            prnt->shortestPathLength = 1 + (prnt->right)->shortestPathLength;
            prnt->longestPathLength = 1 + (prnt->right)->longestPathLength;
        }
        else if (prnt->right == nullptr)
        {
            prnt->shortestPathLength = 1 + (prnt->left)->longestPathLength;
            prnt->longestPathLength = 1 + (prnt->left)->longestPathLength;
        }
        else
        {
            prnt->shortestPathLength = 1 + min((prnt->left)->shortestPathLength, (prnt->right)->shortestPathLength);
            prnt->longestPathLength = 1 + max((prnt->left)->longestPathLength, (prnt->right)->longestPathLength);
        }
        prnt = prnt->parent;
    }
    return 1;
}

int BST::getshortest(TreeNode * start)
{
    if (start == nullptr) return 0;
    return (1 + min(getshortest(start->left), getshortest(start->right)));
}

int BST::getlongest(TreeNode * start)
{
    if (start == nullptr) return 0;
    return (1 + max(getlongest(start->left), getlongest(start->right)));
}

bool BST::insert(int JourneyCode, int price)
{
    if (find(JourneyCode, price)) return 0;
    TreeNode * newnode = new TreeNode(JourneyCode, price);
    if (root == nullptr) 
    {
        root = newnode;
        root->parent = nullptr;
        return 1;
    }
    TreeNode * where = root;
    bool inserted = 0;
    while (inserted == 0)
    {
        if (newnode->JourneyCode > where->JourneyCode)
        {
            if (where->right == nullptr)
            {
                where->right = newnode;
                newnode->parent = where;
                inserted = 1;
            }
            else where = where->right;
        }
        else 
        {
            if (where->left == nullptr)
            {
                where->left = newnode;
                newnode->parent = where;
                inserted = 1;
            }
            else where = where->left;
        }
    }
    if (updatePathLengths(newnode)) return inserted;
    else return 0;
}

bool BST::find(int JourneyCode, int price)
{
    TreeNode * newnode = new TreeNode(JourneyCode, price);
    if (root == nullptr) return 0;
    TreeNode * spot = root;
    bool found = 0;
    while (found == 0)
    {
        if (spot == nullptr) return 0;
        if (spot->issame(newnode)) return 1;
        //if (spot->price == price && spot->JourneyCode != JourneyCode) return 0;
        //if (spot->price != price && spot->JourneyCode == JourneyCode) return 0;
        if (spot->JourneyCode < newnode->JourneyCode)
        {
            spot = spot->right;
        }
        else
        {
            spot = spot->left;
        }
    }
    return found;
}

TreeNode * BST::minimum(TreeNode * start)
{
    if (start == nullptr) return nullptr;
    while (start->left != nullptr) start = start->left;
    return start;
}

TreeNode * BST::successor(TreeNode * x)
{
    if (x == nullptr) return nullptr;
    if (x->right != nullptr) return minimum(x->right);
    else
    {
        TreeNode * p = x->parent;
        if (x == p->left) return p;
        while (p != nullptr && x == p->right)
        {
            x = p;
            p = p->parent;
        }
        return p;
    }
}

bool BST::remove(int JourneyCode, int price)
{
    if (!find(JourneyCode, price)) return 0;
    TreeNode * todelete = new TreeNode(JourneyCode, price);
    TreeNode * lowest = nullptr;
    TreeNode * spot = root;
    TreeNode *prnt = nullptr;
    bool deleted = 0;
    while (deleted == 0)
    {
        if (spot->issame(todelete)) 
        {
            // 3 cases ---- return 1 at the end
            // if (spot == nullptr) return 0;
            // when spot is a leaf
            if (spot->left == nullptr && spot->right == nullptr)
            {
                if (spot == root) {root = nullptr; deleted = 1; continue;}
                if (spot == prnt->left) prnt->left = nullptr;
                else prnt->right = nullptr;
                
            }
            // when the spot has one child
            else if (spot->left != nullptr && spot->right == nullptr)
            {
                if (spot == root) {root = spot->left; deleted = 1; continue;}
                if (spot == prnt->left) prnt->left = spot->left;
                else prnt->right = spot->left;
            }
            else if (spot->left == nullptr && spot->right != nullptr)
            {
                if (spot == root) {root = spot->right; deleted = 1; continue;}
                if (spot == prnt->left) prnt->left = spot->right;
                else prnt->right = spot->right;
            }
            //when the spot has two children
            else
            {
                TreeNode * succ = successor(spot);
                remove(succ->JourneyCode, succ->price);
                if (spot == root) {root = succ; succ->left = spot->left; succ->right = spot->right; return 1;}
                if (spot == prnt->left) prnt->left = succ;
                else prnt->right = succ;
                succ->left = spot->left;
                succ->right = spot->right;
            }
            // modifying path lengths
            if (prnt->left == nullptr && prnt->right == nullptr) 
            {
                prnt->shortestPathLength = 0;
                prnt->longestPathLength = 0;
            }
            else if (prnt->left == nullptr)
            {
                prnt->shortestPathLength = 1 + (prnt->right)->shortestPathLength;
                prnt->longestPathLength = 1 + (prnt->right)->longestPathLength;
            }
            else if (prnt->right == nullptr)
            {
                 prnt->shortestPathLength = 1 + (prnt->left)->shortestPathLength;
                prnt->longestPathLength = 1 + (prnt->left)->longestPathLength;
            }
            else
            {
                prnt->shortestPathLength = 1 + min((prnt->left)->shortestPathLength, (prnt->right)->shortestPathLength);
                prnt->longestPathLength = 1 + max((prnt->left)->longestPathLength, (prnt->right)->longestPathLength);
            }
            updatePathLengths(prnt);
            deleted = 1;
        }
        if (spot->price < todelete->price)
        {
            prnt = spot;
            spot = spot->right;
        }
        else if (spot->price > todelete->price)
        {
            prnt = spot;
            spot = spot->left;
        }
    }
    return deleted;
}

int BST::getImbalance()
{
    if (root == nullptr) return 0;
    else return root->getImbalance();
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

