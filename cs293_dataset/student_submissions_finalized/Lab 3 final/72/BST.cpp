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
ofstream outfile;

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST(){root = NULL; }
BST::BST(TreeNode *root){this->root = root; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    if(find(JourneyCode,price))return false;
    TreeNode *z=new TreeNode(JourneyCode,price);
    TreeNode *y = NULL;
    TreeNode *x = root;
    while( !(x == NULL)){
        
        y = x;
        if(price < x->price)x = x->left;
        else x = x->right;
    }
    
    z->parent = y;
    if(y == NULL)root = z;
    else if(z->price < y->price)y->left=z;
    else y->right = z;

    return true;}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
 
    if(root == NULL)return false;
 
    TreeNode *x = root;
    TreeNode *y = x;
    while( !(x == NULL)){
        
        y = x;
        if(price == x->price)break;
        else if(price < x->price)x=x->left;
        else x=x->right;
    }
    if(x == NULL)return false;
   
    if((x->price==price) || (x->JourneyCode==JourneyCode))return true;

    return false;
    }
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    if(!find(JourneyCode,price))return false; 
    TreeNode *a = root;
    while( price != a->price){
        if(price < a->price)a=a->left;
        else a=a->right;
    }
    TreeNode *z=a;
    TreeNode *y;
    bool var = (root == z);
    if((z->left==NULL)&&(z->right==NULL)){
        if(var){
            root=NULL;
            return true;}
        y = z->parent;
        if(y->left==z)y->left=NULL;
        else y->right=NULL;
        return true;
    }
    else if((z->left==NULL)||(z->right==NULL)){
       
        
        TreeNode *x;
        if(z->left==NULL)x=z->right;
        else x=z->left;
        if(var){
            root=x;
            x->parent=NULL;
            return true;}
        y = z->parent;
        x->parent = z->parent;
        
        if(y->left==z)y->left=x;
        else y->right=x;
        
        
        
        return true;
    }
    else{
        
        y = z->right;
        while (y->left != NULL)
        {
            y=y->left;
        }
        if(y->right != NULL){
            TreeNode *e=y->parent;
            TreeNode *f=y->right;
            if(e->left==y)e->left=f;
            else e->right=f;
            f->parent=e;
        }
        if(z->parent != NULL){
            TreeNode *p = z->parent;
            if(p->left==z)p->left=y;
            else p->right=y;
            y->parent=p;
        }
        (z->left)->parent=y;
        (z->right)->parent=y;
        y->left=z->left;
        y->right=z->right;
        
        if(var){
            root=y;
            y->parent=NULL;
            return true;}
        y->parent=z->parent;
        return true;
    }
    return false;
    }
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

//PreorderTraverse function
void BST::preorderTraverse(TreeNode *base){
    if(base == NULL)return;
    else{
        cout << base->JourneyCode <<endl;
        preorderTraverse(base->left);
        preorderTraverse(base->right);
    }
    return;
}

//PostorderTraverse function
void BST::postorderTraverse(TreeNode *base){
    if(base == NULL)return;
    else{
        postorderTraverse(base->left);
        postorderTraverse(base->right);
        cout << base->JourneyCode <<endl;
    }
    return;
}

//inorderTraverse function
void BST::inorderTraverse(TreeNode *base){
    if(base == NULL)return;
    else{
        inorderTraverse(base->left);
        cout << base->JourneyCode <<endl;
        inorderTraverse(base->right);
    }
    return;
}

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal == 0){
        preorderTraverse(root);
    }
    else if(typeOfTraversal == 1){
        postorderTraverse(root);
    }
    else if(typeOfTraversal == 2){
        inorderTraverse(root);
    }
    return;
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    if(root == NULL)return 0;
    TreeNode *x = root;
    while(x->left != NULL){
        x = x->left;
    }
    return x->price;; }

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
void BST::myCount(int lb, int ub, TreeNode *base, int &cnt){
    if(base == NULL)return;
    else{
        myCount(lb, ub, base->left,cnt);
        if(base->price>=lb && base->price<=ub)cnt++;
        myCount(lb, ub, base->right,cnt);
    }
    return;
}

//I defined a new function myCount to assist the countJourneyPriceBound function so that I can implement it recursively

