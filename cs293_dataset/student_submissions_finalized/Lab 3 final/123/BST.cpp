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
    root = new TreeNode();
    root  = NULL;
}
BST::BST(TreeNode *r){
    root = new TreeNode();
    root = r;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    if (find(JourneyCode,price)){
        return false;
    }
    else{
        TreeNode *y = new TreeNode();
        y = NULL;
        TreeNode *x = new TreeNode();
        x = root;
        
        while(x != NULL){
            y = x;
            if(price < x->price){
                x = x->left;
            }
            else{
                x = x->right;
            }
        }
        TreeNode *newnode = new TreeNode(JourneyCode,price,NULL,NULL,y);
        if(y == NULL){
            root = newnode;
        }
        else if (price < y->price)
        {
            y->left = newnode;
        }
        else{
            y->right = newnode;
        }
        return true;
    }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    //recursive code
    TreeNode *x = new TreeNode();
    x = root;
    if(x == NULL){
        return false;
    }
    if(price == x->price){
        cout<<x->price;
        return true;
    }
    else{
        if(price < x->price){
            x = x->left;
            BST leftTree(x);
            return leftTree.find(JourneyCode, price);
        }
        else{
            x = x->right;
            BST rightTree(x);
            return rightTree.find(JourneyCode,price);
        }
    }
 }
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    TreeNode *x = new TreeNode();
    x = root;
    if(x == NULL){
        return false;
    }
    if(price == x->price){
        if((x->left == NULL) & (x->right == NULL)){
            TreeNode *par = new TreeNode(); //parent of x
            par=x->parent;
            if(par->price < x->price){
                par->right = NULL;
                x->parent = NULL;
                return true;
            }
            else
            {
                par->left = NULL;
                x->parent = NULL;
                return true;
            }
            
        }
        else if ((x->left == NULL) || (x->right == NULL))
        {
            TreeNode *par =  new TreeNode(); //parent of x
            par=x->parent;
            TreeNode *chi =  new TreeNode(); //single child of x
            chi = NULL;
            if (x->left == NULL) //if chi is to the right of x
            {
                chi=x->right;     //saving child  
                x->right = NULL;    //seperating from parent
            }
            else{           //if chi is to the left of x
                chi=x->left;  //saving child
                x->left = NULL;     //seperating from parent
            }
            if(par != NULL){
                if(par->left == x ){     //if x is to left of par
                par->left=chi;     //child must be less than par, so assign par's left child's role to chi   
                chi->parent =par;  //tell child that par is his parent
                x->parent = NULL; //seperate x from his parents too
                }
                else if(par->right == x){       //if x is to right of par
                par->right=chi;    //chi must be greater than p
                chi->parent=par;  //tell chi that par is his parent 
                x->parent = NULL;       //seperate x from hiss parent
                }
            }
            else{
                root = chi;
                chi->parent = NULL; 
            }
        }
        else{ //if x has 2 children
            TreeNode* suc =  new TreeNode();
            TreeNode* suc_chi =  new TreeNode();
            TreeNode* suc_par =  new TreeNode();
            suc_par=suc->parent;
            suc_chi=suc->right;
            suc=this->successor(x);
            suc_par->left = suc_chi;
            suc_chi->parent = suc_par;
            x = suc;
        }
        return true;
    }
    else{
        if(price < x->price){
            x=x->left;
            BST leftTree(x);
            return leftTree.remove(JourneyCode, price);
        }
        else{
            x=x->right;
            BST rightTree(x);
            return rightTree.remove(JourneyCode,price);
        }
    }
 }
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal == 0){
        if(root == NULL){
            return;
        }
        else{
            cout<<root->JourneyCode<<endl;
            BST leftTree(root->left);
            BST rightTree(root->right);
            leftTree.traverse(0);
            rightTree.traverse(0);
        }
    }
    if(typeOfTraversal == 1){
        if(root == NULL){
            return;
        }
        else{
            BST leftTree(root->left);
            BST rightTree(root->right);
            leftTree.traverse(0);
            rightTree.traverse(0);
            cout<<root->JourneyCode<<endl;
        }
    }
    if(typeOfTraversal == 2){
        if(root == NULL){
            return;
        }
        else{
            BST leftTree(root->left);
            BST rightTree(root->right);
            leftTree.traverse(0);
            cout<<root->JourneyCode<<endl;
            rightTree.traverse(0);
        }
    }
 }

