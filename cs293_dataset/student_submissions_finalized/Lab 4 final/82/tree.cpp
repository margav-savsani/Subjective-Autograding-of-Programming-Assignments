#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "tree.h"

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
    this->root->left = root->left;
    this->root->right = root->right;
    this->root->JourneyCode = root->JourneyCode;
    this->root->parent = root->parent;
    this->root->price = root->price;
}

int BST::getImbalance()
{
  if (root == nullptr) return 0;
  else return root->getImbalance();
}

void BST::updateBalance(TreeNode* node, int newLength){
    if(node == nullptr) return;
    else if(!node->parent){
        node->longestPathLength = max(newLength, node->longestPathLength);
        if(node->left && node->right){
            node->shortestPathLength = min(node->left->shortestPathLength, node->right->shortestPathLength) + 1;
        }
        else{
            node->shortestPathLength = 1;
        }
    }
    else{
        node->longestPathLength = max(newLength, node->longestPathLength);
        if(node->left && node->right){
            node->shortestPathLength = min(node->left->shortestPathLength, node->right->shortestPathLength) + 1;
        }
        else if(node->left){
            node->shortestPathLength = node->left->shortestPathLength + 1;
        }
        else if(node->right){
            node->shortestPathLength = node->right->shortestPathLength + 1;
        }
        updateBalance(node->parent, newLength+1);
    }

}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{
    if(root == nullptr){
        root = new TreeNode(JourneyCode, price, nullptr, nullptr, nullptr);
        root->longestPathLength = 1;
        root->shortestPathLength = 1;
        return true;
    }
    TreeNode* tempTemp = nullptr;
    TreeNode* temp = root;
    // bool variable to ckeck the temp is the left or right child of its parent.
    bool isLeft = false;
    while(temp!=nullptr){
        // checking whether the element to be inserted is already present or not.
        if(temp->JourneyCode == JourneyCode && temp->price == price){
            return false;
        }
        // moving to the temp pointer accordingly to reach a leaf so as to insert the node accordingly.
        else if(temp->JourneyCode >= JourneyCode){
            tempTemp = temp;
            temp = temp->left;
            isLeft = true;
        }
        else{
            tempTemp = temp;
            temp = temp->right;
            isLeft = false;
        }
    }
    if(isLeft){
        tempTemp->left = new TreeNode(JourneyCode, price, nullptr, nullptr, tempTemp);
        tempTemp->left->longestPathLength = 1;
        tempTemp->left->shortestPathLength = 1;
        updateBalance(tempTemp->left, 1);
    }
    else{
        tempTemp->right = new TreeNode(JourneyCode, price, nullptr, nullptr, tempTemp);
        tempTemp->right->longestPathLength = 1;
        tempTemp->right->shortestPathLength = 1;
        updateBalance(tempTemp->right, 1);
    }
    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    TreeNode* temp = root;
    while(temp!= nullptr){
        if(temp->JourneyCode == JourneyCode && temp->price == price){
            return true;
        }
        // if current price > price current moves left.
        else if(temp->price >= price){
            temp = temp->left;
        }
        else{
            temp = temp->right;
        }
    }
    return false;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    // removal functions handles 3 cases --> both child null, one child null, none null accordingly.
    TreeNode* temp = root;
    TreeNode* tempTemp = nullptr;
    // bool variable to ckeck the temp is the left or right child of its parent.
    bool isLeft = false;
    while(temp!= nullptr){
        if(temp->JourneyCode == JourneyCode && temp->price == price){ // both child null
            if(temp->right == nullptr && temp->left == nullptr){
                // handling the case fo root separately.
                if(tempTemp == nullptr){
                    root = nullptr;
                    delete temp;
                }
                else if(isLeft){
                    delete temp;
                    tempTemp->left = nullptr;
                }
                else if(!isLeft){
                    delete temp;
                    tempTemp->right = nullptr;
                }
            }
            else if(temp->left != nullptr && temp->right == nullptr){ // one child null
                if(tempTemp == nullptr){
                    root = temp->left;
                    delete temp;
                }
                if(isLeft){
                    tempTemp->left = temp->left;
                    temp->left->parent = tempTemp;
                    delete temp;
                }
                else if(!isLeft){
                    tempTemp->right = temp->left;
                    temp->left->parent = tempTemp;
                    delete temp;
                }
            }
            else if(temp->right != nullptr && temp->left == nullptr){ // one child null
                if(tempTemp == nullptr){
                    root = temp->right;
                    delete temp;
                }
                else if(isLeft){
                    tempTemp->left = temp->right;
                    temp->right->parent = tempTemp;
                    delete temp;
                }
                else if(!isLeft){
                    tempTemp->right = temp->right;
                    temp->right->parent = tempTemp;
                    delete temp;
                }
            }
            else { // both child null
                // finding the predecesor to remove accordingly.
                TreeNode* pred = predecesor(temp);
                int a = pred->price;
                int b = pred->JourneyCode;
                remove(pred->JourneyCode, pred->price);
                temp->price = a;
                temp->JourneyCode = b;
            }
            return true;
        }
        // shifting the temp pointer accordingly.
        else if(temp->price >= price){
            tempTemp = temp;
            temp = temp->left;
            isLeft = true;
        }
        else{
            tempTemp = temp;
            temp = temp->right;
            isLeft = false;
        }
    }
    return false;
}

