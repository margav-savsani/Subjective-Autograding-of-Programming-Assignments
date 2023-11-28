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

BST::BST(){ root = new TreeNode;}
BST::BST(TreeNode *root){ this -> root = root;}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    if (root -> JourneyCode == 0) {root -> JourneyCode = JourneyCode; root -> price = price; return true;} // Only when starting element is added

    TreeNode* nodeptr = root;
    while (nodeptr -> JourneyCode != JourneyCode){
        if (nodeptr -> price > price){
            if (nodeptr -> left == nullptr) {
                TreeNode* newnode = new TreeNode(JourneyCode,price);
                newnode -> parent = nodeptr;
                nodeptr -> left = newnode;
                return true;
            }
            else nodeptr = nodeptr -> left;
        }
        else {
            if (nodeptr -> right == nullptr){
                TreeNode* newnode = new TreeNode(JourneyCode,price);
                newnode -> parent = nodeptr;
                nodeptr -> right = newnode;
                return true;
            }
            else nodeptr = nodeptr -> right;
        }
    }
    return false;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    TreeNode* nodeptr = root;
    while (nodeptr != nullptr){
        if (nodeptr -> price == price){
            return (nodeptr -> JourneyCode == JourneyCode);
        }
        else {
            if (nodeptr -> price > price) nodeptr = nodeptr -> left;
            else nodeptr = nodeptr -> right;
        }
    }
    return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { // This working of remove is unstable and unpolished. As of now, only leaves can be successfully removed. Other code needs correction.
    TreeNode* nodeptr = root;
    while (nodeptr != nullptr){
        if (nodeptr -> JourneyCode == JourneyCode){
            break;
        }
        else {
            if (nodeptr -> price > price) nodeptr = nodeptr -> left;
            else nodeptr = nodeptr -> right;
        }
    }

    if (nodeptr == nullptr) return false;
    else{
        TreeNode* parentptr = nodeptr -> parent;
        if ((nodeptr -> left == nullptr) && (nodeptr -> right == nullptr)){
            if (parentptr -> left == nodeptr) parentptr -> left == nullptr;
            else parentptr -> right = nullptr;
            return true;
        }
        else {
            if ((nodeptr -> left == nullptr) || (nodeptr -> right == nullptr)){
                if (nodeptr -> left == nullptr){
                    if (parentptr -> left == nodeptr) {parentptr -> left = nodeptr -> right; nodeptr -> right -> parent = parentptr;}
                    else {parentptr -> right = nodeptr -> right; nodeptr -> right -> parent = parentptr;}
                    return true;
                }
                if (nodeptr -> right == nullptr){
                    if (parentptr -> left == nodeptr) {parentptr -> left = nodeptr -> left; nodeptr -> left -> parent = parentptr;}
                    else {parentptr -> right = nodeptr -> left; nodeptr -> left -> parent = parentptr;}
                    return true;
                }
            }
            else{
                TreeNode* probe = nodeptr -> right;
                while (probe -> left != nullptr) probe = probe -> left;
                nodeptr -> price = probe -> price; nodeptr -> JourneyCode = probe -> JourneyCode;
                TreeNode* probe_parent_ptr = probe -> parent;
                if (probe_parent_ptr -> left == probe) probe_parent_ptr -> left = nullptr;
                else probe_parent_ptr -> right = nullptr;
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

void BST::traverse(int typeOfTraversal) {

    // PreOrder Traversal
    if (typeOfTraversal == 0){
        TreeNode* nodeptr = root;
        if (nodeptr == nullptr) return;

        BST* left_sub_tree = new BST(root -> left);
        BST* right_sub_tree = new BST(root -> right);

        std::cout << root -> JourneyCode << std::endl;
        left_sub_tree -> traverse(0);
        right_sub_tree -> traverse(0);
    }

    // PostOrder Traversal
    if (typeOfTraversal == 1){
        TreeNode* nodeptr = root;
        if (nodeptr == nullptr) return;

        BST* left_sub_tree = new BST(root -> left);
        BST* right_sub_tree = new BST(root -> right);

        left_sub_tree -> traverse(1);
        right_sub_tree -> traverse(1);
        std::cout << root -> JourneyCode << std::endl;
    }

    // InOrder Traversal
    if (typeOfTraversal == 2){
        TreeNode* nodeptr = root;
        if (nodeptr == nullptr) return;

        BST* left_sub_tree = new BST(root -> left);
        BST* right_sub_tree = new BST(root -> right);

        left_sub_tree -> traverse(2);
        std::cout << root -> JourneyCode << std::endl;
        right_sub_tree -> traverse(2);
    }
    return; }

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode* nodeptr = root;
    while (nodeptr -> left != nullptr) nodeptr = nodeptr -> left;
    return nodeptr -> price; 
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

