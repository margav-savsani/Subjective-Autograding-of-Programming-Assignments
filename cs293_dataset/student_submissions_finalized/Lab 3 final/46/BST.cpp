#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
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
    this->root = NULL;
}

BST::BST(TreeNode *root){
    this->root = root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
        TreeNode *x,*y,*z;
        x = root;
        y = NULL;
        z = new TreeNode(JourneyCode,price);
        if(find(JourneyCode,price)) return false;
        if(x==NULL) {
            root = z;
            root->parent = NULL;
            return true;
        }
        while(x != NULL) {
            y = x;
            if(z->price < x->price) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }
        z->parent = y;
        if(z->price < y->price) {
                 y->left = z;
                 return true; 
        }
        else {
                y->right = z;
                return true;
        }
        return false;
}



TreeNode* BST::find_tree(TreeNode* x,int price,int JourneyCode) {
        if(x == NULL) {
            return NULL;
        }
        if((price == x->price)&&(JourneyCode==x->JourneyCode)) {
            return x;
        }
        if(price < x->price) {
            return find_tree(x->left,price,JourneyCode);
        }
        else {
            return find_tree(x->right,price,JourneyCode);
        }
        return NULL;

}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    if(find_tree(root,price,JourneyCode)==NULL) return false;
    return true;
}

TreeNode* BST::mini(TreeNode* x) {
    if(x == NULL) return NULL;
    while(x->left != NULL) {
        return mini(x->left);
    }
    return x;
}
	
TreeNode* tr_suc(TreeNode* x) {
    if(x->right!=NULL) {
        TreeNode *a,*b;
        a = x->right;
        while(a->left != NULL) {
            a = a->left;
        }
        return a;
    }
    TreeNode* y=x->parent;
    while(y!=NULL && x==(y->right)) {
        x=y;
        y=y->parent;
        return y;
    }
    return NULL;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise

bool BST::remove(int JourneyCode, int price) {
    TreeNode* x = find_tree(root,price,JourneyCode);
    if(x==NULL) return false;
    
    // case-1 no children to x
    TreeNode* x_p = x->parent;
    if(x->left==NULL && x->right==NULL) {
        if(x_p==NULL) {
            root = NULL;
        }
        else if(x_p->right==x) {
            x_p->right=NULL;
            x->parent=NULL;
        }
        else if(x_p->left==x) {
            x_p->left=NULL;
            x->parent=NULL;
        }
        return true;
    }

    // case-2 exactly one child
    TreeNode* x_c;
    bool val=false;
    if(x->left != NULL && x->right == NULL) {
        x_c=x->left;
        val=true;
    }
    else if(x->left == NULL && x->right != NULL) {
        x_c=x->right;
        val=true;
    }
    if(val==true) {
        if(x==root) {
            root=x_c;
            x_c->parent=NULL; 
        }
        else if(x_p->left==x) {
            x_p->left=x_c;
            x_c->parent=x_p;
        }
        else if(x_p->right==x) {
            x_p->right=x_c;
            x_c->parent=x_p;
        }
        return true;
    }

    // case-3 2 children
    TreeNode* suc_X = tr_suc(x);
    int pri = suc_X->price;
    int code = suc_X->JourneyCode;
    remove(suc_X->JourneyCode,suc_X->price);
    x->price = pri;
    x->JourneyCode = code; 
    return true;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::Pre_order(TreeNode* t) {
    if(t==NULL) return;
    cout << t->JourneyCode <<endl;
    Pre_order(t->left);
    Pre_order(t->right);
    return;
}

void BST::Post_order(TreeNode* t) {
    if(t==NULL) return;
    Post_order(t->left);
    Post_order(t->right);
    cout << t->JourneyCode << endl;
    return;
}

void BST::in_order(TreeNode* t) {
    if(t==NULL) return;
    in_order(t->left);
    cout << t->JourneyCode << endl;
    in_order(t->right);
    return;
}

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal==0) Pre_order(root);
    if(typeOfTraversal==1) Post_order(root); 
    if(typeOfTraversal==2) in_order(root);  
    return;
}

// Returns the price of the cheapest journey

int BST::getMinimum() {
    return mini(root)->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.

int countjourney(int lowerPriceBound, int upperPriceBound, TreeNode* root) {
    TreeNode* x=root;
    if(x==NULL) return 0;
    while(x!=NULL) {
        if(x->price >= upperPriceBound) return 1+countjourney(lowerPriceBound,upperPriceBound,root->left);
        if(x->price <= lowerPriceBound) return 1+countjourney(lowerPriceBound, upperPriceBound,root->right);
        else {
            return 1+countjourney(lowerPriceBound,upperPriceBound,root->left)+countjourney(lowerPriceBound,upperPriceBound,root->right);
        }
    }
    return -1;
}

int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    TreeNode* x=root;
    return countjourney(lowerPriceBound,upperPriceBound,root);
    return 0;
    }

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.

TreeNode* get_last(TreeNode* root) {
    TreeNode* x=root;
    while(x!=NULL) {
        if(x->left==NULL && x->right==NULL) return x;
        if(x->left!=NULL && x->right==NULL) x=x->left;
        else if(x->left==NULL && x->right!=NULL) x=x->right;
    }
    return x; // my program should not reach this point.
}

TreeNode* BST::compress(TreeNode* root, string f) {

    ofstream out;
    if(root==NULL||root->left==NULL) {
        return root; // since no need to re-arrange.
    }
    if(root->right==NULL) {
        root->left=compress(root->left,f);
        TreeNode* tmp=new TreeNode(-1,-1);
        tmp->right=root->right;
        tmp->parent=root;
        //(root->right)->parent=tmp;
        root->right=tmp;
        
        (root->left)->parent=NULL;
        root->left=NULL;
        return root;
    }
    root->left= compress(root->left,f);
    root->right= compress(root->right,f);
    TreeNode* last= get_last(root->left);

    TreeNode* tmp=new TreeNode(-1,-1);
    if(last!=NULL) {
        last->right=tmp;
        tmp->parent=last;
        tmp->right=root->left;
        //(root->left)->parent=tmp;
    }
    TreeNode* tm=new TreeNode(-1,-1);
    (root->right)=tm;
    tm->parent=root;
    tm->right=root->left;
    root->left=NULL;
    this->root=root;
    return (this->root);
}

void BST::customStore(string filename) { 

    this->root = compress(root,filename);
    TreeNode* x=this->root;
    ofstream outfile;
    outfile.open(filename);
    while(x!=NULL) {
        if(x->price==-1) outfile << "/" << endl;
        else outfile << x->JourneyCode << " " << x->price << endl;
        x=x->right;
    }
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

