#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

// Recall from Prof. Naveen Garg's lectures how the various rotations are
// applied to restore the balance factor at all nodes of an AVL tree
// to either 0, 1 or -1, after an insert or delete.
// The correspondence between the terminology in Prof. Garg's lectures and
// our terminology in this code is as follows:
//
// Prof. Garg's lectures           Our code
// ---------------------           --------
//   x                             currNode
//   y                             parentNode
//   z                             grandParentNode
//
// Recall also that z (grandParentNode) is the lowest node in the path from
// the root to the inserted node or to the deleted node (as the case may be)
// where the balance factor has either become < -1 or > 1.
// To find what x (currNode) and y (parentNode) should be, you need to
// recall Prof. Garg's lectures.
// These are slightly differently defined when inserting nodes and when
// deleting nodes

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
    // Going back to Prof. Naveen Garg's lecture, x is *currNode,
    // y is *parentNode and z is *grandParentNode

    // Moreover, currNode is the left child of parentNode, and
    // parentNode is the left child of grandParentNode
    // That's why we are doing a rotateLeftLeft

    TreeNode *greatGrandParentNode = grandParentNode->parent;

    // First find if grandParentNode is the left or right child of
    // greatGrandParentNode

    bool isGPLeftChild;
    if (greatGrandParentNode!=nullptr){
        if (greatGrandParentNode->left == grandParentNode)
        {
            isGPLeftChild = true;
        }
        else if (greatGrandParentNode->right == grandParentNode)
        {
            isGPLeftChild = false;
        }
        else
        {
            cerr << "Unexpected condition encountered!" << endl;
            return false;
        }
    }

    // Let T3 be the right child of parentNode (i.e. of y, using notation
    // from Prof. Garg's lectures
    TreeNode *T3 = parentNode->right;

    // Now replicate the single rotation for LeftLeft as from the lecture
    // notes/video using *ONLY* calls to updateAVLParentChild

    // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
    // child of greatGrandParentNode
    if (greatGrandParentNode!=nullptr){
        updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
    }
    else {
        root = parentNode;
        parentNode->parent = nullptr;
    }

    // Make currNode (x in Prof. Garg's lectures) the left child of
    // parentNode (y in Prof. Garg's lectures)
    // The last parameter is "true" to indicate that currNode should be
    // made the left child of parentNode
    updateAVLParentChild(currNode, parentNode, true);

    // Make grandParentNode (z in Prof. Garg's lectures) the right child of
    // parentNode (y in Prof. Garg's lectures)
    // The last parameter is "false" to indicate that grandParentNode
    // should NOT be made the left child of parentNode
    updateAVLParentChild(grandParentNode, parentNode, false);

    // Recall from Prof. Garg's lectures that the left and right subtrees
    // of currNode (i.e. x in Prof. Garg's lectures) stay unchanged after
    // the LeftLeft rotation.  So do don't need to update the children of
    // currNode at all.
    // Similarly, the right subtree of grandParentNode (i.e. z in Prof.
    // Garg's lectures) stays unchanged.  Hence, the right child of
    // grandParentNode doesn't need to be updated at all.
    // The only update needed is that the right subtree of parentNode (i.e.
    // y in Prof. Garg's notes) should now become the left
    // child of grandParentNode (i.e. of z in Prof. Garg's notes).

    // We use "true" as the third argument of the following call to indicate
    // that T3 should become the left child of grandParentNode
    updateAVLParentChild(T3, grandParentNode, true);

    return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
    // Going back to Prof. Naveen Garg's lecture, x is *currNode,
    // y is *parentNode and z is *grandParentNode

    // Moreover, currNode is the right child of parentNode, and
    // parentNode is the left child of grandParentNode.  That's
    // why we are doing a rotateLeftRight

    TreeNode *greatGrandParentNode = grandParentNode->parent;

    // First find if grandParentNode is the left or right child of
    // greatGrandParentNode

    bool isGPLeftChild;
    if (greatGrandParentNode!=nullptr){
        if (greatGrandParentNode->left == grandParentNode)
        {
            isGPLeftChild = true;
        }
        else if (greatGrandParentNode->right == grandParentNode)
        {
            isGPLeftChild = false;
        }
        else
        {
            cerr << "Unexpected condition encountered!" << endl;
            return false;
        }
    }

    // Now replicate the double rotation for LeftRight as from the lecture
    // notes/video using *ONLY* calls to updateAVLParentChild
    //
    // We can directly implement the double rotation, instead of doing two
    // rotations sequentially.  So we'll look at the end-result of the
    // double rotation (refer Prof. Garg's lecture notes) and arrive at that
    // from the original tree.

    // Make currNode (x in Prof. Naveen Garg's lectures) the appropriate
    // child of greatGrandParentNode
    if (greatGrandParentNode!=nullptr){
        updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
    }
    else {
        root = currNode;
        currNode->parent = nullptr;
    }
    // Let T2 be the left child of currNode (i.e. of x)
    TreeNode *T2 = currNode->left;

    // Let T3 be the right child of currNode (i.e. of x)
    TreeNode *T3 = currNode->right;

    // Make parentNode (y in Prof. Garg's lectures) the left child of
    // currNode (x in Prof. Garg's lectures)
    // The last parameter is "true" to indicate that parentNode should be
    // made the left child of currNode
    updateAVLParentChild(parentNode, currNode, true);

    // Make grandParentNode (z in Prof. Garg's lectures) the right child of
    // currNode (x in Prof. Garg's lectures)
    // The last parameter is "false" to indicate that grandParentNode
    // should NOT be made the left child of currNode
    updateAVLParentChild(grandParentNode, currNode, false);

    // Recall from Prof. Garg's lectures that the left subtree of
    // parentNode (i.e. y in Prof. Garg's lectures) and right subtree of
    // grandParentNode (i.e. z in Prof. Garg's lectures) stay unchanged
    // after the LeftRight rotation.  So do don't need to update the
    // left child of parentNode and the right child of grandParentNode
    // at all.
    // The only update needed is that the left subtree of currNode (i.e.
    // x in Prof. Garg's notes) should now become the right subtree of
    // parentNode (y in Prof. Garg's notes).  Similarly, the right subtree
    // of currNode (i.e. of x) should now become the left subtree of
    // grandParentNode (i.e. of z).

    // Let's implement these updations below.

    // We use "false" as the third argument of the following call to indicate
    // that T2 should NOT become the left child of ParentNode
    updateAVLParentChild(T2, parentNode, false);

    // We use "true" as the third argument of the following call to indicate
    // that T3 should become the left child of grandParentNode
    updateAVLParentChild(T3, grandParentNode, true);

    return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{

    TreeNode *greatGrandParentNode = grandParentNode->parent;

    bool isGPLeftChild;
    if (greatGrandParentNode!=nullptr){
        if (greatGrandParentNode->left == grandParentNode)
        {
            isGPLeftChild = true;
        }
        else if (greatGrandParentNode->right == grandParentNode)
        {
            isGPLeftChild = false;
        }
        else
        {
            cerr << "Unexpected condition encountered!" << endl;
            return false;
        }
    }

    // Make currNode (x in Prof. Naveen Garg's lectures) the appropriate
    // child of greatGrandParentNode
    if (greatGrandParentNode!=nullptr){
        updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
    }
    else {
        root = currNode;
        currNode->parent = nullptr;
    }
    // Let T2 be the left child of currNode (i.e. of x)
    TreeNode *T2 = currNode->right;

    // Let T3 be the right child of currNode (i.e. of x)
    TreeNode *T1 = currNode->left;

    updateAVLParentChild(parentNode, currNode, false);

    updateAVLParentChild(grandParentNode, currNode, true);

    updateAVLParentChild(T2, parentNode, true);

    updateAVLParentChild(T1, grandParentNode, false);

    return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
    // Going back to Prof. Naveen Garg's lecture, x is *currNode,
    // y is *parentNode and z is *grandParentNode

    // Moreover, currNode is the left child of parentNode, and
    // parentNode is the left child of grandParentNode
    // That's why we are doing a rotateLeftLeft

    TreeNode *greatGrandParentNode = grandParentNode->parent;

    // First find if grandParentNode is the left or right child of
    // greatGrandParentNode

    bool isGPLeftChild;
    if (greatGrandParentNode!=nullptr){
        if (greatGrandParentNode->left == grandParentNode)
        {
            isGPLeftChild = true;
        }
        else if (greatGrandParentNode->right == grandParentNode)
        {
            isGPLeftChild = false;
        }
        else
        {
            cerr << "Unexpected condition encountered!" << endl;
            return false;
        }
    }

    // Let T3 be the right child of parentNode (i.e. of y, using notation
    // from Prof. Garg's lectures
    TreeNode *T3 = parentNode->left;

    // Now replicate the single rotation for LeftLeft as from the lecture
    // notes/video using *ONLY* calls to updateAVLParentChild

    // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
    // child of greatGrandParentNode
    if (greatGrandParentNode!=nullptr){
        updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
    }
    else {
        root = parentNode;
        parentNode->parent = nullptr;
    }

    // Make currNode (x in Prof. Garg's lectures) the left child of
    // parentNode (y in Prof. Garg's lectures)
    // The last parameter is "true" to indicate that currNode should be
    // made the left child of parentNode
    updateAVLParentChild(currNode, parentNode, false);

    // Make grandParentNode (z in Prof. Garg's lectures) the right child of
    // parentNode (y in Prof. Garg's lectures)
    // The last parameter is "false" to indicate that grandParentNode
    // should NOT be made the left child of parentNode
    updateAVLParentChild(grandParentNode, parentNode, true);

    // Recall from Prof. Garg's lectures that the left and right subtrees
    // of currNode (i.e. x in Prof. Garg's lectures) stay unchanged after
    // the LeftLeft rotation.  So do don't need to update the children of
    // currNode at all.
    // Similarly, the right subtree of grandParentNode (i.e. z in Prof.
    // Garg's lectures) stays unchanged.  Hence, the right child of
    // grandParentNode doesn't need to be updated at all.
    // The only update needed is that the right subtree of parentNode (i.e.
    // y in Prof. Garg's notes) should now become the left
    // child of grandParentNode (i.e. of z in Prof. Garg's notes).

    // We use "true" as the third argument of the following call to indicate
    // that T3 should become the left child of grandParentNode
    updateAVLParentChild(T3, grandParentNode, false);

    return true;

}

