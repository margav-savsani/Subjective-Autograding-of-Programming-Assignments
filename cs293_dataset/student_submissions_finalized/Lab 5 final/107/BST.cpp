#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif



// updates height of nodes up the tree starting at parentOfCurrNode
void BST::updateBSTheight(TreeNode *parentOfCurrNode)
{
  while (parentOfCurrNode!=nullptr)
  {
    // moving up to root... updating height
    if(parentOfCurrNode->left==nullptr && parentOfCurrNode->right==nullptr)
    {
      // no child i.e leaf
      parentOfCurrNode->height=0;
    }
    else if(parentOfCurrNode->left==nullptr)
    {
      // only right child is present
      parentOfCurrNode->height=((parentOfCurrNode->right)->height) + 1;
    }
    else if(parentOfCurrNode->right==nullptr)
    {
      // only left child is present
      parentOfCurrNode->height=((parentOfCurrNode->left)->height) + 1;
    }
    else
    {
      // both left and right children are present, then height is maximum of height of them + 1
      parentOfCurrNode->height=max((parentOfCurrNode->left)->height, (parentOfCurrNode->right)->height) + 1;
    }
    parentOfCurrNode=parentOfCurrNode->parent;  // move control up the tree
  }
}


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

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.

  // We use "return true" below to enable compilation.  Change this as you
  // see fit.



  TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  TreeNode *toinsert = new TreeNode(jrnyCode, price);

  if(root==nullptr)
  {
    // no root present
    root= toinsert;
    root->height=0;
    return true;
  }

  while (currNode != nullptr) {
    if (BSTLessThan(currNode, toinsert)) {
      // go right the tree
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }
    else if (BSTLessThan(toinsert, currNode)) {
      // go left the tree
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
    else { // currNode->JourneyCode == JourneyCode
      return false;
    }
  }
  if(BSTLessThan(toinsert, parentOfCurrNode))
  {
    // left insert
    updateBSTParentChild(toinsert, parentOfCurrNode, true);
    (parentOfCurrNode->left)->height=0;
  }
  else
  {
    // right insert
    updateBSTParentChild(toinsert, parentOfCurrNode, false);
    (parentOfCurrNode->right)->height=0;
  }
  updateBSTheight(parentOfCurrNode);  // Update height up the tree
  return true;
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

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.

  TreeNode *tofind = new TreeNode(jrnyCode, 0);
  TreeNode *currNode = root;
  while(currNode!=nullptr)
  {
    if(BSTLessThan(tofind , currNode))  // go left the tree
      currNode=currNode->left;
    else if(BSTLessThan(currNode, tofind))  // go right the tree
      currNode=currNode->right;
    else  // this is required node
      return currNode->getPrice();
  }
  return -1;  // not found
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in BST with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the BST have the same journey
// code, and journey code is the key for insertion and finding in the BST.

TreeNode* BST::getMinimumNode(TreeNode* curr)
{
	// Minimum jc node is the leftmost node in the BST
	if(curr==nullptr)
		return nullptr;
	if(curr->left==nullptr)
		return curr;	// This will be leftmost node
	return getMinimumNode(curr->left);
}

bool BST::remove(int jrnyCode)
{
  // Implement deletion in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // REMEMBER to update the height of appropriate nodes in the tree
  // after a successful deletion.

  // We use "return true" below to enable compilation.  Change this as you
  // see fit.

  TreeNode *todelete = new TreeNode(jrnyCode, 0);
  TreeNode *currNode = root;
  while(currNode!=nullptr)
  {
    if(BSTLessThan(todelete, currNode))  // go left the tree
      currNode=currNode->left;
    else if(BSTLessThan(currNode, todelete))  // go rightt the tree
      currNode=currNode->right;
    else  // this is node to remove
    {
      TreeNode* toremove= currNode;
      // Root remove cases
    	if(toremove==root && root->right==nullptr && root->left==nullptr) // No child
    	{
    		root=nullptr;
    		return true;
    	}
    	else if(toremove==root && root->right==nullptr)  // Only left child which becomes new root
    	{
    		root=toremove->left;
    		root->parent=nullptr;
    		return true;
    	}
    	else if(toremove==root && root->left==nullptr)	// Only right child which becomes new root
    	{
    		root=toremove->right;
    		root->parent=nullptr;
    		return true;
    	}
    	else if(toremove==root)	// Both left and right child
    	{
    		TreeNode* successor= getMinimumNode(toremove->right); // This will be new root
    		int jc= successor->getJourneyCode();
    		int pc= successor->getPrice();
    		this->remove(jc);  // successor will be removed from it's place
        int ht= root->height;
    		TreeNode* newRoot= new TreeNode(jc, pc);
        // make apt parent child updates
        updateBSTParentChild(root->left, newRoot, true);
        updateBSTParentChild(root->right, newRoot, false);
        // new root set
        root=newRoot;
        root->height=ht;
    		return true;
    	}

    	// Not root remove cases
    	if(toremove->right==nullptr && toremove->left==nullptr) // No child
    	{
        // make apt child of toremove->parent nullptr
    		if((toremove->parent)->right == toremove)
    			(toremove->parent)->right = nullptr;
    		else
    			(toremove->parent)->left = nullptr;
        updateBSTheight(toremove->parent);  // Update height up the tree
        return true;
    	}
    	else if(toremove->right==nullptr)  // Only left child
    	{
        // make toremove->left to be apt child of toremove->parent
    		if((toremove->parent)->right == toremove)
    			updateBSTParentChild(toremove->left, toremove->parent, false);
    		else
    			updateBSTParentChild(toremove->left, toremove->parent, true);
        updateBSTheight(toremove->parent);  // Update height up the tree
    		return true;
    	}
    	else if(toremove->left==nullptr)  // Only right child
    	{
        // make toremove->right to be apt child of toremove->parent
        if((toremove->parent)->right == toremove)
    			updateBSTParentChild(toremove->right, toremove->parent, false);
    		else
    			updateBSTParentChild(toremove->right, toremove->parent, true);
        updateBSTheight(toremove->parent);  // Update height up the tree
    		return true;
    	}
    	else  // Both left and right child
    	{
        TreeNode* successor= getMinimumNode(toremove->right); // This will be node to replace
    		int jc= successor->getJourneyCode();
    		int pc= successor->getPrice();
    		this->remove(jc);  // successor will be removed from it's place
        int ht= toremove->height;
    		TreeNode* newNode= new TreeNode(jc, pc);
        // make apt parent child updates
        updateBSTParentChild(toremove->left, newNode, true);
        updateBSTParentChild(toremove->right, newNode, false);
        // make newNode apt child of toremove->parent
        if((toremove->parent)->left == toremove)
          updateBSTParentChild(newNode, toremove->parent, true);
        else
          updateBSTParentChild(newNode, toremove->parent, false);
        newNode->height=ht;
    		return true;
    	}
      return false;
    }
  }
  return false;
}
