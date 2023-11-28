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

BST::BST() : root{ nullptr } {};

BST::BST(TreeNode *root) : root{ root } {}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
    if (find(JourneyCode, price)) return false;

    // Create the new node
    TreeNode* new_node = new TreeNode { JourneyCode, price };
    new_node->parent = nullptr;

    // Inserting at the root
    if (!root) {
        root = new_node;
        return true;
    }

    // Insert at the right place
    TreeNode* cur { root };
    while (true) {
        if (price > cur->price) {
            if (cur->right) cur = cur->right;
            else {
                cur->right = new_node;
                new_node->parent = cur;
                return true;
            }
        } else {
            if (cur->left) cur = cur->left;
            else {
                cur->left = new_node;
                new_node->parent = cur;
                return true;
            }
        }
    }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    TreeNode* cur { root };
    while (true) {
        if (!cur) return false;

        if (cur->JourneyCode == JourneyCode && cur->price == price) return true;

        if (price > cur->price) cur = cur->right;
        else cur = cur->left;
    }
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
    if (!find(JourneyCode, price)) return false;

    TreeNode* cur { root };

    while (true) {
        if (JourneyCode == cur->JourneyCode && price == cur->price) {
            if (!(cur->left) && !(cur->right)) {
                // Deleting at the leaf
                if (cur == root) root = nullptr;
                else {
                    if (cur->parent->left == cur) cur->parent->left = nullptr;
                    else cur->parent->right = nullptr;
                }

            } else if (!(cur->left) || !(cur->right)) {
                // Deleting node with one child
                TreeNode* next = cur->left ? cur->left : cur->right;
                next->parent = cur->parent;
                if (cur != root) {
                    if (cur->parent->left == cur) cur->parent->left = next;
                    else cur->parent->right = next;
                }
                else {
                    root = next;
                    root->parent = nullptr;
                }

            } else {
                // Deleting node with two children
                TreeNode* next = findmax(cur->left);  // Node to be inserted at the deleted node's place

                // Update pointers from the node
                swap(next->parent, cur->parent);
                swap(next->right, cur->right);
                swap(next->left, cur->left);
                
                // Update pointers to the node
                next->right->parent = next;
                if (next->parent) {
                    if (next->parent->left == cur) next->parent->left = next;
                    else next->parent->right = next;
                }
                else root = next;

                if (next != next->left) {
                    next->left->parent = next;
                    cur->parent->right = cur->left;
                    if (cur->left) cur->left->parent = cur->parent;
                } else {
                    next->left = cur->left;
                    if (next->left) next->left->parent = next;
                }
            }

            return true;

        } else if (price > cur->price) cur = cur->right;
        else cur = cur->left;
    }
}

// Finds the max element in the tree rooted at Root
TreeNode* BST::findmax(TreeNode* Root) {
    while (Root->right) Root = Root->right;
    return Root;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    std::vector<TreeNode> traversal;
    dfs(root, typeOfTraversal, traversal);
    for (auto &node : traversal) std::cout << node.JourneyCode << ' ';
    std::cout << '\n';
}

// Traverses the tree in depth first manner
void BST::dfs(TreeNode* Root, int type, std::vector<TreeNode> &res) {
    if (!Root) return;

    if (type == 0) {
        res.push_back(*Root);
        dfs(Root->left, type, res);
        dfs(Root->right, type, res);
    } else if (type == 1) {
        dfs(Root->left, type, res);
        dfs(Root->right, type, res);
        res.push_back(*Root);
    } else {
        dfs(Root->left, type, res);
        res.push_back(*Root);
        dfs(Root->right, type, res);
    }
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode* node { root };
    if (!node) return 0;
    while (node->left) node = node->left;
    return node->price;
}

// Part II

// Finds the first element with price in the tree greater than value using binary search
int BST::search(const std::vector<TreeNode> &tree, int value) {
    int left { }, right { tree.size() };
    while (left < right) {
        int m = (left + right)/2;
        if (tree[m].price <= value) left = m+1;
        else right = m;
    }
    return left;
}

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    std::vector<TreeNode> tree;
    dfs(root, IN_ORDER, tree);  // Generates the prices in sorted order

    return search(tree, upperPriceBound) - search(tree, lowerPriceBound-1);
}

// Returns the size of the tree rooted at node and updates the values in result
int BST::subtree_size(TreeNode* node, std::vector<std::vector<int>> &res) {
    if (!node) return 0;

    int l = subtree_size(node->left, res);  // Left subtree size
    int r = subtree_size(node->right, res);  // Right subtree size
    res.push_back({node->JourneyCode, node->price, l, r});

    // Subtree size = left subtree size + right subtree size + 1
    return l+r+1;
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) {
    ofstream out;
    out.open(filename);

    // The tree is stored in post order
    std::vector<std::vector<int>> tree;  // Each element is {journey code, price, left subtree size, right subtree size}
    int sz = subtree_size(root, tree);
    for (auto &node : tree) {
        for (int i : node) out << i << ' ';
        out << '\n';
    }

    out.close();
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
 
void BST::customLoad (int flag, string filename) {
    ifstream in;
    in.open(filename);

    std::vector<std::vector<int>> tree;
    int code, prc, l, r;
    // Load the tree into the vector tree
    while (in >> code) {
        in >> prc >> l >> r;
        tree.push_back({code, prc, l, r});
    }
    in.close();

    int first = tree.size() - 1;  // Stores the location of the root
    if (flag == LOAD_LEFT_SUBTREE) first -= tree[first][3]+1;
    
    // Create the root and start creating the tree
    root = new TreeNode { tree[first][0], tree[first][1]};
    root->parent = nullptr;
    load_node(tree, root, first);
}

// Creates the left and right child of node given tree and its position in the tree vector
// 
// Since tree is the post order, therefore the vector is {left subtree, right subtree, root}
// As we know the size of right and left subtree, we can find left and right child in constant
// time given position of root
void BST::load_node (const std::vector<std::vector<int>> &tree, TreeNode* node, int pos) {
    // Left child
    if (tree[pos][2]) {
        int next = pos-tree[pos][3]-1;
        TreeNode* new_node = new TreeNode { tree[next][0], tree[next][1] };
        new_node->parent = node;
        node->left = new_node;

        load_node(tree, new_node, next);
    }

    // Right child
    if (tree[pos][3]) {
        TreeNode* new_node = new TreeNode { tree[pos-1][0], tree[pos-1][1] };
        new_node->parent = node;
        node->right = new_node;

        load_node(tree, new_node, pos-1);
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
        cout << root->price << endl;
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