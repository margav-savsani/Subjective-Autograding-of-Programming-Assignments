//#include <Cstdlib>
#include <iostream>
#include "BST.h"
#include<vector>
#include<cmath>
#include <string>
#include <iostream>
#include <vector>
# include <fstream>

using namespace std;

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4
 

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS
int i=0;
int j=0;
int times=0;
BST::BST(){ root=nullptr; A = new TreeNode[64]; }
BST::BST(TreeNode *root){ this->root=root; A = new TreeNode[64]; }

void BST::hi(){}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {   //insert a node
    if ( find(JourneyCode,price) ){return false;cout<<"found";}
    TreeNode *z=&A[i];
    i++;
    z->JourneyCode=JourneyCode;
    z->price=price;
    TreeNode *y=nullptr;
    TreeNode *x=root;
    while(x!=nullptr){
        y=x; 
        if (z->price< x->price)
           x=x->left;
        else x=x->right;
    }
    z->parent=y; 
    if (y==nullptr) 
      root=z;
    else if (z->price< y->price)
      y->left =z;
    else y->right=z;
        
    return true;  
}

 struct TreeNode* BST:: search(int JourneyCode, int price){ // search and return the node
      TreeNode *x=root;
    while(x!=nullptr && JourneyCode!=x->JourneyCode && price!=x->price){
        if (price< x->price ) x=x->left;
        else x=x->right;
    }
    return x;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {  // return true if node already present 
     TreeNode *x=search(JourneyCode, price);
    if (x==nullptr) {return false;}
    else if ( JourneyCode==x->JourneyCode && price==x->price) return true;
    else return false;
}

 struct TreeNode * BST:: Succ(TreeNode *x){ // find the successor of the node
   if (x->right!=nullptr)
      return TreeMinimum(x->right);
     
    TreeNode *y =x->parent;
    while(y!=nullptr && x==y->right){
        x=y;
        y=y->parent;}
    return y;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {   //delete a node
    if (find(JourneyCode,price)==false)return false;
    else { TreeNode *z=search(JourneyCode, price);
      if (z->left==nullptr && z->right==nullptr )
         z=nullptr;
      else if (z->left==nullptr || z->right==nullptr ){
        if (z==root){
            if (z->left!=nullptr)
            root=z->left;
            else root=z->right;
        }
          else if (z->left==nullptr) {
            if (z==z->parent->left ){
                z->parent->left=z->right;
                z->right->parent=z->parent;}
            else {
                z->parent->right=z->right;
                z->right->parent=z->parent;}
          }

         else {
             if (z==z->parent->left ){
                z->parent->left=z->left;
                z->left->parent=z->parent;}
            else {
                z->parent->right=z->left;
                z->left->parent=z->parent;}
          }
      }

    else {

        TreeNode *y=Succ(z);
        if (y->right!=nullptr){
        if (y->parent->left!=nullptr)
           y->parent->left=y->right; 
        else  y->parent->right=y->right; }
        z=y;
    } return true;
    }
    
    return false; }
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST:: preorder(TreeNode *x){   // different types of traversals
    if (x==nullptr) return;
    else {cout<<x->JourneyCode<<" ";
    preorder(x->left);
    preorder(x->right);}
}

void BST:: postorder(TreeNode *x){
    if (x==nullptr) return;
    else
    {postorder(x->left);
    postorder(x->right);
    cout<<x->JourneyCode<<" ";}
}

void BST:: inorder(TreeNode *x){
    if (x==nullptr) return;
    else
    {inorder(x->left);
    cout<<x->JourneyCode<<" ";
    inorder(x->right);}
}

void BST::traverse(int typeOfTraversal) {
    if (typeOfTraversal==0) //preorder
       preorder(root);
    else if (typeOfTraversal==1) //postorder
       postorder(root);
    else if (typeOfTraversal==2) //inorder
       inorder(root);
    
    return; }

// Returns the price of the cheapest journey
int BST::getMinimum() {   // get the minimum price
    TreeNode *x=root; 
    while (x->left != nullptr){
        x=x->left;
    }
    if (x!=nullptr) return x->price;
    else return 0; }

 struct TreeNode* BST::TreeMinimum(TreeNode * x) {   
    while (x->left != nullptr){  // return the node which has minimum price
        x=x->left;
    }
    return x;}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    int count =countjourneys(root,lowerPriceBound,upperPriceBound);
    if (count>0) return count ;
    else return 0; }

int BST::countjourneys(TreeNode *x,int lowerPriceBound, int upperPriceBound) {
   if (x==nullptr) return 0;
   if (x->price >=lowerPriceBound && x->price <=upperPriceBound)
     return 1+countjourneys(x->left,lowerPriceBound,upperPriceBound)+countjourneys(x->right,lowerPriceBound,upperPriceBound);
    else if ( x->price > upperPriceBound) return countjourneys(x->left, lowerPriceBound,upperPriceBound);
    else return countjourneys(x->right, lowerPriceBound,upperPriceBound);
}


// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) { 
    ofstream outfile;
    outfile.open(filename);
    outfile.close();
    eulertraverse(filename,root);
     }

 void BST::eulertraverse(string filename, TreeNode * x) {   // euler traversal
    ofstream outfile;
    outfile.open(filename,std::ios_base::app);
    
    if (x==nullptr) return;
    outfile<< x->price<<" ";
    outfile<< x->JourneyCode<<endl;
    times++;
    eulertraverse(filename, x->left);
    if (x->left != nullptr) {outfile<< x->price<<" " ;outfile<< x->JourneyCode<< endl;times++;}
    eulertraverse(filename, x->right);
    if (x->right != nullptr) {outfile<< x->price<<" " ;outfile<< x->JourneyCode<< endl;times++;}
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
 
void BST::customLoad (int flag, string filename) { 
    ifstream inFile;
    inFile.open(filename);
    int * B ;// price 
    int *C;//journey code
    C= new int [64];
    B=new int[64];
    int n=0;
    while(n!=times) {inFile >>B[n] ;inFile >>C[n] ;
    n++;}
    inFile.close();
    TreeNode *y;
    root=&A[0];
    root->price=B[0];
    root->JourneyCode= C[0];
    y=root;
    i++;
    j++;
    while (j!=n){if (flag!=3 && y==root) break;
    if (y!=root){
    if (B[j] == y->parent->price && C[j]==y->parent->JourneyCode)
   {
    y=y->parent;
    j++;
    continue;
   }}
    if( B[j] <y->price)
    { 
    y->left =&A[i];
    y->left->price =B[j];
    y->left->JourneyCode =C[j];
    y->left->parent=y;
    i++;
    j++;
    y=y->left;}
    else{
         y->right =&A[i];
    y->right->price=B[j];
     y->right->JourneyCode=C[j];
      y->right->parent=y;
    i++;
    j++;
    y=y->right;}}

    return; }


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