TreeNode* BST::predecesor(TreeNode* node){
    if(node->left){
        TreeNode* temp = node;
        temp = temp->left;
        while(temp->right!=nullptr){
            temp = temp->right;
        }
        return temp;
    }
    // actually this never get called because pred() gets called only when both child of node is not null so...
    else if(node->parent){
        TreeNode* par = node->parent;
        TreeNode* temp = node;
        while(par!=nullptr){
            if(par->right == temp){
                return par;
            }
            else{
                temp = par;
                par = par->parent;
            }
        }
    }
    return nullptr;
}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

// traversal types
void BST::traverse(int typeOfTraversal)
{
    if(typeOfTraversal == PRE_ORDER){
        preOrder(root);
    }
    else if(typeOfTraversal == POST_ORDER){
        postOrder(root);
    }
    else if(typeOfTraversal == IN_ORDER){
        inOrder(root);
    }
    else{
        cout << "No such traversal defined!" << endl;
    }
}

// the following three functions implements the 3 types of traversal functions.

void BST::preOrder(TreeNode* tree){
    if(tree){
        cout << tree->JourneyCode << endl;
        if(tree->left)preOrder(tree->left);
        if(tree->right)preOrder(tree->right);
    }
}

void BST::postOrder(TreeNode* tree){
    if(tree){
        if(tree->left) postOrder(tree->left);
        if(tree->right) postOrder(tree->right);
        cout << tree->JourneyCode << endl;
    }
}

void BST::inOrder(TreeNode* tree){
    if(tree){
        if(tree->left) inOrder(tree->left);
        cout << tree->JourneyCode <<" " << tree->longestPathLength << " " << tree->shortestPathLength << endl;
        if(tree->right) inOrder(tree->right);
    }
}

