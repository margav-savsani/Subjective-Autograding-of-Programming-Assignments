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

BST::BST(){; }
BST::BST(TreeNode *root){this ->root=root;}
TreeNode *s;

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
    s=root;
    bool i=true;
    if(find(JourneyCode,price)) return false;
    else{
        while(i){
            if( root == nullptr){
                TreeNode *v;
                v = new TreeNode();
                v->JourneyCode=JourneyCode;
                v->price=price;
                v->left=nullptr;
                v->right=nullptr;
                v->parent=nullptr;
                root=v;
                i=false;
            }    
            else if( root !=nullptr ){
                cout<<"1"<<endl;
                if((s->price) > price && s->left != NULL){
                s=s->left;
                }
                cout<<"2"<<endl;
                if((s->price) > price && s->left == nullptr){
                    TreeNode *p;
                    p = new TreeNode();
                    p->JourneyCode=JourneyCode;
                    p->price=price;
                    p->parent=s;
                    p->left=nullptr;
                    p->right=nullptr;
                    s->left = p;
                    i=false;
                }
                cout<<"3"<<endl;
                if((s->price) < price && s->right != nullptr){
                    s=s->right;
                    }
                cout<<"4"<<endl;
                if((s->price) < price && s->right == nullptr){
                    TreeNode *q;
                    q = new TreeNode();
                    q->JourneyCode=JourneyCode;
                    q->price=price;
                    q->parent=s;
                    q->left=nullptr;
                    q->right=nullptr;
                    s->right = q;
                    i=false;
                    }
            }
        }
        return true;
    }
}    

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    s=root;
    bool b=false;
    while(b == false && s != nullptr){
        if(s->price == price){
            b=true;
            }
        else if(s->price > price){
            s=s->left;
        }
        else if(s->price < price){
            s=s->right;
        }
    }
    return b;
 }
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
    s=root;
    if(!find(JourneyCode,price)) return false;
    else{
        if(s->price>price){
            s=s->left;
        }
        else if(s->price<price){
            s=s->right;
        }
        else if(s->price==price){
            if(s->left==nullptr && s->right==nullptr){
                s=nullptr;
            }
            else if(s->left==nullptr && s->right!=nullptr){
                if(s->parent->price>s->price){
                    s->parent->left=s->right;
                    s=nullptr;
                }
                else if(s->parent->price<s->price){
                    s->parent->right=s->right;
                    s=nullptr;
                }
            }
            else if(s->left!=nullptr && s->right==nullptr){
                s->parent->left=s->left;
                s=nullptr;
            }
            else if(s->left!=nullptr && s->right!=nullptr){
                TreeNode *x;
                x=s->right;
                while(x->left!=nullptr){
                    x=x->left;
                }
                s->JourneyCode=x->JourneyCode;
                s->price=x->price;
                x=nullptr;
            }
        }
    return true;
    }
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void f(TreeNode *x){

    if(x != nullptr){
        cout<<x->price<<endl;
        f(x->left);
        f(x->right);
        
    }
    return;
}

void g(TreeNode *x){
    if(x != nullptr){
        g(x->left);
        g(x->right);
        cout<<x->price<<endl;
    }
    return;
}

void h(TreeNode *x){
    if(x != nullptr){
        h(x->left);
        cout<<x->price;
        h(x->right);
    }
}

void BST::traverse(int typeOfTraversal) {
    s=root;
        if(typeOfTraversal== PRE_ORDER){
           f(s); 
    }

    else if(typeOfTraversal== POST_ORDER){
            g(s);
    }

    else if(typeOfTraversal== IN_ORDER){
            h(s);
    }

    return; }

// Returns the price of the cheapest journey
int BST::getMinimum() {
    s=root;
    int m=0;
    if(s->left==nullptr) m=s->price;
    else if(s->left!=nullptr) {
        s=s->left;
        m=getMinimum();
        }
    return m;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {return 0; }

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

