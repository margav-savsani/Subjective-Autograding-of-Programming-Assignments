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

bool added(TreeNode* current, int jc, int pr){
    if((current->price==pr)&&(current->JourneyCode==jc)){
        return false;
    }
    else{
        if((current->price==0)&&(current->JourneyCode==0)){
            current->price=pr;
            current->JourneyCode=jc;
            return true;
        }
        if(current->price <= pr){
            if(current->right==nullptr){
                TreeNode *ri= new TreeNode(jc,pr,nullptr,nullptr,current);
                current->right=ri;
                return true;
            }
            else return added(current->right,jc,pr);
        }
        if(current->price > pr){
            if(current->left==nullptr){
                TreeNode *le= new TreeNode(jc,pr,nullptr,nullptr,current);
                current->left=le;
                return true;
            }
            else return added(current->left,jc,pr);
        }
    }
}

TreeNode* found(TreeNode* cur,int jc, int pr){
    if((cur->JourneyCode==jc)&&(cur->price==pr)) return cur;
    else{
        if(cur->price > pr){
            if(cur->left==nullptr) return NULL;
            else{
                return found(cur->left,jc,pr);
            }
        }
        if(cur->price <= pr){
            if(cur->right==nullptr) return NULL;
            else{
                return found(cur->right,jc,pr);
            }
        }
    }
}

void tra_1(TreeNode *cur){
    if(cur==nullptr) return;
    cout<<cur->JourneyCode<<" ";
    tra_1(cur->left);
    tra_1(cur->right);
}

void tra_2(TreeNode *cur){
    if(cur==nullptr) return;
    tra_2(cur->left);
    tra_2(cur->right);
    cout<<cur->JourneyCode<<" ";  
}

void tra_3(TreeNode *cur){
    if(cur==nullptr) return;
    tra_3(cur->left);
    cout<<cur->JourneyCode<<" ";
    tra_3(cur->right);
}

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST(){ 
    root = new TreeNode; 
    root->parent=nullptr; 
    }
BST::BST(TreeNode *root){this->root=root; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    return added(root,JourneyCode,price);
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    if(found(root,JourneyCode,price)!=NULL) return true;
    else return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    if(!find(JourneyCode,price)) return false;
    else{
        TreeNode *t_r=found(root,JourneyCode,price);
        if((t_r->left==nullptr)&&(t_r->right==nullptr)){
            TreeNode *temp=t_r->parent;
            if(temp==nullptr) this->root=nullptr;
            else{
                if(temp->left==t_r) temp->left=nullptr;
                else temp->right=nullptr;
            }
        }
        else if((t_r->left!=nullptr)&&(t_r->right==nullptr)){
            TreeNode *temp=t_r->parent;
            t_r->left->parent=temp;
            if(temp==nullptr) this->root=t_r->left;
            else{
                if(temp->left==t_r) temp->left=t_r->left;
                else temp->right=t_r->left;
            }
        }
        else if((t_r->left==nullptr)&&(t_r->right!=nullptr)){
            TreeNode *temp=t_r->parent;
            t_r->right->parent=temp;
            if(temp==nullptr) this->root=t_r->right;
            else{
                if(temp->left==t_r) temp->left=t_r->right;
                else temp->right=t_r->right;
            }
        }
        else{
            TreeNode *cur=t_r->left;
            while(cur->right!=nullptr){
                cur=cur->right;
            }
            TreeNode *temp=cur;
            remove(cur->JourneyCode,cur->price);
            TreeNode *temp_parent=t_r->parent;
            temp->right=t_r->right;
            temp->right->parent=temp_parent;
            if(temp_parent==nullptr) this->root=temp;
            else{
                if(temp_parent->left==t_r) temp_parent->left=temp;
                else temp_parent->right=temp;
            }
        }
        return true;
    }
 }
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    TreeNode *cur=root;
    if(typeOfTraversal==PRE_ORDER){
        tra_1(cur);
    }
    if(typeOfTraversal==POST_ORDER){
        tra_2(cur);
    }
    if(typeOfTraversal==IN_ORDER){
        tra_3(cur);
    }
    return; 
    }

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode *cur=root;
    while(cur->left!=nullptr){
        cur=cur->left;
    }
    return cur->price;
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

