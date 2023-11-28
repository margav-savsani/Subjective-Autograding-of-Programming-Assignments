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
    TreeNode* t;
    t=new TreeNode();
    root=t;
    }

BST::BST(TreeNode *root){
    this->root=root; 
    }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

TreeNode* BST::get_parent(TreeNode* r, int JourneyCode, int price){
        if(r->right==NULL && r->left==NULL){
            return r;
        }
        if(price > r->price){ 
            get_parent(r->right, JourneyCode, price);
        }
        if(price < r->price){
            get_parent(r->left, JourneyCode, price);
        }
}

bool BST::insert(int JourneyCode, int price) { 
    if(find(JourneyCode,price)){
        return false;
    }
    if(root==NULL){
        root->JourneyCode=JourneyCode;
        root->price=price;
    }
    TreeNode* t;
    // TreeNode* p;
    // TreeNode* par;
    // p=root;
    // int k=0;
    t=new TreeNode;
    t->JourneyCode=JourneyCode;
    t->price=price;
    // while(p!=NULL){
    //     if(t->price > p->price){ 
    //         par=p;
    //         p=p->right;
    //         k=1;
    //     }
    //     if(p->price > t->price){
    //         par=p;
    //         p=p->left;
    //         k=2;
    //     }
    // }
    // if(p==NULL){
    //     t->left=t->right=NULL;
    //     t->parent=par;
    //     if(k==1) par->right=t;
    //     if(k==2) par->left=t;
    // }
    TreeNode* p;
    p=get_parent(root, JourneyCode, price);
    if(p->price < price){
        p->right=t;
    }
    if(p->price > price){
        p->left=t;
    }
    t->parent=p;
    return true;
    }

bool find2(TreeNode* root, int JourneyCode, int price){
    if(root==NULL){
        return false;
    }
    if(root->price==price && root->JourneyCode==JourneyCode){
        return true;
    }
    if(root->price < price){
        find2(root->left,JourneyCode, price);
    }
    if(root->price > price){
        find2(root->right,JourneyCode, price);
    }
    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise

TreeNode* get_address(TreeNode* r, int JourneyCode, int price){
    if(r->price==price && r->JourneyCode==JourneyCode){
        return r;
    }
    if(r->price < price){
        find2(r->left,JourneyCode, price);
    }
    if(r->price > price){
        find2(r->right,JourneyCode, price);
    } 
}

bool BST::find(int JourneyCode, int price) { 
    find2(root, JourneyCode, price);
}

TreeNode* succes(TreeNode* r, int JourneyCode, int price){
    if(r->left==NULL){
        return r;
    }
    succes(r->left,JourneyCode,price);
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise

bool BST::remove(int JourneyCode, int price) {
    if(!(find(JourneyCode,price))){
        return false;
    }
    TreeNode* x;
    x=get_address(root, JourneyCode, price);
    // TreeNode* ptr;
    // ptr=root;
    // while(true){
    //     if(ptr->price==price && ptr->JourneyCode==JourneyCode){
    //         x=ptr;
    //         break;
    //     }
    //     if(ptr->price < price){
    //         ptr=ptr->left;
    //         find(JourneyCode, price);
    //     }
    //     if(ptr->price > price){
    //         ptr=ptr->right;
    //         find(JourneyCode, price);
    //     }  
    // }
    TreeNode* par;
    par=get_parent(root, JourneyCode, price);

    if(x->left==NULL && x->right==NULL){
        if(par->left==x){
            par->left==NULL;
        }
        if(par->right==x){
            par->right==NULL;
        }
    } 
    else if(x->left==NULL){      
        if(par->left==x){
            // (x->right)->right=par->right;
            par->left=x->right;
        }
        if(par->right==x){
            par->right=x->right;
        }
    }
    else if(x->right==NULL){
        if(par->right==x){
            // (x->left)->left=par->left;
            par->right=x->left;
        }
        if(par->left==x){
            par->left=x->left;
        }
    }
    else if((x->left!=NULL && x->right!=NULL)){
        TreeNode* ptr1;
        ptr1=succes(x->right, JourneyCode, price);
        // while(ptr1->left==NULL){
        //     ptr1=ptr1->left;
        // }
        ptr1->right=x->right;
        ptr1->left=x->left;
        ptr1->parent=x->parent;
    }
    return true;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void postorder(TreeNode* r){
    if(r==NULL) return;
    postorder(r->left);
    postorder(r->right);
    cout<<r->JourneyCode<<" "<<r->price;    
}

void preorder(TreeNode* r){
    if(r==NULL) return;
    cout<<r->JourneyCode<<" "<<r->price;
    preorder(r->left);
    preorder(r->right);
}

void inorder(TreeNode* r){
    if(r==NULL) return;
    inorder(r->left);
    cout<<r->JourneyCode<<" "<<r->price;
    inorder(r->right);
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
}

int min(TreeNode* ptr){
    while(ptr->left==NULL){
        ptr=ptr->left;
    }
    int k=ptr->price;
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    return min(root);
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

