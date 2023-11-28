#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <string.h>

using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4




// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Constructor
// an empty tree is denoted by a root node with journeycode and price both 0 and all 3 pointers as NULL
BST::BST(){
    root = new TreeNode();
}

BST::BST(TreeNode *root){
    this->root = root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price){
    if(root->price == 0){// if empty tree
        root->JourneyCode = JourneyCode;
        root->price = price;
        return true;
    }
    return insertRecursive(JourneyCode, price, root);// called a recursive function
}
// same element is inserted in the 
bool BST::insertRecursive(int JourneyCode, int price, TreeNode* myroot){
    if(myroot->JourneyCode == JourneyCode){// if same journey code present, returns false
        return false;
    }
    else if(myroot->price <= price){// if price of given insert is greater then or equal to the price at a node, the new node will be inserted in the right tree. Note: node with same price is inserted in the right tree
        if(myroot->right == NULL){// if right is null, insert the node
            myroot->right = new TreeNode(JourneyCode,price,NULL, NULL, myroot);
            return true;
        }
        else return insertRecursive(JourneyCode, price, myroot->right);// else call recursively
    }
    else{// similarly for left
        if(myroot->left == NULL){
            myroot->left = new TreeNode(JourneyCode,price,NULL, NULL, myroot);
            return true;
        }
        else return insertRecursive(JourneyCode, price, myroot->left);
    }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    if(root->price==0){// if tree is empty, return false
        return false;
    }
    else return findRecursive(JourneyCode,price,root); // called recursive function
}
//find recursively
bool BST::findRecursive(int JourneyCode, int price,TreeNode* myroot){
    if(myroot == NULL){// if we get a null node, it basically means that node isn't present
        return false;
    }
    else if(myroot->JourneyCode == JourneyCode){// if we get the journey code, return true to indicate presence
        return true;
    }
    else if(myroot->price <= price){// otherwise recursively call on left or right branch as appropriate based on price
        return findRecursive(JourneyCode, price, myroot->right);
    }
    else{
        return findRecursive(JourneyCode, price, myroot->left);
    }
}
	

	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    if(root->price == 0) return false;// empty tree returns false
    else return removeRecursive(JourneyCode, price, root, false);// call recursive function
}

bool BST::removeRecursive(int JourneyCode, int price, TreeNode* myroot, bool isleft){// same as find except if we find the node, we call the deletNode function to delete that node
    if(myroot == NULL){
        return false;
    }
    else if(myroot->JourneyCode == JourneyCode){
        deleteNode(myroot, isleft);
        return true;
    }
    else if(myroot->price <= price){
        return removeRecursive(JourneyCode, price, myroot->right,  false);
    }
    else{
        return removeRecursive(JourneyCode, price, myroot->left, true);
    }
}

void BST::deleteNode(TreeNode* node, bool isleft){// deletes a particular node, bool isleft is not needed but makes the code easier to interpret
    //no child
    if(node->left == NULL && node->right == NULL){
        if(node->parent == NULL){// if root
            delete root;
            root = new TreeNode;
        }
        else{//delete the node and set the parent's child's pointer to NULL(appropriate pointer)
            if(isleft){
                node->parent->left = NULL;
            }
            else{
                node->parent->right = NULL;
            }
            delete node;
        }
    }

    //one left child only
    else if(node-> right == NULL){// if right node not pressent
        if(node->parent == NULL){// root
            root->left->parent = NULL;
            TreeNode* newroot = root->left;
            delete root;
            root = newroot;
        }
        else{
            if(isleft){// pounter arithmetic for the deletion
                node->parent->left = node->left;
                node->left->parent = node->parent;
                delete node;
            }
            else{
                node->parent->right = node->left;
                node->left->parent = node->parent;
                delete node;
            }
        }
    }

    //one right child only
    else if(node-> left == NULL){
        if(node->parent == NULL){
            root->right->parent = NULL;
            TreeNode* newroot = root->right;
            delete root;
            root = newroot;
        }
        else{
            if(isleft){
                node->parent->left = node->right;
                node->right->parent = node->parent;
                delete node;
            }
            else{
                node->parent->right = node->right;
                node->right->parent = node->parent;
                delete node;
            }
        }
    }

    //2 children, successor used
    else{
        TreeNode* successorNode = getMinimumNode(node->right);// save the values of successor in our node and delete the successor thus replacing our node with the successor is achieved
        node->JourneyCode = successorNode->JourneyCode;
        node->price = successorNode->price;
        if(node->right != successorNode) deleteNode(successorNode, true);
        else deleteNode(successorNode,false);
    }
    return;
}


// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {// calls correct traverse function
    if(root->price == 0){
        cout <<"empty tree\n";
        return;    
    }
    if(typeOfTraversal == 0) pretrav(root);
    else if(typeOfTraversal == 1) posttrav(root);
    else if(typeOfTraversal == 2) intrav(root);
    else cout << "Not a correct type of traversal\n";
    return; 
}

void BST::pretrav(TreeNode* myroot){// pretraversal
    if(myroot == NULL) return;
    cout << myroot->JourneyCode << "\n";
    pretrav(myroot->left);
    pretrav(myroot->right);
    return;
}

void BST::posttrav(TreeNode* myroot){//post traversal
    if(myroot == NULL) return;
    posttrav(myroot->left);
    posttrav(myroot->right);
    cout << myroot->JourneyCode << "\n";
    return;
}

void BST::intrav(TreeNode* myroot){// inorder
    if(myroot == NULL) return;
    intrav(myroot->left);
    cout << myroot->JourneyCode << "\n";
    intrav(myroot->right);
    return;
}


// Returns the price of the cheapest journey
int BST::getMinimum() {
    if(root->price == 0) return -1;//placeholder value, indicates empty tree, need to update the function in main.cpp to use this funcitonality
    return getMinimumNode(root)->price;
}
TreeNode* BST::getMinimumNode(TreeNode* myroot){
    if(myroot->left == NULL) return myroot;
    else return getMinimumNode(myroot->left);
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {// inorder traversal with conditions
    int ans = recurintravPricecount(root, lowerPriceBound, upperPriceBound);
    return ans; 
}

int BST::recurintravPricecount(TreeNode* myroot,int lowerPriceBound, int upperPriceBound){
    if(myroot == NULL) return 0;
    int left = 0, atnode = 0, right = 0;
    if(myroot->price > lowerPriceBound) left =recurintravPricecount(myroot->left,lowerPriceBound,upperPriceBound);
    if(lowerPriceBound <= myroot->price && upperPriceBound >= myroot->price) atnode = 1;
    if(myroot->price <= upperPriceBound) right =recurintravPricecount(myroot->right,lowerPriceBound,upperPriceBound);
    return left+atnode+right;
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.

void BST::customStore(string filename) { //#denotes left, ! denotes right

    ofstream outfile;
    outfile.open(filename);
    customStorerecur(root,"", outfile);
    outfile.close();
    return;

}

void BST::customStorerecur(TreeNode* myroot,const string& sentinal, ofstream& file){

    if(myroot == NULL) return;
    file << myroot->JourneyCode << " " << myroot->price <<" " << sentinal << "\n";
    customStorerecur(myroot->left, sentinal + "#", file);// stored sentinal to indicate position for O(n) building
    customStorerecur(myroot->right, sentinal + "!", file);
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
 

void BST::customLoad (int flag, string filename) { 
    ifstream infile;
    infile.open(filename);
    if(flag == LOAD_FULL_BST){
        root = new TreeNode;
        infile >> root->JourneyCode >> root->price;//set root
        TreeNode* myroot = root;
        string prevSentinal = "";
        while(true){
            TreeNode* node = new TreeNode;
            string sentinal;
            infile >> node->JourneyCode>>node->price>>sentinal;
            if(infile.eof()) break;

            for(int i = 0; i < prevSentinal.size()-sentinal.size()+1;i++ ){
                myroot= myroot->parent;// go as many back as needed

            }
            if(sentinal[sentinal.size()-1] == '#'){// set value
                myroot->left = node;
                node->parent = myroot;
                myroot = myroot->left;
            }
            else{
                myroot->right = node;
                node->parent = myroot;
                myroot= myroot->right;
            }
            prevSentinal = sentinal;// for next iteration
        }
    }
    else{
        root = new TreeNode;// similar as above just starts at one step later and ends earlier
        infile >> root->JourneyCode >> root->price;
        string prevSentinal;
        infile >> root->JourneyCode >> root->price >> prevSentinal;
        if(prevSentinal[0] == '!'){
            delete(root);
            root = new TreeNode;
            return;
        }
        TreeNode* myroot = root;
        while(true){
            TreeNode* node = new TreeNode;
            // TreeNode* myroot = root;
            string sentinal;
            infile >> node->JourneyCode>>node->price>>sentinal;
            if(infile.eof() || sentinal[0] == '!') break;

            for(int i = 0; i < prevSentinal.size()-sentinal.size()+1;i++ ){
                myroot= myroot->parent;

            }
            if(sentinal[sentinal.size()-1] == '#'){
                myroot->left = node;
                node->parent = myroot;
                myroot = myroot->left;
            }
            else{
                myroot->right = node;
                node->parent = myroot;
                myroot= myroot->right;
            }
            prevSentinal = sentinal;
        }
    }
    return; 
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
