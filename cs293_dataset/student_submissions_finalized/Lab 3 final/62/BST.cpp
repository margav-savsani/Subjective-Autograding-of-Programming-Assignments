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
#define NS -1 //Null Stored

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST(){root = NULL; }
BST::BST(TreeNode *root){this->root=root; }

//see if given journey code was already present in the tree
bool TreeNode::copies(int jrnyCode){
    if (JourneyCode==jrnyCode) return true;
    if (left==NULL&&right==NULL) return false; //leaf
    if (left==NULL) return right->copies(jrnyCode); //check in right subtree
    if (right==NULL) return left->copies(jrnyCode); //check in left subtree
    return (right->copies(jrnyCode)|| left->copies(jrnyCode)); //check both subtrees
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {    
    if (root==NULL){ //insert to empty BST
        root = new TreeNode(JourneyCode, price);
        return true;
    }
    //if (root->copies(JourneyCode)) return false; // returns false if journey code is already present
    TreeNode* current=root;
    while(current!=NULL){//travel down the tree
        if (price<current->price){
            if (current->left==NULL){ // if reached an empty spot, insert here
                current->left=new TreeNode(JourneyCode, price, NULL,NULL,current);
                return true;
            }
            current=current->left; //otherwise keep moving
        }
        else { // >=
            if (current->right==NULL){ // if reached an empty spot, insert here
                current->right=new TreeNode(JourneyCode, price, NULL,NULL,current);
                return true;
            }
            current=current->right; //otherwise keep moving
        }
    }  
    return false;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    TreeNode* current=root;
    while(current!=NULL&&current->JourneyCode!=JourneyCode){  //travelling down the tree      
        if (price<current->price){
            current=current->left;
        }
        else{ // equal prices go to the right by this convention
            current=current->right;
        }
    }    
    if (current==NULL) return false; //did not find match
    if (current->JourneyCode==JourneyCode) return true;
    else return false; //for safety    
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    if (root==NULL) return false;
    //handling the case where root is to be removed
    if (root->JourneyCode==JourneyCode&&root->price==price){
        if (root->left==NULL&root->right==NULL){ //no children
            root=NULL;
        } 
        //one child
        else if (root->left==NULL) { 
            root=root->right;
            root->parent=NULL;            
        }
        else if(root->right==NULL){
            root=root->left;
            root->parent=NULL;            
        }
        else{ //rem function can be called
            root->rem();
        }
        return true;
    }

    TreeNode* current=root;
    while(current!=NULL&&current->JourneyCode!=JourneyCode){
        if (price<current->price){
            current=current->left;
        }
        else{
            current=current->right;
        }
    }    
    if (current==NULL) return false; //found no matches
    if (current->price!=price) return false; //Journey code implied to be same
    
    current->rem(); //remove that node
    return true; 
    
}

/*
To implement:	
    Functions that traverse the BST in various ways!
    type is one of PRE_ORDER, POST_ORDER or IN_ORDER
    Print on cout the journey codes at nodes of the BST in the same order as
    they are encountered in the traversal order
    Print one journey code per line */

void BST::traverse(int typeOfTraversal) {
    if (root==NULL) return; //recursion base case & handling 
    switch (typeOfTraversal){
        case PRE_ORDER:{
            cout<<root->JourneyCode<<endl; //node
            {BST(root->left).traverse(typeOfTraversal);} //print for left
            {BST(root->right).traverse(typeOfTraversal);} //print for right
            break;
        }
        case POST_ORDER:{            
            {BST(root->left).traverse(typeOfTraversal);} //print for left
            {BST(root->right).traverse(typeOfTraversal);} //print for right
            cout<<root->JourneyCode<<endl; //node
            break;
        }
        case IN_ORDER:{
            {BST(root->left).traverse(typeOfTraversal);} //print for left
            cout<<root->JourneyCode<<endl; //node
            {BST(root->right).traverse(typeOfTraversal); } //print for right           
            break;
        }
    }
    return; 
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    if (root==NULL) return -1; //handling null root entry
    TreeNode* current=root;
    for(;current->left!=NULL;current=current->left){} // finding the leftmost child
    return current->price;
}

void TreeNode::rem(){ //helper function to remove a node
    if (parent!=NULL){ //when not root
        if (left==NULL&&right==NULL){ //no children
            if(parent->left==this) parent->left=NULL;
            else parent->right=NULL;
        }
        //one child
        else if (left==NULL){ 
            if(parent->left==this) parent->left=this->right;
            else parent->right=this->right;
            right->parent=this->parent;
            return;
        }
        else if(right==NULL){
            if(parent->left==this) parent->left=this->left;
            else parent->right=this->left;
            left->parent=this->parent;
            return;
        }
    }
    
    //both children present
    TreeNode* successor = succ_below(); //find the successor below
    if (successor!=NULL){ //move successor to node
        this->JourneyCode=successor->JourneyCode;
        this->price=successor->price;

        successor->rem();//delete successor -> will be done within the first part of the function
    }
    return;
    
}

TreeNode* TreeNode::succ_below(){ //find the successor of the node below the given node, used for deletion
    if (right==NULL) return NULL;

    //get least node in right subtree
    TreeNode* get_least=right;
    for(;get_least->left!=NULL;get_least=get_least->left){}//travel through each left child
    return get_least;
}





// Part II


/* Returns the count of journeys that are at least as expensive
   as lowerPriceBound and at most as expensive as upperPriceBound,
   both bounds included. */
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    if (root==NULL) return 0;
    if (root->left==NULL||root->price<lowerPriceBound){ //left subtree invalid
        int ctbelow=0;
        if (root->right!=NULL){
            root=root->right; //for right child
            ctbelow = countJourneysInPriceBound(lowerPriceBound,upperPriceBound);
            root=root->parent;
        }      
        return ((root->price>=lowerPriceBound && root->price<=upperPriceBound)+ ctbelow);
    }
    if (root->right==NULL||root->price>upperPriceBound){ //right subtree invalid
        root=root->left; //for left child
        int ctbelow = countJourneysInPriceBound(lowerPriceBound,upperPriceBound);
        root=root->parent;
    
        return ((root->price<=upperPriceBound && root->price>=lowerPriceBound)+ ctbelow);
    }
    //root lies in range
    int cnt=1;
    root=root->left; //for left child
    cnt += countJourneysInPriceBound(lowerPriceBound,upperPriceBound);
    root=root->parent;
    root=root->right;//for right child
    cnt += countJourneysInPriceBound(lowerPriceBound,upperPriceBound);
    root=root->parent;

    return cnt;
}

