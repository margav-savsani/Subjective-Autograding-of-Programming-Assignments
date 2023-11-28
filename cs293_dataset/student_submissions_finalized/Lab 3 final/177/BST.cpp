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

BST::BST(){ root = new TreeNode; root -> parent = nullptr;}
BST::BST(TreeNode *r){ root = r; root -> parent = nullptr;}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JC_to_find, int price_to_find) { 
    if (root -> JourneyCode == 0) {root -> JourneyCode = JC_to_find; root -> price = price_to_find; return true;} // Only when starting element is added

    TreeNode* newnode = new TreeNode(JC_to_find,price_to_find);
    TreeNode* nodeptr = root;

    while (nodeptr -> JourneyCode != JC_to_find){
        if (nodeptr -> price > price_to_find){
            if (nodeptr -> left == nullptr) {
                newnode -> parent = nodeptr;
                nodeptr -> left = newnode;
                return true;
            }
            else nodeptr = nodeptr -> left;
        }
        else {
            if (nodeptr -> right == nullptr){
                newnode -> parent = nodeptr;
                nodeptr -> right = newnode;
                return true;
            }
            else nodeptr = nodeptr -> right;
        }
    }
    return false;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JC_to_find, int price_to_find) { 
    TreeNode* nodeptr = root;

    while (nodeptr != nullptr){
        if (nodeptr -> price == price_to_find){
            if (nodeptr -> JourneyCode == JC_to_find) return true;
            else nodeptr = nodeptr -> right;
        }
        else {
            if (nodeptr -> price > price_to_find) nodeptr = nodeptr -> left;
            else nodeptr = nodeptr -> right;
        }
    }
    return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JC_to_find, int price_to_find) { // This working of remove is unstable and unpolished. As of now, only leaves can be successfully removed. Other code needs correction.
    TreeNode* nodeptr = root;

    // This loop is designed to reach the node to be deleted
    while (nodeptr != nullptr){
        if (nodeptr -> price == price_to_find){
            if (nodeptr -> JourneyCode == JC_to_find) break;
            else nodeptr = nodeptr -> right;
        }
        else {
            if (nodeptr -> price > price_to_find) nodeptr = nodeptr -> left;
            else nodeptr = nodeptr -> right;
        }
    }

    if (nodeptr == nullptr) return false;
    else{
        TreeNode* parentptr = nodeptr -> parent;
        TreeNode* node_to_delete = nodeptr;

        if ((node_to_delete -> left == nullptr) && (node_to_delete -> right == nullptr)){
            if (parentptr -> left == node_to_delete) parentptr -> left = nullptr;
            else parentptr -> right = nullptr;
            return true;
        }
        else {
            if ((node_to_delete -> left == nullptr) || (node_to_delete -> right == nullptr)){
                if (node_to_delete -> left == nullptr){
                    if (parentptr -> left == node_to_delete) {parentptr -> left = node_to_delete -> right; node_to_delete -> right -> parent = parentptr;}
                    else {parentptr -> right = node_to_delete -> right; node_to_delete -> right -> parent = parentptr;}
                    return true;
                }
                if (node_to_delete -> right == nullptr){
                    if (parentptr -> left == node_to_delete) {parentptr -> left = node_to_delete -> left; node_to_delete -> left -> parent = parentptr;}
                    else {parentptr -> right = node_to_delete -> left; node_to_delete -> left -> parent = parentptr;}
                    return true;
                }
            }
            else{
                TreeNode* probe = node_to_delete -> right;
                while (probe -> left != nullptr) probe = probe -> left;
                node_to_delete -> price = probe -> price; node_to_delete -> JourneyCode = probe -> JourneyCode;
                TreeNode* probe_parent_ptr = probe -> parent;
                if (probe_parent_ptr -> left == probe) probe_parent_ptr -> left = nullptr;
                else probe_parent_ptr -> right = nullptr;
                return true;
            }
        }
    }
    return false; 
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {

    // PreOrder Traversal
    if (typeOfTraversal == 0){
        if (root == nullptr) return;

        TreeNode* nodeptr = root;

        std::cout << root -> JourneyCode << std::endl;
        if (nodeptr -> left != nullptr) {BST* left_sub_tree = new BST(root -> left); left_sub_tree -> traverse(0);}
        if (nodeptr -> right != nullptr) {BST* right_sub_tree = new BST(root -> right); right_sub_tree -> traverse(0);}
    }

    // PostOrder Traversal
    if (typeOfTraversal == 1){
        if (root == nullptr) return;

        TreeNode* nodeptr = root;

        if (nodeptr -> left != nullptr) {BST* left_sub_tree = new BST(root -> left); left_sub_tree -> traverse(1);}
        if (nodeptr -> right != nullptr) {BST* right_sub_tree = new BST(root -> right); right_sub_tree -> traverse(1);}
        std::cout << root -> JourneyCode << std::endl;
    }

    // InOrder Traversal
    if (typeOfTraversal == 2){
        if (root == nullptr) return;

        TreeNode* nodeptr = root;

        if (nodeptr -> left != nullptr) {BST* left_sub_tree = new BST(root -> left); left_sub_tree -> traverse(2);}
        std::cout << root -> JourneyCode << std::endl;
        if (nodeptr -> right != nullptr) {BST* right_sub_tree = new BST(root -> right); right_sub_tree -> traverse(2);}
        
    }
    return; }

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode* nodeptr = root;
    while (nodeptr -> left != nullptr) nodeptr = nodeptr -> left;
    return nodeptr -> price; 
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.

// This function basically copies the in order traversal of a tree into a vector
void internal_journey_in_order(TreeNode* nodeptr, vector<StorageUnit>& in_order) {
    if (nodeptr == nullptr) return;
    else{
        StorageUnit s(nodeptr -> JourneyCode, nodeptr -> price);

        internal_journey_in_order(nodeptr -> left, in_order);
        in_order.push_back(s);
        internal_journey_in_order(nodeptr -> right, in_order);
    }    
}

int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    vector<StorageUnit> in_order_list;
    internal_journey_in_order(root, in_order_list);

    int count = 0;
    
    auto i = in_order_list.begin();
    while (i -> price < lowerPriceBound) i++;
    while ((i -> price <= upperPriceBound) && (i != in_order_list.end())) {count++; i++;}

    return count;
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.

// Similar to a function above, this one copies pre order traversal
void internal_journey_pre_order(TreeNode* nodeptr, vector<StorageUnit>& pre_order) {
    if (nodeptr == nullptr) return;
    else{
        StorageUnit s(nodeptr -> JourneyCode, nodeptr -> price);

        pre_order.push_back(s);
        internal_journey_pre_order(nodeptr -> left, pre_order);
        internal_journey_pre_order(nodeptr -> right, pre_order);
    }     
}

void BST::customStore(string filename) {

    vector<StorageUnit> pre_order_list;
    internal_journey_pre_order(root, pre_order_list);
    int count = pre_order_list.size();

    ofstream file_transfer;
    file_transfer.open(filename);

    file_transfer << count << endl;
    file_transfer << "PRE ORDER BEGINS" << endl;

    for (auto i = pre_order_list.begin(); i != pre_order_list.end(); i++) file_transfer << i -> JourneyCode << endl << i -> price << endl;

    file_transfer << "PRE ORDER ENDS" << endl;

    file_transfer.close();
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
    ifstream transfer_from_file;
    transfer_from_file.open(filename); 

    int count;
    string tmp;
    transfer_from_file >> tmp;
    count = stoi(tmp);
    transfer_from_file >> tmp; // Just holds a garbage string now

    if (flag == 3){
        Stack store(count);

        int root_jc = 0;
        int root_pr = 0;
        transfer_from_file >> root_jc;
        transfer_from_file >> root_pr;

        root -> JourneyCode = root_jc; root -> price = root_pr;
        store.push(root);
        TreeNode* temp;

        for (int i = 1; i < count; i++){

            temp = nullptr;

            int tmp_jc = 0;
            int tmp_pr = 0;
            transfer_from_file >> tmp_jc;
            transfer_from_file >> tmp_pr;
            TreeNode* to_add = new TreeNode(tmp_jc,tmp_pr);

            while (!(store.isEmpty()) && (tmp_pr > store.top() -> price)) temp = store.pop();

            if (temp != nullptr){
                temp -> right = to_add;
                to_add -> parent = temp;
                store.push(temp -> right);
            }

            else{
                store.top() -> left = to_add;
                to_add -> parent = store.top();
                store.push(store.top() -> left);
            }
        }

        transfer_from_file.close(); 
    }   
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

