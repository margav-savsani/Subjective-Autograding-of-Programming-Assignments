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
    this->root = new TreeNode();
     
    }
BST::BST(TreeNode *root){
    this->root = root;
     
    }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
    
    TreeNode*   currNode = root;
    TreeNode*  insNode = new TreeNode(JourneyCode, price);
    bool inserted = false;
    while(!inserted){
        if (insNode->price < currNode->price){
            if (currNode->left == nullptr){
                currNode->left = insNode;
                insNode->parent = currNode;
                inserted = true;
                return true;
            } else {
                currNode = currNode->left;
            }
        }

        else if (insNode->price > currNode->price){
            if (currNode->right == nullptr){
                currNode->right = insNode;
                insNode->parent = currNode;
                inserted = true;
                return true;
            } else {
                currNode = currNode->right;
            }
        } else {
            return false;
        }
    }
    return false;

}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    TreeNode * toFind = new TreeNode(JourneyCode, price);
    TreeNode * currNode = root;


    bool found = false;

    while (!found){
        if (toFind->price < currNode->price){
            if (currNode->left != nullptr){
                currNode = currNode->left;
            } else {
                return false;
            }
        } else if (toFind->price > currNode->price){
            if (currNode->right != nullptr){
                currNode = currNode->right;
            } else {
                return false;
            }
        } else {
            if (toFind->JourneyCode = currNode->JourneyCode){
                found = true;
                return true;
            } else {
                return false;
            }
        }

    }

    return false; }
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    
    bool found = find(JourneyCode, price);
    if (!found){
        return false;
    } else {
        TreeNode * toFind = new TreeNode(JourneyCode, price);
        TreeNode * prevNode = root;
        TreeNode * currNode = root;


        

        while (found){
            if (toFind->price < currNode->price){
                if (currNode->left != nullptr){
                    prevNode = currNode;
                    currNode = currNode->left;
                }
            
            } else if (toFind->price > currNode->price){
                if (currNode->right != nullptr){
                    prevNode = currNode;
                    currNode = currNode->right;
                }
            
            } else if (toFind->JourneyCode = currNode->JourneyCode){
                    if (currNode->left == nullptr && currNode->right == nullptr){
                        if (currNode->parent->left = currNode){
                           currNode->parent->left = nullptr; 
                        } else {
                            currNode->parent->right = nullptr;
                        }
                        return true;
                    } else if (currNode->left == nullptr){
                        if (currNode->parent->left == currNode){
                            currNode->parent->left = currNode->right;
                        } else {
                            currNode->parent->right = currNode->right;
                        }
                        return true;
            
                    } else if (currNode->right == nullptr){
                        if (currNode->parent->left == currNode){
                            currNode->parent->left = currNode->left;
                        } else {
                            currNode->parent->right = currNode->left;
                        }

                        return true;
                    } else {
                        TreeNode * succNode = currNode->right;
                        while(true){
                            if(succNode->left != nullptr) succNode = succNode->left;
                            else break;
                        }

                        remove(succNode->JourneyCode,succNode->price);


                        if (currNode->parent->left == currNode){
                            currNode->parent->left = succNode;
                            succNode->parent = currNode->parent;
                            succNode->left = currNode->left;
                            succNode->right = currNode->right;
                        } else {
                            currNode->parent->right = succNode;
                            succNode->parent = currNode->parent;
                            succNode->left = currNode->left;
                            succNode->right = currNode->right;

                        }
                        return true;
                    }
            
            } 


            
            
            

        }
    }
    
    
    return false; 
    
    }
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    
    if (typeOfTraversal == PRE_ORDER){
        if (root == nullptr) return;
        if (root->JourneyCode != 0){
            cout << root->JourneyCode << endl;
        }

        if (root -> left != nullptr){
            BST  leftTree = BST(root->left) ;
            leftTree.traverse(PRE_ORDER);
        } 
        
        if (root -> right != nullptr){
            BST  rightTree = BST(root->right) ;
            rightTree.traverse(PRE_ORDER);
        } 
        
    } else if (typeOfTraversal == IN_ORDER){

        if(root == nullptr) return;

        if (root -> left != nullptr){
            BST  leftTree = BST(root->left) ;
            leftTree.traverse(PRE_ORDER);
        } 

        if (root -> JourneyCode != 0) cout << root->JourneyCode << endl;

        
        if (root -> right != nullptr){
            BST  rightTree = BST(root->right) ;
            rightTree.traverse(PRE_ORDER);
        } 
        
        
    } else if (typeOfTraversal == POST_ORDER){
        if (root == nullptr) return;
       if (root -> left != nullptr){
            BST  leftTree = BST(root->left) ;
            leftTree.traverse(PRE_ORDER);
        } 
        
        if (root -> right != nullptr){
            BST  rightTree = BST(root->right) ;
            rightTree.traverse(PRE_ORDER);
        } 
        if (root -> JourneyCode != 0) cout << root->JourneyCode << endl;
        
        
    }
    
    
    
    }

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode * currNode = root->right;
    if (currNode != nullptr){
        while(true){
            if (currNode->left != nullptr){
                currNode = currNode->left;

            } else {
                return currNode->price;
            }
        
        }
    } else {
        return 0;
    }
    return 0; }

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
        root = 
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

