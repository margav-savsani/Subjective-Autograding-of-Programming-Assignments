#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <fstream>

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
    root = nullptr;
}
BST::BST(TreeNode *root)
{ 
    this->root = root;
    (this->root)->parent = nullptr;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) 
{
    if (find(JourneyCode, price)) return 0;
    TreeNode * newnode = new TreeNode(JourneyCode, price);
    if (root == nullptr) 
    {
        root = newnode;
        root->parent = nullptr;
        return 1;
    }
    TreeNode * where = root;
    bool inserted = 0;
    while (inserted == 0)
    {
        if (where->price < newnode->price)
        {
            if (where->right == nullptr)
            {
                where->right = newnode;
                newnode->parent = where;
                return 1;
            }
            else where = where->right;
        }
        else 
        {
            if (where->left == nullptr)
            {
                where->left = newnode;
                newnode->parent = where;
                return 1;
            }
            else where = where->left;
        }
    }
    return inserted;
}
    
// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) 
{ 
    TreeNode * newnode = new TreeNode(JourneyCode, price);
    if (root == nullptr) return 0;
    TreeNode * spot = root;
    bool found = 0;
    while (found == 0)
    {
        if (spot == nullptr) return 0;
        if (spot->issame(newnode)) return 1;
        if (spot->price == price && spot->JourneyCode != JourneyCode) return 0;
        if (spot->price != price && spot->JourneyCode == JourneyCode) return 0;
        if (spot->price < newnode->price)
        {
            spot = spot->right;
        }
        else if (spot->price > newnode->price)
        {
            spot = spot->left;
        }
    }
    return found;
}

TreeNode * BST::minimum(TreeNode * start)
{
    if (start == nullptr) return nullptr;
    while (start->left != nullptr) start = start->left;
    return start;
}

TreeNode * BST::successor(TreeNode * x)
{
    if (x == nullptr) return nullptr;
    if (x->right != nullptr) return minimum(x->right);
    else
    {
        TreeNode * p = x->parent;
        if (x == p->left) return p;
        while (p != nullptr && x == p->right)
        {
            x = p;
            p = p->parent;
        }
        return p;
    }
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) 
{
    if (!find(JourneyCode, price)) return 0;
    TreeNode * todelete = new TreeNode(JourneyCode, price);
    TreeNode * spot = root;
    TreeNode *prnt = nullptr;
    bool deleted = 0;
    while (deleted == 0)
    {
        if (spot->issame(todelete)) 
        {
            // 3 cases ---- return 1 at the end
            //if (spot == nullptr) return 0;
            // when spot is a leaf
            if (spot->left == nullptr && spot->right == nullptr)
            {
                if (spot == root) {root = nullptr; return 1;}
                if (spot == prnt->left) prnt->left = nullptr;
                else prnt->right = nullptr;
            }
            // when the spot has one child
            else if (spot->left != nullptr && spot->right == nullptr)
            {
                if (spot == root) {root = spot->left; return 1;}
                if (spot == prnt->left) prnt->left = spot->left;
                else prnt->right = spot->left;
            }
            else if (spot->left == nullptr && spot->right != nullptr)
            {
                if (spot == root) {root = spot->right; return 1;}
                if (spot == prnt->left) prnt->left = spot->right;
                else prnt->right = spot->right;
            }
            //when the spot has two children
            else
            {
                TreeNode * succ = successor(spot);
                remove(succ->JourneyCode, succ->price);
                if (spot == root) {root = succ; succ->left = spot->left; succ->right = spot->right; return 1;}
                if (spot == prnt->left) prnt->left = succ;
                else prnt->right = succ;
                succ->left = spot->left;
                succ->right = spot->right;
            }
            return 1;
        }
        if (spot->price < todelete->price)
        {
            prnt = spot;
            spot = spot->right;
        }
        else if (spot->price > todelete->price)
        {
            prnt = spot;
            spot = spot->left;
        }
    }
    return deleted;
}

void BST::preorder(TreeNode * start)
{
    if (start == nullptr) return;
    cout << start->JourneyCode << endl;
    preorder(start->left);
    preorder(start->right);
}

