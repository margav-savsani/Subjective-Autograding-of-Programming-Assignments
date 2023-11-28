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

BST::BST() {}
BST::BST(TreeNode *root) : root(root) {} // for initialising subtrees independently

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{
    TreeNode *t = new TreeNode(JourneyCode, price);
    if (root == NULL)
    {
        root = t;
        return true; // adds at root if its null
    }
    TreeNode *temp = new TreeNode();
    temp = root;
    while (temp != NULL)
    {
        if (temp->price > price) // if less than root goes to left
        {
            if (temp->JourneyCode == JourneyCode)
            {
                return false; // returns false if already exists
            }
            if (temp->left == NULL)
            {
                TreeNode *t = new TreeNode(JourneyCode, price, NULL, NULL, temp); // new node if its null before
                temp->left = t;
                return true;
            }
            else
                temp = temp->left;
        }
        else if (temp->price < price) // if greater than root goes to right subtree
        {
            if (temp->JourneyCode == JourneyCode)
            {
                return false; // returns false if it already exists
            }
            if (temp->right == NULL)
            {
                TreeNode *t = new TreeNode(JourneyCode, price, NULL, NULL, temp);
                temp->right = t; // creating new node if the position is null
                return true;
            }
            else
            {
                temp = temp->right;
            }
        }
    }
    return false;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    TreeNode *temp = new TreeNode();
    temp = root;
    while (temp != NULL)
    {
        if (temp->price == price && temp->JourneyCode == JourneyCode)
        {
            return true; // if found returns true
        }
        if (temp->price >= price)
        {
            temp = temp->left; // check in left tree if price is less than root's
        }
        else
        {
            temp = temp->right; // check in right subtree if price is more than root's
        }
    }
    return false;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{

    TreeNode *temp = new TreeNode();
    temp = root;

    while (temp != NULL)
    {
        if (temp->price == price && temp->JourneyCode == JourneyCode) // finding node position that needs to be removed
        {
            break;
        }
        if (temp->price >= price)
        {
            temp = temp->left;
        }
        else
        {
            temp = temp->right;
        }
    }

    if (temp == NULL)
    {
        return false; // if it not exists returns false
    }

    if (temp->left == NULL && temp->right == NULL) // leaf removal
    {
        if (temp->parent == NULL) // if root is leaf keep it back to null
        {
            root = NULL;
            return true;
        }
        if (temp->parent->right == temp) // if its a right child
        {
            temp->parent->right = NULL; // changing its parent's child to null
            return true;
        }
        else
        {
            temp->parent->left = NULL; // changing its parent's child to null
            return true;
        }
    }

    if (temp->right == NULL) // if right child is null
    {
        temp->left->parent = temp->parent; // changings its left child's parent to its parent's parent
        if (temp->parent == NULL)
        {
            root = root->left; // for root case only replace it with its left child
            return true;
        }
        if (temp == temp->parent->right) // checking if its a right child
        {
            temp->parent->right = temp->left; // changing its parents child with childs left child
        }
        else
        {
            temp->parent->left = temp->left; // changing its parents child with childs right child
        }
        return true;
    }

    if (temp->left == NULL) // if left child is null
    {
        temp->right->parent = temp->parent; // changing its right child's parent with its parent's parent's
        if (temp->parent == NULL)           // if its root
        {
            root = root->right; // replacing it with its right child
            return true;
        }
        else if (temp == temp->parent->right)
        {
            temp->parent->right = temp->right; // changing its parents child with childs left child
            return true;
        }
        else
        {
            temp->parent->left = temp->right; // changing its parents child with childs right child
        }
        return true;
    }

    TreeNode *succesor = new TreeNode(); // succesor to replace
    succesor = temp->right;              // going to right for bigger than temp values
    while (succesor->left != NULL)       // going to left from there for smallest value bigger than temp values
    {
        succesor = succesor->left;
    }
    if (succesor->parent->left == succesor)
    {
        succesor->parent->left = succesor->right; // if succesor is it's left child replace succesors with sucesor right child
    }
    if (succesor->parent->right == succesor)
    {
        succesor->parent->right = succesor->right; // if succesor is it's right child replace succesors with succesor right child
    }
    if (succesor->right != NULL)
    {
        succesor->right->parent = succesor->parent; // if succesor has a right subtree change its parent to succesor parents
    }

    if (temp->parent == NULL)
    {
        temp->JourneyCode = succesor->JourneyCode; // after deleting succesor replacing it with its succesor
        temp->price = succesor->price;             // after deleting succesor replacing it with its succesor
        return true;
    }
    else
    {
        if (temp->parent->left == temp)
        {
            temp->JourneyCode = succesor->JourneyCode; // after deleting succesor replacing it with its succesor
            temp->price = succesor->price;             // after deleting succesor replacing it with its succesor
        }

        else if (temp->parent->right == temp)
        {
            temp->JourneyCode = succesor->JourneyCode; // after deleting succesor replacing it with its succesor
            temp->price = succesor->price;             // after deleting succesor replacing it with its succesor
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
    if (root->price == 0)
    {
        return;
    }
    BST T1 = BST(root->left);  // left subtree
    BST T2 = BST(root->right); // right subtree
    if (typeOfTraversal == PRE_ORDER)
    {
        cout << root->JourneyCode << " " << root->price << endl;
        if (root->left != NULL)
        {
            T1.traverse(PRE_ORDER); // prints left subtree
        }
        if (root->right != NULL)
        {
            T2.traverse(PRE_ORDER); // prints right subtree
        }
    }
    if (typeOfTraversal == IN_ORDER)
    {
        if (root->left != NULL)
        {
            T1.traverse(IN_ORDER); // inorder of left subtree
        }
        cout << root->JourneyCode << " " << root->price << endl;
        if (root->right != NULL)
        {
            T2.traverse(IN_ORDER); // inorder od right subtree
        }
    }
    if (typeOfTraversal == POST_ORDER)
    {
        if (root->left != NULL)
        {
            T1.traverse(POST_ORDER); // post order of left subtree
        }
        if (root->right != NULL)
        {
            T2.traverse(POST_ORDER); // post order of right subtree
        }
        cout << root->JourneyCode << " " << root->price << endl;
    }
    return;
}

// Returns the price of the cheapest journey
int BST::getMinimum()
{
    TreeNode *temp = new TreeNode();
    temp = root;
    if (temp == NULL)
    {
        return -1; // no root no minimum
    }
    while (temp->left != NULL)
    {
        temp = temp->left; // left subtree has smaller prices
    }
    return (temp->price);
}
// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound)
{
    int b = 0;
    if (root == NULL)
    {
        return 0; // if no root no prices to check
    }
    if (root->price >= lowerPriceBound && root->price <= upperPriceBound)
    {
        b = 1;
    } // if root price is in the bracket its also inside so +1
    if (root->left != NULL)
    {
        BST *T1 = new BST(root->left);
        b = b + T1->countJourneysInPriceBound(lowerPriceBound, upperPriceBound); // checking in left subtree
    }
    if (root->right != NULL)
    {
        BST *T2 = new BST(root->right);
        b = b + T2->countJourneysInPriceBound(lowerPriceBound, upperPriceBound); // checking in right subtree
    }

    return b;
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename)
{
    ofstream outfile;
    outfile.open(filename, std::ios_base::app);
    outfile << root->JourneyCode << " " << root->price << endl; // custom store storing all of bst in a file
    BST T1 = BST(root->left);                                   // for left subtree
    BST T2 = BST(root->right);                                  // for right subtree
    if (root->left != NULL)
    {
        T1.customStore(filename); // storing left subtree
    }
    if (root->right != NULL)
    {
        T2.customStore(filename); // storing right subtree
    }

    outfile.close();
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
vector<string> p;
void spli(string str, char seperator) // for taking string inputs from files
{
    p.clear();
    int currIndex = 0, i = 0;
    int startIndex = 0, endIndex = 0;
    while (i <= str.length())
    {
        if (str[i] == seperator || i == str.length())
        {
            endIndex = i;
            p.push_back(str.substr(startIndex, endIndex - startIndex));
            startIndex = endIndex + 1;
        }
        i++;
    }
}
TreeNode *BST::build(vector<TreeNode *> const &preorder, int &Index, int min, int max)
{
    // Base case
    if (Index == preorder.size())
    {
        return NULL;
    }
    int val = preorder[Index]->price;
    if (val < min || val > max)
    { // if it crosses wither boundary shouldnt check anymore as its not going to be in that subtree
        return NULL;
    }

    // Construct the root node and increment `pIndex`
    TreeNode *node = new TreeNode(preorder[Index]->JourneyCode, preorder[Index]->price); // root case
    Index++;
    node->left = build(preorder, Index, min, val - 1);  // builds the whole left subtree recursively
    node->right = build(preorder, Index, val + 1, max); // builds the whole right subtree recursively
    return node;
}
void BST::customLoad(int flag, string filename)
{
    if (flag == LOAD_FULL_BST)
    {
        ifstream infile;
        infile.open(filename, std::ios_base::app); // input file
        string s;                                  ////data in line
        vector<TreeNode *> T;                      // storing tree data
        while (getline(infile, s))
        {
            spli(s, ' ');
            TreeNode *T1 = new TreeNode(stoi(p[0]), stoi(p[1])); // adding preorder into vector
            T.push_back(T1);
        }
        infile.close(); // closing the file
        int Index = 0;  // index
        root = build(T, Index, 0, 100000);
        return;
    }
else 
    if (flag == LOAD_LEFT_SUBTREE)
    {
        ifstream infile;
        infile.open(filename, std::ios_base::app); // input file
        string s;                                  ////data in line
        vector<TreeNode *> T;
        int maxprice = 0;
        if (getline(infile, s))
        {
            spli(s, ' ');
            maxprice = stoi(p[1]);
        }
        while (getline(infile, s)) // storing tree data
        {
            spli(s, ' ');
            if (maxprice < stoi(p[1]))
            {
                break;
            }
            TreeNode *T1 = new TreeNode(stoi(p[0]), stoi(p[1])); // adding preorder into vector
            T.push_back(T1);
        }
        infile.close(); // closing the file
        int Index = 0;  // index
        root = build(T, Index, 0, 100000);
        return;
    }
}

// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
// Please use the following code to replace the last part of
// BST.cpp that was provided earlier (from below the comment
// DO NOT CHANGE ANYTHING BELOW THIS LINE)
//
//

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
