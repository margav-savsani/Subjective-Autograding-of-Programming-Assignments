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
BST::BST(TreeNode *root):root(root) {}

void findjour(TreeNode* head, int code, bool &f){
    if (head==nullptr) return;
    if (head->JourneyCode==code){
        f=true;
    }
    findjour(head->left, code, f);
    findjour(head->right, code, f);
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
    bool already_present = false;
    findjour(root, JourneyCode, already_present);
    if (already_present){return false;}
    TreeNode *next = root;
    TreeNode* node = nullptr;
    while(next!=nullptr){
        node = next;
        if (next->price>price){
            next = next->left;
        }
        else {
            next = next->right;
        }
    }
    // Now node is where we have to insert the new ticket.
    // If node is nullptr, we need to create a node and make it root.
    if (node==nullptr){
        root = new TreeNode(JourneyCode, price, nullptr, nullptr, nullptr);
    }
    else if (node->price>price){
        node->left = new TreeNode(JourneyCode, price, nullptr, nullptr, node);
    }
    else {
        node->right = new TreeNode(JourneyCode, price, nullptr, nullptr, node);
    }
    return true;
}

TreeNode* BST::getNode(int JourneyCode, int price){
    TreeNode* rootptr = root;
    while(rootptr!=nullptr && price!=rootptr->price){
        if (price<rootptr->price){
            rootptr = rootptr->left;
        }
        else {rootptr = rootptr->right;}
    }
    if (rootptr==nullptr) return nullptr;
    return (rootptr->JourneyCode==JourneyCode ? rootptr : nullptr);
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    if (getNode(JourneyCode, price)==nullptr){
        return false;
    }
    return true;
}

TreeNode* BST::twochild_successor(TreeNode* node){
    TreeNode* curr = node->right;
    TreeNode* left = curr->left;
    while(left!=nullptr){
        curr = left;
        left = left->left;
    }
    return curr;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
    TreeNode* del = getNode(JourneyCode, price);
    if (del==nullptr){
        return false;
    }
    // If node has no children, simply delete the node
    if (del->right==nullptr && del->left==nullptr){
        TreeNode* p = del->parent;
        if (p==nullptr){root=nullptr; delete del; return true;}
        char c = (p->left==del ? 'l' : 'r');
        delete del;
        if (c=='l'){
            p->left=nullptr;
        }
        else {p->right=nullptr;}
        return true;
    }

    // If the node has one child
    if (del->right==nullptr || del->left==nullptr){
        TreeNode *p = del->parent;
        TreeNode *child = (del->right==nullptr ? del->left : del->right);
        if (p==nullptr){root = child; child->parent=nullptr; delete del; return true;}
        char c = (p->left==del ? 'l' : 'r');
        delete del;
        if (c=='l'){
            p->left = child;
            child->parent = p;
        }
        else {
            p->right = child;
            child->parent = p;
        }
        return true;
    }
    // If the node has 2 children
    TreeNode* succ = twochild_successor(del);
    // We know that succ has only a right child or no child.

    // Copying successor into the node to be deleted
    del->JourneyCode = succ->JourneyCode;
    del->price = succ->price;
    // Deleting successor, easier to delete than node which has 2 children
    TreeNode* child = succ->right; //could be nullptr
    TreeNode* succ_parent = succ->parent;
    if (succ_parent->left==succ){
        succ_parent->left = child;
    }
    else {
        succ_parent->right=child;
    }
    if (child!=nullptr) {child->parent = succ_parent;}
    delete succ;
    return true;
}

void BST::preorder(TreeNode* head){
    if (head==nullptr) return;
    cout<<head->JourneyCode<<endl;
    preorder(head->left);
    preorder(head->right);
}

void BST::postorder(TreeNode* head){
    if (head==nullptr) return;

    postorder(head->left);
    postorder(head->right);
    cout<<head->JourneyCode<<endl;
}

void BST::inorder(TreeNode* head){
    if (head==nullptr) return;

    inorder(head->left);
    cout<<head->JourneyCode<<endl;
    inorder(head->right);
}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    if (typeOfTraversal==PRE_ORDER){
        preorder(root);
    }
    else if (typeOfTraversal==POST_ORDER){
        postorder(root);
    }
    else if (typeOfTraversal==IN_ORDER){
        inorder(root);
    }

}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode *node = root;
    TreeNode* left = node->left;
    while(left!=nullptr){
        node = left;
        left = left->left;
    }
    return node->price; 
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

        result.push_back(isLeft ? "├──" : "└──" );

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

