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

BST::BST() { root = NULL; }
BST::BST(TreeNode *root) { this->root = root; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{
    TreeNode *a = root;
    TreeNode *parent = NULL;
    TreeNode *q = new TreeNode(JourneyCode, price);
    while (a != NULL)
    {
        if ((a->price) < price)
        {
            parent = a;
            a = (a->right);
        }
        else if ((a->price) > price)
        {
            parent = a;
            a = (a->left);
        }
        else if ((a->price) == price && ((a->JourneyCode) != JourneyCode))
        {
            if (a->right == NULL)
            {

                a->right = q;
                q->parent = a;
                return true;
            }
            parent = a;
            a = a->right;
            q->parent = parent;
            parent->right = q;
            a->parent = q;
            q->right = a;

            return true;
        }
        else
            return false;
    }

    q->parent = parent;
    if (parent == NULL)
    {
        this->root = q;
    }
    else if ((parent->price) < price)
    {
        parent->right = q;
    }
    else
    {
        parent->left = q;
    }
    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    TreeNode *find_node = root;
    while (find_node != NULL)
    {
        if ((find_node->price) <= price && (find_node->JourneyCode) != JourneyCode)
        {
            find_node = find_node->right;
        }
        else if ((find_node->price) == price && (find_node->JourneyCode) == JourneyCode)
        {
            return true;
        }
        else if ((find_node->price) > price)
        {
            find_node = find_node->left;
        }
    }
    return false;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    TreeNode *find_node = root;
    TreeNode *find_succesor = root;
    while (find_node != NULL)
    {
        if ((find_node->price) <= price && (find_node->JourneyCode != JourneyCode))
        {
            find_node = find_node->right;
            find_succesor = find_succesor->right;
        }
        else if ((find_node->price) > price)
        {
            find_node = find_node->left;
            find_succesor = find_succesor->left;
        }
        else if ((find_node->price) == price && (find_node->JourneyCode) == JourneyCode)
        {
            if (find_node->left == NULL && find_node->right == NULL)
            {
                if (find_node->parent == NULL)
                {
                    this->root = NULL;
                    return true;
                }
                find_node = find_node->parent;
                if (find_node->left != NULL)
                {
                    if (find_node->left->JourneyCode == JourneyCode)
                    {
                        find_node->left = NULL;
                    }
                }
                else
                    find_node->right = NULL;
                return true;
            }
            else if (find_node->left == NULL)
            {
                if (find_node->parent == NULL)
                {
                    find_node->right->parent = NULL;
                    this->root = find_node->right;
                    return true;
                }
                else if (find_node->parent->left != NULL)
                {
                    if (find_node->parent->left->price == price && find_node->parent->left->JourneyCode == JourneyCode)
                    {
                        find_node->right->parent = find_node->parent;
                        find_node->parent->left = find_node->right;
                        return true;
                    }
                }
                else
                {
                    find_node->right->parent = find_node->parent;
                    find_node->parent->right = find_node->right;
                    return true;
                }
            }
            else if (find_node->right == NULL)
            {
                if (find_node->parent == NULL)
                {
                    find_node->left->parent = NULL;
                    this->root = find_node->left;
                    return true;
                }
                else if (find_node->parent->left != NULL)
                {
                    if (find_node->parent->left->price == price && find_node->parent->left->JourneyCode == JourneyCode)
                    {
                        find_node->left->parent = find_node->parent;
                        find_node->parent->left = find_node->left;

                        return true;
                    }
                }
                else
                {
                    find_node->left->parent = find_node->parent;
                    find_node->parent->right = find_node->left;
                    return true;
                }
            }
            else
            {

                find_succesor = find_succesor->right;
                if (find_succesor->left == NULL)
                {
                    if (find_node->parent->left->JourneyCode == JourneyCode)
                    {
                        find_node->parent->left = find_succesor;
                        find_node->right->parent = find_node->parent;
                        find_node->left->parent = find_succesor;
                        find_succesor->left = find_node->left;
                        return true;
                    }
                }
                while ((find_succesor->left) != NULL)
                {
                    find_succesor = find_succesor->left;
                }
                if (find_succesor->right == NULL)
                {
                    find_succesor->parent->left = NULL;
                    find_node->price = find_succesor->price;
                    find_node->JourneyCode = find_succesor->JourneyCode;
                    return true;
                }
                find_succesor->right->parent = find_succesor->parent;
                find_succesor->parent->left = find_succesor->right;
                find_node->price = find_succesor->price;
                find_node->JourneyCode = find_succesor->JourneyCode;
                return true;
            }
        }
    }

    return false;
}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal)
{
    TreeNode *a = root;
    if (typeOfTraversal == PRE_ORDER)
    {
        if (a == NULL)
        {
            return;
        }
        cout << a->JourneyCode << endl;
        TreeNode *b = root->left;
        BST r(b);
        r.traverse(typeOfTraversal);
        TreeNode *c = root->right;
        BST l(c);
        l.traverse(typeOfTraversal);
    }
    else if (typeOfTraversal == POST_ORDER)
    {
        if (a == NULL)
        {
            return;
        }

        TreeNode *b = root->left;
        BST r(b);
        r.traverse(typeOfTraversal);
        TreeNode *c = root->right;
        BST l(c);
        l.traverse(typeOfTraversal);
        cout << a->JourneyCode << endl;
    }
    else if (typeOfTraversal == IN_ORDER)
    {
        if (a == NULL)
        {
            return;
        }

        TreeNode *b = root->left;
        BST r(b);
        r.traverse(typeOfTraversal);
        cout << a->JourneyCode << endl;
        TreeNode *c = root->right;
        BST l(c);
        l.traverse(typeOfTraversal);
    }
}

