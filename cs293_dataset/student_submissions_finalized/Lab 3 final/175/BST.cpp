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

BST::BST(){ // the constructors were pretty straightforward
    root = nullptr;
}
BST::BST(TreeNode *root){
    this->root = root;
    root->parent = nullptr;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price){
    if (find(JourneyCode, price)){ // this checks if the ticket is already present or not
        return false;
    }
    else{
        TreeNode *tmp = root;
        TreeNode *parent = nullptr;
        bool dir;       // 'dir' gives the direction of traversing which is used in line 50
        while (tmp != nullptr){
            if (tmp->price >= price){ // Even if the price is equal, I go to left subtree
                parent = tmp;
                tmp = tmp->left;
                dir = true;
            }
            else{
                parent = tmp;
                tmp = tmp->right;
                dir = false;
            }
        }
        if (parent != nullptr){ // the 'non-root' case
            if (dir){
                parent->left = new TreeNode(JourneyCode, price, nullptr, nullptr, parent);
            }
            else{
                parent->right = new TreeNode(JourneyCode, price, nullptr, nullptr, parent);
            }
        }
        else{ // the 'root' case
            root = new TreeNode(JourneyCode, price, nullptr, nullptr, nullptr);
        }
    }
    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price){
    TreeNode *tmp = root;
    while (tmp != nullptr){
        if (tmp->price == price){
            if (tmp->JourneyCode == JourneyCode){ // return true only if the ticket is found 
                return true;
            }
            tmp = tmp-> left; // I go to the left subtree even if prices are equal since that's how I have implemented the 'insert' function
        }
        else if (tmp->price > price){
            tmp = tmp->left;
        }
        else{
            tmp = tmp->right;
        }
    }
    return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price){
    TreeNode *tmp = root;
    if (tmp == nullptr){ // the 'null-tree' case
        return false;
    }
    else if (tmp->JourneyCode == JourneyCode && tmp->price == price){ // the 'root' case starts here and goes upto line 127
        if (root->left == nullptr && root->right == nullptr){ // zero childs
            root = nullptr;
        }
        else if (root->left != nullptr && root->right == nullptr){ // one child
            root = root->left;
            root->parent = nullptr;
        }
        else if (root->left == nullptr && root->right != nullptr){ // one child
            root = root->right;
            root->parent = nullptr;
        }
        else{               // two childs
            TreeNode *tmp1 = root->left;
            TreeNode *pred = nullptr;
            while (tmp1 != nullptr){
                pred = tmp1;        // finding the predecessor
                tmp1 = tmp1->right;
            }
            if (pred == root->left){ // a separate check to improve the function
                TreeNode *pred_child = pred->left;
                root->JourneyCode = pred->JourneyCode;
                root->price = pred->price;
                root->left = pred_child;
                if (pred_child != nullptr){
                    pred_child->parent = root;
                }
            }
            else{               // swapping the root and the predecessor
                TreeNode *pred_parent =pred->parent;
                pred_parent->right = pred->left;
                root = pred;
                root->left = tmp->left;
                root->right = tmp->right;
            }
        }
    }
    else{                   // the 'non-root' case
        TreeNode *node = nullptr; // finding the 'node' to be deleted
        while(tmp != nullptr){
            if (tmp->price == price){
                if (tmp->JourneyCode == JourneyCode){
                    node = tmp;
                }
                tmp = tmp-> left;
            }
            else if (tmp->price > price){
                tmp = tmp->left;
            }
            else{
                tmp = tmp->right;
            }
        }
        if (node == nullptr){ // if no 'node' found, the ticket is not present
            return false;
        }
        TreeNode *parent = node->parent;
        if (node->left == nullptr && node->right == nullptr){ // zero childs
            if (parent->left == node) parent->left = nullptr;
            else parent->right = nullptr;
        }
        else if (node->left != nullptr && node->right == nullptr){ // one child
            if (parent->left == node) parent->left = node->left;
            else parent->right = node->left;
        }
        else if (node->left == nullptr && node->right != nullptr){ // one child
            if (parent->left == node) parent->left = node->right;
            else parent->right = node->right;
        }
        else{                   // two childs
            TreeNode *tmp1 = node->left;
            TreeNode *pred = nullptr; // finding the predecessor
            while (tmp1 != nullptr){
                pred = tmp1;
                tmp1 = tmp1->right;
            }
            if (pred == node->left){ // a separate check to improve the function
                TreeNode *pred_child = pred->left;
                node->JourneyCode = pred->JourneyCode;
                node->price = pred->price;
                node->left = pred_child;
                if (pred_child != nullptr){
                    pred_child->parent = node;
                }
            }
            else{                           // swapping the root and the predecessor
                TreeNode *pred_parent =pred->parent;
                pred_parent->right = pred->left;
                if (parent->left == node){
                    parent->left = pred;
                    pred->left = node->left;
                    pred->right = node->right;
                }
                else{
                    parent->right = pred;
                    pred->left = node->left;
                    pred->right = node->right;
                }
            }
        }
    }
    return true;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal){
    t_traverse(root, typeOfTraversal); // calling another function
    return;
}

