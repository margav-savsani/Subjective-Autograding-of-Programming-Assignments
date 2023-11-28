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

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST()
{
    root = nullptr;
}
BST::BST(TreeNode *root)
{
    this->root = root;
}

// Return true, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    TreeNode *temp = root;

    while (temp != nullptr)
    {
        if (temp->JourneyCode == JourneyCode)//temporarily store journeycode 
            return true;

        if (price < temp->price)
        {
            temp = temp->left;//keep going left
        }
        else
        {
            temp = temp->right;//keep going right
        }
    }

    if (temp == nullptr)//if null
        return false;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{

    if (find(JourneyCode, price))
    {
        return false;
    }

    TreeNode *nodeToInsert = new TreeNode(JourneyCode, price);//stores the new node to be inserted
    TreeNode *temp = root;//initialize temp as root of the tree

   
    TreeNode *prev = NULL;//stores the prvious temp

    while (temp != NULL)//loop for finding location for insertion
    {
        prev = temp;
        if (price < temp->price)
            temp = temp->left;
        else
            temp = temp->right;
    }

    // If the root is NULL i.e the tree is empty
    // The new node is the root node
    if (prev == NULL)
    {
        root = nodeToInsert;
        return true;
    }

    // If the new key is less than the leaf node key
    // Assign the new node to be its left child
    else if (price < prev->price)
    {
        prev->left = nodeToInsert;
        prev->left->parent = prev;
    }
    // else assign the new node its right child
    else
    {
        prev->right = nodeToInsert;
        prev->right->parent = prev;
    }

    return true;
}

TreeNode *BST::successor(TreeNode *node)
{ // two child case, so successor always in right subtree
    TreeNode *temp = node->right;
    while (temp->left != nullptr)
    {
        temp = temp->left;
    }
    return temp;
}

void BST::mydelete(TreeNode *node)
{

    // leaf
    if (node->left == nullptr && node->right == nullptr)//leaf
    {
        if (node == root)//separate checking for root
            delete (node);
        else
        {
            if (node == node->parent->left)
            {

                node->parent->left = nullptr;//deletion requires certain relations to be changed
                delete (node);
            }

            else
            {

                node->parent->right = nullptr;//deletion requires certain relations to be changed
                delete (node);
            }
        }
    }
    // one child
    else if (node->left == nullptr || node->right == nullptr)
    {
        if (node == root)//separate checking for root
        {
            if (node->left == nullptr)
            {
                root = root->right;//deletion requires certain relations to be changed
                root->parent = nullptr;
            }
            else
            {
                root = root->left;//deletion requires certain relations to be changed
                root->parent = nullptr;
            }
        }
        else
        {
            if (node == node->parent->left)
            {

                if (node->left == nullptr)
                {
                    node->right->parent = node->parent;//deletion requires certain relations to be changed
                    node->parent->left = node->right;//deletion requires certain relations to be changed
                }
                else
                {
                    node->left->parent = node->parent;//deletion requires certain relations to be changed
                    node->parent->left = node->left;//deletion requires certain relations to be changed
                }
            }
            else
            {

                if (node->left == nullptr)
                {
                    node->right->parent = node->parent;//deletion requires certain relations to be changed
                    node->parent->right = node->right;//deletion requires certain relations to be changed
                }
                else
                {
                    node->left->parent = node->parent;//deletion requires certain relations to be changed
                    node->parent->right = node->left;//deletion requires certain relations to be changed
                }
            }
            delete (node);
        }
    }

    else//two children
    {
        TreeNode *succ = successor(node);//min of right node
        int JourneyCode = succ->JourneyCode;
        int price = succ->price;
        mydelete(succ);
        node->JourneyCode = JourneyCode;
        node->price = price;
    }
}
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{

    TreeNode *nodeToDelete = root;
    while (true)
    {
        if (nodeToDelete == NULL)
            return false;

        if (nodeToDelete->JourneyCode == JourneyCode)
        {
            mydelete(nodeToDelete);
            return true;
        }
        if (nodeToDelete->price > price)
        {
            nodeToDelete = nodeToDelete->left;
        }
        else
        {
            nodeToDelete = nodeToDelete->right;
        }
    }

    return true;
}

int BST::getMinimum()
{
    TreeNode *temp = root;
    while (temp->left != nullptr)
    {
        temp = temp->left;//leftmost leap
    }
    return temp->price;
}
void BST::preorder(TreeNode *root)
{
    if (root == nullptr)
        return;
    else
    {
        cout << (root->JourneyCode) << endl;// print 
        preorder(root->left);//left traverse
        preorder(root->right);//right traverse
    }
}

void BST::postorder(TreeNode *root)
{
    if (root == nullptr)
        return;
    else
    {

        postorder(root->left);//left traverse
        postorder(root->right);//right traverse
        cout << (root->JourneyCode) << endl;// print 
    }
}

