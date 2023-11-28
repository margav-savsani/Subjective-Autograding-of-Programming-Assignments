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
#define SENTINAL -1


// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST(){; }
BST::BST(TreeNode *root){
    
    *BST::root = *root;
    //int var = 0;
    
     }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 

    TreeNode *present = NULL;  //declare a null TreeNode
    TreeNode *search = root;   //root of the tree
   // TreeNode *given;           //node for the given values
   // given->JourneyCode = JourneyCode;  //assign passed journeycode and price to "given" treenode
    //given->price = price;

    TreeNode *given = new TreeNode(JourneyCode,price);
     
    while(search != NULL){   // while root of the tree is not null, repeat the loop. finally "search" will give the correct insertion position for the "given" node.
        present = search;    // stores parent of "search" in "present"
        if(search->price > price){     //if price of root is greater than the given price
            search = search->left;            //go to the left subtree
        }
        else{                                 //if price of root is less than the given price
            search = search->right;           //go to the right subtree
        }
    }

    given->parent = present;    // make "present" the parent node of the given node. 

    if(present == NULL){   //if "present" is still NULL means our root of the tree was NULL
        root = given;      //store the "given" node into root.
        return true;       // insertion complete
    }
    else if(given->price < present->price){   //if "present" is not NULL and given price is less than the parent's price
        present->left = given;                // the "given" node will be left node of the parent.
        return true;                          // inserton complete
    }
    else if(given->price > present->price){    //else the "given" node will be right node of the parent.
        present->right = given;               
        return true;    
    }

}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 

    TreeNode *current_root = root;  //store root in TreeNode "current_root"

    while(current_root!=NULL && current_root->JourneyCode!=JourneyCode && current_root->price!=price){ //loop till current_root does not contain the given data
        if(current_root->price < price){
            current_root =  current_root->right;  //if given price is greater than price in current_root, store pointer of current_root->right into current_root 
        }
        else{
            current_root =  current_root->left;  // else store pointer of current_root->left into current_root
        }
    }
    if(current_root==NULL) return false;  // after looping if current_root is again NULL, then ticket not present and return false

    else if(current_root->JourneyCode==JourneyCode && current_root->price==price){  // else ticket is present and return true
        return true;
    }
    return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 

    if(find( JourneyCode, price)){  //if journeycode is present in the tree, go on

        TreeNode *found = root;   // store root of tree into TreeNode "found"
        TreeNode *assign;         
        TreeNode *current = NULL;   //y
        TreeNode *x = NULL;   //x
        TreeNode *succ = NULL;  //successor of assign
        TreeNode *mini = root;  //minimum of the tree
        TreeNode *ex = NULL;  //just declared to use as extra 

        while(found!=NULL && found->JourneyCode!=JourneyCode && found->price!=price){   //loop till current_root does not contain the given data
            if(found->price < price){   //if given price is greater than price in found, store pointer of found->right into found 
                found =  found->right;
            }
            else{
                found = found->left;   // else do opposite
            }
        }
    if(found==NULL) return false;  // after looping if current_root is again NULL, then ticket not present and return false

    else if(found->JourneyCode == JourneyCode && found->price == price){   //if after looping, found contains the given attributes
        assign = new TreeNode(JourneyCode,price,found->left,found->right ,found->parent);  //store found in TreeNode "assign"
    }

    if(assign->left == NULL || assign->right == NULL){  // 
        current = assign;
    }
    else{
        if(assign->right != NULL){
            //if(mini==NULL) return 0;
                while(mini->left != NULL){
                mini = mini->left;
                }
            succ = mini;
        }
        ex = assign->parent;
        while( ex != NULL && assign == ex->right){
            assign = ex;
            ex = ex->parent;
        }
        succ = ex;
        current = succ;
    }

    if(current->left != NULL){
        x = current->left;
    }
    else{
        x = current->right;
    }

    if(x != NULL){
        x->parent = current->parent;
    }

    if(current->parent == NULL){
        root = x;
    }
    else if(current == current->parent->left){
        current->parent->left = x;
    }
    else{
        current->parent->right = x;
    }

    if(current != assign){
        assign->JourneyCode = current->JourneyCode;
        assign->price = current->price;
    }
    return true;
}
    return false;
}
	
void BST::preo(TreeNode *tree){
    if(tree == NULL){
        return;
        }
    else{
        cout << tree->JourneyCode << endl;
        preo(tree->left);
        preo(tree->right);
}
}

void BST::posto(TreeNode *tree){
    if(tree == NULL){
        return;
        }
    else{
        posto(tree->left);
        posto(tree->right);
        cout << tree->JourneyCode << endl;
}
}

void BST::ino(TreeNode *tree){
    if(tree == NULL){
        return;
        }
    else{
        ino(tree->left);
        cout << tree->JourneyCode << endl;
        ino(tree->right);
        
}
}





// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    
    if(typeOfTraversal == 0){
        preo(root);
        }
    if(typeOfTraversal == 1){
        posto(root);
            }
    if(typeOfTraversal == 2){
        ino(root);
        }
 }

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode *minm = root;

    if(minm==NULL) return 0;
    while(minm->left != NULL){
        minm = minm->left;
    }
    return minm->price;
 }

// Part II

int BST::preo_count(TreeNode *tr, int lower, int upper){
    if(tr == NULL){
        return var;
        }
    else{
        if(tr->price >= lower && tr->price <= upper){
            var = var + 1;
        }
        preo_count(tr->left, lower, upper);
        preo_count(tr->right, lower, upper);
    }
    return var;
}

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    var = 0;
    return preo_count(root, lowerPriceBound, upperPriceBound);
     }


void BST::readf(TreeNode *tre, string fil){

     if(tre == NULL){
        outfile << SENTINAL << endl;
        return;
        }
    else{
        outfile << tre->JourneyCode << tre->price << endl;
        readf(tre->left, fil);
        readf(tre->right, fil);
}

}


// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) { 
    
    outfile.open("filename");
    readf(root, filename);
    outfile.close();
    
    return; }
	
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

void BST::writef(TreeNode *tre, string fil, int flag){
    if(flag == 4){
        infile >> Jcode >>  Jprice;

            if(Jcode == SENTINAL){ //write condition for file ending too
                return;
            }

            tre = new TreeNode(Jcode,Jprice);
            if(r==0){
                val = Jcode;
                r++;
            }
            writef(tre->left, fil, flag);
            if(tre->JourneyCode != val){
            writef(tre->right, fil, flag);
            }
        }
    else if(flag == 3){
        
        infile >> Jcode >>  Jprice;
        if(Jcode == SENTINAL){ //write condition for file ending too
                return;
            }

            tre = new TreeNode(Jcode,Jprice);
            writef(tre->left, fil, flag);
            writef(tre->right, fil, flag);
            if(infile.eof()) return;
            
    }
}



void BST::customLoad (int flag, string filename) { 
    ifstream infile;
    infile.open("filename");
    writef(root, filename, flag);
    infile.close();


return; }


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
