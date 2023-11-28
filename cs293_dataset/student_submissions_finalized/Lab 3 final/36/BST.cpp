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

BST::BST()
{
    root = nullptr;
}
BST::BST(TreeNode *root)
{
    this->root = root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{
    if (root == nullptr)
    {
        root = new TreeNode(JourneyCode, price);
        return true;
    }
    if (find(JourneyCode, price))
    {
        return false;
    }

    TreeNode *temp = root;

    while (true)
    {
        if (price <= temp->price)
        {
            if (temp->left == nullptr)
            {
                temp->left = new TreeNode(JourneyCode, price);
                temp->left->parent = temp;
                return true;
            }
            else
            {
                temp = temp->left;
                continue;
            }
        }
        else
        {
            if (temp->right == nullptr)
            {
                temp->right = new TreeNode(JourneyCode, price);
                temp->right->parent = temp;
                return true;
            }
            else
            {
                temp = temp->right;
                continue;
            }
        }
    }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    TreeNode *temp = root;

    while (temp != nullptr)
    {
        if (temp->JourneyCode == JourneyCode && temp->price == price)
        {
            return true;
        }
        else if (price <= temp->price)
        {
            temp = temp->left;
        }
        else
        {
            temp = temp->right;
        }
    }
    return false;
}

struct TreeNode *BST::get(int Journeycode, int price)
{
    TreeNode *temp = root;

    while (temp != nullptr)
    {
        if (temp->JourneyCode == Journeycode && temp->price == price)
        {
            return temp;
        }
        else if (price <= temp->price)
        {
            temp = temp->left;
            continue;
        }
        else
        {
            temp = temp->right;
        }
    }
    return nullptr;
}

// successor
struct TreeNode *BST::successor(TreeNode *x)
{
    x = x->right;
    while (x->left != nullptr)
    {
        x = x->left;
    }
    return x;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    if (!find(JourneyCode, price))
    {
        return false;
    }
    TreeNode *temp = get(JourneyCode, price);
    if (temp == root)
    {
        if (temp->left == nullptr && temp->right == nullptr)
        {
            root = nullptr;
            return true;
        }
        else if (temp->left != nullptr && temp->right == nullptr)
        {
            root->left->parent = nullptr;
            root = root->left;
            return true;
        }
        else if (temp->left == nullptr && temp->right != nullptr)
        {
            root->right->parent = nullptr;
            root = root->right;
            return true;
        }
        else
        {
            TreeNode *suc = successor(temp);
            int tempjcode = suc->JourneyCode, temppri = suc->price;
            remove(tempjcode, temppri);
            temp->JourneyCode = tempjcode;
            temp->price = temppri;
            return true;
        }
        return true;
    }
    // both empty
    if (temp->left == nullptr && temp->right == nullptr)
    {
        if (temp->parent->left == temp)
        {
            temp->parent->left = nullptr;
            return true;
        }
        else
        {
            temp->parent->right = nullptr;
            return true;
        }
        return true;
    }
    // one empty
    else if (temp->left != nullptr && temp->right == nullptr)
    {
        if (temp->parent->left == temp)
        {
            temp->left->parent = temp->parent;
            temp->parent->left = temp->left;
            return true;
        }
        else
        {
            temp->left->parent = temp->parent;
            temp->parent->right = temp->left;
            return true;
        }
    }
    else if (temp->left == nullptr && temp->right != nullptr)
    {
        if (temp->parent->left == temp)
        {
            temp->right->parent = temp->parent;
            temp->parent->left = temp->right;
            return true;
        }
        else
        {
            temp->right->parent = temp->parent;
            temp->parent->right = temp->right;
            return true;
        }
    }
    // 0 empty
    else
    {
        TreeNode *suc = successor(temp);
        int tempjcode = suc->JourneyCode, temppri = suc->price;
        remove(tempjcode, temppri);
        temp->JourneyCode = tempjcode;
        temp->price = temppri;
        return true;
    }
}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal)
{
    TreeNode *temp = root;
    if (typeOfTraversal == PRE_ORDER)
    {
        pre_order(temp);
    }
    else if (typeOfTraversal == POST_ORDER)
    {
        post_order(temp);
    }
    else if (typeOfTraversal == IN_ORDER)
    {
        in_order(temp);
    }
}
void BST::pre_order(TreeNode *x)
{

    if (x == nullptr)
    {
        return;
    }
    else
    {
        cout << x->JourneyCode << endl;
        pre_order(x->left);
        pre_order(x->right);
    }
}
void BST::post_order(TreeNode *x)
{
    if (x == nullptr)
    {
        return;
    }
    else
    {

        post_order(x->left);
        post_order(x->right);
        cout << x->JourneyCode << endl;
    }
}
void BST::in_order(TreeNode *x)
{
    if (x == nullptr)
    {
        return;
    }
    else
    {
        in_order(x->left);
        cout << x->JourneyCode << endl;
        in_order(x->right);
    }
}

// Returns the price of the cheapest journey
int BST::getMinimum()
{
    TreeNode *temp = root;
    while (true)
    {
        if (temp->left == nullptr)
        {
            return temp->price;
        }
        else
        {
            temp = temp->left;
            continue;
        }
    }
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound)
{
    return pricebound(lowerPriceBound, upperPriceBound, root);
}
int BST::pricebound(int lower, int upper, TreeNode *x)
{
    if (x == nullptr)
    {
        return 0;
    }
    if (x->price <= upper && x->price >= lower)
    {
        return 1 + pricebound(lower, upper, x->left) + pricebound(lower, upper, x->right);
    }
    else
    {
        return pricebound(lower, upper, x->right) + pricebound(lower, upper, x->left);
    }
}
// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.

void BST::store(ofstream &out ,TreeNode *x) {
    if (x==nullptr)
    {
        return;
    }
    else {
        out << x->JourneyCode<<"\t" <<x->price <<"\n" ;
        store(out,x->left);
        store(out,x->right);
    }
}
void BST::customStore(string filename) { 
    ofstream out;
    out.open(filename);
    store(out , root);
    out.close();
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
void BST::load(ifstream &in, TreeNode *x, int flag) {
    if(flag==3) {
        int jc,pr;
        in >> jc;
        in >> pr;
        insert(jc,pr);
        load(in,x->left,flag);
        load(in,x->right,flag);
    }
    else {
        int jc,pr;
        in >> jc;
        in >> pr;
        if (root->price<pr) {
            return;
        }
        insert(jc,pr);
        load(in,x->left,flag);
        load(in,x->right,flag);
    }
}
void BST::customLoad(int flag, string filename) { 
    ifstream in;
    in.open(filename);
    load(in,root,flag);
    in.close();
}

// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
// Please use the following code to replace the last part of
// BST.cpp that was provided earlier (from below the comment
// DO NOT CHANGE ANYTHING BELOW THIS LINE)
//
//

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
