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
    root = NULL; 
}
BST::BST(TreeNode *root){
    this->root = root; 
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    if(find(JourneyCode, price)){
        return false;
    }
    TreeNode *finder, *parent = NULL;
    finder = root;
    while(finder != NULL){
        parent = finder;
        if(finder->price >= price){
            finder = finder->left;
        }
        else if(finder->price < price){
            finder = finder->right;
        }
    }

    TreeNode *element = new TreeNode(JourneyCode, price);
    if (parent != NULL){
        element->parent = parent;
        if(parent->price >= price){
            parent->left = element;
        }
        else{
            parent->right = element;
        }
    }
    else{
        root = element;
        element->parent = NULL;
    }
    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    //demo pointer
    TreeNode *finder;
    finder = root;
    while(finder != NULL){
        if (finder->price == price){
            if (finder->JourneyCode == JourneyCode){
                return true;
            }
            else{
                finder = finder->left;
            }
        }
        else if(finder->price > price){
            finder = finder->left;
        }
        else if(finder->price < price){
            finder = finder->right;
        }
    } 
    return false; 
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    if (!find(JourneyCode, price)){
        return false;
    }

    TreeNode *finder;
    finder = root;
    while(true){
        if (finder->price == price){
            if (finder->JourneyCode == JourneyCode){
                break;
            }
            else{
                finder = finder->left;
            }
        }
        else if(finder->price > price){
            finder = finder->left;
        }
        else if(finder->price < price){
            finder = finder->right;
        }
    } 

    //Now we know that finder is pointing to the node we need to delete
    //Have to implement the different cases of deletion

    //Leaf node
    if (finder->left == NULL && finder->right == NULL){
        if((finder->parent) != NULL){
            if ((finder->parent)->right == finder){
                (finder->parent)->right = NULL;
            }
            else{
                (finder->parent)->left = NULL;
            }
        }
        else{
            root = NULL;
        }
        // USED TO SAVE SPACE
        // delete finder;
        return true;
    }

    //Having one child
    else if(finder->left != NULL && finder->right == NULL){
        if ((finder->parent) != NULL){
            if ((finder->parent)->right == finder){
                (finder->parent)->right = finder->left;
                (finder->left)->parent = finder->parent;
            }
            else{
                (finder->parent)->left = finder->left;
                (finder->left)->parent = finder->parent;
            }
        }
        else{
            root = finder->left;
            (finder->left)->parent = NULL;
        }
        // USED TO SAVE SPACE
        // delete finder;
        return true;
    } 
    else if(finder->left == NULL && finder->right != NULL){
        if ((finder->parent) != NULL){
            if ((finder->parent)->right == finder){
                (finder->parent)->right = finder->right;
                (finder->right)->parent = finder->parent;
            }
            else{
                (finder->parent)->left = finder->right;
                (finder->right)->parent = finder->parent;
            }
        }
        else{
            root = finder->right;
            (finder->right)->parent = NULL;
        }
        // USED TO SAVE SPACE
        // delete finder;
        return true;
    } 

    // Having two children
    //using predecessor method
    else{
        TreeNode *pred;
        //Here predecessor is forsure the right most element in the left sub-tree, NOTE can be equal to price value of deleted one
        pred = finder->left;
        // cout << "fnder" << finder->JourneyCode << endl;
        // cout << "pred" << pred->JourneyCode << endl;
        while(pred->right != NULL){
            pred = pred->right;
        }
        // cout << "pred" << pred->JourneyCode << endl;
        //Since our pred would be no more after deletion, lets store its inner values in new node
        int jc = pred->JourneyCode;
        int p = pred->price;
        //Need to properly delete elements, can be called recursively
        bool del = remove(jc, p); //No use of this variable, just a placeholder
        finder->JourneyCode = jc;
        finder->price = p;
    }
    return true;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::preord(TreeNode *cur_root){
    if (cur_root == NULL){
        return;
    }
    cout << cur_root->JourneyCode << endl;
    preord(cur_root->left);
    preord(cur_root->right);
}

void BST::postord(TreeNode *cur_root){
    if (cur_root == NULL){
        return;
    }
    preord(cur_root->left);
    preord(cur_root->right);
    cout << cur_root->JourneyCode << endl;
}

void BST::inord(TreeNode *cur_root){
    if (cur_root == NULL){
        return;
    }
    preord(cur_root->left);
    cout << cur_root->JourneyCode << endl;
    preord(cur_root->right);
}

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal == 0){
        preord(root);
    }

    else if(typeOfTraversal == 1){
        postord(root);
    }

    else{
        inord(root);
    }
    return; 
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode *pointer;
    pointer = root;
    if (pointer == NULL){
        return 0; 
    }
    else{
        int min = pointer->price;
        while(pointer != NULL){
            if (pointer->price < min){
                min = pointer->price;
            }
            pointer = pointer->left;
        }
        return min;
    }
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

