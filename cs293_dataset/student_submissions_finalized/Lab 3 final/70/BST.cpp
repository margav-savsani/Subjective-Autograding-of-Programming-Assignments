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
    root = NULL;
    }
BST::BST(TreeNode *root){
    this->root = root; 
    }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
    TreeNode* node2b = new TreeNode(JourneyCode, price);
    TreeNode* tempp = NULL;
    TreeNode* tempn = root; 
    while(tempn != nullptr){
        tempp = tempn;
        if(node2b->price == tempn->price && node2b->JourneyCode == tempn->JourneyCode){
            return false;
        }
        else if(node2b->price < tempn->price){
            tempn = tempn->left;
        }
        else{
            tempn = tempn->right;
        }
    }
    node2b->parent = tempp;
    if(tempp == nullptr){
        root = node2b;
    }
    else if(price < tempp->price){
        tempp->left = node2b;
    }
    else {
        tempp->right = node2b;
    }
    return true;
    }

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    TreeNode* tempn = root;
    while(tempn!=nullptr && price!=tempn->price){
        if(price < tempn->price){
            tempn = tempn->left;
        }
        else{
            tempn = tempn->right;
        }
    }
    if(tempn==nullptr) return false;
    if(tempn->JourneyCode==JourneyCode && tempn->price==price){
        return true;
    }
    return false;
}

TreeNode* BST::successor(TreeNode* node){
    if(!find(node->JourneyCode, node->price)) return NULL;
    if(node->right!=nullptr){
        node = node->right;
        while(node->left!=nullptr){
            node = node->left;
        }
        return node;
    }
    TreeNode* temp;
    temp = node->parent;
    while(temp!=nullptr && node==temp->right){
        node = temp;
        temp = temp->parent;
    }
    return temp;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
    if(!find(JourneyCode, price)) return false;
    TreeNode* tempn = root;
    while(tempn!=nullptr && price!=tempn->price){
        if(price < tempn->price){
            tempn = tempn->left;
        }
        else{
            tempn = tempn->right;
        }
    }
    TreeNode* node = new TreeNode();
    TreeNode* x = new TreeNode();
    if(tempn->left==nullptr || tempn->right==nullptr){
        node = tempn;
    }
    else{
        node = successor(tempn);
    }
    if(node->left!=nullptr){
        x = node->left;
    }
    else{
        x = node->right;
    }
    if(x!=nullptr){
        x->parent = node->parent;
    }
    if(node->parent==nullptr){
        root = x;
    }
    else if(node == node->parent->left){
        node->parent->left = x;
    }
    else{
        node->parent->right = x;
    }
    if(node!=tempn){
        tempn->price = node->price;
        tempn->JourneyCode = node->JourneyCode;
    }
    return true;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line
void BST::writeInFile(TreeNode* node, ofstream* filename){
    if(filename == nullptr) return;
    //ofstream BSTfile;
    //BSTfile.open(filename);
    *filename << node->JourneyCode << " " << node->price <<endl;
    //BSTfile.close();
}
void BST::preorderTraverse(TreeNode* node, ofstream* filename){
    TreeNode* dividingNode = new TreeNode(0,-1);
    if(node==nullptr) return;
    else{
        if(filename==nullptr){
            cout<<node->JourneyCode<<endl;
        }
        writeInFile(node, &(*filename));
        preorderTraverse(node->left, &(*filename));
        if(node==root){
            writeInFile(dividingNode, &(*filename));
        }
        preorderTraverse(node->right, &(*filename));
    }
} 
void BST::postorderTraverse(TreeNode* node){
    if(node==nullptr) return;
    else{
        postorderTraverse(node->left);
        postorderTraverse(node->right);
        cout<<node->JourneyCode<<endl;
    }
} 
void BST::inorderTraverse(TreeNode* node){
    if(node==nullptr) return;
    else{
        inorderTraverse(node->left);
        cout<<node->JourneyCode<<endl;
        inorderTraverse(node->right);
    }
} 

void BST::traverse(int typeOfTraversal, ofstream* filename=NULL) {
    if(typeOfTraversal==0){
        preorderTraverse(root, &(*filename));
    }
    else if(typeOfTraversal==1){
        postorderTraverse(root);
    }
    else{
        inorderTraverse(root);
    }
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode* node = root;
    if(node==nullptr) return -1;
    while(node->left!=nullptr){
        node = node->left;
    }
    return node->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    if(root==nullptr) return 0;
    TreeNode* node = root;
    while(node!=nullptr && node->price!=lowerPriceBound){
        if(lowerPriceBound < node->price){
            if(node->left!=nullptr){
                node = node->left;
            }
            else break;
        }
        else{
            if(node->right!=nullptr){
                node = node->right;
            }
            else break;
        }
    }
    int countJourneys = 1;
    while(node!=nullptr){
        node = successor(node);
        if(node==nullptr) break;
        if(node->price <= upperPriceBound){
            countJourneys++;
        }
    }
    return countJourneys;
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) {
    ofstream BSTfile;
    BSTfile.open(filename);
    traverse(0, &BSTfile);
    BSTfile.close();
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
vector<string> temp;
void separate (string str, char seperator)  
{  
    temp.clear();
    int currIndex = 0, i = 0;  
    int startIndex = 0, endIndex = 0;  
    while (i <= str.length())  
    {  
        if (str[i] == seperator || i == str.length())  
        {  
            endIndex = i;
            temp.push_back(str.substr(startIndex,endIndex-startIndex));
            startIndex = endIndex + 1;  
        }  
        i++;  
        }     
} 
 
void BST::customLoad (int flag, string filename) {
    ifstream infile ;
    infile.open(filename);
    while(!infile.eof()){
        string s;
        getline(infile, s);
        separate(s,' ');
        if(flag==4 && stoi(temp[0])==0) break;
        else if(stoi(temp[0])==0) continue;
        insert(stoi(temp[0]), stoi(temp[1]));
    }
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
