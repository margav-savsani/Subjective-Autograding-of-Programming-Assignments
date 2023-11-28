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
    root = new TreeNode();     
}
BST::BST(TreeNode *root){
    this->root = root;     
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    TreeNode *x = root;    
    TreeNode *y = x;
    if(root->price==0){
        root->price = price;
        root->JourneyCode = JourneyCode;
        return true;        
    }
    int money=root->price;
    while(x!=nullptr){ 
        if(x->JourneyCode==JourneyCode)return false;
        if(money<price){
            y=x;
            if(y->right==nullptr){
                x = new TreeNode(JourneyCode,price);
                y->right = x;
                break;
            }           
            x=y->right;
            money=x->price;             
        }
        else if(money==price)return false;
        else{
            y=x;
            if(y->left==nullptr){
                x = new TreeNode(JourneyCode,price);
                y->left = x;
                break;
            } 
            x=y->left;
            money=x->price;
        }
    }  
    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    TreeNode *x = root;
    int money = root->price;
    TreeNode *y = x;
    while((x->JourneyCode!=JourneyCode)&&(x!=NULL)){
        if(money<price){
            y=x;
            if(y->right==NULL)break;
            x=y->right;
            money=x->price;
        }
        else{
            y=x;
            if(y->left==NULL)break;
            x=y->left;
            money=x->price;
        }
    }
    if(x->JourneyCode==JourneyCode)return true;
    return false; 
}

TreeNode* BST:: successor(TreeNode x){
    if(x.right!=NULL){
        TreeNode *z = x.right;
        TreeNode *k = z;
        while(true){
            k=z;
            if(k->left == nullptr) break;
            z=k->left;
        }
        return k; 
    }
    TreeNode *y = x.parent;
    while((y!=NULL)&&(x.JourneyCode==(y->right)->JourneyCode)){
        x=*y;
        y=y->parent;
    }   
    return y;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    if(!find(JourneyCode,price))return false; 
    TreeNode *x = root;
    TreeNode *y = x;
    int money = root->price;
    while((x->JourneyCode!=JourneyCode)&&(x!=NULL)){
        if(money<price){
            y=x;
            x=y->right;
            money=x->price;
        }
        else{
            y=x;
            x=x->left;
            money=x->price;
        }
    }
    if((x->left==NULL)&&(x->right==NULL)){
        if(y->right==x)y->right=NULL;
        else y->left=NULL;
        return true;
       
    }
    if((x->left==NULL)&&(x->right!=NULL)){
        if(y->right==x)y->right=x->right;
        else if(y->left==x)y->left=x->right;
        else root=x->right; 
        return true; 
    }
    if((x->left!=NULL)&&(x->right==NULL)){
        if(y->right==x)y->right=x->left;
        else if(y->left==x) y->left=x->left;
        else root=x->left;
        return true;      
    }
    if((x->left!=NULL)&&(x->right!=NULL)){
        TreeNode *z = successor(*x);
        remove(z->JourneyCode,z->price);
        if(y->right==x)y->right=z;
        else if(y->left==x) y->left=z;
        else root=z;
        z->parent = x->parent;
        z->left = x->left;
        z->right = x->right;
        return true;
    }
return false;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line
void BST :: preorder(TreeNode *v){
    if(v==NULL)return;
    else{
        cout<<v->JourneyCode<<endl;
        preorder(v->left);
        preorder(v->right);
    }
}
void BST :: postorder(TreeNode *v){
    if(v==NULL)return;
    else{
        postorder(v->left);
        postorder(v->right);
        cout<<v->JourneyCode<<endl;
    }
}
void BST :: inorder(TreeNode *v){
    if(v==NULL)return;
    else{
        inorder(v->left);
        cout<<v->JourneyCode<<endl;
        inorder(v->right);        
    }
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
    return;
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode *x = root;   
    TreeNode *y=x;
    while(true){
         y=x;
         if(y->left == nullptr) break;
         x=y->left;
    }
    return y->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::money(int lowerPriceBound, int upperPriceBound,TreeNode *v){
    int count=0;
    if(v==NULL)return count;
    if((v->left==NULL)&&(v->right==NULL)){
        if((lowerPriceBound<=v->price)&&(v->price<=upperPriceBound))count++;
        return count;        
    }
    else if((v->left==NULL)&&(v->right!=NULL)){
        if((lowerPriceBound<=v->price)&&(v->price<=upperPriceBound))count++;
        count=count+money(lowerPriceBound,upperPriceBound,v->right);
        return count;
    }    
    else if((v->left!=NULL)&&(v->right==NULL)){
        if((lowerPriceBound<=v->price)&&(v->price<=upperPriceBound))count++;
        count=count+money(lowerPriceBound,upperPriceBound,v->left);
        return count;
    }    
    else{
        if((lowerPriceBound<=v->price)&&(v->price<=upperPriceBound))count++;
        count=count+money(lowerPriceBound,upperPriceBound,v->left);
        count=count+money(lowerPriceBound,upperPriceBound,v->right);
        return count;
    }
    
}
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    return money(lowerPriceBound,upperPriceBound,root);
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::input(ofstream &outfile, TreeNode *v){
    if(v==NULL){
        return;
    }
    else{
        outfile<<v->JourneyCode<<" "<<v->price<<endl; 
        input(outfile,v->left);
        input(outfile,v->right);
    }
    return;
}
void BST::customStore(string filename) { 
   ofstream outfile;
   outfile.open(filename);
   input(outfile,root);
   outfile.close();
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
int j=0,k=0;    
if(flag==3){
    ifstream outfile;
    outfile.open(filename);
    while(true){
        outfile>>j;
        outfile>>k;
        if(outfile.eof())break;
        insert(j,k);
    }
    outfile.close();
    return;
}    
else{
    ifstream outfile;
    outfile.open(filename);
    outfile>>j;
    outfile>>k;
    int l = countJourneysInPriceBound(0,(root->left)->price); 
    for(int i=0;i<l;i++){
        outfile>>j;
        outfile>>k;
        if(outfile.eof())break;
        insert(j,k);
    }
    outfile.close();
    
    return;
}
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