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
    BST_length=0;
    root=new TreeNode();
}
BST::BST(TreeNode *root) {
    
    this->root=root;
    (this->root)->left=nullptr;
    (this->root)->right=nullptr;
    (this->root)->parent=nullptr;
    BST_length=1;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
    if(BST_length==0) {
        this->root=new TreeNode();
        (this->root)->left=nullptr;
        (this->root)->right=nullptr;
        (this->root)->parent=nullptr;
        (this->root)->JourneyCode=JourneyCode;
        (this->root)->price=price;
        BST_length+=1;
        return true;
    }
    else {
        TreeNode* search_node=root;
        while(true) {
            if(search_node->JourneyCode==JourneyCode && search_node->price==price) {
                return false;
            }
            else if(price<=search_node->price) {
                if(search_node->left==nullptr) {
                    TreeNode* new_node = new TreeNode();
                    new_node->left=nullptr;
                    new_node->right=nullptr;
                    new_node->parent=search_node;
                    new_node->JourneyCode=JourneyCode;
                    new_node->price=price;
                    search_node->left=new_node;
                    BST_length+=1;
                    return true;
                }
                else {
                    search_node=search_node->left;
                }
            }
            else {
                if(search_node->right==nullptr) {
                    TreeNode* new_node = new TreeNode();
                    new_node->left=nullptr;
                    new_node->right=nullptr;
                    new_node->parent=search_node;
                    new_node->JourneyCode=JourneyCode;
                    new_node->price=price;
                    search_node->right=new_node;
                    BST_length+=1;
                    return true;
                }
                else {
                    search_node=search_node->right;
                }
            }
            
        }
    }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    if(BST_length==0) return false;
    TreeNode search_node=*root;
    while(true) {
        if(search_node.JourneyCode==JourneyCode && search_node.price==price) {
            return true;
        }
        else if(price<=search_node.price) {
            if(search_node.left==nullptr) return false;
            else search_node=*(search_node.left);
        }
        else {
            if(search_node.right==nullptr) return false;
            else search_node=*(search_node.right);
        }
    }
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
    if(BST_length==0) return false;
    TreeNode* search_node=root;
    while(true) {
        if(search_node->JourneyCode==JourneyCode && search_node->price==price) {
            BST_length-=1;
            TreeNode* search_node_parent=search_node->parent;
            if(search_node_parent==nullptr) {
                if(BST_length==0) {
                    root->left=nullptr;
                    root->right=nullptr;
                    root->parent=nullptr;
                    root->price=0;
                    root->JourneyCode=-1;
                    return true;
                }
                if(search_node->left==nullptr) {
                    root=search_node->right;
                }
                else if(search_node->right==nullptr) {
                    root=search_node->left;
                }
                else {
                    TreeNode* new_node=search_node->right;
                    while(true) {
                        if(new_node->left==nullptr) break;
                        else new_node=new_node->left;
                    }
                    if(new_node->parent==search_node) {
                        new_node->left=search_node->left;
                        new_node->parent=search_node->parent;
                        root=new_node;

                        return true;
                    }
                    else {
                        (new_node->parent)->left=nullptr;
                        new_node->left=search_node->left;
                        new_node->right=search_node->right;
                        new_node->parent=search_node->parent;
                        root=new_node;

                        return true;
                    }
                }


            }
            else {
                std::string branch_of_child;
                if(search_node_parent->left==search_node) branch_of_child="left";
                else branch_of_child="right";

                if(search_node->left==nullptr && search_node->right==nullptr) {
                    if(branch_of_child=="left") search_node_parent->left=nullptr;
                    else search_node_parent->right==nullptr;
                    return true;
                }

                else if(search_node->left==nullptr) {
                    if(branch_of_child=="left") search_node_parent->left=search_node->right;
                    else search_node_parent->right=search_node->left;
                    return true;
                }

                else if(search_node->right==nullptr) {
                    if(branch_of_child=="left") search_node_parent->left=search_node->left;
                    else search_node_parent->left=search_node->left;
                    return true;
                }

                else {
                    TreeNode* new_node=search_node->right;
                    while(true) {
                        if(new_node->left==nullptr) break;
                        else new_node=new_node->left;
                    }
                    if(new_node->parent==search_node) {
                        new_node->left=search_node->left;
                        new_node->parent=search_node->parent;

                        if(branch_of_child=="left") search_node_parent->left=new_node;
                        else search_node_parent->right=new_node;

                        return true;
                    }
                    else {
                        (new_node->parent)->left=nullptr;
                        new_node->left=search_node->left;
                        new_node->right=search_node->right;
                        new_node->parent=search_node->parent;

                        if(branch_of_child=="left") search_node_parent->left=new_node;
                        else search_node_parent->right=new_node;

                        return true;
                    }
                }
            }
        }
        else if(price<=search_node->price) {
            if(search_node->left==nullptr) return false;
            else search_node=search_node->left;
        }
        else {
            if(search_node->right==nullptr) return false;
            else search_node=search_node->right;
        }
    }
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line





void BST::in_order_traverse(TreeNode* cur_node) {
    if(cur_node!=nullptr) {
        in_order_traverse(cur_node->left);
        std::cout<<cur_node->JourneyCode<<"\n";
        in_order_traverse(cur_node->right);
    }
}

void BST::pre_order_traverse(TreeNode* cur_node) {
    if(cur_node!=nullptr) {
        std::cout<<cur_node->JourneyCode<<"\n";
        pre_order_traverse(cur_node->left);
        pre_order_traverse(cur_node->right);
    }
}

void BST::post_order_traverse(TreeNode* cur_node) {
    if(cur_node!=nullptr) {
        post_order_traverse(cur_node->left);
        post_order_traverse(cur_node->right);
        std::cout<<cur_node->JourneyCode<<"\n";
    }
}

void BST::traverse(int typeOfTraversal) {   
    if(typeOfTraversal==0) in_order_traverse(root);
    else if(typeOfTraversal==1) pre_order_traverse(root);
    else post_order_traverse(root);
}

// Returns the price of the cheapest journey
int BST::getMinimum() {

    if(BST_length==0) return 0;

    TreeNode search_node=*root;
    while(true) {
        if(search_node.left==nullptr) return search_node.price;
        else search_node=*(search_node.left);
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

