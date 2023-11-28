#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4

TreeNode::TreeNode()
    : price(0), JourneyCode(0), left(nullptr), right(nullptr)
{
}
TreeNode::TreeNode(int jrnyCode, int jrnyPrice)
    : price(jrnyPrice), JourneyCode(jrnyCode), left(nullptr), right(nullptr)
{
}
TreeNode::TreeNode(int jrnyCode, int jrnyPrice, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent)
    : price(jrnyPrice), JourneyCode(jrnyCode), left(leftChild), right(rightChild), parent(parent)
{
}
TreeNode::~TreeNode()
{
    if (left != nullptr) {
        delete left;
    }
    if (right != nullptr) {
        delete right;
    }
}
TreeNode* TreeNode::minimum_node()
{
    TreeNode* head = this;
    while (head->left != nullptr)
        head = head->left;
    return head;
}
TreeNode* TreeNode::find_node(int JourneyCode, int price)
{
    TreeNode* t = nullptr;
    TreeNode* t_child = this;

    while (t_child != nullptr) {
        t = t_child;
        if (price <= t_child->price) {
            if (price == t_child->price && JourneyCode == t_child->JourneyCode)
                return t_child;
            t_child = t_child->left;
        }
        else
            t_child = t_child->right;
    }

    return nullptr;
}
void TreeNode::traverse(int typeOfTraversal)
{
    switch (typeOfTraversal) {
        case PRE_ORDER:
            std::cout << JourneyCode << '\n';
            if (left != nullptr)
                left->traverse(PRE_ORDER);
            if (right != nullptr)
                right->traverse(PRE_ORDER);
          break;
        case POST_ORDER:
            if (left != nullptr)
                left->traverse(POST_ORDER);
            if (right != nullptr)
                right->traverse(POST_ORDER);
            std::cout << JourneyCode << '\n';
          break;
        case IN_ORDER:
            if (left != nullptr)
                left->traverse(IN_ORDER);
            std::cout << JourneyCode << '\n';
            if (right != nullptr)
                right->traverse(IN_ORDER);
          break;
        default:
            std::cout << "Give valid traversal type!\n";
            throw -1;
    }
}

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

TreeNode* BST::successor(TreeNode* v)
{
    if (v->right != nullptr)
        return (v->right)->minimum_node();
    TreeNode* y = v->parent;
    while (y != nullptr && v == y->right) {
        v = y;
        y = y->parent;
    }
    return y;
}

BST::BST()
    : root(nullptr)
{
}

BST::BST(TreeNode* _root)
    : root(_root)
{
}

BST::~BST()
{
    if (root != nullptr)
        delete root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{
    if (root != nullptr) {
        TreeNode* t = nullptr;
        TreeNode* t_child = root;
        
        while (t_child != nullptr) {
            t = t_child;
            if (price <= t_child->price)
                t_child = t_child->left;
            else
                t_child = t_child->right;
        }

        if (t->JourneyCode == JourneyCode)
            return false;
        
        TreeNode* new_node = new TreeNode(JourneyCode, price, nullptr, nullptr, t);
        
        if (price <= t->price)
            t->left = new_node;
        else
            t->right = new_node;
        
        return true;
    }
    else {
        root = new TreeNode(JourneyCode, price, nullptr, nullptr, nullptr);
        return true;
    }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    if (root != nullptr)
        return (root->find_node(JourneyCode, price) != nullptr);
    else
        return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    if (root != nullptr) {
        TreeNode* t = root->find_node(JourneyCode, price);
        if (t == nullptr)
            return false;

        if (t->left == nullptr && t->right == nullptr) {
            if (t->parent != nullptr) {
                if (t == (t->parent)->left) {
                    (t->parent)->left = nullptr;
                }
                else {
                    (t->parent)->right = nullptr;
                }
            }
            delete t;
        }
        else if (t->left != nullptr && t->right != nullptr) {
            TreeNode* succ = successor(t);

            int succ_JourneyCode = succ->JourneyCode;
            int succ_price = succ->price;

            remove(succ->JourneyCode, succ->price);

            t->price = succ_price;
            t->JourneyCode = succ_JourneyCode;
        }
        else {
            TreeNode* only_child = (t->left != nullptr? t->left : t->right);
            only_child->parent = t->parent;
            if (t->parent != nullptr) {
                if (t == (t->parent)->left) {
                    (t->parent)->left = only_child;
                }
                else {
                    (t->parent)->right = only_child;
                }
                t->parent = nullptr;
            }
            t->left = t->right = nullptr;
            delete t;
        }
        return true;
    }
    else
        return false;
}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal)
{
    if (root != nullptr)
        root->traverse(typeOfTraversal);
    else
        std::cout << "Empty tree\n";
    return;
}

// Returns the price of the cheapest journey
int BST::getMinimum()
{
    if (root != nullptr)
        return root->minimum_node()->price;
    else {
        std:;cout << "No minimum, BST is empty!\n";
        throw -1;
    }
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound)
{
    return 0;
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename)
{
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
 
void BST::customLoad (int flag, string filename)
{
    return;
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
        root = curr->left;
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
        root = root->right;
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

