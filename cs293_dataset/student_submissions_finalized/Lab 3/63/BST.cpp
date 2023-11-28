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

BST::BST(){
    this->root = new TreeNode();
    this->root->parent = nullptr;
}
BST::BST(TreeNode *root){
    this->root = root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    TreeNode * A = this->root;
    while (true){
        if (A->parent == nullptr && A->JourneyCode == 0 && A->price == 0){
            A->JourneyCode = JourneyCode;
            A->price = price;
            return 1;
        }
        if (A->JourneyCode == JourneyCode && A->price == price){
            return 0;
        }

        if (price > A->price && A->right != nullptr){
            A = A->right;
            continue;
        }
        else if (price <= A->price && A->left != nullptr){
            A = A->left;
            continue;
        }
        else if (price <= A->price && A->left == nullptr){
            A->left = new TreeNode(JourneyCode, price);
            A->left->parent = A;
            return 1;
        }
        else if (price > A->price && A->right == nullptr){
            A->right = new TreeNode(JourneyCode, price);
            A->right->parent = A;
            return 1;
        }
    }
    return false;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    TreeNode * A = this->root;
    while(true){
        if (A->price == price){
            if (A->JourneyCode == JourneyCode){
                return 1;
            }
            else if(A->left != nullptr && A->left->price == price){
                A = A->left;
                continue;
            }
            return 0;
        }
        else if(A->price > price){
            if (A->left == nullptr){
                return 0;
            }
            A = A->left;
            continue;
        }
        else if(A->price < price){
            if (A->right == nullptr){
                return 0;
            }
            A = A->right;
            continue;
        }
    }
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    TreeNode * A = root;
    while(true){
        if (A->price == price){
            if (A->JourneyCode == JourneyCode){
                break;
            }
            else if(A->left != nullptr && A->left->price == price){
                A = A->left;
                continue;
            }
            return 0;
        }
        else if(A->price > price){
            if (A->left == nullptr){
                return 0;
            }
            A = A->left;
            continue;
        }
        else if(A->price < price){
            if (A->right == nullptr){
                return 0;
            }
            A = A->right;
            continue;
        }
    }
    if (A->left == nullptr && A->right == nullptr){
        A->parent = nullptr;
        return 1;
    }
    else if (A->left == nullptr){
        if (A->parent == nullptr){
            A->right->parent = A->parent;
            return 1;
        }

        if (A->parent->left == A){
            A->parent->left = A->right;
        }
        else if (A->parent->right == A){
            A->parent->right = A->right;
        }
        A->right->parent = A->parent;

        return 1;
    }
    else if (A->right == nullptr){
        if (A->parent == nullptr){
            A->left->parent = A->parent;
            return 1;
        }

        if (A->parent->left == A){
            A->parent->left = A->left;
        }
        else if (A->parent->right == A){
            A->parent->right = A->left;
        }
        A->left->parent = A->parent;
        return 1;
    }

    TreeNode * B = A->right;
    while (B->left != nullptr){
        B = B->left;
    }
    if (A->parent == nullptr){
        B->parent = nullptr;
        B->right = A->right;
        B->left = A->left;
        return 1;
    }
    if (A->parent->left == A){
            A->parent->left = B;
        }
    else if (A->parent->right == A){
        A->parent->right = B;
    }
    B->parent = A->parent;
    return 1;
}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    if (root == nullptr) return;
    TreeNode * T = root;
    if (typeOfTraversal == PRE_ORDER){
        root = T->left;
        traverse(PRE_ORDER);
        root = T->right;
        traverse(PRE_ORDER);
    }
    else if(typeOfTraversal == POST_ORDER){
        root = T->left;
        traverse(POST_ORDER);
        root = T->right;
        traverse(POST_ORDER);
        root = T;
    }
    else if (typeOfTraversal == IN_ORDER){
        root = T->left;
        traverse(IN_ORDER);
        root = T;
        cout << root->JourneyCode << endl;
        root = T->right;
        traverse(IN_ORDER);
    }
    root = T;
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode * A = this->root;
    while (A->left != nullptr){
        A = A->left;
    }
    return A->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {return 0; }

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
 
void BST::customLoad (int flag, string filename) { return; }


// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
void BST::printBST(const string& prefix, bool isLeft=false)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->JourneyCode << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = root->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::getBST(const string& prefix,  bool isLeft=false)
{
    if( root != nullptr )
    {
        result.push_back(prefix);

        result.push_back(isLeft ? "├──" : "└──" );

        // print the value of the node
        result.push_back(root->JourneyCode + "\n");
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        getBST( prefix + (isLeft ? "│   " : "    "), true);
        root = root->right;
        getBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::clearResult(){
    result.clear();
}

vector<string> BST::getResult(){
    return result;
}

