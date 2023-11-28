#include "tree.h"

static int max(int a, int b)
{
    if (a >= b)
        return a;
    return b;
}

static int min(int a, int b)
{
    if (a <= b)
        return a;
    return b;
}

// constructors for TreeNode
TreeNode::TreeNode()
    : journey(0, 0), left(nullptr), right(nullptr)
{
}
TreeNode::TreeNode(int jrnyCode, int jrnyPrice)
    : journey(jrnyCode, jrnyPrice), left(nullptr), right(nullptr)
{
}
TreeNode::TreeNode(int jrnyCode, int jrnyPrice, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent)
    : journey(jrnyCode, jrnyPrice), left(leftChild), right(rightChild), parent(parent)
{
}
TreeNode::TreeNode(Journey journey, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent)
    : journey(journey), left(leftChild), right(rightChild), parent(parent)
{
}

int TreeNode::getImbalance() 
{
    updatePathLengths();
    return (longestPathLength - shortestPathLength);
}

void TreeNode::updatePathLengths()
{
    if (left != nullptr && right != nullptr) {
        left->updatePathLengths();
        right->updatePathLengths();
        longestPathLength = max(left->longestPathLength, right->longestPathLength) + 1;
        shortestPathLength = min(left->shortestPathLength, right->shortestPathLength) + 1;
    }
    else if (left == nullptr && right == nullptr)
        longestPathLength = shortestPathLength = 0;
    else {
        shortestPathLength = 0;
        TreeNode* only_child = (left != nullptr ? left : right);
        only_child->updatePathLengths();
        longestPathLength = only_child->longestPathLength + 1;
    }
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
TreeNode* TreeNode::find_node(Journey journey) 
{
    TreeNode* t = nullptr;
    TreeNode* t_child = this;

    while (t_child != nullptr) {
        t = t_child;
        if (journey <= t_child->journey) {
            if (journey == t_child->journey)
                return t_child;
            t_child = t_child->left;
        }
        else
            t_child = t_child->right;
    }

    return nullptr;
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
    if (root != nullptr) {
        root->shortestPathLength = 1;
        root->longestPathLength = 1;
    }
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
bool BST::insert(Journey journey)
{
    if (root != nullptr) {
        TreeNode* t = nullptr;
        TreeNode* t_child = root;
        while (t_child != nullptr) {
            t = t_child;
            if (journey <= t_child->journey)
                t_child = t_child->left;
            else
                t_child = t_child->right;
        }

        if (t->journey == journey)
            return false;

        TreeNode* new_node = new TreeNode(journey, nullptr, nullptr, t);

        if (journey <= t->journey)
            t->left = new_node;
        else
            t->right = new_node;

        return true;
    }
    else {
        root = new TreeNode(journey, nullptr, nullptr, nullptr);
        return true;
    }
}

// returns true, if the ticket with given attributes is found, false otherwise
    // uses TreeNode::find_node(int, int)
bool BST::find(Journey journey)
{
    if (root != nullptr)
        return (root->find_node(journey) != nullptr);
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
bool BST::remove(Journey journey)
{
    if (root != nullptr) {
        TreeNode* t = root->find_node(journey);
        if (t == nullptr)
            return false;

        if (t->left == nullptr && t->right == nullptr) {
            if (t->parent != nullptr) {
                if (t == t->parent->left) {
                    t->parent->left = nullptr;
                }
                else {
                    t->parent->right = nullptr;
                }
            }
            else {
                root = nullptr;
            }
            delete t;
        }
        else if (t->left != nullptr && t->right != nullptr) {
            TreeNode* pred = predecessor(t);

            Journey pred_journey = pred->journey;

            remove(pred->journey);

            t->journey = pred_journey;
        }
        else {
            TreeNode* only_child = (t->left != nullptr? t->left : t->right);
            if (t->parent != nullptr) {
                only_child->parent = t->parent;
                if (t == t->parent->left) {
                    t->parent->left = only_child;
                }
                else {
                    t->parent->right = only_child;
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

int BST::getImbalance()
{
    if (root != nullptr) {
        return root->getImbalance();
    }
    return 0;
}

// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
void BST::printBST(std::string const& prefix, bool isLeft)
{
    if (root != nullptr) {
        std::cout << prefix;

        std::cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        std::cout << root->journey << std::endl;
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
        result.push_back(std::to_string(root->journey.getJourneyCode()) + "\n");
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

std::vector<std::string> BST::getResult(){
    return result;
}

