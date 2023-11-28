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
    root=NULL;
}

BST::BST(TreeNode *root){
    this->root = root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
        TreeNode *y,*x,*z;
        x = root;
        z =new TreeNode(JourneyCode,price);
        y=NULL;
        while(x != NULL) {
            y = x;
            if(z->price < x->price) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }
        z->parent = y;
        if(y == NULL) {
            root = z;
            return true;
        }
        else if(z->price < y->price) {
                 y->left = z;
                 return true; 
        }
        else {
                y->right = z;
                return true;
        }
        return false;
}

TreeNode* BST::find_tree(TreeNode* x,int price) {
        if(x == NULL) {
            return NULL;
        }
        if(price == x->price) {
            return x;
        }
        if(price < x->price) {
            return find_tree(x->left,price);
        }
        else {
            return find_tree(x->right,price);
        }
        return NULL;

}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    if(find_tree(root,price)==NULL) return false;
    return true;
}

TreeNode* BST::mini(TreeNode* x) {
    if(x == NULL) return NULL;
    while(x->left != NULL) {
        return mini(x->left);
    }
    return x;
}
	
TreeNode* tr_suc(TreeNode* x) {
    if(x->right!=NULL) {
        TreeNode *a,*b;
        a = x->right;
        while(a->left != NULL) {
            a = a->left;
        }
        return a;
    }
    TreeNode* y=x->parent;
    while(y!=NULL && x==(y->right)) {
        x=y;
        y=y->parent;
        return y;
    }
    return NULL;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
    TreeNode *x,*z,*y;
    x=root;
    y=tr_suc(x);
    z = find_tree(x,price);
    if(z->left==NULL || z->right==NULL) {
        y=z;
    }
    else {
        y = tr_suc(z);
    }
    if(y->left != NULL) {
        x=y->left;
    }
    else {
        x=y->right;
    }
    if(x!=NULL) {
        x->parent=y->parent;
    }
    if(y->parent==NULL) {
        root = x;
    }
    else if(y==(y->parent)->left) {
        x=(y->parent)->left;
    }
    else {
        x=(y->parent)->right;
    }
    if(y!=z) {
        z->price = y->price;
    }
    return y;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::Pre_order(TreeNode* t) {
    if(t==NULL) return;
    cout << t->price <<endl;
    Pre_order(t->left);
    Pre_order(t->right);
    return;
}

void BST::Post_order(TreeNode* t) {
    if(t==NULL) return;
    Pre_order(t->left);
    Pre_order(t->right);
    cout << t->price << endl;
    return;
}

void BST::in_order(TreeNode* t) {
    if(t==NULL) return;
    Pre_order(t->left);
    cout << t->price << endl;
    Pre_order(t->right);
    return;
}

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal==0) Pre_order(root);
    if(typeOfTraversal==1) Post_order(root); 
    if(typeOfTraversal==2) in_order(root);  
    return;
}

// Returns the price of the cheapest journey

int BST::getMinimum() {
    return mini(root)->price;
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

