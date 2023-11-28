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

BST::BST(){root = nullptr; }
BST::BST(TreeNode *root){BST::root = root; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
    if(root == nullptr){
        //cout << "here1" << endl;
        root = new TreeNode(JourneyCode, price, nullptr, nullptr, nullptr);
        //cout << root->JourneyCode << root->price << endl;
        /*
        cout << "PRE" << endl;
        traverse(0);
        cout << "IN" << endl;
        traverse(2);
        */
        return true;
    }
    //cout << "here2" << endl;
    TreeNode *current_node = root;
    TreeNode *current_node_parent = nullptr;
    while(current_node != nullptr){
        if (JourneyCode == current_node->JourneyCode) return 0;
        if (price < current_node->price){
            //cout << "hereleft" << endl;
            current_node_parent = current_node;
            current_node = current_node->left;
        }
        else{
            //cout << "hereright" << endl;
            current_node_parent = current_node;
            current_node = current_node->right;
        }
    }
    current_node = new TreeNode(JourneyCode, price, nullptr, nullptr, current_node_parent);
    if(price < current_node_parent->price){
        current_node_parent->left = current_node;
    }
    else{
        current_node_parent->right = current_node;
    }
    //cout << root->JourneyCode << root->price << endl;
    //cout << current_node->JourneyCode << current_node->price << endl;
    /*
    cout << "PRE" << endl;
    traverse(0);
    cout << "IN" << endl;
    traverse(2);
    */
    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    TreeNode *current_node = root;
    while (current_node != nullptr){
        if (JourneyCode == current_node->JourneyCode && price == current_node->price) return true;
        if (price < current_node->price){
            current_node = current_node->left;
        }
        else{
            current_node = current_node->right;
        }
    }
    return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
    TreeNode *current_node = root;
    while (current_node != nullptr){
        if (JourneyCode == current_node->JourneyCode && price == current_node->price){
            if (current_node->left == nullptr && current_node-> right == nullptr){
                //cout << "here" << current_node->JourneyCode << " " << current_node->price << endl;
                if(current_node->parent != nullptr){
                    if(current_node->price < current_node->parent->price){
                        current_node->parent->left = nullptr;
                    }
                    else{
                        current_node->parent->right = nullptr;
                    }
                }
                else root = nullptr;
                delete[] current_node;
                current_node = nullptr;
            }
            else if (current_node->left == nullptr || current_node->right == nullptr){
                TreeNode *current_node_parent = current_node->parent;
                TreeNode *current_node_child;

                if(current_node->left != nullptr){
                    current_node_child = current_node->left;
                }
                else if (current_node->right != nullptr){
                    current_node_child = current_node->right;
                }

                current_node_child->parent = current_node_parent;
                if(current_node->parent != nullptr){
                    if(current_node_child->price < current_node_parent->price){
                        current_node_parent->left = current_node_child;
                    }
                    else{
                        current_node_parent->right = current_node_child;
                    }
                }
                else root = current_node_child;
                delete[] current_node;
            }
            else{
                TreeNode *successor = current_node->right;
                while(successor->left != nullptr) successor = successor->left;
                TreeNode *current_node_parent = current_node->parent;
                TreeNode temp(successor->JourneyCode, successor->price, successor->left, successor->right, current_node_parent);
                remove(successor->JourneyCode, successor->price);
                current_node->JourneyCode = temp.JourneyCode;
                current_node->price = temp.price;
            }
            /*
            cout << "PRE" << endl;
            traverse(0);
            cout << "IN" << endl;
            traverse(2);
            */
            return true;
        }
        if (price < current_node->price){
            current_node = current_node->left;
        }
        else{
            current_node = current_node->right;
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
    if(root != nullptr){
        TreeNode *curr = root;
        //cout << "here" << endl;
        if(typeOfTraversal == 0){ // PRE ORDER
            cout << curr->JourneyCode << endl;
            root = curr->left;
            traverse(typeOfTraversal);
            root = curr->right;
            traverse(typeOfTraversal);
        }
        else if(typeOfTraversal == 1){ // POST ORDER
            root = curr->left;
            traverse(typeOfTraversal);
            root = curr->right;
            traverse(typeOfTraversal);
            cout << curr->JourneyCode << endl;
        }
        else{ // IN ORDER
            root = curr->left;
            traverse(typeOfTraversal);
            cout << curr->JourneyCode << endl;
            root = curr->right;
            traverse(typeOfTraversal);
        }
        root = curr;
    }
    return;
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    if(root == nullptr) return 0;
    TreeNode *current_node = root;
    while(current_node->left != nullptr) current_node = current_node->left;
    return current_node->price;
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


// Please use the following code to replace the last part of
// BST.cpp that was provided earlier (from below the comment
// DO NOT CHANGE ANYTHING BELOW THIS LINE)
//
//

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

