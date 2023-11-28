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

BST::BST()
{
    root = NULL;
}
BST::BST(TreeNode *root)
{
    this->root=root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCodeN, int priceN)
{
    if(root==NULL)
    {
        root = new TreeNode;
        root->parent=NULL;
        root->left=NULL;
        root->right=NULL;
        root->price=priceN;
        root->JourneyCode=JourneyCodeN;
        return true;
    }
    TreeNode* A=root;
    TreeNode* B=new TreeNode;
    B->JourneyCode=JourneyCodeN;
    B->price=priceN;
    B->left=NULL;
    B->right=NULL;
    while(true)
    {
        if(A!=NULL)
        {
            if(A->price > priceN)
            {
                if(A->left==NULL)
                {
                  B->parent=A;
                  A->left=B;
                  return true;  
                }
                A=A->left;
                continue;
            }
            if(A->price < priceN)
            {
                if(A->right==NULL)
                {
                  B->parent=A;
                  A->right=B;
                  return true;  
                }
                A=A->right;
                continue;
            }
            if(A->price == priceN)
            {
                if(JourneyCodeN==A->JourneyCode)
                {
                    return false;
                }
                else
                {
                    if(A->right==NULL)
                    {
                        B->parent=A;
                        A->right=B;
                        return true;  
                    }
                    A=A->right;
                    continue;
                }
            }
        }
    }
}
//assumption! if same value of cost is added, then it will added to the right of old one
// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    TreeNode* A=root;
    while(true)
    {
        if(A!=NULL)
        {
            if(A->price > price)
            {
                if(A->left==NULL)
                {
                    return false;
                }
                A=A->left;
                continue;
            }
            if(A->price < price)
            {
                if(A->right==NULL)
                {
                    return false;
                }
                A=A->right;
                continue;
            }
            if(JourneyCode==A->JourneyCode&&A->price == price)
            {
                return true;
            }
        }
    }
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{//assuming there are no one nodes which have same cost
    TreeNode* A=root;
    while(true)
    {
        if(A!=NULL)
        {
            if(A->price > price)
            {
                if(A->left==NULL)
                {
                    return false;
                }
                A=A->left;
                continue;
            }
            if(A->price < price)
            {
                if(A->right==NULL)
                {
                    return false;
                }
                A=A->right;
                continue;
            }
            if(A->price == price&&JourneyCode==A->JourneyCode)
            {
                if(A->left == NULL && A->right==NULL)
                {
                    if(A->parent==NULL)
                    {
                        delete A;
                        root=NULL;
                    }
                    else if((A->parent)->left==A)
                    {
                        (A->parent)->left=NULL;
                        delete A;
                    }
                    else if((A->parent)->right==A)
                    {
                        (A->parent)->right=NULL;
                        delete A;
                    }
                }
                else if(A->left != NULL && A->right == NULL)
                {
                    if(A->parent==NULL)
                    {
                        root=A->left;
                        (A->left)->parent=NULL;
                        delete A;
                    }
                    else if((A->parent)->left==A)
                    {
                        (A->parent)->left=A->left;
                        (A->left)->parent=A->parent;
                        delete A;
                    }
                    else if((A->parent)->right==A)
                    {
                        (A->parent)->right=A->left;
                        (A->left)->parent=A->parent;
                        delete A;
                    }
                }
                else if(A->left == NULL && A->right != NULL)
                {
                    if(A->parent==NULL)
                    {
                        root=A->right;
                        (A->right)->parent=NULL;
                        delete A;
                    }
                    else if((A->parent)->left==A)
                    {
                        (A->parent)->left=A->right;
                        (A->right)->parent=A->parent;
                        delete A;
                    }
                    else if((A->parent)->right==A)
                    {
                        (A->parent)->right=A->right;
                        (A->right)->parent=A->parent;
                        delete A;
                    }
                }
                else if(A->left != NULL && A->right != NULL)
                {
                    int JourneyCode1;
                    int price1;
                    TreeNode* B=A->left;
                    while(true)
                    {
                        if(B->right == NULL)
                        {
                            price1=B->price;
                            JourneyCode1=B->JourneyCode;
                            remove(JourneyCode1,price1);
                            break;
                        }
                        B=B->right;
                    }
                    A->JourneyCode=JourneyCode1;
                    A->price=price1;
                }
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    } 
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal)
{
    traverse_tree(typeOfTraversal,root);
    return;
}
void BST::traverse_tree(int typeOfTraversal,TreeNode* C)
{
    if(C==NULL)
    {
        return;
    }
    if(typeOfTraversal==0)
    {
        if(C==NULL)
        {
            return;
        }
        cout << C->price<<endl;
        traverse_tree(0,C->left);
        traverse_tree(0,C->right);
        return;
    }
    if(typeOfTraversal==1)
    {
        if(C==NULL)
        {
            return;
        }
        traverse_tree(1,C->left);
        traverse_tree(1,C->right);
        cout << C->price<<endl;
        return;
    }
    if(typeOfTraversal==2)
    {
        if(C==NULL)
        {
            return;
        }
        traverse_tree(2,C->left);
        cout << C->price<<endl;
        traverse_tree(2,C->right);
        return;
    }
    cout<<"ERROR\n";
}

// Returns the price of the cheapest journey
int BST::getMinimum()
{
    TreeNode* A;
    A=root;
    while(true)
    {
        if(A==NULL)
        {
            return -1;
        }
        if(A->left==NULL)
        {
            return A->price;
        }
        A=A->left;
    }
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