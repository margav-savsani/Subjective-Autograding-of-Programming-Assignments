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

BST::BST(){; }
BST::BST(TreeNode *root){; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    
    if(root == NULL){
        root = new TreeNode(JourneyCode, price);
        return true;
    }
    else{
        TreeNode *temp = root;
        while(temp != NULL){

            if(temp->price > price){
                if(temp->left == NULL){
                    temp->left = new TreeNode(JourneyCode, price);
                    
                    temp->left->parent = temp;

                    return true;
                }
                else{
                    temp = temp->left;
                }
            }
            else{
                if(temp->right == NULL){
                    temp->right = new TreeNode(JourneyCode, price);

                    temp->right->parent = temp;

                    return true;
                }
                else{
                    // cout << "11 check" << endl; 
                    temp = temp->right;
                }
            }
        }
    }
    
    return false;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    
    TreeNode *temp = root;

    while(temp != NULL){
        if(temp->JourneyCode == JourneyCode){
            return true;
        }
        else if(temp->price > price){
            temp = temp->left;
        }
        else{
            temp = temp->right;
        }
    }
    
    return false; 
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    
    TreeNode *temp = root;
    while(temp != NULL){

        if(temp->JourneyCode == JourneyCode){

            // cout << "found " << JourneyCode << endl;

            if (temp == root){
                if (temp->left == NULL && temp->right == NULL){
                    delete temp;
                    root = NULL;
                    return true;

                } else {

                    if (temp->left == NULL){
                        root = temp->right;
                        root->parent = NULL;
                       
                        delete temp;
                        return true;

                    } else if (temp->right == NULL){
                        root = temp->left;
                        root->parent = NULL;
                       
                        delete temp;
                        return true;

                    } else {
                        if (temp->right->left != NULL){

                            TreeNode *temp2 = temp->right->left;

                            while(temp2->left != NULL){
                                temp2 = temp2->left;
                            }

                            // temp2->right = root->right;
                            // temp2->left = root->left;

                            root->JourneyCode = temp2->JourneyCode;
                            root->price = temp2->price;

                            if(temp2->right != NULL){
                                temp2->parent->left = temp2->right;
                                temp2->right->parent = temp2->parent;
                            } else {
                                temp2->parent->left = NULL;
                            }

                            // temp2->parent->left = NULL;
                            // root = temp2;
                            // root->parent = NULL;

                            // temp2->right->parent = temp2;
                            // temp2->left->parent = temp2;

                            // delete temp;
                            delete temp2;
                            return true;

                        } else {

                            temp->right->left = root->left;
                            temp->right->left->parent = temp->right;
                            root = temp->right;
                            root->parent = NULL;

                            delete temp;
                            return true;
                        }
                    }

                }

            } else if(temp->left == NULL && temp->right == NULL){

                // cout << "!" << endl;

                if(temp->parent->left == temp){
                    temp->parent->left = NULL;
                }
                else{
                    temp->parent->right = NULL;
                }

                delete temp;
                return true;
            } else if(temp->left == NULL){
                // cout << "!!" << endl;

                // cout << temp->parent->JourneyCode << endl;
                // cout << temp->JourneyCode << endl;
                // cout << temp->parent->left->JourneyCode << endl;

                if(temp->parent->left == temp){

                    // cout << "ohmg" << endl;
                    temp->parent->left = temp->right;
                    temp->right->parent = temp->parent;
                }
                else{


                    temp->parent->right = temp->right;

                    temp->right->parent = temp->parent;




                }
                    delete temp;
                    return true;


            } else if(temp->right == NULL){
                // cout << "!!!" << endl;

                if(temp->parent->left == temp){
                    temp->parent->left = temp->left;
                    // temp->left->parent = temp->parent;
                }
                else{
                    temp->parent->right = temp->left;
                    // temp->left->parent = temp->parent;
                }

                temp->left->parent = temp->parent;
                
                delete temp;
                return true;
            } else {

                // cout << "ohh" << endl;

                TreeNode *temp2 = temp->right;

                while(temp2->left != NULL){
                    temp2 = temp2->left;
                }

                temp->JourneyCode = temp2->JourneyCode;
                temp->price = temp2->price;

                if (temp2->parent == temp){
                    if (temp2->right != NULL){
                        temp2->parent->right = temp2->right;
                        temp2->right->parent = temp2->parent;
                    } else {
                        temp2->parent->right = NULL;
                    }

                } else {

                    if (temp2->right != NULL){
                        // cout << "hm" << endl;
                        temp2->parent->left = temp2->right;
                        temp2->right->parent = temp2->parent;
                    } else {
                        temp2->parent->left = NULL;
                    }

                }


                delete temp2;
                return true;
            }

        } else if(temp->price > price){
            // cout << price << " " << temp->JourneyCode << " " << temp->price << endl;
            temp = temp->left;
        } else {
            // cout << price << " " << temp->JourneyCode << " " << temp->price << endl;
            temp = temp->right;

        }

    }
    
    return false; 
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void preOrder(TreeNode *temp){
    
    if(temp != NULL){
        cout << temp->JourneyCode << endl;
        preOrder(temp->left);
        preOrder(temp->right);
    }
    
    return;
}

void postOrder(TreeNode *temp){
    
    if(temp != NULL){
        postOrder(temp->left);
        postOrder(temp->right);
        cout << temp->JourneyCode << endl;
    }
    
    return;
}

void inOrder(TreeNode *temp){
    
    if(temp != NULL){
        inOrder(temp->left);
        cout << temp->JourneyCode << endl;
        inOrder(temp->right);
    }
    
    return;
}

void BST::traverse(int typeOfTraversal) {
    
    if(typeOfTraversal == 0){
        preOrder(root);
    }
    else if(typeOfTraversal == 1){
        postOrder(root);
    }
    else if(typeOfTraversal == 2){
        inOrder(root);
    }
    
    return; 
}


// Returns the price of the cheapest journey
int BST::getMinimum() {

    TreeNode *temp = root;

    if (root != NULL){

        int min = temp->price;
    
        while(temp != NULL){

            if(temp->price < min){
                min = temp->price;
            }

            temp = temp->left;
        }

        return min;

    }

    return 0; 
}

// Part II

void InOrder_no_cout(TreeNode *temp, int lowerPriceBound, int upperPriceBound, int& count){
    
    if(temp != NULL){
        InOrder_no_cout(temp->left, lowerPriceBound, upperPriceBound, count);
        if (temp->price >= lowerPriceBound && temp->price <= upperPriceBound){
            count += 1;
        }
        InOrder_no_cout(temp->right, lowerPriceBound, upperPriceBound, count);
    }     
}

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {

    TreeNode* temp = root;
    int count = 0;

    InOrder_no_cout(temp, lowerPriceBound, upperPriceBound, count);

    return count;

}

void recursive_store(ofstream& file_to_append , TreeNode* root) { 

    if (root != NULL){ 

        file_to_append << root->JourneyCode << " " << root->price << endl;
        
        recursive_store(file_to_append, root->left);
        recursive_store(file_to_append, root->right);

    } else {

        file_to_append << "- -" << endl;
    }

} 

void recursive_load(ifstream& file , TreeNode* child , TreeNode* root_parent, int flag, TreeNode* root) { 
    string left;
    string right;

    if (!file.eof()) {
        
        // get two characters of a line
        file >> left >> right;
         
        if ( left == "-" && right == "-")  { 
            if (root_parent->right == child) {
                root_parent->right = NULL;
            } 
            else {
                root_parent->left = NULL;
            } 

            delete child; 
        } 
        else { 

            if (flag == 4){
                if (root_parent != child){
                    if (stoi(right) > root->price){
                        cout << stoi(right) << " " << root->price << endl;
                        root->right = NULL;
                        delete child;
                    }
                }
            }
 
            child->parent = root_parent;
            child->JourneyCode = stoi(left); 
            child->price = stoi(right);

            child->left = new TreeNode(); 
            child->right = new TreeNode(); 

            recursive_load(file, child->left, child, flag, root); 
            recursive_load(file, child->right, child, flag, root); 

        } 
    }
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) { 

    ofstream file; file.open(filename);
    
    recursive_store(file,root) ;  
    
    file.close(); 
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
    
    ifstream file ; 
    file.open(filename);

    root = new TreeNode();

    recursive_load(file, root, NULL, flag, root);
    file.close(); 
    
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
        root = curr;
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
        result.push_back(to_string(root->JourneyCode) + "\n");
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        getBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr;
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

