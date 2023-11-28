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

BST::BST(){this->root = NULL; }
BST::BST(TreeNode *root){this->root = root;}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { if (std::find(journey.begin(), journey.end(), JourneyCode) != journey.end())
    {
        return false;
    }
    journey.push_back(JourneyCode);
    TreeNode *x = root;
    TreeNode *y;
    if (x == NULL)
    {
        x = new TreeNode(JourneyCode, price);
        x->parent = NULL;
        root = x;
        return true;
    }
    while (x != NULL)
    {
        if (x->price > price)
        {
            if (x->left == NULL)
            {
                x->left = new TreeNode(JourneyCode, price);
                return true;
            }
            else
                x = x->left;
        }

        else if (x->price <= price)
        {
            if (x->right == NULL)
            {
                x->right = new TreeNode(JourneyCode, price);
                return true;
            }
            else
                x = x->right;
        }
    }
    return true;}


void BST::myprint( TreeNode*a ,int i ){
    if (i==2){
     if (a->left != NULL) {myprint(a->left,2);}
     cout << a->price<<endl;
     if (a->right != NULL) {myprint(a->right,2);}
}
  if (i==0){
     cout << a->price<<endl;
     if (a->left != NULL) {myprint(a->left,0);}
     if (a->right != NULL) {myprint(a->right,0);}
}

if (i==1){
     if (a->left != NULL) {myprint(a->left,1);}
     if (a->right != NULL) {myprint(a->right,1);}
     cout << a->price<<endl;
}
}

void BST::myout( TreeNode*a  , ofstream& outfile){
    outfile << a->JourneyCode<<" "<<a->price<<endl;
     if (a->left != NULL) {myout(a->left,outfile);}
     else {outfile<<-1<<endl;}
     if (a->right != NULL) {myout(a->right,outfile);}
     else {outfile<<-1<<endl;}
}

TreeNode* BST::myload( TreeNode*a , ifstream& input){
  int N ;
  input >> N;
  if (N == -1){ return NULL;}
  else {
    int k ; input >> k;
    a = new TreeNode(N,k);
    a->left=myload(a->left,input);
    a->right=myload(a->right,input);
    return a;
  }


}
// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { TreeNode *x = root;
    TreeNode *y;
    if (x == NULL)
    {
        return false;
    }
    while (x != NULL)
    {
        if (x->price > price)
        {

            y = x;
            x = x->left;
        }

        else if (x->price < price)
        {
            y = x;
            x = x->right;
        }
        else if (x->price == price)
        {
            if (x->JourneyCode == JourneyCode)
            {
                return true;
            }
            else
            {
                y = x;
                x = x->right;
            }
        }
    }
    return false;}

       TreeNode* BST::Mymin( TreeNode* a){
         TreeNode *x = a->right;
            while (x->left != NULL)
            {
                x = x->left;
            }
            if (x->left == NULL)
            {
                return x;
            }
    };
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    TreeNode *x = root;
    TreeNode *y;
    if (x == NULL)
    {
        return false;
    }
    while (x != NULL)
    {
        if (x->price > price)
        {

            y = x;
            x = x->left;
        }

        else if (x->price < price)
        {
            y = x;
            x = x->right;
        }
        else if (x->price == price)
        {
            if (x->JourneyCode == JourneyCode)
            {
                break;
            }
            else
            {
                y = x;
                x = x->right;
            }
        }
    }
  
        if (x == NULL)
        {
            return false;
        }
        
        else 
        {
           
            if (x->left == NULL && x->right == NULL)
            {   if (x->JourneyCode == root->JourneyCode)
                 {
                    root =NULL;
                 }
                else
                if (y->left == x)
                {
                    y->left = NULL;
                }
                else if (y->right == x)
                {
                    
                    y->right = NULL;
                }
            }

            else if (x->left == NULL)
            {   if (x->JourneyCode==root->JourneyCode)
                {
                   root = x->right;  
                }
                else if (y->left == x)
                {
                    y->left = x->right;
                }
                else if (y->right == x)
                {
                    y->right = x->right;
                }
            }

            else if (x->right == NULL)
            {
                if (x->JourneyCode==root->JourneyCode)
                {
                   root = x->left;  
                }
                else if (y->left == x)
                {
                    y->left = x->left;
                }
                else if (y->right == x)
                {
                    y->right = x->left;
                }
            }

            else {
              TreeNode* success = Mymin(x);
              remove(success->JourneyCode,success->price);
              x->JourneyCode = success->JourneyCode;
              x->price = success->price; 
            }

            return true;
             }
        }
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {myprint(root,typeOfTraversal); return; }

// Returns the price of the cheapest journey
int BST::getMinimum() { TreeNode *x = root;
            if (x == NULL)
            {
                return -1;
            }
            while (x->left != NULL)
            {
                x = x->left;
            }
            if (x->left == NULL)
            {
                return x->price;
            }
             }

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) { 
    if (root == NULL){return 0;}
    return root->getcount(lowerPriceBound,upperPriceBound);
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
myout(root,outfile);
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
    ifstream input ;
    input.open(filename);
    if (flag==3) {root=myload(root,input); }
    if (flag==4) {root->left=myload(root,input); }
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

