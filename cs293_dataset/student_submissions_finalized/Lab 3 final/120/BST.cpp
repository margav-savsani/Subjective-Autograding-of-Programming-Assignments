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
BST::BST(TreeNode *root1){
    root=root1;
 }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price){

    TreeNode *node;
    TreeNode *insert=new TreeNode(JourneyCode,price);
    if(root==nullptr){
        root=insert;
        return true;
    }
    else if(find(JourneyCode,price)){
        return false;
    }
    else{
        node=find2(JourneyCode,price);
        if(node->price > price && node->left==nullptr){
            node->left=insert;
            insert->parent=node;
            return true;
        }
        
        else if(node->price <price && node->right==nullptr){
            node->right=insert;
            insert->parent=node;
            return true;
        }

    }

}

// Return True, if the ticket with given attributes is found, false otherwise
TreeNode *BST::find2(int JourneyCode, int price) { //assumption
    TreeNode *node;
    node=root;
    if(node==nullptr){
        return nullptr;
    }
    while(true){
        if(node->price==price){
            if(node->JourneyCode==JourneyCode){
                return node;}
            else{
                node=node->right;
            }
        }
        else if(node->price<price){
            if(node->right==nullptr){
                return node;
            }
            node=node->right;
        }
        else if(node->price>price){
            if(node->left==nullptr){
                return node;
            }
            node=node->left;
        }
        }
 }
 
 bool BST::find(int JourneyCode, int price) { 
    TreeNode *node;
    node=root;
    if(root==nullptr){
        return false;
    }
    while(true){
        if(node->price==price){
            if(node->JourneyCode==JourneyCode){
                return true;}
            else{
                node=node->right;
            }
        }
        else if(node->price<price){
            if(node->right==nullptr){
                return false;
            }
            node=node->right;
        }
        else if(node->price>price){
            if(node->left==nullptr){
                return false;
            }
            node=node->left;
        }
        }
 }	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    TreeNode *n=root;
    if(find2(JourneyCode,price)==nullptr && find(JourneyCode,price)==true){
        if(n->left==nullptr&&n->right!=nullptr){
            root=n->right;
            root->parent=nullptr;
            return true;
        }
        if(n->left!=nullptr&&n->right==nullptr){
            root=n->left;
            root->parent=nullptr;
            return true;
        }   
    }
    else if(find(JourneyCode,price)==false){
        return false;
    }

    TreeNode *node=find2(JourneyCode,price);
    if(node->left==nullptr && node->right==nullptr){
        if(node->parent==nullptr){
            root=nullptr;
            return true;
        }
        else if(node->parent->price > node->price){
            node->parent->left=nullptr;
            return true;
        }
        else{
            node->parent->right=nullptr;
            return true;
        }
    }
    else if((node->left==nullptr&&node->right!=nullptr)||(node->left!=nullptr&&node->right==nullptr)){
        if(node->parent==nullptr&& node->left==nullptr){
            root=node->right;
            return true;
        }
        else if(node->parent==nullptr&&node->right==nullptr){
            root=node->left;
            return true;
        }
        else if(node->left==nullptr){
            node->right->parent=node->parent;
            node->parent->right=node->right;
            return true;
        }
        else{
            node->left->parent=node->parent;
            node->parent->left=node->left;
            return true;
        }
    }
}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
if(typeOfTraversal==0){ //pre
pre_traverse(root);

}
if(typeOfTraversal==1){ //post
post_traverse(root);
}
if(typeOfTraversal==2){ //in
in_traverse(root);
}
}
void BST::pre_traverse(TreeNode*r){
if(r==NULL) return;
if(r!=NULL) cout<<r->price<<" "<<endl;
pre_traverse(r->left);
pre_traverse(r->right);
 
}
void BST::post_traverse(TreeNode*r){
if(r==NULL) return;
post_traverse(r->left);
post_traverse(r->right);
if(r!=NULL) cout<<r->price<<" "<<endl;
 
}
void BST::in_traverse(TreeNode*r){
if(r==NULL) return;
in_traverse(r->left);
if(r!=NULL) cout<<r->price<<" "<<endl;
in_traverse(r->right);
 
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode *node;
    node=root;
    if(root==nullptr){
        return -1;
    }
    else{
        while(node->left!=nullptr){
            node=node->left;
        }
        return node->price;
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


// ********************
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