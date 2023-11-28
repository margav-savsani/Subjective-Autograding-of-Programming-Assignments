#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
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
    this->root = nullptr;
}

BST::BST(TreeNode *root)
{
    this->root = new TreeNode(root->JourneyCode, root->price, root->left = nullptr, root->right = nullptr, root->parent = nullptr);
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{
    if (root == nullptr)
    {
        root = new TreeNode(JourneyCode, price);
        return true;
    }

    else
    {
        TreeNode *Root = root;
        while (true)
        {
            if (Root->JourneyCode == JourneyCode)
            {
                return false;
            }
            if (Root->price < price)
            {
                if (Root->right == NULL)
                {
                    Root->right = new TreeNode(JourneyCode, price, nullptr, nullptr, Root);
                    return true;
                }
                else
                {
                    Root = Root->right;
                    continue;
                }
            }
            else
            {
                if (Root->left == NULL)
                {
                    Root->left = new TreeNode(JourneyCode, price, nullptr, nullptr, Root);
                    return true;
                }
                else
                {
                    Root = Root->left;
                    continue;
                }
            }
        }
    }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{

    if (root == nullptr)
    {
        return false;
    }
    TreeNode *Root = root;
    while (true)
    {
        if (Root->price == price && Root->JourneyCode == JourneyCode)
        {
            return true;
        }
        else
        {
            if (Root->price < price)
            {
                if (Root->right == nullptr)
                {
                    //  delete[] Root;
                    return false;
                }
                else
                {
                    Root = Root->right;
                    continue;
                }
            }
            else
            {
                if (Root->left == nullptr)
                {
                    //  delete[] Root
                    return false;
                }
                else
                {
                    Root = Root->left;
                    continue;
                }
            }
        }
    }
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    TreeNode *Root = root;
    while (true)
    {
        if (Root == nullptr)
        {
            return false;
        }
        if (Root->JourneyCode == JourneyCode && Root->price == price)
        {
            if (Root == root)
            {
                if (Root->left == nullptr && Root->right == nullptr)
                {
                    root = nullptr;
                    return true;
                }
                else if (Root->left == nullptr)
                {
                    root = Root->right;
                    root->parent = nullptr;
                    delete[] Root;
                    return true;
                }
                else if (Root->right == nullptr)
                {
                    root = Root->left;
                    root->parent = nullptr;
                    delete[] Root;
                    return true;
                }
                else
                {
                    TreeNode *pred = Root;
                    pred = pred->left;
                    while (pred->right != nullptr)
                    {
                        pred = pred->right;
                    }
                    Root->JourneyCode = pred->JourneyCode;
                    Root->price = pred->price;
                    Root->left = pred->left;

                    if (pred->left != nullptr)
                    {
                        pred->parent->right = pred->left;
                        pred->left->parent = pred->parent;
                        delete[] pred;
                        return true;
                    }
                    else
                    {
                        delete[] pred;
                        return true;
                    }
                }
            }
            else if (Root->left == nullptr && Root->right == nullptr)
            {
                if (Root->parent->left == Root)
                {
                    Root->parent->left = nullptr;
                }
                else if (Root->parent->right == Root)
                {
                    Root->parent->right = nullptr;
                }
                delete[] Root;
                return true;
            }
            else if (Root->left == nullptr)
            {
                if (Root->parent->left == Root)
                {
                    Root->parent->left = Root->right;
                    Root->right->parent = Root->parent;
                    delete[] Root;
                    return true;
                }
                else if (Root->parent->right == Root)
                {
                    Root->parent->right = Root->right;
                    Root->right->parent = Root->parent;
                    delete[] Root;
                    return true;
                }
            }
            else if (Root->right == nullptr)
            {
                if (Root->parent->left == Root)
                {
                    Root->parent->left = Root->left;
                    Root->left->parent = Root->parent;
                    delete[] Root;
                    return true;
                }
                else if (Root->parent->right == Root)
                {
                    Root->parent->right = Root->left;
                    Root->left->parent = Root->parent;
                    delete[] Root;
                    return true;
                }
            }
            else
            {
                TreeNode *pred = Root->left;
                while (pred->right != nullptr)
                {
                    pred = pred->right;
                }
                Root->JourneyCode = pred->JourneyCode;
                Root->price = pred->price;
                Root->left = pred->left;
                if (pred->left != nullptr)
                {
                    pred->parent->right = pred->left;
                    // pred->left->parent=pred->parent;
                    delete[] pred;
                    return true;
                }
                else
                {
                    pred->parent->left = nullptr;
                    delete[] pred;
                    return true;
                }
            }
        }
        else if (Root->price < price)
        {
            Root = Root->right;
            continue;
        }
        else
        {
            Root = Root->left;
            continue;
        }
    }
}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal)
{
    if (root == nullptr)
        return;
    TreeNode *Root = root;
    recursive_traverse(root, typeOfTraversal);
    return;
}

void BST::recursive_traverse(TreeNode *node, int typeOfTraversal)
{
    if (typeOfTraversal == 0)
    {
        if (node == nullptr)
            return;
        cout << node->JourneyCode << endl;
        recursive_traverse(node->left, typeOfTraversal);
        recursive_traverse(node->right, typeOfTraversal);
    }
    else if (typeOfTraversal == 1)
    {
        if (node == nullptr)
            return;
        recursive_traverse(node->left, typeOfTraversal);
        recursive_traverse(node->right, typeOfTraversal);
        cout << node->JourneyCode << endl;
    }
    else if (typeOfTraversal == 2)
    {
        if (node == nullptr)
            return;
        recursive_traverse(node->left, typeOfTraversal);
        cout << node->JourneyCode << endl;
        recursive_traverse(node->right, typeOfTraversal);
    }
    return;
}

// Returns the price of the cheapest journey
int BST::getMinimum()
{
    if (root == nullptr)
        return 0;
    TreeNode *Root = root;
    int min = Root->price;
    while (true)
    {
        if (Root->left == nullptr)
        {
            break;
        }
        else
        {
            Root = Root->left;
            min = Root->price;
        }
    }
    return min;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound)
{
    if (root == nullptr)
        return 0;
    int count = countPrice(root, lowerPriceBound, upperPriceBound);
    return count;
}

int BST::countPrice(TreeNode *node, int lowerLimit, int upperLimit)
{
    if (node == nullptr)
        return 0;
    else if (node->price == lowerLimit && node->price == upperLimit)
        return 1;
    else if (node->price >= lowerLimit && node->price <= upperLimit)
    {
        return countPrice(node->left, lowerLimit, upperLimit) + countPrice(node->right, lowerLimit, upperLimit) + 1;
    }
    else if (node->price > upperLimit)
    {
        return countPrice(node->left, upperLimit, lowerLimit);
    }
    else
    {
        return countPrice(node->right, lowerLimit, upperLimit);
    }
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename)
{
    int h=height(root);
    int maxnode=pow(2,h) -1;
    int *store=new int[maxnode];
    int *price_store=new int[maxnode];
    for(int i=0; i<maxnode; i++){
        store[i]=-1;
        price_store[i]=-1;
    }
    
    ofstream outfile;
    outfile.open(filename);
    Store(root,store,price_store,0);
    for(int i=0;i<maxnode;i++){
        outfile<<store[i]<<" "<<price_store[i]<<endl;
    }
    outfile.close();
    delete[] store;
    return;
}

//level order traversal (read from intenet)
void BST:: Store(TreeNode * node, int *arr,int* price_arr,int lctn){
    if (node == nullptr){  
        return;
    }
    arr[lctn]=node->JourneyCode;
    price_arr[lctn]=node->price;
    if (node->left != nullptr){
        Store(node->left,arr,price_arr,(2*lctn)+1);
    }
    if (node->right != nullptr){
        Store(node->right,arr,price_arr,(2*lctn)+2);
    }
    return;
}

// Returns height of tree given its root
int BST::height(TreeNode * node){
    if (node == NULL) return 0;
    else
        return 1 + max(height(node->left), height(node->right));
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
    ifstream infile;
    infile.open(filename);
        int r1;
        infile>>r1;
        int r2;
        infile>>r2;
        if(r1==-1){
            return;
        }
        else{
            int root_pos=0;
            root = new TreeNode(r1,r2);
            int h=height(root);
            int **arr= new int*[2*h+1];
            
            for(int i=0;i<2*h+1;i++){
                arr[i]=new int[2];
                infile >> arr[i][0];
                infile >> arr[i][1];
            }
            if(flag==LOAD_FULL_BST){ 
                recursive_load(root,arr,0,2*h+1);
            }
            else if(flag==LOAD_LEFT_SUBTREE){
                if(arr[1][0]==-1) return;
                TreeNode *root2= new TreeNode(arr[1][0],arr[1][1]);  //simply changed the root to left child of root and load its full tree
                recursive_load(root2,arr,1,2*h+1); 
            }
    }
    return;
}

void BST::recursive_load(TreeNode * node,int **arr, int pstn,int max){
    if(node==nullptr){
        return;
    }
     
        int pstn_2=2*pstn+1;
        if(pstn_2<max ){
            if(arr[pstn_2][0]!=-1){
                node->left=new TreeNode(arr[pstn_2][0],arr[pstn_2][1]);
                recursive_load(node->right,arr,pstn_2,max);
            }
            pstn_2=2*pstn+2;
            if(pstn_2<max){
                if(arr[pstn_2][0]!=-1){
                    node->right=new TreeNode(arr[pstn_2][0],arr[pstn_2][1]);
                    recursive_load(node->right,arr,pstn_2,max);
                }
            }
        }
    
}

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
        result.push_back(to_string(root->JourneyCode) + "\n");
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
