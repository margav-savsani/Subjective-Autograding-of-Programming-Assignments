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
    root = new TreeNode();
    root->parent = nullptr; }
BST::BST(TreeNode *root){this->root = root;}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    TreeNode* y = nullptr;
    TreeNode* x = root;
    while (x!=nullptr){
        y = x;
        if (JourneyCode == x->JourneyCode && price == x->price) return false;
        else if(price < x->price) x = x->left;
        else x = x->right;
    }
    TreeNode *z = new TreeNode(JourneyCode,price,nullptr,nullptr,y);
    if (y == nullptr) root = z;
    else if (z->price < y->price) y->left = z;
    else y->right = z;
    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    TreeNode* x = root;
    while (x != nullptr && (x->price!=price || x->JourneyCode != JourneyCode)){
        if (price < x->price)
            x = x->left;
        else{
            x = x->right;
        }
    }
    if (x == nullptr)
        return false;
    else
        return true;
    }
TreeNode* BST::search(int JourneyCode,int price){
    TreeNode* x = root;
    while (x != nullptr && (x->price!=price || x->JourneyCode != JourneyCode)){
        if (price < x->price)
            x = x->left;
        else{
            x = x->right;
        }
    }
    return x;
}

TreeNode* BST::treenode_min(TreeNode *x){
    while(x->left != nullptr){
        x = x->left;
    }
    return x;
}

TreeNode* BST::successor(TreeNode* x){
    if (x->right != nullptr)
        return treenode_min(x->right);
    TreeNode* y = x->parent;    
    while (y != nullptr && x==y->right){
        x = y;
        y = x->parent;
    }
    return y;
} 
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    TreeNode* z = search(JourneyCode,price);
    if(z == nullptr){
        return false;
    }
    if(z == root){
        if(z->left == nullptr && z->right == nullptr){
            root = nullptr;
            return true;
        }
        else if(z->left != nullptr && z->right == nullptr){
            root = z->left;
            return true;
        }
        else if(z->left == nullptr && z->right != nullptr){
            root = z->right;
            return true;
        }
    }
    if(z->left == nullptr && z->right == nullptr){
        TreeNode *y = z->parent;
        if(y->left == z){
            y->left = nullptr;
        }
        else y->right = nullptr;
        return true;
    }
    else if(z->left == nullptr){
        TreeNode*y = z->parent;
        if(y->left == z){
            TreeNode*x = z->right;
            x->parent = y;
            y->left = x;
        }
        else{
            TreeNode*x = z->right;
            x->parent = y;
            y->right = x;
        }
        return true;
    }
    else if(z->right == nullptr){
        TreeNode*y = z->parent;
        if(y->left == z){
            TreeNode*x = z->left;
            x->parent = y;
            y->left = x;
        }
        else{
            TreeNode*x = z->left;
            x->parent = y;
            y->right = x;
        }
        return true;
    }
    else{
        TreeNode*y = successor(z);
        remove(y->JourneyCode,y->price);
        z->JourneyCode=y->JourneyCode;
        z->price=y->price;
        return true;
    }

 }
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal == 0){
        if (root == nullptr) return;
        else {
        cout<< root->JourneyCode<<endl;
        BST *x = new BST(root->left);
        BST *y = new BST(root->right);
        x->traverse(0);
        y->traverse(0);
        return;
        }
    }
    else if(typeOfTraversal == 1){
        if (root == nullptr) return;
        else {
        BST *x = new BST(root->left);
        BST *y = new BST(root->right);
        x->traverse(1);
        y->traverse(1);
        cout<< root->JourneyCode<<endl;
        return;
        }
    }
    else if(typeOfTraversal == 2){
        if (root == nullptr) return;
        else{
            BST *x = new BST(root->left);
            BST *y = new BST(root->right);
            x->traverse(2);
            cout<< root->JourneyCode<<endl;
            y->traverse(2);
            return;
        }
    }
 }

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode* x = root;
    if (x == nullptr){
        return 0;
    }
    while (x->left != nullptr){
        x = x->left;
    }
    return x->price;
 }

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    int count = 0;
    TreeNode* x = root;
    TreeNode* y = root;
    while (x != nullptr && (x->price!=lowerPriceBound)){
        if (lowerPriceBound < x->price){
            y = x;
            x = x->left;
        }
        else {
            y = x;
            x = x->right;
        }
    }
    if(x!=nullptr){
 
        count++;
  
        while(successor(x) != nullptr && successor(x)->price<=upperPriceBound){
            count++;
            cout << count << endl;
            x = successor(x);
        }
        return count;
    }
    else{
        if(y->price <= upperPriceBound) count++;
        while(successor(y) != nullptr && successor(y)->price<=upperPriceBound){
            count++;
            y = successor(y);
        }
        return count;
    }
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.

