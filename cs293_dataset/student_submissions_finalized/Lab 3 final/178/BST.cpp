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
 root=NULL;}
BST::BST(TreeNode *root){
    this->root=root; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    if(find(JourneyCode,price)){return false;}
     TreeNode *z = new TreeNode;
    if (root==NULL){
        root=z;
        z->price=price;
        z->JourneyCode=JourneyCode;
        z->left=NULL;
        z->right=NULL;
        return true;
    }
    TreeNode *y=NULL;
    TreeNode *t =root;

    while(t!=NULL){
    if(t->JourneyCode==JourneyCode){return false;}
    else if(t->price>=price){
        y=t;
        t=t->left;}
    else if(t->price<price){
        y=t ;
        t=t->right;}  
    }
    if(y->price>price) y->left = new TreeNode(JourneyCode,price,NULL,NULL,y);
    else y->right =  new TreeNode(JourneyCode,price,NULL,NULL,y);
    return true;
}
      
TreeNode* BST::find2(TreeNode*root,int JourneyCode, int price){
    if(root==NULL){return NULL;}
    TreeNode*t=root;
    if(t->price>price)return find2(t->left,JourneyCode,price);
    if(t->price<price)return find2(t->right,JourneyCode,price);
    if(t->price==price) return t;
       return t; }

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
TreeNode*k= find2(root, JourneyCode,  price );
if(k==NULL)return false;
return true;
}

TreeNode* BST::search(int JourneyCode, int price){
    TreeNode *t = new TreeNode;
    t=root;

     while(t!=NULL){
      if((t->JourneyCode==JourneyCode)&&(t->price==price)){return t;}
      if(t->price>price){t=t->right;}
      if(t->price<price){t=t->left;}  
    }  
    return t;
    
}      

TreeNode* BST::Minimum(TreeNode*x){
    
     while(x->left!=NULL){
       x=x->left;
    }     
    return x;
}

TreeNode* BST::Maximum(TreeNode*x){
    while (x->right!=NULL){
        x=x->right;
    }
    return x;
}

TreeNode* BST::Successor(TreeNode*x){
    if(x->right!=NULL){
        return Minimum(x->right);
    }
    else{
        return Maximum(x->left);
    }
}
// Returns false, if JourneyCode isn't present
struct TreeNode* BST:: deleteNode(struct TreeNode* root, int price)
{
    // base case
    if (root == NULL)
        return root;
  
    // If the key to be deleted is 
    // smaller than the root's
    // key, then it lies in left subtree
    if (price < root->price)
        root->left = deleteNode(root->left, price);
  
    // If the key to be deleted is
    // greater than the root's
    // key, then it lies in right subtree
    else if (price > root->price)
        root->right = deleteNode(root->right, price);
  
    // if key is same as root's key, then This is the node
    // to be deleted
    else {
        // node has no child
        if (root->left==NULL and root->right==NULL)
            return NULL;
        
        // node with only one child or no child
        else if (root->left == NULL) {
            root=root->right;
            return root;
        }
        else if (root->right == NULL) {
           root=root->left;
            return root;
        }
  
        // node with two children: Get the inorder successor
        // (smallest in the right subtree)
        struct TreeNode* temp =  Minimum(root->right);
                 
        // Copy the inorder successor's content to this node
        root->price = temp->price;
  
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->price);
    }
    return root;}
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
   
   if(!find(JourneyCode,price)) return false;
   else {
     root = deleteNode(root,price);
     return true;
   }}

	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::preorder(TreeNode*x){
    if(x!=NULL){
        cout<< x->JourneyCode <<endl ;
        preorder(x->left);
        preorder(x->right);
    }
}

void BST::postorder(TreeNode*x){
    if(x!=NULL){
        postorder(x->right);
        postorder(x->left);
        cout<< x->JourneyCode <<endl ;
    }
}

void BST::inorder(TreeNode*x){
    if(x!=NULL){
        inorder(x->left);
        cout<< x->JourneyCode <<endl ;
        inorder(x->right);
    }
}

void BST::traverse(int typeOfTraversal) {
    TreeNode*x=root;
    if(x==NULL){return ;}
    if (typeOfTraversal==0){
         preorder(x);
    }
    if(typeOfTraversal==1){
         postorder(x);
    }
    if(typeOfTraversal==2){
        inorder(x);
    }
    
    return ; }

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode *t= root;
    
    while(t->left!=NULL){
       t=t->left;
    }     
    return t->price ;
    }

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::size(TreeNode*x){
    if(x==NULL){
        return 0;
    }
    else 
    return (size(x->left)+1+size(x->right));
}

int BST::greater(TreeNode*,int k){
    TreeNode*x=root;
    if(x==NULL)
    return 0;
    if(x->price>k)
        return greater(x->left,k)+1+size(x->right);
    else
    return greater(x->right,k);
}
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {    
    TreeNode*x=root;
    int p=greater(x,lowerPriceBound);
    int q=greater(x,upperPriceBound);

    return (p-q+1); }

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::store(TreeNode*root,string filename){
    ofstream outfile;
    outfile.open(filename, std::ios_base::app);

    if (root == NULL){
        return;
    }
    outfile<<root->JourneyCode << " ";
    outfile<<root->price<<endl;
    store(root->left,filename);
    store(root->right, filename);
    outfile.close();
}

void BST::customStore(string filename) { 
    ofstream outfile;
    outfile.open(filename);
    outfile.close();
    store(root,filename);

    return; }
	
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


// Please use the following code to replace the last part of
// BST.cpp that was provided earlier (from below the comment
// DO NOT CHANGE ANYTHING BELOW THIS LINE)
//
//

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
