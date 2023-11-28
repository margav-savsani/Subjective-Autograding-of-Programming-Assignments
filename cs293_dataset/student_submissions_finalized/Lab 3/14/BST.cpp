#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <fstream>
#include <cstdlib>
#include <sstream>

using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4

//global variable
vector<int> val;

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST()
{ 
    //cout << "default\n";
    root = NULL;
}
BST::BST(TreeNode *root)
{
    //parent = NULL may indicate that it is a root node
    //cout << "constructed with root";
    this->root = root;
    (this->root)->parent = NULL;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) 
{
    //if found tHen rturns false as it can't insert
    if(find(JourneyCode, price)) return false;

    TreeNode* newnode;
    newnode = new TreeNode(JourneyCode,price);
    TreeNode* r = root;
    TreeNode* n = NULL;
    bool done=false;

    // if root is empty before the new node will tself become the root
    if(root == NULL)
    {
        //cout << "insert at root\n";
        root = newnode;
        root->parent = NULL;
        return true;
    }
    
    while(r!=NULL)
    {
        n=r;
        if(price < r->price) r=r->left;
        else r=r->right;
    }

    if(price < n->price)
    {
        n->left = newnode;
        newnode->parent = r;
        return true;
    }

    else
    {
        n->right = newnode;
        newnode->parent = n;
        return true;
    }

    return n;

}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    TreeNode* needed;
    TreeNode* r;
    needed = new TreeNode(JourneyCode, price);
    r = root;
    bool isthere = false;

    //if the tree is empty then returns false 
    if(root == NULL) return false;

    while(!isthere)
    {
        if(r == NULL) return false;

        if(r->sameattributes(needed)) return true;

        if( (r->price == price && r->JourneyCode != JourneyCode) || (r->price != price && r->JourneyCode == JourneyCode) )return false;
        //anyways the second case in the above doesn't occur ig but still to be defensive

        //navigate till it finds
        if(r->price < price) r=r->right;
        else if(r->price > price) r=r->left;
    }
    return isthere;
}

//utility functions for remove
TreeNode* BST::minvaluenode(TreeNode* given)
{
    if(given == NULL) return NULL;

    while(given->left != NULL) given = given->left;
    return given;
}

