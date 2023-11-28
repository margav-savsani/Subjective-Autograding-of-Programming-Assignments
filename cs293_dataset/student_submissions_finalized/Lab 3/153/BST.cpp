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


TreeNode* makeLeaf(int, int, TreeNode*);

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

/**
 * @brief Construct a new BST::BST object. Sets the root to a nullptr.
 * 
 */
BST::BST(){
    this->root = nullptr; 
}
/**
 * @brief Construct a new BST::BST object
 * 
 * @param root The desired root of the tree. 
 */
BST::BST(TreeNode *root){
    this->root = root; 
}

/**
 * @brief Inserts the given code-price pair into the BST
 * 
 * @param JourneyCode The code identifying the journey.
 * @param price The price of the journey
 * @return true if the code-price pair was successfully added,
 * @return false if given JourneyCode is already present in the BST
 */
bool BST::insert(int JourneyCode, int price) { 
    if(this->findAndReturn(JourneyCode, price) != nullptr) return false;

    if(this->root == nullptr){
        this->root = makeLeaf(JourneyCode, price, nullptr);
        return true;
    }

    TreeNode* cur_node = this->root;
    TreeNode* prev_node = nullptr;
    
    while(cur_node != nullptr){
        if(cur_node->JourneyCode == JourneyCode) return false;
        if(price < cur_node->price){
            prev_node = cur_node;
            cur_node = prev_node->left;
        }else{
            prev_node = cur_node;
            cur_node = prev_node->right;
        }
    }

    if(price < prev_node->price && prev_node->left == nullptr){
        cur_node = makeLeaf(JourneyCode, price, prev_node);
        prev_node->left = cur_node;
    }else if(prev_node->right == nullptr){
        cur_node = makeLeaf(JourneyCode, price, prev_node);
        prev_node->right = cur_node;
    }
    return true;
}
/**
 * @brief Creates a new node as a leaf, given data parameters and the parent of the leaf 
 * 
 * @param JourneyCode The code identifying the journey
 * @param price The price of the journey
 * @param parent Parent node of the resultant leaf
 * @return TreeNode* the pointer to the leaf node created
 */
TreeNode* BST::makeLeaf(int JourneyCode, int price, TreeNode* parent){
    TreeNode* res = new TreeNode();
    res->price = price;
    res->JourneyCode = JourneyCode;
    res->parent = parent;
    res->right = nullptr;
    res->left = nullptr;

    return res;
}

/**
 * @brief Checks if the given journey code exists in the sub-tree rooted at sub_root. 
 * 
 * @param JourneyCode Code to be searched for
 * @param sub_root Root of the sub-tree to be searched
 * @return true if the JourneyCode was found in the sub-tree,
 * @return false otherwise
 */
bool BST::journeyCodeExists(int JourneyCode, TreeNode* sub_root){
    if(sub_root == nullptr) return false;

    if(sub_root->JourneyCode == JourneyCode) return true;

    return this->journeyCodeExists(JourneyCode, sub_root->left) || this->journeyCodeExists(JourneyCode, sub_root->right);
}

/**
 * @brief Searches for a node with the given attribute pair in the BST. 
 * 
 * @param JourneyCode The code to be searched for
 * @param price The price corresponding to the JourneyCode
 * @return TreeNode* the node containing the exact code-price pair, nullptr if no such node found 
 */
TreeNode* BST::findAndReturn(int JourneyCode, int price){
    TreeNode* cur_node = this->root;

    while(cur_node != nullptr){
        if(cur_node->JourneyCode==JourneyCode && cur_node->price==price) return cur_node;

        if(price < cur_node->price) cur_node = cur_node->left;
        else cur_node = cur_node->right;
    }

    return nullptr;
}
/**
 * @brief Searches for the given attribute pair in the BST. 
 * 
 * @param JourneyCode The code to be searched for
 * @param price The price corresponding to the JourneyCode
 * @return true if ticket with given pair of attributes was found,
 * @return false otherwise
 */
