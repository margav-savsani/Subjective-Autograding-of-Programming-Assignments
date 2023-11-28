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
    
    root = NULL;
    
 }
BST::BST(TreeNode *root){
    this->root=root; 
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
    if(find(JourneyCode,price)){ return false;}
    else{
        if(root==NULL){
            root=new TreeNode(JourneyCode,price);  
            root->parent=NULL;   
                  
        }
        else{
            if(root->price < price){
                if(root->right==NULL){
                    (root->right) = new TreeNode(JourneyCode,price);     
                    (root->right)->parent=root;
                    
                    
                }
                else{

                    BST b(root->right);
                    b.insert(JourneyCode,price);
                    
                }
            }

            else if(root->price > price){
                if(root->left==NULL){
                    (root->left) = new TreeNode(JourneyCode,price);     
                    (root->left)->parent=root;
                    
                    
                }
                else{

                    BST b(root->left);
                    b.insert(JourneyCode,price);
                    
                }
            }
        }
        return true;
    }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
        // finding the given element iteratively.
        TreeNode* x=root;
        while(x!=NULL and x->price!=price){
            if(x->price > price){
                x=x->left;
            }
            else{
                x=x->right;
            }
        }
        if(x!=NULL && x->price==price and x->JourneyCode==JourneyCode){
            return true;
        }
        else{return false;}

    
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {

    if(!find(JourneyCode,price)){return false;}
    // finding the location of node that is to be removed
    TreeNode* x=root;
    TreeNode* del;
    while(x!=NULL and x->price!=price){
        if(x->price > price){
            x=x->left;
        }
        else{
            x=x->right;
        }
    }
    if(x!=NULL && x->price==price and x->JourneyCode==JourneyCode){
        del=x;
    }
    // stored the node in variable called del.
    //in case of no children
    if(del->left==NULL && del->right==NULL){
        if(del->parent==NULL){del=NULL;root=del;}

        else if(del->parent!=NULL){
            if(del->parent->price > del->price){del->parent->left=NULL;}
            else if(del->parent->price < del->price){del->parent->right=NULL;}
        }
    }

    //1child
    else if(del->left==NULL && del->right!=NULL){
        if(del->parent==NULL){del=del->right;del->parent=NULL;root=del;}

        else if(del->parent!=NULL){
            if(del->parent->price > del->price){
                del->parent->left=del->right;
            }
            else if(del->parent->price < del->price){
                del->parent->right=del->right;
            }
            del->right->parent=del->parent;
        }
    }
    else if(del->left!=NULL && del->right==NULL){
        if(del->parent==NULL){del=del->left;del->parent=NULL;root=del;}

        else if(del->parent!=NULL){
            if(del->parent->price > del->price){
                del->parent->left=del->left;
            }
            else if(del->parent->price < del->price){
                del->parent->right=del->left;
            }
            del->left->parent=del->parent;
        }
    }

    //2children
    else if(del->left!=NULL && del->right!=NULL){
        TreeNode* x=del->left; 
        while(x->right!=NULL){
            x=x->right;
        }                                 // x is successor of del.
        int pri=x->price;              // store values of x in new variables
        int Jcode=x->JourneyCode;
        remove(x->JourneyCode,x->price);               // remove successor recursively
        del->price=pri;                     // overwrite value of root with above stored values.
        del->JourneyCode=Jcode;
    }
    return true;

}


	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal==0){
        if(root==NULL){return;}
        else{
            cout<<root->JourneyCode<<" ";
            BST bl(root->left);
            BST br(root->right);
            bl.traverse(0);
            br.traverse(0);
        }
    }
    else if(typeOfTraversal==1){
        if(root==NULL){return;}
        else{   
            BST bl(root->left);
            BST br(root->right);
            bl.traverse(1);
            br.traverse(1);
            cout<<root->JourneyCode<<" ";
        }
    }
    else if(typeOfTraversal==2){
        if(root==NULL){return;}
        else{   
            BST bl(root->left);
            BST br(root->right);
            bl.traverse(2);
            cout<<root->JourneyCode<<" ";
            br.traverse(2);
        }
    }
    return; 
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    if(root==NULL){return 0;}
    TreeNode* x=root;
    while(x->left!=NULL){
        x=x->left;
    }
    return x->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    if(root==NULL){return 0;}                        // calculate this value for both left and right subtree recursively. if root-price is in given range, return 1 + calculted sum,else return sum
    else{
        BST bl(root->left);
        BST br(root->right);
        int count=bl.countJourneysInPriceBound(lowerPriceBound,upperPriceBound)+br.countJourneysInPriceBound(lowerPriceBound,upperPriceBound);
        if(root->price >= lowerPriceBound && root->price <= upperPriceBound){
            return 1+count;
        }
        else{
            return count;
        }
    }
}

int l_no=0;
// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) {
    ofstream fout;
    fout.open(filename);
    if(root==NULL){fout.close();}
    else{
        l_no++;
        fout<<l_no<<" "<<root->JourneyCode<<" "<<root->price<<" "<<-1<<endl;;
        BST bl(root->left);
        BST br(root->right);
        bl.customStore(filename);
        br.customStore(filename);
        fout.close();
    }
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

void BST::customLoad (int flag, string filename) {  return ;}

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