TreeNode* BST::successor(TreeNode* given)
{
    TreeNode* pog = given->parent; //parent of given
    //if we are given a empty value to find successor
    //to be defensive
    if(given == NULL) return NULL;

    if(given->right !=NULL) return minvaluenode(given->right);
    else
    {
        if(given == pog->left) return pog; //given is the left child
        while(pog!=NULL && given == pog->right)
        {
            given = pog;
            pog = pog->parent;
        }
        return pog;
    }
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) 
{ 
    //If node is not there then return
    if(!find(JourneyCode, price)) return false;
    
    TreeNode* needed;
    needed = new TreeNode(JourneyCode, price);
    TreeNode *n = NULL;
    TreeNode *r = root;

    bool done=false;

    while(!done)
    {
        //after reaching the node which has to be deleted
        //three cases may take place
        if(r->sameattributes(needed))
        {
            //case 1
            //no chidren -> leaf node
            if(r->left == NULL && r->right == NULL)
            {
                if(r == root){root = NULL; return true;}
                if(r == n->left) n->left = NULL;
                else n->right = NULL;
            }
            //if 1 child
            //2 subcases
            else if(r->left == NULL && r->right!=NULL)
            {
                if(r == root) {root = r->right; return true;}
                if(r == n->left) n->left = r->right;
                else n->right = r->right;
            }
            else if(r->left != NULL && r->right==NULL)
            {
                if(r == root) {root = r->left; return true;}
                if(r == n->left) n->left = r->left;
                else n->right = r->left;
            }
            //if 2 children
            //can solve in two ways using successor way
            else
            {
                TreeNode* s = successor(r);
                remove(s->JourneyCode,s->price);
                if(r == root) 
                {
                    root = s;
                    s->left = r->left;
                    s->right = r->left;
                }
                else
                {
                    n->right = s;
                    s->left = r->left;
                    s->right = r->right;
                }
            }
            return true;
        }
        if(r->price < price)
        {
            n = r;
            r =r->right;
        }
        else if(r->price > price)
        {
            n = r;
            r = r->left;
        }
    } 
    return done;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

// utility functions 
void BST::preorder(TreeNode* given)
{
    //end is reached then return
    if(given == NULL) return;
    cout << given->JourneyCode << endl;
    preorder(given->left);
    preorder(given->right);
}

void BST::postorder(TreeNode* given)
{
    //end is reached then return
    if(given == NULL) return;
    postorder(given->left);
    postorder(given->right);
    cout << given->JourneyCode << endl;
}

void BST::inorder(TreeNode* given)
{
    //end is reached then return
    if(given == NULL) return;
    inorder(given->left);
    cout << given->JourneyCode << endl;
    inorder(given->right);
}

//utility function of customstore
void BST::storepreorder(TreeNode* given)
{
    if(given == NULL) return;
    val.push_back(given->price);
    storepreorder(given->left);
    storepreorder(given->right);
}

void BST::traverse(int typeOfTraversal)
{
    switch (typeOfTraversal)
    {
        case 0: preorder(root);break;
        case 1: postorder(root);break;
        case 2: inorder(root);break;
    }
    return; 
}

// Returns the price of the cheapest journey
int BST::getMinimum() 
{
    TreeNode* minimumvaluenode;
    TreeNode* r = root;

    //if the tree is empty
    if(root == NULL) return INT_MAX; 
    //assuming tree size will never be such great

    while(r->left!=NULL) r=r->left;
    return r->price;
}

// Part II

//utility function for countjourneyinpricebound
int BST::utilcountJourneysInPriceBound(TreeNode* r, int l, int u)
{

    if(r == NULL) {return 0; }//cout << "I am null";};

    //special case included just to make it return much before to improve efficiency
    if(r->price == u && r->price == l) return 1;

    if(r->price <= u && r->price >= l)
    {
        return 1 + utilcountJourneysInPriceBound(r->left,l,u)+utilcountJourneysInPriceBound(r->right,l,u);
    }

    //to improve efficiency and reduce number of comparisons
    //if price is less than low bound
    else if (r->price <= l) return utilcountJourneysInPriceBound(r->right,l,u);
    else return utilcountJourneysInPriceBound(r->left,l,u);

}

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) 
{
    TreeNode* r = root;
    return utilcountJourneysInPriceBound(root, lowerPriceBound, upperPriceBound); 
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename)
{
    storepreorder(root);
    ofstream fn;
    fn.open(filename);
    for(int i=0;i<val.size(),i++;)
    {
        fn << to_string(val[i]) << endl;
    } 
    fill(val.begin(),val.end(),0);
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

//utility function of custom load
// TreeNode* BST::buildtree(int pre[], int*preIndex, int JourneyCode, int price, int min, int max, int size)
// {
//     TreeNode* newroot = NULL;

//     //base case
//     if(*preIndex >= size) return NULL;

//     if(price>min && price<max)
//     {
//         newroot = new TreeNode();
//     }

// }

void BST::customLoad (int flag, string filename) 
{
    // int preIndex=0;
    // int pre[val.size()];
    // ifstream inf;
    // inf.open(filename);
    // if(inf.is_open())
    // {
    //     for(int i=0;i<val.size();i++)
    //     {
    //         inf >> pre[i];
    //     }
    //     inf.close();
    // }
    // switch (flag)
    // {
    // case 3:buildtree(pre,&preIndex,pre[0],INT_MIN,INT_MAX,val.size());
    // case 4:buildtree(pre,&preIndex,pre[1],INT_MIN,INT_MAX,val.size());
    // }
    return; 
}


// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

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


// // Adapted from Adrian Schneider's code on StackOverflow
// void BST::printBST(const string& prefix, bool isLeft=false)
// {
//     if( root != nullptr )
//     {
//         cout << prefix;

//         cout << (isLeft ? "|--" : "|__" );

//         // print the value of the node
//         cout << root->JourneyCode << endl;
//         TreeNode *curr = root;
//         root = root->left;
//         // enter the next tree level - left and right branch
//         printBST( prefix + (isLeft ? "│   " : "    "), true);
//         root = root->right;
//         printBST( prefix + (isLeft ? "│   " : "    "), false);
//         root = curr;
//     }
// }

// void BST::getBST(const string& prefix,  bool isLeft=false)
// {
//     if( root != nullptr )
//     {
//         result.push_back(prefix);

//         result.push_back(isLeft ? "├──" : "└──" );

//         // print the value of the node
//         result.push_back(to_string(root->JourneyCode) + "\n");
//         TreeNode *curr = root;
//         root = root->left;
//         // enter the next tree level - left and right branch
//         getBST( prefix + (isLeft ? "│   " : "    "), true);
//         root = root->right;
//         getBST( prefix + (isLeft ? "│   " : "    "), false);
//         root = curr;
//     }
// }

// void BST::clearResult(){
//     result.clear();
// }

// vector<string> BST::getResult(){
//     return result;
// }