// Returns the price of the cheapest journey
int BST::getMinimum() { 
    if(root->left == NULL){
        return root->price;
    }
    else{
        BST leftTree(root->left);
        return leftTree.getMinimum();
    }
}

// Returns the root with price of the cheapest journey
TreeNode* BST::getMinimumRoot(){
    if(root->left == NULL){
        return root;
    }
    else{
        BST leftTree(root->left);
        return leftTree.getMinimumRoot();
    }    
}

//Returns successor of given TreeNode as argument
TreeNode* BST::successor(TreeNode* x){
    if (x->right != NULL){
        BST rightTree(x->right);
        return rightTree.getMinimumRoot();
    }
    TreeNode* suc_par =  new TreeNode();
    suc_par = x->parent;
    while ((suc_par != NULL) & (x == suc_par->right))
    {
        TreeNode* p = new TreeNode();
        p=suc_par->parent; 
        x = suc_par;
        suc_par = p;
    }
    return suc_par;
}

void nodeCopy(TreeNode *org, TreeNode *doop){
    doop->JourneyCode = org->JourneyCode;
    doop->left = org->left;
    doop->parent = org->parent;
    doop->price = org->price;
    doop->right = org->right;
    return;
}

// Part II

//Create vector of all TreeNodes in INORDER 
vector<TreeNode*> BST::in_vec(TreeNode* x){
    vector<TreeNode*> v;
    if(x == NULL){
        return v;
    }
    else{
        v.push_back(x);
        vector<TreeNode*> l_v;
        l_v = in_vec(x->left);
        vector<TreeNode*> r_v;
        r_v = in_vec(x->right);
        vector<TreeNode*> fin(l_v);
        fin.insert(l_v.end(), v.begin(), v.end());
        fin.insert(fin.end(), r_v.begin(), r_v.end());
        return fin;
    }
}

//Create vector of all TreeNodes in PREORDER 
vector<TreeNode*> BST::pre_vec(TreeNode* x){
    vector<TreeNode*> v;
    if(x == NULL){
        return v;
    }
    else{
        v.push_back(x);
        vector<TreeNode*> l_v;
        l_v = pre_vec(x->left);
        vector<TreeNode*> r_v;
        r_v = pre_vec(x->right);
        vector<TreeNode*> fin(v);
        fin.insert(v.end(), l_v.begin(), l_v.end());
        fin.insert(fin.end(), r_v.begin(), r_v.end());
        return fin;
    }
}



// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    int l_index = 0;
    int h_index = 0;
    vector<TreeNode*> v;
    v = in_vec(root);
    while(true){
        if(v[l_index]->price <= lowerPriceBound){
            l_index++;
            h_index++;
            continue;
        }
        if(v[h_index]->price <= upperPriceBound){
            h_index++;
        }
        else{
            break;
        }
    }
    int count = h_index - l_index;
    return count;
 }

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) { 
    ofstream Tree(filename);
    vector<TreeNode*> v;
    v = pre_vec(root);
    for(int i = 0; i<(int)v.size(); i++){
        string jour = to_string(v[i]->JourneyCode);
        string pri = to_string(v[i]->price);
        string item = jour + "-" + pri;
        Tree << item;
    }
    Tree.close();
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
    if(flag == LOAD_FULL_BST){
        ifstream Tree(filename);
        string jour_pri;
        while (getline(Tree, jour_pri))
        {
            int n = jour_pri.length();
 
            // declaring character array
            char char_array[n + 1];
 
            // copying the contents of the
            // string to char array
            strcpy(char_array, jour_pri.c_str());
            char *token = strtok(char_array, "-");
            
            while (token != NULL)
            {
                int a = atoi(token);
                token = strtok(NULL, "-");
                int b = atoi(token);
                insert(a,b);
            }
        }  
    }
    else if(flag == LOAD_LEFT_SUBTREE){
        ifstream Tree(filename);
        string jour_pri;
        while (getline(Tree, jour_pri))
        {
            int n = jour_pri.length();
 
            // declaring character array
            char char_array[n + 1];
 
            // copying the contents of the
            // string to char array
            strcpy(char_array, jour_pri.c_str());
            char *token = strtok(char_array, "-");
            
            while (token != NULL)
            {
                int a = atoi(token);
                token = strtok(NULL, "-");
                int b = atoi(token);
                insert(a,b);
            }
        }
        remove(root->JourneyCode,root->price);  
    }
    return;
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

