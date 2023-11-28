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
{ // Initialising the tree
    this->root = new TreeNode;
    this->root = NULL;
}

BST::BST(TreeNode *root)
{ // Initialising the tree
    this->root = new TreeNode;
    this->root = root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{
    TreeNode *y = NULL;                             // Parent before whom the new node has to be inserted.
    TreeNode *x = this->root;                       // initialising the x by root.
    TreeNode *z = new TreeNode(JourneyCode, price); // New node to be inserted in the tree.
    if (x == NULL)
    { // If the root pointer is null then add the given node to root node itself.
        this->root = new TreeNode;
        this->root->JourneyCode = JourneyCode;
        this->root->price = price;
        return true;
    }
    while (x != NULL)
    { // Find till there is a place to fill.
        y = x;
        if ((x->price) > price)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    z->parent = y; // Alloting the parent of z as y.

    // ALLOTING THE CHILD OF Y TO Z.
    if (z->price < y->price)
    {
        y->left = z;
        return true;
    }
    else
    {
        y->right = z;
        return true;
    }
    return false; // case when the price is equal and insertion cannot be done
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    TreeNode *x = root; // STARTING FROM ROOT NODE
    while (x != NULL && ((x->price != price) || (x->JourneyCode != JourneyCode)))
    {
        // SEARCH TILL THE EXACT STATION IS FOUND
        // OR WE REACH A NULL.
        if (price < (x->price))
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    if (x == NULL)
    { // IF NO SUCH NODE
        return false;
    }
    else
    { // TRUE IF NODE IS FOUND.
        return true;
    }
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    TreeNode *x = this->root; // STARTING FROM ROOT NODE
    while (x != NULL && ((x->price != price) || (x->JourneyCode != JourneyCode)))
    {
        // SEARCH TILL THE EXACT STATION IS FOUND
        // OR WE REACH A NULL.
        if (price < (x->price))
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    } // Finally x would be the element returned from our search
    if (x == NULL)
    { // IF NO SUCH NODE
        return false;
    }
    else
    { // TRUE IF NODE IS FOUND.
        TreeNode *y = new TreeNode;
        TreeNode *z = new TreeNode;
        if (x->left == NULL || x->right == NULL)
        {
            // If there is no left or right child of x
            // That means atmost one child for x.
            y = x; // y is the node to be deleted.
        }
        else
        {
            y = successor(x); // IF not then x has two child and we assign y as the successor of x.
        }
        if (y->left != NULL)
        { // If no left child of y then assign z as the left child of y.
            z = y->left;
        }
        else
        {
            z = y->right; // otherwise z is the right child
        }
        if (z != NULL)
        {
            z->parent = y->parent;
        }
        if (y->parent == NULL)
        {
            this->root = z; // if y is the root
        }
        else if (y == y->parent->left)
        {
            y->parent->left = z;
        }
        else
        {
            y->parent->right = z;
        }
        if (y != x)
        {
            x->JourneyCode = y->JourneyCode;
            x->price = y->price; // Copying all the content
        }
        return true;
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
    TreeNode *x = new TreeNode;
    x = root;
    if (x == NULL)
    {
        return;
    }
    if (typeOfTraversal == PRE_ORDER)
    {
        cout << x->price << endl;
        BST lefttree(x->left);   // left subtree
        BST righttree(x->right); // right subtree
        lefttree.traverse(PRE_ORDER);
        righttree.traverse(PRE_ORDER);
    }
    else if (typeOfTraversal == POST_ORDER)
    {
        BST lefttree(x->left);   // left subtree
        BST righttree(x->right); // right subtree
        lefttree.traverse(POST_ORDER);
        righttree.traverse(POST_ORDER);
        cout << x->price << endl;
    }

    else if (typeOfTraversal == IN_ORDER)
    {

        BST lefttree(x->left);   // left subtree
        BST righttree(x->right); // right subtree
        lefttree.traverse(IN_ORDER);
        cout << x->price << endl;
        righttree.traverse(IN_ORDER);
    }
    return;
}

// Returns the price of the cheapest journey
int BST::getMinimum()
{
    TreeNode *x = this->root;
    while (x->left != NULL)
    {
        x = x->left;
    }
    int minprice = x->price;
    return minprice;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound)
{
    // Traverse the tree in Inorder Traversal and then store the elements that are within the bounds
    int totalcount = 0;
    TreeNode *x = new TreeNode;
    x = root;
    if (x == NULL)
    {
        return 0;
    }
    if (x->price > upperPriceBound)
    { // If price greater then check only in left subtree.
        root = x->left;
        totalcount += countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
        root = x;
        return totalcount;
    }
    if (x->price < lowerPriceBound)
    { // If price less then check only in right
        root = x->right;
        totalcount += countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
        root = x;
        return totalcount;
    }
    else
    { // If within the bounds then we check both the subtrees.
        totalcount += 1;
        root = x->left;
        totalcount += countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
        root = x->right;
        totalcount += countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
        root = x;
        return totalcount;
    }
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) // Function to store the nodes in a text file
{
    ofstream outfile;
    outfile.open(filename, ios_base::out | ios_base::app);
    if (root == NULL) //
    {
        outfile << -10 << " " << -20 << endl; // tore -10 and -20 as the values if there is a NULL pointer.
        return;
    }
    TreeNode *x = root;
    int pricecurr = root->price;
    int Journey = root->JourneyCode;
    outfile << Journey << " " << pricecurr << " " << endl; // Output to the file.
    root = x->left;                                        // Exploiting the root to traverse the tree.
    customStore(filename);
    root = x->right;
    customStore(filename);
    root = x; // Assigning the root back to original.
    outfile.close();
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

TreeNode *Recursivefileread(TreeNode *givenroot, ifstream &readingfile) // Function to read the file recursively
                                                                        // i.e in continuation.
{ // Returns the pointer of the root of the Node at which the add was done
    int journey, jprice;
    if (readingfile >> journey >> jprice)
    {
        TreeNode *orig = givenroot; // The original root of the tree.
        // Setting the values.
        givenroot->JourneyCode = journey;
        givenroot->price = jprice;
        if (givenroot->JourneyCode == -10) // If it is a NULL then return the NODE as NULL
        {
            givenroot = NULL;
        }
        else
        {
            TreeNode *b = new TreeNode; // Left Subtree.
            b->parent = givenroot;
            givenroot->left = Recursivefileread(b, readingfile);
            TreeNode *c = new TreeNode; // Right subtree.
            c->parent = givenroot;
            givenroot->right = Recursivefileread(c, readingfile);
        }
        return givenroot;
    }
    readingfile.close();
    return NULL; // If reached the end of file.
}

void BST::customLoad(int flag, string filename)
{
    ifstream readingfile;
    readingfile.open(filename); // READING INPUT
    int journey, jprice;
    if (flag == LOAD_FULL_BST)
    {
        root = new TreeNode;
        root->parent = NULL; //Assigning a new Node to root and reading the Nodes
        Recursivefileread(root, readingfile);
    }
    if (flag == LOAD_LEFT_SUBTREE)
    {
        readingfile >> journey >> jprice;
        root = new TreeNode;
        root->parent = NULL; //Assigning the root a new Memory
        Recursivefileread(root, readingfile);
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