// Returns the price of the cheapest journey
int BST::getMinimum()
{
    TreeNode *a = root;
    while (a->left != NULL)
    {
        a = a->left;
    }
    return a->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound)
{
    TreeNode *a = root;
    if (a == NULL)
    {
        return 0;
    }
    else if ((a->price) >= lowerPriceBound && (a->price) <= upperPriceBound)
    {
        BST b(root->left);
        BST c(root->right);
        return 1 + b.countJourneysInPriceBound(lowerPriceBound, upperPriceBound) + c.countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
    }
    else if ((a->price) < lowerPriceBound)
    {
        BST b(root->right);
        return b.countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
    }
    else
    {
        BST b(root->left);
        return b.countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
    }
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename)
{

    TreeNode *a = root;
    if (a == NULL)
    {
        return;
    }
    BST b(a->left);
    BST c(a->right);
    ofstream outfile;
    outfile.open(filename, ios_base::app);
    outfile << a->JourneyCode << "  " << a->price << endl;
    outfile.close();
    b.customStore(filename);
    c.customStore(filename);
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
int find_size(string a)
{
    ifstream out;
    int N;
    int count = 0;
    out.open(a);
    while (out >> N)
    {
        count++;
    }
    out.close();
    return count / 2;
}
int find(TreeNode arr[], int start, int end, int p)
{
    if (arr[start].price < p && arr[start + 1].price > p)
    {
        return start;
    }
    else if (arr[(start + end) / 2].price > p)
    {
        return find(arr, start, ((start + end) / 2) - 1, p);
    }
    else
    {
        return find(arr, (start + end) / 2, end, p);
    }
}
TreeNode *build_tree(int start, int end, TreeNode arr[])
{
    if (start > end)
    {
        return NULL;
    }
    int j = arr[start].price;
    int i = find(arr, start, end, j);
    TreeNode *root = new TreeNode(arr[i].JourneyCode, arr[i].price);
    if (start == end)
    {

        return root;
    }
    root->left = build_tree(start + 1, i, arr);
    root->left->parent = root;
    root->right = build_tree(i + 1, end, arr);
    root->right->parent = root;
    return root;
}
void BST::customLoad(int flag, string filename)
{

    ifstream outfile;
    int N;
    int r = find_size(filename);
    
    int count = 0;
    outfile.open(filename);
    TreeNode *a = new TreeNode[r];
    while (outfile >> N)
    {
        a[count].JourneyCode = N;
        outfile >> N;
        a[count].price = N;
        count++;
    }
    this->root = build_tree(0, r - 1, a);
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