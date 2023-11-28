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
    this->root->parent = nullptr;
}
BST::BST(TreeNode *root){
    this->root = root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

bool BST::insert(int JourneyCode, int price) { // time : O(h), h is height of the tree
    /* this has been iteratively written. If two journeys have the same price,
    we go to the right subtree */
    TreeNode * A = this->root;
    while (true){
        if (root == nullptr){
            root = new TreeNode(JourneyCode, price);
            return 1;
        }
        if (A->parent == nullptr && A->JourneyCode == 0 && A->price == 0){
            A->JourneyCode = JourneyCode;
            A->price = price;
            return 1;
        }
        if (A->JourneyCode == JourneyCode && A->price == price){
            return 0;
        }

        if (price >= A->price && A->right != nullptr){
            A = A->right;
            continue;
        }
        else if (price < A->price && A->left != nullptr){
            A = A->left;
            continue;
        }
        else if (price < A->price && A->left == nullptr){
            A->left = new TreeNode(JourneyCode, price);
            A->left->parent = A;
            return 1;
        }
        else if (price >= A->price && A->right == nullptr){
            A->right = new TreeNode(JourneyCode, price);
            A->right->parent = A;
            return 1;
        }
    }
    return false;
}

// Return True, if the ticket with given attributes is found, false otherwise

bool BST::find(int JourneyCode, int price) { // time: O(h), h is height of the tree
    /* this has been iteratively written. If two journeys have the same price,
    we go to the right subtree */ 
    TreeNode * A = this->root;
    while(true){
        if (A->price == price){
            if (A->JourneyCode == JourneyCode){
                return 1;
            }
            else if (A->right != nullptr){
                A = A->right;
                continue;
            }
            else if(A->left != nullptr){
                A = A->left;
                continue;
            }
            return 0;
        }
        else if(A->price > price){
            if (A->left == nullptr){
                return 0;
            }
            A = A->left;
            continue;
        }
        else if(A->price < price){
            if (A->right == nullptr){
                return 0;
            }
            A = A->right;
            continue;
        }
    }
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise

bool BST::remove(int JourneyCode, int price) {  // time : O(h), h is height of the tree 
    /* this has been written iteratively */

    TreeNode * A = root;
    while(true){
        // find the node to be deleted first
        if (A->price == price){
            if (A->JourneyCode == JourneyCode){  
                break;
            }
            else if (A->right != nullptr){
                A = A->right;
                continue;
            }
            else if(A->left != nullptr){
                A = A->left;
                continue;
            }
            return 0;
        }
        else if(A->price > price){
            if (A->left == nullptr){
                return 0;
            }
            A = A->left;
            continue;
        }
        else if(A->price < price){
            if (A->right == nullptr){
                return 0;
            }
            A = A->right;
            continue;
        }
    }
    // first handle the cases of deleting the root.
    if (A == root){
        if (A->left == nullptr && A->right == nullptr){
         
           root = nullptr;
            return 1;
        }
        else if (A->left == nullptr){
            A->right->parent = nullptr;
            root = A->right;
            delete A;
            return 1;
        }
        else if (A->right == nullptr){
            A->left->parent = nullptr;
            root = A->left;
            delete A;
            return 1;
        }
        // finds the successor
        TreeNode *B = A->right;
        while(B->left != nullptr){
            B = B->left;
        } 
        if (B == A->right){
            B->parent = nullptr;
            A->left->parent = B;
            B->left = A->left;
            root = B;
            delete A;
            return 1;
        }
        if (B->parent->left == B){
            B->parent->left = B->right;
        }
        else if (B->parent->right == B){
            B->parent->right = B->right;
        }
        if (B->right != nullptr){
            B->right->parent = B->parent;
        }
        B->right = A->right;
        A->right->parent = B;
        A->left->parent = B;
        B->left = A->left;
        B->parent = nullptr;
        root = B;
        delete A;
        return 1;
    }
    // if node to be deleted is not he root node.
    if (A->left == nullptr && A->right == nullptr){
        if (A->parent->left == A){
            A->parent->left = nullptr;
            delete A; 
            return 1;
        }
        else if (A->parent->right == A){
            A->parent->right = nullptr;
            delete A; 
            return 1;
        }
    }
    
    else if (A->left == nullptr){
        if (A->parent->left == A){
            A->parent->left = A->right;
            A->right->parent = A->parent;
        }
        else if (A->parent->right == A){
            A->parent->right = A->right;
            A->right->parent = A->parent;
        }
        delete A;
        return 1;
    }
    else if (A->right == nullptr){
        if (A->parent->left == A){
            A->parent->left = A->left;
            A->left->parent = A->parent;
        }
        else if (A->parent->right == A){
            A->parent->right = A->left;
            A->left->parent = A->parent;
        }
        delete A;
        return 1;
    }
    TreeNode *B = A->right;
    while(B->left != nullptr){
        B = B->left;
    } 
    if (B == A->right){
        B->parent = A->parent;
        B->left = A->left;
        A->left->parent = B;
        if (A->parent->left == A){
            A->parent->left = B;
        }
        else if (A->parent->right == A){
            A->parent->right = B;
        }
        delete A;
        return 1;
    }
    if (B->parent->left == B){
        B->parent->left = B->right;
    }

    if (B->right != nullptr){
        B->right->parent = B->parent;
    }
    B->right = A->right;
    A->right->parent = B;
    B->left = A->left;
    A->left->parent = B;
    B->parent = A->parent;
    if (A->parent->left == A){
        A->parent->left = B;
    }
    else if (A->parent->right == A){
        A->parent->right = B;
    }
    delete A;
    return 1;
}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {   // time : O(n), n is the total number of nodes
    /* recursively traverse the tree in method determined by the flag */
    if (root == nullptr) return;
    TreeNode * T = root;
    if (typeOfTraversal == PRE_ORDER){
        cout << root->JourneyCode << endl;
        root = T->left;
        traverse(PRE_ORDER);
        root = T->right;
        traverse(PRE_ORDER);
    }
    else if(typeOfTraversal == POST_ORDER){
        root = T->left;
        traverse(POST_ORDER);
        root = T->right;
        traverse(POST_ORDER);
        root = T;
        cout << root->JourneyCode << endl;
    }
    else if (typeOfTraversal == IN_ORDER){
        root = T->left;
        traverse(IN_ORDER);
        root = T;
        cout << root->JourneyCode << endl;
        root = T->right;
        traverse(IN_ORDER);
    }
    root = T;
}

// Returns the price of the cheapest journey

int BST::getMinimum() {     // time : O(h), h is height of the tree
    /* goes to the leftmost node and returns */
    TreeNode * A = this->root;
    while (A->left != nullptr){
        A = A->left;
    }
    return A->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {      // worst case O(n), n is the number of nodes.
    /* recursively checks for values in range [lowerPriceBound, upperPriceBound]. If the current node satisfies
    the condition, we add 1 to the counter"*/
    TreeNode *A = root;
    if (root->left == nullptr && root->right == nullptr){
        if (root->price >= lowerPriceBound && root->price <= upperPriceBound){
            return 1;
        }
        return 0;
    } 
    else if (root->right == nullptr){
        if (root->price >= lowerPriceBound && root->price <= upperPriceBound){
            root = root->left;
            int a = countJourneysInPriceBound(lowerPriceBound, upperPriceBound);    // left subtree
            root = A;
            return 1+a;
        }
        root = root->left;
        int a = countJourneysInPriceBound(lowerPriceBound, upperPriceBound);         // left subtree
        root = A;
        return a;
    } 
    else if (root->left == nullptr){
        if (root->price >= lowerPriceBound && root->price <= upperPriceBound){
            root = root->right;
            int a = countJourneysInPriceBound(lowerPriceBound, upperPriceBound);         // right subtree
            root = A;
            return 1+a;
        }
        root = root->right;
        int a = countJourneysInPriceBound(lowerPriceBound, upperPriceBound);             // right subtree
        root = A;
        return a;
    }
    root = root->left;
    int a = countJourneysInPriceBound(lowerPriceBound, upperPriceBound);             // left subtree
    root = A->right;
    int b = countJourneysInPriceBound(lowerPriceBound, upperPriceBound);            // right subtree
    root = A;
    if (root->price >= lowerPriceBound && root->price <= upperPriceBound){
        return 1+a+b;
    }
    return a+b;
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.

void BST::customStore(string filename) {    // time: O(n), space: O(n), n is the total number of nodes.
    /* write each node as price, JourneyCode pair to the file. If we have nullptr, write "n" "n".*/
    ofstream f;
    f.open(filename, ios_base::app);
    TreeNode * A = root;
    f << root->price << " " << root->JourneyCode << " ";
    f.close();
    if (root->left == nullptr){
        f.open(filename, ios_base::app);
        f << "n" << " " << "n" << " ";
        f.close();
    }
    else {
        root = root->left;
        customStore(filename);      // recursively store the left subtree
        root = A;
    }
    f.open(filename, ios_base::app);
    f.close();
    if (root->right == nullptr){
        f.open(filename, ios_base::app);
        f << "n" << " " << "n" << " ";
        f.close();
    }
    else {
        root = root->right;
        customStore(filename);      // recursively store the right subtree
        root = A;
    }
    f.close();
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
 
void BST::customLoad (int flag, string filename) { // time: O(n), n is the total number of nodes.
    ifstream f;
    f.open(filename);
    string a,b,s;
    f >> a >> b;
    bool bo = 0;                               // is marked true if previously read value is a = "n" and b = "n"
    TreeNode * A = root;
    if (flag == LOAD_LEFT_SUBTREE){            // If we just have to load left subtree, we can ignore the first entry.
        f >> a >> b;
    }
    else if (flag != LOAD_FULL_BST){           // Incorrect flag returns.
        return;
    }
    root->price = stoi(a);
    root->JourneyCode = stoi(b);

    vector<TreeNode*> V;                        // Plays role of a stack
    V.push_back(A);                             // We push into stack, each time we create a new TreeNode.

    while (f >> a >> b && V.size() > 0){        // Break the loop if file ends or the stack becomes empty

        if (a != "n" && b != "n"){                    
            if (bo){
                bo = 0;
                V.pop_back();
                TreeNode * B = new TreeNode(stoi(b),stoi(a));   
                A->right = B;
                B->parent = A;
                A = B;
                V.push_back(A);
                continue;
            }
            bo = 0;
            TreeNode * B = new TreeNode(stoi(b),stoi(a));   
            A->left = B;
            B->parent = A;
            A = B;
            V.push_back(A);
        }
        else if (a == "n" && b == "n"){         // handles the case of nullptr
            if (bo){
                V.pop_back();
                A = V.back();
                bo = 0;
            }
            bo = 1;
            continue;
        }
    }
    f.close();
}


// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
// void BST::printBST(const string& prefix, bool isLeft=false)
// {
//     if( root != nullptr )
//     {
//         cout << prefix;

//         cout << (isLeft ? "|--" : "|__" );

//         // print the value of the node
//         cout << root->JourneyCode << endl;
//         TreeNode *curr = root;
//         root = root->left;
//         // enter the next tree level - left and right branch
//         printBST( prefix + (isLeft ? "│   " : "    "), true);
//         root = root->right;
//         printBST( prefix + (isLeft ? "│   " : "    "), false);
//         root = curr;
//     }
// }

void BST::printBST(const string& prefix, bool isLeft=false)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->JourneyCode << endl;
        TreeNode *curr = root;
        root = curr->left;
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

