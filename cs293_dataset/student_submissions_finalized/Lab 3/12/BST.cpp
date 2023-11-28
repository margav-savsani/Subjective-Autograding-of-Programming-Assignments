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

BST::BST(): root(nullptr){}
BST::BST(TreeNode *root): root(root){}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
    // Check if the tree is empty.
    if (!root){
        root = new TreeNode(JourneyCode, price, nullptr);
        return true;
    }
    TreeNode *curr = root;

    // binary search loop. Search for where to put it.
    while (true){

        // invariant: curr is never null.

        if (curr->JourneyCode == JourneyCode)
            return false; // this journey code is already in the tree - we do not add another entry for the same journey.
        
        if (price < curr->price){
            if (curr->left) 
                curr = curr->left; // search in the left subtree of curr.
            else{
                curr->left = new TreeNode(JourneyCode, price, curr); // place it if left subtree does not exist. This insert preserves the bst property.
                return true;
            }
        }
        else {
            if (curr->right) 
                curr = curr->right; // search in the right subtree of curr
            else{
                curr->right = new TreeNode(JourneyCode, price, curr); // place it if right subtree does not exist
                return true;
            }
        }
    }
    // The above loop is bound to terminate since depth of the tree left to check is bounded below by 0 and is strictly decreasing.
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    return (getnode(JourneyCode, price) != nullptr);
}

TreeNode *BST::getnode(int JourneyCode, int price) const{
    // Check if the tree is empty.
    if (!root){
        return nullptr; // the journey cannot possibly be here.
    }
    TreeNode *curr = root;

    // binary search loop to search for the key.
    while (true){
        // invariant: curr is never null.

        if (curr->JourneyCode == JourneyCode)
            return (curr->price == price) ? curr: nullptr; // both attributes must match. But we must exit the loop if the right key(journey code) is found, since we are guaranteed this key occurs only once by the insertion procedure. So we don't look further for it.
        
        if (price < curr->price){
            if (curr->left) 
                curr = curr->left; // search in the left subtree of curr.
            else{
                return nullptr;
            }
        }
        else {
            if (curr->right) 
                curr = curr->right; // search in the right subtree of curr.
            else{
                return nullptr;
            }
        }
    }
    // The above loop is bound to terminate since depth of the tree left to check is bounded below by 0 and is strictly decreasing.
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
    if (!root)
        return false; // cannot delete non-existent node.
    
    TreeNode *loc = getnode(JourneyCode, price);
    if (!loc)
        return false; // cannot delete non-existent node.

    return del(loc); // loc is a valid TreeNode in the tree.
    // del will return true here.
    
    // int degree = bool(loc->left) + bool(loc->right);

    // switch (degree)
    // {
    // case 0:
    // {
    //     TreeNode *par = loc->parent;
    //     if (!par); // this is here to assert that par is not nullptr so that the later else-if's can assume par != nullptr. Ideally we can just return in this case and then move on, but this is a nice idea.
    //     else if (par->left == loc){
    //         par->left = nullptr;
    //     }
    //     else{
    //         assert(par->right == loc);
    //         par->right = nullptr;
    //     }
    //     delete loc;
    //     break;
    // }
    // 
    // case 1:
    // {
    //     TreeNode *par = loc->parent;
    //     TreeNode *child = (loc->left) ? loc->left: loc->right;
    //     assert(child);
    //     if (par->left == loc){
    //         par->left = child; // assign the left of parent to loc's child - as though loc was not even there.
    //         child->parent = par;
    //     }
    //     else{
    //         par->right = child;
    //         child->parent = par;
    //     }
    //     delete loc;
    //     break;
    // }
    
    // case 2:
    // {
    //     TreeNode *succ_loc = BST(loc->right).min();
    //     loc->JourneyCode = succ_loc->JourneyCode;
    //     loc->price = succ_loc->price; // just change the JourneyCode and price in loc. The pointers must remain as is.
        

    // }

    // }
}

// deleted a node given a pointer to it. Note that we will call this function only when we are sure that loc is a valid TreeNode* in the tree.
bool BST::del(TreeNode *loc){
    if (!root)
        return false; // cannot delete non-existent node.
    if (!loc)
        return false; // cannot delete non-existent node.

    int degree = bool(loc->left) + bool(loc->right);

    switch (degree)
    {
    case 0:
    {
        TreeNode *par = loc->parent;
        if (!par); // this is here to assert that par is not nullptr so that the later else-if's can assume par != nullptr. Ideally we can just return in this case and then move on, but this is a nice idea.
        else if (par->left == loc){
            par->left = nullptr;
        }
        else{
            assert(par->right == loc);
            par->right = nullptr;
        }
        delete loc;
        break;
    }

    case 1:
    {
        TreeNode *par = loc->parent;
        TreeNode *child = (loc->left) ? loc->left: loc->right;
        assert(child);
        if (!par){
            child->parent = nullptr;
            delete loc;
            break;
        }
        if (par->left == loc){
            par->left = child; // assign the left of parent to loc's child - as though loc was not even there.
            child->parent = par;
        }
        else{
            par->right = child;
            child->parent = par;
        }
        delete loc;
        break;
    }
    
    case 2:
    {
        TreeNode *succ_loc = BST(loc->right).min();
        loc->JourneyCode = succ_loc->JourneyCode;
        loc->price = succ_loc->price; // just change the JourneyCode and price in loc. The pointers must remain as is.

        del(succ_loc); // we are guaranteed, by construction of succ_loc, that we will enter either case 0/case 1 in this call to del.
        break;
    }

    }
    return true;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    switch (typeOfTraversal)
    {
    case PRE_ORDER:
        cout << root->JourneyCode << endl;
        if (root->left) BST(root->left).traverse(PRE_ORDER);
        if (root->right) BST(root->right).traverse(PRE_ORDER);
        break;
    case POST_ORDER:
        if (root->left) BST(root->left).traverse(POST_ORDER);
        if (root->right) BST(root->right).traverse(POST_ORDER);
        cout << root->JourneyCode << endl;
        break;
    case IN_ORDER:
        if (root->left) BST(root->left).traverse(IN_ORDER);
        cout << root->JourneyCode << endl;
        if (root->right) BST(root->right).traverse(IN_ORDER);
        break;
    default:
        cout << "Invalid type of Traversal.\nUsage: Pre-order 0 Post-order 1 In-order 2" << endl;
    }
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode *loc_of_min = min();
    if (!loc_of_min)
        return -1; // return value if no element in the tree.
    return loc_of_min->price;
}

TreeNode *BST::min() const{
    if (!root)
        return nullptr; // no min-element iff tree is empty.
    
    TreeNode *curr = root;
    while(curr->left)
        curr = curr->left;
    return curr;
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
