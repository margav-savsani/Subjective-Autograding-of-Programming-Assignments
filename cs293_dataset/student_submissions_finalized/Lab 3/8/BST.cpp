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
int noOfChildren(TreeNode* node) {
    if (node->left == nullptr && node->right == nullptr) return 0;
    else if (node->left != nullptr && node->right == nullptr) return 1;
    else if (node->left == nullptr && node->right != nullptr) return 1;
    else if (node->left != nullptr && node->right != nullptr) return 2;
}

TreeNode *treeMin(TreeNode* rootNode) {
    TreeNode * ptr = rootNode;
    while (ptr -> left != nullptr)
    {
        ptr = ptr -> left;
    }
    
    return ptr;
}

TreeNode* successor(TreeNode* node) {
    TreeNode* ptr1 = node;
    TreeNode* ptr2 = ptr1 -> parent;
    if (node -> right != nullptr)
    {
        return node -> right;   
    }

    else {
        while (!(ptr2 -> left == ptr1))
        {
            if(ptr2 == nullptr) break;
            ptr1 = ptr2;
            ptr2 = ptr2 -> parent;
        }
        
        if (ptr2 != nullptr)
        {
            return ptr2;
        }

        return nullptr;
        
    }
    
}

void joinNodes(TreeNode* parent, TreeNode* child, bool left = true){
    if(left == true){
        parent -> left = child;
        child -> parent = parent;
    }    

    else {
        parent -> right = child;
        child -> parent = parent;
    }
}

bool isLeft(TreeNode* parent, TreeNode* child) {
    if (parent -> left == child)
    {
        return true;
    }

    else if (parent -> right == child)
    {
        return false;
    }
    return false; 
}

BST::BST(){
    root = nullptr;    
}
BST::BST(TreeNode *root){
    this->root = root;
 }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
    TreeNode *ptr = root;
    TreeNode *ptr2 = nullptr;
    
    //cout << "inserting" << endl;
    while (ptr != nullptr)
    {
        //cout << "stuck" << endl;
       if (ptr -> price > price)
       {
            ptr2 = ptr;
            ptr  = ptr -> left;
       }

       else if (ptr -> price == price && ptr -> JourneyCode == JourneyCode)
       {
        return false;
       }
       

       else
       {
            ptr2 = ptr;
            ptr = ptr -> right;
       }
    }

    TreeNode *node = new TreeNode(JourneyCode,price);
    //if tree do not ahs a node
    if (ptr2 == nullptr)
    {
        root = node;
    }
    
    // if node was there before
    else if(ptr2 -> price > price) {
        ptr2 -> left = node;
        node -> parent = ptr2;
    }

    else
    {
        ptr2 -> right = node;
        node -> parent = ptr2;
    }

    return true;
}

//void BST::printTree() {
    //TreeNode* ptr = root
    //while (/* condition */)
    //{
        ///* code */
    //}
    
//}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    TreeNode *ptr = root;
    while (ptr != nullptr)
    {
       if (ptr -> price == price && ptr -> JourneyCode == JourneyCode)
       {
        return true;
       }

       else if (ptr -> price > price)
       {
            ptr  = ptr -> left;
       }

       

       else
       {
            ptr = ptr -> right;
       }
    
        
    }
    
    return false;
}

TreeNode* BST::findNode(int JourneyCode, int price) {
    TreeNode *ptr = root;
    while (ptr != nullptr)
    {
       if (ptr -> price == price && ptr -> JourneyCode == JourneyCode)
       {
        return ptr;
       }

       else if (ptr -> price > price)
       {
            ptr  = ptr -> left;
       }

       

       else
       {
            ptr = ptr -> right;
       }
    }

   // return nullptr;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    TreeNode* node = findNode(JourneyCode,price);

    if (!find(JourneyCode,price))
    {
        return false;   
    }

    else if (noOfChildren(node) == 0)
    {
        TreeNode* parent = node->parent;
        if (parent -> left == node)
        {
            parent -> left = nullptr;
        }
        
        else {
            parent -> right = nullptr;
        }
        return true;
    }

    else if (noOfChildren(node) == 1)
    {
        TreeNode* child = node->left == nullptr ? node->right : node->left; 
        joinNodes(node->parent,child, isLeft(node->parent,node));
        return true;
        
    }
    
    else if (noOfChildren(node) == 2) {
        joinNodes(node -> parent, successor(node), isLeft(node -> parent, node));
        return true;
    }
    
    
    
    //successor(findNode(JourneyCode,price)) ->printNode();
    return false; 
}



// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {return; }

// Returns the price of the cheapest journey
int BST::getMinimum() {return 0; }

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {return 0; }

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) { return; }
	
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
 
void BST::customLoad (int flag, string filename) { return; }


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

/*

int main() {
    BST b;
    b.insert(50,50);
    b.insert(25,25);
    b.insert(75,75);

    b.insert(12,12);
    b.insert(30,30);
    b.insert(60,60);
    b.insert(85,85);
    b.insert(90,90);
    b.insert(80,80);
    b.insert(35,35);
    b.insert(28,28);
    //b.insert(333,67);

    //b.findNode(75,75) -> printNode();

    b.printBST("");
    b.remove(35,35);
    b.printBST("");
    b.remove(30,30);
    b.printBST("");


   
    //b.printBST("node");
    //TreeNode *t = new TreeNode();
    //t ->printNode();
   
    
    
    
    
}
*/