void BST::inorder(TreeNode * start)
{
    if (start == nullptr) return;
    inorder(start->left);
    cout << start->JourneyCode << endl;
    inorder(start->right);
}

void BST::postorder(TreeNode * start)
{
    if (start == nullptr) return;
    postorder(start->left);
    postorder(start->right);
    cout << start->JourneyCode << endl;
}

void BST::traverse(int typeOfTraversal) 
{
    if (typeOfTraversal == PRE_ORDER) preorder(root);
    else if (typeOfTraversal == POST_ORDER) postorder(root);
    else if (typeOfTraversal == IN_ORDER) inorder(root);
    return; 
}

// Returns the price of the cheapest journey
int BST::getMinimum() 
{
    if (minimum(root) == nullptr) return INT_MAX;
    else return minimum(root)->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) 
{
    if (root == nullptr) return 0;
    if (root->price == lowerPriceBound && root->price == upperPriceBound) return 1;
    if (root->price < lowerPriceBound) 
    {
        BST * other = new BST(root->right);
        return other->countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
    }
    if (lowerPriceBound <= root->price && root->price <= upperPriceBound) 
    {
        BST * other1 = new BST(root->left);
        BST * other2 = new BST(root->right);
        return (1 + other1->countJourneysInPriceBound(lowerPriceBound, root->price)
                    + other2->countJourneysInPriceBound(root->price, upperPriceBound));
    } 
    if (root->price > upperPriceBound)
    {
        BST * other = new BST(root->left);
        return other->countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
    }
    return 0;
}
// pre-order traversal stored
// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::store(ofstream &outfile)
{
    if (root == nullptr) return;
    outfile << root->JourneyCode << ' ' << root->price << endl;
    if (root->left != nullptr)
    {
        BST(root->left).store(outfile);
    }
    if (root->right != nullptr)
    {
        BST(root->right).store(outfile);
    }

}

void BST::customStore(string filename) 
{ 
    //cout << "customstore start\n";
    ofstream outfile;
    outfile.open(filename);
    //cout << "here\n";
    if (root == nullptr) return;
    //cout << "here2\n";
    store(outfile);
    outfile.close();
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
void BST::customLoad (int flag, string filename) 
{ 
    //cout << "customload start\n";
    if (flag == 3 || flag == 4)
    {
        ifstream infile;
        infile.open(filename);
        vector<int> el;
        TreeNode * rel = nullptr;
        int rootprice;
        //cout << "here1\n";
        int i = 0;
        int jrny, prc;
        while (infile >> jrny >> prc)
        {
            //cout << "here6\n";
            //if (infile.eof()) break;
            //cout << "here2\n";
            //cout << jrny << ' ' << prc << endl;
            if (i == 0 && flag == 4)
            {
                rootprice = prc;
                i++;
                continue;
            }
            TreeNode * newnode = new TreeNode(jrny, prc);
            //cout << "here3\n";
            if ((i == 0 && flag == 3) || (i == 1 && flag == 4)) 
            {
                el.push_back(prc); 
                root = newnode; 
                //cout << "here4\n";
                root->parent = nullptr; 
                rel = root; 
                //cout << "here5\n";
                i++;
                //printBST("", false);
                continue;
            }
            if (flag == 4 && rootprice < prc) break;
            if (prc < el.back())
            {
                //cout << "here7\n";
                rel->left = newnode;
                newnode->parent = rel;
                rel = newnode;
                el.push_back(prc);
                i++;
                //printBST("", false);
                continue;
            }
            int last = -1;
            while (prc > el.back())
            {
                //if the price is greater than the last element
                //pop the last element
                //if the next element is greater than price
                //or if stack is empty
                //make this element the right child of the element you just popped
                //else make the rel point to its parent
                last = el.back();
                if (prc > last) el.pop_back();
                if (el.back() > prc || el.empty())
                {
                    rel->right = newnode;
                    rel = newnode;
                    //printBST("", false);
                    break;
                }
                else
                {
                    rel = rel->parent;
                }
            }
            el.push_back(prc);
            i++;
        }
        infile.close();
        //printBST("", false);
    }
    else return;
}


// *************************************************************
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
        //cout << "here?" << endl;
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
