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
    root = nullptr; 
}
BST::BST(TreeNode *root){
        this->root = root; 
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
//


bool BST::insert(int JourneyCode, int price) { 
        TreeNode *present = root;
        if(present == nullptr){
            // Tree was empty earlier, just insert it at root
            root = new TreeNode(JourneyCode, price);
            return true;
        }
        while(true){
            /* cout << "Inserting"  << endl; */
            if(present->JourneyCode == JourneyCode){
                return false;
            }
            if (price <= present->price){
                if (present->left == nullptr){
                    // Found a place to insert, present->left
                    present->left = new TreeNode(JourneyCode, price, nullptr, nullptr, present); // Make a new node with null left and right and parent = present
                    return true;
                }
                else{
                    // Keep traversing
                    present = present->left;
                    if (present == present->left){
                        cout << "Super error"  << endl;
                        return false;
                    }
                }
            }
            else{
                if (present->right == nullptr){
                    // Insert at present->right 
                    /* cout << "Inserting to the right"  << endl; */
                    present->right = new TreeNode(JourneyCode, price, nullptr, nullptr, present); // Make a new node with null left and right and parent = present
                    return true;
                }
                else{
                    present = present->right ;
                    if(present == present->right){
                        cout << "Super error in right"  << endl;
                        return false;
                    }
                }
            }
        }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
        /* cout << "Finding"  << endl; */
        TreeNode *present = root;
        // From the root, keep iterating according to the binary tree specification: if the price is <= price of present go in the left subtree else right
        // Equal value prices are sent in the left subtree
        while(present != nullptr){
            if(present->JourneyCode == JourneyCode && present->price == price){
                    return true;
                    // Entry found
            }
            if(price <= present->price){
                present = present->left;
            }
            else {
                present = present->right;
            }
        }
        return false; 
}

	
// Returns false, if JourneyCode isn't present
/* // Deletes the corresponding entry and returns True otherwise */

bool BST::remove(int JourneyCode, int price) { 
        // First find the node
        TreeNode *present = root;
        while(present != nullptr){
            if(present->JourneyCode == JourneyCode && present->price == price){
                break;
            }
            if(price <= present->price){
                present = present->left;
            }
            else {
                present = present->right;
            }
        }
        if(present == nullptr) return false;
        if(present->parent == nullptr){
            // We are deleting the root node
            TreeNode *temp = root;
            if(root == nullptr){
                // Should never happen
                return false;
            }
            if(root->right == nullptr && root->left == nullptr){
                root = nullptr;
            }
            else if (root->right == nullptr){
                root = root->left;
                root->parent = nullptr;
            }
            else if (root->left== nullptr){
                root = root->right;
                root->parent = nullptr;
            }
            else{
                
                    TreeNode *succ = root->right;
                    while(succ->left != nullptr){
                        succ = succ->left;
                    }
                    // Remove succ from its present position, it can have no children, or atmost a right subtree
                    int newprice = succ->price;
                    int newJC = succ->JourneyCode;
                    remove(newJC, newprice);
                    root->JourneyCode = newJC;
                    root->price = newprice;
                    return true;
            }
            delete temp;
            return true;
        }

        //Handle the general case when node is not the root node
        if (present->right == nullptr && present->left == nullptr){
            // Leaf node
            if(present->price > present->parent->price){
                // We are in the right child of parent
                present->parent->right = nullptr;
            }
            else{
                present->parent->left = nullptr;
            }
            delete present;
            return true;
        }
        else if(present->right == nullptr){
            //Only the left child is present
            if(present->price > present->parent->price){
                // We are in the right child of parent
                present->parent->right = present->left;
            }
            else{
                present->parent->left = present->left;
            }
            present->left->parent = present->parent;
            /* // delete present; */
            return true;
        }
        else if(present->left== nullptr){
            //Only the right child is present
            if(present->price > present->parent->price){
                // We are in the right child of parent
                present->parent->right = present->right;
            }
            else{
                present->parent->left = present->right;
            }
            present->right->parent = present->parent;
            delete present;
            return true;
        }
        else{
            // Both children are present
            // Find the successor
            TreeNode *succ = present->right;
            while(succ->left != nullptr){
                succ = succ->left;
            }
            /* cout << succ->JourneyCode  << endl; */
            // Remove succ from its present position, it can have no children, or atmost a right subtree
            int jcode = succ->JourneyCode;
            int newprice = succ->price;
            remove(jcode, newprice);
            present->JourneyCode = jcode;
            present->price = newprice;
            return true;


        }

        return false; 
}


	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
        if (typeOfTraversal == 0){
                // preorder
                BST::preorder(root);
        }        
        else if (typeOfTraversal == 1){
                // postorder
                BST::postorder(root);
        }        
        if (typeOfTraversal == 0){
                //inorder
                BST::inorder(root);
        }        
        
        return; 
}


