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


// constructor when no parameter is passed

BST::BST(){
    root = nullptr;
}

// constructor when root is passed as parameter

BST::BST(TreeNode *root){
    this->root = root;
}



// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {

    TreeNode* x = root;
    TreeNode* y = nullptr;

    // when tree is empty, new element added is the root itself
    if(root == NULL){
        root = new TreeNode(JourneyCode, price, nullptr, nullptr, y);
        return true;
    }


    // in any other case
    while(true){
        if(x == nullptr){
            x = new TreeNode(JourneyCode, price, nullptr, nullptr, y);
            if(x->price > y->price) y->right = x;
            else y->left = x;
            return true;
        } else if(x->JourneyCode == JourneyCode) {
            return false;   // returns false when same journey code
        } else {
            if(price > x->price){
                y = x;
                x = x->right;   // moves right, if element has greater price than current node
            } else {
                y = x;
                x = x->left;    // moves left, if element has smaller price than current node
            }
        }
    }

}


// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {

    TreeNode *x = root;

    while(true){
        if(x == nullptr){
            return false;   // returns false if no element is found
        } else if(x->price == price && x->JourneyCode == JourneyCode){
            return true;    
        } else {
            if(price > x->price){
                x = x->right;
            } else {
                x = x->left;
            }
        }
    }
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
    TreeNode *x = root;
    TreeNode *y;

    // uses the code for 'find' to search element before removing

    while(true){
        if(x == nullptr){  
            return false;   
        } else if(x->price == price && x->JourneyCode == JourneyCode){
            y = x->parent;

            // case when the node has no children

            if(x->right == nullptr && x->left == nullptr){
        
                if(y->right == x){
                    y->right = nullptr;
                    return true;
                } else {
                    y->left = nullptr;
                    return true;
                }
            } 

            // case when the node has only a left child

            else if(x->right == nullptr && x->left != nullptr){
                
                if(y->right == x){
                    y->right = x->left;
                    return true;
                } else {
                    y->left = x->left;
                    return true;
                }

            }

            // case when the node has only a right child

            else if(x->right != nullptr && x->left == nullptr){

                if(y->right == x){
                    y->right = x->right;
                    return true;
                } else {
                    y->left = x->right;
                    return true;
                }

            }

            // case when the node has both left and right children

            else {

                TreeNode* curr = x->left;

                while(curr->right != nullptr)
                    curr = curr->right;

                BST::remove(curr->JourneyCode, curr->price);

                x->JourneyCode = curr->JourneyCode;
                x->price = curr->price;

            }


        } else {
            if(price > x->price){
                x = x->right;
            } else {
                x = x->left;
            }
        }
    }
}
	

// preorder traversal funciton
void BST::preOrder(TreeNode* x){

    if(x == nullptr) return;
    else {
        cout << x->price << endl;
        preOrder(x->left);
        preOrder(x->right);
    }
}


// postorder traversal funciton
void BST::postOrder(TreeNode* x){

    if(x == nullptr) return;
    else {
        postOrder(x->left);
        postOrder(x->right);
        cout << x->price << endl;
    }
}

// inorder traversal funciton
void BST::inOrder(TreeNode* x){

    if(x == nullptr) return;
    else {
        inOrder(x->left);
        cout << x->price << endl;
        inOrder(x->right);
    }
}




// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line


void BST::traverse(int typeOfTraversal) {

    TreeNode* x = root;

	if(typeOfTraversal == 0){
        preOrder(x);
    }

    else if(typeOfTraversal == 1){
        postOrder(x);
    }

    else if(typeOfTraversal == 2){
        inOrder(x);
    }
}


// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode* curr = root;

    if(root == nullptr) return 0;

    while(curr->left != nullptr)
        curr = curr->left;

    return curr->price;
}



// Part II




