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

// Constructors for the BST Class
BST::BST(){
    root = NULL;
}
BST::BST(TreeNode *root){ this->root = root; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
     TreeNode* toInsert; // initializes a node with the given parameters
     toInsert->JourneyCode = JourneyCode;
     toInsert->price = price;
     
     TreeNode *y = NULL;
     TreeNode *x = root;

     while(x!=NULL){
        y = x;
        if(price< (x->price)){
            x = (x->left);
        }
        else{
            x = (x->right);
        }
     }
     toInsert->parent = y;
     if (y==NULL){
        root = toInsert;
        return true;
     }
     // checking for both strict inequlities to remove the probability of equality in the tree prices
     else if (toInsert->price < y->price){
        y->left = toInsert;
        return true;
     }
     else if (toInsert->price > y->price){
        y->right = toInsert;
        return true;
     }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    TreeNode * x = root;
    while (x==NULL && (price!=(x->price) || JourneyCode!=(x->JourneyCode))){
        if(price < (x->price)){
            x = (x->left);
        }
        else {
            x = (x->right);
        }
    }
    if((price==(x->price) && JourneyCode==(x->JourneyCode))){
        return true; // both the prices and journey code matches
    }
    else{
        return false; // node not found
    }
    
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
    bool isPresent = find(JourneyCode, price);
    if(!isPresent){
        return false;
    }
    else{
        TreeNode* x = root;
        if(price < x->price)
        {
            // Checking for NULL Node is not necessary since we know that the node exists and the value of node is less that that of current node
            BST removeLeft(x->left);
            removeLeft.remove(JourneyCode, price);

        }
        else if(price == x->price)
        {   
            // the node is a leaf
            if (x->right == NULL && x->left == NULL){
                x->parent == NULL;
                if ((x->parent)->left == x){ // the leaf is a left leaf
                    (x->parent)->left = NULL;
                    return true;
                } 
                else if ((x->parent)->right == x){ // the leaf is a right leaf
                    (x->parent)->right = NULL;
                    return true;
                }
            } 

            // The node has only 1 child
            if (x->right == NULL || x->left == NULL){
                if(x->right == NULL){// It has a left child
                    if((x->parent)->left == x){ // it has right parent
                        // making new connections
                        (x->left)->parent = (x->parent);
                        (x->parent)->left = (x->left);

                        // deallocating all relatives of x
                        (x->left) = NULL;
                        (x->right) = NULL;
                        (x->parent) = NULL;
                        return true; 
                    }
                    else if ((x->parent)->right == x){ // it has a left parent
                        // making new connections
                        (x->left)->parent = (x->parent);
                        (x->parent)->right = (x->left);

                        // deallocating all relatives of x
                        (x->left) = NULL;
                        (x->right) = NULL;
                        (x->parent) = NULL;
                        return true; 
                    }
                }
                else if (x->left == NULL){ // It has a right child
                    if((x->parent)->left == x){ // it has right parent
                        // making new connections
                        (x->right)->parent = (x->parent);
                        (x->parent)->left = (x->right);

                        // deallocating all relatives of x
                        (x->left) = NULL;
                        (x->right) = NULL;
                        (x->parent) = NULL; 
                        return true;
                    }
                    else if ((x->parent)->right == x){ // it has a left parent
                        // making new connections
                        (x->right)->parent = (x->parent);
                        (x->parent)->right = (x->right);

                        // deallocating all relatives of x
                        (x->left) = NULL;
                        (x->right) = NULL;
                        (x->parent) = NULL; 
                        return true;
                    }
                }
            }

            // The node has exactly 2 child
            if (x->right != NULL && x->left != NULL){
                // finding the successor of the current node
                
                // find the successor in the right subtree
                TreeNode* succ = x;// stores the successor of x
                TreeNode* y; // node to traverse the array

                // y = minimum(rightsubtree) // WRITE HERE!! DO NOT FORGET !!!
                if (x->right != NULL){
                    y = x->right;

                    while(y->left != NULL){
                        y = y->left;
                    }

                    succ = y;
                }
                // case where successor is in the left sub parent
                
                y = (x->parent);

                while ((y != NULL) && x == (y->right)){
                    x = y;
                    y = y->parent;
                }
                succ = y; 

                // Above this, successor is fixed.
                TreeNode temp; // temporarily save the data of thesuccessor 
                temp.JourneyCode = succ -> JourneyCode;
                temp.price = succ -> price;

                BST deleteSucc(succ); // deletes the successor of the current node - recursively
                
                // Replace the data of the successor in x
                x->JourneyCode = temp.JourneyCode;
                x->price = temp.price;

                return true;
            }

        }
        else if (price > x->price)
        {
            BST removeRight(x->right);
            removeRight.remove(JourneyCode, price);
        }

    }
      
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal==2){
        TreeNode* x = root;

        if(x->left != NULL){ BST leftTree(x->left); leftTree.traverse(IN_ORDER);}
        cout<<(x->JourneyCode);
        if(x->right != NULL){ BST rightTree(x->right); rightTree.traverse(IN_ORDER);} 
        
    }
    else if(typeOfTraversal==1){
        TreeNode* x = root;

        if(x->left != NULL){ BST leftTree(x->left); leftTree.traverse(POST_ORDER);}
        if(x->right != NULL){ BST rightTree(x->right); rightTree.traverse(POST_ORDER);}
        cout<<(x->JourneyCode);
        
    }
    else if(typeOfTraversal==0){
        TreeNode* x = root;

        cout<<(x->JourneyCode);
        if(x->left != NULL){ BST leftTree(x->left); leftTree.traverse(PRE_ORDER);}
        if(x->right != NULL){ BST rightTree(x->right); rightTree.traverse(PRE_ORDER);}
        
    }
    return; 
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    if(root==NULL){
        return 0; // no tree case
    }
    if(root->left == NULL){
        return root->price; // returns the price of the root if only one node is present in the tree
    }
    // else left child exists
    TreeNode *leftChild =  root->left;

    while(leftChild!=NULL){
        leftChild = leftChild->left;
    }
    return leftChild->price; 
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