void BST::inorder(TreeNode *root)
{
    if (root == nullptr)
        return;
    else
    {

        inorder(root->left);//left traverse
        cout << (root->JourneyCode) << endl;// print 
        inorder(root->right);//right traverse
    }
}
// Functions that traverse the BST in various ways!
// type can be PRE_ORDER, POST_ORDER or IN_ORDER, which
// #defined numeric constants defined in BST.cpp
// This function prints on cout the journey codes (one per line)
// encountered on traversing the BST in the given traversal order
void BST::traverse(int typeOfTraversal)
{
    if (typeOfTraversal == 0)
    {
        preorder(root);
    }
    else if (typeOfTraversal == 1)
    {
        postorder(root);
    }
    else if (typeOfTraversal == 2)
    {
        inorder(root);
    }
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.

int BST::modifiedpreorder(int lower, int upper, TreeNode *node, int &counter)
{
    if (node == nullptr)
    {
        return 0;
    }
    if (node->price >= lower && node->price <= upper)
        counter++;
    if (node->price > lower)
    {

        modifiedpreorder(lower, upper, node->left, counter);//left subtree
    }
    if (node->price <= upper)
    {

        modifiedpreorder(lower, upper, node->right, counter);//right subtree
    }
    return counter;//number of nodes within the range
}
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound)
{

    int counter = 0;
    if (root == nullptr)
        return 0;
    else
    {
        return modifiedpreorder(lowerPriceBound, upperPriceBound, root, counter);
    }
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.

void BST::sentinel(TreeNode *temp, ofstream &outfile, string str)
{

    if (temp == nullptr)
        return;
    outfile << temp->JourneyCode << " " << temp->price << " ";
    outfile << str << endl;

    //     if(temp->parent->left==temp){// if node is left child
    //             str = str.append("$");//sentinel for left
    //             outfile<<str<<endl;
    //            // if(temp->left!=nullptr || temp->right!=nullptr){

    //                 if(temp->right == nullptr)
    //                     TreeNode* temp1 = temp;
    //                     while(temp>temp1->parent){
    //                     height--;
    //                     temp1 = temp1->parent;
    //                 }
    //                 height--;
    //             }

    //      }
    //     else{// if node is right child
    //             str = str.append("*");//sentinel for righ
    //             outfile<<str<<endl;
    //              if(temp->right!=nullptr || temp->left!=nullptr){

    //             if(temp->right == nullptr)
    //                 TreeNode* temp1 = temp;
    //                 while(temp>temp1->parent){
    //                     height--;
    //                     temp1 = temp1->parent;
    //                 }
    //                 height--;//one extra reqd
    //             }
    //     }
    // }//tried this but recursively worked very easily and multiple cases didnt have to be checked

    sentinel(temp->left, outfile, str + "$");//copies $ at the end if going left
    sentinel(temp->right, outfile, str + "*");//copies $ at the end if going right
}

void BST::customStore(string filename)
{

    ofstream outfile;
    outfile.open(filename);

    TreeNode *temp = root;
    string str = "";

    sentinel(temp, outfile, str);
    outfile.close();
}

void BST::customLoad(int flag, string filename)
{

    ifstream infile;
    infile.open(filename);
    if (flag == LOAD_FULL_BST)
    {
        int JourneyCode, price, i;
        string code;//for taking in input the sentinel
        infile >> JourneyCode;
        infile >> price;
        root = new TreeNode(JourneyCode, price);
        TreeNode *temp = root;
        string prevcode = "";//initially null string

        while (true)
        {
            //for root
            int JourneyCode, price;
            string code;
            infile >> JourneyCode;
            infile >> price;
            infile >> code;
            if (infile.eof())//if file reaches end
                break;
            TreeNode *node = new TreeNode(JourneyCode, price);


            int count = 0;
            while (count < prevcode.length() - code.length() + 1)//temp goes upward till count reaches this difference
            {
                temp = temp->parent;
                count++;
            }

            if (code[code.length() - 1] == '$')//last element $ go left
            {

                temp->left = node;
                node->parent = temp;//set parent and child accordingly
            }
            else
            {

                temp->right = node;
                node->parent = temp;//set parent and child accordingly
            }
            temp = node;
            prevcode = code;
        }
    }
    else{//after the root
        int JourneyCode, price, i;
        string code;
        infile >> JourneyCode;
        infile >> price;
        string prevcode;
        infile >> JourneyCode >> price >>prevcode;
        root = new TreeNode(JourneyCode, price);
        TreeNode *temp = root;
        

        while (true)
        {

            int JourneyCode, price;
            string code;
            infile >> JourneyCode;
            infile >> price;
            infile >> code;
            if (infile.eof() || code[0]== '*')
                break;
            TreeNode *node = new TreeNode(JourneyCode, price);

            //(code.length() < prevcode.length()) or vice versa
            int count = 0;
            while (count < prevcode.length() - code.length() + 1)//temp goes upward till count reaches this difference
            {
                temp = temp->parent;
                count++;
            }

            if (code[code.length() - 1] == '$')
            {

                temp->left = node;
                node->parent = temp;//set parent and child accordingly
            }
            else
            {

                temp->right = node;
                node->parent = temp;//set parent and child accordingly
            }
            temp = node;
            prevcode = code;
        }
    }
}

// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

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
