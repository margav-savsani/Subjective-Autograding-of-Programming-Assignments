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

BST::BST()
{
    root = nullptr;
}
BST::BST(TreeNode *root)
{
    this->root = root;
    (this->root)->parent = nullptr;
}

// Returns false, if given JourneyCode is already present in the BST
// nodeerts the element and returns  True otherwise
bool BST::insert(int JourneyCode, int price)
{

    TreeNode *father = nullptr;
    TreeNode *son = root;
    // IMPORTANT- We have to create a new node(dynamic) each and every time to get a different address. If we donot add new, then the node created gets the same address as of root. To overcome this, always create a new node.
    TreeNode *node = new TreeNode(JourneyCode, price);

    while (son != nullptr)
    {
        father = son;

        if ((son->JourneyCode == node->JourneyCode) && (son->price == node->price))
        {
            return false;
        }
        if (node->price <= father->price)
        {
            son = father->left;
        }
        else
        {
            son = father->right;
        }
    }

    node->parent = father;
    if (father == nullptr)
    {
        root = node;
    }
    else if (node->price <= father->price)
    {
        father->left = node;
    }
    else
    {
        father->right = node;
    }
    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    TreeNode *node = new TreeNode(JourneyCode, price);
    TreeNode *start;
    start = root;
    while (start != NULL)
    {
        if (start->JourneyCode == node->JourneyCode && start->price == node->price)
        {
            return true;
        }
        else if (node->price <= start->price)
        {
            start = start->left;
        }
        else
        {
            start = start->right;
        }
    }
    return false;
}
//Function defined for finding the node in tree;
TreeNode* BST::getNode(int JourneyCode, int price){
    TreeNode *node = new TreeNode(JourneyCode, price);
    TreeNode *start;
    start = root;
    while (start != NULL)
    {
        //cout<<"getNode"<<endl;
        if (start->JourneyCode == node->JourneyCode && start->price == node->price)
        {
            // cout<<"if"<<endl;
            // cout<<start->JourneyCode<<" "<<start->price<<endl;
            return start;
        }
        else if (node->price <= start->price)
        {
            start = start->left;
        }
        else
        {
            start = start->right;
        }
    }
    return nullptr;
}
TreeNode* BST::getSuccessor(TreeNode* node){
    TreeNode* start = node;
    TreeNode* pstart = start->parent;
        // cout<<"Succ"<<endl;
        if(start->right!=nullptr){
            pstart = start;
            start = start->right;
            while(start->left != nullptr){
                pstart = start;
                start = start->left;
                return start;
            }
            // cout<<"enter1"<<endl;
            
        }
        else{
            pstart = start->parent;
            while(pstart->left != start){
                start = pstart;
                pstart = pstart->parent;
                return pstart;
            }
            
        }
        // cout<<pstart->JourneyCode<<" "<<pstart->price<<endl;
        // return start;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise

bool BST::remove(int JourneyCode, int price)
{
    TreeNode *node = getNode(JourneyCode, price);
    cout<<node->JourneyCode<<" "<<node->price<<endl;
    TreeNode* x;
    TreeNode* y;
    if(node==nullptr){
        return false;
    }
    else{
        if(node->left == nullptr || node->right==nullptr){
            y = node;
        }
        else{y=getSuccessor(node);}
        if(y->left!=nullptr){
            x = y->left;
        }
        else x = y->right;
        if(x!=nullptr){
            x->parent=y->parent;
        }
        if(y->parent==nullptr){
            root = x;
        }
        else if( y = y->parent->left){
            y->parent->left=x;
        }
        else{
            y->parent->right=x;
        }
        if (y!=node){
            node->JourneyCode = y->JourneyCode;
            node->price=y->price;
        }

    }
    return true;
    
}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line
void BST::post_order(TreeNode *node){
    if(node == nullptr){
        return;
    }
    else{
        post_order(node->left);
        post_order(node->right);
        cout<<node->JourneyCode<<endl;
    }
}
void BST::pre_order(TreeNode *node){
    if(node == nullptr){
        return;
    }
    else{
        cout<<node->JourneyCode<<endl;
        pre_order(node->left);
        pre_order(node->right);
    }
}
void BST::pre_order_store(TreeNode *node, string filename){
    ofstream output;
    output.open(filename);
    if(node == nullptr){
        output<<"-1 ";
        output.close();
        return;
    }
    else{
        output<<node->JourneyCode <<"-"<<node->price<<" ";
        output.close();
        pre_order(node->left);
        pre_order(node->right);
    }
}
void BST::in_order(TreeNode *node){
    if(node == nullptr){
        return;
    }
    else{
        in_order(node->left);
        cout<<node->JourneyCode<<endl;
        in_order(node->right);
    }
}
// vector<int> BST::in_order_price(TreeNode *node){
//     TreeNode* Arr = new TreeNode[]
//     if(node == nullptr){
//         return;
//     }
//     else{
//         in_order(node->left);

//         //cout<<node->JourneyCode<<<<endl;
//         in_order(node->right);
//     }
// }
void BST::traverse(int typeOfTraversal){ 
    //TreeNode* start=root;
    if(POST_ORDER==typeOfTraversal){
        post_order(root);
    }
    else if(PRE_ORDER==typeOfTraversal){
        pre_order(root);
    }
    else if(IN_ORDER==typeOfTraversal){
        in_order(root);
    }
    
    return; 
    }

// Returns the price of the cheapest journey
int BST::getMinimum()
{
    TreeNode *start;
    start = root;
    while ((start->left) != nullptr)
    {
        start = start->left;
    }
    return start->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) { 
   count_recursion(root , lowerPriceBound, upperPriceBound);
}
int BST::count_recursion(TreeNode* node, int min, int max) { 
    //TreeNode* node = root;
    //int count = 0;
    if(node == nullptr){
        return 0;
    }
    if(node->price <= min){
        return count_recursion(node->right, min, max);
    }
    else if(node->price >= max){
        return count_recursion(node->left, min, max);
    }
    else{
        return 1 + count_recursion(node->left,min,max)+ count_recursion(node->right,min,max);
    }
    
    }

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) { 
    //We can just store preorder into the file as inorder is ascending order
    pre_order_store(root, filename);
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

void BST::customLoad(int flag, string filename) { 
    
    }

// ************************************************************
// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
void BST::printBST(const string &prefix, bool isLeft = false)
{
    if (root != nullptr)
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__");

        // print the value of the node
        cout << root->JourneyCode << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST(prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST(prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::getBST(const string &prefix, bool isLeft = false)
{
    if (root != nullptr)
    {
        result.push_back(prefix);

        result.push_back(isLeft ? "|--" : "|__");

        // print the value of the node
        result.push_back(root->JourneyCode + "\n");
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        getBST(prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        getBST(prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::clearResult()
{
    result.clear();
}

vector<string> BST::getResult()
{
    return result;
}
