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

BST::BST()
{
    root = nullptr;
}
BST::BST(TreeNode *root) 
{ 
    this->root->left = root->left;
    this->root->right = root->right;
    this->root->JourneyCode = root->JourneyCode;
    this->root->parent = root->parent;
    this->root->price = root->price;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) 
{   
    if(root == nullptr){
        root = new TreeNode(JourneyCode, price, nullptr, nullptr, nullptr);
        return true;
    }
    TreeNode* tempTemp = nullptr;
    TreeNode* temp = root;
    bool isLeft = false;
    while(temp!=nullptr){
        if(temp->JourneyCode == JourneyCode && temp->price == price){
            return false;
        }
        else if(temp->price > price){
            tempTemp = temp;
            temp = temp->left;
            isLeft = true;
        }
        else{
            tempTemp = temp;
            temp = temp->right;
            isLeft = false;
        }
    }
    if(isLeft){tempTemp->left = new TreeNode(JourneyCode, price, nullptr, nullptr, tempTemp);}
    else{
        tempTemp->right = new TreeNode(JourneyCode, price, nullptr, nullptr, tempTemp);
    }
    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) 
{  
    TreeNode* temp = root;
    while(temp!= nullptr){
        if(temp->JourneyCode == JourneyCode && temp->price == price){
            return true;
        }
        else if(temp->price > price){
            temp = temp->left;
        }
        else{
            temp = temp->right;
        }
    }
    return false;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) 
{  
    TreeNode* temp = root;
    TreeNode* tempTemp = nullptr;
    // TODO root
    bool isLeft = false;
    while(temp!= nullptr){
        if(temp->JourneyCode == JourneyCode && temp->price == price){
            if(temp->right == nullptr && temp->left == nullptr){
                if(tempTemp == nullptr){
                    root = nullptr;
                    delete temp;
                }
                else if(isLeft){
                    delete temp;
                    tempTemp->left = nullptr;
                }
                else if(!isLeft){
                    delete temp;
                    tempTemp->right = nullptr;
                }
            }
            else if(temp->left != nullptr && temp->right == nullptr){
                if(tempTemp == nullptr){
                    root = temp->left;
                    delete temp;
                }
                if(isLeft){
                    tempTemp->left = temp->left;
                    temp->left->parent = tempTemp;
                    delete temp;
                }
                else if(!isLeft){
                    tempTemp->right = temp->left;
                    temp->left->parent = tempTemp;
                    delete temp;
                }
            }
            else if(temp->right != nullptr && temp->left == nullptr){
                if(tempTemp == nullptr){
                    root = temp->right;
                    delete temp;
                }
                else if(isLeft){
                    tempTemp->left = temp->right;
                    temp->right->parent = tempTemp;
                    delete temp;
                }
                else if(!isLeft){
                    tempTemp->right = temp->right;
                    temp->right->parent = tempTemp;
                    delete temp;
                }
            }
            else {
                TreeNode* pred = predecesor(temp);
                cout << pred->price << pred->JourneyCode << endl;
                int price = pred->price; 
                int JourneyCode = pred->JourneyCode;
                remove(pred->JourneyCode, pred->price);
                temp->price = price;
                temp->JourneyCode = JourneyCode;
            }

            return true;
        }
        else if(temp->price > price){
            tempTemp = temp;
            temp = temp->left;
            isLeft = true;
        }
        else{
            tempTemp = temp;
            temp = temp->right;
            isLeft = false;
        }
    }
    return false;
}

TreeNode* BST::predecesor(TreeNode* node){
    if(node->left){
        TreeNode* temp = node;
        temp = temp->left;
        while(temp->right!=nullptr){
            temp = temp->right;
            cout << "Hello1" << endl;
        }
        return temp;
    }
    else if(node->parent){
        TreeNode* par = node->parent;
        TreeNode* temp = node;
        while(par!=nullptr){
            if(par->right == temp){
                return par;
            }
            else{
                temp = par;
                par = par->parent;
            }
        }
    }

    return nullptr;
}


// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal)
{  
    if(typeOfTraversal == PRE_ORDER){
        preOrder(root);
    }
    else if(typeOfTraversal == POST_ORDER){
        postOrder(root);
    }
    else if(typeOfTraversal == IN_ORDER){
        inOrder(root);
    }
    else{
        cout << "No such traversal defined!" << endl;
    }
}

void BST::preOrder(TreeNode* tree){
    if(tree){
        cout << tree->JourneyCode << endl;
        if(tree->left)preOrder(tree->left);
        if(tree->right)preOrder(tree->right);
    }
}

void BST::postOrder(TreeNode* tree){
    if(tree){
        if(tree->left) postOrder(tree->left);
        if(tree->right) postOrder(tree->right);
        cout << tree->JourneyCode << endl;
    }
}

void BST::inOrder(TreeNode* tree){
    if(tree){
        if(tree->left) inOrder(tree->left);
        cout << tree->JourneyCode << endl;
        if(tree->right) inOrder(tree->right);
    }
}

// Returns the price of the cheapest journey
int BST::getMinimum() 
{  
    TreeNode* temp = root;
    while(temp->left != nullptr){
        temp = temp->left;
    }
    return temp->price;
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