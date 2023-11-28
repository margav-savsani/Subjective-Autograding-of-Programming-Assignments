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
    TreeNode();
}
BST::BST(TreeNode *root){
    this->root = root;
}


bool BST::insert(int JourneyCode, int price) { 
    if(root->price >= price){
        if(root->JourneyCode = JourneyCode){
            return false;
        }
        if(root->left==nullptr){
            TreeNode(JourneyCode,price,nullptr,nullptr,root);
        }
        else{
            BST(root->left);
            insert(JourneyCode,price);
        }
    }
    else if(root->price < price){
        if(root->JourneyCode = JourneyCode){
            return false;
        }
        if(root->right==nullptr){
            TreeNode(JourneyCode,price,nullptr,nullptr,root);
        }
        else{
            BST(root->right);
            insert(JourneyCode,price);
        }   
    }
return true;
}


bool BST::find(int JourneyCode, int price) { 
    if(root->JourneyCode==JourneyCode && root->price==price){
        return true;
    }
    else if(root->price >=price){
        BST(root->left);
        find(JourneyCode,price);
    }
    else{
        BST(root->right);
        find(JourneyCode,price);
    }
return false; 
}
TreeNode* BST::successor(int JourneyCode,int price){
    if(root->JourneyCode==JourneyCode && root->price==price){
        if(root->right!=nullptr){
            BST(root->right);
            while(root->left==nullptr){
                BST(root->left);
            }
            return root;
        }
        TreeNode *y;
        y = root->parent;
        if(root->right==nullptr){
            while(y!-nullptr && root = y->right){
                x = y;
                y = root->parent;

            }
        }
    }
    else if(root->price >=price){
        BST(root->left);
        find(JourneyCode,price);
    }
    else{
        BST(root->right);
        find(JourneyCode,price);
    }    
}

bool BST::remove(int JourneyCode, int price) { 

}
void BST::preorder(TreeNode *root){
    if(root == nullptr){
        return;
    }
    else{
        cout<<root->JourneyCode<<endl;
        preorder(root->left);
        preorder(root->right);
    }
}
void BST::postorder(TreeNode *root){
    if(root == nullptr){
        return;
    }
    else{
        postorder(root->left);
        postorder(root->right);
        cout<<root->JourneyCode<<endl;
    }
}
void BST::inorder(TreeNode *root){
    if(root == nullptr){
        return;
    }
    else{
        inorder(root->left);
        cout<<root->JourneyCode<<endl;
        inorder(root->right);
    }
}

void BST::traverse(int typeOfTraversal){
    if(typeOfTraversal==0){
        preorder(root);
    }
    if(typeOfTraversal==1){
        postorder(root);
    }
    if(typeOfTraversal==2){
        inorder(root);
    }
}


int BST::getMinimum() {
    if(root->left==nullptr){
        return root->price;
    }
    else{
        BST(root->left);
    }
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







