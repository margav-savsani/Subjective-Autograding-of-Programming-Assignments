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

// Constructors for the BST Class
BST::BST(){
    root = NULL;
}
BST::BST(TreeNode *root){ this->root = root; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
     // initializes a node with the given parameters
     TreeNode * toInsert = new TreeNode;
     if (toInsert!=NULL){
        toInsert->JourneyCode = JourneyCode;
        toInsert->price = price;
     }
     if (root==NULL){
        // cout<<"root is null"<<endl;
        root = toInsert;
        return true;
     }

     // cout<<"Price of node to be inserted"<<toInsert->price<<endl;
     // cout<<"JourneyCode of node to be inserted"<<toInsert->JourneyCode<<endl;
     
     TreeNode *y = new TreeNode;
     TreeNode *x = root;

     while(x!=NULL){
        y = x;
        if(price< (x->price)){
            x = (x->left);
        }
        else{
            x = (x->right);
        }
     }
     toInsert->parent = y;
     if (y==NULL){
        root = toInsert;
        return true;
     }
     else if (toInsert->price < y->price){
        y->left = toInsert;
        return true;
     }
     else{
        y->right = toInsert;

        return true;
     }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    TreeNode * x = root;
    while (x!=NULL && (price!=(x->price) || JourneyCode!=(x->JourneyCode))){
        
        if(price < (x->price)){
            x = (x->left);
        }
        else {
            x = (x->right);
        }
    }
    if (x==NULL){
        return false;
    }
    if((price==(x->price) && JourneyCode==(x->JourneyCode))){
        return true; // both the prices and journey code matches
    }
    else{
        return false; // node not found
    }
    
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
    if (root==NULL){
        return false;
    }
    bool isPresent = find (JourneyCode, price);
    if (!isPresent){
        return false;
    }
    // Journey is present
    TreeNode* curr = root;

    while(curr!=NULL && curr->JourneyCode != JourneyCode){
        if (curr->left!=NULL && price < curr->price){
            curr = curr->left;
        }
        else if (curr->right!=NULL && price > curr-> price){
            curr = curr->right;
        }
    }
    if (curr==NULL){
        return false;
    }
    else{
        // The current node is leaf
        if (curr->left==NULL && curr->right == NULL){
            if (curr->parent!=NULL){
                if ((curr->parent)->left == curr){ // curr is left child
                    curr->parent->left = NULL;
                    curr->parent = NULL;
                    return true;
                }
                else if ((curr->parent)->right == curr){ // curr is right child
                    curr->parent->right = NULL;
                    curr->parent = NULL;
                    return true;
                }
            }
            else {// if parent = null, then curr is root 
                root = NULL;
                return true;
            }
        }

        // The current node has one child - left child
        if (curr->left != NULL && curr->right == NULL){
            // curr does not have a parent - it is root
            if (curr==root){
                root = curr->left;
                curr->left->parent = NULL;
                curr->left = NULL;
                return true;
            }
            // curr has a parent
            else if ((curr->parent)->left == curr){ // parent-curr-child form a straight line
                //creating new pointers
                (curr->parent)->left = curr->left;
                (curr->left)->parent = curr->parent;

                //deleting extra nodes
                curr->left = NULL;
                curr->parent = NULL;

                return true;
            }
            else{ // parent-curr-child do not form a straight line (form an angle)
                //creating new pointers
                (curr->parent)->right = curr->left;
                (curr->left)->parent = curr->parent;

                //deleting extra nodes
                curr->left = NULL;
                curr->parent = NULL;

                return true;
            }
        }
        else if (curr->right != NULL && curr->left == NULL){ // It has only right child
            // curr does not have a parent - it is root
            if (curr == root){
                root = curr->right;
                curr->right->parent = NULL;
                curr->right = NULL;
                return true;
            }
            // curr has a parent
            else if ((curr->parent)->right == curr){ // parent-curr-child form a straight line
                //creating new pointers
                (curr->parent)->right = curr->right;
                (curr->right)->parent = curr->parent;

                //deleting extra nodes
                curr->right = NULL;
                curr->parent = NULL;

                return true;
            }
            else{ // parent-curr-child do not form a straight line (form an angle)
                //creating new pointers
                (curr->parent)->left = curr->right;
                (curr->right)->parent = curr->parent;

                //deleting extra nodes
                curr->right = NULL;
                curr->parent = NULL;

                return true;
            }
        }
        else{ // node has both chidren
                //There will be a right tree

                TreeNode* succ = curr->right; // stores the pointer to successor of the current node
                while(succ->left!=NULL){
                    succ = succ->left;
                }
                // cout<<"succ of 10 is "<<succ->price;
                TreeNode* temp = new TreeNode; // to store the values of temp
                temp->JourneyCode = succ->JourneyCode;
                temp->price = succ->price;

                // Remove the successor
                // The current node is leaf
                if (succ->right == NULL){
                    if ((succ->parent)->left == succ){ // succ is left child
                        succ->parent->left = NULL;
                        succ->parent = NULL;
                    }
                    else if ((succ->parent)->right == succ){ // succ is right child
                        succ->parent->right = NULL;
                        succ->parent = NULL;
                    }
                    
                }

                // It has only right child

                else if (succ->right != NULL && succ->left == NULL){ // It has only right child
                    // succ does not have a parent - it is root
                    if (succ == root){
                        root = succ->right;
                        succ->right->parent = NULL;
                        succ->right = NULL;
                    }
                    // succ has a parent
                    else if ((succ->parent)->right == succ){ // parent-succ-child form a straight line
                        //creating new pointers
                        (succ->parent)->right = succ->right;
                        (succ->right)->parent = succ->parent;

                        //deleting extra nodes
                        succ->right = NULL;
                        succ->parent = NULL;
                    }
                    else{ // parent-succ-child do not form a straight line (form an angle)
                        //creating new pointers
                        (succ->parent)->left = succ->right;
                        (succ->right)->parent = succ->parent;

                        //deleting extra nodes
                        succ->right = NULL;
                        succ->parent = NULL;
                    }
                } 

                //copying the values of the successor into the current node
                curr->JourneyCode  = temp->JourneyCode;
                curr->price = temp->price;
                delete temp;

                return true;
            }
    }

      
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal==2){
        TreeNode* x = root;

        if(x->left != NULL){ BST leftTree(x->left); leftTree.traverse(IN_ORDER);}
        cout<<(x->JourneyCode)<<" ";
        if(x->right != NULL){ BST rightTree(x->right); rightTree.traverse(IN_ORDER);} 
        
    }
    else if(typeOfTraversal==1){
        TreeNode* x = root;

        if(x->left != NULL){ BST leftTree(x->left); leftTree.traverse(POST_ORDER);}
        if(x->right != NULL){ BST rightTree(x->right); rightTree.traverse(POST_ORDER);}
        cout<<(x->JourneyCode)<<" ";
        
    }
    else if(typeOfTraversal==0){
        TreeNode* x = root;

        cout<<(x->JourneyCode)<<" ";
        if(x->left != NULL){ BST leftTree(x->left); leftTree.traverse(PRE_ORDER);}
        if(x->right != NULL){ BST rightTree(x->right); rightTree.traverse(PRE_ORDER);}
        
    }
    return; 
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    if(root==NULL){
        return 0; // no tree case
    }
    if(root->left == NULL){
        return root->price; // returns the price of the root if only one node is present in the tree
    }
    // else left child exists
    TreeNode *leftChild =  root;

    while(leftChild->left!=NULL){
        leftChild = leftChild->left;
    }
    return leftChild->price; 
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.