int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    int cnt=0;
    myCount(lowerPriceBound,upperPriceBound,root,cnt);
    return cnt; }

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::myStore(TreeNode *node){
    outfile<<"-"<<" "<<node->JourneyCode<<" "<< node->price<<endl;
    if(node->left!=NULL){
        outfile<<"("<<endl;
        myStore(node->left);
        outfile<<")"<<endl;
    }
    if(node->right!=NULL){
        outfile<<"{"<<endl;
        myStore(node->right);
        outfile<<"}"<<endl;
    }
}

//I used myStore to implement customStore recursively which stores 
//each node with it's characters determining whether it goes to left subtree or right subtree

void BST::customStore(string filename) { 
    
    outfile.open(filename);
    outfile<<"-"<<" "<<root->JourneyCode<<" "<< root->price<<endl;
    if(root->left!=NULL){
        outfile<<"("<<endl;
        myStore(root->left);
        outfile<<")"<<endl;
    }
    if(root->right!=NULL){
        outfile<<"{"<<endl;
        myStore(root->right);
        outfile<<"}"<<endl;
    }
    outfile.close();
    return; }
	
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
 

//This loads either the full tree or only the left subtree accordingly 
//I implemented it in linear time by using a Stack to store my parent nodes accordingly
void BST::customLoad (int flag, string filename) { 
    ifstream infile;
    infile.open(filename);
    vector<TreeNode*> stacc;
    if(flag==3){
        while(true){
            char c;
            infile >> c;
            if(infile.eof())break;
            if(c == '-'){
                int jc=0;
                int pr=0;
                infile>>jc;
                infile>>pr;
                TreeNode *x = new TreeNode(jc,pr);
                if(stacc.empty()==true){
                    root=x;
                    x->parent=NULL;
                    }
                stacc.push_back(x);
            }
            else if(c == '('){
                char sen;
                infile >> sen;
                if(sen=='-'){
                    TreeNode *par=stacc.back();
                    int jc=0;
                    int pr=0;
                    infile>>jc;
                    infile>>pr;
                    TreeNode *x = new TreeNode(jc,pr);
                    par->left=x;
                    x->parent=par;
                    stacc.push_back(x);
                }
            }
            else if(c == '{'){
                char sen;
                infile >> sen;
                if(sen=='-'){
                    TreeNode *par=stacc.back();
                    int jc=0;
                    int pr=0;
                    infile>>jc;
                    infile>>pr;
                    TreeNode *x = new TreeNode(jc,pr);
                    par->right=x;
                    x->parent=par;
                    stacc.push_back(x);
                }
            }
            else if(c == ')'){
                stacc.pop_back(); 
            }
            else if(c == '}'){
                stacc.pop_back();
            }
        }
    }
    else if(flag==4){
        char st;
        infile>>st;
        int stjc=0;
        int stpr=0;
        infile>>stjc;
        infile>>stpr;
        int index=0;
        if(infile.eof())return;
        char tre;
        infile>>tre;
        if(tre == '{')return;
        if(tre == '(')index++;
        while(true){
            char c;
            infile >> c;
            if(infile.eof())break;
            if(c == '-'){
                int jc=0;
                int pr=0;
                infile>>jc;
                infile>>pr;
                TreeNode *x = new TreeNode(jc,pr);
                if(stacc.empty()==true){
                    root=x;
                    x->parent=NULL;
                    }
                stacc.push_back(x);
            }
            else if(c == '('){
                index++;
                char sen;
                infile >> sen;
                if(sen=='-'){
                    TreeNode *par=stacc.back();
                    int jc=0;
                    int pr=0;
                    infile>>jc;
                    infile>>pr;
                    TreeNode *x = new TreeNode(jc,pr);
                    par->left=x;
                    x->parent=par;
                    stacc.push_back(x);
                }
            }
            else if(c == '{'){
                char sen;
                infile >> sen;
                if(sen=='-'){
                    TreeNode *par=stacc.back();
                    int jc=0;
                    int pr=0;
                    infile>>jc;
                    infile>>pr;
                    TreeNode *x = new TreeNode(jc,pr);
                    par->right=x;
                    x->parent=par;
                    stacc.push_back(x);
                }
            }
            else if(c == ')'){
                stacc.pop_back(); 
                index--;
                if(index==0)break;
            }
            else if(c == '}'){
                stacc.pop_back();
            }
        }
    }
    infile.close();
    return; }


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
