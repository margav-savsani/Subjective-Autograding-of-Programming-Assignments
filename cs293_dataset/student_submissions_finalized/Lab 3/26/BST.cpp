#include <set>
#include <iostream>
#include <string>
#include <vector>
#include "string.h"

using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST() { root = nullptr; }
BST::BST(TreeNode *root1) { root = root1; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{
    TreeNode *v = root;
    TreeNode *p = nullptr;
    int flag=0;
    while (v != nullptr)
    {
        flag=1;
        if ((v->JourneyCode) != JourneyCode)
        {
            if (v->price > price)
            {
                p = v;
                v = (v->left);
            }
            else
            {
                p = v;
                v = (v->right);
            }
        }
        else
        {
            return false;
        }
    }
    v=new TreeNode(JourneyCode, price, nullptr, nullptr, p);
    if(p!=nullptr){
        if(p->price>price){
        p->left=v;

        }
        else{
         p->right=v;


    }
    }
    if(flag==0){
        root=v;
    }

    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    TreeNode *v = root;
    TreeNode *p = nullptr;
    while (v != nullptr)
    {
        if (v->price == price)
        {
            if (v->JourneyCode == JourneyCode)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else if (v->price > price)
        {
            p = v;
            cout<<p->price<<endl;
            if(v->left!=nullptr){
                v = (v->left);
                cout<<v->price<<endl;
            }
            else{
                return false;
            }
        }
        else
        {
            p = v;
            if(v->right!=nullptr){
                v = (v->right);
                cout<<v->price<<endl;
            }
            else{
                return false;
            }

        }
    }
    return false;
}

struct TreeNode *BST::minValue(struct TreeNode *node)
{
    struct TreeNode *current = node;

    while (current->left != NULL)
    {
        current = current->left;
    }
    return current;
}
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    TreeNode *v = root;
    TreeNode *p = nullptr;
    while (v != nullptr)
    {

        if (v->price == price)
        {
            if (v->JourneyCode == JourneyCode)
            {
                if (v->left == nullptr && v->right == nullptr)
                {
                    if(root==v){
                        root=nullptr;
                    }
                    v=nullptr;
                    if(p->price>price){
                        p->left=nullptr;

                    }
                    else{
                        p->right=nullptr;


                    }
                    
                }
                else if (v->left == nullptr)
                {
                    if(p!=nullptr){
                    if ((p->left)->price == v->price)
                    {
                        p->left = v->right;
                    }
                    else
                    {
                        p->right = v->right;
                    }
                    (v->right)->parent = v->parent;
                    }
                    else{
                        root=v->right;
                    }

                }
                else if (v->right == nullptr)
                {
                    if(p!=nullptr){
                    if ((p->left)->price == v->price)
                    {
                        p->left = v->left;
                    }
                    else
                    {
                        p->right = v->left;
                    }
                    (v->left)->parent = v->parent;
                    }
                    else{
                        root=v->left;
                    }
                }
                else
                {
                    TreeNode *temp = Suc(v);
                    v->JourneyCode = Suc(v)->JourneyCode;
                    v->price = Suc(v)->price;
                    remove(temp->JourneyCode, temp->price);
                }

                return true;
            }
            else
            {
                return false;
            }
        }
        else if (v->price > price)
        {
            p = v;
            v = (v->left);
        }
        else
        {
            p = v;
            v = (v->right);
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
    TreeNode *v = root;
    if (typeOfTraversal == 0)
    {
        preorder(v);
    }
    else if (typeOfTraversal == 1)
    {
        postorder(v);
    }
    else
    {
        inorder(v);
    }
}

// Returns the price of the cheapest journey
int BST::getMinimum()
{
    TreeNode *v = root;
    TreeNode *p;
    int min;
    while ((v->left) != nullptr)
    {
        v = (v->left);
    }
    return (v->price);
}

struct TreeNode *BST::Suc(TreeNode *node)
{
    TreeNode *r = node->right;
    return minValue(r);
}
void BST::preorder(struct TreeNode *node)
{
    if (node == nullptr)
    {
        return;
    }
    cout << node->JourneyCode << endl;

    preorder(node->left);

    preorder(node->right);
}

void BST::postorder(struct TreeNode *node)
{
    if (node == nullptr)
    {
        return;
    }
    postorder(node->left);

    // then recur on right subtree
    postorder(node->right);

    // now deal with the node
    cout << node->JourneyCode << endl;
}

void BST::inorder(struct TreeNode *node)
{
    if (node == nullptr)
    {
        return;
    }

    inorder(node->left);

    cout << node->JourneyCode << endl;

    inorder(node->right);
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) { return 0; }

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) { return; }

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
