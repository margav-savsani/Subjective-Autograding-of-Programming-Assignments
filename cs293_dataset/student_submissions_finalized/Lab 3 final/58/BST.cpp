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

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price){

    if(root->JourneyCode==JourneyCode ) return true;
    
    if(price<=root->price && root->left==nullptr){
        return false;
    }

    if(price>root->price && root->right==nullptr){
        return false;
    }

    if(price<=root->price){
        BST l(root->left);
        return l.find(JourneyCode,price);
    }

    if(price>root->price){
        BST r(root->right);
        return r.find(JourneyCode,price);
    }
}
// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price){
    
    if(find(JourneyCode,price)) return false;

    if(root->JourneyCode==0 && root->price==0){
        root->JourneyCode=JourneyCode;
        root->price=price;
        return true;
    }

    if(price<=root->price && root->left==nullptr){
        TreeNode *l=new TreeNode(JourneyCode,price);
        l->parent=root;
        root->left=l;
        return true;
    }
    
    if(price<=root->price){
        BST l(root->left);
        
        return l.insert(JourneyCode,price);
    }

    if(price>root->price && root->right==nullptr){
        TreeNode *r=new TreeNode(JourneyCode,price);
        r->parent=root;
        root->right=r;
        return true;
    }

    if(price>root->price){
        BST r(root->right);

        return r.insert(JourneyCode,price);
    }

    
}

TreeNode *BST::getadress(int JourneyCode,int price){
    if(root->price ==price && root->JourneyCode==JourneyCode) return root;
    
    if(price<=root->price){
        BST l(root->left);
        return l.getadress(JourneyCode,price);
    }

    if(price>root->price){
        BST r(root->right);
        return r.getadress(JourneyCode,price);
    }
}

TreeNode *BST::getmax(TreeNode *kingleft){
    if(kingleft->right==NULL) {return kingleft;}

    else {return getmax(kingleft->right);}
}

TreeNode *BST::getpredecessor(TreeNode *king){
    return getmax(king->left);
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price){
    
    if(!find(JourneyCode,price)) return false;

    TreeNode *tn=getadress(JourneyCode,price);

    if(tn->right==NULL && tn->left==NULL){ if(tn->parent->left==NULL) {tn->parent->right=NULL;return true;}
                                            else if(tn->parent->right==NULL) {tn->parent->left=NULL;return true;}
                                            else { if(tn->parent->left->JourneyCode==JourneyCode) {tn->parent->left=NULL;return true;}
                                                    else {tn->parent->right=NULL;return true;}}
                                         }
    else if(tn->right==NULL && tn->left!=NULL){
        if(tn->parent->left==NULL){tn->parent->right=tn->left;
                                    tn->left->parent=tn->parent;
                                    return true;}

        else if(tn->parent->right==NULL){tn->parent->left=tn->left;
                                          tn->left->parent=tn->parent;
                                          return true;}

        else { if(tn->parent->left->JourneyCode==JourneyCode) {tn->parent->left=tn->left;
                                                                tn->left->parent=tn->parent;
                                                                return true;}
                else {tn->parent->right=tn->left;
                        tn->left->parent=tn->parent;
                        return true;}
            }
    }


    else if(tn->right!=NULL && tn->left==NULL){
        if(tn->parent->left==NULL){tn->parent->right=tn->right;
                                    tn->right->parent=tn->parent;
                                    return true;}

        else if(tn->parent->right==NULL){tn->parent->left=tn->right;
                                          tn->right->parent=tn->parent;
                                          return true;}

        else { if(tn->parent->left->JourneyCode==JourneyCode) {tn->parent->left=tn->right;
                                                                tn->right->parent=tn->parent;
                                                                return true;}
                else {tn->parent->right=tn->right;
                        tn->right->parent=tn->parent;
                        return true;}
            }
    }

    else {

        TreeNode *predecessor=getpredecessor(tn);
        bool god=remove(predecessor->JourneyCode,predecessor->price);

        tn->JourneyCode=predecessor->JourneyCode;
        tn->price=predecessor->price;

        return true;
    }
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal){
    
    if(typeOfTraversal==0){
        cout << root->JourneyCode <<endl;
        if(root->left!=NULL) {BST l(root->left);l.traverse(0);}
        if(root->right!=NULL) {BST r(root->right);r.traverse(0);}
    }

    else if(typeOfTraversal==1){
        if(root->left!=NULL) {BST l(root->left);l.traverse(1);}
        if(root->right!=NULL) {BST r(root->right);r.traverse(1);}
        cout << root->JourneyCode <<endl;
    }

    else if(typeOfTraversal==2){
        if(root->left!=NULL) {BST l(root->left);l.traverse(2);}
        cout <<root->JourneyCode <<endl;
        if(root->right!=NULL) {BST r(root->right);r.traverse(2);}
    }
    
    return;
}

// Returns the price of the cheapest journey
int BST::getMinimum(){
    if(root->left==NULL) return root->price;

    else {
        BST l(root->left);
        return l.getMinimum();
    }
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound){
    if(root->left==NULL && root->right==NULL){
        if(root->price>=lowerPriceBound && root->price<=upperPriceBound){ return 1;}
        else return 0;
    }

    else if(root->left!=NULL && root->right==NULL){
        BST l(root->left);
        if(root->price>=lowerPriceBound && root->price<=upperPriceBound){ return (1+l.countJourneysInPriceBound(lowerPriceBound,upperPriceBound));}
        else return l.countJourneysInPriceBound(lowerPriceBound,upperPriceBound);
    }

    else if(root->left==NULL && root->right!=NULL){
        BST r(root->right);
        if(root->price>=lowerPriceBound && root->price<=upperPriceBound){ return (1+r.countJourneysInPriceBound(lowerPriceBound,upperPriceBound));}
        else return r.countJourneysInPriceBound(lowerPriceBound,upperPriceBound);
    }

    else{
        BST l(root->left),r(root->right);
        if(root->price>=lowerPriceBound && root->price<=upperPriceBound){ return (1+l.countJourneysInPriceBound(lowerPriceBound,upperPriceBound)+r.countJourneysInPriceBound(lowerPriceBound,upperPriceBound));}
        else return (l.countJourneysInPriceBound(lowerPriceBound,upperPriceBound)+r.countJourneysInPriceBound(lowerPriceBound,upperPriceBound));
    }
}

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
        result.push_back(to_string(root->JourneyCode) + "\n");
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


