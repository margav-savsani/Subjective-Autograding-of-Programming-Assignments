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
#define MISS -1

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST() {
    root = nullptr;
}
BST::BST(TreeNode *root) {
    this->root = root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
    if(find(JourneyCode, price))        // cant insert if found
        return false;
    TreeNode *new_node, *null_node, *parent;
    new_node = new TreeNode(JourneyCode, price);
    if(root == nullptr)
        root = new_node;    // inserting the first node of empty tree
    else {                  
        parent = nullptr;
        null_node = root;
        while(null_node != nullptr) {       // finding the position for new node to be inserted
            parent = null_node;
            if(price < null_node->price)
                null_node = null_node->left;
            else
                null_node = null_node->right;
        }
        if(price < parent->price)
            parent->left = new_node;
        else
            parent->right = new_node;

        new_node->parent = parent;
    }
    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    TreeNode* node = root;
    while(node != nullptr) {
        if(price == node->price && JourneyCode == node->JourneyCode)
            return true;
        else if(price < node->price)
            node = node->left;
        else
            node = node->right;
    }
    return false;
}

// Finds the element and returns the pointer to the node (if found), else
TreeNode* BST::find(int &JourneyCode, int &price, int a) {          // a is just to distinguish the signatures
    TreeNode* node = root;
    while(node != nullptr) {
        if(price == node->price && JourneyCode == node->JourneyCode)
            return node;
        else if(price < node->price)
            node = node->left;
        else
            node = node->right;
    }
    return nullptr;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise

bool BST::remove(int JourneyCode, int price) {
    TreeNode* node = new TreeNode();
    node = find(JourneyCode, price, 0);

    if(!node)       // node to be deleted not present
        return false;

    TreeNode *x,*y;
    if (node->left == nullptr || node->right == nullptr)  y = node;
    else    y = successor(node);

    if (y->left != nullptr)     x = y->left;
    else                        x = y->right;

    if (x!=nullptr)    x->parent = y->parent;

    if (y->parent == nullptr)       root = x;
    else if (y == y->parent->left)  y->parent->left = x;
    else                            y->parent->right = x;

    if (y!=node) {
        node->JourneyCode = y->JourneyCode;
        node->price = y->price;
    }

    return true;
}

// finds the successor of a node
TreeNode* BST::successor(TreeNode* node) {
    TreeNode* suc = node;
    if (node->right != nullptr) {
        suc = suc->right;
        while (suc->left != nullptr) 
        suc = suc->left;
        return suc;
    }
    else {
        suc = node->parent;
        while (suc!=nullptr && node==suc->right) {
            node = suc;
            suc = suc->parent;
        }
        return suc;
    }
}
// finds the predecessor of a node
TreeNode* BST::predecessor(TreeNode* node) {
    TreeNode* pre = node;
    if (node->left != nullptr) {
        pre = pre->left;
        while (pre->right != nullptr) 
            pre = pre->right;
        return pre;
    }
    else {
        pre = node->parent;
        while (pre!=nullptr && node==pre->left) {
            node = pre;
            pre = pre->parent;
        }
        return pre;
    }
}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    TreeNode* node = root;
    if(typeOfTraversal == 0)
        preorder(node);
    else if(typeOfTraversal == 1)
        postorder(node);
    else if(typeOfTraversal == 2)
        inorder(node);
    else
        cout <<"ERROR\n";
    return;
}

void BST::inorder(TreeNode* node) {
    if(node == nullptr)
        return;
    inorder(node->left);
    cout << node->JourneyCode << endl;
    inorder(node->right);
    return;
}

void BST::postorder(TreeNode* node) {
    if(node == nullptr)
        return;
    postorder(node->left);
    postorder(node->right);
    cout << node->JourneyCode << endl;
    return;
}
void BST::preorder(TreeNode* node) {
    if(node == nullptr)
        return;
    cout << node->JourneyCode << endl;
    preorder(node->left);
    preorder(node->right);
    return;
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode* node = root;
    while(node->left != nullptr)        // cheapest journey is the leftmost element from the root
        node = node->left;
    return node->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.

int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    int count=0;
    count += inordercount(lowerPriceBound, upperPriceBound, root);
    return count;
}

// returns the count in bound, by traversing in-order of the tree
int BST::inordercount(int &low, int &upp, TreeNode* node) {
    int count = 0;
    if(node == nullptr)
        return 0;
    if (node->price > low)                      count += inordercount(low, upp, node->left);
    if (node->price >=low && node->price <=upp) count++;
    if (node->price <= upp)                     count += inordercount(low, upp, node->right);
    return count;
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.

void BST::customStore(string filename) {
    ofstream out(filename);
    uploading(root, out);
    out.close();
    return;
}

// storing the tree as a Code - Price pair in the file
void BST::uploading(TreeNode* node, ofstream &out) {
    if(node == NULL) {
        out << "-1\n";          // a sentinel character to mark the end of any subtree path
        return;
    }
    out << node->JourneyCode << " "<< node->price << "\n";
    uploading(node->left, out);                                 // storing in pre order format
    uploading(node->right, out);
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
    ifstream in(filename);
    int JourneyCode, price;
    in >> JourneyCode;
    if(JourneyCode == -1)   // no root present
        return;

    in >> price;
    if(flag == 4) {             // the first element, i.e.,  the root is not to be considerd in LEFT_SUBTREE
        in >> JourneyCode;
        if(JourneyCode == -1)   // no left subtree present
            return;
        in>>price;
    }
    root = new TreeNode(JourneyCode, price);    // building tree pre orderly
    root->left = add_on(in, root);
    root->right = add_on(in, root);
    return;
}

// adds a new node to the tree, at the parent node passed
TreeNode* BST::add_on(ifstream &in, TreeNode* parent) {
    int JourneyCode, price;
    in >> JourneyCode;
    if (JourneyCode == -1)      // no node present to add
        return nullptr;
    in >> price;
    TreeNode* node = new TreeNode(JourneyCode,price,nullptr,nullptr,parent);
    node->left = add_on(in, node);
    node->right = add_on(in, node);
    return node;
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
