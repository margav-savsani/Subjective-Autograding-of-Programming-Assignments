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

BST::BST() { root = nullptr; }
BST::BST(TreeNode *root)
{
    this->root = root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{
  
    // TreeNode *y = new TreeNode;
    //y->left=nullptr
    TreeNode *res = new TreeNode;
    TreeNode *y=nullptr;
    
    if (root == nullptr)
    {
        root=new TreeNode(JourneyCode,price,nullptr,nullptr,nullptr);
        
        return true;
    }

    else {
          TreeNode *x = root;
        while (x != nullptr)
    {
        if (x->JourneyCode == JourneyCode)
        {
            return false;
        }

        if (price >= x->price)
        {
            y = x;
            x = x->right;
            

        }
        else if (price < x->price)
        {
            y = x;
            x = x->left;
           
        }
        
    }
    if (price < y->price)
    {
        res->parent = y;
        y->left = res;
        res->JourneyCode = JourneyCode;
        res->price = price;
        
        
    }
    else
    {
        res->parent = y;
        y->right = res;
        res->JourneyCode = JourneyCode;
        res->price = price;
    }
    }

    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{

    TreeNode *x = root;

    while (x != nullptr)
    {

        if (x->price == price && x->JourneyCode == JourneyCode)
        {
            return true;
        }
        if (x->price > price)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }

    return false;
}
TreeNode *BST::predecessor(TreeNode *z)
{

    if (z->left != nullptr)
    {
        TreeNode *t1 = z->left;
        while (t1->right != nullptr)
        {
            t1 = t1->right;
        }

        return t1;
    }
    if (z->parent == nullptr)
    {
        return nullptr;
    }
    TreeNode *t1 = z->parent;
    TreeNode *t2 = z;
    while (t1 != nullptr)
    {
        if (t1->right == t2)
        {
            return t1;
        }
        t2 = t1;
        t1 = t1->parent;
    }
    return nullptr;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    if (find(JourneyCode, price))
    {
        TreeNode *x = root;
        while (x != nullptr)
        {

            if (x->price == price && x->JourneyCode == JourneyCode)
            {
                if (x->left == nullptr && x->right == nullptr)
                {
                    delete x;
                }
                else if (x->right == nullptr)
                {
                    TreeNode *t = x->left;
                    if (x->parent != nullptr)
                    {
                        TreeNode *t2 = x->parent;
                        if (x == t2->left)
                        {
                            t->parent = t2;
                            t2->left = t;
                            delete x;
                        }
                        else
                        {
                            t->parent = t2;
                            t2->right = t;
                            delete x;
                        }
                    }
                    else
                    {
                        delete root;
                        root = t;
                    }
                }
                else if (x->left == nullptr)
                {
                    TreeNode *t = x->right;
                    if (x->parent != nullptr)
                    {
                        TreeNode *t2 = x->parent;
                        if (x == t2->left)
                        {
                            t->parent = t2;
                            t2->left = t;
                            delete x;
                        }
                        else
                        {
                            t->parent = t2;
                            t2->right = t;
                            delete x;
                        }
                    }
                    else
                    {
                        delete root;
                        root = t;
                    }
                }
                else
                {
                    
                        TreeNode *p = predecessor(x);
                        x->JourneyCode=p->JourneyCode;
                        x->price=p->price;
                        if(p->left==nullptr && p->right==nullptr){
                            delete p;
                        }
                        else{
                        TreeNode *z= p->parent;
                        TreeNode *y= p->left;
                        if(z->right==p){
                            y->parent=z;
                            z->right =y;
                            delete p;
                        }
                        else{
                            y->parent =z;
                            z->left=y;
                            delete p;
                        }
                        }
                    
                   
                }
                return true;
            }
        
        if (x->price > price)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
}

return false;
}
void BST::MYPRE_ORDER(TreeNode *y){
    if(y!=nullptr){
    cout<<y->JourneyCode<<endl;
    MYPRE_ORDER(y->left);
    MYPRE_ORDER(y->right);

    }
    else{
        return;
    }
}
void BST::MYPOST_ORDER(TreeNode *y){
    if(y!=nullptr){
    
    MYPOST_ORDER(y->left);
    MYPOST_ORDER(y->right);
    cout<<y->JourneyCode<<endl;

    }
    else{
        return;
    }
}
void BST::MYIN_ORDER(TreeNode *y){
    if(y!=nullptr){
    
    MYIN_ORDER(y->left);
    cout<<y->JourneyCode<<endl;
    MYIN_ORDER(y->right);
    

    }
    else{
        return;
    }
}




// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) { 
    if(typeOfTraversal==0){
        MYPRE_ORDER(root);
    }
    else if(typeOfTraversal==1){
        MYPOST_ORDER(root);
    }
    else if(typeOfTraversal==2){
        MYIN_ORDER(root);
    }

 }

// Returns the price of the cheapest journey
int BST::getMinimum()
{
    TreeNode *x = root;
    TreeNode *y = new TreeNode;
    while (x != nullptr)
    {
        y = x;
        x = x->left;
    }

    return y->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) { return 0; }

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

void BST::customLoad(int flag, string filename) { return; }

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