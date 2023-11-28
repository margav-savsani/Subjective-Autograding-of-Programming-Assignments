#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

// updates or rotated tree when currNode is left child of parentNode, which is left child of grandParentNode(the point of imbalance)
bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{   
    TreeNode* T = parentNode->right;
    TreeNode* greatGrandParent = grandParentNode->parent;   // stores pointer to parent of grandParentNode

    if(greatGrandParent != nullptr){
        if(grandParentNode == (greatGrandParent->left))
            updateAVLParentChild(parentNode, greatGrandParent, true);       // grandParentNode becomes the child of parentNode
        else if(grandParentNode == (greatGrandParent->right)){
            updateAVLParentChild(parentNode, greatGrandParent, false);}
        else {
            cerr << "Unexpected condition encountered!" << endl;    // handling possible errors
            return false;
        }
    }
    else {      // if greatGrandParent is a nullptr => grandParent is the root
        updateAVLParentChild(parentNode, nullptr, true);    // parent of parentNode is now the nullptr
        root = parentNode;                                  // after rotation, parentNode becomes the new root of tree
    }
    updateAVLParentChild(grandParentNode, parentNode, false);   //parentNode's right child is the grandParentNode
    updateAVLParentChild(T, grandParentNode, true);             // grandParentNode's left child is parent's initial right tree
    return true;
}

// updates or rotates tree when currNode is left child of parentNode, which is left child of grandParentNode(the point of imbalance)
bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
    TreeNode *T2 = currNode->left;
    TreeNode *T3 = currNode->right;     // need to store for later use
    TreeNode* greatGrandParent = grandParentNode->parent;   // stores pointer to parent of grandParentNode

    if(greatGrandParent != nullptr){
        if(grandParentNode == (greatGrandParent->left))
            updateAVLParentChild(currNode, greatGrandParent, true);     // currNode's parent is now the greatParentNode
        else if(grandParentNode == (greatGrandParent->right))
            updateAVLParentChild(currNode, greatGrandParent, false);
        else {
            cerr << "Unexpected condition encountered!" << endl;
            return false;
        }
    }
    else{       // if greatGrandParent is a nullptr => grandParent is the root
        updateAVLParentChild(currNode, nullptr, true);  // parent of currNode is now the nullptr
        root = currNode;                                // after rotation, currNode becomes the new root of tree
    }
    updateAVLParentChild(parentNode, currNode, true);           // parentNode is left child of currNode
    updateAVLParentChild(grandParentNode, currNode, false);     // grandParentNode is right child of currNode
    updateAVLParentChild(T2, parentNode, false);                // currNode's initial left child is right child of parentNode
    updateAVLParentChild(T3, grandParentNode, true);            // currNode's initial right child if left child of grandParentNode
    return true;
}

// updates or rotates tree when currNode is left child of parentNode, which is right child of grandParentNode(the point of imbalance)
bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
    TreeNode *T2 = currNode->right;
    TreeNode *T3 = currNode->left;      // need to store for later use
    TreeNode* greatGrandParent = grandParentNode->parent;   // stores pointer to parent of grandParentNode

    if(greatGrandParent != nullptr){
        if(grandParentNode == (greatGrandParent->left))
            updateAVLParentChild(currNode, greatGrandParent, true);     // currNode's parent is now the greatParentNode
        else if(grandParentNode == (greatGrandParent->right))
            updateAVLParentChild(currNode, greatGrandParent, false);
        else {
            cerr << "Unexpected condition encountered!" << endl;
            return false;
        }
    }
    else{       // if greatGrandParent is a nullptr => grandParent is the root
        updateAVLParentChild(currNode, nullptr, true);  // parent of currNode is now the nullptr
        root = currNode;                                // after rotation, currNode becomes the new root of tree
    }
    updateAVLParentChild(parentNode, currNode, false);          // parentNode is right child of currNode
    updateAVLParentChild(grandParentNode, currNode, true);      // grandParentNode is left child of currNode
    updateAVLParentChild(T2, parentNode, true);                 // currNode's initial right child is left child of parentNode
    updateAVLParentChild(T3, grandParentNode, false);           // currNode's initial left child if right child of grandParentNode
    return true;
}

