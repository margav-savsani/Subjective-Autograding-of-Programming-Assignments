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
    root->JourneyCode=0;
    root->price=0;
    root=nullptr;
    root->right=nullptr;
    root->parent=nullptr;
 }
BST::BST(TreeNode *root){
    root=root;


}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::Insert(int JourneyCode,int price, TreeNode *x) {
    root=x;
    if(price==x->price) {
            if(x->JourneyCode==JourneyCode) return false;
            else {
                if(x->right==nullptr) {
                x->right->JourneyCode=JourneyCode;
                x->right->price=price;
                x->right->right=nullptr;
                x->right->left=nullptr;
                x->right->parent=x;
                return true;
                }
                else{
                BST rightTree;
                rightTree.root=x->right;
                return rightTree.Insert(JourneyCode,price,x->right);
            }
            }
        }
        else if(price<x->price) {
            if(x->left==nullptr) {
                x->left->JourneyCode=JourneyCode;
                x->left->price=price;
                x->left->left=nullptr;
                x->left->right=nullptr;
                x->parent->parent=x;
                return true;
            }
            else{

              BST leftTree;
              leftTree.root=x->left;
              return leftTree.Insert(JourneyCode,price,x->left);
            }
        }
        else  {
            if(x->right==nullptr) {
                x->right->JourneyCode=JourneyCode;
                x->right->price=price;
                x->right->right=nullptr;
                x->right->left=nullptr;
                x->right->parent=x;
                return true;
                }
                else{
                   BST rightTree;
                   rightTree.root=x->right;
                   return rightTree.Insert(JourneyCode,price,x->right);
        }
        }
}
        
        

bool BST::insert(int JourneyCode, int price) { 
    return Insert(JourneyCode,price,root);
}


// Return True, if the ticket with given attributes is found, false otherwise
bool BST::Find(int JourneyCode,int price, TreeNode *x) {
     if(x==nullptr) return false;
    if(x->price==price) {
        if(x->JourneyCode==JourneyCode) return true;
        else{
            BST rightTree;
            rightTree.root=x->right;
            return rightTree.Find(JourneyCode,price,x->right);
        }
    }
    else if(x->price>price) {
        BST leftTree;
        leftTree.root=x->left;
        return leftTree.Find(JourneyCode,price,x->left);
    }
    else {
        BST rightTree;
        rightTree.root=x->right;
        return rightTree.Find(JourneyCode,price,x->right);
    }

}
bool BST ::find (int JourneyCode, int price) {
   return Find(JourneyCode,price,root) ;
   
}

	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise

TreeNode* BST::Successor(TreeNode *x) {
    if(x->right!=nullptr) {
        x=x->right;
        while(x->left!=nullptr) {
            x=x->left;

        }
        return x;
    }
    else {
      return NULL;
    }
     
}
bool BST::Remove(int JourneyCode, int price,TreeNode *x) {

    x=root ;
    if(x==nullptr) return false;
    else {
        if(x->price==price) {
            if(x->JourneyCode==JourneyCode) {
                if((x->left==nullptr)&&(x->right==nullptr)) {
                    x=nullptr;
                    return true;
                } 
                else if((x->left!=nullptr)&&(x->right==nullptr)){
                    if(x->parent->price>x->price){
                        x->parent->left=x->left;
                        x->left->parent=x->parent;
                        x=nullptr;
                        return true;
                    }
                    else{
                        x->parent->right=x->left;
                        x->left->parent=x->parent;
                        x=nullptr;
                        return true;
                    }
                }
                else if((x->left=nullptr)&&(x->right=nullptr)){
                    if(x->parent->price<=x->price) {
                        x->parent->right=x->right;
                        x->right->parent=x->parent;
                        x=nullptr;
                        return true;
                    }
                    else{
                        x->parent->left=x->right;
                        x->right->parent=x->parent;
                        x=nullptr;
                        return true;
    
                }
               }
               else{
                   int tempprice=0;
                   int tempJourneyCode=0;
                   TreeNode *tempnode;
                   tempprice=Successor(x)->price;
                   tempJourneyCode=Successor(x)->JourneyCode;
                   x->price=tempprice;
                   x->JourneyCode=tempJourneyCode;
                   if(Successor(x)->right==nullptr) {
                     tempnode=Successor(x);
                     tempnode=nullptr;
                     return true;
                     }
                   else {
                       Successor(x)->parent->left=Successor(x)->right;
                       Successor(x)->right->parent=Successor(x)->parent;
                       tempnode=Successor(x);
                       tempnode=nullptr;
                       return true;
                   }

               }
               
             
        }
        else{
            BST rightTree;
            rightTree.root=x->right;
            return rightTree.Remove(JourneyCode,price,x->right);
        }
    }
    else if(x->price>price) {
        BST leftTree;
        leftTree.root=x->left;
        return leftTree.Remove(JourneyCode,price,x->left);
    }
    else {
        BST rightTree;
        rightTree.root=x->right;
        return rightTree.Remove(JourneyCode,price,x->right);
    }
    }
}
bool BST::remove(int JourneyCode, int price) {
    return Remove(JourneyCode,price,root);
}

  
        
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print onvoid pe journey code per line
void BST:: preorder(TreeNode *x) {
    
    if(x==nullptr) return;
    else{
        cout<<x->JourneyCode<<endl;
        preorder(x->left);
        preorder(x->right);
    }
}
void BST:: postorder(TreeNode *x) {
    
    if(x==nullptr) return;
    else {
        postorder(x->left);
        postorder(x->right);
        cout<<x->JourneyCode<<endl;
    }
}
void BST::inorder(TreeNode *x) {
    
    if(x==nullptr) return;
    else {
        inorder(x->left);
        cout<<x->JourneyCode<<endl;
        inorder(x->right);
    }
}
void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal==0) {
        preorder(root);
    }
    else if(typeOfTraversal==1) {
        postorder(root);
    }
    else if(typeOfTraversal==2) {
        inorder(root);
    }


    
}


// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode *x;
    x=root;
    if(root=nullptr) return 0;
    else {
        while(x->left!=nullptr) {
            x=x->left;
        }
        return x->price;
    }
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::CountJourneysInPriceBound(int lowerPriceBound,int upperPriceBound, TreeNode *x) {
    if(x->price<lowerPriceBound) {
        if(x->right==nullptr) {
            return 0;
        }
        else {
        BST rightTree;
        rightTree.root=x->right;
        return rightTree.countJourneysInPriceBound(lowerPriceBound,upperPriceBound);
        }
    }
    else if(x->price==lowerPriceBound) {
        if(x->right==nullptr) {
            return 1;
        }
        else{
         BST rightTree;
        rightTree.root=x->right;
        return rightTree.countJourneysInPriceBound(lowerPriceBound,upperPriceBound)+1;
        }
    }
    else if (x->price>upperPriceBound) {
        if(x->left==nullptr) {
            return 0;
        }
        else{
        BST leftTree;
        leftTree.root=x->left;
        return leftTree.countJourneysInPriceBound(lowerPriceBound,upperPriceBound);
        }
    }
    else if(x->price==upperPriceBound) {
        if(x->right==nullptr) {
            return 1;
        }
        else{
        BST leftTree;
        leftTree.root=x->right;
        return leftTree.countJourneysInPriceBound(lowerPriceBound,upperPriceBound)+1;
        }
    }
    else{
        if(x->left==nullptr&&x->right!=nullptr) {
            BST rightTree;
        rightTree.root=x->right;
        return rightTree.countJourneysInPriceBound(lowerPriceBound,upperPriceBound)+1;
        }
        else if(x->left!=nullptr&&x->right==nullptr) {
        BST leftTree;
        leftTree.root=x->right;
        return leftTree.countJourneysInPriceBound(lowerPriceBound,upperPriceBound)+1;
    }
        else{
        BST rightTree;
        BST leftTree;
        rightTree.root=x->right;
        leftTree.root=x->left;
        return rightTree.countJourneysInPriceBound(lowerPriceBound,upperPriceBound)+leftTree.countJourneysInPriceBound(lowerPriceBound,upperPriceBound)+1;
    }
    }
}
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    return CountJourneysInPriceBound(lowerPriceBound,upperPriceBound,root);
}
// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) { return; }
	
// While loading a tree from a file written by customStore, we
// can have one of two modes of loading.  We could either ask
// for the entire tree to be loaded or only the  subtree of
// the root (if it exists) to be loaded.  The loadMode flag
// takes one of two values LOAD_FULL_BST or LOAD_LEFT_SUBTREE,
// that are #defined in BST.cpp.
// If loadMode is LOAD_FULL_BST, customLoad should load the
// entire BST that was stored in filename using customStore.
// If loadMode is LOAD_LEFT_SUBTREE, customLoad should load
// only the  subtree of the root of the BST that was
// stored in filename using customStore.
// Your implementation of customLoad should be efficient --
// its time and space complexity should be linear in the size
// of the tree that is being loaded.  So, for example, if the
//  sub-tree of the root is small compared to the right
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
        // enter the next tree level -  and right branch
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
        // enter the next tree level -  and right branch
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