/*  Store the current tree in a file called filename.  You should
    store using a scheme that uses no more disk space than that
    required to store all elements in the BST, plus perhaps a small
    constant times the number of elements.  You should also store
    in a manner such that your implementation of customLoad is as
    memory and time efficient as possible. */
void BST::customStore(string filename) { 
    ofstream file(filename,ios::out); //open file, overwrite mode
        if(root==NULL) file<<int(NS)<<' '; //insert sentinel character if NULL
        else root->store(file); // call store helper function
    file.close();
    return; 
}
	
/*  While loading a tree from a file written by customStore, we
    can have one of two modes of loading.  We could either ask
    for the entire tree to be loaded or only the left subtree of
    the root (if it exists) to be loaded.  The loadMode flag
    takes one of two prices LOAD_FULL_BST or LOAD_LEFT_SUBTREE,
    that are #defined in BST.cpp.
    If loadMode is LOAD_FULL_BST, customLoad should load the
    entire BST that was stored in filename using customStore.
    If loadMode is LOAD_LEFT_SUBTREE, customLoad should load
    only the left subtree of the root of the BST that was
    stored in filename using customStore.
    Your implementation of customLoad should be efficient --
    its time and space complexity should be linear in the size
    of the tree that is being loaded.  So, for example, if the
    left sub-tree of the root is small compared to the right
    sub-tree, customLoad's time and space complexity should
    be small even though the entire BST may be very large. */
 
void BST::customLoad (int flag, string filename) { 
    ifstream file(filename);//open file to read
    if (flag==LOAD_FULL_BST){ //start reading from start
        root=read(file);
    }
    else if (flag==LOAD_LEFT_SUBTREE){ //just increment root characters to just print left subtree!
        int first;
        file >> first;
        //to handle null root
        if (first!=NS) 
            file >> first;
            root=read(file);
    }
    file.close();
    return; 
}

//helper function to store tree to file
void TreeNode::store(ofstream& file){
    //preorder
    file<<this->JourneyCode<<' '<<this->price<<' ';

    //left subtree
    if (this->left==NULL)
        file<<int(NS)<<' ';
    else
        this->left->store(file);
 
    //right subtree
    if (this->right==NULL)
       file<<int(NS)<<' ';
    else
        this->right->store(file);

    return;
}

//helper function to read tree from file;
//returns the pointer to the created node
TreeNode* BST::read(ifstream& file){
    int first, second;
    file >> first;
    if (first==NS) return NULL; //null root
    file >> second;
    TreeNode* toreturn = new TreeNode(first,second);//make pointer for node

    //for left subtree, null for now
    {TreeNode* child = read(file);
    if (child!=NULL){//set child/parent pointers for the new connections
        toreturn->left=child; 
        child->parent=toreturn;
    }
    }
    //for right subtree, null for now
    {TreeNode* child = read(file);
    if (child!=NULL){//set child/parent pointers for the new connections
        toreturn->right=child;
        child->parent=toreturn;
    }
    }

    return toreturn;

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