void BST::store(TreeNode* TN, ofstream &textfile){
     if(TN == nullptr) return;
     textfile << TN->price << endl;
     textfile << TN->JourneyCode << endl;
     textfile << -2 << endl;
     store(TN->left, textfile);
     textfile << -1 << endl;
     store(TN->right, textfile);
}

void BST::customStore(string filename) { 
    ofstream outfile;
    outfile.open(filename);
    store(root, outfile);
    outfile.close();
    return;
    // ofstream outfile;
    // outfile.open(filename);
    // if (root == NULL)
    //     return;

    // // Create an empty stack and push root to it
    // stack<TreeNode *> nodeStack;
    // nodeStack.push(root);

    /* Pop all items one by one. Do following for every popped item
       a) print it
       b) push its right child
       c) push its left child
    Note that right child is pushed first so that left is processed first */
    // while (nodeStack.empty() == false)
    // {
    //     // Pop the top item from stack and print it
    //     struct TreeNode *node = nodeStack.top();
    //     outfile << node->price << " " << node->JourneyCode << endl;
    //     nodeStack.pop();

    //     // Push right and left children of the popped node to stack
    //     if (node->right)
    //         nodeStack.push(node->right);
    //     if (node->left)
    //         nodeStack.push(node->left);

    //     outfile.close();
    // }
}
	
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
 
void BST::customLoad (int flag, string filename) { 
    if(flag == LOAD_FULL_BST){
        ifstream infile;
        infile.open(filename);
        int N;
        infile >> N;
        root->price = N;
        TreeNode* currentnode = root;
        while(infile >> N){

            if(N == -2){
                infile >> N;
                if(N != -1){
                    TreeNode *z = new TreeNode();
                    z->price = N;
                    infile >> N;
                    z->JourneyCode = N;
                    currentnode->left = z;
                    z->parent = currentnode;
                    currentnode = z;
                }
            }
            else if (N == -1){
                currentnode = currentnode->parent;
            }
            else{
                TreeNode *z = new TreeNode();
                z->price = N;
                infile >> N;
                z->JourneyCode = N;
                currentnode->right = z;
                z->parent = currentnode;
                currentnode = z;
            }
        }
    }
    if (flag == LOAD_LEFT_SUBTREE){
        ifstream infile;
        infile.open(filename);
        int N;
        int count = 0;
        infile >> N;
        root->price = N;
        TreeNode* currentnode = root;
        while(infile >> N){

            if(N == -2){
                count ++;
                infile >> N;
                if(N != -1){
                    TreeNode *z = new TreeNode();
                    z->price = N;
                    infile >> N;
                    z->JourneyCode = N;
                    currentnode->left = z;
                    z->parent = currentnode;
                    currentnode = z;
                }
            }
            else if (N == -1){
                count --;
                currentnode = currentnode->parent;
            }
            else{
                if (count == 0) return ;
                TreeNode *z = new TreeNode();
                z->price = N;
                infile >> N;
                z->JourneyCode = N;
                currentnode->right = z;
                z->parent = currentnode;
                currentnode = z;
            }
        }
    }

 }


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
        result.push_back(to_string(root->JourneyCode) + "\n");
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