// updates or rotated tree when currNode is right child of parentNode, which is right child of grandParentNode(the point of imbalance)
bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
    TreeNode* T = parentNode->left;
    TreeNode* greatGrandParent = grandParentNode->parent;   // stores pointer to parent of grandParentNode

    if(greatGrandParent != nullptr){
        if(grandParentNode == greatGrandParent->left)
            updateAVLParentChild(parentNode, greatGrandParent, true);       // grandParentNode becomes the child of parentNode
        else if(grandParentNode == greatGrandParent->right)
            updateAVLParentChild(parentNode, greatGrandParent, false);
        else {
            cerr << "Unexpected condition encountered!" << endl;    // handling possible errors
            return false;
        }
    }
    else{       // if greatGrandParent is a nullptr => grandParent is the root
        updateAVLParentChild(parentNode, nullptr, true);    // parent of parentNode is now the nullptr
        root = parentNode;                                  // after rotation, parentNode becomes the new root of tree
    }
    updateAVLParentChild(grandParentNode, parentNode, true);    //parentNode's left child is the grandParentNode
    updateAVLParentChild(T, grandParentNode, false);            // grandParentNode's right child is parent's initial left tree
    return true;    
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int jrnyCode, int price)
{
    if(find(jrnyCode))        // cant insert if already present
        return false;

    TreeNode *new_node, *null_node, *parent;
    new_node = new TreeNode(jrnyCode, price);
    if(root == nullptr)
        root = new_node;    // inserting the first node of empty tree
    else {                  
        parent = nullptr;
        null_node = root;
        while(null_node != nullptr) {       // finding the position for new node to be inserted
            parent = null_node;
            if(AVLLessThan(new_node, null_node))
                null_node = null_node->left;
            else
                null_node = null_node->right;
        }
        if(AVLLessThan(new_node, parent))
            parent->left = new_node;
        else
            parent->right = new_node;
        new_node->parent = parent;
        
        TreeNode* ancestor = new_node->parent;      // pointing to the ancestors of inserted node along the tree upto root
        TreeNode* son = new_node;                   // son of the ancestor along the route of root to inserted node
        TreeNode* grandson = nullptr;               // grandson of the ancestor along the route of root to inserted node
        bool balanceDone = false;                   // point of imbalance is only one during insetion, so need to check again and again
        while(ancestor != nullptr)      // traversing up until the root
        {
            // only height of nodes along th path from newNode to root can possibly change
            // and also only nodes along this path can have a possible imbalance created

            updateHeight(ancestor);     // updating height because of insertion of newNode
            if(!balanceDone){               // balancing not yet done
                if(imbalance(ancestor)){    // if an imbalance is encountered
                    ancestor = balance(grandson, son, ancestor);    // calling function to correct the imbalance
                    balanceDone = true;     // no need to check for imbalance further
            }}
            grandson = son;                 // updating the grandson to son
            son = ancestor;                 // updating the son to the present ancestor
            ancestor = ancestor->parent;    // ancestor points to next ancestor along route
        }
    }
    return true;    // insertion succesful
}

// returns 1 if found, 0 if not found

int AVLTree::find(int jrnyCode)
{
    TreeNode* dummy = new TreeNode(jrnyCode, 0);    // holds the value of JourneyCode to compare between two TreeNodes
                                                    // since JourneyCode is a private variable and can be compared only by a function
    TreeNode* node = root;
    while(node != nullptr) {
        if(AVLLessThan(dummy, node))
            node = node->left;
        else if(AVLLessThan(node, dummy))
            node = node->right;
        else
            return 1;       // node found
    }
    return 0;               // node not found
}

// checks if the given node has a possible imbalance
bool AVLTree::imbalance(TreeNode* node)
{
    if(node == nullptr)     // nothing to check
        return false;
    
    if(node->left == nullptr && node->right == nullptr)     // imbalance not possible
        return 0;
    if(node->left == nullptr)                               // imbalance if non-null tree has height greater than 0
        return node->right->height >= 1;
    if(node->right == nullptr)
        return node->left->height >= 1;                     // imbalance if non-null tree has height greater than 0

    return abs(node->left->height - node->right->height) > 1;   // imbalance if heights of the 2 children differ by more than 1
}

// checks the positions of the grandson, son, and ancestor
// and calls appropriate functions to correct the imbalance based on relative positioning

TreeNode* AVLTree::balance(TreeNode* x, TreeNode* y, TreeNode* z)
{
    if(z->left != nullptr){
        if(x == (z->left->left))
        {
            rotateLeftLeft(x,y,z);
            updateHeight(x);
            updateHeight(z);
            updateHeight(y);    // y needs to be updated last as x and z are children of it
            return y;           // ancestor needs to be updated from this point onwards
        }
        if(x == (z->left->right))
        {
            rotateLeftRight(x,y,z);
            updateHeight(y);
            updateHeight(z);
            updateHeight(x);    // x needs to be updated last as y and z are children of it
            return x;           // ancestor needs to be updated from this point onwards
        }
    }
    if(z->right != nullptr){
        if(x == (z->right->left))
        {
            rotateRightLeft(x,y,z);
            updateHeight(y);
            updateHeight(z);
            updateHeight(x);    // x needs to be updated last as y and z are children of it
            return x;           // ancestor needs to be updated from this point onwards
        }
        if(x == (z->right->right))
        {
            rotateRightRight(x,y,z);
            updateHeight(x);
            updateHeight(z);
            updateHeight(y);    // y needs to be updated last as x and z are children of it
            return y;           // ancestor needs to be updated from this point onwards
        }
    }
    return nullptr;
}

