#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4


// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST(){
    root = NULL;    //initializing root to null as no elements yet
}
BST::BST(TreeNode *root){   
    this->root = root;      //updating root based on given parameter
    root->parent = NULL;    //and also for root the parent is null
}

bool BST::isRoot(TreeNode *x){
    if (x==root) return true;       //returning true if x is same as the root
    return false;                   //else false
}

TreeNode* BST::prev(TreeNode *current){
    TreeNode *result_pre=NULL;              //to keep track of parent of whatever node we are currently looking
    TreeNode *result = current->left;       //this is the number that we are currently checking initialized to left node 
    while (result != NULL){                 //if the currently checked element is null then return the last element i.e. the parent i.e result_pre
        result_pre = result;        //if not null then we go further down the tree on the right side till right pointer is null
        result = result->right;
    }
    return result_pre;
}

TreeNode *BST::give(TreeNode *root, int JourneyCode, int price){    //returns the node based on given input values
    
    //root null means no tree and hence no element, returning NULL
    if (root == NULL){      
        return NULL;
    }

    //if price matches then 
    if (root->price == price){
        if (root->JourneyCode == JourneyCode){
            return root;
        }
        else{
            if (root->left == NULL){
                //cout << "returning the root 2" << endl;
                return root;
            }
            return BST::give(root->left, JourneyCode, price);
        }
    }
    else if (root->price < price){
        if (root->right == NULL){
            //cout << "returning the root 3" << endl;
            return root;
        }
        return BST::give(root->right, JourneyCode, price);
    }
    else {
        if (root->left == NULL){
            //cout << "returning the root 4" << endl;
            return root;
        }
        return BST::give(root->left, JourneyCode, price);
    }
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    TreeNode *new_node = new TreeNode(JourneyCode,price);
    TreeNode *insert_here = BST::give(this->root, JourneyCode,price);
    if (insert_here==NULL){
        root = new_node;
        root->parent=NULL;
        //cout << "this point was reached" << endl;
        //cout << "new root created" << endl;
        return true;
    }

    if (insert_here->JourneyCode == JourneyCode) return false;
    else {
        if (price <= insert_here->price){
            insert_here->left = new_node;
            new_node->parent = insert_here;
            //cout << "inserted to left" <<endl;
            return true;
        }
        else {
            insert_here->right = new_node;
            new_node->parent = insert_here;
            //cout << "inserted to right" <<endl;
            return true;
        }
    }

    return false;
}



// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    if (BST::give(root, JourneyCode, price)->JourneyCode == JourneyCode 
        &&
        BST::give(root, JourneyCode, price)->price == price 
        )
    {
        return true;
    }
    return false; 
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    TreeNode *node=BST::give(this->root, JourneyCode, price);
    if (node == NULL){
        return false;
    }
    if (node->JourneyCode == JourneyCode 
        &&
        node->price == price 
        )
    {
        if (node->parent == NULL && node->left == NULL && node->right == NULL){

            this->root = NULL;
            delete node;
            return true;
        }
        else if (node->parent == NULL && node->left == NULL){

            node->right->parent = NULL;
            this->root = node->right;
            delete node;
            return true;
        }
        else if (node->parent == NULL && node->left != NULL){
            TreeNode *previous = BST::prev(node);
            //cout << "This point was reached" << endl;
            int jrny = previous->JourneyCode;
            int pr = previous->price;
            //cout << jrny << " " << pr << endl;
            BST::remove(jrny, pr);
            //cout << "This point was reached 2" <<endl;
            node->JourneyCode = jrny;
            node->price = pr;

            return true;

        }
        
        else if (node->left == NULL && node->right == NULL ){
            if (node->parent->left == node){
                //cout << "this point was reached 3" << endl;
                node->parent->left = NULL;
                delete node;
            }
            else {
                
                node->parent->right = NULL;
                delete node;
            }
            return true;
        }
        else if (node->left == NULL && node->right != NULL){
            if (node->parent->left == node){
                node->parent->left = node->right;
                node->right->parent = node->parent;
                delete node;
                return true;
            }
            else {
                node->parent->right = node->right;
                node->right->parent = node->parent;
                delete node;
                return true;
            }
        }
        else if (node->left != NULL){
            TreeNode *previous = BST::prev(node);
            int jrny = previous->JourneyCode;
            int pr = previous->price;

            BST::remove(jrny, pr);

            node->JourneyCode = jrny;
            node->price = pr;
            return true;

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
    TreeNode *current = this->root;
    if (root == NULL){
        return;
    }

    if (typeOfTraversal == 0){
        cout << root->JourneyCode << endl;
        TreeNode *current = this->root;
        this->root = current->left;
        traverse(0);
        this->root = current->right;
        traverse(0);
        this->root = current;
        //cout<<"this poimt was reached" << endl;
        return;
    }
    else if (typeOfTraversal == 2){

        TreeNode *current = this->root;
        this->root = current->left;
        traverse(2);
        cout << current->JourneyCode << endl;
        this->root = current->right;
        traverse(2);
        this->root = current;
        //cout<<"this poimt was reached" << endl;
        return;
    }
    else if (typeOfTraversal == 1){
        
        TreeNode *current = this->root;
        this->root = current->left;
        traverse(1);
        this->root = current->right;
        traverse(1);
        this->root = current;
        cout << root->JourneyCode << endl;
        //cout<<"this poimt was reached" << endl;
        return;
    }

}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode *current_pre = NULL;
    TreeNode *current = this->root;
    while (current!= NULL){
        current_pre = current;
        current = current->left;
    }
    return current_pre->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    if (this->root == NULL) {
        return 0;
    }
    else if (this->root->price < lowerPriceBound){
        TreeNode *curr = this->root;
        this->root = curr->right;
        int result = countJourneysInPriceBound(lowerPriceBound,upperPriceBound);
        this->root = curr;
        return result;
    }
    else if (this->root->price > upperPriceBound){
        TreeNode *curr = this->root;
        this->root = curr->left;
        int result = countJourneysInPriceBound(lowerPriceBound,upperPriceBound);
        this->root = curr;
        return result;
    }
    else {
        TreeNode *curr = this->root;
        int result = 1;
        this->root = curr->left;
        result += countJourneysInPriceBound(lowerPriceBound,upperPriceBound);
        this->root = curr->right;
        result += countJourneysInPriceBound(lowerPriceBound,upperPriceBound);
        this->root = curr;
        return result;
    }
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) { 
    ofstream o;
    o.open(filename, ios_base::app);

    if (this->root == NULL){
        o << -1 << " " << -1 << endl;
        return;
    }
    
    o << this->root->JourneyCode << " " << this->root->price << endl;
    TreeNode *current = this->root;
    this->root = current->left;
    customStore(filename);
    this->root = current->right;
    customStore(filename);
    this->root = current;
    //cout<<"this poimt was reached" << endl;
    return;
    
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
    ifstream i;
    i.open(filename);
    int jrny, pr;
    int tag=0;
    int max=INT_MAX;
    stack<TreeNode *> Stack;
    vector<TreeNode *> sk;
    
    while (!i.eof()){
        i >> jrny >> pr;
        if (pr > max) break;

        if (this->root == NULL && pr != -1){
            if (flag == LOAD_FULL_BST){
                insert(jrny, pr);
                //Stack.push(this->root);
                sk.push_back(this->root);
            }
            else {
                i >> jrny >> pr;
                if (pr == -1) return;
                insert(jrny,pr);
                //Stack.push(this->root);
                sk.push_back(this->root);
                max = pr;
            }
            continue;
        }

        if (pr == -1){
            if (tag == 0){
                tag = 1;
            }
            else {
                //Stack.pop();
                sk.pop_back();
            }
        }
        else if (tag == 0){
            TreeNode *t = new TreeNode(jrny, pr);
            //Stack.top()->left = t;
            sk[sk.size()-1]->left = t; 
            //t->parent = Stack.top();
            t->parent = sk[sk.size()-1];
            //Stack.push(t);
            sk.push_back(t);
        }
        else if (tag == 1){
            TreeNode *t = new TreeNode(jrny, pr);
            //Stack.top()->right = t;
            sk[sk.size()-1]->right = t;
            //t->parent = Stack.top();
            t->parent = sk[sk.size()-1];
            //Stack.pop();
            sk.pop_back();
            //Stack.push(t);
            sk.push_back(t);
            tag = 0;
        }
    }
    return;
    
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

