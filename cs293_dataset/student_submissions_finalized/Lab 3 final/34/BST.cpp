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

BST::BST()
{
    root = new struct TreeNode();
}
BST::BST(struct TreeNode *root_1)
{
    root = new struct TreeNode(root_1->JourneyCode, root_1->price, root_1->left, root_1->right, root_1->parent);
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{
    if (root->left == nullptr && root->right == nullptr && root->JourneyCode == 0 && root->price == 0)
    {
        root->JourneyCode = JourneyCode;
        root->price = price;
        return true;
    }
    //temp stores the the address of parent of place where we have to store the values.
    struct TreeNode *temp = root;
    while (true)
    {
        if (temp->JourneyCode == JourneyCode && temp->price == price)
        {
            // if we found the JourneyCode then exit.
            return false;
        }
        //the prices greater than or equal to the temp price are stored in right subtree of temp
        else if (temp->price <= price)
        {
            if (temp->right == nullptr)
            {
                temp->right = new struct TreeNode(JourneyCode, price);
                temp->right->parent = temp;
                return true;
            }
            else
                temp = temp->right;
        }
        //the prices less than or equal to the temp price are stored in left subtree of temp
        else
        {
            if (temp->left == nullptr)
            {
                temp->left = new struct TreeNode(JourneyCode, price);
                temp->left->parent = temp;
                return true;
            }
            else
                temp = temp->left;
        }
    }
    return false;
}
// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    //temp will travel through tree according to its price value until it is equal to 
    struct TreeNode *temp = root;
    while (true)
    {
        if (temp->JourneyCode == JourneyCode && temp->price == price)
        {
            // The JourneyCode is found return true;
            return true;
        }
        else if (temp->price <= price)
        {
            if (temp->right == nullptr)
            {
                //we reached the end so no such JourneyCode present
                return false;
            }
            else
                temp = temp->right;
        }
        else
        {
            if (temp->left == nullptr)
            {
                //we reached the end so no such JourneyCode present
                return false;
            }
            else
                temp = temp->left;
        }
    }
}
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    //After the while loop is executed, temp will store the address of node to be deleted.
    struct TreeNode *temp = root;
    //After the while loop is executed, temp_parent will store the address of parent of node to be deleted.
    struct TreeNode *temp_parent = nullptr;
    while (true)
    {
        if (temp->JourneyCode == JourneyCode && temp->price == price)
        {
            //the temp to be deleted is found
            break;
        }
        else if (temp->price <= price)
        {
            if (temp->right == nullptr)
            {
                // reached the end and temp not found
                return false;
            }
            else
            {
                temp = temp->right;
                temp_parent = temp->parent;
            }
        }
        else
        {
            if (temp->left == nullptr)
            {
                // reached the end and temp not found
                return false;
            }
            else
            {
                temp = temp->left;
                temp_parent = temp->parent;
            }
        }
    }
    //case 1 : the temp is leaf node.
    if (temp->right == nullptr && temp->left == nullptr)
    {
        //this is the case when the temp is root
        if (temp_parent == nullptr)
        {
            temp->JourneyCode = 0;
            temp->price = 0;
            return true;
        }
        else
        {
            //temp is removed.
            if (temp_parent->left == temp)
            {
                temp->parent = nullptr;
                temp_parent->left = nullptr;
                return true;
            }
            else
            {
                temp_parent->right = nullptr;
                temp->parent = nullptr;
                return true;
            }
        }
    }
    //case 2 : the temp has only one child.
    else if (temp->right == nullptr || temp->left == nullptr)
    {
        //the case when temp is root.
        if (temp_parent != nullptr)
        {
            //the child is left child
            if (temp->right == nullptr)
            {
                struct TreeNode *child = temp->left;
                child->parent = temp_parent;
                if (temp_parent->left == temp)
                {
                    temp_parent->left = child;
                }
                else
                {
                    temp_parent->right = child;
                }
                temp->parent = nullptr;
                temp->left = nullptr;
                return true;
            }
            //the child is right child
            else
            {
                struct TreeNode *child = temp->right;
                child->parent = temp_parent;
                if (temp_parent->left == temp)
                {
                    temp_parent->left = child;
                }
                else
                {
                    temp_parent->right = child;
                }
                temp->parent = nullptr;
                temp->right = nullptr;
                return true;
            }
        }
        //when temp is not root.
        else
        {
            if (temp->right == nullptr)
            {
                root = temp->left;
                temp->left = nullptr;
                root->parent = nullptr;
                return true;
            }
            else
            {
                root = temp->right;
                temp->right = nullptr;
                root->parent = nullptr;
                return true;
            }
        }
    }
    //case 3 : the temp has two child.
    else
    {
        //successor stores the address of successor of temp.
        struct TreeNode *successor = temp->right;
        while (true)
        {
            if (successor->left != nullptr)
            {
                successor = successor->left;
            }
            else
                break;
        }
        //the info of successor and temp are swaped.
        temp->JourneyCode = successor->JourneyCode;
        temp->price = successor->price;
        successor->JourneyCode = JourneyCode;
        successor->price = price;
        temp = successor;
        temp_parent = successor->parent;
        //it is obvious that the successor's left child is nullptr.
        //so it has atmost 1 child.
        //case 1 : it has no child.
        if (temp->right == nullptr)
        {
            if (temp_parent->left == temp)
            {
                temp->parent = nullptr;
                temp_parent->left = nullptr;
                return true;
            }
            else
            {
                temp_parent->right = nullptr;
                temp->parent = nullptr;
                return true;
            }
        }
        //case 2 : it has left child.
        else
        {
            struct TreeNode *child = temp->right;
            child->parent = temp_parent;
            if (temp_parent->left == temp)
            {
                temp_parent->left = child;
            }
            else
            {
                temp_parent->right = child;
            }
            temp->parent = nullptr;
            temp->right = nullptr;
            return true;
        }
    }
    return true;
}
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal)
{
    struct TreeNode *temp = root;
    if (typeOfTraversal == 0)
        preorder(temp);
    else if (typeOfTraversal == 1)
        postorder(temp);
    else if (typeOfTraversal == 2)
        inorder(temp);
}

