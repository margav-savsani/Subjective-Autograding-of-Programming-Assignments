#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST() {
    root = nullptr; 
    }
BST::BST(TreeNode *root) { 
    this->root=root; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{
    TreeNode *x;
    TreeNode *y;
    x = root;
    y = NULL;
    while (x != NULL)
    {
        y = x;
        if (price < x->price)
            x = x->left;
        else
            x = x->right;
    }
    if (y == NULL)
        root = TreeNode(JourneyCode, price);
    else if (price < y->price)
        y->left = TreeNode(JourneyCode, price) else y->right = TreeNode(JourneyCode, price) return false;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    if (root == NULL)
        return false;
    if (root->price == price &&root->JourneyCode = JourneyCode)
        return true;
    if (root->price < price)
    {
        root = root->right;
        find(JourneyCode, price)
    }
    else
    {
        root = root->left;
        find(JourneyCode, price)
    }
    return false;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price){
    if (!find(JourneyCode, price))
        return false;
    else
    {
        TreeNode *c = root;                 //c denotes child
        TreeNode *p = NULL;              //p denotes parent
        while (true){
            if (c->price == price && c->JourneyCode == JourneyCode)
            {
                break;
            }
            p = new struct TreeNode();
            p = c;
            if (c->price > price) c = c->left;
            else c = c->right;
            
        }
        if (c->left == NULL && c->right == NULL){
            if (p == NULL){
                delete root;
                root = NULL;
            }
            else if (p->left == c){
                p->left == NULL;
            }
            else if (p->right == c){
                p->right == NULL;
            }
            c = NULL;
        }
        else if ((c->left == NULL) && (c->right != NULL))
        {
            if (p == NULL){
                root = c->right;
                root->parent = NULL;
            }
            else if (p->left == c){
                p->left = c->right;
                (c->right)->parent = p;
            }
            else if (p->right == c){
                p->right = c->right;
                (x->right)->parent = y;
            }
        }

        else if ((c->right == NULL) && (c->left != NULL))
        {
            if (p == NULL){
                root = c->left;
                root->parent = NULL;
            }
            else if (p->left == c){
                p->left = c->left;
                (c->left)->parent = p;
            }
            else if (p->right == c){
                p->right = c->left;
                (c->left)->parent = p;
            }
        }
        else{
            TreeNode *node = x;
            if (node->right->left == NULL){
                if (node->right->right == NULL){
                    node->price = node->right->price;
                    node->JourneyCode = node->right->JourneyCode;
                    node->right = NULL;
                }
                else{
                    node->price = node->right->price;
                    node->JourneyCode = node->right->JourneyCode;
                    node->right = node->right->right;
                    node->right->parent = node;
                }
            }
            else{
                TreeNode *x = c;
                TreeNode *r = c->right;
                while (r->left != NULL)
                {
                    x = r;
                    r = r->left;
                }
                int journeycode = r->JourneyCode;
                int PRICe = r->price;
                BST Tree(x);
                Tree.remove(JC, pc);
                node->JourneyCode = journeycode;
                node->price = PRICe;
        }
        return true;
    }
    }
}


bool BST::remove(int JourneyCode, int price)
{
    if (!find(JourneyCode, price))
        return false;
    else
    {
        root = removeNode(root, price);
        return true;
    }
}

// this returns the pointer to the node which is the inorder successor
TreeNode *BST::InorderSuccessor(TreeNode *root)
{
    TreeNode *x = root;
    while (x != NULL && x->left != NULL)
    {
        x = x->left;
    }
    return x;
}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal)
{
    if (root == NULL)
        return;
    TreeNode *x;
    if (typeOfTraversal == PRE_ORDER)
    {
        x = root;
        cout << root->JourneyCode << endl;
        root = x->left;
        traverse(PRE_ORDER);
        root = x->right;
        traverse(PRE_ORDER);
        return;
    }
    if (typeOfTraversal == POST_ORDER)
    {
        x = root;
        root = x->left;
        traverse(POST_ORDER);
        root = x->right;
        traverse(POST_ORDER);
        root = x;
        cout << root->JourneyCode << endl;
        return;
    }
    if (typeOfTraversal == IN_ORDER)
    {
        x = root;
        root = x->left;
        traverse(IN_ORDER);
        cout << root->JourneyCode << endl;
        root = x->right;
        traverse(IN_ORDER);
        return;
    }
    return;
}

// Returns the price of the cheapest journey
int BST::getMinimum()
{
    if (root == NULL)
        return 0;
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root->price;
}
//does the same thing but returns a struct pointer instead
TreeNode *BST::minNode(TreeNode *node)
{
    TreeNode *var = node;
    while (var && var->left != NULL)
    {
        var = var->left;
    }
    return var;
}
// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.

int BST::inordertrav(int lbound, int hbound, int total){
    if(root == NULL) return total;
    TreeNode *var = root;
    root=root->left;
    int total1 = inordertrav(lbound,hbound,total);
    if(var->price>=lbound && var->price<=hbound){
        total++;
    }
    root=var->right;
    int total=inordertrav(lbound,hbound,total1);
    root=var;
    return total2;
}


int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    return inordertrav(lowerPriceBound,upperPriceBound,0);
    }



// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) {

    
    
     return; }

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

void BST::customLoad(int flag, string filename) { return; }

// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
void BST::printBST(const string &prefix, bool isLeft = false)
{
    if (root != NULL)
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__");

        // print the value of the node
        cout << root->JourneyCode << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST(prefix + (isLeft ? "│   " : "    "), true);
        root = root->right;
        printBST(prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::getBST(const string &prefix, bool isLeft = false)
{
    if (root != NULL)
    {
        result.push_back(prefix);

        result.push_back(isLeft ? "├──" : "└──");

        // print the value of the node
        result.push_back(root->JourneyCode + "\n");
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        getBST(prefix + (isLeft ? "│   " : "    "), true);
        root = root->right;
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
