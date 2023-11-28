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

BST::BST(){root=nullptr;}
BST::BST(TreeNode *root){this->root=root;}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
    TreeNode* new_node;
    new_node=new TreeNode(JourneyCode,price);
    TreeNode* x;TreeNode* y;
    x=root;
    y=nullptr;
    while(x!=nullptr){
        y=x;
        if(price==x->price) return false;
        if(price<x->price) x=x->left;
        else x=x->right;
    }
    new_node->parent=y;
    if(y==nullptr){root=new_node;}
    else if(price<y->price) y->left=new_node;
    else y->right=new_node;
    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    TreeNode* x;
    x=root;
    while(x!=nullptr && price!=x->price){
        if(price<x->price) x=x->left;
        else x=x->right;
    }
    if(x==nullptr) return false;
    else if(x->JourneyCode==JourneyCode) return true;
    else return false;
}
	
// Returns false, if price isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    if(!find(JourneyCode,price)){return false;}
    TreeNode* z;
    TreeNode* y;
    TreeNode* x;
    z=root;
    while(price!=z->price){
        if(price<z->price) z=z->left;
        else z=z->right;
    }
    if(z->left==nullptr||z->right==nullptr) y=z;
    else y=Successor(z);
    if(y->left!=nullptr) x=y->left;
    else x=y->right;
    if(x!=nullptr) x->parent=y->parent;
    if(y->parent==nullptr) root=x;
    else if(y==y->parent->left) y->parent->left=x;
    else y->parent->right=x;
    if(y!=z){
        z->JourneyCode=y->JourneyCode;
        z->price=y->price;
    }
      return true;
 }
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse_dummy(int typeOfTraversal,TreeNode* node) {
    if(typeOfTraversal==0){
     if (node!= NULL) {
      cout<<node->JourneyCode<<" ";
      traverse_dummy(0,node->left);
      traverse_dummy(0,node->right);
   }
    }
    if(typeOfTraversal==1){
     if (node != NULL) {
      traverse_dummy(1,node->left);
      traverse_dummy(1,node->right);
      cout<<node->JourneyCode<<" ";
   }
    }
    if(typeOfTraversal==2){
     if (node != NULL) {
      traverse_dummy(2,node->left);
      cout<<node->JourneyCode<<" ";
      traverse_dummy(2,node->right);
   }
    }
    return;
 }
void BST::traverse(int typeOfTraversal){
    traverse_dummy(typeOfTraversal,root);
    cout<<endl;
}
TreeNode* BST::Successor(TreeNode* y){
if(y->right!=nullptr){
    TreeNode* x;
    x=y->right;
while(x->left!=nullptr){
    x=x->left;}
return x;}
  TreeNode* z;
  z=y->parent;
  while(y!=nullptr && y==z->right){
    y=z;
    z=z->parent;
  }
return z;
}
// Returns the price of the cheapest journey
int BST::getMinimum() {
TreeNode* x;
    x=root;
while(x->left!=nullptr){
    x=x->left;
}
return x->price;
}
// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
void BST::Counter(TreeNode* node, int k1, int k2, int* count1)
{
    if (node!= NULL) {
      if(k1<=node->price && node->price>=k2)(*count1)++;
      Counter(node->left,k1,k2,count1);
      Counter(node->right,k1,k2,count1);
   }
   return;
}
 
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    TreeNode* x;x=root;
    TreeNode* y;y=root; 
    int count=0;
    Counter(root,lowerPriceBound,upperPriceBound,&count);
    return count;    
 }

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::populateNodesInArray(TreeNode* r, int* arr,int* arr1, int pos)
{
    if(r == nullptr){ return; }
    arr[pos] = r->price;
    arr1[pos]= r->JourneyCode;
    if(r->left != nullptr){
        populateNodesInArray(r->left, arr, arr1 , 2*pos + 1);
    }
    if(r->right != NULL){
        populateNodesInArray(r->right, arr, arr1 , 2*pos + 2);
    }
}
void BST::treeToArray(TreeNode* node,int* arr,int* arr1,int maxNodes)
{
    // Initialize all the nodes with -1
    for(int i=0; i<maxNodes; i++){
        arr[i] = -1;
        arr1[i]=-1;}
    // Populating nodes in array
    populateNodesInArray(node, arr,arr1, 0);
}
void BST::customStore(string filename) { 
    int* arr;
    int* arr1;
    arr = new int[500];
    arr1 =new int[500];
    treeToArray(root,arr,arr1,500);
    return; 
    ofstream outfile;
    outfile.open("filename");
    for(int i=0; i<500; i++){
        outfile<<arr[i]<<arr1[i];
    }
    outfile<<endl;
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
void BST::populateTreeFromArray(TreeNode* r, int* arr, int* arr1,int n, int pos)
{
    if(r == NULL || arr == NULL || n==0){ return; }
    // Setting the left subtree of root
    int newPos = 2*pos+1;
    if(newPos < n && arr[newPos] != -1)
    {
        r->left = new TreeNode(arr[newPos],arr1[newPos]);
        populateTreeFromArray(r->left, arr, arr1, n, newPos);
    }
    // Setting the Right subtree of root
    newPos = 2*pos+2;
    if(newPos < n && arr[newPos] != -1)
    {
        r->right = new TreeNode(arr[newPos],arr[newPos]);
        populateTreeFromArray(r->right, arr, arr1 , n, newPos);
    }
}
TreeNode* BST::arrayToTree(int* arr, int n ,int* arr1)
{
    if(arr == nullptr || arr[0] == -1){ return nullptr; }
    // We will populate the root node here
    // and leave the responsibility of populating rest of tree
    // to the recursive function
    TreeNode* root1 = new TreeNode(arr[0],arr1[0]);
    populateTreeFromArray(root1, arr, arr1, n, 0);
    return root1;
}
void BST::customLoad (int flag, string filename) { 
    ifstream infile;
    infile.open("filename");
    int* arr; int* arr1;
    arr=new int[500];
    arr1=new int[500];
    int i=0;
    while(!infile.eof()){
        int data;
        infile>>data;
        arr[i]=data;
        infile>>data;
        arr1[i]=data;
    }
    if(flag==3){ 
    root=arrayToTree(arr,500,arr1);
    return; }
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