// This is an extra function created by me to make the 'traverse' function work as desired

void BST::t_traverse(TreeNode *start, int typeOfTraversal){ // the implementation of this function is pretty straightforward
    TreeNode *tmp = start;
    if (tmp == nullptr) return; // the 'null-tree' case
    if (typeOfTraversal == PRE_ORDER){
        cout << tmp->JourneyCode << endl;
        t_traverse(tmp->left, typeOfTraversal);
        t_traverse(tmp->right, typeOfTraversal);
    }
    else if (typeOfTraversal == IN_ORDER){
        t_traverse(tmp->left, typeOfTraversal);
        cout << tmp->JourneyCode << endl;
        t_traverse(tmp->right, typeOfTraversal);
    }
    else if (typeOfTraversal == POST_ORDER){
        t_traverse(tmp->left, typeOfTraversal);
        t_traverse(tmp->right, typeOfTraversal);
        cout << tmp->JourneyCode << endl;
    }
    return;
}

// Returns the price of the cheapest journey
int BST::getMinimum(){
    TreeNode *tmp = root;
    if (tmp == nullptr){ // the 'null-tree' case
        return 0;
    }
    TreeNode *parent = nullptr;
    while (tmp != nullptr){
        parent = tmp;
        tmp = tmp->left; // just keep going left until you encounter a null pointer
    }
    return parent->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound){
    TreeNode *tmp = root;
    if (tmp == nullptr){ // the 'null-tree' case
        return 0;
    }
    TreeNode *parent = nullptr;
    while (tmp != nullptr){ // first, I go to the earliest node which lies inside the range and then count the number of nodes following it
        if (tmp->price > upperPriceBound){
            parent = tmp;
            tmp = tmp->left;
        }
        else if (tmp->price < lowerPriceBound){
            parent = tmp;
            tmp = tmp->right;
        }
        else{
            parent = tmp;
            break;
        }
    }
    return countJourneys(parent, lowerPriceBound, upperPriceBound); // 'parent' is the earliest node which lies inside the range
}

// This is an extra function created by me to make the 'countJourneysInPriceBound' function work as desired

int BST::countJourneys(TreeNode *start, int lowerPriceBound, int upperPriceBound){
    int count = 0;      // here, I count the number of nodes
    TreeNode *tmp = start;
    if (tmp != nullptr){
        if (tmp->price >= lowerPriceBound && tmp->price <= upperPriceBound){ // if inside range, increase count
            count += 1;
        }
        if (tmp->left != nullptr){
            if (tmp->left->price < lowerPriceBound){ // an extra check to improve efficiency
                count += countJourneys(tmp->left->right, lowerPriceBound, upperPriceBound);
            }
            else{
                count += countJourneys(tmp->left, lowerPriceBound, upperPriceBound); // the recursive calls
            }
        }
        if (tmp->right != nullptr){
            if (tmp->right->price > upperPriceBound){ // an extra check to improve efficiency
                count += countJourneys(tmp->right->left, lowerPriceBound, upperPriceBound);
            }
            else{
                count += countJourneys(tmp->right, lowerPriceBound, upperPriceBound); // the recursive calls
            }
        }
    }
    return count;
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename){
    ofstream f;
    f.open(filename);
    string v = store(root); // calling another function which returns a string and then just writing it to 'filename'
    for(int i=0;i<v.size();i++){
        f << v[i];
    }
    f.close();
}

