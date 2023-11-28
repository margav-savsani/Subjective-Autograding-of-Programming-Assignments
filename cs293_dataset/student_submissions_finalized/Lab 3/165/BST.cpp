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
    root=nullptr;
   
}
BST::BST(TreeNode *root){
    this->root = root; 

}

// Return true, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode,int price){
    TreeNode* temp = root;
   
    while(temp!=nullptr){
        if(temp->JourneyCode == JourneyCode && temp->price == price)
            return true;

        if(price < temp->price){
            temp = temp->left;
           
        }
        else{
            temp = temp->right;
           
        }
    }

    if (temp == nullptr)
        return false;

}

bool BST::beforeInsertFind(int JourneyCode,int price){
    TreeNode* temp = root;
   
    while(temp!=nullptr){
        if(temp->JourneyCode == JourneyCode)
            return true;

        if(price < temp->price){
            temp = temp->left;
           
        }
        else{
            temp = temp->right;
           
        }
    }

    if (temp == nullptr)
        return false;

}
// Returns false, if given JourneyCode is already present in the BST
	// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price){


    if(beforeInsertFind(JourneyCode,price)){
        return false;
    }

    
    TreeNode* nodeToInsert = new TreeNode();
    nodeToInsert->JourneyCode = JourneyCode;
    nodeToInsert->price = price;
    TreeNode* temp = root;
    
    if(root == nullptr){
        
        root = nodeToInsert;
        
        return true;
    }
    
    while(temp->left!=nullptr && temp->right!=nullptr){
        
            if(price < temp->price){
                temp = temp->left;
            }
            else{
                temp = temp->right;
            }
    }
    
    
    
    if(price < temp->price){
        temp->left = nodeToInsert;
    }
    else
        temp->right = nodeToInsert;
    
    return true;
       
    

}

// Returns false, if JourneyCode isn't present
	// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price){
    if(!find(JourneyCode,price))
        return false;
    else{
        
        TreeNode* nodeToDelete;
        nodeToDelete->JourneyCode = JourneyCode;
        nodeToDelete->price = price;
        TreeNode* curr = root;
        TreeNode* prev = nullptr;

        while(curr != nullptr && curr->JourneyCode != JourneyCode){
            prev = curr;
            if(price < curr->price)
                curr = curr->left;
            else    
                curr = curr->right;
            
        }

        
        if(curr->left == nullptr || curr->right == nullptr){//check if node has atmost one child
            TreeNode* newCurr;
            if(curr->left == nullptr)
                newCurr = curr->right;
            else    
                newCurr = curr->left;
        
            if(prev == nullptr)//that is node to be deleted is the root
                return true;

            if(curr == prev->left){
                prev->left = newCurr;
            }        
            else{
                prev->right = newCurr;
            }
            free(curr);
        }
        else{
            TreeNode* p = nullptr;
            TreeNode* temp;

            //compute inorder successor
            temp = curr->right;
            while(temp->left!=NULL){
                p = temp;
                temp = temp->left;
            }

            if(p!=NULL){
                p->left = temp->right;
            }
            else{
                curr->right = temp->right;
            }
            curr->JourneyCode = temp->JourneyCode;
            curr->price = temp->price;
            free(temp);
        }

        return true;

    }
}


int BST::getMinimum(){
    TreeNode* temp = root;
    while(temp->left!=nullptr){
        temp = root->left;
    }
    return temp->price;
}
void BST::preorder(TreeNode* root){
    if(root == nullptr)
        return;
    else{
        cout<<(root->JourneyCode)<<endl;
        preorder(root->left);
        preorder(root->right);
    }
}

void BST::postorder(TreeNode* root){
    if(root == nullptr)
        return;
    else{
       
        postorder(root->left);
        postorder(root->right);
        cout<<(root->JourneyCode)<<endl;
    }
}

void BST::inorder(TreeNode* root){
    if(root == nullptr)
        return;
    else{
       
        inorder(root->left);
        cout<<(root->JourneyCode)<<endl;
        inorder(root->right);
        
    }
}
// Functions that traverse the BST in various ways!
	// type can be PRE_ORDER, POST_ORDER or IN_ORDER, which
        // #defined numeric constants defined in BST.cpp
        // This function prints on cout the journey codes (one per line)
        // encountered on traversing the BST in the given traversal order
void BST::traverse(int typeOfTraversal){
    if(typeOfTraversal == 0){
        preorder(root);
    }
    else if(typeOfTraversal == 1){
        postorder(root);

    }
    else if(typeOfTraversal == 2){
        inorder(root);
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

