// #include <bits/stdc++.h>
#include <iostream>
#include <fstream>
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

BST::BST()
{
    root = NULL;
}
BST::BST(TreeNode *root)
{
    this->root = root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{
    //Handles the case when the tree is empty
    if (root == NULL)
    {
        root =new TreeNode(JourneyCode,price,NULL,NULL,NULL);
        return true;
    }

    TreeNode *parent = root;
    TreeNode *node = root;

    //Iteratively goes through the tree to insert in O(nlogn)
    //If n elements is to be inserted 
    while (node != NULL)
    {
            parent = node;
            if (node->price > price)
            {

                node = node->left;
            }
            else
            {

                node = node->right;
            }
    }
    //enters the last element of the tree.
    if (parent->price > price)
    {
        parent->left = new TreeNode(JourneyCode, price,NULL,NULL,parent);
        return true;
    }
    else
    {
        parent->right = new TreeNode(JourneyCode, price,NULL,NULL,parent);
        return true;
    }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{   
    //uses the custom made function to find.
    TreeNode *node = findNode(root, JourneyCode, price);
    //If node is NULL the node, isn't present in the tree.
    if (node == NULL)
        return false;
    return true;
}

//If it finds the node, it returns the node, else  returns NULL
TreeNode *BST::findNode(TreeNode *root, int price)
{
    TreeNode *node = root;
    while (node != NULL && node->price != price)
    {
        if (node->price > price)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }
    }
    return node;
}

//Overloaded function, it also matches the correct JourneyCode
TreeNode *BST::findNode(TreeNode *root, int JourneyCode, int price)
{
    TreeNode *node = root;
    // search until null or the node with the proper price 
    //and journey specifications is found
    while (node != NULL && !(node->price == price && node->JourneyCode == JourneyCode))
    {
        if (node->price > price)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }
    }
    return node;
}

