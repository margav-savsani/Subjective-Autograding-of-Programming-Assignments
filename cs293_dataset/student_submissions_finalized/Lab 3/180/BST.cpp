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
    root = NULL;
}
BST::BST(TreeNode *root){
    this->root = root;
}

bool BST::find_j(int JourneyCode ,int price ){
    TreeNode *x = this->root;
    while(x != NULL){
        if( x->JourneyCode == JourneyCode){
            return true;
        }
        else if(x->price > price){
            x = x->left;
        }
        else 
            x = x->right;
    }
    return false;
}

 TreeNode * BST::findnode(int JourneyCode, int price){
    TreeNode *x = this->root;
    while(x != NULL){
        if( x->JourneyCode == JourneyCode && x->price == price){
            return x;
        }
        else if(x->price > price){
            x = x->left;
        }
        else 
            x = x->right;
    }

    return NULL;
 }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 

    if(find_j(JourneyCode,price)){
        return false;
    }
    else{
        TreeNode * z;
        z  = new TreeNode(JourneyCode,price);
        TreeNode *y = NULL;
        TreeNode *x = this->root;

        while(x != NULL){
            y = x;
            if(x->price > z->price){
                x = x->left;
            }
            else 
             x = x->right;
        }

        z->parent = y;
        if(y == NULL){
            this->root = z;
        }
        else {
            if(y->price > z->price){
                y->left= z;
            }
            else
                y->right = z;
        }

    }

    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    TreeNode *x = this->root;
    while(x != NULL){
        if(x->price == price && x->JourneyCode == JourneyCode){
            return true;
        }
        else if(x->price > price){
            x = x->left;
        }
        else 
            x = x->right;
    }
    return false;
 }
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise

TreeNode* BST::successor(TreeNode* z){
    if(z->right != NULL){
        TreeNode*p = z->right;
        while(p->left != NULL){
            p = p->left;
        }
        return p;
    }

    return NULL;
}

bool BST::remove(int JourneyCode, int price) { 
    if(find(JourneyCode , price) == false){
        cout << "journey not found";
        return false;
    }
    else{
        TreeNode* d = this->findnode(JourneyCode,price);
        if(d->right == NULL && d->left == NULL){
            TreeNode* p = d->parent;
            if(p->left == d){
                p->left = NULL;
            }
            else
                p->right = NULL;

            delete(d);
            return true;    
        }

        else if(d->right == NULL || d->left == NULL){
            TreeNode* p = d->parent;
            TreeNode* c;
            if(d->left == NULL){
                c = d->right;
            }
            else 
                c = d->left;

            if(p->right = d){
                p->right = c;
                delete(d);
            }
            else
                p->left = c;
                delete(d);

            return true;        
        }

        else{
            TreeNode * s = successor(d);
            d->JourneyCode = s->JourneyCode;
            d->price = s->price;
            this->remove(s->JourneyCode,s->price);
            return true;
        }
    }
 }
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traversal(int typeofTraversal , TreeNode * treenode){
    if(typeofTraversal == 0){
        if(treenode == NULL){
            return;
        }
        else
            cout << treenode->JourneyCode << endl;
            traversal(typeofTraversal,treenode->left);
            traversal(typeofTraversal,treenode->right);
    }

    if(typeofTraversal == 1){
        if(treenode == NULL){
            return;
        }
        else
            
            traversal(typeofTraversal,treenode->left);
            traversal(typeofTraversal,treenode->right);
            cout << treenode->JourneyCode << endl;
    }

    if(typeofTraversal == 2){
        if(treenode == NULL){
            return;
        }
        else
            
            traversal(typeofTraversal,treenode->left);
            cout << treenode->JourneyCode << endl;
            traversal(typeofTraversal,treenode->right);
    }
}

void BST::traverse(int typeOfTraversal) {
    TreeNode *x = this->root;
    traversal(typeOfTraversal,x);

 }

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode *x = this->root;
    while(x->left !=NULL){
        x = x->left;
    }
    return x->price;
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

int main(){

BST b;
for(int i = 0; i < 5 ; i++){
    b.insert(i*i,i*i);
}
for(int i = 0; i < 4 ; i++){
    b.insert(i,i);
}

b.printBST("");
b.traverse(1);
cout << "**************" << endl;
b.traverse(0);
cout << "**************" << endl;
b.traverse(2);

cout << b.remove(1,1) << endl;
cout << b.getMinimum() << endl;
cout << "remove done" << endl;
b.printBST("");
b.traverse(1);

}



