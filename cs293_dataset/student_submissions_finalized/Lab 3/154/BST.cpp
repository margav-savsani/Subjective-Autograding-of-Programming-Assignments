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

BST::BST(){root=nullptr; }
BST::BST(TreeNode *root){this->root = root; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    if(root == nullptr){
        root = new TreeNode(JourneyCode, price);
        root->parent = nullptr;
        return true;
    }
    if(root->price == price){
        if(root->JourneyCode == JourneyCode){
            return false;
        }
    }

    if(root->price > price){

        if(root->left == nullptr){
            root->left = new TreeNode(JourneyCode, price, nullptr, nullptr, root);
            return true;
        }
        else{
            TreeNode* curr = root;
            root = root->left;
            bool res = insert(JourneyCode, price);
            root = curr;
            return res;
        }
    }
    else{
        if(root->right == nullptr){
            root->right = new TreeNode(JourneyCode, price, nullptr, nullptr, root);
            return true;
        }
        else{
            TreeNode* curr = root;
            root = root->right;
            bool res = insert(JourneyCode, price);
            root = curr;
            return res;
        }
    }
    return false;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    if(root == nullptr){
        return false;
    }
    if(root->price == price){
        if(root->JourneyCode == JourneyCode){
            return true;
        }
    }
    TreeNode* curr = root;
    if(root->price > price){
        root = root->left;
    }
    else{
        root = root->right;
    }
    bool result = find(JourneyCode, price);
    root = curr;
    return result;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    if(root == nullptr){
        return false;
    }
    if(root->price == price){
        if(root->JourneyCode == JourneyCode){

            // if node to be deleted has 1/0 child
            if(root->left == nullptr || root->right == nullptr){
                TreeNode* child = nullptr;
                if(root->left == nullptr){
                    child = root->right;
                }
                else{
                    child = root->left;
                }
                if(root->parent != nullptr){
                    if(root->parent->left == root){
                        root->parent->left = child;
                    }
                    else if(root->parent->right == root){
                        root->parent->right = child;
                    }
                }
                if(child!=nullptr){
                    // 1 child case
                    child->parent = root->parent;
                }
                delete root;
                root = child;
                return true;
            }

            // if node has 2 childs
            TreeNode* curr = root;
            TreeNode* succesor = root->right;
            while(succesor->left != nullptr){
                succesor = succesor->left;
            }
            root->JourneyCode = succesor->JourneyCode;
            root->price = succesor->price;
            root = succesor;
            if(!remove(root->JourneyCode, root->price)){
                cout<<"MEGA ERROR\n";
                return false;
            }
            root = curr;
            return true;
        }
        // return false;
    }
    TreeNode* curr = root;
    if(root->price > price){
        root = root->left;
    }
    else{
        root = root->right;
    }
    bool result = remove(JourneyCode, price);
    root = curr;
    return result;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    if(root == nullptr) return;

    if(typeOfTraversal == PRE_ORDER){
        TreeNode* curr = root;
        cout<<curr->JourneyCode<<endl;
        root = curr->left;
        traverse(typeOfTraversal);
        root = curr->right;
        traverse(typeOfTraversal);
        root = curr;
    }
    else if(typeOfTraversal == POST_ORDER){
        TreeNode* curr = root;

        root = curr->left;
        traverse(typeOfTraversal);

        root = curr->right;
        traverse(typeOfTraversal);

        cout<<curr->JourneyCode<<endl;

        root = curr;
    }
    else if(typeOfTraversal == IN_ORDER){
        TreeNode* curr = root;

        root = curr->left;
        traverse(typeOfTraversal);

        cout<<curr->JourneyCode<<endl;

        root = curr->right;
        traverse(typeOfTraversal);

        root = curr;
    }

}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    if (root == nullptr) return 0;
    TreeNode* curr = root;
    while(curr->left != nullptr){
        curr = curr->left;
    }
    return curr->price;
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