//Finds the successor of the given node;
TreeNode *BST::findSucessor(TreeNode *node)
{   
    //If right is not null, get the left most element of right tree
    if (node->right != NULL)
    {
        node = node->right;
        while (node->left != NULL)
        {
            node = node->left;
        }
        return node;
    }
    //Else traverse up the parent node,until the node is to the left of the parent
    TreeNode *parent = node->parent;
    while (parent != NULL && node == parent->right)
    {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

bool BST::removeRecursive(TreeNode *ptr, int JourneyCode, int price)
{   
    //If left is  NULL and right is NULL, deletion is simple
    if (ptr->left == NULL && ptr->right == NULL)
    {
        if (ptr == root)
        {
            root = NULL;
            delete ptr;
            return true;
        }
        if (ptr->parent->left == ptr)
            ptr->parent->left = NULL;
        else
            ptr->parent->right = NULL;
        delete ptr;
        return true;
    }
    //If left is  NULL or right is NULL, deletion is simple,
    //but we need to handle a few cases
    else if (ptr->left == NULL)
    {
        if (ptr == root)
        {
            root = root->right;
            root->parent = NULL;

            delete ptr;
            return true;
        }
        if (ptr->parent->left == ptr)
        {
            ptr->parent->left = ptr->right;
            ptr->right->parent = ptr->parent;
        }
        else
        {
            ptr->parent->right = ptr->right;
            ptr->right->parent = ptr->parent;
        }
        delete ptr;
        return true;
    }
    else if (ptr->right == NULL)
    {
        if (ptr == root)
        {
            root = root->left;
            root->parent = NULL;

            delete ptr;
            return true;
        }
        if (ptr->parent->left == ptr)
        {
            ptr->parent->left = ptr->left;
            ptr->left->parent = ptr->parent;
        }
        else
        {
            ptr->parent->right = ptr->left;
            ptr->left->parent = ptr->parent;
        }
        delete ptr;
        return true;
    }
    //It the node's left and right are not null we find its successor and 
    //replace that node's values's with that of the successor, and then call
    //delete on the successor
    TreeNode *sucessor = findSucessor(ptr);
    ptr->JourneyCode = sucessor->JourneyCode;
    ptr->price = sucessor->price;
    return removeRecursive(sucessor, sucessor->JourneyCode, sucessor->price);
}
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
//Uses the custom defined function to recursively deleted the node.
bool BST::remove(int JourneyCode, int price)
{
    //First it finds the node, and if not null deletes by calling removeRecursive.
    TreeNode *delNode = findNode(root, JourneyCode, price);
    if (delNode == NULL)
        return false;
    else
        return removeRecursive(delNode, JourneyCode, price);
}

//Recursive function for preorder
void BST::PreOrder(TreeNode *node)
{
    if (node == NULL)
        return;
    cout <<"Journey Code:"<<node->JourneyCode<<" Price:"<<node->price<< endl;
    PreOrder(node->left);
    PreOrder(node->right);
}
//Recursive function for InOrder
void BST::InOrder(TreeNode *node)
{
    if (node == NULL)
        return;

    InOrder(node->left);
    cout <<"Journey Code:"<<node->JourneyCode<<" Price:"<<node->price<< endl;
    InOrder(node->right);
}
//Recursive function for postOrder
void BST::PostOrder(TreeNode *node)
{
    if (node == NULL)
        return;

    PostOrder(node->left);
    PostOrder(node->right);
    cout <<"Journey Code:"<<node->JourneyCode<<" Price:"<<node->price<< endl;
}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line
void BST::traverse(int typeOfTraversal)
{
    switch (typeOfTraversal)
    {
    case PRE_ORDER:
        PreOrder(root);
        break;
    case POST_ORDER:
        PostOrder(root);
        break;
    case IN_ORDER:
        InOrder(root);
        break;
    default:
        break;
    }
    return;
}

// Returns the price of the cheapest journey
//Gets the left most  element
int BST::getMinimum()
{
    TreeNode *p = root;
    while (p->left != NULL)
    {
        p = p->left;
    }
    return p->price;

    return 0;
}

// Part II
int BST::countJourneysInPriceBound(TreeNode *node, int lowerPriceBound, int upperPriceBound)
{   

    int count = 0;
    //Base case
    if (lowerPriceBound > upperPriceBound)
        return 0;
    //Base case
    if (lowerPriceBound == upperPriceBound)
    {   
        //checks if the node or it's children has the same value as UB and LB
        if (findNode(node, lowerPriceBound) != NULL)
            return 1;
        return 0;
    }
    // LB<= price <= UB
    if (lowerPriceBound <= node->price && node->price <= upperPriceBound)
    {   
        //first count, the node, and then go left or right
        //also bounds are changed, as we know the left subtree cannot
        //have its upperbound > UB
        count++;
        if (node->left != NULL)
        {
            count += countJourneysInPriceBound(node->left, lowerPriceBound, node->price);
        }
        if (node->right != NULL)
        {
            count += countJourneysInPriceBound(node->right, node->price, upperPriceBound);
        }
        return count;
    }
    //Case where, the UB>LB> price
    if (lowerPriceBound >= node->price)
    {
        if (lowerPriceBound == node->price)
            count++;
        if (node->right != NULL)
            count += countJourneysInPriceBound(node->right, lowerPriceBound, upperPriceBound);
        return count;
    }
    //Case where, the price>UB>LB
    if (upperPriceBound <= node->price)
    {
        if (upperPriceBound == node->price)
            count++;
        if (node->left != NULL)
            count += countJourneysInPriceBound(node->left, lowerPriceBound, upperPriceBound);
        return count;
    }

    return 0; //must never reach here
}
// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.

//uses it's overloaded version, to calculate the Bounds
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound)
{
    TreeNode *node = root;
    int count = countJourneysInPriceBound(node, lowerPriceBound, upperPriceBound);
    return count;
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.

//Uses PreOrder Traversal to store BST nodes in two vectors passed as reference
void BST::PreOrderStore(TreeNode *node, vector<int> &JourneyCodes, vector<int> &Prices)
{

    //if a node is NULL store -1 as sentinel
    if (node == NULL)
    { 
        JourneyCodes.push_back(-1);
        Prices.push_back(-1);
        return;
    }
    JourneyCodes.push_back(node->JourneyCode);
    Prices.push_back(node->price);
    PreOrderStore(node->left, JourneyCodes, Prices);
    PreOrderStore(node->right, JourneyCodes, Prices);
}
//As preorder is O(n), it is also O(n)
void BST::customStore(string filename)
{
    ofstream file;
    file.open(filename.c_str());
    vector<int> JourneyCodes;
    vector<int> Prices;
    PreOrderStore(this->root, JourneyCodes, Prices);
    //Transfers the content of the vector onto the file
    for (int i = 0; i < JourneyCodes.size(); i++)
    {
        file << JourneyCodes[i] << " " << Prices[i] << endl;
    }
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

//Uses preorder to load the BST from the file, hence its O(n)
void BST::loadBST(TreeNode* &node,TreeNode* parent,vector<int> &JourneyCodes,vector<int> &Prices)
{   
    //In each recursive depth the vectors get smaller by 1 as elements are added
    //If the vectors are empty we break out of recursion
    if(JourneyCodes.size() == 0 || Prices.size() == 0) return;
    //if the vector's first element is -1, store NULL
    if(JourneyCodes.front() != -1)
    {
        node = new TreeNode(JourneyCodes.front(),Prices.front(),NULL,NULL,parent);
        JourneyCodes.erase(JourneyCodes.begin(),JourneyCodes.begin()+1); 
        Prices.erase(Prices.begin(),Prices.begin()+1); 
        loadBST(node->left,node,JourneyCodes,Prices);
        loadBST(node->right,node,JourneyCodes,Prices);
    }
    else
    {
        JourneyCodes.erase(JourneyCodes.begin(),JourneyCodes.begin()+1); 
        Prices.erase(Prices.begin(),Prices.begin()+1); 
        return;
    }
    
}

//Loads the tree according to the flag.
//Uses loadBST to do so
void BST::customLoad(int flag, string filename)
{

    ifstream file;
    file.open(filename.c_str());
    vector<int> JourneyCodes;
    vector<int> Prices;
    int j, p;
    file >> j; file >> p;
    JourneyCodes.push_back(j);
    Prices.push_back(p);
    while (file >> j && file >> p)
    {   
        //since it's preoder, the moment, we encounter the element
        //to be greater than the root, we break out of the loop
        if(flag == LOAD_LEFT_SUBTREE && p >= Prices[0])
            break;
        JourneyCodes.push_back(j);
        Prices.push_back(p);
        
    }
    switch (flag)
    {
    case LOAD_FULL_BST:
        loadBST(root,NULL,JourneyCodes,Prices);
        break;
    case LOAD_LEFT_SUBTREE:
        loadBST(root,NULL,JourneyCodes,Prices);
    default:
        break;
    }
    return;
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
        root = curr->right;
        printBST(prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::getBST(const string &prefix, bool isLeft = false)
{
    if (root != nullptr)
    {
        result.push_back(prefix);

        result.push_back(isLeft ? "|--" : "|__");

        // print the value of the node
        result.push_back(to_string(root->JourneyCode) + "\n");
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        getBST(prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
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
