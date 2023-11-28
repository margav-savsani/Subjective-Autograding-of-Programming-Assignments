#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4


// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS
TreeNode* TreeMinimum(TreeNode* x){
    while(x->left != nullptr){
        x =x->left;
    }
    return x;
}

TreeNode* BST::TreeSuccessor(TreeNode* x){
    if(x->right != nullptr){
        return TreeMinimum(x->right);
    }
    TreeNode* y = x->parent;
    while (y != nullptr and x == y->right){
        x = y;
        y = y->parent;
    }
    return y;
}

BST::BST(){
    root=new TreeNode;
}

BST::BST(TreeNode *root){
    this->root=root;
}

TreeNode* BST::search(int JourneyCode, int price){
    TreeNode* x;
    x=root;
    while (x != nullptr){
        if(price ==x->price && JourneyCode == x->JourneyCode){
            return x;
        }
        if (price < x->price){
            x = x->left;
        }
        else{
            x=x->right;
        }
    }
    return x;
}

bool BST::insert(int JourneyCode,int price){ 
    TreeNode* z=new TreeNode(JourneyCode,price);
    if(root->price==0){
        root=z;
        return true;
    }
    TreeNode* x=root;
    bool left=false;
    while (x!=nullptr){
        if(price==x->price){
            return false;
        }
        if(price<x->price){
            if(x->left==nullptr){
                left=true;
                break;
            }
            x=x->left;
        }
        else{
            if(x->right==nullptr){
                break;
            }
            x=x->right;
        }
    }
    if(left){
        x->left=z;
        z->parent=x;
    }
    else{
        x->right=z;
        z->parent=x;
    }
    if(price>x->price){
        x->right=z;
        z->parent=x;
    }
    else{
        x->left=z;
        z->parent=x;
    }
    return true;
}

bool BST::find(int JourneyCode, int price) { 
    TreeNode* x=search(JourneyCode,price);
    if(x==nullptr){
        return false;
    }
    return true;
}

bool BST::remove(int JourneyCode, int price) {
    TreeNode* z;
    z=search(JourneyCode,price);
    if(z==nullptr){
        return false;
    }
    if((z->left == nullptr)&&( z->right == nullptr)){
        if(z->parent->left==nullptr){
            z->parent->right=nullptr;
        }
        else if(z->parent->left==z){
            z->parent->left=nullptr;
        }
        else if(z->parent->left==z){
            z->parent->left=nullptr;
        }
        else{
            z->parent->right=nullptr;
        }
        return true;
    }
    else if(z->left == nullptr){
        if(z->parent->left==z){
            z->parent->left=z->right;
        }
        else{
            z->parent->right=z->right;
        }
        return true;
    }
    else if( z->right == nullptr){
        if(z->parent->left==z){
            z->parent->left=z->left;
        }
        else{
            z->parent->right=z->left;
        }
        return true;
    }
    else{
        TreeNode* y;
        y = TreeSuccessor(z);
        z->price = y->price;
        z->JourneyCode=y->JourneyCode;
        if((y->left == nullptr)&&( y->right == nullptr)){
            if(y->parent->left==y){
                y->parent->left=nullptr;
            }
            else{
                y->parent->right=nullptr;
            }
            return true;
        }
        else if(y->left == nullptr){
            if(y->parent->left==y){
                y->parent->left=y->right;
            }
            else{
                y->parent->right=y->right;
            }
            return true;
        }
        else if( y->right == nullptr){
            if(y->parent->left==y){
                y->parent->left=y->left;
            }
            else{
                y->parent->right=y->left;
            }
            return true;
        }
        return true;
    }
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line
void preorder(TreeNode* t){
    if (t == nullptr){return;}
    else{
        TreeNode* tn=t;
        cout<<t->JourneyCode;
        preorder(tn->left);
        preorder(tn->right);
    }
}
void postorder(TreeNode* t){
    if (t == nullptr){return;}
    else{
        TreeNode* tn=t;
        postorder(tn->left);
        postorder(tn->right);
        cout<<t->JourneyCode;
    }
}
void inorder(TreeNode* t){
    if (t== nullptr){
        return;
    }
    else
    {
        TreeNode* tn=t;
        inorder(tn->left);
        cout<<t->JourneyCode;
        inorder(tn->right);
    }
}

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal==0){
        TreeNode* t=root;
        preorder(t);
    }
    if(typeOfTraversal==1){
        TreeNode* t=root;
        postorder(t);
    }
    if(typeOfTraversal==2){
        TreeNode* t=root;
        inorder(t);
    }
    return;
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode* p=root;
    int price=0;
    while(p!=nullptr){
        if(p->left==nullptr){
            price+=p->price;
            p=p->right;
        }
    }
    return price;
}

int counting(int lowerPriceBound, int upperPriceBound,TreeNode* t,int &count,int price){
    price=t->price;
    int p=price;
    if(price>upperPriceBound){
        return 0;
    }
    if(t->left==nullptr){
        if(price>lowerPriceBound){
            count++;
        }
    }
    else{price=price+counting(lowerPriceBound,upperPriceBound,t->left,count,p);}
    if(price>upperPriceBound){
        return 0;
    }
    if(t->right==nullptr){
       if(price>lowerPriceBound){
            count++;
        }
    }
    else{price=price+counting(lowerPriceBound,upperPriceBound,t->right,count,p);}
    return price;
}    

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    TreeNode* t=root;   
    int count=0;
    counting(lowerPriceBound,upperPriceBound,t,count,0);
    return count;
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::preorder1(ofstream &o,TreeNode* t){
    TreeNode* tn=t;
    o<<t->price<<" "<<t->JourneyCode<<" ";
    if(tn->left==nullptr){
        o<<-1<<" ";
    }
    else{
        preorder1(o,tn->left);
    }
    if(tn->right==nullptr){
        o<<-1<<" ";
    }
    else{
        preorder1(o,tn->right);
    }
    return;
}

void BST::customStore(string filename) { 
    ofstream o(filename);
    TreeNode* p=root;
    preorder1(o,p);
    o.close();
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
 
void read_preorder(fstream &f,int flag, TreeNode *t){
    if(f.eof( )){
        return;
    }
    int word;
    f>>word;
    if(word==-1){
        return;
    }
    t->price=word;
    f>>word;
    t->JourneyCode=word;
    read_preorder(f,flag,t->left);
    read_preorder(f,flag,t->right);
}

void BST::customLoad (int flag, string filename) { 
    fstream f;
    TreeNode* t=root;
    string file;
    f.open(file.c_str());
    if(flag==3)
    {read_preorder(f,flag,t);}
    else if(flag==4){
        read_preorder(f,flag,t->left);
    }
    f.close( ); 
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
