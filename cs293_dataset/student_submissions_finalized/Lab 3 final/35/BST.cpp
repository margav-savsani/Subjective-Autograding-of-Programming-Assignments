#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stack>

using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST(){ 
    this->root = nullptr; 
    }
BST::BST(TreeNode *root){
    this->root = root;
    }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    if(this->find(JourneyCode,price)){return false;}  
    TreeNode * New = new TreeNode();
    New->JourneyCode = JourneyCode;
    New->price = price;
    New->parent = nullptr;
    TreeNode * y = nullptr;
    TreeNode * x = this->root;
    while(x != nullptr){
        y = x;
        if(price < x->price){
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    New->parent = y;
    if( y == nullptr){
        this->root = New;
    }
    else if(price < y->price){
        y->left = New;
    }
    else if(price > y->price){
        y->right = New;
    }
    return true;
    }

    

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    if(this->root == nullptr){  
        return false;
    }
    TreeNode* x = this->root;
    while((x!= nullptr)&&(x->price != price)){
        if(x->price > price){x = x->left;}
        else{x = x->right;}
    }
    if(x == nullptr){
        return false;
    }
    else if((x->price == price)&&(x->JourneyCode == JourneyCode)){
        
        return true;
    }
    else {return false;};
    }
	
TreeNode* BST :: superfind(int JourneyCode, int price){
    if(this->root == nullptr){
        return nullptr;
    }
    TreeNode* x = this->root;
    while((x!= nullptr)&&(x->price != price)){
        if(x->price > price){x = x->left;}
        else{x = x->right;}
    }
    if(x == nullptr){
        return nullptr;
    }
    else if((x->price == price)&&(x->JourneyCode == JourneyCode)){
        return x;
    }
    else return nullptr;
}


// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    TreeNode * x = this->superfind(JourneyCode,price);
    if(x == nullptr) return false; 
    if((x->left == nullptr)&&(x->right == nullptr)){
        if(x->parent == nullptr){this->root = nullptr;}
        else if(x->parent->price > x->price){
            x->parent->left = nullptr;
        }
        else{x->parent->right = nullptr;}
        return true;
    }
    if((x->left == nullptr)&&(x->right != nullptr)){
        if(x->parent == nullptr){
            this->root = x->right;
            x->right->parent = nullptr;
        }
        else if(x->parent->price > x->price){
            x->parent->left = x->right;
            x->right->parent = x->parent;
        }
        else if(x->parent->price < x->price){
            x->parent->right = x->right;
            x->right->parent = x->parent;
        }
        return true;
    }
    if((x->left != nullptr)&&(x->right == nullptr)){
        if(x->parent==nullptr){
            this->root = x->left;
            x->left->parent = nullptr;
        }
        else if(x->parent->price > x->price){
            x->parent->left = x->left;
            x->left->parent = x->parent;
        }
        else if(x->parent->price < x->price){
            x->parent->right = x->left;
            x->left->parent = x->parent;
        }
        return true;
    }
    if((x->left != nullptr)&&(x->right != nullptr)){
        TreeNode * z = predecessor(x);
        if(z->left != nullptr){
            z->left->parent = z->parent;
            z->parent->right = z->left;
            if(x->parent->left = x){
                x->parent->left = z;
            }
            else if(x->parent->right = x){
                x->parent->right = z;
            }
            x->left->parent = z;
            x->right->parent = z;
        }
        else{
            if(x->left != z){
                z->parent->right = nullptr;
                x->left->parent = z;
                x->right->parent = z;
                if(x->parent->left = x){
                    x->parent->left = z;
                }
                else if(x->parent->right = x){
                    x->parent->right = z;
                }
            }
            else{
            x->right->parent = z;
            if(x->parent->left = x){
                x->parent->left = z;
            }
            else if(x->parent->right = x){
                x->parent->right = z;
            }
            }
        }
        return true;
    }
    return false;
    }
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line
void BST :: visit1(TreeNode * T){
        if(T != nullptr){
            cout << T->JourneyCode << endl;
            visit1(T->left);
            visit1(T->right);
            return;
        }
        return;
        }
void BST :: visit2(TreeNode * T){
        if(T != nullptr){
            visit2(T->left);
            visit2(T->right);
            cout << T->JourneyCode << endl; 
            return;
        }
            return;
        }