// This is an extra function created by me
string BST::store(TreeNode *start){
    string s;
    TreeNode *tmp = start;
    if (tmp != nullptr){        // the price and the code is wrote in separate lines for each node, two sentinel characters 'L' and 'R' is used to specify the left and right subtree
        s += to_string(tmp->price) + "\n";
        s += to_string(tmp->JourneyCode) + "\n";
        s += "L\n";
        s += store(tmp->left);
        s += "R\n";
        s += store(tmp->right);
    }
    return s;
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
 
void BST::customLoad (int flag, string filename){
    if (flag == LOAD_FULL_BST){
        TreeNode *tmp;
        TreeNode *parent = nullptr;
        ifstream f;
        f.open(filename);
        vector<TreeNode *> v; // this vector improves efficiency a lot
        string s;
        // the following 5 variables are very crucial to the implementation
        int found = 0;
        int count = 0;
        int price = 0;
        int code = 0;
        bool dir;
        while (getline (f, s)){
            if (isdigit(s[0])){ // if the first char is a digit, then it has to be either price or code
                found = 1;
                if (count == 0){
                    price = stoi(s); // reading price
                    count = 1;
                }
                else{
                    code = stoi(s); // reading code
                    count = 0;
                }
            }
            if (count == 0 && found == 1){ // creating the node once I get the price, code and parent
                if (parent != nullptr){ // the 'non-root' case
                    if (dir){
                        parent->left = new TreeNode();
                        tmp = parent->left;
                    }
                    else{
                        parent->right = new TreeNode();
                        tmp = parent->right;
                    }
                }
                else{ // the 'root' case
                    root = new TreeNode(code, price, nullptr, nullptr, parent);
                    tmp = root;
                }
                tmp->JourneyCode = code;
                tmp->price = price;
                tmp->left = nullptr;
                tmp->right = nullptr;
                tmp->parent = parent;
                found = 0;
            }
            if (s == "L"){
                v.push_back(tmp); // store the pointer whenever "L" is found
                parent = tmp;
                dir = true;
            }
            else if (s == "R"){
                tmp = v[v.size() - 1]; // retrieve the topmost pointer and then pop it whenever "R" is found, this improves efficiency a lot
                v.pop_back();
                parent = tmp;
                dir = false;
            }
        }
        f.close();
    }
    else if (flag == LOAD_LEFT_SUBTREE){ // the implementation is almost same except for a few changes in line 463 and 472
        TreeNode *tmp;
        TreeNode *parent = nullptr;
        ifstream f;
        f.open(filename);
        vector<TreeNode *> v;
        string s;
        int found = 0;
        int count = 0;
        int price = 0;
        int code = 0;
        bool dir;
        while (getline (f, s)){
            if (isdigit(s[0])){
                found = 1;
                if (count == 0){
                    price = stoi(s);
                    count = 1;
                }
                else{
                    code = stoi(s);
                    count = 0;
                }
            }
            if (count == 0 && found == 1){
                if (parent != nullptr){
                    if (dir){
                        parent->left = new TreeNode();
                        tmp = parent->left;
                    }
                    else{
                        parent->right = new TreeNode();
                        tmp = parent->right;
                    }
                }
                else{
                    root = new TreeNode();
                    tmp = root;
                }
                tmp->JourneyCode = code;
                tmp->price = price;
                tmp->left = nullptr;
                tmp->right = nullptr;
                tmp->parent = parent;
                found = 0;
            }
            if (s == "L"){
                v.push_back(tmp);
                parent = tmp;
                dir = true;
            }
            else if (s == "R"){
                if (v.size() == 1){ // no need to retrieve the right branch of 'root'
                    break;
                }
                tmp = v[v.size() - 1];
                v.pop_back();
                parent = tmp;
                dir = false;
            }
        }
        if (root != nullptr){ // just change 'root' to 'root->left'
            if (root->left == nullptr){
                root = nullptr;
            }
            else{
                root = root->left;
                root->parent = nullptr;
            }
        }
        f.close();
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