bool BST::find(int JourneyCode, int price) {
    return (this->findAndReturn(JourneyCode,price) != nullptr);
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
    return this->removeNode(this->findAndReturn(JourneyCode, price));
}
bool BST::removeNode(TreeNode* cur_node){
    if(cur_node == nullptr) return false;

    if(cur_node->right == nullptr && cur_node->left==nullptr){
        if(this->isLeftChild(cur_node)) cur_node->parent->left = nullptr;
        else cur_node->parent->right = nullptr;
        delete cur_node;
    }else if(cur_node->right == nullptr){
        cur_node->left->parent = cur_node->parent;

        if(this->isLeftChild(cur_node)) cur_node->parent->left = cur_node->left;
        else cur_node->parent->right = cur_node->left;

        delete cur_node;
    }else if(cur_node->left == nullptr){
        cur_node->right->parent = cur_node->parent;

        if(this->isLeftChild(cur_node)) cur_node->parent->left = cur_node->right;
        else cur_node->parent->right = cur_node->right;

        delete cur_node;
    }else{
        TreeNode* successor = this->minNode(cur_node->right);
        cur_node->price = successor->price;
        cur_node->JourneyCode = successor->JourneyCode;

        return this->removeNode(successor);
    }

    return true;
}
/**
 * @brief Checks if the node is left child of its parent; 
 * 
 * @param node The node to be checked 
 * @return true if the node is indeed a left child of the parent,
 * @return false if parent is non-existent or if node is the right child of the parent
 */
bool BST::isLeftChild(TreeNode* node){
    if(node->parent == nullptr) return false;
    return (node->parent->left == node);
}
/**
 * @brief Finds the leftmost (and thus the least in defined ordering) node in the BST 
 * 
 * @param sub_root The root of the sub-tree which is to be searched
 * @return TreeNode* the leftmost node in the BST
 */
TreeNode* BST::minNode(TreeNode* sub_root){
    if(sub_root == nullptr) return nullptr;

    TreeNode* res = sub_root;
    while(res->left != nullptr) res = res->left;

    return res;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line
void BST::traverse(int typeOfTraversal) {
    switch(typeOfTraversal){
        case PRE_ORDER:
            this->preOrderTraversal(this->root);break;
        case POST_ORDER:
            this->postOrderTraversal(this->root);break;
        case IN_ORDER:
            this->inOrderTraversal(this->root); break;
        default:
            break;
    }
}
/**
 * @brief Traverses the tree pre-order, printing the JourneyCode of the nodes reached
 * 
 * @param sub_root The root of the sub-tree whose pre-order traversal is required. 
 */
void BST::preOrderTraversal(TreeNode* sub_root){
    if(sub_root == nullptr) return;

    cout<<sub_root->JourneyCode<<"\n";
    this->preOrderTraversal(sub_root->left);
    this->preOrderTraversal(sub_root->right);
}
/**
 * @brief Traverses the tree post-order, printing the JourneyCode of the nodes reached
 * 
 * @param sub_root The root of the sub-tree whose post-order traversal is required. 
 */
void BST::postOrderTraversal(TreeNode* sub_root){
    if(sub_root == nullptr) return;

    this->postOrderTraversal(sub_root->left);
    this->postOrderTraversal(sub_root->right);
    cout<<sub_root->JourneyCode<<"\n";
}
/**
 * @brief Traverses the tree in-order, printing the JourneyCode of the nodes reached
 * 
 * @param sub_root The root of the sub-tree whose in-order traversal is required. 
 */
void BST::inOrderTraversal(TreeNode* sub_root){
    if(sub_root == nullptr) return;

    this->inOrderTraversal(sub_root->left);
    cout<<sub_root->JourneyCode<<"\n";
    this->inOrderTraversal(sub_root->right);
}

/**
 * @brief Returns the price of the cheapest journey
 * 
 * @return int the price of the cheapest journey stored in the BST
 */
int BST::getMinimum() {
    if(this->root == nullptr) return -1;

    // TreeNode* cur_node = this->root;
    // while(cur_node->left != nullptr) cur_node = cur_node->left;

    return (this->minNode(this->root))->price;
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