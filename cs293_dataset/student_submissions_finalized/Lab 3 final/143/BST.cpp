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
    root= new TreeNode();
   
    
}
BST::BST(TreeNode *root){
    root = new TreeNode(root->JourneyCode,root->price);
    root = this->root; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    TreeNode *x;
    x = this->root;
    if(x->price==0){
        x = new TreeNode(JourneyCode,price);
        root=x;
        return true;
    }
    else{
    while(true){
    if(x->price>=price){
        if(x->left==nullptr){
            x->left = new TreeNode(JourneyCode,price,nullptr,nullptr,x);
            return true;
        }
        else{
            x = x->left;
        }
    }   
    if(x->price<price){
        if(x->right==nullptr){
            x->right= new TreeNode(JourneyCode,price,nullptr,nullptr,x);
            return true;
        }
        else{
            x = x->right;
        }
    }   
    }
    }
    return false;}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    TreeNode *x;
    x = this->root;
    while(true){
        if(x==nullptr){
            break;
        }
        if(x->JourneyCode==JourneyCode && x->price == price){
            return true;
        }
        else if(x->price>=price){
            x = x->left;
        }
        else if(x->price<price){
            x= x->right;
        }
    }
return false; }
TreeNode* BST::successor(TreeNode *ele){
    if(ele->right!=nullptr){
        ele = ele->right;
        while(true){
            if(ele->left==nullptr){
                return ele;
            }  
            else{
                ele = ele->left;
            }
        }
    }
    TreeNode *y;
    y = ele->parent;
    while(y!=nullptr && y->right==ele){
        ele = y;
        if(y!=root){
        y = y->parent;
        }
        else{
            y=nullptr;
        }
    }
    return y;
}
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    TreeNode *x;
    x = root;
    while(true){
        if(x==nullptr){
            return false;
        }
        if(x->JourneyCode==JourneyCode && x->price == price){
            break;
        }
        else if(x->price>=price){
            x = x->left;
        }
        else if(x->price<price){
            x = x->right;
        }
    }
    
    if(x==root && x->left==nullptr && x->right==nullptr){
        root=new TreeNode();
    }
    else{
        TreeNode *y;
        if(x==root){
            if(x->left==nullptr){
                root=x->right;
            }
            else if(x->right==nullptr){
                root=x->left;
            }
            else{
                x->left->parent=x->right;
                root=x->right;
                root->left=x->left;
            }

        }
        if(x->left==nullptr || x->right==nullptr){
            y = x;
        }
        else{
            y = successor(x);
        }
        if(y->left!=nullptr){
            x = y->left;
        }
        else{
            x = y->right;
        }
        if(x!=nullptr){
            x->parent=y->parent;
        }
        if(y->parent == nullptr){
            root = x;
        }
        else if(y==y->parent->left){
            y->parent->left = x;
        }
        else if(y==y->parent->right){
            y->parent->right=x;
        }
        if(y!=x){
            x=y;
        }
    }    
    
   
    return true; }
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line
void BST::preorder(TreeNode *Root){
    if(Root==nullptr){
        return;
    }
    else{
        cout<<Root->JourneyCode<<endl;
        preorder(Root->left);
        preorder(Root->right);
    }
}
void BST::postorder(TreeNode *Root){
    if(Root==nullptr){
        return;
    }
    else{
        postorder(Root->left);
        postorder(Root->right);
        cout<<Root->JourneyCode<<endl;
    }
}
void BST::inorder(TreeNode *Root){
    if(Root==nullptr){
        return;
    }
    else{
        inorder(Root->left);
        cout<<Root->JourneyCode<<endl;
        inorder(Root->right);
    }
}
void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal==0){
        preorder(root);
    }
    if(typeOfTraversal==1){
        postorder(root);
    }
    if(typeOfTraversal==2){
        inorder(root);
    }
return; }

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode *x;
    x = this->root;
    while(true){
        if(x->left==nullptr){
            return x->price;
        }
        else{
            x = x->left;
        }
    } }

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    int count = 0 ;
    TreeNode *x;
    x = root;
    while(true){
        if(x->price>lowerPriceBound && x->left!=nullptr){
            x = x->left;
        }
        else{
            break;
        }
    }
    while(true){
        if(x!=nullptr){
        if(x->price>upperPriceBound){
            break;
        }
        else if(x->price==upperPriceBound){
            count++;
            break;
        }
        else if(x->price<upperPriceBound && x->price>=lowerPriceBound ){
            count++;
        }
        }
        else{
            break;
        }
        x = successor(x);
    }

return count; }

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
        cout << root->JourneyCode<< endl;
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
