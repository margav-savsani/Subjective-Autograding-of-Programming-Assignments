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
    root = nullptr;
}
BST::BST(TreeNode *root){
    this->root = root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
    if(root == nullptr){ // Empty BST
        root = new TreeNode(JourneyCode, price, nullptr, nullptr, nullptr);
        return true;
    }
    TreeNode *node, *p;
    p = new TreeNode;
    node = root;
    while(true){
        if(node->price >= price && node->left == nullptr){
            p->parent = node;
            node->left = p;
            p->JourneyCode = JourneyCode;
            p->price = price;
            return true;
        }
        else if(node->price < price && node->right == nullptr){
            p->parent = node;
            node->right = p;
            p->JourneyCode = JourneyCode;
            p->price = price;
            return true;
        }
        else if(node->price >= price){
            if(node->price == price && node->JourneyCode == JourneyCode) return false;
            node = node->left; // Moving to the left even if it is equal
        }
        else node = node->right;
    }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    TreeNode *node;
    node = root;
    while(true){
        if(node->price == price){
            if(node->JourneyCode == JourneyCode) return true;
            else node = node->left;
        }
        else if(node->price > price) node = node->left;
        else node = node->right;
        if(node == nullptr) break;
    } 
    return false; 
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {

     TreeNode *node;
     node = root;
     while(true){
        if(node->price >= price){
            if(node->price == price && node->JourneyCode == JourneyCode){
                
                // Case 1
                if(node->left==nullptr && node->right==nullptr){

                    if(node->parent == nullptr){
                        
                        delete node;
                        root = nullptr;
                        return true;
                    }
                    else if(node->parent->left == node) {  

                        node->parent->left = nullptr;}
                    else {
                        
                        node->parent->right = nullptr;}
                    delete node;
                }

                // Case 2
                else if((node->left == nullptr && node->right != nullptr)||(node->left != nullptr && node->right == nullptr)){

                    if(node == root){
                        if(node->left == nullptr) root = node->right;
                        else root = node->left;
                        delete node;
                        return true;
                    }
                    if(node->left == nullptr){
                        node->right->parent = node->parent;
                        if(node->parent->left == node) node->parent->left = node->right;
                        else node->parent->right = node->right;
                        delete node;
                        return true;
                    }
                    else{
                        node->left->parent = node->parent;
                        if(node->parent->left == node) node->parent->left = node->left;
                        else node->parent->right = node->left;
                        delete node;
                        return true;
                    }
                }

                // Case 3
                else{
                    TreeNode *temp;
                    temp = node->left;
                    while(true){
                        if(temp->right == nullptr) break;
                        temp = temp->right;
                    }
                    int jou = temp->JourneyCode;
                    int pri = temp->price;
                    remove(temp->JourneyCode, temp->price);
                    node->JourneyCode = jou;
                    node->price = pri;
                }

                return true;
            }
            node = node->left;
        }
        else node = node->right;
        if(node == nullptr) break;
     }
     return false;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal == PRE_ORDER) traversePre(root);
    else if(typeOfTraversal == POST_ORDER) traversePost(root);
    else if(typeOfTraversal == IN_ORDER) traverseIn(root);
}

void BST::traversePre(TreeNode *node){
    if(node == nullptr) return;
    cout << node->JourneyCode << endl;
    traversePre(node->left);
    traversePre(node->right);
}

void BST::traversePost(TreeNode *node){
    if(node == nullptr) return;
    traversePre(node->left);
    traversePre(node->right);
    cout << node->JourneyCode << endl;
}

void BST::traverseIn(TreeNode *node){
    if(node == nullptr) return;
    traversePre(node->left);
    cout << node->JourneyCode << endl;
    traversePre(node->right);
}


// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode *node = root;
    while(node->left != nullptr){
        node = node->left;
    }
    return node->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    vector <int> prices;
    traverseSort(prices, root);
    int start = 0, end = 0;
    for(int i = 0; i < prices.size(); i++){
        if(prices[i] >= lowerPriceBound){
            start = i;
            break;
        }
    }
    for(int i = start; i < prices.size(); i++){
        if(prices[i] >= upperPriceBound){
            start = i-1;
            break;
        }
        end = prices.size()-1;
    }
    return end-start+1;
}

void BST::traverseSort(vector <int> &prices, TreeNode *node){
    if(node == nullptr) return;
    traverseSort(prices, node->left);
    prices.push_back(node->price);
    traverseSort(prices, node->right);
}



// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) {
    ofstream o;
    o.open(filename); 
    cs(filename, root, o);
    o.close();
}

void BST::cs(string filename, TreeNode* node, ofstream& o){
    if(node == nullptr) return;
    o << node->JourneyCode << " " << node->price << endl;
    if(node->left != nullptr){
        o << "-1" << endl;
        cs(filename, node->left, o);
        o << "-2" << endl << "0" << endl;
    }
    if(node->right != nullptr){
        o << "-3" << endl;
        cs(filename, node->right, o);
        o << "-4" << endl << "0" << endl;
    }
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
    ifstream i;
    i.open(filename);
    int jou, pri;
    i >> jou >> pri;
    root = new TreeNode(jou, pri, nullptr, nullptr, nullptr);
    if(flag == LOAD_LEFT_SUBTREE){
        int d;
        i >> d;
        if(d != -1) return;
        else{
            int jou, pri;
            i >> jou >> pri;
            TreeNode *node = new TreeNode(jou, pri, nullptr, nullptr, root);
            vector <TreeNode*> par;
            for(int line = 2; true; line++){
                if(line%2 == 0){
                    int d;
                    i >> d;
                    if(d == -1){
                        par.push_back(node);
                        TreeNode *temp = new TreeNode;
                        node->left = temp;
                        temp->parent = par.back();
                        node = temp;
                    }
                    else if(d == -3){
                        par.push_back(node);
                        TreeNode *temp = new TreeNode;
                        node->right = temp;
                        temp->parent = par.back();
                        node = temp;
                    }
                    else if(d == -2 || d == -4){
                        node = par.back();
                        if(node == root && d == -2) return;
                        par.pop_back();
                    }
                }
                else{
                    int jou, pri;
                    i >> jou;
                    if(jou == 0){}
                    else{
                        i >> pri;
                        node->JourneyCode = jou;
                        node->price = pri;
                    }
                }
                if(i.eof()) break;
            }
            i.close();
            return;
        }
    } 
    TreeNode *node = root;
    vector <TreeNode*> par;
    for(int line = 2; true; line++){
        if(line%2 == 0){
            int d;
            i >> d;
            if(d == -1){
                par.push_back(node);
                TreeNode *temp = new TreeNode;
                node->left = temp;
                temp->parent = par.back();
                node = temp;
            }
            else if(d == -3){
                par.push_back(node);
                TreeNode *temp = new TreeNode;
                node->right = temp;
                temp->parent = par.back();
                node = temp;
            }
            else if(d == -2 || d == -4){
                node = par.back();
                par.pop_back();
            }
        }
        else{
            int jou, pri;
            i >> jou;
            if(jou == 0){}
            else{
                i >> pri;
                node->JourneyCode = jou;
                node->price = pri;
            }
        }
        if(i.eof()) break;
    }
    i.close();
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