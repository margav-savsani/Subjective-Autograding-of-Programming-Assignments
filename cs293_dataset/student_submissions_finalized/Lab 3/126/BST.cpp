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
    root=nullptr;
 }
BST::BST(TreeNode *root){
    this->root=root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise



bool BST::insert(int JourneyCode, int price) { 
    TreeNode *ins=new TreeNode;
    ins->JourneyCode=JourneyCode;
    ins->price=price;
    ins->left=nullptr;
    ins->right=nullptr;
    TreeNode *y=nullptr; 
    TreeNode *x=root;
    while(x!=nullptr){
        y=x;
        if(JourneyCode==x->JourneyCode)
            return false;
        else if(price<(x->price)){
            x=x->left;
        }  
        else{
            x=x->right;
        }
    }
    ins->parent=y;
    if(y==nullptr){
        root=ins;
    }
    //instead of the following 4 lines, x=ins should work
    else if((y->price)>price)
        y->left=ins;
    else
        y->right=ins;
    return true;
  }
// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    TreeNode *x=root;
    while(x!=nullptr){
        if((x->JourneyCode==JourneyCode)&&(x->price==price)){
            return true;
        }
        else if(x->price>price){
            x=x->left;
        }
        else{
            x=x->right;
        }
    }
    return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
    TreeNode *t=root;
    while(t!=nullptr){
        if((t->JourneyCode==JourneyCode)&&(t->price==price)){
            break;
        }
        else if(t->price>price){
            t=t->left;
        }
        else{
            t=t->right;
        }
    }
    if(t==nullptr){
        return false;
    }
    else{
        //case1, t has 0 children
        if(t->left==nullptr&&t->right==nullptr){
            if(t->parent!=nullptr){
                if(t->parent->left==t){
                    t->parent->left=nullptr;
                }
                else{
                    t->parent->right=nullptr;
                }
            }
            else{
                root=nullptr;
            }
        }
        //case2, t has 1 child
        else if(t->left==nullptr){
            if(t->parent!=nullptr){
                if(t->parent->left==t){
                    t->parent->left=t->right;
                    t->right->parent=t->parent;
                    t=nullptr;
                }
                else{
                    t->parent->right=t->right;
                    t->right->parent=t->parent;
                    t=nullptr;
                }
            }
            else{
                root=t->right;
                root->parent=nullptr;
            }
        }
        else if(t->right==nullptr){
            if(t->parent!=nullptr){
                if(t->parent->left==t){
                    t->parent->left=t->left;
                    t->left->parent=t->parent;
                    t=nullptr;
                }
                else{
                    t->parent->right=t->left;
                    t->left->parent=t->parent;
                    t=nullptr;
                }
            }
            else{
                root=t->left;
                root->parent=nullptr;
            }
        }
        else{
            //finding the successor
            TreeNode *temp=t->right;
            while(temp->left!=nullptr){
                temp=temp->left;
            }
            
            if(temp->right==nullptr){
                t->JourneyCode=temp->JourneyCode;
                t->price=temp->price;
                if(temp->parent->left==temp){
                    temp->parent->left=nullptr;
                }
                else{
                    temp->parent->right=nullptr;
                }
            }
            else{
                if(temp->parent->left==temp){
                    temp->parent->left=temp->right;
                    temp->right->parent=temp->parent;
                }
                else{
                    temp->parent->right=temp->right;
                    temp->right->parent=temp->parent;
                }
                t->JourneyCode=temp->JourneyCode;
                t->price=temp->price;
                temp=nullptr;
            }
        }
    }
    return true;
}

void BST::pre(TreeNode* n){
    if(n==nullptr){
        return;
    }
    else{
        cout<<n->JourneyCode;
        pre(n->left);
        pre(n->right);
        return;
    }
}
void BST::post(TreeNode* n){
    if(n==nullptr){
        return;
    }
    else{
        post(n->left);
        post(n->right);
        cout<<n->JourneyCode;
        return;
    }
}
void BST::inord(TreeNode* n){
    if(n==nullptr){
        return;
    }
    else{
        inord(n->left);
        cout<<n->JourneyCode;
        inord(n->right);
        return;
    }
}

void BST::pre1(TreeNode *n, ostream& outfile){
    if(n==nullptr){
        return;
    }
    else{
        if(n->left==nullptr&&n->right==nullptr){
            outfile<<n->price<<" "<<n->JourneyCode<<" ";
        }
        else{
            outfile<<n->price<<" "<<n->JourneyCode<<" "<<-1<<" ";
            pre1(n->left, outfile);
            pre1(n->right, outfile);
            outfile<<-2<<" ";
        }
        return;
        
    }
}

	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal==0){
        pre(root);
    }
    else if(typeOfTraversal==1){
        post(root);
    }
    else if(typeOfTraversal==2){
        inord(root);
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
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    return;
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) { 
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
        root=curr;
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
        result.push_back(to_string(root->JourneyCode) + "\n");
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        getBST( prefix + (isLeft ? "│   " : "    "), true);
        root=curr;
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