void BST :: visit3(TreeNode * T){
        if(T != nullptr){
            visit3(T->left);
            cout << T->JourneyCode << endl;
            visit3(T->right);
            return;
        }
        return;
        }     

void BST :: supervisit(TreeNode * T,int lowerPriceBound, int upperPriceBound,int &I){            
        if(T != nullptr){
            supervisit(T->left,lowerPriceBound,upperPriceBound,I);
            if(T->price >= lowerPriceBound && T->price <= upperPriceBound){
                I++;
            }
            supervisit(T->right,lowerPriceBound,upperPriceBound,I);
            return;
        }
        return;
        }      

void BST::traverse(int typeOfTraversal) {
    TreeNode * x = this->root;
    if(typeOfTraversal == 0){
        visit1(x);
    }
    else if(typeOfTraversal == 1){   
        visit2(x);
    }
    else if(typeOfTraversal == 2){
        visit3(x);
    }
    return;
    }

// Returns the price of the cheapest journey
int BST::getMinimum() {
    if(this->root == nullptr){
    return 0;
    }
    TreeNode * x = this->root;
    while(x->left != nullptr){
        x = x->left;
    }
    return x->price;
    }

TreeNode * BST :: successor(TreeNode * T){
    if(T->right == nullptr){
        return nullptr;
    }
    TreeNode * x = T->right;
    while(x->left != nullptr){
        x = x->left;
    }
    return x;
}
TreeNode * BST :: predecessor(TreeNode * T){
    if(T->left == nullptr){
        return nullptr;
    }
    TreeNode * x = T->left;
    while(x->right != nullptr){
        x = x->right;
    }
    return x;
}


// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    int I=0;
    supervisit(this->root,lowerPriceBound,upperPriceBound,I);
    return I;
    }

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST :: superpreorder(TreeNode * T,ofstream &file){
        if(T != nullptr){           
            if(T->parent != nullptr){
            if(T->parent->left == T){
                if(T->parent->right == nullptr){
                    file << "#" << " ";
                }
                else {file << "!" << " ";}
            }
            else {file << "@" << " ";}
            }
            file << " " << T->JourneyCode << " " << T->price << endl;
            if(T->left == nullptr && T->right == nullptr){
                file <<"$" << " " ;
                // $ represent that the current node is a leaf
            } 
            if(T->left != nullptr){superpreorder(T->left,file);}
            if(T->right != nullptr){superpreorder(T->right,file);}
            return;
        }
        return;
        }
void BST::customStore(string filename) { 
    ofstream file;
    file.open(filename);
    superpreorder(root,file);
    file.close();
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
    ifstream file;
    file.open(filename);
    TreeNode *currnode=new TreeNode;
    stack<TreeNode*> StackNoRight;
    StackNoRight.push(nullptr);
    file>>currnode->JourneyCode;
    file>>currnode->price; 
    root=currnode;
    string val;  
    //LOAD_FULL_BST Case
    while(file>>val){
        if(val == "!"){
            int Jprice,Jcode;
            file>>Jcode>>Jprice;
            TreeNode *temp=new TreeNode(Jcode,Jprice,nullptr,nullptr,currnode);
            currnode->left=temp;
            currnode=currnode->left;
        }
        if(val == "@"){
            int Jprice,Jcode;
            file>>Jcode>>Jprice;
            TreeNode *temp=new TreeNode(Jcode,Jprice,nullptr,nullptr,currnode);
            currnode->right=temp;
            currnode=currnode->right;
        }
        if(val == "#"){
            int Jprice,Jcode;
            file>>Jcode>>Jprice;
            TreeNode *temp=new TreeNode(Jcode,Jprice,nullptr,nullptr,currnode);
            currnode->left=temp;    
            StackNoRight.push(currnode);
            currnode=currnode->left;
        }
        if(val == "$"){
            currnode=currnode->parent;
        }
        
        while((currnode->right!=nullptr)||StackNoRight.top()==currnode){
            if(StackNoRight.top()==currnode){
                StackNoRight.pop();
            }
            currnode=currnode->parent;
            if(currnode==nullptr) break;
        }
    }
    file.close();
    //LOAD_LEFT_SUBTREE Case
    if(flag == 4){
        root = root->left;
        if(root!=nullptr) root->parent=nullptr;
        return;
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

        result.push_back(isLeft ? "├──" : "└──" );

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

