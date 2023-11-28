//#include <bits/stdc++.h>
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



// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS
BST::BST(){ ; }
BST::BST(TreeNode *root1){root = root1;}
// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
    bool rightChild;
     if (find(JourneyCode, price)){
    struct TreeNode* probe = root;
    struct TreeNode* iterator;

    do{
        iterator = probe;
    if (price < (probe->price)){
        probe = probe->left;
        rightChild = false;
    }
    else if(price > (probe->price)){
        probe = probe->right;
        rightChild = true;
    }
    } while(probe != NULL);
    
    struct TreeNode* newNode = new TreeNode(JourneyCode, price);
    newNode->parent = iterator;
    if (rightChild == false){
        iterator->left = newNode;
    }
    else{
        iterator->right = newNode;
    }
    return true;
    }
    return false;
    }

// Return True, if the ticket with given attributes is found, false otherwise
bool search(struct TreeNode* presentNode, int key,int JourneyCode){
        if(presentNode==NULL) return;
        if(presentNode->JourneyCode == JourneyCode && presentNode->price==key) return true;
        if(presentNode->price > key) search(presentNode->left, key, JourneyCode);
        else search(presentNode->right, key, JourneyCode);
        return false;
    }
    
bool BST::find(int JourneyCode, int price) {
    struct TreeNode* presentNode = root;
    return search(presentNode, price, JourneyCode);
}
    
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
    
    struct TreeNode* probe = root;
    struct TreeNode* iterator;

    do{
        iterator = probe;
    if (price < (probe->price)){
        probe = probe->left;
        rightChild = false;
    }
    else if(price > (probe->price)){
        probe = probe->right;
        rightChild = true;
    }
    } while((probe != NULL) || ((probe->JourneyCode != JourneyCode)&&(probe->price != price)));
    
    // node to be deleted is a leaf
    if ((probe->right == NULL) && (probe->left == NULL) && (rightChild == true)){
        iterator->right = NULL;
    }
    else if ((probe->right == NULL) && (probe->left == NULL) && (rightChild == false)){
        iterator->left = NULL;
    }

    // node to be deleted has one child
    if (((probe->right != NULL) || (probe->left != NULL)) && (rightChild == true)){
        if (probe->right != NULL){
        iterator->right = probe->right;
        }
        else{
            iterator->right = probe->left;
        }
    }
    else if (((probe->right != NULL) || (probe->left != NULL)) && (rightChild == false)){
         if (probe->right != NULL){
        iterator->left = probe->right;
        }
        else{
            iterator->left = probe->left;
        }
    }

    // node to be deleted has two children
    if ((probe->right != NULL)&&(probe->left != NULL)){
        
    }

    struct TreeNode* newNode = new TreeNode(JourneyCode, price);
    newNode->parent = iterator;
    if (rightChild == false){
        iterator->left = newNode;
    }
    else{
        iterator->right = newNode;
    }
    
    
    
    if(find(JourneyCode, price)){

    }
    return false;
    }
    
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line
struct TreeNode preorder(struct TreeNode* v){
            if(v==NULL) return;
            else {
                cout << v->JourneyCode << endl;
                preorder(v->left);
                preorder(v->right);
            }
        }
        struct TreeNode postorder(struct TreeNode* v){
            if(v==NULL) return;
            else {
                postorder(v->left);
                postorder(v->right);
                cout << v->JourneyCode << endl;
            }
        }
        struct TreeNode inorder(struct TreeNode* v){
            if(v==NULL) return;
            else {
                preorder(v->left);
                preorder(v->right);
                cout << v->JourneyCode << endl;
            }
        }

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal==0) preorder(root);
    else if(typeOfTraversal==1) postorder(root);
    else if(typeOfTraversal==2) inorder(root);
    return;
}
// Returns the price of the cheapest journey
int BST::getMinimum() {
    struct TreeNode* presentNode = root;
     while(presentNode->left != NULL){
        presentNode = presentNode->left;
        }
        return presentNode->price;
    }

/* ..................Part1 ends....................*/
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

