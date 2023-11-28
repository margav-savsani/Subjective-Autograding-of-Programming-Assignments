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
    // create an empty tree if nothing is specified
    this->root = nullptr;
}
BST::BST(TreeNode *root){
    // initialize the root
    this->root = root;
}

void BST::preorder(TreeNode *t){
    // added functionality for preorder traversal
    if(t == nullptr) return;
    else{
        cout << t->JourneyCode << endl;
        preorder(t->left);
        preorder(t->right);
    }
}

void BST::postorder(TreeNode *t){
    // added functionality for postorder traversal
    if(t == nullptr) return;
    else{
        postorder(t->left);
        postorder(t->right);
        cout << t->JourneyCode << endl;
    }
}

void BST::inorder(TreeNode *t){
    // added functionality for inorder traversal
    if(t == nullptr) return;
    else{
        inorder(t->left);
        cout << t->JourneyCode << " " << t->price << endl;
        inorder(t->right);
    }
}


// helper function to return number of elements in bounds
// inorder traversal is done of BST
// if visited node is in bounds, count is increased
void BST::boundHelper(TreeNode *t, int lower, int higher, int &count){
    if(t == nullptr) return;
    else{
        boundHelper(t->left, lower, higher, count);
        if(t->price <= higher && t->price >= lower) count++;
        boundHelper(t->right, lower, higher, count);
    }
}

// helper function to store BST
// preorder traversal of BST is done with a slight modification
// when we encounter nullptr, we output a sentinel character which is -1
void BST::storeHelper(TreeNode *t, ofstream &file){
    if(t == nullptr){
        file << -1 << " " << -1 << " ";
    }
    else{
        file << t->JourneyCode << " " << t->price << " ";

        storeHelper(t->left, file);
        storeHelper(t->right, file);
    }
}


// helper function for loading BST from file
// BST is recursively built
void BST::loadHelper(TreeNode *&t, TreeNode *prnt, ifstream &file){
    int jc, prc;
    file >> jc >> prc;

    if(jc == -1 && prc == -1) return;
    else{
        t = new TreeNode(jc, prc);
        t->parent = prnt;

        loadHelper(t->left, t, file);
        loadHelper(t->right, t, file);
    }
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {

    // if an empty tree then create a root node
    if(root == nullptr){
        root = new TreeNode(JourneyCode, price);
        return true;
    }

    TreeNode *ptr = root;

    // search for required node
    while(true){

        // return false if already present
        if(ptr->JourneyCode == JourneyCode && ptr->price == price){
            return false;
        }

        // go left if required key is less than or equal
        if(ptr->price >= price && ptr->left != nullptr){
            ptr = ptr->left;
        }
        // go right if required key is strictly more
        else if(ptr->price < price && ptr->right != nullptr){
            ptr = ptr->right;
        }
        // insert to left 
        else if(ptr->price >= price && ptr->left == nullptr){
            ptr->left = new TreeNode(JourneyCode, price);
            ptr->left->parent = ptr;
            return true;
        }
        // insert to right
        else if(ptr->price < price && ptr->right == nullptr){
            ptr->right = new TreeNode(JourneyCode, price);
            ptr->right->parent = ptr;
            return true;
        }
    }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    TreeNode *ptr = root;

    // same code as in insert
    while(true){
        if(ptr == nullptr){
            return false;
        }
        else if(ptr->JourneyCode == JourneyCode && ptr->price == price){
            return true;
        }
        else if(ptr->price >= price){
            ptr = ptr->left;
        }
        else{
            ptr = ptr->right;
        }
    }
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
    TreeNode *ptr = root;

    // get the pointer to node that we have to delete
    while(true){
        if(ptr == nullptr){
            return false;
        }
        else if(ptr->JourneyCode == JourneyCode && ptr->price == price){
            break;
        }
        else if(ptr->price >= price){
            ptr = ptr->left;
        }
        else{
            ptr = ptr->right;
        }
    }

    // if the node we want to delete is root node
    if(ptr == root){

        // if root node is a leaf
        if(ptr->left == nullptr && ptr->right == nullptr){
            delete root;
            root = nullptr;
            return true;
        }

        // if left child of root node is empty
        else if(ptr->left == nullptr && ptr->right != nullptr){
            TreeNode *p = ptr->right;
            delete root;
            root = p;
            root->parent = nullptr;
            return true;
        }

        // if right child of root node is empty
        else if(ptr->left != nullptr && ptr->right == nullptr){
            TreeNode *p = ptr->left;
            delete root;
            root = p;
            root->parent == nullptr;
            return true;
        }

        // if root node has both children
        else{
            TreeNode *xd = ptr->left;

            while(true){
                if(xd->right == nullptr){
                    break;
                }
                else{
                    xd = xd->right;
                }
            }

            int reqJourneyCode = xd->JourneyCode;
            int reqPrice = xd->price;

            remove(reqJourneyCode, reqPrice);

            ptr->JourneyCode = reqJourneyCode;
            ptr->price = reqPrice;

            return true;
        }
    }


    // for nodes which are not root nodes

    TreeNode *prnt = ptr->parent;
    TreeNode **prntToChild;


    if(prnt->left != nullptr){
        if(prnt->left->JourneyCode == ptr->JourneyCode && prnt->left->price == ptr->price){
            prntToChild = &(prnt->left);
        }
    }

    if(prnt->right != nullptr){
        if(prnt->right->JourneyCode == ptr->JourneyCode && prnt->right->price == ptr->price){
            prntToChild = &(prnt->right);
        }
    }

    // if node is a leaf
    if(ptr->left== nullptr && ptr->right == nullptr){
        delete *prntToChild;
        *prntToChild = nullptr;
        return true;
    }

    // only left child empty
    else if(ptr->left == nullptr){
        TreeNode *temp = ptr->right;

        delete *prntToChild;
        *prntToChild = temp;
        temp->parent = prnt;
        return true;
    }

    // only right child empty
    else if(ptr->right == nullptr){
        TreeNode *temp = ptr->left;

        delete *prntToChild;
        *prntToChild = temp;
        temp->parent = prnt;
        return true;
    }

    // node has both children
    else{
        TreeNode *xd = ptr->left;

        while(true){
            if(xd->right == nullptr){
                break;
            }
            else{
                xd = xd->right;
            }
        }

        int reqJourneyCode = xd->JourneyCode;
        int reqPrice = xd->price;

        remove(reqJourneyCode, reqPrice);

        ptr->JourneyCode = reqJourneyCode;
        ptr->price = reqPrice;

        return true;
    }
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal == PRE_ORDER){
        preorder(root);
    }

    if(typeOfTraversal == POST_ORDER){
        postorder(root);
    }

    if(typeOfTraversal == IN_ORDER){
        inorder(root);
    }
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode *ptr = root;

    while(true){
        if(ptr->left == nullptr){
            return ptr->price;
        }
        else{
            ptr = ptr->left;
        }
    }
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    int count = 0;
    boundHelper(root, lowerPriceBound, upperPriceBound, count);
    return count;
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) {
    ofstream outfile;
    outfile.open(filename);

    storeHelper(root, outfile);

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
 
void BST::customLoad (int flag, string filename) {
    ifstream infile;
    infile.open(filename);

    // to load only left subtree
    if( flag == LOAD_LEFT_SUBTREE){
        int jc, prc;
        infile >> jc >> prc;
    }

    loadHelper(root, nullptr, infile);

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

