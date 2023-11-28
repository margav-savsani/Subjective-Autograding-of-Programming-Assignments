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
    root = NULL;                                    //default constructor
}
BST::BST(TreeNode *root){                           //when root is given
    this->root = root;
}

bool BST::find_j(int JourneyCode ,int price ){       //find function which matches only journey code
    TreeNode *x = this->root;
    while(x != NULL){
        if( x->JourneyCode == JourneyCode){
            return true;
        }
        else if(x->price > price){
            x = x->left;
        }
        else 
            x = x->right;
    }
    return false;
}

 TreeNode * BST::findnode(int JourneyCode, int price){              //return pointer to the node having given values
    TreeNode *x = this->root;
    while(x != NULL){
        if( x->JourneyCode == JourneyCode && x->price == price){
            return x;
        }
        else if(x->price > price){
            x = x->left;
        }
        else 
            x = x->right;
    }

    return NULL;
 }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {                      //insert TreeNode

    if(find_j(JourneyCode,price)){
        return false;
    }
    else{
        TreeNode * z;
        z  = new TreeNode(JourneyCode,price);
        TreeNode *y = NULL;
        TreeNode *x = this->root;

        while(x != NULL){
            y = x;
            if(x->price > z->price){
                x = x->left;
            }
            else 
             x = x->right;
        }

        z->parent = y;
        if(y == NULL){
            this->root = z;
        }
        else {
            if(y->price > z->price){
                y->left= z;
            }
            else
                y->right = z;
        }

    }

    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {                       //find Treenode with given values
    TreeNode *x = this->root;
    while(x != NULL){
        if(x->price == price && x->JourneyCode == JourneyCode){
            //
            return true;
        }
        else if(x->price > price){
            x = x->left;
        }
        else 
            x = x->right;
    }
    //cout << "false" << endl;
    return false;
 }
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise

TreeNode* BST::successor(TreeNode* z){                     //returns pointer to the successor of given TreeNode
    if(z->right != NULL){
        TreeNode*p = z->right;
        while(p->left != NULL){
            p = p->left;
        }
        return p;
    }

    return NULL;
}

bool BST::remove(int JourneyCode, int price) {                
    if(find(JourneyCode , price) == false){                   //if Treenode not found return false
        return false;                   
    }
    else{
        
        TreeNode* d = this->findnode(JourneyCode,price);

        if(d->right == NULL && d->left == NULL){              //if both children are Null just delete the node 
            
            if(d == root){
                delete root;
                root = NULL;
                return true;
            }
            TreeNode* p = d->parent;
            if(p->left == d){
                p->left = NULL;
            }
            else
                p->right = NULL;

            delete d;
            return true;    
        }

        else if(d->right == NULL){                            // if deleted node has 1 branch then add that branch to deleted's parent
            TreeNode* c = d->left;
            if(d== root){
                delete root;
                root = c;
                root->parent=NULL;
                return true;
            }  

            TreeNode* p = d->parent;
            

            if(p->right == d){
                p->right = c;
                c->parent=p;
                delete d;
            }
            else{
                p->left = c;
                c->parent=p;
                delete d;
            }
            return true;        
        }

        else if(d->left == NULL){
            
            TreeNode* c = d->right;

            if(d == root){
                delete root;
                root = c;
                root->parent=NULL;
                return true;
            }

            TreeNode* p = d->parent;

            if(p->right == d){
                p->right = c;
                c->parent = p;
                delete(d);
            }
            else{
                p->left = c;
                c->parent = p;
                delete d;
            }
            return true;        
        }

        else{                                    // if none of the children is NULL then use succesor's method
            
            TreeNode * s = successor(d);
            int j = s->JourneyCode;
            int p = s->price;
            remove(j,p);
            d->JourneyCode = j;
            d->price = p;
            return true;
        }
        //cout << "remove done" << endl;
        return true;
    }
 }
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traversal(int typeofTraversal , TreeNode * treenode){             //traversal's recurcive function
    if(typeofTraversal == 0){
        if(treenode == NULL){
            return;
        }
        else
            cout << treenode->JourneyCode << endl;
            traversal(typeofTraversal,treenode->left);
            traversal(typeofTraversal,treenode->right);
    }

    if(typeofTraversal == 1){
        if(treenode == NULL){
            return;
        }
        else
            
            traversal(typeofTraversal,treenode->left);
            traversal(typeofTraversal,treenode->right);
            cout << treenode->JourneyCode << endl;
    }

    if(typeofTraversal == 2){
        if(treenode == NULL){
            return;
        }
        else
            
            traversal(typeofTraversal,treenode->left);
            cout << treenode->JourneyCode << endl;
            traversal(typeofTraversal,treenode->right);
    }
}

void BST::traverse(int typeOfTraversal) {                    //this will call the above recursive function                     
    TreeNode *x = this->root;
    traversal(typeOfTraversal,x);

 }

// Returns the price of the cheapest journey
int BST::getMinimum() {                                      //returns the minimum price
    TreeNode *x = this->root;
    while(x->left !=NULL){
        x = x->left;
    }
    return x->price;
 }

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.

int BST::count(int lowerPriceBound, int upperPriceBound , TreeNode* strt , int &countss){        //recursive function incremets if price is between the ranges
    if(strt == NULL){
        return countss;
    }
    else{
        if(strt->price >=lowerPriceBound && strt->price <= upperPriceBound){
            countss ++;
        }
        count(lowerPriceBound,upperPriceBound,strt->left,countss);
        count(lowerPriceBound,upperPriceBound,strt->right,countss);
        return countss;
    }
}
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {  //calls recursive count function
    int countss = 0;
    count(lowerPriceBound,upperPriceBound,root,countss);
    return countss;
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.

void BST::customprint(TreeNode* x , ofstream *s){             //null pointer will be determined by -1 -1
    if(x == NULL){
        *s << -1 <<" "<< -1  << " ";
        return;
    }
    *s << x->JourneyCode <<" " <<x->price <<" ";
    customprint(x->left , s);
    customprint(x->right , s);

}
void BST::customStore(string filename) {                   // stores values in another file
    ofstream outfile;
    outfile.open(filename);
    customprint(root,&outfile); 
    outfile.close();
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
void BST::custominput(TreeNode* &base ,TreeNode* par , ifstream* infile ){              //untill the tree finishes takes input and create node accrodingly
    
    int journeycode, price;
    *infile >> journeycode >> price ;
    if(journeycode != -1){
        base = new TreeNode(journeycode,price);
        base->parent = par;
        custominput(base->left,base,infile);
        custominput(base->right,base,infile);
    }
    else
        return;
    
}
void BST::customLoad (int flag, string filename) {                    
    ifstream infile;
    infile.open(filename);
    if(flag == LOAD_FULL_BST){
        custominput(root,NULL,&infile);
    }
    else if(flag == LOAD_LEFT_SUBTREE){                    //if we want left subtree we should ignore first entry
        int journeycode;
        int price;
        infile >>journeycode>>price;
        custominput(root,NULL,&infile);
    }
    infile.close();
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
