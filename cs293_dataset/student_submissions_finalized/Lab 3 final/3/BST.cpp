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

BST::BST() { root = new TreeNode(0, 0, nullptr, nullptr, nullptr); }
BST::BST(TreeNode *root) : root(root) { ; }

ofstream indata;                                            // used in custom store
ifstream outdata;                                           // used in custom load

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{
    TreeNode *active;
    active = root;                                          // here active changes for every for loop according to price values
    for (int i = 0; i >= 0; i++)
    {
        if (active->JourneyCode == 0)                       // for the initial root case
        {
            active->JourneyCode = JourneyCode;
            active->price = price;
            return true;
        }

        if (active->JourneyCode == JourneyCode)             // inserts the element
            return false;

        if (active->price < price)                          // pushes active to right
        {
            if (active->right == nullptr)
            {
                active->right = new TreeNode(0, 0, nullptr, nullptr, active);
                active->right->parent = active;
            }
            active = active->right;
        }
        else                                                // pushes active to left
        {
            if (active->left == nullptr)
            {
                active->left = new TreeNode(0, 0, nullptr, nullptr, active);
                active->left->parent = active;
            }
            active = active->left;
        }
    }
    return false;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)                  // the function of active here is same as in insert
{
    TreeNode *active;
    active = root;
    for (int i = 0; i >= 0; i++)
    {
        if (active->JourneyCode == JourneyCode)             // returns true if found
            return true;

        if (active->price < price)
        {
            if (active->right == nullptr)
            {
                return false;
            }
            else
                active = active->right;
        }
        else
        {
            if (active->left == nullptr)
            {
                return false;
            }
            else
                active = active->left;
        }
    }

    return false;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    TreeNode *active;
    TreeNode *temp;
    active = root;                                          // the function of active here is same as in insert

    for (int i = 0; i >= 0; i++)
    {
        if (active->JourneyCode == JourneyCode)
        {
            if (active->left == nullptr && active->right == nullptr) // no sub nodes case
            {
                if (active->parent == nullptr)
                {
                    active->JourneyCode = 0;
                    active->price = 0;
                    return true;
                }
                else if (active->parent->right == active) // del of root case
                {
                    active->parent->right = nullptr;
                    return true;
                }
                else
                {
                    active->parent->left = nullptr;
                    return true;
                }

                return true;
            }
            else if (active->left == nullptr)               // only right sub node case
            {
                if (active->parent == nullptr)
                {
                    root = active->right;
                    root->parent = nullptr;
                    return true;
                }
                else
                {
                    if (active->parent->right == active)    // both nodes case
                    {
                        active->parent->right = active->right;
                        active->right->parent = active->parent;
                        return true;
                    }
                    else
                    {
                        active->parent->left = active->right;
                        active->right->parent = active->parent;
                        return true;
                    }
                }
            }
            else if (active->right == nullptr)
            {
                if (active->parent == nullptr)
                {
                    root = active->left;
                    root->parent = nullptr;
                    return true;
                }
                else
                {
                    if (active->parent->right == active)
                    {
                        active->parent->right = active->left;
                        active->left->parent = active->parent;
                        return true;
                    }
                    else
                    {
                        active->parent->left = active->left;
                        active->left->parent = active->parent;
                        return true;
                    }
                }
            }
            else
            {
                if (active->parent == nullptr)                  // root del case in both nodes case
                {
                    temp = active->right;
                    while (true)
                    {
                        if (temp->left == nullptr)
                        {
                            temp->left = new TreeNode(active->left->JourneyCode, active->left->price, active->left->left, active->left->right, temp);
                            root = active->right;
                            root->parent = nullptr;
                            return true;
                        }
                        temp = temp->left;
                    }
                }
                else                                            // non root case
                {
                    temp = active->right;
                    while (true)
                    {
                        if (temp->left == nullptr)
                        {
                            temp->left = new TreeNode(active->left->JourneyCode, active->left->price, active->left->left, active->left->right, temp);
                            break;
                        }
                        temp = temp->left;
                    }
                    if (active->parent->right == active)
                    {
                        active->parent->right = active->right;
                        active->right->parent = active->parent;
                        return true;
                    }
                    else
                    {
                        active->parent->left = active->right;
                        active->right->parent = active->parent;
                        return true;
                    }
                }
            }
        }

        if (active->price < price)                              // this loop has similiar function as in insert
        {
            if (active->right == nullptr)
            {
                return false;
            }
            else
                active = active->right;
        }
        else
        {
            if (active->left == nullptr)
            {
                return false;
            }
            else
                active = active->left;
        }
    }

    return false;
}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::prints(int x, TreeNode *node)                             // sub function for traverse
{
    if (node == nullptr) return;

    if (x == 0)                                                     // pre order case
    {
        cout<<node->JourneyCode<<endl;
        if(node->left != nullptr) prints(0, node->left);
        if(node->right != nullptr) prints(0, node->right);
        return;
    }

    if (x == 2)                                                     // in order case
    {
        if(node->left != nullptr) prints(2, node->left);
        cout << node->JourneyCode << endl;
        if(node->right != nullptr) prints(2, node->right);
        return;
    }

    if (x == 1)                                                     // post order case
    {
        if(node->left != nullptr) prints(1, node->left);
        if(node->right != nullptr) prints(1, node->right);
        cout << node->JourneyCode << endl;
        return;
    }

}