// updates the height of the passed node based on the heights of its children

bool AVLTree::updateHeight(TreeNode* node)
{
    if(node->left == nullptr && node->right == nullptr)     // no children so height 0
        node->height = 0;
    else if(node->left == nullptr)                          // height is 1 more then the height of non-null child
        node->height = 1 + node->right->height;
    else if(node->right == nullptr)                         // height is 1 more then the height of non-null child
        node->height = 1 + node->left->height;
    else
        node->height = 1 + max(node->left->height, node->right->height);    // height is 1 more then the max of heights of both children
    return true;
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
    TreeNode* node;
    node = find(jrnyCode, 0);   // finding with JourneyCode only

    if(!node)       // node to be deleted not present
        return false;

    TreeNode *x,*y;
    if (node->left == nullptr || node->right == nullptr)  y = node;
    else    y = successor(node);

    TreeNode* ancestor = y->parent;

    if (y->left != nullptr)     x = y->left;
    else                        x = y->right;

    if (x!=nullptr)    x->parent = y->parent;

    if (y->parent == nullptr)       root = x;
    else if (y == y->parent->left)  y->parent->left = x;
    else                            y->parent->right = x;

    if (y!=node) {              // copying entries of node into y with the help of dummy varialbe
        TreeNode dum = *y;      // since TreeNode has private variables
        dum.parent = node->parent;
        dum.right = node->right;
        dum.left = node->left;
        *node = dum;
    }

    // possible disturbances in height and balance occur along the route from deleted node to root
    // and also balancing a node doesnt imply no further balancings required up the tree, unlike insertion
    // so we keep checking for imbalance at every node, and only then update the son and grandson

    TreeNode *son, *grandson;
    while(ancestor != nullptr)      // traversing up from the node deleted to the root
    {
        updateHeight(ancestor);
        if(imbalance(ancestor)){            // if node is imbalanced
            son = newSon(ancestor);         // son points to child of ancestor with largest height
            grandson = newGrandSon(son);    // grandson points to child of son with largest height
            ancestor = balance(grandson, son, ancestor);    // balancing the tree
        }
        ancestor = ancestor->parent;        // updating the ancestor to higher ancestor
    }
    return true;
}

// finds a node based on JourneyCode and returns the pointer to it, if found
TreeNode* AVLTree::find(int JourneyCode, int price) {       // dummy price to distinguish with other find function
    TreeNode* dummy = new TreeNode(JourneyCode, price);     // holds the value of JourneyCode to compare between two TreeNodes
                                                            // since JourneyCode is a private variable and can be compared only by a function
    TreeNode* node = root;
    while(node != nullptr) {
        if(AVLLessThan(dummy, node))
            node = node->left;
        else if(AVLLessThan(node, dummy))
            node = node->right;
        else
            return node;        // node found
    }
    return nullptr;             // node not found
}

// returns the pointer to the successor of the passed node
// used when deleting a node with two non-null children

TreeNode* AVLTree::successor(TreeNode* node) {
    TreeNode* suc = node;
    if (node->right != nullptr) {
        suc = suc->right;
        while (suc->left != nullptr) 
        suc = suc->left;
        return suc;
    }
    else {
        suc = node->parent;
        while (suc!=nullptr && node==suc->right) {
            node = suc;
            suc = suc->parent;
        }
        return suc;
    }
}

// returns the son of the passed ancestor, which is the child with largest height
// used when imbalance occurs when travelling up the tree after deletion
TreeNode* AVLTree::newSon(TreeNode* ancestor)
{
    TreeNode* son;
    if(ancestor->right == nullptr)
        son = ancestor->left;
    else if(ancestor->left == nullptr)
        son = ancestor->right;
    else
        son = (ancestor->left->height > ancestor->right->height) ? ancestor->left : ancestor->right;
    return son;
}

// returns the son of the passed node, which is the child with largest height
// used when imbalance occurs when travelling up the tree after deletion
TreeNode* AVLTree::newGrandSon(TreeNode* son)
{
    TreeNode* grandson;
    if(son == nullptr)
        grandson = nullptr;
    else if(son->right == nullptr)
        grandson = son->left;
    else if(son->left == nullptr)
        grandson = son->right;
    else
        grandson = (son->left->height > son->right->height) ? son->left : son->right;
    return grandson;
}
