#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST() { root = nullptr; }
BST::BST(TreeNode *root)
{
    this->root = root;
}
void BST::MYIN_ORDER(TreeNode *y) // inorder traversal basically
{
    if (y != nullptr)
    {

        MYIN_ORDER(y->left);
        cout << y->JourneyCode << endl;
        MYIN_ORDER(y->right);
    }
    else
    {
        return;
    }
}
bool BST::check(int JourneyCode, int price, TreeNode *y) // checking if a journey code is present or not
{
    bool b = false, c = false;
    if (y->JourneyCode == JourneyCode)
    {
        return true;
    }

    if (y->left != nullptr)
    {
        b = check(JourneyCode, price, y->left);
    }
    if (y->right != nullptr)
    {
        c = check(JourneyCode, price, y->right);
    }
    return (b || c);
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) // inserting a node
{

    // TreeNode *y = new TreeNode;
    // y->left=nullptr
    TreeNode *res = new TreeNode;
    TreeNode *y = nullptr;

    if (root == nullptr) // inserting at root
    {
        root = new TreeNode(JourneyCode, price, nullptr, nullptr, nullptr);

        return true;
    }

    else
    {

        TreeNode *x = root;
        if (check(JourneyCode, price, x)) // if a journey code is present , insertion failed
        {
            return false;
        }
        while (x != nullptr) // if prices are same insert at right
        {

            if (price >= x->price)
            {
                y = x;
                x = x->right;
            }
            else if (price < x->price)
            {
                y = x;
                x = x->left;
            }
        }
        if (price < y->price)
        {
            res->parent = y;
            y->left = res;
            res->JourneyCode = JourneyCode;
            res->price = price;
        }
        else
        {
            res->parent = y;
            y->right = res;
            res->JourneyCode = JourneyCode;
            res->price = price;
        }
    }

    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) // finding a node using binary search
{

    TreeNode *x = root;

    while (x != nullptr)
    {

        if (x->price == price && x->JourneyCode == JourneyCode)
        {
            return true;
        }
        if (x->price > price)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }

    return false;
}
TreeNode *BST::predecessor(TreeNode *z) // finding the largest number less than the given node
{

    if (z->left != nullptr)
    {
        TreeNode *t1 = z->left;
        while (t1->right != nullptr)
        {
            t1 = t1->right;
        }

        return t1;
    }
    if (z->parent == nullptr)
    {
        return nullptr;
    }
    TreeNode *t1 = z->parent;
    TreeNode *t2 = z;
    while (t1 != nullptr)
    {
        if (t1->right == t2)
        {
            return t1;
        }
        t2 = t1;
        t1 = t1->parent;
    }
    return nullptr;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) // Deletion  , 3 different cases
{
    if (find(JourneyCode, price))
    {
        TreeNode *x = root;
        while (x != nullptr)
        {

            if (x->price == price && x->JourneyCode == JourneyCode)
            {
                if (x->left == nullptr && x->right == nullptr)
                {
                    TreeNode *Y = x->parent;
                    if (x == Y->left)
                    {
                        Y->left = nullptr;
                    }
                    else if (x == Y->right)
                    {
                        Y->right = nullptr;
                    }
                }
                else if (x->right == nullptr)
                {
                    TreeNode *t = x->left;
                    if (x->parent != nullptr)
                    {
                        TreeNode *t2 = x->parent;
                        if (x == t2->left)
                        {
                            t->parent = t2;
                            t2->left = t;
                        }
                        else
                        {
                            t->parent = t2;
                            t2->right = t;
                        }
                    }
                    else
                    {

                        root = t;
                    }
                }
                else if (x->left == nullptr)
                {
                    TreeNode *t = x->right;
                    if (x->parent != nullptr)
                    {
                        TreeNode *t2 = x->parent;
                        if (x == t2->left)
                        {
                            t->parent = t2;
                            t2->left = t;
                        }
                        else
                        {
                            t->parent = t2;
                            t2->right = t;
                        }
                    }
                    else
                    {

                        root = t;
                    }
                }
                else
                {

                    TreeNode *p = predecessor(x);
                    x->JourneyCode = p->JourneyCode;
                    x->price = p->price;
                    if (p->left == nullptr && p->right == nullptr)
                    {
                        TreeNode *Y = p->parent;
                        if (p == Y->left)
                        {
                            Y->left = nullptr;
                        }
                        else if (p == Y->right)
                        {
                            Y->right = nullptr;
                        }
                    }
                    else
                    {
                        TreeNode *z = p->parent;
                        TreeNode *y = p->left;
                        if (z->right == p)
                        {
                            y->parent = z;
                            z->right = y;
                        }
                        else
                        {
                            y->parent = z;
                            z->left = y;
                        }
                    }
                }
                return true;
            }

            if (x->price > price)
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }
    }

    return false;
}
void BST::MYPRE_ORDER(TreeNode *y) // pre-order
{
    if (y != nullptr)
    {
        cout << y->JourneyCode << endl;
        MYPRE_ORDER(y->left);
        MYPRE_ORDER(y->right);
    }
    else
    {
        return;
    }
}
void BST::MYPOST_ORDER(TreeNode *y) // post order
{
    if (y != nullptr)
    {

        MYPOST_ORDER(y->left);
        MYPOST_ORDER(y->right);
        cout << y->JourneyCode << endl;
    }
    else
    {
        return;
    }
}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal)
{
    if (typeOfTraversal == 0)
    {
        MYPRE_ORDER(root);
    }
    else if (typeOfTraversal == 1)
    {
        MYPOST_ORDER(root);
    }
    else if (typeOfTraversal == 2)
    {
        MYIN_ORDER(root);
    }
}

