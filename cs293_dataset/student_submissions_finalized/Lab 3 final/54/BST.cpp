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
root=NULL;
}
BST::BST(TreeNode *root){
this->root=root; 
}

int BST:: count(TreeNode *T,int lowerbound,int upperbound){
if (T==NULL) return 0;
if ((T->price==upperbound)&&(T->price==lowerbound)) return 1;
if ((T->price<=upperbound) && (T->price>=lowerbound)){
      return (1+count(T->left,lowerbound,upperbound)+count(T->right,lowerbound,upperbound));}
if (T->price < lowerbound){
      return count(T->right,lowerbound,upperbound);}
if (T->price>upperbound){
     return count(T->left,lowerbound,upperbound);}
}

TreeNode* BST::search(TreeNode *T,int price,int JourneyCode){
while (T!=NULL)
{
  if ((T->JourneyCode==JourneyCode)&&(T->price==price)){return T;} 
  if (T->price>price){ return search(T->left,price,JourneyCode);}
  if (T->price<price){return search (T->right,price,JourneyCode);}
} 
return NULL;
}

TreeNode* BST::predecessor(TreeNode *T,int price){
TreeNode* x=T;
while(x->right!=NULL)
{
  x=x->right;
}
return x;
}

void BST::POSTORDER(TreeNode *X){
if (X==NULL) return;
else{
 POSTORDER(X->left);
 POSTORDER(X->right);
 cout<<X->JourneyCode<<endl;
}   
}

void BST::INORDER(TreeNode *X){
if (X==NULL) return;
else{
  INORDER(X->left);
  cout<<X->JourneyCode<<endl;
  INORDER(X->right);
}
}

void BST:: PREORDER(TreeNode *X){
if (X==NULL) return ;
else{
 
  cout<<X->JourneyCode<<endl;
   PREORDER(X->left);
  PREORDER(X->right);
}
}


bool BST::insert(int JourneyCode,int price) {
TreeNode* A = new TreeNode;
A->price=price;
A->JourneyCode=JourneyCode;A->left=NULL;A->right=NULL; A->parent=NULL;

if (find(JourneyCode,price)) return false;
if (root==NULL) 
{
  root=A;
  return true;
}
TreeNode* x = new TreeNode;
TreeNode* y = new TreeNode;
x=root;
while(x!=NULL)
{
  if (price<x->price){
    if (x->left==NULL){ 
      x->left=y;
      y->JourneyCode=JourneyCode;
      y->price=price;
      y->parent=x;
      y->left=NULL;
      y->right=NULL;
      return true; }
    x=x->left;}
  if (price>x->price){
    if (x->right==NULL){ 
      x->right=y;
      y->JourneyCode=JourneyCode;
      y->price=price;
      y->parent=x;
      y->left=NULL;
      y->right=NULL;
      return true; }
    x=x->right;
    }
}
return true;

}

bool BST::find(int JourneyCode, int price) { 
if (root==NULL) return false;
TreeNode *x=new TreeNode;
x=root;
while (x!=NULL){
if ((x->JourneyCode==JourneyCode)&&(x->price==price)){return true;} 
if (x->price>price){x=x->left;}
else if (x->price<price) {x=x->right;}
}
return false;
}
	

bool BST::remove(int JourneyCode, int price) { 

TreeNode* x =search(root,price,JourneyCode);
if (x==NULL) {return false;}
if((root->JourneyCode==JourneyCode)&&(root->price==price)){
if((root->left==NULL)&&(root->right==NULL)){root=NULL;return true;}

if ((root->left==NULL)&&(root->right!=NULL))
{  
   root=root->right;
   root->parent=NULL;
   return true;
}
if ((root->left!=NULL)&&(root->right==NULL))
{
   root=root->left;
   root->parent=NULL;
  return true;
}
if ((root->left!=NULL)&&(root->right!=NULL))
{
 TreeNode *pre =predecessor(root->left,root->price);
 int a=0;
 int b=0;
 a=pre->price;
 b=pre->JourneyCode;
 remove(b,a);
 root->price=a;
 root->JourneyCode=b;
return true;}
}
if (x!=root){
TreeNode* p=x->parent;
if ((x->left==NULL)&&(x->right==NULL)){
  if (p->price<price){p->right=NULL;}
  else p->left=NULL;
  x=NULL;
return true;
}
if ((x->left==NULL)&&(x->right!=NULL))
{
   if (p->price<price) p->right=x->right;
   else p->left=x->right;  
   x->right->parent=p;
   return true;
}
if ((x->left!=NULL)&&(x->right==NULL))
{
   if (p->price<x->price) p->right=x->left;
   else p->left=x->left;  
   x->left->parent=p;
return true;
}
if ((x->left!=NULL)&&(x->right!=NULL))
{
 TreeNode *pre =predecessor(x->left,x->price);
 int a=0;
 int b=0;
 a=pre->price;
 b=pre->JourneyCode;
 remove(b,a);
 x->price=a;
 x->JourneyCode=b;
return true;
}
}
return true;
}



void BST::traverse(int typeOfTraversal){
  TreeNode *x=root;
if (typeOfTraversal==0){PREORDER(x);}
if (typeOfTraversal==1){POSTORDER(x);}
if (typeOfTraversal==2){INORDER(x);}
}

int BST::getMinimum(){
TreeNode *x=root;
while(x->left!=NULL)
{
  x=x->left;
}
return x->price;
}


// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
return count(root,lowerPriceBound,upperPriceBound);
}


// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) 
{ 
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
        root = root->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::getBST(const string& prefix,  bool isLeft=false)
{
    if( root != nullptr )
    {
        result.push_back(prefix);

        result.push_back(isLeft ? "├──" : "|__" );

        // print the value of the node
        result.push_back(to_string(root->JourneyCode) + "\n");
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        getBST( prefix + (isLeft ? "│   " : "    "), true);
        root = root->right;
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

