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

BST::BST() { ; }
BST::BST(TreeNode *root)
{
    root = NULL;
    root->left = NULL;
    root->right = NULL;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
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
            else if (t->price <= price)
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
                if (t->price > price)
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

// Return True, if the ticket with given attributes is found, false otherwise
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
        else if (temp->price > price)
        {
            temp = temp->left;
        }
        else
            temp = temp->right;
    }
    return false;
}
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise

bool BST::remove(int JourneyCode, int price) // Remove has 3 cases.
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
        else if (z->price > price)
        {
            if (z->left != NULL)
                z = z->left;
        }
        else if (z->price < price)
        {
            if (z->right != NULL)
                z = z->right;
        }
    }

    if (z->left == NULL && z->right == NULL)  // when leaf is deleted
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
    else if (z->left == NULL)      // when delete element has only right child.
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
    else if (z->right == NULL)      // when delete element has only left child.
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
        x = predecessor(z); // predecessor     
        if (x->parent->left == x)          // when deleted element has 2 children
        {
            x->parent->left = x->left;
        }
        if (x->parent->right == x)            // I exchanged predecessor values with delete element values.
        {                                     // So works get easy :)
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

struct TreeNode *BST::predecessor(TreeNode *curr)
{                                                      // find predecessor
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

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal)
{
    if (typeOfTraversal == PRE_ORDER)
    {
        preOrder(root);
    }
    if (typeOfTraversal == POST_ORDER)
    {
        postOrder(root);
    }
    if (typeOfTraversal == IN_ORDER)
    {
        inOrder(root);
    }

    return;
}

void BST::preOrder(struct TreeNode *root)     // Recursive function for preorder
{
    TreeNode *temp = new TreeNode();
    temp = root;
    if (temp != NULL)
    {
        cout << temp->JourneyCode << " " << temp->price << endl;
        preOrder(temp->left);
        preOrder(temp->right);
    }
}

void BST::inOrder(struct TreeNode *root)       // Recursive function for inorder
{
    TreeNode *temp = new TreeNode();
    temp = root;
    if (temp != NULL)
    {
        preOrder(temp->left);
        cout << temp->JourneyCode << " " << temp->price << endl;
        preOrder(temp->right);
    }
}

void BST::postOrder(struct TreeNode *root)     // // Recursive function for postorder
{
    TreeNode *temp = new TreeNode();
    temp = root;
    if (temp != NULL)
    {
        postOrder(temp->left);
        postOrder(temp->right);
        cout << temp->JourneyCode << " " << temp->price << endl;
    }
}

// Returns the price of the cheapest journey
int BST::getMinimum()
{
    TreeNode *temp = new TreeNode();
    temp = root;
    if (temp == NULL)
    {
        return -1;
    }
    while (temp->left != NULL)
    {
        temp = temp->left;
    }
    return (temp->price);
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound)
{

    int ans = BOUNDS(root, lowerPriceBound, upperPriceBound);

    return ans;
}

int BST::BOUNDS(struct TreeNode *root, int lowerPriceBound, int upperPriceBound) // Used this function for recursion
{
    TreeNode *temp = new TreeNode();
    temp = root;
    if (temp == NULL)
    {
        return 0;
    }
    if (temp->price >= lowerPriceBound && temp->price <= upperPriceBound)
    {
        return (BOUNDS(temp->left, lowerPriceBound, upperPriceBound) + 1 + BOUNDS(temp->right, lowerPriceBound, upperPriceBound));
    }
    else
    {
        return (BOUNDS(temp->left, lowerPriceBound, upperPriceBound) + BOUNDS(temp->right, lowerPriceBound, upperPriceBound));
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

    customTreeStorePreOrder(filename, root);

}

void BST::customTreeStorePreOrder(string filename, struct TreeNode *root)  // Store recursively inorder
{
    TreeNode *temp = new TreeNode();
    temp = root;
    if (temp != NULL)
    {
        ofstream file;
        file.open(filename, std::ios_base::app);
        file << temp->JourneyCode << " " << temp->price << endl;
        file.close();
        customTreeStorePreOrder(filename, temp->left);
        customTreeStorePreOrder(filename, temp->right);
    }
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
                                                   // Uses O(n) time :)
    vector<TreeNode *> PREORDER;
    TreeNode *x = NULL;
    fstream file;
    int journey, price;
    file.open(filename);
    while (file >> journey >> price)
    {
        x = new TreeNode(journey, price);
        PREORDER.push_back(x);
    }

    file.close();
    
    if (flag==LOAD_FULL_BST)        // Print whole BST
    {
        int start = 0;
        int end = 10000000;
        int pIndex = 0;
        root = constructBST(PREORDER, pIndex, start, end);
    }
    if (flag==LOAD_LEFT_SUBTREE)     // Print left subtree optimally
    {
        int start = 0;
        int end = PREORDER[0]->price +1;
        int pIndex = 1;
        root = constructBST(PREORDER, pIndex, start, end);
    }
}
struct TreeNode *BST::constructBST(vector<TreeNode *> const &PREORDER, int &pIndex, int start, int end) // New function which uses RECURSION.
{
    if (pIndex == PREORDER.size())
    {
        return NULL;
    }
    int val = PREORDER[pIndex]->price;
    if ((start > val) || (val > end))
    {
        return NULL;
    }
    TreeNode *node = new TreeNode(PREORDER[pIndex]->JourneyCode, PREORDER[pIndex]->price);   // O(n) is done :).
    pIndex++;
    node->left = constructBST(PREORDER, pIndex, start, val - 1);       // Left part of each node
    node->right = constructBST(PREORDER, pIndex, val + 1, end);        // Right part of each node
    return node;
}

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