void BST::traverse(int typeOfTraversal)
{
    if (root->JourneyCode == 0)
        return;

    if (typeOfTraversal == 0)                                       // goes into sub function and operates recurcively
    {
        cout << root->JourneyCode << endl;
        if(root->left != nullptr) prints(0, root->left);
        if(root->right != nullptr) prints(0, root->right);
        return;
    }

    if (typeOfTraversal == 2)
    {
        if(root->left != nullptr) prints(2, root->left);
        cout << root->JourneyCode << endl;
        if(root->right != nullptr) prints(2, root->right);
        return;
    }

    if (typeOfTraversal == 1)
    {
        if(root->left != nullptr) prints(1, root->left);
        if(root->right != nullptr) prints(1, root->right);
        cout << root->JourneyCode << endl;
        return;
    }
}

// Returns the price of the cheapest journey
int BST::getMinimum()
{
    TreeNode *active;
    active = root;

    for (int i = 0; i >= 0; i++)                                    // goes till non empty left most element and outputs price
    {
        if (active->JourneyCode == 0)
        {
            return 0;
        }

        if (active->left == nullptr)
        {
            return active->price;
        }
        else
            active = active->left;
    }

    return 0;
}

// Part II

int BST::counts(TreeNode *node, int lowerPriceBound, int upperPriceBound) // sub function for price bound
{
    if (lowerPriceBound <= node->price && node->price <= upperPriceBound) // sufficient case
    {
        if (node->left != nullptr && node->right != nullptr)
        {
            return 1+counts(node->right,lowerPriceBound,upperPriceBound)+counts(node->left,lowerPriceBound,upperPriceBound);
        }
        else if (node->left != nullptr)
        {
            return 1+counts(node->left,lowerPriceBound,upperPriceBound);
        }
        else if (node->right != nullptr)
        {
            return 1+counts(node->right,lowerPriceBound,upperPriceBound);
        }
        else return 1;
    }
    else if (lowerPriceBound > node->price)                                 // goes to left
    {
        if (node->right != nullptr)
        {
            return counts(node->right,lowerPriceBound,upperPriceBound);
        }
        else
        {
            return 0;
        }
        
    }
    else if (upperPriceBound < node->price)                                 // goes to right
    {
        if (node->left != nullptr)
        {
            return counts(node->left,lowerPriceBound,upperPriceBound);
        }
        else
        {
            return 0;
        }
        
    }
    else return 0;
}

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) // outputs total count
{
    return counts(root, lowerPriceBound, upperPriceBound);
}

void BST :: stores(TreeNode *node)                                           // recurcive sub funtion for custom store
{
    indata<<node->JourneyCode<<" "<<node->price<<endl;
    if (node->left != nullptr) stores(node->left);
    if (node->right != nullptr) stores(node->right);                         // operates in pre order
    return;
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename)                                      // stores in pre order
{
    indata.open(filename);

    indata<<root->JourneyCode<<" "<<root->price<<endl;

    if(root->left != nullptr) stores(root->left);
    indata<<'0'<<endl;
    if(root->right != nullptr) stores(root->right);

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
void BST::customLoad(int flag, string filename)
{
    outdata.open(filename);
    int code;
    int pr;
    TreeNode *active;
    TreeNode *temp;
    active = root;

    outdata >> code;
    outdata >> pr;
    active->JourneyCode = code;
    active->price = pr;


    if(flag == LOAD_FULL_BST)
    {
        while( outdata >> code)
        {
            if (code == 0) outdata>>code;
            
            outdata >> pr;

            insert(code,pr);
        }
        return;
    }

    if(flag == LOAD_LEFT_SUBTREE)
    {
        outdata>>code;outdata>>pr;

        while( outdata >> code && code != 0)
        {
            outdata >> pr;
            insert(code,pr);
        }
        return;
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
