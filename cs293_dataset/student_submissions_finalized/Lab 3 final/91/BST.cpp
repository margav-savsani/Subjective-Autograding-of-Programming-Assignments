// Arnav Aditya Singh
// 210050018
#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4

// constructors for TreeNode
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

// returns pointer to minimum node of the subtree with this as root
    // goes left at every node
TreeNode* TreeNode::minimum_node()
{
    TreeNode* head = this;
    while (head->left != nullptr)
        head = head->left;
    return head;
}
// returns pointer to maximum node of the subtree with this as root
    // goes right at every node
TreeNode* TreeNode::maximum_node()
{
    TreeNode* head = this;
    while (head->right != nullptr)
        head = head->right;
    return head;
}

// returns pointer to node with given JourneyCode, price
// returns nullptr if not found
    // at every node, we compare requested price with price of that node
    // if req price > node price, we go right
    // else if req price == node price, we check if this is the required node
    // else we go left
    // terminating when nullptr is reached
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

// prints BST in the requested manner of traversal
    // self-explanatory
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

// stores the subtree (which has root as this) in file filename
    // stores preorder traversal of the tree
void TreeNode::customStore(std::string const& filename)
{
    std::ofstream file;
    file.open(filename, std::ios_base::app);
    file << JourneyCode << ' ' << price;
    if (left != nullptr) {
        file << ' ';
        file.close();
        left->customStore(filename);
        file.open(filename, std::ios_base::app);
    }
    if (right != nullptr) {
        file << ' ';
        file.close();
        right->customStore(filename);
        file.open(filename, std::ios_base::app);
    }

    file.close();
}

// returns pointer to successor of TreeNode *v
    // if right != nullptr then we return minimum of right subtree
    // else we return lowest ancestor whose left child is also an ancestor
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

// returns pointer to predecessor of TreeNode *v
    // if left != nullptr then we return maximum of left subtree
    // else we return lowest ancestor whose right child is also an ancestor
TreeNode* BST::predecessor(TreeNode* v)
{
    if (v->left != nullptr)
        return (v->left)->maximum_node();
    TreeNode* y = v->parent;
    while (y != nullptr && v == y->left) {
        v = y;
        y = y->parent;
    }
    return y;
}

// constructors for BST class
BST::BST()
    : root(nullptr)
{
}
BST::BST(TreeNode* _root)
    : root(_root)
{
}
// destructor for BST class
    // Heh's smart destruction TM
BST::~BST()
{
    if (root != nullptr) {
        {
            BST left_tree(root->left);
            BST right_tree(root->right);
        }
        delete root;
    }
}

// returns false, if given JourneyCode is already present in the BST
// inserts the element and returns true otherwise
    // find appropriate TreeNode to insert new TreeNode (going left for <= and right for >),
    // check if it isn't already there
    // and if not, insert it
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

// returns true, if the ticket with given attributes is found, false otherwise
    // uses TreeNode::find_node(int, int)
bool BST::find(int JourneyCode, int price)
{
    if (root != nullptr)
        return (root->find_node(JourneyCode, price) != nullptr);
    else
        return false;
}

// returns false, if JourneyCode isn't present
// deletes the corresponding entry and returns true otherwise
    // using TreeNode::find_node we check if the node is even present
    // if it has no children we directly delete it (after taking care of parent)
    // if it has two children we remove predecessor**** and put values of predecessor in this node
    // else we transfer only child to parent and delete
    // all the while taking care of nullptrs and a=making sure we set root when needed
    // **** see https://cs.stackexchange.com/questions/119958/algorithm-to-delete-bst-nodes-with-duplicated-values for why predecessor and not successor is used
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
            else {
                root = nullptr;
            }
            delete t;
        }
        else if (t->left != nullptr && t->right != nullptr) {
            TreeNode* pred = predecessor(t);

            int pred_JourneyCode = pred->JourneyCode;
            int pred_price = pred->price;

            remove(pred->JourneyCode, pred->price);

            t->price = pred_price;
            t->JourneyCode = pred_JourneyCode;
        }
        else {
            TreeNode* only_child = (t->left != nullptr? t->left : t->right);
            if (t->parent != nullptr) {
                only_child->parent = t->parent;
                if (t == (t->parent)->left) {
                    (t->parent)->left = only_child;
                }
                else {
                    (t->parent)->right = only_child;
                }
                t->parent = nullptr;
            }
            else {
                only_child->parent = nullptr;
                root = only_child;
            }
            t->left = t->right = nullptr;
            delete t;
        }
        return true;
    }
    else
        return false;
}

