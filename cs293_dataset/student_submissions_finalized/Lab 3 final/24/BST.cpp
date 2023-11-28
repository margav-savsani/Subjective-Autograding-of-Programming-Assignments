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
    //root=NULL;
}
BST::BST(TreeNode *root){
    this->root=root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

 
bool BST::insert(int JourneyCode, int price) { 
    TreeNode *y=nullptr;
    TreeNode *x=root;
    if(root==nullptr){root=new TreeNode(JourneyCode,price); return true;}
    if(find(JourneyCode,price)) 
         return false;
    else{ while(x!=nullptr){
        y=x;
        if(price<  x->price){x=x->left;}
        else x=x->right;
    }
    TreeNode *z=new TreeNode(JourneyCode,price);
    z->parent=y;
    if(y==nullptr){
        root=z;
    }
    else if(z->price < y->price){y->left=z;}
    else y->right=z;
    return true;}
}
// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    TreeNode * s;
    s=root;
    //if(s==nullptr) return false;
    while(s!=NULL){
        //cout<<"entersed while loop  in find"<<endl;
        if((s->price==price) && (s->JourneyCode==JourneyCode)){
            return true;
        }
        else if(price < s->price){
            s=s->left;
        }
        else{
            s=s->right;
        }
    }
    return false;
}
//adding nextto function and mini function
TreeNode* BST :: nextto(TreeNode* x){
    if(x->right!=nullptr){
        return mini(x->right);
    }
    TreeNode* p=x->parent;
    while((x=p->right)&&(p!=nullptr)){  //parent null case missed
        //cout<<"nknj"<<endl;
        x=p;
        p=p->parent;
    }
    return p;
}
TreeNode* BST :: mini(TreeNode *x){
    while(x->left!=nullptr){
        x=x->left;
    }
    return x;
}
//adding nextto function and mini function

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    if(find(JourneyCode,price)){
        TreeNode *c;
        c=root;
        //cout<<"entered remove function"<<endl;
        while(true){
            if (c==nullptr) return false;//ROOT NULL ......................
            else if((c->price==price) && (c->JourneyCode==JourneyCode)){
                //cout<<"fnke";

                //no kids case
                if((c->right==nullptr)&&(c->left==nullptr)){
                    if(c->parent!=nullptr){
                        if((c->parent)->price < c->price) (c->parent)->right=nullptr;
                        else c->parent->left=nullptr;
                    }
                else c=NULL;
                delete c;
                }
                
                //one kid case
                else if((c->right==nullptr)&&(c->left!=nullptr)){
                    //cout<<"njf1";
                    if(c->parent!=nullptr){
                        if((c->parent)->price < c->price) (c->parent)->right=c->left;
                        else (c->parent)->right=c->right;
                    }
                else root=c->left;
                delete c;
                }
                else if((c->right!=nullptr)&&(c->left==nullptr)){
                    //cout<<"njf2";
                    if(c->parent!=NULL){
                        if((c->parent)->price < c->price) (c->parent)->left=c->left;
                        else (c->parent)->left=c->right;
                    }
                else root=c->right;
                delete c;
                }

                //two kids cases
                else{
                    //cout<<"entered two kids case";
                    TreeNode *d=nextto(c); //successor
                    //cout<<"hvvhjvj";
                    int p=d->JourneyCode;
                    int q=d->price;
                    remove(d->JourneyCode,d->price);
                    c->price=q;
                    c->JourneyCode=p;

                }
            return true;
            }
     {
        if(c->price>price)c=c->left;
        else c=c->right;
     }
        }
       // return false;
    }

    else{
       return false;
    }
}	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal==0){
        preorder(root);
    }
    else if(typeOfTraversal==1){
        postorder(root);
    }
    else if(typeOfTraversal==2){
        inorder(root);
    }
    return;
}
void BST :: preorder(TreeNode* x){
    TreeNode * y=x;
    if(y==nullptr)return;
    else{
        cout<<y->JourneyCode<<endl;
        preorder(y->left);
        preorder(y->right);
    }
}
void BST :: postorder(TreeNode* x){
    TreeNode * y=x;
    if(y==nullptr)return;
    else{
        cout<<y->JourneyCode<<endl;
        postorder(y->left);
        postorder(y->right);
    }
}
void BST :: inorder(TreeNode* x){
    TreeNode * y=x;
    if(y==nullptr)return;
    else{
        cout<<y->JourneyCode<<endl;
        inorder(y->left);
        inorder(y->right);
    }
}
// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode * m=mini(root);
    return m->price;
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