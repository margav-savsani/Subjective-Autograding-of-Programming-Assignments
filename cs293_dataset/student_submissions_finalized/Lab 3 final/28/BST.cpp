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

BST::BST() { root = NULL; }
BST::BST(TreeNode *root)
{
    this->root = root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{
    if (findjourneycode(JourneyCode, price))
        return false;
    /* void insert(Node*& root, int key)
  {
      Node* node = new Node(key);
      if (!root) {
          root = node;
          return;
      }
      Node* prev = NULL;
      Node* temp = root;
      while (temp) {
          if (temp->val > key) {
              prev = temp;
              temp = temp->left;
          }
          else if (temp->val < key) {
              prev = temp;
              temp = temp->right;
          }
      }
      if (prev->val > key)
          prev->left = node;
      else
          prev->right = node;
  }*/
    TreeNode *node = new TreeNode(JourneyCode, price);
    if (root == NULL)
    {
        root = node;
        return true;
    }
    TreeNode *prev = NULL;
    TreeNode *temp = root;
    while (temp != NULL)
    {
        if (temp->price >= price)
        {
            prev = temp;
            temp = temp->left;
        }
        else if (temp->price < price)
        {
            prev = temp;
            temp = temp->right;
        }
    }
    if (prev->price >= price)
    {
        prev->left = node;
        node->parent = prev;
        return true;
    }
    else
    {
        prev->right = node;
        node->parent = prev;
        return true;
    }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::findjourneycode(int JourneyCode, int price)
{
    TreeNode *x = root;
    while ((x != NULL) && (x->JourneyCode != JourneyCode))
    {
        if (x->price >= price)
            x = x->left;
        else
            x = x->right;
    }
    if (x == NULL)
        return false;
    else
        return true;
}

bool BST::find(int JourneyCode, int price)
{
    TreeNode *x = root;
    while ((x != NULL) && ((x->price != price) || (x->JourneyCode != JourneyCode)))
    {
        if (x->price >= price)
            x = x->left;
        else
            x = x->right;
    }
    if (x == NULL)
        return false;
    else
        return true;
}

TreeNode *BST::findadd(int JourneyCode, int price)
{
    TreeNode *x = root;
    while ((x != NULL) && ((x->price != price) || (x->JourneyCode != JourneyCode)))
    {
        if (x->price >= price)
            x = x->left;
        else
            x = x->right;
    }
    return x;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
// bool BST::remove(int JourneyCode, int price)
// {
//     if (find(JourneyCode, price) == 0)
//         return false;
//     TreeNode *node = findadd(JourneyCode, price);
//     if(node==root){
//         if(root->left==NULL &root->right==NULL) {root=NULL;return true;}
//         else if(root->left==NULL){
//             root=root->right;
//             root->parent=NULL;
//             return true;
//         }
//         else if(root->right==NULL){
//             root=root->left;
//             root->parent=NULL;
//             return true;
//         }
//         else {
//             TreeNode * Successor=NULL;

//         }

//     }
//     else if (node->left == NULL && node->right == NULL)
//     {
//         if ((node->parent)->left == node)
//             (node->parent)->left = NULL;
//         if ((node->parent)->right == node)
//             (node->parent)->right = NULL;
//         // delete node;
//         return true;
//     }
//     else if (node->left == NULL)
//     {
//         if ((node->parent)->left == node)
//         {
//             (node->parent)->left = node->right;
//             (node->right)->parent = node->parent;
//         }
//         if ((node->parent)->right == node)
//         {
//             (node->parent)->right = node->right;
//             (node->right)->parent = node->parent;
//         }
//         // delete node;
//         return true;
//     }
//     else if (node->right == NULL)
//     {
//         if ((node->parent)->left == node)
//         {
//             (node->parent)->left = node->left;
//             (node->left)->parent = node->parent;
//         }
//         if ((node->parent)->right == node)
//         {
//             (node->parent)->right = node->left;
//             (node->left)->parent = node->parent;
//         }
//         // delete node;
//         return true;
//     }
//     else
//     {
//         TreeNode *Successor = NULL;
//         if ((node->right)->left == NULL)
//         {
//             Successor = node->right;
//             if ((node->parent)->left == node)
//             {
//                 (node->parent)->left = Successor;
//                 Successor->left = node->left;
//                 Successor->parent = node->parent;
//             }
//             if ((node->parent)->right == node)
//             {
//                 (node->parent)->right = Successor;
//                 Successor->left = node->left;
//                 Successor->parent = node->parent;
//             }
//         }
//         TreeNode *temp = node->right;
//         if ((node->right)->left != NULL)
//         {
//             while (temp != NULL)
//             {
//                 temp = temp->left;
//             }
//             Successor = temp;
//             if ((node->parent)->left == node)
//             {
//                 (Successor->parent)->left = NULL;
//                 Successor->right = node->right;
//                 Successor->left = node->left;
//                 Successor->parent = node->parent;
//                 // (Successor->right)->left = NULL;
//                 (node->parent)->left = Successor;
//                 (node->right)->parent = Successor;
//             }
//             if ((node->parent)->right == node)
//             {
//                 (Successor->parent)->left = NULL;
//                 Successor->right = node->right;
//                 Successor->left = node->left;
//                 Successor->parent = node->parent;
//                 // (Successor->right)->left = NULL;
//                 (node->parent)->right = Successor;
//                 (node->right)->parent = Successor;
//             }
//         }
//         return true;
//     }

//      return false;
// }

bool BST::remove(int JourneyCode, int price)
{
    TreeNode *z = findadd(JourneyCode, price);
    if (z == nullptr)
    {
        return false;
    }
    if (z == root)
    {
        if (z->left == nullptr && z->right == nullptr)
        {
            root = nullptr;
            return true;
        }
        else if (z->left != nullptr && z->right == nullptr)
        {
            root = z->left;
            return true;
        }
        else if (z->left == nullptr && z->right != nullptr)
        {
            root = z->right;
            return true;
        }
    }
    if (z->left == nullptr && z->right == nullptr)
    {
        TreeNode *y = z->parent;
        if (y->left == z)
        {
            y->left = nullptr;
        }
        else
            y->right = nullptr;
        return true;
    }
    else if (z->left == nullptr)
    {
        TreeNode *y = z->parent;
        if (y->left == z)
        {
            TreeNode *x = z->right;
            x->parent = y;
            y->left = x;
        }
        else
        {
            TreeNode *x = z->right;
            x->parent = y;
            y->right = x;
        }
        return true;
    }
    else if (z->right == nullptr)
    {
        TreeNode *y = z->parent;
        if (y->left == z)
        {
            TreeNode *x = z->left;
            x->parent = y;
            y->left = x;
        }
        else
        {
            TreeNode *x = z->left;
            x->parent = y;
            y->right = x;
        }
        return true;
    }
    else
    {
        TreeNode *y = successor(z);
        remove(y->JourneyCode, y->price);
        z->JourneyCode = y->JourneyCode;
        z->price = y->price;
        return true;
    }
}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal)
{

    if (typeOfTraversal == IN_ORDER)
        Inorder(root);
    if (typeOfTraversal == PRE_ORDER)
        Preorder(root);
    if (typeOfTraversal == POST_ORDER)
        Postorder(root);
}

// Returns the price of the cheapest journey
int BST::getMinimum()
{
    if (root == NULL)
        return 0;
    else if (root->left == NULL)
        return (root->price);
    TreeNode *current = root;
    while (current->left != NULL)
    {
        current = current->left;
    }
    return (current->price);
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound)
{
    if (root == NULL)
        return 0;
    else if (root->price >= lowerPriceBound && root->price <= upperPriceBound)
    {
        BST t1(root->left);
        BST t2(root->right);
        return 1 + t1.countJourneysInPriceBound(lowerPriceBound, upperPriceBound) + t2.countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
    }
    else
    {
        BST t1(root->left);
        BST t2(root->right);
        return t1.countJourneysInPriceBound(lowerPriceBound, upperPriceBound) + t2.countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
    }
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
    outfile.open(filename);
    if (root == NULL)
        return;

    // Create an empty stack and push root to it

    stack<TreeNode *> s;
    TreeNode *curr = root;

    while (curr != NULL || s.empty() == false)
    {
        /* Reach the left most Node of the
           curr Node */
        while (curr != NULL)
        {
            /* place pointer to a tree node on
               the stack before traversing
              the node's left subtree */
            s.push(curr);
            curr = curr->left;
        }

        /* Current must be NULL at this point */
        curr = s.top();
        s.pop();

        outfile << curr->price << " " << curr->JourneyCode << endl;

        /* we have visited the node and its
           left subtree.  Now, it's right
           subtree's turn */
        curr = curr->right;

    } /* end of while */

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

TreeNode * create(vector<int>a ,vector<int>b){
   int counter=0;
    
    TreeNode *root1 =new TreeNode(b[0],a[0]);
    
    if(a[1]<=a[0]) TreeNode * lef=new TreeNode(b[1],a[1]);

    TreeNode *root=NULL;
  //  root->left=lef;

    for(int i=0;i<a.size();i++){
       

    }

   return root1;

}

void BST::customLoad(int flag, string filename)
{
    ifstream infile;
    infile.open(filename);
    int count = 0;
    vector<int> prices;
    vector<int> codes;
    int price, code;
    infile >> price;
    //cout << price << endl;
    infile >> code;
   // cout << code << endl;
    prices.push_back(price);
    count++;
    codes.push_back(code);
    count++;
    // TreeNode * root=new TreeNode(code,price);

    while (!infile.eof())
    {
        infile >> price;
        infile >> code;
        if (!infile.eof())
        {
            prices.push_back(price);
            codes.push_back(code);
         //   cout << code << endl;
        }
    }
    root=create(prices,codes);

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

        result.push_back(isLeft ? "├──" : "└──");

        // print the value of the node
        result.push_back(root->JourneyCode + "\n");
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
