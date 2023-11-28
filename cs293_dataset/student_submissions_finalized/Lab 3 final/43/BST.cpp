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
    root = new TreeNode();
     }
BST::BST(TreeNode *root1){root = root1; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

bool BST::insert(int JourneyCode, int price) {
   if((root->JourneyCode == 0)&&(root->price == 0)){
    root->JourneyCode = JourneyCode;
    root->price = price;
    root->parent = nullptr;
    return true;
   }
   else if((root->JourneyCode == JourneyCode)&&(root->price == price)){
     return false;
   }
   else if(root->price < price){
    TreeNode *r;
    if(root->right == nullptr){
        r = new TreeNode(JourneyCode,price);
        root->right = r;
        r->parent = root;
        return true;
    }
    else{
        r = root->right;
        BST m;
        m.root = r;
        return m.insert(JourneyCode,price);
    }
   }
   else if(root->price >= price){
    TreeNode *r;
    if(root->left == nullptr){
        r = new TreeNode(JourneyCode,price);
        root->left = r;
        r->parent = root;
        return true;
    }
    else{
        r = root->left;
        BST m;
        m.root = r;
        return m.insert(JourneyCode,price);
    }
   }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    if((root->JourneyCode) == JourneyCode && (root->price) == price ){
        return true;
    }
    else if(root->price > price){
        if(root->left==nullptr){
            return false;
        }
        else{
            BST m(root->left);
            return m.find(JourneyCode,price);
        }
    }
    else if(root->price <=price){
        if(root->right==nullptr){
            return false;
        }
        else{
            BST m(root->right);
            return m.find(JourneyCode,price);
        }
     }
 }
 TreeNode *Predecessor(TreeNode *r){
    TreeNode *p;
    p = r->left;
   while(true){
    if(p->right == nullptr){
        return p;
    }
    p = p->right;
   }
 }
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    if(find(JourneyCode,price)){
         if(root->JourneyCode == JourneyCode && root->price == price&&(root->parent != nullptr) ){
            if(root->right==nullptr&&root->left == nullptr){
                TreeNode *t;
                t = root->parent;
                if(t->right == root){
                    t->right = nullptr;
                    return true;
                }
                else if(t->left == root){
                    t->left = nullptr;
                    return true;
                }
            }
            else if(root->right == nullptr && root->left != nullptr){
                TreeNode *t;
                t = root->parent;
                if(t->right == root){
                    t->right = root->left;
                    (root->left)->parent = t;
                    return true;
                } 
                else if(t->left == root){
                    t->left = root->left;
                    (root->left)->parent = t;
                    return true;
                } 
            }
            else if(root->left == nullptr && root->right != nullptr){
                TreeNode *t;
                t = root->parent;
                if(t->right == root){
                    t->right = root->right;
                    (root->right)->parent = t;
                    return true;
                }
                else if(t->left == root){
                    t->left = root->right;
                    (root->right)->parent = t;
                    return true;
                }
            } 
            else if(root->left !=nullptr&&root->right != nullptr){
                    if(root->left->right == nullptr){
                            if(root == root->parent->right){
                                    root->parent->right = root->left;
                                    
                            }
                            else{
                                    root->parent->left = root->left;
                                    
                            }
                            root->left->parent = root->parent;
                            root->left->right = root->right;
                            root->right->parent = root->left;
                            return true;
                    }
                    TreeNode *p;
                    p = Predecessor(root);
                    TreeNode *r,*s;
                    r = p->left;
                    s = p->parent;
                    if(r!=nullptr){
                        if(root == (root->parent)->left){
                          (root->parent)->left = p;
                         
                        }
                        else if(root == (root->parent)->right){
                          (root->parent)->right = p;
                          
                        }
                        p->parent = root->parent;
                        p->left = root->left;
                        p->right = root->right;
                        (root->left)->parent = p;
                        (root->right)->parent = p;
                        r->parent = s;
                        s->right = r;
                        return true;
                    }
                    else {
                        if(root == (root->parent)->left){
                            s->right = nullptr;
                            (root->parent)->left = p;   
                        }
                        else if(root == (root->parent)->right){
                            s->right = nullptr; 
                            (root->parent)->right = p;
                        }
                        p->parent = root->parent;
                        p->left = root->left;
                        p->right = root->right;
                        (root->right)->parent = p;
                        (root->left)->parent = p;
                        return true;

                    }
            }
         }
         else if(root->JourneyCode == JourneyCode && root->price == price&&(root->parent == nullptr)){
               if(root->left == nullptr&& root->right== nullptr){
                   root = new TreeNode(); 
                   root->parent = nullptr;
               }
               else if(root->left == nullptr&& root->right != nullptr){
                   root = root->right;
                   root->parent = nullptr;
               }
               else if(root->left != nullptr&& root->right == nullptr){
                    root = root->left;
                   root->parent = nullptr;
               }
               else{
                 if(root->left->right == nullptr){
                    root->left->right = root->right;
                    root->right->parent = root->left;
                    root = root->left;
                    root->parent = nullptr;
                 }
                 else{
                    TreeNode *p,*r;
                    p = Predecessor(root);
                    r = p->left;
                    if(r == nullptr){
                        p->left = root->left;
                        p->right = root->right;
                        p->parent->right = nullptr;
                        root->left->parent = p;
                        root->right->parent = p;
                        root = p;
                        root->parent = nullptr;
                    }
                    else{
                        p->left = root->left;
                        p->right = root->right;
                        p->parent->right = r;
                        r->parent = p->parent;
                        root->left->parent = p;
                        root->right->parent = p;
                        root = p;
                        root->parent = nullptr;
                    }
                 }
               }     
       return true;
        }
    
    else if(root->price > price){
            TreeNode *r;
            r = root->left;
            BST m(r);
            return m.remove(JourneyCode,price);  
    }
    else if(root->price <=price){
            TreeNode *r;
            r = root->right;
            BST m(r);
            return m.remove(JourneyCode,price);
    }
 }
 else{
    return false;
 }
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal == 0){
        if(root != nullptr){
            cout<<root->JourneyCode<<endl;
            BST m(root->left),n(root->right);
             m.traverse(0);
             n.traverse(0);
        }
    }
    if(typeOfTraversal == 2){
        if(root != nullptr){
            BST m(root->left),n(root->right);
            m.traverse(2);
            cout<<root->JourneyCode<<endl;
            n.traverse(2);
        }
    }
    if(typeOfTraversal == 1){
        if(root != nullptr){
            BST m(root->left),n(root->right);
            m.traverse(1);
            n.traverse(1);
            cout<<root->JourneyCode<<endl;
        }
    }
 }

// Returns the price of the cheapest journey
int BST::getMinimum() {
    if(root->left==nullptr){
        return root->price;
    }
    else{
        BST m(root->left);
        return m.getMinimum();
    } 
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

