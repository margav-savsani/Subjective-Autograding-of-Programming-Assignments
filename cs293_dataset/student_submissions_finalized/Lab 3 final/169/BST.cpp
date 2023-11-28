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
root = new TreeNode; }
BST::BST(TreeNode *root){
this->root = root;}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode,int price) {
    TreeNode *x = root;
    TreeNode *y = x;
    if (root == NULL) {
    root->JourneyCode=JourneyCode;
    root->price=price;
    return true;
    }
    while(x!=nullptr){
    if (JourneyCode==root->JourneyCode)
    return false;
    if ( JourneyCode-root->JourneyCode<0){
        y =x;
        if(y->right==nullptr){
        	x = new TreeNode(JourneyCode,price);
        	y->right=x;
        	break;}
        x=y->right;
        price=x->price;
        }
        
    else{
    y = x;
    if(y->left==nullptr){
    x=new TreeNode(JourneyCode,price);
    y->left=x;
    break
    ;}
    x=y->left;
    price=x->price;}
      
}
return true;
}

bool findintree(TreeNode *root,int JourneyCode,int price){
          TreeNode *x=root;
          int cmp=x->price-price;
          if (x==NULL) return NULL;
          if(cmp==0&&x->JourneyCode==JourneyCode){
                      return x;}
          if(cmp>0) return findintree(x->left,JourneyCode,price);
          else return findintree(x->right,JourneyCode,price);
          }
bool BST::find(int JourneyCode, int price) {
    TreeNode *x = root;
    x=root;
    if(findintree(x,JourneyCode,price) == NULL)
    return false;
    else 
    return true;
     }

	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
int removeMin(TreeNode *root,int JourneyCode) {
    if (root->left != NULL) {
        root->left = removeMin(root->left, JourneyCode);
        return root;
    } else
        return root->right;
}
bool BST::remove(int JourneyCode, int price) {
    if (find(JourneyCode,price) == NULL) return false;
    int cmp = JourneyCode-root->JourneyCode;
    if (cmp < 0) {
        root->left = removeMin(root->left, JourneyCode);
    } else if (cmp > 0) {
        root->right = removeMin(root->right, JourneyCode);
    } else {
        if (root->left == NULL) {
            root = root->right;
        } else if (root->right == NULL) {
            root = root->left;
        } else {
            // two children
          int  minNode = findMin(root->right);
            root->right = removeMin(root->right);
            root->JourneyCode = minNode.JourneyCode;
            root->price = minNode.price;
        }
    }
    return root;
}


bool BST::remove(int JourneyCode, int price) { return remove(JourneyCode); }
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line
void printPostorder(struct TreeNode* node)
{
    if (node == NULL)
        return;
  
    // first recur on left subtree
    printPostorder(node->left);
  
    // then recur on right subtree
    printPostorder(node->right);
  
    // now deal with the node
    cout << node->data << " ";
}
  
/* Given a binary tree, print its nodes in inorder*/
void printInorder(struct TreeNode* node)
{
    if (node == NULL)
        return;
  
    /* first recur on left child */
    printInorder(node->left);
  
    /* then print the data of node */
    cout << node->data << " ";
  
    /* now recur on right child */
    printInorder(node->right);
}
  
/* Given a binary tree, print its nodes in preorder*/
void printPreorder(struct TreeNode* node)
{
    if (node == NULL)
        return;
  
    /* first print data of node */
    cout << node->data << " ";
  
    /* then recur on left subtree */
    printPreorder(node->left);
  
    /* now recur on right subtree */
    printPreorder(node->right);
}
void BST::traverse(int typeOfTraversal) {printPreorder(root);
printInorder(root);
printPostorder(root);
  }

// Returns the price of the cheapest journey
int BST::getMinimum() {if (root.left != NULL)
        		return getMinimum(root.left);
   			 else
    			    return false;
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

        result.push_back(isLeft ? "├──" : "└──" );

        // print the value of the node
        result.push_back(root->JourneyCode + "\n");
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

