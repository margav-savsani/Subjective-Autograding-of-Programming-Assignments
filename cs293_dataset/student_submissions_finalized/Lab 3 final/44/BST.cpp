#include "stdc++.h"
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

BST::BST(){root = NULL; }
BST::BST(TreeNode *root){BST::root = root;}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    if(find(JourneyCode, price)) return false; // returns false in case the entry is already present
    
    if (root == NULL){
        root->JourneyCode = JourneyCode;
        root->price = price;
        return true;
    }
    TreeNode* probe = root;
    TreeNode* probe1;

    // allocates memory for the new node
    TreeNode* newNode = new TreeNode(JourneyCode, price);

    // traverses the tree so as to find the location for the new node 
    while(probe != NULL){
        probe1 = probe;
        if (price > (probe->price)) probe = probe->right;
        else if (price < (probe->price)) probe = probe->left;
    }

    // puts the new node at the desired location  
    if(price > (probe1->price)) probe1->right = newNode;
    else if(price < (probe1->price)) probe1->left = newNode;

    newNode->parent = probe1; // updates the child pointer of the parent node
    return true;
    }

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    TreeNode* probe = root;

    while(probe!=NULL){ 
        if ((probe->JourneyCode) == JourneyCode){
            foundNode = probe; // stores the location of the searched node
            return true;
        }
        // if block that traverses along the BST
        if (price > (probe->price)) probe = (probe->right);
        else if (price < (probe->price)) probe = (probe->left);
    }
    return false;
    }
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    // remove leaf node
    // remove node with one child
    // remove node with two children

    if (find(JourneyCode, price) == true){
        if ((foundNode->right == NULL) && (foundNode->left == NULL)){
            if(((foundNode->parent)->right) == foundNode) {
                foundNode->parent->right = NULL;
            }
            else {
                foundNode->parent->left = NULL;
            }    
            return true;
        }
        if (!(foundNode->right == NULL) != !(foundNode->left == NULL)){
            if((foundNode->right) != NULL){
            (foundNode->right)->parent = foundNode->parent;
            if (((foundNode->parent)->right) == foundNode) (foundNode->parent)->right = foundNode->right;
            else (foundNode->parent)->left = foundNode->right;
            }
            else{
            (foundNode->left)->parent = foundNode->parent;
            if (((foundNode->parent)->right) == foundNode) (foundNode->parent)->right = foundNode->left;
            else (foundNode->parent)->left = foundNode->left;
            }
            return true;
        }
        if ((foundNode->right != NULL) && (foundNode->left != NULL)){
            // find successor
            // deletes successor 
            // replace it in place of the to-be deleted node
        struct TreeNode* succ_probe = successor(foundNode); // stores the successor node pointer

        // successor node values copied to be transferred into the to-be deleted node
        int JC = succ_probe->JourneyCode;
        int pr = succ_probe->price;
        struct TreeNode* foundNode1 = foundNode;

        remove(succ_probe->JourneyCode, succ_probe->price); // removes the successor node

        // copies the successor node values in the to-be deleted node
        foundNode1->JourneyCode = JC;
        foundNode1->price = pr;
        return true;
        }
    return false; 
    }
}

// finds the successor of the argument node by finding the min value in the right subtree
struct TreeNode* BST::successor(struct TreeNode* node1){
    struct TreeNode* probe = node1->right;
    while(probe->left != NULL){
        probe = probe->left;
    }
    return probe;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    // depending upon the argument of the traverse function, invoke the corresponding sub-function
    if (typeOfTraversal == 0) preOrder(root);
    else if (typeOfTraversal == 1) postOrder(root);
    else if (typeOfTraversal == 2) inOrder(root);
    return; 
    }

void BST::preOrder(struct TreeNode* probe){
    if (probe == NULL) return;
    cout << probe->JourneyCode << endl; // prints the node
    preOrder(probe->left); // recursively calls the left child
    preOrder(probe->right); // recursively calls the right child
    return;
}

void BST::postOrder(struct TreeNode* probe){
    if (probe == NULL) return;
    postOrder(probe->left); // recursively calls the left child
    postOrder(probe->right); // recursively calls the right child
    cout << probe->JourneyCode << endl; // prints the node
    return;
}

void BST::inOrder(struct TreeNode* probe){
    if (probe == NULL) return;
    inOrder(probe->left); // recursively calls the left child
    cout << probe->JourneyCode << endl; // prints the node
    inOrder(probe->right); // recursively calls the right child
    return;
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    // keeps traversing to the left of the BST until it reaches NULL
    struct TreeNode* probe = root;
    while(probe->left != NULL){
        probe = probe->left;
    }
    return probe->price; 
    }

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.

int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    up_bound = upperPriceBound;
    lower_bound = lowerPriceBound;
    inOrder_cmp(root); // inorder traversal
    return count_cmp; // the count is returned
    }

// traverses the BST inOrderly while comparing the price with the lower and upper bound at each visit
// increases the count_cmp private variable whenever the condition is met
void BST::inOrder_cmp(struct TreeNode* probe){
    if (probe == NULL) return;
    inOrder_cmp(probe->left);
    if ((probe->price) >= lower_bound && (probe->price) <= up_bound) count_cmp ++;
    inOrder_cmp(probe->right);
    return;
}

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


// int main(){
//     TreeNode* tr = new TreeNode(1,500);
//     const string srr;
//     BST tree;
//     //cout << tree.find(2, 1000) << endl;
//     tree.insert(2,1000);
//     tree.insert(3,700);
//     tree.insert(4, 2000);
//     tree.insert(5, 200);
//     tree.insert(6, 100);

//    // cout << "Minimum = " << tree.getMinimum() << endl;

//     tree.printBST(srr);
//    cout << tree.remove(2, 1000) << endl;
//     cout << " " << endl;
//     tree.printBST(srr);

//     //cout << "Minimum = " << tree.getMinimum() << endl;


//    // cout << tree.find(1, 500) << endl;
//     //cout << tree.find(2, 1000) << endl;
//     //cout << tree.find(3, 1500) << endl;
//   // tree.traverse(2);
//   // cout << (tree.successor(tr))->price;
//   // tree.printBST(srr);
//   //cout << "Count = " << tree.countJourneysInPriceBound(300, 400) << endl;
    
// //    cout << tree.getMinimum() << endl;
//     return 0;
// }