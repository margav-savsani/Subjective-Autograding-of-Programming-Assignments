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
    root = nullptr;
}
BST::BST(TreeNode *root){
    this->root = root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price){
    if(find(JourneyCode, price)) return false;
    
    TreeNode* check = root, *toadd = new TreeNode(JourneyCode, price);
    if(check == nullptr){
        root = toadd;
        return true;
    }
    while(true){
        if(check->price >= price){
            if(check->left != nullptr){
                check = check->left;
            }
            else{
                check->left = toadd;
                return true;
            }
        }
        else{
            if(check->right != nullptr){
                check = check->right;
            }
            else{
                check->right = toadd;
                return true;
            }
        }
    }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price){
    TreeNode* check = root;
    if(check == nullptr) return false;
    if(check->price == price){
        return (check->JourneyCode == JourneyCode) || BST(check->left).find(JourneyCode, price) || BST(check->right).find(JourneyCode, price);
    }
    if(price < check->price) return (BST(check->left).find(JourneyCode, price));
    else return (BST(check->right).find(JourneyCode, price));
}

void BST::preorder(TreeNode* v){
    if(v==nullptr) return;
    cout << v->JourneyCode << "\n";
    preorder(v->left);
    preorder(v->right);
}

void BST::postorder(TreeNode* v){
    if(v==nullptr) return;
    preorder(v->left);
    preorder(v->right);
    cout << v->JourneyCode << "\n";
}

void BST::inorder(TreeNode* v){
    if(v==nullptr) return;
    preorder(v->left);
    cout << v->JourneyCode << "\n";
    preorder(v->right);
}

TreeNode* BST::findnode(int JourneyCode, int price){
    TreeNode* check = root;
    if(check == nullptr) return check;
    if(check->price == price){
        if((check->JourneyCode == JourneyCode)){
            return check;
        }
        else if(BST(check->left).find(JourneyCode, price)){
            return BST(check->left).findnode(JourneyCode, price);
        }
        else if(BST(check->right).find(JourneyCode, price)){
            return BST(check->right).findnode(JourneyCode, price);
        }
    }
    if(price < check->price) return (BST(check->left).findnode(JourneyCode, price));
    else return (BST(check->right).findnode(JourneyCode, price));
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price){
    if(!find(JourneyCode, price)) return false;

    TreeNode* node = findnode(JourneyCode, price);
    if(node->left == nullptr){
        TreeNode* a = node->parent;
        if(a->left->JourneyCode == JourneyCode && a->left->price == price) a->left = node->right;
        else if(a->right->JourneyCode == JourneyCode && a->right->price == price) a->right = node->right;
        return true;
    }
    if(node->right == nullptr){
        TreeNode* a = node->parent;
        if(a->left != nullptr && a->left->JourneyCode == JourneyCode && a->left->price == price) a->left = node->left;
        else if(a->right != nullptr && a->right->JourneyCode == JourneyCode && a->right->price == price) a->right = node->left;
        return true;
    }

    TreeNode* pred = node->left;
    while(pred->right != nullptr){
        pred = pred->right;
    }
    pred->parent->parent = pred->left;
    pred->parent = node->parent;
    pred->left = node->left;
    pred->right = node->right;
    return true;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal){
    if(typeOfTraversal == PRE_ORDER) preorder(root);
    else if(typeOfTraversal == POST_ORDER) postorder(root);
    else if(typeOfTraversal == IN_ORDER) inorder(root);
}

// Returns the price of the cheapest journey
int BST::getMinimum(){
    TreeNode* check = root;
    if(check == nullptr) return 0;
    while(check->left != nullptr){
        check = check->left;
    }
    return check->price;
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
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::getBST(const string& prefix,  bool isLeft=false)
{
    if( root != nullptr )
    {
        result.push_back(prefix);

        result.push_back(isLeft ? "|--" : "|__" );

        // print the value of the node
        result.push_back(root->JourneyCode + "\n");
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        getBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
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