// helper function for the countJourney function, which basically
// pushes the elements in the vector using TreeSort
void BST::getSorted(vector<int> &v, TreeNode* x){
    if(x == nullptr) return;
    else {
        getSorted(v, x->left);
        v.push_back(x->price);
        getSorted(v, x->right);
    }
}



// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    vector<int> prices;
    int count = 0;
    getSorted(prices, root);

    for (auto i = prices.begin(); i != prices.end() ; ++i)
    {
        if(lowerPriceBound <= *i && *i <= upperPriceBound) count++;
    }
    return count;
}


// helper function for storing the Tree, using pre order sorting.
// the function outputs the tree as
//
//
// root->JourneyCode
// root->price
// root->left->JourneyCode
// root->left->price
// -1
// root->right->JourneyCode
// root->right->price
//
// when the right child is called, the negative of height is printed
//

void BST::storeHelper(string filename, TreeNode* x, int height){
    ofstream out;
    out.open(filename, ios_base::app);

    //preorder sort

    if(x==nullptr) return;
    else{
        out << x->JourneyCode << endl;
        out << x->price << endl;

        storeHelper(filename, x->left, height-1);
        if(x->right != nullptr) out << height << endl;
        storeHelper(filename, x->right, height-1);
    }

    out.close();
}




// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.


void BST::customStore(string filename) {

    storeHelper(filename, root);

}
	

// function loads the stored tree and
// helps to load the left sub-branch of the tree 


void BST::loadLeft(string filename){

    // file is opened
    ifstream in;
    in.open(filename);

    // vars declared
    int height = 0;
    int jcode;
    int price;
    TreeNode* x = root;

    int input;

    while(in >> input){
        // when right branch is opened
        if(input == -1){
            root = root->left;
            break;
        }

        // when the root is found. first iteration goes here
        if(height == 0){
            jcode = input;
            in >> price;
            root = new TreeNode(jcode, price, nullptr, nullptr, nullptr);
            x = root;
            height--;
        }

        // case when the branch is printed
        // height is taken as negative
        else if(input < 0){
            while(height  != input){
                x= x->parent;   // go to parent node
                height++;
            }

            in >> jcode;
            in >> price;

            // the right node of parent is defined
            x->right = new TreeNode(jcode, price, nullptr, nullptr, x);
            x = x->right;   
            height--;
            
        } else {
            // case when left node has to be printed
            jcode = input;
            in >> price;
            x->left = new TreeNode(jcode, price, nullptr, nullptr, x);
            x = x->left;
            height--;   // negative is postive :p

        }
    }
    in.close();
}


// function helps to load the tree from file,
// and also returns the whole tree, instead of 
// a subbranch

void BST::loadFull(string filename){
    
    // input stream defined
    ifstream in;
    in.open(filename);

    // vars defined
    int height = 0;
    int jcode;
    int price;
    TreeNode* x = root;

    int input;

    while(in >> input){
    
        // first case, to define the node
        if(height == 0){
            jcode = input;
            in >> price;
            root = new TreeNode(jcode, price, nullptr, nullptr, nullptr);
            x = root;
            height--;
        }

        // case when file has the -ve of branch
        // it goes to right child of the tree
        else if(input < 0){

            // loops until the proper height of the node is reached
            while(height  != input){
                x= x->parent;
                height++;
            }

            in >> jcode;
            in >> price;

            // right child is defined
            x->right = new TreeNode(jcode, price, nullptr, nullptr, x);
            x = x->right;   
            height--;
            
        } else {

            // case when left child is to be defined
            jcode = input;
            in >> price;
            x->left = new TreeNode(jcode, price, nullptr, nullptr, x);
            x = x->left;
            height--;   // negative is postive :p

        }
    }
    in.close();
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
    if(flag == 3){
        loadFull(filename);
    } else if(flag == 4){
        loadLeft(filename);
    }
}

// ************************************************************
// Please use the following code to replace the last part of
// BST.cpp that was provided earlier (from below the comment
// DO NOT CHANGE ANYTHING BELOW THIS LINE)
//
//

// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINES

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