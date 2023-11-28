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
BST :: BST(){
    root = NULL;
}

BST :: BST(TreeNode *root){
    this->root = root;
}

bool BST :: ins(TreeNode *p, int JourneyCode, int price){
    if(root==NULL){
        TreeNode *i = new TreeNode(JourneyCode, price, NULL, NULL, NULL);
        root = i;
        return true;
    }
    else{
        if (price == p->price){
            if (JourneyCode == p->JourneyCode){
                return false;
            } 
        }
        if (price > p->price){
            if (p->right == NULL){
                TreeNode *val = new TreeNode(JourneyCode, price);
                p->right = val;
                return true;
            }
            return ins(p->right, JourneyCode, price);
        }
        else{
            if(p->left == NULL){
                TreeNode *value = new TreeNode(JourneyCode, price); 
                p->left = value;
                return true;  
            }
            return  ins(p->left, JourneyCode, price);
        }
    }
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST :: insert(int JourneyCode, int price){
    TreeNode *i = root;
    return ins(i,JourneyCode,price);
}

bool BST :: findfunc(TreeNode *p, int JourneyCode, int price) {
    if(price == p->price){
        if(JourneyCode == p->JourneyCode){
            return true;
        }
        else{
            return false;
        }
    }
    if(price > p->price){
        if(p->right == NULL){
            return false;
        }
        return findfunc(p->right, JourneyCode, price);
    }
    if(price < p->price){
        if(p->left == NULL){
            return false;  
        }
        return findfunc(p->left, JourneyCode, price);
    }
    return false;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST :: find(int JourneyCode, int price){
    TreeNode *f = root;
    return findfunc(f, JourneyCode, price);
}

TreeNode* BST :: min(TreeNode *n){
    while(n->left != NULL){
        n = n->left;
    }
    return n;
}

TreeNode* BST :: del(TreeNode *r, int key){
    if(r == NULL){
        return r;
    }
    if(key < r->price){
        r->left = del(r->left, key);
    }
    else if(key > r->price){
        r->right = del(r->right, key);
    }
    else{
        if(r->left == NULL && r->right == NULL){
            return NULL;
        }
        else if(r->left == NULL){
            TreeNode *temp = r->right;
            free(r);
            return temp;
        }
        else if(r->right == NULL){
            TreeNode *temp = r->left;
            free(r);
            return temp;
        }
        else if(r->left != NULL && r->right != NULL){
            TreeNode *temp = min(r->right);
            r->JourneyCode = temp->JourneyCode;
            r->price = temp->price;
            r->right = del(r->right, temp->price);
        }
    }
    return r;
}



bool BST :: remove(int JourneyCode, int price){
    if( !(find(JourneyCode,price)) ){
        return false;
    }
    else{
        root = del(root,price);
    }
    return true;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line
void BST :: preorder(TreeNode *n){
    if(n == NULL){
        return ;
    }
    else{
        cout << n->JourneyCode << endl;
        preorder(n->left);
        preorder(n->right);
    }
}

void BST :: postorder(TreeNode *n){
    if(n == NULL){
        return ;
    }
    else{
        postorder(n->left);
        postorder(n->right);
        cout << n->JourneyCode << endl;
    }
}

void BST :: inorder(TreeNode *n){
    if(n == NULL){
        return ;
    }
    else{
        inorder(n->left);
        cout << n->JourneyCode << endl;
        inorder(n->right);
    }
}

void BST :: traverse(int typeOfTraversal){
    TreeNode *t = root;
    if(typeOfTraversal == PRE_ORDER){
        preorder(t);
    }
    if(typeOfTraversal == POST_ORDER){
        postorder(t);
    }
    if(typeOfTraversal == IN_ORDER){
        inorder(t);
    }
}

// Returns the price of the cheapest journey
int BST :: getMinimum(){
    TreeNode *m = root;
    while(m->left != NULL){
        m = m->left;
    }
    return m->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST :: count(TreeNode *a, int lowerPriceBound, int upperPriceBound){
    int c = 0;
    if(a->price >= lowerPriceBound && a->price <= upperPriceBound){
        c++;
    }
    c = c + count(a->left, lowerPriceBound, upperPriceBound);
    c = c + count(a->right, lowerPriceBound, upperPriceBound);
    return c;
}

int BST :: countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound){
    TreeNode *r = root;
    if(getMinimum()>upperPriceBound){
        return 0;
    }
    return count(r, lowerPriceBound, upperPriceBound);
}

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
