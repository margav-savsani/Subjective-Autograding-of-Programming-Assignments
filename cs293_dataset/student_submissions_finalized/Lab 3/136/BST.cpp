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
    root=new TreeNode();
}
BST::BST(TreeNode *root){
    this->root=root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
TreeNode* BST::search(int JourneyCode, int price,bool insert){
    TreeNode *t=root;
    while(true){
        if(t->price==price){
            return t;
        }
        if((t->left==nullptr)&&(t->right==nullptr)){
            if(insert){
                if(t->price>price){
                    TreeNode* p=new TreeNode(JourneyCode, price);
                    t->left=p;
                    t->right=nullptr;
                    return nullptr;
                }
                if(t->price<price){
                    TreeNode* p=new TreeNode(JourneyCode, price);
                    t->right=p;
                    t->left=nullptr;
                    return nullptr;
                }
            }
        }
        if(t->left==nullptr){
            if(insert){
                if(t->price>price){
                    TreeNode* p=new TreeNode(JourneyCode, price);
                    t->left=p;
                    return nullptr;
                }
            }
        }
        if(t->right==nullptr){                        
            if(insert){
                if(t->price<price){
                    TreeNode* p=new TreeNode(JourneyCode, price);
                    t->right=p;
                    return nullptr;
                }
            }
        }
        else if(t->price>price){
            t=t->left;
            if(t->price<price){
                return t;
            }
        }
        else if(t->price<price){
            t=t->right;
            if(t->price>price){
                return t;
            }
        }
    }
}

bool BST::insert(int JourneyCode, int price) { 
    //search and see
    if(root->price==0){
        root=new TreeNode(JourneyCode,price);
        return true;
    }
    if(search(JourneyCode, price,true)==nullptr){
        return true;
    }
    TreeNode* t=search(JourneyCode, price,true);
    if(t->price==price){
        return false;
    }
    else{
        if(t->price>price){
            TreeNode* p=new TreeNode(JourneyCode, price);
            p->parent=t->parent;    
            p->left=nullptr;
            p->right=t;
            t->parent->right=p;
            t->parent=p;
        }
        else if(t->price<price){
            TreeNode* p=new TreeNode(JourneyCode, price);
            p->parent=t->parent;
            p->right=nullptr;
            p->left=t;
            t->parent->left=p;
            t->parent=p;
        }
        return true;
    }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    if(root==nullptr){
        return false;
    }
    TreeNode* p=search(JourneyCode,price,false);
    if((p->JourneyCode==JourneyCode)&&(p->price==price)){
        return true;
    }    
    return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
    TreeNode* p=search(JourneyCode,price,false);
    if((p->JourneyCode==JourneyCode)&&(p->price==price)){
        //swap
        if(p->parent->right==p){
            p->parent->right=p->right;
            p->right->parent=p->parent;
            insert(p->JourneyCode,p->price);
        }
        else{
            p->parent->left=p->left;
            p->left->parent=p->parent;
            insert(p->JourneyCode,p->price);
        }
        return true;
    }    
    return false;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line
void preorder(TreeNode* t){
    if (t == nullptr){return;}
    else{
        TreeNode* tn=t;
        cout<<t->JourneyCode;
        preorder(tn->left);
        preorder(tn->right);
    }
}
void postorder(TreeNode* t){
    if (t == nullptr){return;}
    else{
        TreeNode* tn=t;
        postorder(tn->left);
        postorder(tn->right);
        cout<<t->JourneyCode;
    }
}
void inorder(TreeNode* t){
    if (t== nullptr){
        return;
    }
    else
    {
        TreeNode* tn=t;
        inorder(tn->left);
        cout<<t->JourneyCode;
        inorder(tn->right);
    }
}

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal==0){
        TreeNode* t=root;
        preorder(t);
    }
    if(typeOfTraversal==1){
        TreeNode* t=root;
        postorder(t);
    }
    if(typeOfTraversal==2){
        TreeNode* t=root;
        inorder(t);
    }
    return;
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode* p=root;
    int price=0;
    while(p!=nullptr){
        if(p->left==nullptr){
            price+=p->price;
            p=p->right;
        }
    }
    return price;
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

