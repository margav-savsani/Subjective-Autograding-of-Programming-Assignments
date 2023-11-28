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
    this->root=NULL;
}
BST::BST(TreeNode *root){
    this->root=root;
}

bool Contains(int jrnycode, int val, TreeNode*& node) {
    if(node == nullptr){
        return false;
    } else if(val == node->price){
        return true;
    } else if(val < node->price){
        return Contains(jrnycode, val, node->left);
    } else{
        return Contains(jrnycode, val, node->right);
    }
}


bool Insert(int jrnycode, int val, TreeNode* node) {
    if(Contains(jrnycode,val, node)==true)return false;

    /*if(val == node->price){
        if(jrnycode == node->JourneyCode)
            return false;
    }*/
    if(val < node->price){
        if(node->left == nullptr){
            node->left = new TreeNode(jrnycode, val);
            return true;
        } else{
            return Insert(jrnycode, val, node->left);
        }
    } else if(val> node->price){
        if(node->right == nullptr){
            node->right = new TreeNode(jrnycode, val);
            return true;
        } else{
            return Insert( jrnycode,val, node->right);
        }
    }
    return false;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    bool b = false;
    if(root==nullptr){
        this->root = new TreeNode(JourneyCode,price);
        b = true;
    }
    else {
        b = Insert(JourneyCode,price,this->root);
    }
    return b;
}



// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    return Contains(JourneyCode, price, this->root);
}

TreeNode*& FindMin(TreeNode*& node) {
    if(node == nullptr){
        throw "No Min value";
    } else if(node->left == nullptr){
        return node;
    } else{
        return FindMin(node->left);
    }
}



// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise

bool Remove(int val, int jrnycode, TreeNode*& node) {
    if(node == nullptr){
        return false;
    } 
    else if (val == node->price && jrnycode == node->JourneyCode){        
        TreeNode* trash = nullptr;
        if(node->left == nullptr && node->right == nullptr){            
            trash = node;
            node = nullptr;
        }
        else if(node->left != nullptr && node->right == nullptr){            
            trash = node;
            node = node->left;
        }
        else if(node->left == nullptr && node->right != nullptr){
            trash = node;
            node = node->right;
        }
        else{            
            TreeNode*& minNode = FindMin(node->right); 
            node->price = minNode->price;
            node->JourneyCode = minNode->JourneyCode;
            Remove(minNode->price, minNode->JourneyCode, minNode);
        }
        if(trash != nullptr) {delete trash;}
        return true;
    }
    else if(val < node->price){
        Remove(val, jrnycode, node->left);
    } else{
        Remove(val,jrnycode, node->right);
    }
    return true;
}

bool BST::remove(int JourneyCode, int price) { 
    return Remove(price, JourneyCode, this->root);

}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void printInorder(struct TreeNode* node)
{
    if (node == NULL)return;
    printInorder(node->left);
    cout << node->JourneyCode << endl;
    printInorder(node->right);
}

void printPreorder(struct TreeNode* node)
{
    if (node == NULL)return;
    cout << node->JourneyCode << endl;
    printPreorder(node->left);
    printPreorder(node->right);
}

void printPostorder(struct TreeNode* node)
{
    if (node == NULL)return;
    printPostorder(node->left);
    printPostorder(node->right);
    cout << node->JourneyCode << endl;
}

void BST::traverse(int typeOfTraversal) {
    TreeNode* node =root;
    //inorder traversal
    if(typeOfTraversal==2){
        printInorder(node);
    }
    //postorder traversal
    else if (typeOfTraversal==1){
        printPostorder(node);
    }
    //preorder traversal
    else{
        printPreorder(node);
    }
    return; }

// Returns the price of the cheapest journey

TreeNode* minprice(TreeNode* node){
    if(!node) return NULL;
    if(node->left == NULL)return node;
    else return minprice(node->left);
}

int BST::getMinimum() {
    if(root==nullptr)return 0;
    else return minprice(root)->price;
}
// Part II


// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.

int journeycnt(int minval,int maxval,TreeNode* node){
    if(!node)return 0;
    else if(node->price > maxval) return journeycnt(minval,maxval,node->left);
    else if (node->price < minval) return journeycnt(minval,maxval,node->right);
    else return (journeycnt(minval,maxval,node->left) + journeycnt(minval,maxval,node->right) + 1);
}

int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    if(getMinimum()>upperPriceBound)return 0;
    return journeycnt(lowerPriceBound,upperPriceBound,root); 
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.

int sizetree(TreeNode* node){
    if(node == NULL)return 0;
    else return (sizetree(node->left)+sizetree(node->right)+1);
}

void Preorder(struct TreeNode* node, int *arrp, int *arrjc, string file)
{   
    if (node == NULL)return;
    ofstream outfile;
    outfile.open(file);
        outfile << node->price <<"  " << node->JourneyCode;
        outfile << endl;
        Preorder(node->left , arrp , arrjc , file);
        Preorder(node->right , arrp , arrjc , file);
    outfile.close();
    return;
}

void BST::customStore(string filename) { 
    int arr1[sizetree(root)]; // stores price
    int arr2[sizetree(root)]; // stores JourneyCode
    Preorder(root , arr1 , arr2 , filename);
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

TreeNode* NewNode(int jrnycode ,int val)
{
    TreeNode * node = new TreeNode();
    node->price = val;
    node->JourneyCode = jrnycode;
    node->left = node->right = NULL;
    return node;
}

TreeNode * ConstructTree(int price[] , int jrny[] , int *index ,int keyp, int keyjc, int min, int max, int size){
{
    if (*index >= size)
        return NULL;
    TreeNode* root = NULL;
    if (keyp > min && keyp < max) {
        root = NewNode(keyp,keyjc);
        *index = *index + 1;
        if (*index < size) {
            root->left = ConstructTree(price,jrny, index, price[*index], jrny[*index], min, keyp, 100000);
        }
        if (*index < size) {
            root->right = ConstructTree(price,jrny, index,price[*index],jrny[*index], keyp, max, 100000);
        }
    }
        return root;
}

}

TreeNode* constructTree(int valarr[], int jrnycodearr[] , int szval , int szjrnycode){
    int preIndex = 0;
    return ConstructTree(valarr,jrnycodearr, &preIndex, valarr[0], jrnycodearr[0], INT_MIN, INT_MAX , 100000);
}

void BST::customLoad (int flag, string filename) { 
    int N=sizetree(root);
    int A1[N]; // stores price
    int A2[N]; // stores JourneyCode
    ifstream infile;
    infile.open(filename);
    for(int i=0;i<N;i++){
        infile >> A1[i]>>A2[i];
    }
    infile.close();
    TreeNode * node = constructTree(A1, A2, N, N);
    if(flag==3) printPreorder(node);
    else printPreorder(node->left);
    return;
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

