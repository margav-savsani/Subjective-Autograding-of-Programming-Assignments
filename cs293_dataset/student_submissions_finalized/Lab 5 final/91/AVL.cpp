#include "AVL.h"

void AVLTree::updateHeights(TreeNode* t)
{
    if (t == nullptr)
        return;
    int prevHeight = t->height;
    if (t->left != nullptr && t->right != nullptr)
        t->height = std::max(t->left->height, t->right->height) + 1;
    else if (t->left == nullptr && t->right == nullptr)
        t->height = 0;
    else if (t->right == nullptr)
        t->height = t->left->height + 1;
    else
        t->height = t->right->height + 1;
    if (prevHeight == 0 || prevHeight != t->height)
        updateHeights(t->parent);
}

bool AVLTree::rotate(TreeNode* currNode)
{
    TreeNode* parentNode;
    TreeNode* grandParentNode;
    if (currNode != nullptr && (parentNode = currNode->parent) != nullptr && (grandParentNode = parentNode->parent) != nullptr) {
        if ((currNode == parentNode->left) == (parentNode == grandParentNode->left)) {
            // LL or RR
            bool isLL = (currNode == parentNode->left);
            TreeNode* midTree = (isLL ? parentNode->right : parentNode->left);
            TreeNode* greatGrandParentNode = grandParentNode->parent;
            bool isGPLeftChild = false;
            if (greatGrandParentNode != nullptr) {
                isGPLeftChild = (greatGrandParentNode->left == grandParentNode);
            }
            else {
                root = parentNode;
            }
            
            updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);

            updateAVLParentChild(grandParentNode, parentNode, !isLL);
            
            updateAVLParentChild(midTree, grandParentNode, isLL);

            updateHeights(midTree);
            updateHeights(currNode);
            updateHeights(grandParentNode);
            updateHeights(parentNode);
            return true;
        }
        else {
            // LR or RL
            bool isLR = (currNode == parentNode->right);
            TreeNode* midTreeToGP = (isLR ? currNode->right : currNode->left);
            TreeNode* midTreeToP = (isLR ? currNode->left : currNode->right);
            TreeNode* greatGrandParentNode = grandParentNode->parent;
            bool isGPLeftChild = false;
            if (greatGrandParentNode != nullptr) {
                isGPLeftChild = (greatGrandParentNode->left == grandParentNode);
            }
            else {
                root = currNode;
            }
            updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
            
            updateAVLParentChild(midTreeToGP, grandParentNode, isLR);
            updateAVLParentChild(midTreeToP, parentNode, !isLR);
            
            updateAVLParentChild(grandParentNode, currNode, !isLR);
            updateAVLParentChild(parentNode, currNode, isLR);

            updateHeights(midTreeToP);
            updateHeights(midTreeToGP);
            updateHeights(grandParentNode);
            updateHeights(parentNode);
            return true;
        }
    }
    else {
        return false;
    }
}

bool AVLTree::rotateLeftLeft(TreeNode* currNode, TreeNode* parentNode, TreeNode* grandParentNode)
{
    return rotate(currNode);
}

bool AVLTree::rotateLeftRight(TreeNode* currNode, TreeNode* parentNode, TreeNode* grandParentNode)
{
    return rotate(currNode);
}

bool AVLTree::rotateRightLeft(TreeNode* currNode, TreeNode* parent, TreeNode* grandParent)
{
    return rotate(currNode);
}

bool AVLTree::rotateRightRight(TreeNode* currNode, TreeNode* parent, TreeNode* grandParent)
{
    return rotate(currNode);
}

void AVLTree::recursiveDelete(TreeNode *currNode) {
    if (currNode != nullptr) {
        TreeNode* leftChild = currNode->left;
        TreeNode* rightChild = currNode->right;

        delete currNode;
        recursiveDelete(leftChild);
        recursiveDelete(rightChild);
    }
    return;
}

bool AVLTree::AVLLessThan(TreeNode* leftArg, TreeNode*rightArg) {
    if ((leftArg != nullptr) && (rightArg != nullptr)) {
        bool result = (*leftArg < *rightArg);
        totalComparisonCost += perComparisonCost;
        return result;
    }
    else {
        std::cerr << "Unexpected exceptional condition!\n";
        exit(-1);
    }
}

