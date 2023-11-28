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
    root = nullptr;
}
BST::BST(TreeNode *root){
    this->root = root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price){
    // If tree is empty then add directly
    if(root == nullptr){
        root = new TreeNode(JourneyCode, price, nullptr, nullptr, nullptr);
        return true;
    }
    else{
        // Else go till its position then add

        TreeNode* y = nullptr;
        TreeNode* x = root;
        while(x != nullptr){
            // If already present return false
            if(x->JourneyCode == JourneyCode) return false;

            y = x;
            if(price < x->price){
                x = x->left;
            }
            else{
                x = x->right;
            }
        }

        // Now y will be the parent of node to be added
        if(price < y->price){
            y->left = new TreeNode(JourneyCode, price, nullptr, nullptr, y);
        }
        else{
            y->right = new TreeNode(JourneyCode, price, nullptr, nullptr, y);
        }

        return true;
    }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price){
    if(root == nullptr) return false;

    // If price matches then check journeycode
    if(root->price == price){
        if(root->JourneyCode == JourneyCode) return true;
        // If price is equal but journeyCode is not then search on both sides
        else{
            BST leftSubTree(root->left);
            BST rightSubTree(root->right);
            return(leftSubTree.find(JourneyCode, price) || rightSubTree.find (JourneyCode, price));
        }
    }
    // Else if price is smaller search on left
    else if(root->price > price){
        BST leftSubTree(root->left);
        return leftSubTree.find(JourneyCode, price);
    }
    // else search on right
    else{
        BST rightSubTree(root->right);
        return rightSubTree.find(JourneyCode, price);
    }
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price){
    if(root == nullptr) return false;

    // Special case for root
    if(root->JourneyCode == JourneyCode){
        TreeNode* x = root;
        // Case 1: Both child are null
        if(x->left == nullptr && x->right == nullptr){
            root = nullptr;
            delete x;
        }
        // Case 2: Left child is null
        else if(x->left == nullptr){
            root = x->right;
            x->right->parent = root;
            delete x;
        }
        // Case 3: Right child is null
        else if(x->right == nullptr){
            root = x->left;
            x->left->parent = root;
            delete x;
        }
        // Case 4: No child is null
        else{
            // Get successor
            TreeNode* z = successor(x);
            // Replace at root
            x->JourneyCode = z->JourneyCode;
            x->price = z->price;

            // Delete successor
            if(z->left == nullptr && z->right == nullptr){
                if(z->parent->left == z) z->parent->left = nullptr;
                else if(z->parent->right == z) z->parent->right = nullptr;
                delete z;
            }
            else{
                if(z->parent->left == z) z->parent->left = z->right;
                else if(z->parent->right == z) z->parent->right = z->right;
                z->right->parent = z->parent;
                delete z;
            }

        }
        return true;
    }
    
    TreeNode* x = root;
    // Find the node with matching journeyCode
    while(x != nullptr && (x->JourneyCode != JourneyCode)){
        if(price < x->price){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }
    if(x == nullptr) return false;
    else{
        TreeNode* y = x->parent;
        // Case 1: Both child are null
        if(x->left == nullptr && x->right == nullptr){
            if(y->left == x) y->left = nullptr;
            else if(y->right == x) y->right = nullptr;
            delete x;
        }
        // Case 2: Left child is null
        else if(x->left == nullptr){
            if(y->left == x) y->left = x->right;
            else if(y->right == x) y->right = x->right;
            x->right->parent = y;
            delete x;
        }
        // Case 3: Right child is null
        else if(x->right == nullptr){
            if(y->left == x) y->left = x->left;
            else if(y->right == x) y->right = x->left;
            x->left->parent = y;
            delete x;
        }
        // Case 4: No child is null
        else{
            // Get successor
            TreeNode* z = successor(x);
            // Replace at current node
            x->JourneyCode = z->JourneyCode;
            x->price = z->price;

            // Delete successor
            if(z->left == nullptr && z->right == nullptr){
                if(z->parent->left == z) z->parent->left = nullptr;
                else if(z->parent->right == z) z->parent->right = nullptr;
                delete z;
            }
            else{
                if(z->parent->left == z) z->parent->left = z->right;
                else if(z->parent->right == z) z->parent->right = z->right;
                z->right->parent = z->parent;
                delete z;
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

void BST::traverse(int typeOfTraversal){
    if(root == nullptr) return;

    BST left(root->left);
    BST right(root->right);

    if(typeOfTraversal == PRE_ORDER){
        cout << root->JourneyCode << endl;
        left.traverse(typeOfTraversal);
        right.traverse(typeOfTraversal);
    }
    else if(typeOfTraversal == IN_ORDER){
        left.traverse(typeOfTraversal);
        cout << root->JourneyCode << endl;
        right.traverse(typeOfTraversal);
    }
    else if(typeOfTraversal == POST_ORDER){
        left.traverse(typeOfTraversal);
        right.traverse(typeOfTraversal);
        cout << root->JourneyCode << endl;
    }
    else{
        cout << "INVALID TYPE OF TRAVERSAL" << endl;
    }
}

// Returns the price of the cheapest journey
int BST::getMinimum(){
    if(root == nullptr){
        cout << "No journeys available" << endl;
        return -1;
    }
    else{
        TreeNode* x = root;
        while(x->left != nullptr){
            x = x->left;
        }
        return x->price;
    }
}

// Gets pointer of node with minimum price
TreeNode* BST::minimum(TreeNode* x){
    // Get leftmost node
    while (x->left != nullptr)
    {
        x = x->left;
    }
    return x;
}

// Gets pointer to successor of given node
TreeNode* BST::successor(TreeNode* x){
    if (x->right != nullptr){
        // If right child is present then return minimum of right subtree
        return minimum(x->right);
    }
    else{
        // else find lowest ancestor whose left child is also an ancestor
        TreeNode* y = x->parent;
        while(y != nullptr && x == y->right)
        {
            x = y;
            y = y->parent;
        }
        return y;
    }
}



// Part II


// Recursive helper function for countJourneysInPriceBound
int BST::countRecursive(TreeNode* start, int lb, int ub){
    if(start == nullptr) return 0;

    // If node is in range add 1 to count
    int count = 0;
    if(lb <= start->price && start->price <= ub) count++;

    // recurr
    if(start->price <= lb){
        return count + countRecursive(start->right, lb, ub);
    }
    else if(start->price > ub){
        return count + countRecursive(start->left, lb, ub);
    }
    else{
        return count + countRecursive(start->left, lb, ub) + countRecursive(start->right, lb, ub);
    }
}

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound){
    return BST::countRecursive(root, lowerPriceBound, upperPriceBound);
}


// Recursive function to fill a vector with pointers to nodes in preorder
void BST::getPreorder(vector<TreeNode*>& v){
    if(root == nullptr) return;

    BST left(root->left);
    BST right(root->right);

    v.push_back(root);
    left.BST::getPreorder(v);
    right.BST::getPreorder(v);
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename){
    vector<TreeNode*> preorder;
    BST::getPreorder(preorder);     // fill vector with preorder

    // store in file
    ofstream storeFile;
    storeFile.open(filename);
    for (int i = 0; i < preorder.size(); i++)
    {
        storeFile << preorder[i]->JourneyCode << " " << preorder[i]->price << endl;
    }
    storeFile.close();
}
	

// Recursive function for making tree from given preorder
// Initially min will be -inf and max will be +inf
// Now make a root with preorder[i]
// get its left subtree by recurring with min=min and max=nodeValue-1
// get its right subtree by recurring with min=nodeValue and max=max
TreeNode* BST::makeTree(vector<TreeNode*>& preorder, int& i, int min, int max){
    // If vector completed then return
    if(i >= preorder.size()) return nullptr;

    // if not in range return null
    if(preorder[i]->price < min || preorder[i]->price > max){
        return nullptr;
    }
    else{
        TreeNode* root = preorder[i];
        i++;

        // get left subtree
        root->left = BST::makeTree(preorder, i, min, root->price-1);
        // get right subtree
        root->right = BST::makeTree(preorder, i, root->price, max);

        if(root->left != nullptr) root->left->parent = root;
        if(root->right != nullptr) root->right->parent = root;

        return root;
    }

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
 
void BST::customLoad (int flag, string filename){
    // make vector of nodes
    vector<TreeNode*> preorder;

    ifstream dataFile;
    dataFile.open(filename);

    // get all data if flag is for full
    if(flag == LOAD_FULL_BST){
        while (true) {
            TreeNode* x = new TreeNode;
            dataFile >> x->JourneyCode;
            dataFile >> x->price;
            if( dataFile.eof() ) break;
            preorder.push_back(x);
        }
    }
    // get only data of left tree if flag is for left only
    else if(flag == LOAD_LEFT_SUBTREE){
        int price;
        dataFile >> price; dataFile >> price;
        while (true) {
            TreeNode* x = new TreeNode;
            dataFile >> x->JourneyCode;
            dataFile >> x->price;
            if(price <= x->price) break;
            if( dataFile.eof() ) break;
            preorder.push_back(x);
        }
    }

    int i=0;
    root = BST::makeTree(preorder, i, INT_MIN, INT_MAX);
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
