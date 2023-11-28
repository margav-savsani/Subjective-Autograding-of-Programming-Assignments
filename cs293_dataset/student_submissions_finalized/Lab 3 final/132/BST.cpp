//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <string.h>

using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST() { ; }
BST::BST(TreeNode *root) { ; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price){
    TreeNode *prev =NULL;
    while(root!=NULL){
       prev = root;
       if(price==root->price ){
                
       }
       else if(price<root->price){
           root = root->left;
       }
       else{
           root = root->right;
       }
   }
      TreeNode* p = new TreeNode(JourneyCode, price); 
   if(price<prev->price){
       prev->left = p ;
   }
   else{
       prev->right = p;
   }
};
// struct treeNode* prev = NULL;
//  while (TreeNode!=NULL)
//  { prev = TreeNode;

// if(price == TreeNode->jrnyCode)return false;
// else if (price<TreeNode->jrnyCode)
// { TreeNode = TreeNode->left; }
// else{ TreeNode  =  TreeNode->right; }
// }
// struct TreeNode* new = createNode(price);
// if(price<prev->price){
//     prev ->left = new;}
//     else{
//         prev ->right = new;
//     }
// return true;
// }

// int BST::createNode(int price){
//     struct TreeNode *n;
//     n = (struct node *) malloc(sizeof(struct TreeNode));
//     n->price = price;
//     n->left =NULL;
//     n->right = NULL;
//     return n;
// };

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{    
    if (root == NULL)
    {
        return NULL;
    }
    if (price == root->price)
    {
        return true;
    }
    else if (price<root->price){
       root= root->left;
        bool x = find(JourneyCode,price);
       root = root->parent; 
       return x; 
        
    }
    else{
    root-> right; 
    find(JourneyCode , price);
     bool x = find(JourneyCode,price);
     root = root->parent;
    return x;
    }
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{    if (price < root->price)
{    root = root->left;
     bool x = remove(JourneyCode, price);
     root = root->parent;}

    else if (price > root->price)
{    root = root->right;
     bool x = remove(JourneyCode, price);
     root = root->parent;
}    remove(JourneyCode,price){
     if (root->left == NULL || root->right==NULL)
     {  int y = price;
     }
     else (y = TreeSuccessor(price))
    
    if(root->left != NULL)
     {
        x = root->left(y);
     }
     else (x = root->right(y);)
    if (x != NULL)
    {
       root->parent(x) = parent(y); 
    }
    
}




}
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal)
{  if (typeOfTraversal == 0){
   void preOrder(TreeNode* root)
   {
    if(root!=NULL){
        cout<< root->data<<endl;
        preOrder(root->left);
        preOrder(root->right);
    }
}
   
}
//PRE_ORDER 0
   else if(typeOfTraversal == 1){
    void postOrder(TreeNode* root)
    {
    if(root!=NULL){
        postOrder(root->left);
        postOrder(root->right);
       cout<< root->data;
    }
}

   }
// post order
   else if(typeOfTraversal == 2){
    void inOrder(struct  node* root){
    if(root!=NULL){
        inOrder(root->left);
        cout<< root->data<<endl;
        inOrder(root->right);
    }
}
   }
 // inorder   
}
// Returns the price of the cheapest journey
int BST::getMinimum()
{
  if (root->left){
      root -> left;
    int x = getMinimum();
    return x;
    }
    else return root ->price;


  };


// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound)
{   int count =0;
    void traversing(TreeNode* root){
    while(root!=NULL){
        if ( root->price >= lowerPriceBound && root->price <= upperPriceBound){
            count++;
        }
      
       else if(price<root->price)
      {  root = root->left;
     void x = traversing(TreeNode* root);
     root = root->parent;}
      else (price>root->price)
      {  root = root->right;
     void x = traversing(TreeNode* root);
     root = root->parent;}
    }
        
        
    }

    return count;}


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

void BST::customLoad(int flag, string filename)
{

    return;
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
        root = root->right;
        printBST(prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::getBST(const string &prefix, bool isLeft = false)
{
    if (root != nullptr)
    {
        result.push_back(prefix);

        result.push_back(isLeft ? "├──" : "└──");

        // print the value of the node
        result.push_back(root->JourneyCode + "\n");
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        getBST(prefix + (isLeft ? "│   " : "    "), true);
        root = root->right;
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