void AVLTree::updateAVLParentChild(TreeNode *childNode, TreeNode *parentNode, bool isLeftChild)
{
    if ((childNode != nullptr) && (parentNode != nullptr)) {
        TreeNode* oldParent = childNode->parent;
        childNode->updateParentChild(parentNode, isLeftChild);
        totalParentChildUpdateCost += perParentChildUpdateCost;
    }
    else if ((childNode == nullptr) && (parentNode != nullptr)) {
        if (isLeftChild) {
            parentNode->left = nullptr;
        }
        else {
            parentNode->right = nullptr;
        }
        // No updating of totalParentChildUpdateCost needed here
    }
    else if ((childNode != nullptr) && (parentNode == nullptr)) {
        childNode->parent = nullptr;
        // No updating of totalParentChildUpdateCost needed here
    }
    else {
        // both childNode and parentNode are nullptr
        // Nothing to do really
        // No updating of totalParentChildUpdateCost needed here
        ;
    }
    return;
}

// Constructors
AVLTree::AVLTree(int perCompCost, int perParntChldUpdCost) {
    root = nullptr;
    totalComparisonCost = 0;
    totalParentChildUpdateCost = 0;
    perComparisonCost = perCompCost;
    perParentChildUpdateCost = perParntChldUpdCost;
}

AVLTree::AVLTree(TreeNode* newRoot, int perCompCost, int perParntChldUpdCost) {
    root = newRoot;
    totalComparisonCost = 0;
    totalParentChildUpdateCost = 0;
    perComparisonCost = perCompCost;
    perParentChildUpdateCost = perParntChldUpdCost;
}

AVLTree::~AVLTree()
{
    recursiveDelete(root);
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.
bool AVLTree::insert(int jrnyCode, int price)
{
    TreeNode* new_node = new TreeNode(jrnyCode, price);
    
    TreeNode* t = nullptr;
    TreeNode* t_child = root;
        
    if (root != nullptr) {
        while (t_child != nullptr) {
            t = t_child; 
            if (AVLLessThan(new_node, t_child))
                t_child = t_child->left;
            else
                t_child = t_child->right;
        }
        
        if (AVLLessThan(new_node, t))
            t->left = new_node;
        else
            t->right = new_node;
        new_node->parent = t;
    }
    else {
        root = new_node;
        return true;
    }
    updateHeights(new_node);

    TreeNode* headGrandChild = new_node;
    if (headGrandChild->parent != nullptr) {
        TreeNode* head = headGrandChild->parent->parent;
        while (head != nullptr && (((head->left == nullptr || head->right == nullptr) && head->height <= 1) || (head->left != nullptr && head->right != nullptr && std::abs(head->left->height - head->right->height) <= 1))) {
            headGrandChild = headGrandChild->parent;
            head = head->parent;
        }
        if (head == nullptr)
            return true;
        rotate(headGrandChild);
    }
    
    return true;
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
{
    TreeNode* t = nullptr;
    TreeNode* t_child = root;

    TreeNode* sought_node = new TreeNode(jrnyCode, 0);
    while (t_child != nullptr) {
        t = t_child;
        if (AVLLessThan(sought_node, t_child))
            t_child = t_child->left;
        else {
            if (jrnyCode == t_child->JourneyCode)
                return t_child->price;
            t_child = t_child->right;
        }
    }
    return -1;
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in AVL tree with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the AVL tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::remove(int jrnyCode)
{
    // Implement deletion in AVL tree followed by balance factor restoration
    // by properly identifying x, y, z as used in Prof. Garg's lectures
    // (equivalently, currNode, parentNode, grandParentNode in our code) and
    // invoking rotateLeftLeft, rotateLeftRight, rotateRightLeft and/or
    // rotateRightRight as appropriate.

    // It is your responsibility to find out the right x, y, z (or currNode,
    // parentNode, grandParentNode) following Prof. Garg's lectures
    //
    // Once you identify these correctly, simply invoking the appropriate
    // rotation(s) should do the job.
    // You don't even need to invoke rotation twice for the double
    // rotations -- the way rotationLeftRight is implemented, and
    // rotationRightLeft should be implemented, you should be able to achieve
    // the effect of the double rotation using one invokation of the
    // appropriate member function.

    // You MUST use only AVLLessThan to compare two journey codes.    You
    // can create a new node containing the journey code to be searched
    // (along with some arbitrary price) and invoke AVLLessThan on the
    // current node in the tree that you are inspecting and the new node
    // to do your comparison.

    // REMEMBER to update the height of appropriate nodes in the tree
    // after a successful deletion.
    
    // We use "return true" below to enable compilation.    Change this as you
    // see fit.
    return true;
}
