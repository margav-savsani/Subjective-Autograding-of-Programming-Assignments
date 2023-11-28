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
BST::BST(TreeNode *A){
    this->root = A;
 }
// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    TreeNode *x,*y,*z;
    bool c;
    x = root;
    y = NULL;
    z = new TreeNode(JourneyCode,price);
    if(root == NULL) {root = z;c = true;}
    while(x != NULL){
        y = x;
        if(x->JourneyCode == JourneyCode){
            c = false;
        }
        else{
            c = true;
        }
        if(x->price < price){
            x = x->right;
        }
        else{
           x = x->left;
        }
    }
   z->parent = y;
   if(y == NULL){
    root = z;
   }
   else if(z->price < y->price){
    y->left = z;
   }
   else{
    y->right = z;
   }
    return c;
}
// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price){
    TreeNode *x;
    bool c;
    x = root;
    while(x != NULL){
        if(x->JourneyCode == JourneyCode){
            c = true;
        }
        else{
            c = false;
        }
        if(x->price < price){
            x = x->right;
        }
        else{
            x = x->left;
        }
    }
    return c;
}
TreeNode *search(TreeNode *a, int JourneyCode, int price){
        if(a->price == price){
        return a;
        }
        if(a->price > price){
            return search(a->left,JourneyCode,price);
        }
        else{
            return search(a->right,JourneyCode,price);
        }
}
TreeNode *min(TreeNode *a){
      TreeNode *x;
      x = a;
      while(x->left != NULL){
        x = x->left;
      }
      return x;
  }
TreeNode *successor(TreeNode *a){
    TreeNode *x,*y;
    x = a;
    y = NULL;
    if(x->right != NULL) {return min(x->right);}
    y = x->parent;
    while(y != NULL and y->right == x){
        x = y;
        y = x->parent;
    }
    return y;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price){
    bool c;
    if(find(JourneyCode,price)){
        c = true;
        TreeNode *z;
        cout << "-1";
        z = search(root,JourneyCode,price);
        cout << "0";
        if(z == root){
         root = successor(root);
         cout << "1";
        }
        if(z->left == NULL && z->right == NULL){
            z->parent->left = NULL;
            z->parent->right = NULL;
        }
         if(z->left == NULL && z->right != NULL){
            z->parent->right = z->right;
            z->right->parent = z->parent;
        }
         if(z->left != NULL && z->right == NULL){
            z->parent->left = z->left;
            z->left->parent = z->parent;
        }
        else{
            TreeNode *k;
            k = successor(z);
            z = k;
            if(k->right == NULL){
                k->parent->right = NULL;
            }
            else{
                if(k->parent->price > k->right->price){
                    k->parent->left = k->right;
                    k->right->parent = k->parent;
                }
                else{
                    k->parent->right = k->right;
                    k->right->parent = k->parent;
                }
            }
        }
    }
    else{
        c = false;
    }
    return c;
}
void preorder(TreeNode *a){
    if(a == NULL){
        return;
    }
    else{
        cout << a->JourneyCode << " ";
        preorder(a->left);
        preorder(a->right);
    }
}
void postorder(TreeNode *a){
    if(a == NULL){
        return;
    }
    else{
        postorder(a->left);
        postorder(a->right);
        cout << a->JourneyCode << " ";
    }
}
vector<int> V;
void inorder(TreeNode *a){
    if(a == NULL){
        return;
    }
    else{
        inorder(a->left);
        cout << a->JourneyCode << " ";
        V.push_back(a->price);
        inorder(a->right);
    }
}
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    int a;
    a = typeOfTraversal;
    if(a == 0){
        preorder(root);
    }
    else if(a == 1){
        postorder(root);
    }
    else if(a == 2){
        inorder(root);
    }
}
// Returns the price of the cheapest journey
int BST::getMinimum(){
    TreeNode *a;;
    a = root;
   if(a== NULL){return 0;}
    while(a->left != NULL){
        a = a->left;
   }
   return a->price;
   }

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    TreeNode *a;
    a = root;
    int count=0;
    for(int i=0;i<V.size();i++){
        if(V[i] >= lowerPriceBound && V[i] <= upperPriceBound){
            count++;
        }
        else{
            continue;
        }
    }
     return count;
}
// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) {
    ofstream foo;
        foo.open(filename,ios::out);
        for(int i=0;i<V.size();i++){
            foo << V[i] << " ";
        }
    foo.close();
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
 
void BST::customLoad (int flag, string filename) {}


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