// Returns the price of the cheapest journey
int BST::getMinimum() // finding minimum
{
    TreeNode *x = root;
    TreeNode *y = new TreeNode;
    while (x != nullptr)
    {
        y = x;
        x = x->left;
    }

    return y->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countMore(int lowerPriceBound, int upperPriceBound, TreeNode *x) // counting bounds recursively
{
    int count = 0;
    if (x == nullptr)
    {
        return count;
    }
    else
    {
        if (x->price >= lowerPriceBound && x->price <= upperPriceBound)
        {
            count++;
        }
        count = count + countMore(lowerPriceBound, upperPriceBound, x->left) + countMore(lowerPriceBound, upperPriceBound, x->right);
    }
    return count;
}
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) // just calling the above function
{

    return countMore(lowerPriceBound, upperPriceBound, root);
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.

void BST::mystore(string filename, TreeNode *x) // storing using recursion ,preorder
{
    ofstream offile;
    offile.open(filename, ios::app);
    if (x == nullptr)
    {
        return;
    }
    if (x->left != nullptr)
    {
        x->a = true;
    }
    if (x->right != nullptr)
    {
        x->b = true;
    }
    offile << x->JourneyCode << " " << x->price << " " << x->a << " " << x->b << endl;
    mystore(filename, x->left);
    mystore(filename, x->right);
}
void BST::customStore(string filename) // Just calling the above function
{
    mystore(filename, root);

    return;
}

// While loading a tree from a file written by customStore, we
// can have one of two modes of loading.  We could either ask
// for the entire tree to be loaded or only the left subtree of
// the root (if it exists) to be loaded.  The loadMode flag
// takes one of two values LOAD_FULL_BST or LOAD_LEFT_SUBTREE,
// that are #defined in BST.cpp.
// If loadMode is LOAD_FULL_BST, customLoad should load the
// entire BST that was stored in filename using customStore.
// If loadMode is LOAD_LEFT_SUBTREE, customLoad should load
// only the left subtree of the root of the BST that was
// stored in filename using customStore.
// Your implementation of customLoad should be efficient --
// its time and space complexity should be linear in the size
// of the tree that is being loaded.  So, for example, if the
// left sub-tree of the root is small compared to the right
// sub-tree, customLoad's time and space complexity should
// be small even though the entire BST may be very large.

void BST::customLoad(int flag, string filename) // loading used vector to store right elements , puts element in right only if left is null, and then removes the pointer because now it's right node is used
{

    if (flag == 3)
    {
        vector<TreeNode *> v;
        TreeNode *k = new TreeNode(0, 0);
        ifstream infile;
        infile.open(filename);
        while (!(infile.eof()))
        {

            int a, b;
            bool x, z;
            infile >> a >> b >> x >> z;
            if (root == nullptr)
            {
                k->JourneyCode = a;
                k->price = b;
                k->a = x;
                k->b = z;
                root = k;
                if (z == true)
                {
                    v.push_back(k);
                }
            }
            else
            {
                TreeNode *Y = new TreeNode(0, 0);
                Y->JourneyCode = a;
                Y->price = b;
                Y->a = x;
                Y->b = z;
                if (k->a == true)
                {
                    k->left = Y;
                    Y->parent = k;
                }
                else
                {
                    if (v.empty())
                    {
                        infile.close();
                        ofstream file;
                        file.open(filename, ios::trunc);
                        file.close();

                        return;
                    }
                    TreeNode *B = v.back();
                    B->right = Y;
                    Y->parent = B;
                    v.pop_back();
                }

                if (z == true)
                {
                    v.push_back(Y);
                }
                k = Y;
            }
        }

        infile.close();
        ofstream file;
        file.open(filename, ios::trunc);
        file.close();
    }
    if (flag == 4) // using the same logic ignoring the first line as it contains original root
    {
        vector<TreeNode *> v;
        TreeNode *k = new TreeNode(0, 0);
        ifstream infile;
        infile.open(filename);
        int count = 0;
        while (!(infile.eof()))
        {

            int a, b;
            bool x, z;
            infile >> a >> b >> x >> z;
            if (count == 0)
            {
                count++;
                continue;
            }

            if (root == nullptr)
            {
                k->JourneyCode = a;
                k->price = b;
                k->a = x;
                k->b = z;
                root = k;
                if (z == true)
                {
                    v.push_back(k);
                }
            }
            else
            {
                TreeNode *Y = new TreeNode(0, 0);
                Y->JourneyCode = a;
                Y->price = b;
                Y->a = x;
                Y->b = z;
                if (k->a == true)
                {
                    k->left = Y;
                    Y->parent = k;
                }
                else
                {
                    if (v.empty())
                    {
                        infile.close();
                        ofstream file;
                        file.open(filename, ios::trunc);
                        file.close();
                        return;
                    }
                    TreeNode *B = v.back();
                    B->right = Y;
                    Y->parent = B;
                    v.pop_back();
                }

                if (z == true)
                {
                    v.push_back(Y);
                }
                k = Y;
            }
            count++;
        }

        infile.close();
        ofstream file;
        file.open(filename, ios::trunc);
        file.close();
    }

    return;
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
