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
    TreeNode root;
}
BST::BST(TreeNode *root){
    TreeNode root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
     TreeNode *y=nullptr;
     TreeNode *x=root;
     TreeNode z(JourneyCode,price);
     while (x!=nullptr){
        y=x;
        if (price<x->price){
            x=x->left;
        }
        else{
            x=x->right;
        }
     }
     z.parent=y;
     if (y==nullptr){
        *root=z;
        return true;
     }
     else if (z.price<y->price){
        y->left=&z;
        return true;
     }
     else{
        y->right=&z;
        return true;
     }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    TreeNode *x=root;
    while(x!=nullptr && x->price!=price){
        if (price<x->price){
            x=x->left;
        }
        else{
            x=x->right;
        }
    }
    if(x==nullptr){
        return false;
    }
    return true;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
    TreeNode *x=root;
    while(x!=nullptr && x->price!=price){
        if (price<x->price){
            x=x->left;
        }
        else{
            x=x->right;
        }
    }
    if(x==nullptr){
        return false;
    }
    else{
        if(x->right==nullptr && x->left==nullptr){
            if (x->parent==nullptr){
                return false;
            }
            else if(x->price<x->parent->price){
                x->parent->left=nullptr;
                return true;
            }
            else{
                x->parent->right=nullptr;
                return true;
            }
        }
        else if(x->right==nullptr){
            if (x->parent==nullptr){
                return false;
            }
            else if(x->price<x->parent->price){
                x->parent->left=x->left;
                return true;
            }
            else{
                x->parent->right=x->left;
                return true;
            }
        }
        else if(x->left==nullptr){
            if (x->parent==nullptr){
                return false;
            }
            else if(x->price<x->parent->price){
                x->parent->left=x->right;
                return true;
            }
            else{
                x->parent->right=x->right;
                return true;
            }
        }
        else{
            TreeNode *y;
            if(x->left!=nullptr){
                y=x->left;
                while (y->right!=nullptr){
                    y=y->right;
                }
                if (y->left==nullptr){
                    x->JourneyCode=y->JourneyCode;
                    x->price=y->price;
                    return true;
                }
                else{
                    y->parent->right=y->left;
                    x->JourneyCode=y->JourneyCode;
                    x->price=y->price;
                    return true;
                }
            }
            else{
                y=x->parent;
                TreeNode *z;
                z=x;
                while(y!=nullptr && z==y->left){
                    z=y;
                    y=y->parent;
                }
                TreeNode *k;
                if (y->right!=nullptr){
                    k=y->right;
                }
                else{
                    k=y->left;
                }
                if (k!=nullptr){
                    k->parent=y->parent;
                }
                if(y->parent==nullptr){
                    root=k;
                }
                else if(y==y->parent->right){
                    y->parent->right=k;
                }
                else{
                    y->parent->left=k;
                }
                if(y!=x){
                    x->JourneyCode=y->JourneyCode;
                    x->left=y->left;
                    x->parent=y->parent;
                    x->price=y->price;
                    x->right=y->right;
                    return true;
                }
                else{
                    return false;
                }
            }
        }
    }
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    if (typeOfTraversal==0){
        preOrder(root);
    }
    else if(typeOfTraversal==1){
        postOrder(root);
    }
    else if(typeOfTraversal==2){
        inOrder(root);
    }
}
void BST::preOrder(TreeNode * r){
    if (r==nullptr){
        return;
    }
    else{
        cout<<r->JourneyCode<<endl;
        preOrder(r->left);
        preOrder(r->right);
    }
}
void BST::postOrder(TreeNode * r){
    if (r==nullptr){
        return;
    }
    else{
        preOrder(r->left);
        preOrder(r->right);
        cout<<r->JourneyCode<<endl;
    }
}
void BST::inOrder(TreeNode * r){
    if (r==nullptr){
        return;
    }
    else{
        preOrder(r->left);
        cout<<r->JourneyCode<<endl;
        preOrder(r->right);
    }
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode *x=root;
    while(x->left!=nullptr){
        x=x->left;
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

