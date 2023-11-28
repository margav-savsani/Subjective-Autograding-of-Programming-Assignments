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

    ofstream outfile;
    ifstream infile;

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST(){root = NULL;}
BST::BST(TreeNode *root){this->root = root;}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    TreeNode* varParent = NULL;
    TreeNode* varCurrent = root;
    while(varCurrent != NULL){
        int x = varCurrent->price;
        if(x < price){
            varParent = varCurrent;
            varCurrent = varCurrent->right;
        }
        else if(x > price){
                varParent = varCurrent;
                varCurrent = varCurrent->left;
        }
        else{
            return false;
        }
    }

    if(varParent == NULL){
        root = new TreeNode(JourneyCode, price, NULL, NULL, NULL);
        return true;
    }

    if(varParent->price < price){
        varParent->right = new TreeNode(JourneyCode, price, NULL, NULL, varParent);
        varParent->identity = 1;
        if(varParent->left != NULL)
            varParent->identity = 2;
    }
    else{
        varParent->left = new TreeNode(JourneyCode, price, NULL, NULL, varParent);
        varParent->identity = -1;
        if(varParent->right != NULL)
            varParent->identity = 2;
    }
    return true;

}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    TreeNode *var = root;
    while(var != NULL){
        if(var->price == price)
            return true;
        else if(var->price < price)
            var = var->right;
        else
            var = var->left;
    }
    return false;
}

TreeNode* BST::find(TreeNode *var, int price){
    while(var != NULL){
        if(var->price == price)
            return var;
        else if(var->price < price)
            return find(var->right, price);
        else
            return find(var->left, price);
    }
    return NULL;
}

TreeNode* BST::TreeMinimum(TreeNode* var){
    TreeNode *varParent = var->parent;
    while(var != NULL){
        varParent = var;
        var = var->left;
    }
    return varParent;
}

TreeNode* BST::TreeSuccessor(TreeNode *var){
    if(var->right != NULL){
        return TreeMinimum(var->right);
    }
    TreeNode *varParent = var->parent;
    while(varParent != NULL && var == varParent->right){
        var = varParent;
        varParent = varParent->parent;
    }
    return varParent;
}


// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
    TreeNode* tobeDel = find(root, price);
    TreeNode* tobeDelPar = new TreeNode;
    if(tobeDel == NULL)
        tobeDelPar = NULL;
    else
        tobeDelPar = tobeDel->parent;
    
    if(tobeDel == NULL)
        return false;
    else if(tobeDel->left == NULL && tobeDel->right == NULL){
        if(tobeDelPar == NULL){
            root = NULL;
            return true;
        }
        else if(tobeDelPar->price < price){
            tobeDelPar->right = NULL;
            tobeDelPar->identity = 0;
            if(tobeDelPar->left != NULL)
                tobeDelPar->identity = -1;
        }
        else{
            tobeDelPar->left = NULL;
            tobeDelPar->identity = 0;
            if(tobeDelPar->right != NULL)
                tobeDelPar->identity = 1;
        }
        //delete(tobeDel);
        return true;
    }
    else if(tobeDel->left == NULL){
        if(tobeDelPar == NULL){
            tobeDel->right->parent = tobeDelPar;
            return true;
        }
        else if(tobeDelPar->price < price){
            tobeDelPar->right = tobeDel->right;
            tobeDel->right->parent = tobeDelPar;
        }
        else{
            tobeDelPar->left = tobeDel->right;
            tobeDel->right->parent = tobeDelPar;
        }
        delete(tobeDel);
        return true;
    }
    else if(tobeDel->right == NULL){
        if(tobeDelPar == NULL){
            tobeDel->left->parent = tobeDelPar;
        }
        else if(tobeDelPar->price < price){
            tobeDelPar->right = tobeDel->left;
            tobeDel->left->parent = tobeDelPar;
        }
        else{
            tobeDelPar->left = tobeDel->left;
            tobeDel->left->parent = tobeDelPar;
        }
        delete(tobeDel);
        return true;
    }
    else{
        TreeNode *successor = TreeSuccessor(tobeDel);
        if(successor->right == NULL){
            if(successor->parent->price < successor->price){
                successor->parent->right = NULL;
                if(successor->parent->left != NULL)
                    successor->parent->identity = -1;
                else
                    successor->parent->identity = 0;
            }    
            else{
                successor->parent->left = NULL;
                if(successor->parent->right != NULL)
                    successor->parent->identity = 1;
                else
                    successor->parent->identity = 0;            
            }
            tobeDel->price = successor->price;
            tobeDel->JourneyCode = successor->JourneyCode;
            delete(successor);
            return true;
        }
        else{
            if(successor->parent->price < successor->price){
                if(successor->parent->right == NULL)
                    successor->parent->identity = 2;
                successor->parent->right = successor->right;
                successor->right->parent = successor->parent;
            }
            else{
                if(successor->parent->left == NULL)
                    successor->parent->identity = 2;
                successor->parent->left = successor->right;
                successor->right->parent = successor->parent;
            }
            tobeDel->price = successor->price;
            tobeDel->JourneyCode = successor->JourneyCode;
            delete(successor);
            return true;
        }
    }
}
	
void BST::preorder(TreeNode *var){
    if(var==NULL)
        return;
    std::cout << var->JourneyCode << std::endl;
    preorder(var->left);
    preorder(var->right);
}

void BST::postorder(TreeNode *var){
    if(var==NULL)
        return;
    postorder(var->left);
    postorder(var->right);
    std::cout << var->JourneyCode << std::endl;
}

void BST::inorder(TreeNode *var){
    if(var==NULL)
        return;
    inorder(var->left);
    std::cout << var->JourneyCode << std::endl;
    inorder(var->right);
}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal == 0)
        preorder(root);
    else if(typeOfTraversal == 1)
        postorder(root);
    else if(typeOfTraversal == 2)
        inorder(root);
    return;
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode *minNode = TreeMinimum(root);
    return minNode->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lPB, int uPB)
{
    int count=0;
    TreeNode* var = root;
    TreeNode* lPBnode = NULL;
    while(var != NULL){
        if(var->price < lPB)
            var = var->right;
        else if(var->price == lPB){
            lPBnode = var;
            break;
        }
        else if(var->left == NULL || var->left->price < lPB){
            lPBnode = var;
            break;
        }
        else
            var = var->left;
    }
    if(lPBnode = NULL)
        return 0;
    while(lPBnode->price <= uPB){
        count++;
        lPBnode = TreeSuccessor(lPBnode);
    }
    return count;
}

void BST::copyBST(TreeNode* curr){
    if(curr == NULL)
        return;
    outfile << curr->identity << " " << curr->price << " " << curr->JourneyCode << endl;      
    copyBST(curr->left);
    copyBST(curr->right);
}
// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) { 
    outfile.open(filename);
    copyBST(root);
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
 
void BST::loadBST(TreeNode* pres){
    if(pres == NULL){
    }
}

void BST::customLoad (int flag, string filename) {
    infile.open(filename);
    loadBST(root);
    infile.close();
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


//int main(){
  //  BST* a= new BST;
    //a->insert(2763, 12);
    //a->remove(2763, 12);
//.}