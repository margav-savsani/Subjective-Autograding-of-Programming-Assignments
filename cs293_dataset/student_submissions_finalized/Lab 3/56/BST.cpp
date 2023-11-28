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

//Assuming that right subtree contains elements >= root and left subtree < root

BST::BST(){
    root = new TreeNode();
    root = NULL;
   // root->parent = NULL;
}
BST::BST(TreeNode *root){
    this->root = root;
    root->parent = NULL;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    bool res;
    if(root != NULL){        
        if(price < root->price){            
            if(root->left == NULL){
                TreeNode* tempch = new TreeNode(JourneyCode, price);
                root->left = tempch;
                tempch->parent = root;
                res = true;
                return true;
            }
            else{
                TreeNode* temp = root;
                root = root->left;
                res = insert(JourneyCode, price);
                root = temp;
            }
            
        }
        else if(price >= root->price){
            if(root->JourneyCode == JourneyCode){
                res = false;
                return false;
            }
            if(root->right == NULL){
                TreeNode* tempch = new TreeNode(JourneyCode, price);
                root->right = tempch;
                tempch->parent = root;
                res = true;
                return true;
            }
            TreeNode* temp = root;
            root = root->right;
            res = insert(JourneyCode, price);
            root = temp;
        }
    }
    else{
        root = new TreeNode(JourneyCode, price); 
        root->parent = NULL;
        res = true;
    }
    return res;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    bool res;
    if(root != NULL){        
        if(root->JourneyCode == JourneyCode && root->price == price){
            return true;
        }
        if(price < root->price){
            TreeNode* temp = root;
            root = root->left;
            res = find(JourneyCode, price);            
            root = temp;
        }
        else if(price >= root->price){
            TreeNode* temp = root;
            root = root->right;
            res = find(JourneyCode, price);
            root = temp;
        }
        
        return res;
    }
    else{
        return false;
    }
}

TreeNode* BST::findNode(int JourneyCode, int price){
    TreeNode* res;
    if(root != NULL){        
        if(root->JourneyCode == JourneyCode && root->price == price){
            return root;
        }
        if(price < root->price){
            TreeNode* temp = root;
            root = root->left;
            res = findNode(JourneyCode, price);            
            root = temp;
        }
        else if(price >= root->price){
            TreeNode* temp = root;
            root = root->right;
            res = findNode(JourneyCode, price);
            root = temp;
        }
        
        return res;
    }
    else{
        return NULL;
    }
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    TreeNode* node = findNode(JourneyCode, price);
    if(node == NULL){        
        return false;
    }    
    else{    //handle the case when root gets deleted
        if(node->left == NULL && node->right == NULL){
            
            if(node->parent != NULL){
                if((node->parent)->right == node){
                    (node->parent)->right = NULL;
                }
                else if((node->parent)->left == node){
                    (node->parent)->left = NULL;
                }
            }
            else{
                root = NULL;
            }
        }
        else if(node->left == NULL || node->right == NULL){
            if(node->parent != NULL){
                TreeNode* temp;
                if(node->left == NULL){
                    temp = node->right;                  
                    
                }
                else if(node->right == NULL){
                    
                    temp = node->left;
                }
                if((node->parent)->right == node){
                    (node->parent)->right = temp;
                }
                else if((node->parent)->left == node){
                    (node->parent)->left = temp;
                }
                temp->parent = node->parent;
            }
            else{
                if(node->left == NULL){
                    root = node->right;
                    (node->right)->parent = NULL;
                }
                else if(node->right == NULL){
                    root = node->left;
                    (node->left)->parent = NULL;
                }
            }

        }
        else{
            TreeNode* temp3 = root;
            root = node->right;
            TreeNode* succ = getMinimumNode();
            
            root = temp3;
            remove(succ->JourneyCode, succ->price);
            
            if(node->parent != NULL){
                if((node->parent)->right == node){
                    (node->parent)->right = succ;
                }
                else if((node->parent)->left == node){
                    (node->parent)->left = succ;
                }
                succ->parent = node->parent;
                
            }
            
            else{
                root = succ;
                succ->parent = NULL;
            }
            
            succ->left = node->left;
            
            succ->right = node->right;
            
            (node->left)->parent = succ;
            (node->right)->parent = succ;
            
            
            
        }
    }
    return true;
    
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    if(root != NULL){
        if(typeOfTraversal == PRE_ORDER){
            
            cout << root->JourneyCode << endl;
            TreeNode* temp = root;
            root = root->left;
            traverse(typeOfTraversal);
            root = temp;
            root = root->right;
            traverse(typeOfTraversal);
            root = temp;
        }
        else if(typeOfTraversal == IN_ORDER){
            TreeNode* temp = root;
            root = root->left;
            traverse(typeOfTraversal);
            root = temp;
            cout << root->JourneyCode << endl;
            root = root->right;
            traverse(typeOfTraversal);
            root = temp;
        }
        else if(typeOfTraversal == POST_ORDER){
            TreeNode* temp = root;
            root = root->left;
            traverse(typeOfTraversal);
            root = temp;
            root = root->right;
            traverse(typeOfTraversal);
            root = temp;
            cout << root->JourneyCode << endl;
        }
    }
}

TreeNode* BST::getMinimumNode(){
    if(root != NULL){
        TreeNode* trav = root;
        while(trav->left != NULL){
            trav = trav->left;
        }
        return trav;
    }
    else{
        return NULL;
    }
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    if(root != NULL){
        TreeNode* trav = root;
        while(trav->left != NULL){
            trav = trav->left;
        }
        return trav->price;
    }
    return 0;   //look into this
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
