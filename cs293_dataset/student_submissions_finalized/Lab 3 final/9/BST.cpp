#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
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

BST::BST() { root = NULL; }
BST::BST(TreeNode *root) { this->root = root; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{
    TreeNode *start = root;
    TreeNode *previous = NULL;

    if (!start)
    {
        root = new TreeNode(JourneyCode, price);
        return 1;
    }
    if (start->JourneyCode == JourneyCode)
    {
        return 0;
    }

    while (start)
    {
        previous = start;
        if (start->price > price)
        {
            start = start->left;
        }
        else
        {
            start = start->right;
        }
    }

    if (price < previous->price)
    {
        TreeNode *newnode = new TreeNode(JourneyCode, price);
        previous->left = newnode;
        previous->left->parent = previous;
    }
    else
    {
        TreeNode *newnode = new TreeNode(JourneyCode, price);
        previous->right = newnode;
        previous->right->parent = previous;
    }
    return 1;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    TreeNode *node = root;
    if (!node)
    {
        return 0;
    }
    if ((price == node->price) and (JourneyCode == node->JourneyCode))
    {
        return 1;
    }
    if (price < node->price)
    {
        return (BST(node->left).find(JourneyCode, price));
    }
    else
    {
        return (BST(node->right).find(JourneyCode, price));
    }
    return 1;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    if (find(JourneyCode, price) == 0)
    {
        return 0;
    }
    TreeNode *node = root;

    if (price < node->price)
    {
        BST(node->left).remove(JourneyCode, price);
    }
    else if (price > root->price)
        BST(node->right).remove(JourneyCode, price);

    else
    {
        // node has no child
        if (!node->left and !node->right)
        {
            if (!node->parent)
            {
                node = NULL;
                return 1;
            }
            if (node->parent->price > node->price)
            {
                node->parent->left = NULL;
            }
            else
            {
                node->parent->right = NULL;
            }
            node = NULL;
        }

        // node with only one child
        else if (!node->left)
        {
            struct TreeNode *temp = node->right;
            if (!node->parent)
            {
                node = temp;
                return 1;
            }
            else if (node->parent->price > node->price)
            {
                node->parent->left = temp;
            }
            else
            {
                node->parent->right = temp;
            }
            free(root);
            node = temp;
        }
        else if (!node->right)
        {
            struct TreeNode *temp = root->left;
            if (!node->parent)
            {
                node = temp;
                return 1;
            }
            else if (node->parent->price > node->price)
            {
                node->parent->left = temp;
            }
            else
            {
                node->parent->right = temp;
            }
            free(root);
            node = temp;
        }

        // node with two children
        else
        {
            struct TreeNode *temp = root->right;
            while (temp->left)
            {
                temp = temp->left;
            }
            if (node->parent->price > node->price)
            {
                node->parent->left = temp;
            }
            else
            {
                node->parent->right = temp;
            }
            temp->right = root->right;
            temp->left = root->left;
            if (temp->parent->price > temp->price)
            {
                temp->parent->left = NULL;
            }
            else
            {
                temp->parent->right = NULL;
            }
            temp->parent = root->parent;
            free(root);
            node = temp;
        }
    }
    return 1;
}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void inorder(struct TreeNode *root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    cout << root->JourneyCode << endl;
    inorder(root->right);
}

void preorder(struct TreeNode *root)
{
    if (root == NULL)
        return;
    cout << root->JourneyCode << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(struct TreeNode *root)
{
    if (root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    cout << root->JourneyCode << " ";
}

void BST::traverse(int typeOfTraversal)
{
    if (typeOfTraversal == 0)
    {
        // PRE_ORDER
        preorder(root);
    }
    if (typeOfTraversal == 1)
    {
        // POST_ORDER
        postorder(root);
    }
    if (typeOfTraversal == 2)
    {
        // IN_ORDER
        inorder(root);
    }
    return;
}

// Returns the price of the cheapest journey
int BST::getMinimum()
{
    TreeNode *node = root;
    while (node->left != NULL and node)
    {
        node = node->left;
    }
    return node->price;
}

// Part II

int inprice(struct TreeNode *root, int lower, int upper)
{
    int count = 0;
    if (root == NULL)
        return 0;
    if (root->price >= lower and root->price <= upper)
        count++;
    count += inprice(root->left, lower, upper);
    count += inprice(root->right, lower, upper);
    return count;
}
// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound)
{
    return inprice(root, lowerPriceBound, upperPriceBound);
}

void preorderfile(struct TreeNode *root, string filename)
{
    ofstream outfile;
    outfile.open(filename);

    if (root == NULL)
    {
        outfile.close();
        return;
    }
    outfile << root->price << " " << root->JourneyCode << endl;
    preorder(root->left);
    preorder(root->right);

    outfile.close();
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename)
{
    preorderfile(root, filename);
    return;
}

// --------------Reference - Geeks for Geeks ----------------------------------------------------------------------------------------------------------
// A utility function to create a node
TreeNode *newNode(int JourneyCode, int price)
{
    TreeNode *temp = new TreeNode(JourneyCode, price);
    temp->left = temp->right = NULL;
    return temp;
}

// A recursive function to construct
// BST from pre[]. preIndex is used
// to keep track of index in pre[].
TreeNode *constructTreeUtil(int pre[], int *preIndex, vector<int> jcodearr, int price,
                            int min, int max, int size)
{
    // Base case
    if (*preIndex >= size)
        return NULL;

    TreeNode *root = NULL;

    // If current element of pre[] is in range, then
    // only it is part of current subtree
    if (price > min && price < max)
    {
        // Allocate memory for root of this
        // subtree and increment *preIndex
        root = newNode(jcodearr[0], price);
        *preIndex = *preIndex + 1;

        if (*preIndex < size)
        {
            // Construct the subtree under root
            // All nodes which are in range
            // {min .. price} will go in left
            // subtree, and first such node
            // will be root of left subtree.
            root->left = constructTreeUtil(pre, preIndex, jcodearr,
                                           pre[*preIndex],
                                           min, price, size);
        }
        if (*preIndex < size)
        {
            // All nodes which are in range
            // {price..max} will go in right
            // subtree, and first such node
            // will be root of right subtree.
            root->right = constructTreeUtil(pre, preIndex, jcodearr,
                                            pre[*preIndex],
                                            price, max, size);
        }
    }

    return root;
}

// The main function to construct BST
// from given preorder traversal.
// This function mainly uses constructTreeUtil()
TreeNode *constructTree(int pre[], vector<int> jcodearr, int size)
{
    int preIndex = 0;
    return constructTreeUtil(pre, &preIndex, jcodearr, pre[0],
                             INT_MIN, INT_MAX, size);
}

// -----------------------------------------------------------------------------------------------------

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
    vector<int> pricearr;
    vector<int> jcodearr;
    while (1)
    {
        int price0, jcode0;
        infile >> price0;
        infile >> jcode0;
        if (infile.eof())
        {
            break;
        }
        pricearr.push_back(price0);
        jcodearr.push_back(price0);
    }
    infile.close();

    int n = pricearr.size();
    int pre[n];
    for (int i = 0; i < n; i++)
    {
        pre[i] = pricearr[i];
    }
    if (flag = LOAD_FULL_BST)
        root = constructTree(pre, jcodearr, n);

    if (flag = LOAD_LEFT_SUBTREE)
        root = constructTree(pre, jcodearr, n);

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
        result.push_back(root->JourneyCode + "\n");
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
