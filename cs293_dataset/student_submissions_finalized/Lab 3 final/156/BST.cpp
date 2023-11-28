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
    root = nullptr;
    N=0;
}
BST::BST(TreeNode *root){
    this->root=root;
    N=1;
 }

void TreeNode::preorder(){
    cout << JourneyCode;
    if(left!=nullptr) left->preorder();
    if(right!=nullptr) right->preorder();
}
void TreeNode::postorder(){
    if(left!=nullptr) left->postorder();
    if(right!=nullptr) right->postorder();
    cout << JourneyCode;
}
void TreeNode::inorder(){
    if(left!=nullptr) left->inorder();
    cout << JourneyCode;
    if(right!=nullptr) right->inorder();
}
void TreeNode::travel(int lower, int upper, int &count){
    //function made for Price Bound function
    if(price>=lower && price<=upper){
        count++;
        if(left!=nullptr) left->travel(lower,upper,count);
        if(right!=nullptr) right->travel(lower,upper,count);
    }
    else if(price<lower){
        if(right!=nullptr) right->travel(lower,upper,count);
    }
    else if(price>upper){
        if(left!=nullptr) left->travel(lower,upper,count);
    }
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    if(N==0){
        root = new TreeNode(JourneyCode,price);
        N++;
    }
    else{
        TreeNode *x;
        TreeNode *y;
        x = root;
        y = nullptr;
        while(x!=nullptr){
            y = x;
            //y is needed as when x becomes null we need to know what was the last element that would be the parent
            if(price==y->price && JourneyCode==y->JourneyCode){
                return false;
            }
            //could do either left or right in case of equality but I chose left
            else if(price<=(y->price)){
                x = x->left;
            }
            else{
                x = x->right;
            }
        }
        if(price > (y->price)){
            //need to pass y as well else how would you access parent of a child in remove function!!!
            //not setting parent here was giving segfault while running delete function 
            //that took me 3 hrs to debug :)
            y->right = new TreeNode(JourneyCode,price,nullptr,nullptr,y);
        }
        else{
            y->left = new TreeNode(JourneyCode,price,nullptr,nullptr,y);
        }
    }
    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    TreeNode *x = root;
    while(x!=nullptr){
        if((x->price==price) && (x->JourneyCode==JourneyCode)){
            return true;
        }
        else if(price <= (x->price)){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }
    return false; 
}

TreeNode* BST::successor(TreeNode *x){
    //made this function only for use in the remove function hence did not consider the case of
    //x->right being null as this function is being called only when node has two children
    return min(x->right);
}
	
TreeNode* BST::min(TreeNode *x){
    TreeNode *k = x;
    while(k->left!=nullptr){
        k = k->left;
    }
    return k;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
    bool fnd = find(JourneyCode,price);
    if(fnd==false) {return false;}
    else{
        TreeNode *x = root;
        long long int n=0;
        while(x!=nullptr){
            if((x->price==price) && (x->JourneyCode==JourneyCode)){
                //when the node to be removed is a leaf
                if((x->left==nullptr) && (x->right==nullptr)){
                    if(n==0){
                        root = nullptr;
                        N=0;
                    }
                    else{
                        if((x->parent)->price >= price){
                            (x->parent)->left = nullptr;
                            x->parent = nullptr;
                        }
                        else{
                            (x->parent)->right = nullptr;
                            x->parent = nullptr;
                        }
                    }
                }

                //the node to be deleted has only one child
                else if((x->left==nullptr) || (x->right==nullptr)){
                    if(n==0){
                        if(x->left==nullptr){
                            root = (x->right);
                            (x->right)->parent = nullptr;
                            x->right = nullptr;
                        }
                        else{
                            root = x->left;
                            (x->left)->parent = nullptr;
                            x->left = nullptr;
                        }
                    }
                    else{
                        if(x->left==nullptr){
                            if((x->parent)->price >= x->price){
                                (x->parent)->left = x->right;
                                (x->right)->parent = x->parent;
                                x = nullptr;
                            }
                            else{
                                (x->parent)->right = x->right;
                                (x->right)->parent = x->parent;
                                x = nullptr;
                            }
                        }
                        else{
                            if((x->parent)->price >= x->price){
                                (x->parent)->left = x->left;
                                (x->left)->parent = x->parent;
                                x = nullptr;
                            }
                            else{
                                (x->parent)->right = x->left;
                                (x->left)->parent = x->parent;
                                x = nullptr;
                            }
                        }
                    }
                }

                //The case where the node to be deleted has two children
                else{
                        //use recursion you would not need to take care of cases as in the prev code
                        TreeNode* z=successor(x);
                        if(x->parent == nullptr){
                            TreeNode* temp = z;
                            remove(z->JourneyCode,z->price);
                            root->JourneyCode = temp->JourneyCode;
                            root->price = temp->price;
                            return true;
                        }
                        else{
                            TreeNode* temp = z;
                            remove(z->JourneyCode,z->price);
                            x->JourneyCode = temp->JourneyCode;
                            x->price = temp->price;
                            return true;
                        }
                }
                return true;
            }
            else if(price <= (x->price)){
                n++;
                x = x->left;
            }
            else{
                n++;
                x = x->right;
            }
        }
    }
    return false;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per 

//Preorder : Root,Left,Right 
//Postorder : Left,Right,Root
//Inorder : Left,Root,Right
void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal==0){
        TreeNode *x = root;
        x->preorder();
    }
    else if(typeOfTraversal==1){
        TreeNode *x = root;
        x->postorder();
    }
    else if(typeOfTraversal==2){
        TreeNode *x = root;
        x->inorder();
    }
}

// Returns the price of the cheapest journey
int BST::getMinimum() { 
    TreeNode *x = root;
    TreeNode *y = nullptr;
    while(x!=nullptr){
        y = x;
        x = x->left;    
    }
    return y->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    int count = 0;
    TreeNode* x = root;
    x->travel(lowerPriceBound,upperPriceBound,count);
    return count;
}

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

// Please use the following code to replace the last part of
// BST.cpp that was provided earlier (from below the comment
// DO NOT CHANGE ANYTHING BELOW THIS LINE)
//
//

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

