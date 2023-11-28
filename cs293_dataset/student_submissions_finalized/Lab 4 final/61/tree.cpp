#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <fstream>

using namespace std;

#include "tree.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST()
{
    root = NULL;
}
BST::BST(TreeNode *root)
{
    this->root = root;
}
int BST::get_imbalance()
{
    return root->Imbalance();
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{
    if (find(JourneyCode, price))
    {
        return false;
    }
    TreeNode *newnode = new TreeNode(JourneyCode, price);
    TreeNode *y = NULL;
    TreeNode *x = root;
    while (x != NULL)
    {
        y = x;
        if (JourneyCode < x->JourneyCode)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    newnode->parent = y;
    if (y == NULL)
    {
        root = newnode;
        return true;
    }
    else
    {
        if (JourneyCode < y->JourneyCode)
        {
            y->left = newnode;
        }
        else
        {
            y->right = newnode;
        }
        return true;
    }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    TreeNode *x = root;
    while (x != NULL && (x->price != price || x->JourneyCode != JourneyCode))
    {
        if (JourneyCode > x->JourneyCode)
        {
            x = x->right;
        }
        else
        {
            x = x->left;
        }
    }
    if (x == NULL)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    TreeNode *x = root;
    TreeNode *y;
    while (x != NULL && (x->price != price || x->JourneyCode != JourneyCode))
    {
        y = x;
        if (price > x->price)
        {
            x = x->right;
        }
        else
        {
            x = x->left;
        }
    }
    if (x == NULL)
    {
        return false;
    }
    if (x->right == NULL && x->left == NULL)
    {
        if (y->right == x)
        {
            y->right = NULL;
        }
        else
        {
            y->left = NULL;
        }
        x->parent = NULL;
    }
    else if (x->right == NULL)
    {
        if (x == root)
        {
            root = x->left;
            root->parent = NULL;
        }
        else if (y->right == x)
        {

            y->right = x->left;
            x->parent = NULL;
            x->left->parent = y;
        }
        else
        {
            y->left = x->left;
            x->parent = NULL;
            x->left->parent = y;
        }
    }
    else if (x->left == NULL)
    {
        if (x == root)
        {
            root = x->right;
            root->parent = NULL;
        }
        else if (y->right == x)
        {
            y->right = x->right;
            x->parent = NULL;
            x->right->parent = y;
        }
        else
        {
            y->left = x->right;
            x->parent = NULL;
            x->right->parent = y;
        }
    }
    else
    {
        TreeNode *succ = x->right;
        TreeNode *succ_p = x;
        while (succ->left != NULL)
        {
            succ_p = succ;
            succ = succ->left;
        }
        if (succ_p == x)
        {
            if (y->right == x)
            {
                y->right = succ;
                succ_p->parent = y;
                succ->left = x->left;
                x->left->parent = succ;
            }
            else
            {
                y->left = succ;
                succ_p->parent = y;
                succ->left = x->left;
                x->left->parent = succ;
            }
            return true;
        }
        succ->left = x->left;
        succ->right = x->right;
        succ->parent = y;
        if (succ_p->right == succ)
        {
            succ_p->right = NULL;
        }
        else
        {
            succ_p->left = NULL;
        }
        succ_p->parent = NULL;
        succ->left = x->left;
        x->left->parent = succ;
        x->left = NULL;
        succ->right = x->right;
        x->right->parent = succ;
        x->right = NULL;
        succ->parent = y;
        x->parent = NULL;

        if (y->right == x)
        {

            y->right = succ;
        }
        else
        {
            y->left = succ;
        }
    }
    return true;
}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal)
{
    TreeNode *x = root;
    if (typeOfTraversal == 0)
    {
        traverse_pre(x);
    }
    else if (typeOfTraversal == 1)
    {
        traverse_post(x);
    }
    else if (typeOfTraversal == 2)
    {
        traverse_io(x);
    }
    return;
}

// Returns the price of the cheapest journey
int BST::getMinimum()
{
    TreeNode *x = root;
    if (x == NULL)
    {
        return 0;
    }
    while (x->left != NULL)
    {
        x = x->left;
    }
    return x->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound)
{
    int num = 0;
    inorder(root, num, lowerPriceBound, upperPriceBound);
    return num;
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) { 
        ofstream outfile;
        outfile.open(filename);
        TreeNode* x=root;
        loading(x,outfile);
        outfile.close();
        

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

void BST::customLoad(int flag, string filename)
{   
    ifstream infile;
    infile.open(filename);
    vector<string> arr;
    string word;
    while(infile>>word){
        arr.push_back(word);
    }
    
    struct TreeNode* ans; 
    int num_heads=0;
    stack <struct TreeNode *> stk;
    int index = 0;
    bool found = false;
    while (index<arr.size())
    {
        if (arr[index] == "#")
        {
            index++;
            found = true;
        }
        struct TreeNode *head = new struct TreeNode(stoi(arr[index+1]),stoi(arr[index]));
        num_heads++;
        if(num_heads==1){
            root=head;
        }
        if (!stk.empty())
        {
            stk.top()->right = head;
            stk.pop();
        }
        if (found)
        {
            found = false;
            stk.push(head);
        }
        struct TreeNode *current = head;
        index=index+2;
        if (index >= arr.size())
            {
                break;
            }
        if (arr[index] == "#")
        {
            index++;
            found = true;
        }
        while (stoi(arr[index]) < head->price)
        {   
           
            if (found)
            {
                found = false;
                stk.push(new struct TreeNode(0,stoi(arr[index])));
            }
            if (arr[index] == "#")
            {
                index++;
                found = true;
                continue;
            }
            current->left = new struct TreeNode(stoi(arr[index+1]),stoi(arr[index]));
            index=index+2;
            if (index >= arr.size())
            {
                break;
            }
            if (arr[index] == "#")
            {
                index++;
                found = true;
                continue;
            }
        }
    }
    if(flag==4){
        root=root->left;
    }

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