int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    return countRecursive(root, lowerPriceBound, upperPriceBound);
}
int BST::countRecursive(TreeNode* curr, int lowerPriceBound, int upperPriceBound){
    if (curr==NULL){
        return 0;
    }
    if (curr->price < lowerPriceBound){
            return countRecursive(curr->right, lowerPriceBound, upperPriceBound);
    }
    else if (curr->price >upperPriceBound){
            return countRecursive(curr->left, lowerPriceBound, upperPriceBound);
    }
    else {
        return 1 + countRecursive(curr->right, lowerPriceBound, upperPriceBound) + countRecursive(curr->left, lowerPriceBound, upperPriceBound);
    }
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

    if (root == NULL){
        outfile.close(); // to close the file if no tree
    }

    vector<TreeNode *> nodes;
    nodes.push_back(root);

    while(nodes.empty() == false){
        TreeNode * curr = nodes[nodes.size()- 1];
        if (curr==root->left){ // to enter the sentinel to identify the start of left subtree
            outfile<<"-1 -1"<<endl;
        }
        if (curr==root->right){ // to enter sentinel to identify end of left subtree
            outfile<<"-2 -2"<<endl;
        }
        outfile<< curr->JourneyCode <<" "<<curr->price<<endl; // to store the journey code and price in the output file
        
        nodes.pop_back();
        if (curr->right!=NULL){
            nodes.push_back(curr->right);
        }
        if (curr->left){
            nodes.push_back(curr->left);
        }
    }
    

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
    
    ifstream infile;
    infile.open(filename);
    // cout<<"File is open? "<<infile.is_open()<<endl;
    int JourneyCode, price;
    vector<int> preOrder;
    vector <int> preOrderCodes;

    if (flag == LOAD_FULL_BST){
        while(infile>> JourneyCode && infile>> price){
            if (price==-1 && JourneyCode==-1 || price==-2 && JourneyCode==-2){ //sentinel for identifying left subtree
                continue; // ignoring the sentinels for printing the full BST
            }
            preOrder.push_back(price);
            preOrderCodes.push_back(JourneyCode);

            // cout<<JourneyCode;
            // cout<<price;
        }
    }
    else if (flag == LOAD_LEFT_SUBTREE){
        bool inLeftTree = false;
        while(infile>> JourneyCode && infile>> price){ 
            if (price==-1 && JourneyCode==-1){ //sentinel for identifying left subtree
                inLeftTree = true;
                continue;
            }
            if (price==-2 && JourneyCode==-2){ //sentinel for identifying left subtree
                inLeftTree = false;
                break;
            }
            if (inLeftTree == true){
                preOrder.push_back(price);
                preOrderCodes.push_back(JourneyCode);
            }

            // cout<<JourneyCode;
            // cout<<price;
        }
    }

    // the first element is the root of BST
    root = new TreeNode(preOrderCodes[0], preOrder[0]);
    // create a stack and push root to it
    vector<TreeNode * > nodes;
    nodes.push_back(root); // pushes the root in the stack
    
    // traverse the array from index 1
    for (int i = 1; i < preOrder.size(); i++) {
        // initialize temp as null
        TreeNode *temp = NULL;
        
        // while current element is greater than top of stack
        // remove top of stack and store it in temp
        while ((nodes.size()!=0) && preOrder[i] > nodes[nodes.size() -1]->price) {
            temp = nodes[nodes.size() -1];
            nodes.pop_back();
        }
        
        // if temp is null
        if (temp == NULL) {
            // make temp as top of stack
            temp = nodes[nodes.size() -1];
            // current element is left of temp
            temp->left = new TreeNode(preOrderCodes[i], preOrder[i]);
            // add current element to stack
            nodes.push_back(temp->left);
        } else {
            // current element is right of temp
            temp->right = new TreeNode(preOrderCodes[i], preOrder[i]);
            // add current element to the stack
            nodes.push_back(temp->right);
        }
    }

    infile.close();
}


// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE


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


