#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include<fstream>

using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4


// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST(){ root  = NULL; }
BST::BST(TreeNode *root){  this->root =  root; root->parent=SENTINAL; SENTINAL->right=root; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    TreeNode* temp1=NULL;                // used to find the location of the parent of the node which is NULL
    TreeNode* temp2=root;                // used to find the location of the node
    while(temp2 != NULL ){   
        if(temp2->JourneyCode != JourneyCode){
           temp1 = temp2;
            if(price < temp1->price){
                temp2 = temp2->left;
            }
            else temp2 = temp2->right; 
        }    
        else break;
    } 
    if(temp2 != NULL){
        return false;    
    }
    else{
        if(temp1 == NULL){           
            root = new TreeNode;
            root->JourneyCode = JourneyCode;
            root->price = price;
            root->parent = SENTINAL;
            SENTINAL->right = root;
        }
        else{
            if(temp1->price > price){                
                temp1->left = new TreeNode;
                temp1->left->JourneyCode = JourneyCode;
                temp1->left->price = price;
                temp1->left->parent = temp1;
            }
            else{
                temp1->right = new TreeNode;
                temp1->right->JourneyCode = JourneyCode;
                temp1->right->price = price;
                temp1->right->parent = temp1;
            }
        }
        return true;
    }
}

// Return the node corresponding the entries.
struct TreeNode* BST::find_node(int JourneyCode, int price){
    TreeNode* temp=root;   
    while(temp != NULL){
        if(temp->price == price && temp->JourneyCode == JourneyCode) break;
        if(price < temp->price) temp = temp->left;
        else temp = temp->right;    
    }
    return temp;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    TreeNode* temp= find_node(JourneyCode,price);      
    if(temp == NULL) return false;
    else return true; 
}
	
// Finds Succesor of the node
struct TreeNode* BST::find_succ(int JourneyCode, int price){
    TreeNode* temp = find_node(JourneyCode, price);
    temp=temp->right;    
    while(temp->left != NULL && temp->price > price){
        temp = temp->left;
    }  
    return temp;
}

// helps in removing an entry
void BST::remove_helper(TreeNode* temp,TreeNode* temp2){
    if(temp->right != temp2){
        if(temp2->right != NULL){
            temp2->parent->left = temp2->right;
            temp2->right->parent = temp2->parent;
        }
        else if(temp2->right == NULL){
            temp2->parent->left = NULL;
        }
        temp2->right = temp->right;
        if(temp->right != NULL)                    
        temp->right->parent = temp2;
    }
    temp2->left = temp->left;
    if(temp->left != NULL)
    temp->left->parent = temp2;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    TreeNode* temp= find_node(JourneyCode,price);        
    if(temp == NULL ){
        return false;
    }    
    else{        
        if(temp->parent->left == temp){
            if(temp->left == NULL && temp->right == NULL){
                temp->parent->left = NULL;
            }
            else if(temp->left == NULL ){
                temp->parent->left = temp->right;
                temp->right->parent = temp->parent;
            }
            else if(temp->right == NULL){
                temp->parent->left = temp->left;
                temp->left->parent = temp->parent;
            }      
            else {           
                TreeNode* temp2 = find_succ(JourneyCode,price);       
                remove_helper(temp,temp2);                              
                temp2->parent = temp->parent;
                temp->parent->left = temp2;                                                                                                                                          
            } 
        }              
        if(temp->parent->right == temp){            
            if(temp->left == NULL && temp->right == NULL){
                temp->parent->right = NULL;
                if(temp == root) root = NULL;
            }
            else if(temp->left == NULL){
                temp->parent->right = temp->right;
                temp->right->parent = temp->parent;
                if(temp == root) root = temp->right;
            }
            else if(temp->right == NULL){
                temp->parent->right = temp->left;
                temp->left->parent = temp->parent;
                if(temp == root) root = temp->left;
            }    
            else{        
                TreeNode* temp2 = find_succ(JourneyCode,price);                 
                remove_helper(temp,temp2);
                temp2->parent = temp->parent;
                temp->parent->right = temp2;   
                if(temp == root) root = temp2;                                                              
            }            
        }       
        return true;
    }
        
}

//Inorder traversel
void BST::Inorder(TreeNode* root){
    if(root == NULL) return;
    else{
        Inorder(root->left);
        cout<<root->JourneyCode<<endl;
        Inorder(root->right);
    }
}

//Post order traversal
void BST::Postorder(TreeNode* root){
    if(root == NULL) return;
    else{
        Postorder(root->left);
        Postorder(root->right);
        cout<<root->JourneyCode<<endl;
    }
}

//Preorder traversel
void BST::Preorder(TreeNode* root){
    if(root == NULL) return;
    else{
        cout<<root->JourneyCode<<endl;
        Preorder(root->left);
        Preorder(root->right);        
    }
}


// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    TreeNode* temp =root;
    if(typeOfTraversal == 0) Preorder(root);
    if(typeOfTraversal == 1) Postorder(root);
    if(typeOfTraversal == 2) Inorder(root);
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    int min;
    TreeNode* temp = root;
    if(temp == NULL) return 0;
    else{
        while(temp->left != NULL){
            temp =temp->left;
        }
        return temp->price; 
    }    
}

// Part II
int BST::counter(TreeNode* root,int a, int b){
    int count;
    if(root==NULL) return 0;
    else if(root->price == a){        
        count=1+counter(root->right,a,b);
    } else if(root->price == b){        
        count=1+counter(root->left,a,b);
    } else if(root->price < a){
        count=counter(root->right,a,b);
    } else if(root->price > b){
        count=counter(root->left,a,b);
    } else{
        count=1+counter(root->left,a,b) + counter(root->right,a,b);
    }
    return count;
}
// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    return counter(root,lowerPriceBound,upperPriceBound); 
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.

void BST::storing(TreeNode* root,ofstream &outfile){     
    if(root == NULL) outfile<<0<<" "<<0<<endl;
    else{
        outfile<<root->price<<" "<<root->JourneyCode<<endl;
        storing(root->left,outfile);
        storing(root->right,outfile);        
    }
    return;
}

void BST::customStore(string filename) {     
    ofstream outfile;
    outfile.open(filename);
    storing(root,outfile);
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

struct TreeNode* BST::loader(ifstream &infile){
    int a,b;
    infile>>a>>b;
    TreeNode* root = new TreeNode;    
    if(a != 0 && b!= 0){
        root->price = a;
        root->JourneyCode = b;
    } 
    if(a == 0 && b==0){
        root = NULL;
    } else {
        root->left=loader(infile);
        if(root->left != NULL) root->left->parent=root;        
        root->right=loader(infile);
        if(root->right != NULL) root->right->parent=root;
    }
    return root;
}
void BST::customLoad (int flag, string filename) { 
    TreeNode* req_root;
    ifstream infile;
    infile.open(filename);
    if(flag == 3){    
        req_root = loader(infile);    
    }
    if(flag == 4){
        int a,b;
        infile>>a>>b;
        req_root = loader(infile); 
    }
    infile.close();
    BST req_bst(req_root);
    return; 
}

// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
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