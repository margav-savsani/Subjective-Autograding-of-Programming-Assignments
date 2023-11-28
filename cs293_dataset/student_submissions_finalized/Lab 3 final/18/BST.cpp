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
    root=nullptr;
}
BST::BST(TreeNode *root){ 
    this->root = root;
}


struct TreeNode* BST::search(int JourneyCode, int price){
    /*TreeNode *x=root;
    if(x==nullptr) return nullptr;
    if(x->price==price) return x;
    if(x->price>price){
        x=x->left;
        BST A(x);
        return A.search(JourneyCode,price);
    }
    else{
        x=x->right;
        BST B(x);
        return B.search(JourneyCode,price);
    }*/
    //if(root==nullptr) return nullptr;
    //TreeNode x(root->JourneyCode, root->price, root->left, root->right, root->parent);
    TreeNode *y = root;
    while(y!=nullptr){
        if(price==y->price) break;
        if(price<y->price) {
            y=y->left;
        }
        else y=y->right;
    }
    return y;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    /*TreeNode *y = root;
    while(y!=nullptr){
        if(price==y->price) break;
        if(price<y->price) y=y->left;
        else y=y->right;
    }
    if(y==nullptr) return false;
    return true;*/
    if(search(JourneyCode,price)!=nullptr) return true;
    return false;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
	if(root!=nullptr) {
    if(find(JourneyCode, price)) return false;
    TreeNode *z= new TreeNode(JourneyCode, price);
    TreeNode *x,*y;
    y = nullptr;
    x = root;
    while(x!=nullptr){
        y=x;
        if(x->price>z->price) x=x->left;
        else x=x->right;
    }
    z->parent=y;
    if(y==nullptr) root=z;
    else if(z->price<y->price) y->left = z;
    else y->right = z;
    return true;
    }
    TreeNode *x = new TreeNode(JourneyCode,price);
    root=x;
    return true;
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode *x=root;

    while(x->left != nullptr){
        x = x->left;
    }
    return x->price;
}

struct TreeNode* BST::successor(int JourneyCode, int price){
    TreeNode *x =new TreeNode;
    //TreeNode *result =new TreeNode;
    x=search(JourneyCode, price);
    if(x==nullptr) return x;
    if(x->right!=nullptr){
        TreeNode *y=root->right;
        while(y->left != nullptr){
            y = y->left;
        }
        return y;
    }
    TreeNode *parent=x->parent;
    while((parent!=nullptr)&&(x==parent->right)){
        x=parent;
        parent=parent->parent;
    }
    return parent;
    /*if(x->right!=nullptr){
        x=x->right;
        BST A(x);
        result->price=A.getMinimum();
        return result;
    }
    TreeNode *parent=x->parent;
    while((parent!=nullptr)&&(x==parent->right)){
        x=parent;
        parent=parent->parent;
    }
    return parent;*/
    
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    if(!find(JourneyCode, price)) return false;
    TreeNode *x=search(JourneyCode,price);
    if((x->left==nullptr)&&(x->right==nullptr)){
        x->parent->left=nullptr;
        x->parent->right=nullptr;
    }
    else if((x->left==nullptr)&&(x->right!=nullptr)){
        x->right->parent = x->parent;
        x->parent->right=x->right;

    }
    else if((x->left!=nullptr)&&(x->right==nullptr)){
        x->left->parent = x->parent;
        x->parent->left=x->left;
    }
    else if((x->left!=nullptr)&&(x->right!=nullptr)){
        TreeNode *succ=successor(JourneyCode, price);
        remove(succ->JourneyCode,succ->price);
        x=succ;
    }
    return true;

}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal==PRE_ORDER){ //preorder
        TreeNode *x=new TreeNode;
        x=root;
        if(x==nullptr) return;
        cout<<x->JourneyCode<<" ";
        TreeNode *y=x->left;
        BST A(y);
        A.traverse(PRE_ORDER);
        TreeNode *z=x->right;
        BST B(z);
        B.traverse(PRE_ORDER);
    }
    if(typeOfTraversal==(IN_ORDER)){ //inorder
        TreeNode *x=root;
        if(x==nullptr) return;
        TreeNode *y=x->left;
        BST A(y);
        A.traverse(IN_ORDER);
        TreeNode *z=x->right;
        BST B(z);
        B.traverse(IN_ORDER);
        cout<<x->JourneyCode<<" ";
    }
    if(typeOfTraversal==(POST_ORDER)){ //postorder
        TreeNode *x=root;
        if(x==nullptr) return;
        TreeNode *y=x->left;
        BST A(y);
        A.traverse(POST_ORDER);
        cout<<x->JourneyCode<<" ";
        TreeNode *z=x->right;
        BST B(z);
        B.traverse(POST_ORDER);
    }
}


// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    int count=0;
    TreeNode *x=search(0,lowerPriceBound); //since no use of Journey Code in search function
    if(x!=nullptr){
        if(x->parent->right==x){
            while(x->price<=upperPriceBound && x!=nullptr){
                count++;
                x=x->right;
            }
            return count;
        }
        else{
            while(x->price<=upperPriceBound){
                count++;
                x=x->right;
            }
            TreeNode *y=search(0,lowerPriceBound);
            TreeNode *z=y->parent;
            int new_lowerBound = z->price;
            int extra = countJourneysInPriceBound(new_lowerBound,upperPriceBound);
            return count+extra;
        }
    }
    return countJourneysInPriceBound((lowerPriceBound+1),upperPriceBound);
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
        root = root->right;
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
        root = root->right;
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

