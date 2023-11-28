#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

// Returns true on successful insertion in BST. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the BST

bool BST::insert(int jrnyCode, int price)
{
    // Implement insertion in BST

    // You MUST use only BSTLessThan to compare two journey codes.  You
    // can create a new node containing the journey code to be inserted
    // and invoke BSTLessThan on the current node in the tree that you
    // are inspecting and the new node to do your comparison.
    TreeNode *head = nullptr;
    TreeNode* next = root;
    TreeNode *newNode = new TreeNode(jrnyCode, price);
    if (next == nullptr) {
        root = newNode;
        return true;
    }
    while (next != nullptr) {
        head = next;
        if (BSTLessThan(head, newNode)) {
            next = next->right;
        }
        else {
            next = next->left;
        }
    }
    updateBSTParentChild(newNode, head, (BSTLessThan(newNode, head)));

    // REMEMBER to update the heights of appropriate nodes in the tree
    // after an insertion.
    while (head!=nullptr){
        head->height = 1 + max(getHeight(head->left), getHeight(head->right));
        head = head->parent;
    }

    // We use "return true" below to enable compilation.  Change this as you
    // see fit.
    return true;
}

TreeNode* BST::getNode(int jrnyCode){
    TreeNode* next = root;
    TreeNode* search = new TreeNode(jrnyCode, 0);
    TreeNode* head = nullptr;
    while (next!=nullptr){
        head=next;
        if (BSTLessThan(search, head)){
            next=next->left;
        }
        else if (equal(head, search)){
            return head;
        }
        else {
            next=next->right;
        }
    }
    return nullptr;
}
TreeNode* BST::twochild_successor(TreeNode* node){
    TreeNode* curr = node->right;
    TreeNode* left = curr->left;
    while(left!=nullptr){
        curr = left;
        left = left->left;
    }
    return curr;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST
int BST::find(int jrnyCode)
{
    // Implement find in BST

    // You MUST use only BSTLessThan to compare two journey codes.  You
    // can create a new node containing the journey code to be searched
    // (along with some arbitrary price) and invoke BSTLessThan on the
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

// Returns true on successful deletion of the entry in BST with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the BST have the same journey
// code, and journey code is the key for insertion and finding in the BST.

bool BST::remove(int jrnyCode)
{
    // Implement deletion in BST

    // You MUST use only BSTLessThan to compare two journey codes.  You
    // can create a new node containing the journey code to be searched
    // (along with some arbitrary price) and invoke BSTLessThan on the
    // current node in the tree that you are inspecting and the new node
    // to do your comparison.
    TreeNode* start;
    TreeNode* del = getNode(jrnyCode);
    if (del==nullptr){
        return false;
    }
    // If node has no children, simply delete the node
    if (del->right==nullptr && del->left==nullptr){
        TreeNode* p = del->parent;
        start = p;
        if (p==nullptr){root=nullptr; delete del; return true;}
        char c = (p->left==del ? 'l' : 'r');
        delete del;
        if (c=='l'){
            p->left=nullptr;
        }
        else {p->right=nullptr;}
    }

    // If the node has one child
    else if (del->right==nullptr || del->left==nullptr){
        TreeNode *p = del->parent;
        start = p;
        TreeNode *child = (del->right==nullptr ? del->left : del->right);
        if (p==nullptr){root = child; child->parent=nullptr; delete del;}
        char c = (p->left==del ? 'l' : 'r');
        delete del;
        if (c=='l'){
            p->left = child;
            child->parent = p;
        }
        else {
            p->right = child;
            child->parent = p;
        }
    }
    
    else {
        // If the node has 2 children
        TreeNode* succ = twochild_successor(del);
        // We know that succ has only a right child or no child.

        // Copying successor into the node to be deleted
        del->setjc(succ->getjc());
        del->setPrice(succ->getPrice());
        // Deleting successor, easier to delete than node which has 2 children
        TreeNode* child = succ->right; //could be nullptr
        TreeNode* succ_parent = succ->parent;
        start = succ_parent;
        if (succ_parent->left==succ){
            succ_parent->left = child;
        }
        else {
            succ_parent->right=child;
        }
        if (child!=nullptr) {child->parent = succ_parent;}
        delete succ;
        return true;
    }

    // REMEMBER to update the height of appropriate nodes in the tree
    // after a successful deletion.
    // We start at the node 'start' and move upwards, updating heights of nodes along the way
    while (start!=nullptr){
        start->height = 1 + max(getHeight(start->right), getHeight(start->left));
        start = start->parent;
    }
    // We use "return true" below to enable compilation.  Change this as you
    // see fit.

    return true;
}