// prints requested traversal of the BST
    // uses TreeNode::traverse(int typeOfTraversal)
void BST::traverse(int typeOfTraversal)
{
    if (root != nullptr)
        root->traverse(typeOfTraversal);
    else
        std::cout << "Empty tree\n";
    return;
}

// returns the price of the cheapest journey
    // uses TreeNode::minimum_node()
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

// returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included
    // using BST::successor(TreeNode* v)
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound)
{
    int n = 0;
    if (upperPriceBound < lowerPriceBound)
        return 0;
    if (root == nullptr)
        return 0;
    TreeNode* head = root->minimum_node();

    while (head != nullptr && head->price < lowerPriceBound)
        head = successor(head);
    while (head != nullptr && head->price <= upperPriceBound) {
        head = successor(head);
        n++;
    }

    return n;
}

// stores BST in file filename
    // uses TreeNode::customStore(std::string const&)
void BST::customStore(std::string const& filename)
{
    std::ofstream file;
    file.open(filename);
    file << "";
    file.close();
    if (root != nullptr)
        root->customStore(filename);
}

// returns pointer to root of tree constructed from the vector<int>s jcs and prs
    // a utility function for BST::customLoad(int, std::string const&)
TreeNode* BST::constructTree(std::vector<int> const& jcs, std::vector<int> const& prs, int& index, int jc, int pr, int min, int max)
{
    if (index >= jcs.size())
        return nullptr;
 
    TreeNode* head = nullptr;
 
    if (pr > min && pr <= max) {
        head = new TreeNode(jc, pr);
        index += 1;
 
        if (index < jcs.size()) {
            head->left = constructTree(jcs, prs, index, jcs[index], prs[index], min, pr);
            if (head->left != nullptr)
                head->left->parent = head;
        }
        if (index < jcs.size()) {
            head->right = constructTree(jcs, prs, index, jcs[index], prs[index], pr, max);
            if (head->right != nullptr)
                head->right->parent = head;
        }
    }
 
    return head;
}

// loads BSt from a file that was created by BST::customStore(std::string const&)
void BST::customLoad(int flag, std::string const& filename)
{
    this->~BST();
    std::ifstream file(filename);
    std::vector<int> jcs;
    std::vector<int> prs;
    while (!file.eof()) {
        int jc, pr;
        file >> jc >> pr;
        jcs.push_back(jc);
        prs.push_back(pr);
    }
    if (flag == LOAD_FULL_BST) {
        int index = 0;
        root = constructTree(jcs, prs, index, jcs[0], prs[0], INT_MIN, INT_MAX);
    }
    else if (flag == LOAD_LEFT_SUBTREE) {
        int index = 1;
        root = constructTree(jcs, prs, index, jcs[1], prs[1], INT_MIN, prs[0]);
    }
}

// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
void BST::printBST(std::string const& prefix, bool isLeft=false)
{
    if (root != nullptr) {
        std::cout << prefix;

        std::cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        std::cout << root->JourneyCode << std::endl;
        TreeNode* curr = root;
        root = curr->left;
        // enter the next tree level - left and right branch
        printBST(prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST(prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::getBST(std::string const& prefix,  bool isLeft=false)
{
    if (root != nullptr) {
        result.push_back(prefix);

        result.push_back(isLeft ? "|--" : "|__" );

        // print the value of the node
        result.push_back(std::to_string(root->JourneyCode) + "\n");
        TreeNode* curr = root;
        root = curr->left;
        // enter the next tree level - left and right branch
        getBST(prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        getBST(prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::clearResult(){
    result.clear();
}

vector<std::string> BST::getResult(){
    return result;
}