// Returns the price of the cheapest journey
// FINDS THE LEFTMOST CHILD
int BST::getMinimum() 
{  
    TreeNode* temp = root;
    while(temp->left != nullptr){
        temp = temp->left;
    }
    return temp->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.


int childJourneyCount(TreeNode* node, int lowerPriceBound, int upperPriceBound, int count=0){
    if(node == nullptr) return count;
    
    // the first two conditions handles the case when the price at the current node is not in bounds.
    TreeNode* temp = node;
    if(temp->price > upperPriceBound){
        temp = temp->left;
        return childJourneyCount(temp, lowerPriceBound, upperPriceBound, count);
    }
    else if(temp->price < lowerPriceBound){
        temp = temp->right;
        return childJourneyCount(temp, lowerPriceBound, upperPriceBound, count);
    }
    // if in bounds then call the function again with the correct node and increase count.
    else{
        count++;
        return ( count + childJourneyCount(temp->left, lowerPriceBound, upperPriceBound) + childJourneyCount(temp->right, lowerPriceBound, upperPriceBound));
    }
}

int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) { 
    return childJourneyCount(root, lowerPriceBound, upperPriceBound);
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.


// this function stores the tree as a sequence of string where I used 3-sentinels to denote left child(L), right child(R) and null child(N).
// since this is just a preorder traversal with some strings appended to the contents of the node its still O(cn) --> O(n)
string storeTree(TreeNode* node, string& tree){
    tree+=to_string(node->price) + " " + to_string(node->JourneyCode) + " ";
    if(node->left){
        tree+="L";
        tree=storeTree(node->left, tree);
    }
    else{
        tree+="LN";
    }

    if(node->right){
        tree+="R";
        tree=storeTree(node->right, tree);
    }
    else{
        tree+="RN";
    }
    return tree;
}

void BST::customStore(string filename) {
    string init = "";
    string treeString = storeTree(root, init);
    ofstream outFile;
    outFile.open(filename);
    outFile << treeString << endl;
    outFile.close();
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


// load the tree stored as string.
void BST::loadTree(string &tree, TreeNode* node){
    if(tree == "") return;
    
    // this condition handles the creation of root.
    if(node == nullptr){
        string strAfterPrice = tree.substr(tree.find(" ")+1);
        string strAfterJourney = strAfterPrice.substr(strAfterPrice.find(" ")+1);
        
        node = new TreeNode(stoi(strAfterPrice.substr(0, strAfterPrice.length() - strAfterPrice.find(" "))), stoi(tree.substr(0, tree.length() - tree.find(" "))), nullptr, nullptr, nullptr);
        root = node;
        tree = strAfterJourney;
    }
    // to store the left subtree.
    if(tree[0] == 'L'){
        string newTree = tree.substr(1);
        if(newTree[0] == 'N'){
            node->left = nullptr;
            tree = newTree.substr(1);
        }
        else{
            string strAfterPrice = newTree.substr(newTree.find(" ")+1);
            string strAfterJourney = strAfterPrice.substr(strAfterPrice.find(" ")+1);
            
            TreeNode* next = new TreeNode(stoi(strAfterPrice.substr(0, strAfterPrice.length() - strAfterPrice.find(" "))), stoi(newTree.substr(0, newTree.length() - newTree.find(" "))), nullptr, nullptr, node);
            node->left = next;
            tree = strAfterJourney;
            loadTree(tree, next);
        }
    }

    //  to store the right subtree.
    if(tree[0] == 'R'){
        string newTree = tree.substr(1);
        if(newTree[0] == 'N'){
            node->right = nullptr;
            tree = newTree.substr(1);
        }
        else{
            string strAfterPrice = newTree.substr(newTree.find(" ")+1);
            string strAfterJourney = strAfterPrice.substr(strAfterPrice.find(" ")+1);
            
            TreeNode* next = new TreeNode(stoi(strAfterPrice.substr(0, strAfterPrice.length() - strAfterPrice.find(" "))), stoi(newTree.substr(0, newTree.length() - newTree.find(" "))), nullptr, nullptr, node);
            node->right = next;
            tree = strAfterJourney;
            loadTree(tree, next);
        }
    }
}

// thos function is to store the left subtree of the tree stored as string.
// very similar to the previous function, just added a cnt variable to don't store the right subtree.
void BST::leftLoadTree(string &tree, TreeNode* node, int cnt){
    if(tree == "") return;

    // handles the creation of left child of original tree root as the left subtree root.
    if(node == nullptr){
        string strAfterPrice = tree.substr(tree.find(" ")+1);
        string strAfterJourney = strAfterPrice.substr(strAfterPrice.find(" ")+1);

        if(strAfterJourney[0] == 'L'){
            tree = strAfterJourney.substr(1);
            if(strAfterJourney[1] == 'N'){
                root = nullptr;
                return;
            }
            else{
                strAfterPrice = tree.substr(tree.find(" ")+1);
                strAfterJourney = strAfterPrice.substr(strAfterPrice.find(" ")+1);
                node = new TreeNode(stoi(strAfterPrice.substr(0, strAfterPrice.length() - strAfterPrice.find(" "))), stoi(tree.substr(0, tree.length() - tree.find(" "))), nullptr, nullptr, nullptr);
                root = node;
                tree = strAfterJourney;
            }
        }
        
    }

    if(tree[0] == 'L'){
        string newTree = tree.substr(1);
        if(newTree[0] == 'N'){
            node->left = nullptr;
            tree = newTree.substr(1);
        }
        else{
            string strAfterPrice = newTree.substr(newTree.find(" ")+1);
            string strAfterJourney = strAfterPrice.substr(strAfterPrice.find(" ")+1);
            
            TreeNode* next = new TreeNode(stoi(strAfterPrice.substr(0, strAfterPrice.length() - strAfterPrice.find(" "))), stoi(newTree.substr(0, newTree.length() - newTree.find(" "))), nullptr, nullptr, node);
            node->left = next;
            tree = strAfterJourney;
            leftLoadTree(tree, next, cnt+1);
        }
    }

    // not storing in case of right subtree storage.
    if(tree[0] == 'R' && cnt != 0){
        string newTree = tree.substr(1);
        if(newTree[0] == 'N'){
            node->right = nullptr;
            tree = newTree.substr(1);
        }
        else{
            string strAfterPrice = newTree.substr(newTree.find(" ")+1);
            string strAfterJourney = strAfterPrice.substr(strAfterPrice.find(" ")+1);
            
            TreeNode* next = new TreeNode(stoi(strAfterPrice.substr(0, strAfterPrice.length() - strAfterPrice.find(" "))), stoi(newTree.substr(0, newTree.length() - newTree.find(" "))), nullptr, nullptr, node);
            node->right = next;
            tree = strAfterJourney;
            leftLoadTree(tree, next, cnt+1);
        }
    }

}

//  function which calls another functions according to the flag provided, to load tree from the string stored.
void BST::customLoad(int flag, string filename) {
    ifstream f(filename); //taking file as inputstream
    string tree;
    if(f) {
        ostringstream ss;
        ss << f.rdbuf(); // reading data
        tree = ss.str();
    }
    cout<<tree;
    if(flag == LOAD_FULL_BST){
        loadTree(tree, nullptr);
    }
    else if(flag == LOAD_LEFT_SUBTREE){
        leftLoadTree(tree, nullptr, 0);
    }
    else{
        cout << "WRONG FLAG" << endl;
    }

}

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


    // // cout << price << endl;
    // if(root == nullptr){
    //     root = new TreeNode(JourneyCode, price, nullptr, nullptr, nullptr);
    //     root->shortestPathLength = 1;
    //     root->longestPathLength = 1;        
    //     return true;
    // }
    // TreeNode* tempTemp = nullptr;
    // TreeNode* temp = root;
    // // bool variable to ckeck the temp is the left or right child of its parent.
    // bool isLeft = false;
    // while(temp!=nullptr){
    //     // checking whether the element to be inserted is already present or not.
    //     if(temp->JourneyCode == JourneyCode && temp->price == price){
    //         if(tempTemp == nullptr) return false;
    //         else{
    //             while(tempTemp!= nullptr){
    //                 if(tempTemp->left->price == temp->price){
    //                     if(tempTemp->right){
    //                         tempTemp->longestPathLength = max(tempTemp->left->longestPathLength + 1, tempTemp->right->longestPathLength + 1);
    //                         tempTemp->shortestPathLength = min(tempTemp->left->shortestPathLength + 1, tempTemp->right->shortestPathLength + 1);
    //                         tempTemp = tempTemp->parent;
    //                         temp = temp->parent;
    //                     }
    //                     else{
    //                         tempTemp->longestPathLength = temp->longestPathLength + 1;
    //                         tempTemp->shortestPathLength = temp->shortestPathLength + 1;
    //                         tempTemp = tempTemp->parent;
    //                         temp = temp->parent;
    //                     }
    //                 }
    //                 else{
    //                     if(tempTemp->left){
    //                         tempTemp->longestPathLength = max(tempTemp->left->longestPathLength + 1, tempTemp->right->longestPathLength + 1);
    //                         tempTemp->shortestPathLength = min(tempTemp->left->shortestPathLength + 1, tempTemp->right->shortestPathLength + 1);
    //                         tempTemp = tempTemp->parent;
    //                         temp = temp->parent;
    //                     }
    //                     else{
    //                         tempTemp->longestPathLength = temp->longestPathLength + 1;
    //                         tempTemp->shortestPathLength = temp->shortestPathLength + 1;
    //                         tempTemp = tempTemp->parent;
    //                         temp = temp->parent;
    //                     }
    //                 }
    //             }
    //         }
    //         return false;
    //     }
    //     // moving to the temp pointer accordingly to reach a leaf so as to insert the node accordingly.
    //     else if(temp->price >= price){
    //         temp->longestPathLength = temp->longestPathLength + 1;
    //         temp->shortestPathLength = min(temp->shortestPathLength, temp->longestPathLength);
            
    //         tempTemp = temp;
    //         temp = temp->left;
    //         isLeft = true;
    //     }
    //     else{
    //         temp->longestPathLength = temp->longestPathLength + 1;
    //         temp->shortestPathLength = min(temp->shortestPathLength, temp->longestPathLength);

    //         tempTemp = temp;
    //         temp = temp->right;
    //         isLeft = false;
    //     }
    // }
    // if(isLeft){
    //     tempTemp->left = new TreeNode(JourneyCode, price, nullptr, nullptr, tempTemp);
    //     tempTemp->left->longestPathLength = 1;
    //     tempTemp->left->shortestPathLength = 1;
    // }
    // else{
    //     tempTemp->right = new TreeNode(JourneyCode, price, nullptr, nullptr, tempTemp);
    //     tempTemp->right->longestPathLength = 1;
    //     tempTemp->right->shortestPathLength = 1;
    // }
    // return true;




