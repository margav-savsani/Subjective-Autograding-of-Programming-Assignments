//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <fstream>

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
bool BST::insert(int JourneyCode, int price){
    if(root==NULL){
        TreeNode* newNode = new TreeNode(JourneyCode,price);
        root = newNode;
        root->parent=NULL;
        return true;
    }
    if(find(JourneyCode, price)) return false;
    TreeNode* true_root = root;
    if(root->price<=price){
        if(root->right==NULL){
            TreeNode* newNode = new TreeNode(JourneyCode,price,NULL,NULL,root);
            root->right=newNode;
        }
        else{
            root = true_root->right;
            insert(JourneyCode,price);
            root = true_root;
        }
    }
    else{
        if(root->left==NULL){
            TreeNode* newNode = new TreeNode(JourneyCode,price,NULL,NULL,root);
            root->left=newNode;
        }
        else{
            root = true_root->left;
            insert(JourneyCode,price);
            root = true_root;
        }
    }
    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price){
    if(root==NULL) return false;
    if(root->price==price&&root->JourneyCode==JourneyCode) return true;
    TreeNode* true_root = root;
    if(root->price<=price){
        root = true_root->right;
        bool ans = find(JourneyCode,price);
        root = true_root;
        return ans;
    }
    else{
        root = true_root->left;
        bool ans = find(JourneyCode,price);
        root = true_root;
        return ans;
    }
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price){
    if(!find(JourneyCode,price)) return false;
    if(root==NULL) return false;
    if(root->JourneyCode==JourneyCode){
        if(root->left==NULL&&root->right==NULL){
            if(root->parent==NULL){
                root=NULL;
                return true;
            }
            else if(root->parent->left==root){
                root->parent->left=NULL;
                root->parent=NULL;
            }
            else if(root->parent->right==root){
                root->parent->right=NULL;
                root->parent=NULL;
            }
        }
        else if(root->left==NULL){
            root->price=root->right->price;
            root->JourneyCode=root->right->JourneyCode;
            root->left=root->right->left;
            root->right=root->right->right;
        }
        else if(root->right==NULL){
            root->price=root->left->price;
            root->JourneyCode=root->left->JourneyCode;
            root->right=root->left->right;
            root->left=root->left->left;
        }
        else{
            TreeNode* successor = root->right;
            while(successor->left!=NULL){
                successor=successor->left;
            }
            int final_price = successor->price;
            int final_code = successor->JourneyCode;
            remove(successor->JourneyCode,successor->price);
            root->price=final_price;
            root->JourneyCode=final_code;
        }
    }
    else if(price>=root->price){
        TreeNode* true_root = root;
        root = true_root->right;
        remove(JourneyCode,price);
        root = true_root;
    }
    else{
        TreeNode* true_root = root;
        root = true_root->left;
        remove(JourneyCode,price);
        root = true_root;
    }
    return true;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal){
    if(root==NULL) return;
    if(typeOfTraversal==0){
        TreeNode* true_root = root;
        cout << root->JourneyCode << endl;
        root=true_root->left;
        traverse(0);
        root=true_root->right;
        traverse(0);
        root=true_root;
    }
    else if(typeOfTraversal==1){
        TreeNode* true_root = root;
        root=true_root->left;
        traverse(1);
        root=true_root->right;
        traverse(1);
        root=true_root;
        cout << root->JourneyCode << endl;
    }
    else if(typeOfTraversal==2){
        TreeNode* true_root = root;

        root=true_root->left;
        traverse(2);

        cout << true_root->JourneyCode << endl;

        root=true_root->right;
        traverse(2);
        root=true_root;
    }
    return;
}

// Returns the price of the cheapest journey
int BST::getMinimum(){
    if(root==NULL) return -1;
    TreeNode* true_root = root;
    while(root->left!=NULL){
        root = root->left;
    }
    TreeNode* ans = root;
    root = true_root;
    return ans->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound){
    if(root==NULL) return 0;
    if(root->price<=upperPriceBound&&root->price>=lowerPriceBound){
        TreeNode* true_root = root;
        root = root->left;
        int left = countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
        root = true_root->right;
        int right = countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
        root = true_root;
        return 1 + left + right;
    }
    else if(root->price>upperPriceBound){
        TreeNode* true_root = root;
        root = root->left;
        int left = countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
        root = true_root;
        return left;
    }
    else{
        TreeNode* true_root = root;
        root = root->right;
        int right = countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
        root = true_root;
        return right;
    }
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename){
    ofstream outfile;
    outfile.open(filename);
    CustomStore1(outfile);
    return;
}
	
void BST::CustomStore1(ofstream &outfile){
    if(root==NULL) return;
    outfile << root->JourneyCode << ' ' << root->price << ' ';
    if(root->left==NULL) outfile << 0 << ' ';
    else outfile << 1 << ' ';
    if(root->right==NULL) outfile << 0 << ' ';
    else outfile << 1 << ' ';
    outfile << endl;
    if(root->left==NULL&&root->right==NULL) outfile << -1 << ' ' << -1 << ' ' << -1 << ' ' << -1 << '\n';
    TreeNode* true_root = root;
    root = true_root->left;
    CustomStore1(outfile);
    root = true_root->right;
    CustomStore1(outfile);
    root = true_root;
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
 
void BST::customLoad(int flag, string filename){
    ifstream infile;
    infile.open(filename);
    vector<TreeNode*> insert_to_right;
    TreeNode* current_parent;
    int insert_location;
    int journeyCode;
    int price;
    int l;
    int r;
    infile >> journeyCode >> price >> l >> r;
    TreeNode *root_node = new TreeNode(journeyCode,price);
    root = root_node;
    current_parent=root;
    if(r==1&&l==1) insert_to_right.push_back(root);
    if(r==1&&l==0) insert_location=1;
    else insert_location=0;
    while(!infile.eof()){
        if(journeyCode==-1){
            infile >> journeyCode >> price >> l >> r;
            if(infile.eof()){
                if(flag==4) root=root->left;
                return;
            }
            TreeNode *node = new TreeNode(journeyCode,price,NULL,NULL,insert_to_right.back());
            insert_to_right.back()->right=node;
            insert_to_right.pop_back();
            current_parent=node;
            if(r==1&&l==1) insert_to_right.push_back(node);
            if(r==1&&l==0) insert_location=1;
            else insert_location=0;
            continue;
        }
        infile >> journeyCode >> price >> l >> r;
        if(infile.eof()){
            if(flag==4) root=root->left;
            return;
        }
        if(journeyCode==-1) continue;
        TreeNode *node = new TreeNode(journeyCode,price,NULL,NULL,current_parent);
        if(insert_location==1) current_parent->right=node;
        else if(insert_location==0) current_parent->left=node;
        current_parent=node;
        if(r==1&&l==1) insert_to_right.push_back(node);
        if(r==1&&l==0) insert_location=1;
        else insert_location=0;
    }
    if(flag==4) root=root->left;
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
        cout << root->JourneyCode << '-' << root->price << endl;
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