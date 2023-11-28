#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4

void preorder(TreeNode *root)
{
    if (root == nullptr)
        return;
    cout << root->JourneyCode << endl;
    preorder(root->left);
    preorder(root->right);
}
void inorder(TreeNode *root)
{
    if (root == nullptr)
        return;
    inorder(root->left);
    cout << root->JourneyCode << endl;
    inorder(root->right);
}
void postorder(TreeNode *root)
{
    if (root == nullptr)
        return;
    postorder(root->left);
    postorder(root->right);
    cout << root->JourneyCode << endl;
}

int bound(TreeNode *root ,int lower , int upper) { 
    if (root == nullptr) return 0 ; 
    if ( root->price > upper )  return bound(root->left , lower, upper) ;
    if ( root->price < lower )  return bound(root->right , lower, upper) ;
    return 1+bound(root->left , lower, upper) + bound(root->right , lower, upper) ;
}

void store(ofstream& file , TreeNode* root) { 
      if (root == nullptr)  file<<". ."<<endl  ;
      else { 
            file<<(root->JourneyCode)<<" "<< (root->price)<<endl ;
            store(file , root->left) ;  
            store(file , root->right) ;  
      } 
} 

void load(ifstream& file , TreeNode* child , TreeNode* parent ,int flag , TreeNode* root ) { 
      string x , y ; 
      if (!file.eof()) {
        file>>x>>y  ;
        if ( x == "" ) return ; 
        if ( x == "."  )  { 
           if (parent->left == child) parent->left = nullptr ; 
           else parent->right = nullptr ; 
           delete child ; 
        } 
        else { 
             int journey = stoi(x) ; 
             int price = stoi(y); 

             if (flag == 4 &&  root != child && price > (root->price)) {  //FOR LOADING LEFT SUBTREE 
                    cout<<price<<" "<<(root->price)<<endl  ; 
                    root->right = nullptr ; delete child ;
                    return ;  
             } 

             child->JourneyCode = journey ; 
             child->price = price ; 
             child->parent = parent ;
             child->left = new TreeNode() ; 
             child->right = new TreeNode() ; 
             load( file , child->left , child ,flag , root ); 
             load( file , child->right , child , flag ,root ); 
        } 
      }
}

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST() { ; }
BST::BST(TreeNode *root) { ; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{   
    
    
    if (root == nullptr)
    {
        root = new TreeNode(JourneyCode, price);
    }
    else
    { // root exists .
        TreeNode *x = root;
        TreeNode *parent;

        while (x != nullptr &&  (price != price || JourneyCode != x->JourneyCode) )
        {
            parent = x;
            if (price < x->price)
                x = x->left;
            else
                x = x->right;
        }
        // if (price == 173036) { 
        //     cout<<"stop";
        // }
        if (x != nullptr &&  x->JourneyCode == JourneyCode && x->price == price  )
            return false; // if price is already found .

        // if ( x!=nullptr && x->JourneyCode != JourneyCode && x->price == price  ) {
        //      parent = x ; 
        //      parent->left = new TreeNode(JourneyCode, price, parent->left,nullptr,parent );
        //      return true ; 
        // }

        else
        { // if element is not found .
            if (price == parent->price)  { 
                if (parent->right == nullptr)  parent->right = new TreeNode(JourneyCode, price, parent ) ; 
                else  parent->left = new TreeNode(JourneyCode, price, parent ) ;
            }
            else if (price > parent->price)
                parent->right = new TreeNode(JourneyCode, price, parent );
            else
                parent->left = new TreeNode(JourneyCode, price, parent);
        }
    }
    return true;
}

TreeNode *BST::get(int JourneyCode, int price)
{
    TreeNode *x = root;
    while (x != nullptr && (price != x->price ||  JourneyCode != x->JourneyCode ))
    {   
        if (price < x->price)
            x = x->left;
        else
            x = x->right;
    }
    if (x != nullptr && price == x->price && JourneyCode == x->JourneyCode)
        return x;
    else
        return nullptr;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    return get(JourneyCode, price) != nullptr;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise

bool BST::deleteNode(TreeNode* element) { 
    if (element == nullptr)
        return false;
    else
    { // if element is present
        if (element->left == nullptr && element->right == nullptr)
        { // no children
            if (element->parent == nullptr)
                root = nullptr; // execptional case for root element
            else
            {
                if (element->parent->left == element)
                    element->parent->left = nullptr;
                else
                    element->parent->right = nullptr;
            }
            delete element ; 
        }
        else if (element->left == nullptr || element->right == nullptr)
        {
            TreeNode *child;
            if (element->left == nullptr)
                child = element->right; // find child
            else
                child = element->left;

            if (element->parent == nullptr)
                root = child; // execptional case for root element
            else
            {
                child->parent = element->parent; // change the parent of the child of the element .
                if (element->parent->left == element)
                    element->parent->left = child; // change parent node child to element child
                else
                    element->parent->right = child;
            }
            delete element ; 
        }
        else
        {   
            TreeNode* succesor ; 
            if (element->right != nullptr) // to find the successor of the element .
            {
                TreeNode *x = element->right;
                while (x->left != nullptr)
                    x = x->left;
                succesor = x; // this is the minimum of the right tree
            }
            else
            {
                TreeNode *x = element;
                TreeNode *y = x->parent;
                while (y != nullptr && y->right == x)
                {
                    x = y;
                    y = y->parent;
                }
                succesor = y;
            }
            // element->parent = succesor->parent ; 
            // element->left = succesor->left ; 
            // element->right = succesor->right ; 
            element->JourneyCode = succesor->JourneyCode ; 
            element->price = succesor->price ; 
            deleteNode(succesor) ;
        }
    }
    return true ;
}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal)
{
    if (typeOfTraversal == 0)
        preorder(root);
    else if (typeOfTraversal == 1)
        inorder(root);
    if (typeOfTraversal == 2)
        postorder(root);
}

// Returns the price of the cheapest journey
int BST::getMinimum()
{
    TreeNode *x = root;
    while (x->left != nullptr)
        x = x->left;
    return x->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) { 
      return bound(root,lowerPriceBound,upperPriceBound);  
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) { 
    ofstream file ; 
    file.open(filename) ;
    store(file,root) ;  
    file.close() ; 
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

void BST::customLoad(int flag, string filename) { 
    ifstream file ; 
    file.open(filename) ;   
    root = new TreeNode() ;
    load(file,root,nullptr,flag,root) ;  
    file.close() ; 
}

// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
void BST::printBST(const string &prefix, bool isLeft = false)
{
    if (root != nullptr)
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__");

        // print the value of the node
        cout << root->JourneyCode << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST(prefix + (isLeft ? "│   " : "    "), true);
        root = curr;
        root = root->right;
        printBST(prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::getBST(const string &prefix, bool isLeft = false)
{
    if (root != nullptr)
    {
        result.push_back(prefix);

        result.push_back(isLeft ? "├──" : "└──");

        // print the value of the node
        result.push_back(root->JourneyCode + "\n");
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        getBST(prefix + (isLeft ? "│   " : "    "), true);
        root = root->right;
        getBST(prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::clearResult()
{
    result.clear();
}

vector<string> BST::getResult()
{
    return result;
}
bool BST::remove(int JourneyCode, int price)
{
    TreeNode *element = get(JourneyCode, price);
    bool x = deleteNode(element) ; 
    //  if (!x && getMinimum() == 510 ) {
    //     if (price == 739) {
    //        TreeNode* a ; 
    //        TreeNode* b ; 
    //        a = get(819101,739) ; 
    //        b = get(694067, 739) ; 
    //        cout<<"819101"<<endl ; 
    //     }
    // }
    return x ; 
}

