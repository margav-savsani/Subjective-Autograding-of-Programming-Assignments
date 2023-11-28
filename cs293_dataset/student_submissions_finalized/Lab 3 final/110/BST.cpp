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
    int key;
    vector<string> result;
    left = NULL;
    right = NULL;
    parent = NULL;
}
BST::BST(TreeNode *root){
    this->root = root;
    int key = root-> price;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

TreeNode* insertelement(TreeNode* node,int key,int JourneyCode){     // defining new function for using recursion
    if(node == NULL){
        TreeNode* n = new TreeNode(JourneyCode,key);
        node = n;
        return node;
    }
    else if(node->price<key){
        node->right = insertelement(node->right,key,JourneyCode);
        node->right->parent= node;
    }
    else{
        node->left = insertelement(node->left,key,JourneyCode);
        node->left->parent = node;
    }
     return node;
}

bool BST::insert(int JourneyCode, int price) { 
    if(find(JourneyCode,price)){
        return false;
    }
    // TreeNode *t;
    // t->JourneyCode = JourneyCode;
    // t->price = price;

    root  = insertelement(root,price,JourneyCode);   
    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise

TreeNode* Search(TreeNode* node,int JourneyCode,int price){
    if(node==NULL) return NULL;
    else if(node->price == price){
        return node;
    }
    else if(node->price < price){
        // cout << node->JourneyCode << endl;
        return Search(node->right,JourneyCode,price);
    }
    else { 
        // cout << node->JourneyCode << endl;

        return Search(node->left,JourneyCode,price);
    }
}

bool BST::find(int JourneyCode, int price) { 
    TreeNode* t =  new TreeNode(JourneyCode,price);
    t = Search(root,JourneyCode,price);

    if(t==NULL) return false;
    return true;
}
	
// Returns false, if JourneyCode isn't present
// deletions the corresponding entry and returns True otherwise

TreeNode* minim(TreeNode* node){
    if(node->left == NULL) return node;
    else return minim(node->left); 
}

TreeNode* Sucessor(TreeNode* node){
    if(node->right != NULL) return minim(node->right);
    else if(node->parent !=NULL  && node->parent->left == node) return node->parent;
    else return NULL;
}

// TreeNode* deletion(TreeNode* root,int price){
//     if(root == NULL) return root;
//     if(price < root->price) root->left = deletion(root->left,price);
//     else if(price > root->price) root->right = deletion(root->right,price);
//     else{
//         if(root->left == NULL && root->right == NULL) return NULL;
//         else if(root->left == NULL) root->right = deletion(root->right,price);
//         else if(root->right == NULL) root->left = deletion(root->left,price);
//     }
//     return root;
// }


bool BST::remove(int JourneyCode, int price) { 
    TreeNode* r = new TreeNode(JourneyCode,price);
    r = Search(root,JourneyCode,price);
    if(r==NULL) return false;
    if(r->left == NULL && r->right == NULL){ 
        if (r != root){
            if (r->parent->left == r){
                r->parent->left = NULL;
            } else {
                r->parent->right = NULL;
            }
            delete r;
        } else {
            root = NULL;   
        }
    }else if(r->left == NULL ){
        TreeNode* x = new TreeNode();
        x = r->right;
        TreeNode* y = new TreeNode();
        
        y = r->parent;
        if(r != root){
            if(y->right == r){
                y->right = x;
                x->parent = y;
            }
            else if(y->left == r){
                y->left = x;
                x->parent = y;
            }
            delete r;
        }
        else {
            root->right->parent = NULL;   
            root = root->right;
        }
    }
    else if(r->right == NULL ){
        TreeNode* x = new TreeNode();
        x = r->left;
        TreeNode* y = new TreeNode();
        y = r->parent;
        if(r != root){
            if(y->right == r){
                y->right = x;
                x->parent = y;
            }
            else if(y->left == r){
                y->left = x;
                x->parent = y;
            }
        }
        else{ 
            root->left->parent = NULL;
            root = root->left;
        }
    }
    else{
       TreeNode* x = new TreeNode();
        x = Sucessor(r);
        r->price = x->price;
        r->JourneyCode = x->JourneyCode;
        if (x->right == NULL && x->left == NULL){
            if (x->parent == r){
                r->right = NULL;
            } else {
                x->parent->left = NULL;
            }
            
            // x->parent->right = NULL;
            // cout << "r's right is null, r's journey code is: " << r->JourneyCode << endl;
        }
        else if (x->right != NULL) {
            if (x->parent != r){
                x->parent->left = x->right;
                x->right->parent = x->parent;
            } else {
                x->parent->right = x->right;
                x->right->parent = x->parent;
            }
        } 
        // else {
            // cout << "checking" << endl;
        // }

        // x->parent = NULL;

        delete x;

    }
    return true;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void pre(TreeNode* root){
    if(root != NULL)
        cout<<root->JourneyCode<<endl;
    if(root->left != NULL)    
        pre(root->left);
    if(root->right != NULL)
        pre(root->right);
}

void post(TreeNode* root){
    if(root->left != NULL) post(root->left);
    if(root->right != NULL) post(root->right);
    if(root != NULL) cout<<root->JourneyCode<<endl;
}

void inorder(TreeNode* root){
    if(root->left != NULL) inorder(root->left);
    if(root != NULL) cout<<root->JourneyCode<<endl;
    if(root->right !=NULL) inorder(root->right);

}

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal == 0) pre(root);
    else if(typeOfTraversal == 1) post(root);
    else if(typeOfTraversal == 2) inorder(root);
    else cout<<"Please enter a valid entry"<<endl;
 }

// Returns the price of the cheapest journey

int BST::getMinimum() {
    TreeNode* mini;
    mini = minim(root);
    return mini->price;
}

TreeNode* max(TreeNode* node){
    if(node->right == NULL) return node;
    else return max(node->right); 
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.

void bndorder(TreeNode* root, int lowerPriceBound, int upperPriceBound, int& num){
    if (root != NULL){

        if(root->left != NULL) bndorder(root->left, lowerPriceBound, upperPriceBound, num);
        if (root->price <= upperPriceBound && root->price >= lowerPriceBound){
                    // cout << root->price << " ";
                num++;
        }
        if(root->right !=NULL) bndorder(root->right, lowerPriceBound, upperPriceBound, num);
    } else {
        return;
    }

}

int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    
    int num = 0;

    bndorder(root, lowerPriceBound, upperPriceBound, num);

    // cout << endl;
    
    return num; 
    
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void storeord(TreeNode* root,string filename){
    if(root->left != NULL) storeord(root->left,filename);
    if(root != NULL){ 
        ofstream outfile;
        outfile.open(filename);
        outfile<<root->JourneyCode<<endl;
        outfile.close();
    }
    if(root->right !=NULL) storeord(root->right,filename);

}
void BST::customStore(string filename) {
    storeord(root,filename); 
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
    if(flag == 3) storeord(root,filename);
    else if(flag == 4) storeord(root->left,filename);
}


// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
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