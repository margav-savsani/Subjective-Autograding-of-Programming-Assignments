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
bool BST::insert(int JourneyCode, int price) {
    bool b = find(JourneyCode,price);
    if(b){
        return false;
    }
    else{
        TreeNode *x = root;
        TreeNode *y = nullptr;
        while (x!=nullptr){
            cout << x->price << y << endl;
            y = x;
            if (price < x->price){
                x = x->left;
            }
            else if (price > x->price){
                x = x->right;
            }
            else{
                break;
            }
        }
        if (y==nullptr){
            TreeNode temp(JourneyCode, price); 
        }
        else{
            if ( price < y->price ){
                *(y->left) = TreeNode(JourneyCode, price); 
                y->left->parent = y;
            }
            else if( price > y->price ){
                *(y->right) = TreeNode(JourneyCode, price); 
                y->right->parent = y;
            }
            else{
                if(x!=nullptr){
                    TreeNode temp(JourneyCode, price, nullptr, x->right, x);
                    *((x->right)->parent)=temp;
                    *(x->right) = temp;
                }
                else{
                    TreeNode temp(JourneyCode, price, nullptr, nullptr, nullptr);
                    *x = temp;
                }
            }
        }
        return true;
    }

}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    TreeNode *x = root;
    while(1){
        if ( x == nullptr ){
            return false;
        }
        if (  price < x->price ){
            x = x->left;
        }
        else if (price > x->price){
            x = x->right;
        }
        else if (price == x->price && JourneyCode==x->JourneyCode){
            return true;
        }
        else {
            BST L(x->left);
            BST R(x->right);

            return (L.find(JourneyCode, price)) || (R.find (JourneyCode, price));
        }
    }

}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
    bool b = find(JourneyCode, price);
    if (b){
        TreeNode *y = nullptr;
        TreeNode *x = root;
        while (x!=nullptr){
            y = x;
            if (price < x->price){
                x = x->left;
            }
            else if (price > x->price){
                x = x->right;
            }
            else if (price==x->price && JourneyCode==x->JourneyCode){
                y = x->parent;
                break;
            }
            else{
                while(price=x->price && JourneyCode!=x->JourneyCode){
                    x = x->right;
                    y = x;
                }
                y = x->parent;
                break;
            }
        }
        if ( x->left == nullptr && x->right == nullptr ){
            if( y->right == x ){
                y->right == nullptr;
            }
            if(y->left == x) {
                y->left == nullptr;
            }
        }

        else if ( (x->left==nullptr) && (x->right!=nullptr) ){
            if(y->left==x){
                y->left = x->right;
                (x->right)->parent = y;
            }
            if(y->right==x){
                y->right = x->right;
                (x->right)->parent = y;
            }

        }

        else if ( (x->right==nullptr) && (x->left!=nullptr) ){
            if(y->right==x){
                y->right = x->left;
                (x->left)->parent = y;
            }
            if(y->left==x){
                y->left = x->left;
                (x->left)->parent = y;
            }

        }

        else{
            //
        }
        
        return true;

    }
    else{
        return false;
    }
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal==0){
        //preorder
        BST S(root);
        traverse_pre(S);
    }
    if(typeOfTraversal==1){
        //postorder
        BST S(root);
        traverse_post(S);
    }
    if(typeOfTraversal==2){
        //interorder
        BST S(root);
        traverse_int(S);  
    }
}

void BST::traverse_pre(BST S){
    if (S.root==nullptr){
        return;
    }
    cout << S.root->JourneyCode;
    BST S1(S.root->left);
    BST S2(S.root->right);
    traverse_pre(S1);
    traverse_pre(S2);
}

void BST::traverse_post(BST S){
    if (S.root==nullptr){
        return;
    }
    BST S1(S.root->left);
    BST S2(S.root->right);
    traverse_post(S1);
    traverse_post(S2);
    cout << S.root->JourneyCode;
}

void BST::traverse_int(BST S){
    if (S.root==nullptr){
        return;
    }
    BST S1(S.root->left);
    BST S2(S.root->right);
    traverse_int(S1);
    cout << S.root->JourneyCode;
    traverse_int(S2);
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode *x = root;
    TreeNode *y = nullptr;
    while ( x!=nullptr ){
        y = x;
        x = x->left;
    }
    return y->price;
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





