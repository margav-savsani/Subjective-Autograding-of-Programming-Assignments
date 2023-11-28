#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

// Returns true on successful insertion in BST. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the BST
/*
bool BST::insert(int jrnyCode, int price)
{
  // Implement insertion in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
  return true;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
  // Implement find in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
  return -1;
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in BST with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the BST have the same journey
// code, and journey code is the key for insertion and finding in the BST.

bool BST::remove(int jrnyCode)
{
  // Implement deletion in BST
  
  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // REMEMBER to update the height of appropriate nodes in the tree
  // after a successful deletion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.




  return true;
}
*/

/* OLD CODE BELOW THIS LINE ========================================================================================================== */

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

bool BST::insert(int JourneyCode, int price, TreeNode* p/*=nullptr*/) { 
    // assumption : if price is equal, element is included in the right subtree.
    // if the child is NULL , established parent, inserts in the null node. returns true
    // establishment of parent is done while insertion itself. 

    // base case i.e. first node. 
    // root has space allocated already, and knows that its parent is nullptr during construction itself.
    // if segfault, try *root = TreeNode(JourneyCode, price)
    // root can be nullptr if previously deleted. 
    
    

    // base case.
    if (root == nullptr){
        root = new TreeNode(JourneyCode, price, nullptr, nullptr, p);
        if (p!=nullptr){
            if (root->price < p->price){
                p->left = root;
            }
            else{
                p->right=root;
            }
        }
        insert_sorted(*prices, price);
        return true;
    }

    if ((JourneyCode == root->JourneyCode) && (price == root->price)){
        return false;
    }

    // if root is not nullptr, it will check its children beforehand, hence, no issues of wrong insertions. 

    if (price < root->price){
        
        // if the left child is NULL, insert this as the left child, else insert recursively

        // left subtree constructor assuming that the root of left subtree has some value stored. (i.e. leftptr is not nullptr)
        // if not, the insert function should insert there itself 

        if (root->left == nullptr) {
            root->left = new TreeNode(JourneyCode, price, nullptr, nullptr, root);
            insert_sorted(*prices, price);
            return true;
        }
        else {

            // left is not null hence left child has memory allocated. 

            BST leftchild(root->left, prices);
            return leftchild.insert(JourneyCode, price);
        }
    }

    else if (price >= root->price){

        // if the right child is NULL, insert this as the right child, else insert recursively

        if (root->right == nullptr) {
            // this node is given information about parent during insertion. 
            root->right = new TreeNode(JourneyCode, price, nullptr, nullptr, root);
            insert_sorted(*prices, price);
            return true;
        }
        else {
            BST rightchild(root->right, prices);
            return rightchild.insert(JourneyCode, price);
        }
    }

}

// from this point onwards memory has been allocated, so no issue will arise regarding segfaults.


// Return True, if the ticket with given attributes is found, false otherwise

// FINDS the element 
bool BST::find(int JourneyCode) { 
    
    // base case -- checking inside the root itself
    if (root == nullptr){

        // check in predecessor -- no need (we start by calling root of the tree.)
        return false;
    }
    
    if (root->JourneyCode == 0){
        return false;
    }
    
    
    // this is the root of some subtree. Which has some non-trivial value.
    if (root->JourneyCode == JourneyCode){
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
            BST leftchild(root->left, prices);
            return leftchild.find(JourneyCode);
        }
    }
    
    else if (JourneyCode >= root->JourneyCode){
        if (root->right == nullptr) {
            return false;

        }
        else {
            BST leftchild(root->right, prices);
            bool result = leftchild.find(JourneyCode);
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
bool BST::remove(int JourneyCode) { 
    
    // base case -- checking inside the root itself
    // sets the node to NULL upon deletion and the parent is a pointer so no need to update it.

    if (root == nullptr){
        return false;
    }

    // FOUND
    if (root->JourneyCode == JourneyCode){
        
        // now that the node is found, let us focus upon deleting it. 

        /* SHADY PART ======= MAY CAUSE ISSUES ======================== 

        int idx = closest(*prices, price);
        
        if ((*prices)[idx] == price){
            prices->erase(prices->begin() + idx);
        }
        */

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

            else if ((root->parent)->left == root) {
                (root->parent)->left = nullptr;
            }
            else {
                (root->parent)->right = nullptr;
            }
            return true;
        }
        
        // ONE CHILD EXISTS ONLY
        else if ((root->left == nullptr) && (root->right != nullptr)) {
            
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
            return true;
        }

        else if ((root->right == nullptr) && (root->left != nullptr)) {

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

            return true;
            
        }

        // neither of the nodes is null. 

        else {
            // find the node in the tree which is the predecessor. 
            // successor node is then deleted as well. 
            if (root->right != nullptr) {
                BST rightchild(root->right, prices);
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
            BST leftchild(root->left, prices);
            return leftchild.remove(JourneyCode);
        }
    }
    else if (JourneyCode >= root->JourneyCode){

        // checking if the right subtree is there
        if (root->right == nullptr){
           
            return false;
        }
        else{
            BST rightchild(root->right, prices);
            
            return rightchild.remove(JourneyCode);
        }
    }
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
        return root->price;
    }
    else {
        BST leftchild(root->left, prices);
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
        BST leftchild(root->left, prices);
        return leftchild.getMin();
    }
}