void BST::preorder(struct TreeNode *temp)
{
    if (temp == nullptr)
    {
        return;
    }
    cout << temp->JourneyCode << endl;
    preorder(temp->left);
    preorder(temp->right);
}

void BST::inorder(struct TreeNode *temp)
{
    if (temp == nullptr)
    {
        return;
    }
    inorder(temp->left);
    cout << temp->JourneyCode << endl;
    inorder(temp->right);
}
void BST::postorder(struct TreeNode *temp)
{
    if (temp == nullptr)
    {
        return;
    }
    postorder(temp->left);
    postorder(temp->right);
    cout << temp->JourneyCode << endl;
}

// Returns the price of the cheapest journey
int BST::getMinimum()
{
    struct TreeNode *Min = root;
    while (true)
    {
        if (Min->left == nullptr)
            return Min->price;
        else
        {
            Min = Min->left;
        }
    }
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.

//the following task is done by using inorder traversal.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound)
{
    //counts total nodes with given condition.
    int count = 0;
    if (root != nullptr)
    {
        //stores the address of root since root is changed in program.
        struct TreeNode *curr = root;
        root = root->left;
        count += countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
        root = curr;
        //if the root(the current node) satisfies the condition then increase count.
        if (root->price >= lowerPriceBound && root->price <= upperPriceBound)
            count++;
        root = root->right;
        count += countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
        root = curr;
    }
    return count;
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename)
{
    ofstream f;
    f.open(filename, std::ios_base::app);
    struct TreeNode *curr = root;
    f << root->JourneyCode << " " << root->price << endl;
    if (root->left != nullptr)
    {
        // "[" this bracket is used to indicate the start of left subtree. 
        f << "[" << endl;
        f.close();
        root = root->left;
        customStore(filename);
        f.open(filename, std::ios_base::app);
        // "]" this bracket is used to indicate the end of left subtree. 
        f << "]" << endl;
    }
    root = curr;
    if (root->right != nullptr)
    {
        // "{" this bracket is used to indicate the start of right subtree. 
        f << "{" << endl;
        f.close();
        root = root->right;
        customStore(filename);
        f.open(filename, std::ios_base::app);
        // "}" this bracket is used to indicate the end of right subtree. 
        f << "}" << endl;
    }
    root = curr;
    f.close();
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

void BST::customLoad(int flag, string filename)
{
    //parent stores the parent of the root(the current node)
    struct TreeNode *parent = nullptr;
    int count = 0;
    ifstream f;
    f.open(filename);
    char bracket;
    // if LOAD_FULL_BST
    if (flag == 4)
    {
        int useless;
        for (int i = 0; i < 2; i++)f >> useless;
        f >> bracket;
        if(bracket == '['){
            count++;
            f >> root->JourneyCode;
            f >> root->price;
        }
        else{
            root = nullptr;
            return;
        }
    }
    //if LOAD_LEFT_SUBTREE
    else if (flag == 3)
    {
        f >> root->JourneyCode;
        f >> root->price;
    }
    while (!f.eof())
    {
        f >> bracket;
        //this is to stop when the left subtree ends since LOAD_LEFT_SUBTREE will load only left part.
        if (!(flag == 4 && count == 0))
        {
            if (bracket == '[')
            {
                //when left subtree is started
                int JrnyCode;
                int Jrnyprice;
                f >> JrnyCode;
                f >> Jrnyprice;
                root->left = new struct TreeNode(JrnyCode, Jrnyprice);
                parent = root;
                root = root->left;
                root->parent = parent;
                //when left subtree starts the count increases.
                count++;
            }
            else if (bracket == '{')
            {
                //when right subtree is started
                int JrnyCode;
                int Jrnyprice;
                f >> JrnyCode;
                f >> Jrnyprice;
                root->right = new struct TreeNode(JrnyCode, Jrnyprice);
                parent = root;
                root = root->right;
                root->parent = parent;
            }
            else if (bracket == ']')
            {
                //left subtree ends
                if (root->parent == nullptr)
                {
                    parent = nullptr;
                }
                else
                {
                    //assigning the address of parent of the node to root i.e. going reverse.
                    root = parent;
                    parent = root->parent;
                }
                //when the left subtree ends the counts decreases
                count--;
            }
            else if (bracket == '}')
            {
                if (root->parent == nullptr)
                {
                    parent = nullptr;
                }
                else
                {
                    root = parent;
                    parent = root->parent;
                }
            }
        }
    }
    f.close();
    f.open("test.ser", std::ofstream::out | std::ofstream::trunc);
    f.close();
}

// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
void BST::printBST(const string &prefix, bool isLeft = false)
{
    if (root != nullptr)
    {
        std::cout << prefix;

        std::cout << (isLeft ? "|--" : "|__");

        // print the value of the node
        std::cout << root->JourneyCode << endl;
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
