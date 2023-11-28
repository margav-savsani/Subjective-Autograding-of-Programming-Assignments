#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

#include "tree.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4

// if node is uninitialised, its price and Journey code are set to 0 by default constructor. 
// I will check nullptr

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Memory : Each node insertion has memory already present for the root and alllocates memory for its immediate chilren. 
// root is also a nullptr in the beginning. ONLY insertion can allocate memory. 

int ARR_SIZE = 100;

BST::BST(){
    // everything set to default values. -- length will not be a part of root here (nullptr should make it obvious)
    root = nullptr; 
    root = nullptr; 
}

// this constructor is NOT used to allot memory. Segfault : Modified to allocation as well. It is only used for subtraversals. 
// memory allocation happens only in construction of BST and insertion

BST::BST(TreeNode *root, TreeNode* p/*=nullptr*/){
    // root already contains information of linking before insertion. 
    // hence, only set the root as root of BST
    root->shortestPathLength = root->longestPathLength = 1;
    this->root = root;
    if (p!=nullptr) this->p=p;
}

int BST::getImbalance()
{
  if (root == nullptr) return 0;
  else return root->getImbalance();
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise


// Given : the prices are unique. Hence, we can simply count the number of elements in the vector prices. from one point to another. 

//                      **** HELPER FUNCTIONS FOR PART - II ****

template< typename T >
typename std::vector<T>::iterator 
   insert_sorted( std::vector<T> & vec, T const& item )
{
    return vec.insert
        ( 
            std::upper_bound( vec.begin(), vec.end(), item ),
            item 
        );
}

// returns index of closest element >= the input value
int closest(std::vector<int> const& vec, int value) {
    auto const it = std::lower_bound(vec.begin(), vec.end(), value);
    if (it == vec.end()) { return -1; }

    return distance(vec.begin(), it);
}

//                  **** END OF HELPER FUNCTIONS FOR PART- II ******

bool BST::insert(int JourneyCode, int price, TreeNode* p/*=nullptr*/) { 
    // assumption : if price is equal, element is included in the right subtree.
    // if the child is NULL , established parent, inserts in the null node. returns true
    // establishment of parent is done while insertion itself. 

    // base case i.e. first node. 
    // root has space allocated already, and knows that its parent is nullptr during construction itself.
    // if segfault, try *root = TreeNode(JourneyCode, price)
    // root can be nullptr if previously deleted. 
    
    // update path lengths here
   
    // base case.
    if (root == nullptr){
        root = new TreeNode(JourneyCode, price, nullptr, nullptr, p);
        // root->updatepaths(1);
        // putting path length in root 
        root->shortestPathLength = root->longestPathLength = 1;
        // updating other path lengths
        
        // increasing it for all parents. 
        if (p!=nullptr){
            if (root->JourneyCode < p->JourneyCode){
                p->left = root;
            }
            else{
                p->right=root;
            }

        return true;
        }
    }
    if ((JourneyCode == root->JourneyCode) && (price == root->price)){
        return false;
    }

    // if root is not nullptr, it will check its children beforehand, hence, no issues of wrong insertions. 

    if (JourneyCode < root->JourneyCode){
        
        // if the left child is NULL, insert this as the left child, else insert recursively

        // left subtree constructor assuming that the root of left subtree has some value stored. (i.e. leftptr is not nullptr)
        // if not, the insert function should insert there itself 

        if (root->left == nullptr) {
            root->left = new TreeNode(JourneyCode, price, nullptr, nullptr, root);
            root->left->shortestPathLength = root->left->longestPathLength = 1;
            root->left->updatepaths();
            return true;
        }
        else {

            // left is not null hence left child has memory allocated. 

            BST leftchild(root->left);
            return leftchild.insert(JourneyCode, price);
        }
    }

    else if (JourneyCode >= root->JourneyCode){

        // if the right child is NULL, insert this as the right child, else insert recursively

        if (root->right == nullptr) {
            // this node is given information about parent during insertion. 
            root->right = new TreeNode(JourneyCode, price, nullptr, nullptr, root);
            root->right->shortestPathLength = root->right->longestPathLength = 1;
            root->right->updatepaths();
            return true;
        }
        else {
            BST rightchild(root->right);
            return rightchild.insert(JourneyCode, price);
        }
    }

}

// from this point onwards memory has been allocated, so no issue will arise regarding segfaults.


// Return True, if the ticket with given attributes is found, false otherwise

// FINDS the element 
bool BST::find(int JourneyCode, int price) { 
    
    // base case -- checking inside the root itself
    if (root == nullptr){

        // check in predecessor -- no need (we start by calling root of the tree.)
        return false;
    }
    
    if (root->JourneyCode == 0){
        return false;
    }
    
    
    // this is the root of some subtree. Which has some non-trivial value.
    if ((root->JourneyCode == JourneyCode) && (root->price == price)){
        return true;
    }  
    
    // if root is the "actual" node, it being set to nullptr.
    // can cause excess use of memory, however inlab so will optimise later. 

    
    // checking in the corresponding children depending upon the price. 
    if (JourneyCode < root->JourneyCode){

        // first check for null pointer. 
        if (root->left == nullptr) {
            return false;
        }
        else {
            BST leftchild(root->left);
            return leftchild.find(JourneyCode, price);
        }
    }
    
    else if (JourneyCode >= root->JourneyCode){
        if (root->right == nullptr) {
            return false;

        }
        else {
            BST leftchild(root->right);
            bool result = leftchild.find(JourneyCode, price);
            return result;
        }
    }

}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
// to be used ONLY for pointers inside the tree. 
bool BST::remove(TreeNode* input) {
    
    if (input == nullptr) {return false;}
    // LEAF NODE
    if ((input->left == nullptr) && (input->right == nullptr)){
        // memory allocation to this node will again happen during insertion, so we can safely set this to nullptr
        // it has no need of remembering its parent. 
        // parent of the root points to its child's memory, changing value of child has no effect on that.  
        
        // if the parent about to become the root node, the tree needs to know that. 
        
        // base case : this is the root of the tree

        

        if (input->parent == nullptr) {
            input = nullptr;
        }

        else if ((input->parent)->left == input) {
            (input->parent)->left = nullptr;
            
        }
        else {
            (input->parent)->right = nullptr;
        }
        return true;
    }
    
    // ONE CHILD EXISTS ONLY
    else if ((input->left == nullptr) && (input->right != nullptr)) {
        
        // now we replace root with right memory. Memory allocation has been done for the node since it ain't null. 
        (input->right)->parent = input->parent;
        
        if ((input->parent)->right == input)
            (input->parent)->right = input->right;
        else 
            (input->parent)->left = input->right;
        return true;
    }

    else if ((input->right == nullptr) && (input->left != nullptr)) {

        // now we replace root with left memory. 
        (input->left)->parent = input->parent;
        
        if ((input->parent)->right == input)
            (input->parent)->right = input->left;
        else 
            (input->parent)->left = input->left;
        
        return true;
        
    }

}

// DELETION IS NOT THAT EASY
bool BST::remove(int JourneyCode, int price) { 
    
    // base case -- checking inside the root itself
    // sets the node to NULL upon deletion and the parent is a pointer so no need to update it.

    if (root == nullptr){
        return false;
    }

    // FOUND
    if ((root->JourneyCode == JourneyCode) && (root->price == price)){
        
        
        // now that the node is found, let us focus upon deleting it. 
        
        // LEAF NODE
        if ((root->left == nullptr) && (root->right == nullptr)){
            // memory allocation to this node will again happen during insertion, so we can safely set this to nullptr
            // it has no need of remembering its parent. 
            // parent of the root points to its child's memory, changing value of child has no effect on that.  
            
            // if the parent about to become the root node, the tree needs to know that. 
            
            // base case : this is the root of the tree

            

            if (root->parent == nullptr) {
                root = nullptr;
                
            }
            // only deletion of leaf node and one child case causes this. 
            else if ((root->parent)->left == root) {
                root->parent->updatepaths();
                (root->parent)->left = nullptr;
            }
            else {
                root->parent->updatepaths();
                (root->parent)->right = nullptr;
            }
            return true;
        }
        
        // ONE CHILD EXISTS ONLY
        else if ((root->left == nullptr) && (root->right != nullptr)) {
            int path = root->shortestPathLength;
            // patching child 
            (root->right)->parent = root->parent;
            
            // patching parent
            if (root->parent == nullptr) {
                this->root = root->right;
            }
            else if ((root->parent)->left == root) 
                (root->parent)->left = root->right;
            else 
                (root->parent)->right = root->right;

            root->parent->updatepaths(path);
            return true;
        }

        else if ((root->right == nullptr) && (root->left != nullptr)) {
            int path = root->shortestPathLength;
            // patching child
            (root->left)->parent = root->parent;
            
            // patching parent
            if (root->parent == nullptr){
                this->root = root->left;
            }
            else if ((root->parent)->left == root) 
                (root->parent)->left = root->left;
            else 
                (root->parent)->right = root->left;

            root->parent->updatepaths(path);
            return true;
            
        }

        // neither of the nodes is null. 

        else {
            // find the node in the tree which is the predecessor. 
            // successor node is then deleted as well. 
            if (root->right != nullptr) {
                BST rightchild(root->right);
                TreeNode* result = new TreeNode();
                result = rightchild.getMin();
                int jc = result->JourneyCode, prc = result->price;
                //removes node from the tree (it still ingers in memory), and then substitutes it.
                bool success = rightchild.remove(result); // modifies root as well. 
                

                // patching everything up

                TreeNode* old_root = new TreeNode();
                old_root = root;

                root = new TreeNode(jc, prc, old_root->left, old_root->right, old_root->parent);
                
                // patching child
                if (old_root->right != nullptr)
                    (old_root->right)->parent = root;

                if (old_root->left != nullptr)
                    (old_root->left)->parent = root;
                
                // patching parent
                if (old_root->parent == nullptr) {
                    // the new node as root has already been set.
                }
                else if ((old_root->parent)->left == old_root)
                    (old_root->parent)->left = root;
                else 
                    (old_root->parent)->right = root;
                
                return success;

            }

        }
    }  
    
    
    // FINDING
    // checking in the corresponding children depending upon the price. 
    if (JourneyCode < root->JourneyCode){

        // checking if the left subtree is there. 
        if (root->left == nullptr){
            return false;
        }
        else{
            BST leftchild(root->left);
            return leftchild.remove(JourneyCode, price);
        }
    }
    else if (JourneyCode >= root->JourneyCode){

        // checking if the right subtree is there
        if (root->right == nullptr){
           
            return false;
        }
        else{
            BST rightchild(root->right);
            
            return rightchild.remove(JourneyCode, price);
        }
    }
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    // traverses the tree and prints the journey codes corresponding to the traversal. 
    
    BST leftchild(root->left);
    BST rightchild(root->right);
    
    // base case
    if (root == nullptr) {return;}

    // PRE_ORDER case
    if (typeOfTraversal == PRE_ORDER){
        std::cout << root->JourneyCode << endl;
        if (root->left != nullptr)
            leftchild.traverse(typeOfTraversal);
        if (root->right != nullptr)
            rightchild.traverse(typeOfTraversal);
    }

    // IN_ORDER case
    else if (typeOfTraversal == IN_ORDER) {
        if (root->left != nullptr)
            leftchild.traverse(typeOfTraversal);
        std::cout << root->JourneyCode << endl;
        
        if (root->right != nullptr)
            rightchild.traverse(typeOfTraversal);
    }

    // POST_ORDER case
    else if (typeOfTraversal == POST_ORDER) {
        if (root->left != nullptr)
            leftchild.traverse(typeOfTraversal);
        if (root->right != nullptr)
            rightchild.traverse(typeOfTraversal);
        std::cout << root->JourneyCode << endl;
    }

    return;
    
}


// Returns the price of the cheapest journey
int BST::getMinimum() {
    

    // if the tree is empty 0 is returned
    // base cases : assumption -- the price is positive
    if (root == nullptr){
        return 0;
    }
    
    // if the root does not have a left child then return the node's price, else, return the price of leftchild.
    if (root->left == nullptr){
        return root->JourneyCode;
    }
    else {
        BST leftchild(root->left);
        return leftchild.getMinimum();
    }
}

TreeNode* BST::getMin() {
    // if the tree is empty 0 is returned
    // base cases : assumption -- the price is positive
    if (root == nullptr){
        return nullptr;
    }
    
    // if the root does not have a left child then return the node's price, else, return the price of leftchild.
    if (root->left == nullptr){
        return root;
    }
    else {
        BST leftchild(root->left);
        return leftchild.getMin();
    }
}

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