// Now I define 3 functions for preorder postorder and inorder traversal

void BST::preorder(TreeNode *start){
    // Just the standard preorder traversal, first output root, then left and right recursively
    if(start == nullptr) return;
    cout << start->price  << endl;
    BST::inorder(start->left);
    BST::inorder(start->right);
}
void BST::postorder(TreeNode *start){
    // Just the standard postorder traversal, first left and right recursively then output the root
    if(start == nullptr) return;
    BST::inorder(start->left);
    BST::inorder(start->right);
    cout << start->price  << endl;
}
void BST::inorder(TreeNode *start){
    // Just the standard inorder traversal, first output left and then  root and then right recursively
    if(start == nullptr) return;
    BST::inorder(start->left);
    cout << start->price  << endl;
    BST::inorder(start->right);
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
        TreeNode *present = root;
        if (present == nullptr){
            // tree is empty
            // Shouldn't happen ever
            cout << "Empty tree"  << endl;
            return -1;
        }
        // Keep going left until we reach the end
        while(present->left != nullptr){
            present = present->left;
        }
        return present->price;
}


// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
//
//
//

int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
        if (root == nullptr){
            return 0;
        }
        if (root->price < lowerPriceBound){
            // Count only in the right subtree
            return BST(root->right).countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
        }
        if (root->price > upperPriceBound){
            // count only in the left subtree
            return BST(root->left).countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
        }
        // return 1+right +left
        return 1+BST(root->right).countJourneysInPriceBound(lowerPriceBound, upperPriceBound) + BST(root->left).countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.

void BST::recStore(TreeNode * base, ofstream &out){
    // When we reach a null pointer store a sentinel -1 -1, will be helpful when reading. Store it in a preorder
    if (base == nullptr){
        out << -1<< -1 << endl;
        return;
    }
    out << base->JourneyCode << " " << base->price << endl;
    recStore(base->left, out);
    recStore(base->right, out);
    return;
}

void BST::customStore(string filename) { 
        ofstream out(filename);
        // Call the recursive function
        recStore(root, out);
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

void BST::customLoadRec(ifstream &in, TreeNode *&Node){
    // We are passed a nullpointer and we change its value to whatever we get from the file
    int jc, price;
    in >> jc >> price;
    if(jc == -1 && price == -1){
        // Reached a sentinel character, don't go further in this child
        return;
    }
        Node = new TreeNode(); // Initialise the node
        Node->JourneyCode = jc;
        Node->price = price;
        // Do the same recursively
        customLoadRec(in, Node->left);
        customLoadRec(in, Node->right);
}
void BST::customLoad (int flag, string filename) { 
        ifstream in(filename);
        if(flag == LOAD_LEFT_SUBTREE){
            // Since we store in a preorder, we can just neglect the first input (which is the root) and start reading from the next entry. The recursion will end when we reach the end of the left subtree 
            int a, b;
            in >> a >> b;
        }
        customLoadRec(in, root);   
        return; 
}

// DO NOT CHANGE ANYTHING BELOW THIS LINE)
//
//

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
