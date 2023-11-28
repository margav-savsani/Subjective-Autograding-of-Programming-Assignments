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

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    TreeNode *l;
    TreeNode *r;
    TreeNode *p;
    p=root;
    if(find(JourneyCode,price)){
        return false;
    }

    while(! (find(JourneyCode,price))){
        p=root;
        if(root==NULL){
            root->price=price;
            root->JourneyCode;
            //cout<<"root null"<<endl;
            return true;
        }
        if(p==NULL){
            p->price=price;
            p->JourneyCode=JourneyCode;
            return true;
        }
        while(p!=NULL){
            if(price< p->price){
                p=p->left;
                break;
            }
            else if(price>= p->price){
                p=p->right;
                break;
            }
        }
    }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    while(root!=NULL){
        if((root->price==price) && (root->JourneyCode==JourneyCode)){
            return true;
        }
        else if(price<root->price){
            root=root->left;
        }
        else if(price>=root->price){
            root=root->right;
        }
    }
    return false;
}
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    if(find(JourneyCode,price)){
        while(root!=NULL){
            if((root->price==price) && (root->JourneyCode==JourneyCode)){
                if((root->right==NULL)&&(root->left==NULL)){
                    root->price=0;
                    root->JourneyCode=0;
                }
                else if((root->right==NULL)&&(root->left!=NULL)){
                    root=root->left;
                }
                else if((root->right!=NULL)&&(root->left==NULL)){
                    root=root->right;
                }
                else if((root->right!=NULL)&&(root->left!=NULL)){
                    root=root->left;
                }
            return true;
            }
        }
        return false;
    }
    else{
        return false;
    }
}	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {return; }

// Returns the price of the cheapest journey
int BST::getMinimum() {return 0; }


	


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
