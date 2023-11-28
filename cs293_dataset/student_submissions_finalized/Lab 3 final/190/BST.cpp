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
    jrnycount = 0;
 }
BST::BST(TreeNode *root){
    this->root = root;
    jrnycount = 0;
 }



//=============================================================================================================================





// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 


    if(find(JourneyCode, price)){
        return false;
    }
    
    if(root == NULL){

        // cout << 42 << endl;
        root = new TreeNode();
        root->JourneyCode = JourneyCode;
        root->price = price;
        // cout << 46 << endl;

        return true;
    }
    
    
    TreeNode *z = new TreeNode();

    // cout << 54 << endl;

    z->price = price;
    // cout << 57 << endl;
    z->JourneyCode = JourneyCode;

    // cout << 56 << endl;
    
    TreeNode *y = new TreeNode();
    y = NULL;
    TreeNode *x = new TreeNode();
    x = root;

    // cout << 65 << endl;
    while(x != NULL){
        y = x;

        if(z->price   <   x->price){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }

    // cout << 77 << endl;

    
    // cout << 84 << endl;

    z->parent = y;

    if(y == NULL){
        root = z;
    }
    else if(z->price < y->price){
        y->left = z;
    }
    else{
        y->right = z;
    }

    // cout << 87 << endl;
    return true;
}




//=============================================================================================================================





// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 

    TreeNode *x = root;

    while( x != NULL && x->price != price){
        if( price   <   x->price){
            x = x->left;
        }
        else {
            x = x->right;
        }
    }

    if(x == NULL){
        return false;
    }

    while(x->JourneyCode != JourneyCode){

        if(x->price != price){
            return false;
        }
        else{
            x = x->right;
        }

        if( x == NULL ){
            return false;
        }
    }

    // Fact that you reached here is proof that x is the right match!
    return true;

}






//=============================================================================================================================










	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    // cout << 171 << endl;
    //First finding the particular node to be deleted
    TreeNode *z = root;
    // cout << 174 << endl;

    while( z != NULL && z->price != price){
        if( price   <   z->price){
            z = z->left;
        }
        else {
            z = z->right;
        }
    }

    if(z == NULL){
        return false;
    }

    while(z->JourneyCode != JourneyCode){

        if(z->price != price){
            return false;
        }
        else{
            z = z->right;
        }

        if( z == NULL ){
            return false;
        }
    }

    // cout << 203 << endl;
    // z is to be deleted;

    TreeNode *y = new TreeNode();
    TreeNode *x = new TreeNode();

    if( z->left == NULL   ||    z->right == NULL){
        y =  z;
    }
    else{
        y = TreeSuccessor(z);
    }

    if( y->left != NULL ){
        x = y->left;
    }
    else{
        x = y->right;
    }


    // cout << 224 << endl;
    if(x != NULL){
        x->parent = y->parent;
    }

    // cout << 229 << endl;
    if(y->parent == NULL){
        root = x;
        // cout << 232 << endl;
    }
    else if( y == y->parent->left ){
        y->parent->left = x;
    }
    else {
        y->parent->right = x;
    }

    // cout << 239 << endl;

    if( y != z ){
        *z = *y;        //Copying all values of y into z
    } 

    return true;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line






//=============================================================================================================================








void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal == PRE_ORDER){
        preOrderTraverse(root);
    }
    else if(typeOfTraversal == IN_ORDER){
        inOrderTraverse(root);
    }
    else if(typeOfTraversal == POST_ORDER){
        postOrderTraverse(root);
    }
    return;
}

void BST::preOrderTraverse(TreeNode *x){
    if(x == NULL) return;

    cout << x->JourneyCode << endl;
    preOrderTraverse(x->left);
    preOrderTraverse(x->right);

    return;        
    
}
void BST::inOrderTraverse(TreeNode *x){
    if(x == NULL) return;

    preOrderTraverse(x->left);
    cout << x->JourneyCode << endl;
    preOrderTraverse(x->right);

    return;   
}
void BST::postOrderTraverse(TreeNode *x){
    if(x == NULL) return;

    preOrderTraverse(x->left);
    preOrderTraverse(x->right);
    cout << x->JourneyCode << endl;

    return;   
}








//=============================================================================================================================










// Returns the price of the cheapest journey
int BST::getMinimum() {
    return TreeMinimum(root)->price;    
 
}

TreeNode* BST::TreeSuccessor(TreeNode *x){
    if( x->right != NULL ) {
        TreeMinimum(x->right);
    } 

    TreeNode *y;
    y = x->parent;

    while(  y != NULL    &&    x == y->right ){
        x = y;
        y = y->parent;
    }

    return y;

}

TreeNode* BST::TreeMinimum(TreeNode *x){
    while( x->left != NULL ){
        x = x->left;
    }

    return x;
}


//=============================================================================================================================
//=============================================================================================================================
//=============================================================================================================================
//=============================================================================================================================
//=============================================================================================================================


























// Part II

void BST::countPriceRange(TreeNode *x, int p1, int p2, int &count){
    if(x == NULL) return;

    if(x->price >= p1 && x->price <= p2){
        count++;
    }
    countPriceRange(x->left, p1, p2, count);
    countPriceRange(x->right, p1, p2, count);

    return;        
    
}

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    int count=0;
    countPriceRange(root, lowerPriceBound, upperPriceBound, count);
    return count; 
}




// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.



void BST::printTree(TreeNode*x, ofstream &outfile, string s){
    
    
        outfile << s <<" " << x->JourneyCode << " " << x->price << "\n";
        // cout << 432<<endl;



        if (x->left != NULL)
        {
            printTree(x->left, outfile, s + "L");
        }

        if (x->right != NULL)
        {
            printTree(x->right, outfile, s + "R");
        }
    
}

void BST::customStore(string filename) { 
    ofstream outfile ;
    outfile.open(filename) ;
    printTree(root, outfile, "F");
    outfile << '\0';
    
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
    ifstream inputfile;
    inputfile.open(filename);
    string str;
    if(flag == LOAD_FULL_BST){
        inputfile >> str;
        while(str[0] != '\0'){
            
            TreeNode *x;
            int i=0;
            while(str[i] != '\0'){
                if(str[i] == 'F'){
                    x = root;
                }
                else if(str[i] == 'L'){
                    x = x->left;
                }
                else if(str[i] == 'R'){
                    x = x->right;
                }
                i++;
            }
            int jc;
            int p;
            inputfile >> jc >> p;
            x->JourneyCode = jc;
            x->price = p;

            inputfile >> str;
        }
    }
}


// ************************************************************
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