int getImbalance(TreeNode* T){
    return abs(getHeight(T->left) - getHeight(T->right));
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.
bool AVLTree::insert(int jrnyCode, int price)
{
    // Implement insertion in AVL tree followed by balance factor restoration
    // by properly identifying x, y, z as used in Prof. Garg's lectures
    // (equivalently, currNode, parentNode, grandParentNode in our code) and
    // invoking rotateLeftLeft, rotateLeftRight, rotateRightLeft and/or
    // rotateRightRight as appropriate.

    TreeNode *head = nullptr;
    TreeNode* next = root;
    TreeNode *newNode = new TreeNode(jrnyCode, price);
    if (next == nullptr) {
        root = newNode;
        return true;
    }
    while (next != nullptr) {
        head = next;
        if (AVLLessThan(newNode, head)) {
            next = next->left;
        }
        else {
            next = next->right;
        }
    }
    updateAVLParentChild(newNode, head, (AVLLessThan(newNode, head)));

    // It is your responsibility to find out the right x, y, z (or currNode,
    // parentNode, grandParentNode) following Prof. Garg's lectures
    //
    TreeNode *x, *y, *z;
    x = newNode;
    y = head;
    z = head->parent;
    /* If insertion causes T to become unbalanced, we
    travel up the tree from the newly created node until
    we find the first node x such that its grandparent z
    is unbalanced node.
    */
    while (z!=nullptr){
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        z->height = 1+ max(getHeight(z->right), getHeight(z->left));
        if (getImbalance(z)>1){
            break;
        }
        x=y;
        y=z;
        z = z->parent;
    }
    if (z==nullptr){
        return true;
    }
    // Once you identify these correctly, simply invoking the appropriate
    // rotation should do the job.
    // You don't even need to invoke rotation twice for the double
    // rotations -- the way rotationLeftRight is implemented, and
    // rotationRightLeft should be implemented, you should be able to achieve
    // the effect of the double rotation using one invokation of the
    // appropriate member function.
    bool dir;
    if (z->right==y && y->right==x){
        dir = 0;
        rotateRightRight(x, y, z);
    }
    else if (z->right==y && y->left==x){
        dir = 1;
        rotateRightLeft(x, y, z);
    }
    else if (z->left==y && y->right==x){
        dir = 1;
        rotateLeftRight(x, y, z);
    }
    else if (z->left==y && y->left==x){
        dir = 0;
        rotateLeftLeft(x, y, z);
    }
    
    // You MUST use only AVLLessThan to compare two journey codes.  You
    // can create a new node containing the journey code to be inserted
    // and invoke AVLLessThan on the current node in the tree that you
    // are inspecting and the new node to do your comparison.

    // REMEMBER to update the heights of appropriate nodes in the tree
    // after an insertion.
    if (dir){
        // x goes from h+2 to h+3
        // y goes from h+3 to h+2
        // z goes from h+4 to h+2
        x->height+=1;
        y->height-=1;
        z->height-=2;
    }
    else {
        // z height goes form h+4 to h+2, rest all are same
        z->height-=2;
    }
    // We use "return true" below to enable compilation.  Change this as you
    // see fit.
    return true;
}
TreeNode* AVLTree::getNode(int jrnyCode){
    TreeNode* search = new TreeNode(jrnyCode, 0);
    TreeNode* head = root;
    while (head!=nullptr){
        if (AVLLessThan(search, head)){
            head=head->left;
        }
        else if (equal(head, search)){
            return head;
        }
        else {
            head=head->right;
        }
    }
    return nullptr;
}
TreeNode* AVLTree::twochild_successor(TreeNode* node){
    TreeNode* curr = node->right;
    TreeNode* left = curr->left;
    while(left!=nullptr){
        curr = left;
        left = left->left;
    }
    return curr;
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.
int AVLTree::find(int jrnyCode)
{
    // Implement find in AVL tree.
    // This is really no different from finding in a binary search tree.
    // This operation cannot cause any balance factor disturbances.

    // You MUST use only AVLLessThan to compare two journey codes.  You
    // can create a new node containing the journey code to be searched
    // (along with some arbitrary price) and invoke AVLLessThan on the
    // current node in the tree that you are inspecting and the new node
    // to do your comparison.
    TreeNode* head = getNode(jrnyCode);
    if (head==nullptr){
        return -1;
    }
    else {
        return head->getPrice();
    }
    // We use "return -1" below to enable compilation.  Change this as you
    // see fit.
    return -1;
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

void AVLTree::rebalance(TreeNode* w){
    TreeNode *z, *y, *x;
    z = w;
    while (z!=nullptr){
        z->height = 1 + max(getHeight(z->right), getHeight(z->left));
        if (getImbalance(z)>1){
            y = (getHeight(z->right) > getHeight(z->left) ? z->right : z->left );
            x = (getHeight(y->right) > getHeight(y->left) ? y->right : y->left );
            break;
        }
        z = z->parent;
    }
    if (z==nullptr){
        return;
    }
    if (z->left==y && y->left==x){
        rotateLeftLeft(x, y, z);
    }
    if (z->right==y && y->right==x){
        rotateRightRight(x, y, z);
    }
    if (z->left==y && y->right==x){
        rotateLeftRight(x, y, z);
    }
    if (z->right==y && y->left==x){
        rotateRightLeft(x, y, z);
    }
    rebalance(x);
}

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
    TreeNode* del = getNode(jrnyCode);
    if (del==nullptr){
        return false;
    }
    TreeNode* z;
    // If node has no children, simply delete the node
    if (del->right==nullptr && del->left==nullptr){
        TreeNode* p = del->parent;
        z = p;
        if (p==nullptr){root=nullptr; delete del;}
        else {
            char c = (p->left==del ? 'l' : 'r');
            delete del;
            if (c=='l'){
                p->left=nullptr;
            }
            else {p->right=nullptr;}
        }
    }
    // If the node has one child
    // In an AVL tree, such a node will have a leaf as its child
    else if (del->right==nullptr || del->left==nullptr){
        z = del;
        TreeNode *child = (del->right==nullptr ? del->left : del->right);
        // child is a leaf
        del->setjc(child->getjc());
        del->setPrice(child->getPrice());
        delete child;
        del->right = nullptr; del->left = nullptr;
    }

    else {
        // If the node has 2 children
        TreeNode* succ = twochild_successor(del);
        // We know that succ has only a right child or no child.

        // Copying successor into the node to be deleted
        del->setjc(succ->getjc());
        del->setPrice(succ->getPrice());
        // Deleting successor, easier to delete than node which has 2 children
        TreeNode* child = succ->right; //could be nullptr, or a leaf
        if (child==nullptr){
            bool isleft = (succ->parent->left==succ ? 1 : 0);
            z = succ->parent;
            delete succ;
            if (isleft){
                succ->parent->left=nullptr;
            }
            else {succ->parent->right=nullptr;}
        }
        else {
            // Copy child into succ, delete child
            z = succ;
            succ->setjc(child->getjc());
            succ->setPrice(child->getPrice());
            delete child;
            succ->right = nullptr;
        }
    }

    // It is your responsibility to find out the right x, y, z (or currNode,
    // parentNode, grandParentNode) following Prof. Garg's lectures
    rebalance(z);
    // Once you identify these correctly, simply invoking the appropriate
    // rotation(s) should do the job.
    // You don't even need to invoke rotation twice for the double
    // rotations -- the way rotationLeftRight is implemented, and
    // rotationRightLeft should be implemented, you should be able to achieve
    // the effect of the double rotation using one invokation of the
    // appropriate member function.

    // You MUST use only AVLLessThan to compare two journey codes.  You
    // can create a new node containing the journey code to be searched
    // (along with some arbitrary price) and invoke AVLLessThan on the
    // current node in the tree that you are inspecting and the new node
    // to do your comparison.

    // REMEMBER to update the height of appropriate nodes in the tree
    // after a successful deletion.

    // We use "return true" below to enable compilation.  Change this as you
    // see fit.
    return true;
}
