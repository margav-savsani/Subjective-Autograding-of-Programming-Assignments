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
  if(greatGrandParentNode==nullptr)
  {
    // if our grandParentNode is root
    // parentNode becomes new root
    parentNode->parent=nullptr;
    root=parentNode;
  }
  else
  {
    // First find if grandParentNode is the left or right child of
    // greatGrandParentNode

    bool isGPLeftChild;
    if (greatGrandParentNode->left == grandParentNode) {
      isGPLeftChild = true;
    }
    else if (greatGrandParentNode->right == grandParentNode) {
      isGPLeftChild = false;
    }
    else {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }

    // Now replicate the single rotation for LeftLeft as from the lecture
    // notes/video using *ONLY* calls to updateAVLParentChild

    // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
    // child of greatGrandParentNode
    updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  }


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

  // Let T3 be the right child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures
  TreeNode *T3 = parentNode->right;

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T3, grandParentNode, true);

  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of parentNode
  updateAVLParentChild(grandParentNode, parentNode, false);

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
  if(greatGrandParentNode==nullptr)
  {
    // if our grandParentNode is root
    // currNode becomes new root
    currNode->parent=nullptr;
    root=currNode;
  }
  else
  {
    // First find if grandParentNode is the left or right child of
    // greatGrandParentNode

    bool isGPLeftChild;
    if (greatGrandParentNode->left == grandParentNode) {
      isGPLeftChild = true;
    }
    else if (greatGrandParentNode->right == grandParentNode) {
      isGPLeftChild = false;
    }
    else {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
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
    updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  }


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

  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;

  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;

  // We use "false" as the third argument of the following call to indicate
  // that T2 should NOT become the left child of ParentNode
  updateAVLParentChild(T2, parentNode, false);

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T3, grandParentNode, true);


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

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Implement this yourself
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the left child of parentNode, and
  // parentNode is the right child of grandParentNode.  That's
  // why we are doing a rotateRightLeft

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  if(greatGrandParentNode==nullptr)
  {
    // if our grandParentNode is root
    // currNode becomes new root
    currNode->parent=nullptr;
    root=currNode;
  }
  else
  {
    // First find if grandParentNode is the left or right child of
    // greatGrandParentNode

    bool isGPLeftChild;
    if (greatGrandParentNode->left == grandParentNode) {
      isGPLeftChild = true;
    }
    else if (greatGrandParentNode->right == grandParentNode) {
      isGPLeftChild = false;
    }
    else {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }

    // Now replicate the double rotation for RightLeft as from the lecture
    // notes/video using *ONLY* calls to updateAVLParentChild
    //
    // We can directly implement the double rotation, instead of doing two
    // rotations sequentially.  So we'll look at the end-result of the
    // double rotation (refer Prof. Garg's lecture notes) and arrive at that
    // from the original tree.

    // Make currNode (x in Prof. Naveen Garg's lectures) the appropriate
    // child of greatGrandParentNode
    updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  }


  // Recall from Prof. Garg's lectures that the right subtree of
  // parentNode (i.e. y in Prof. Garg's lectures) and left subtree of
  // grandParentNode (i.e. z in Prof. Garg's lectures) stay unchanged
  // after the RightLeft rotation.  So do don't need to update the
  // right child of parentNode and the left child of grandParentNode
  // at all.
  // The only update needed is that the right subtree of currNode (i.e.
  // x in Prof. Garg's notes) should now become the left subtree of
  // parentNode (y in Prof. Garg's notes).  Similarly, the left subtree
  // of currNode (i.e. of x) should now become the right subtree of
  // grandParentNode (i.e. of z).

  // Let's implement these updations below.

  // Let T2 be the right child of currNode (i.e. of x)
  TreeNode *T2 = currNode->right;

  // Let T3 be the left child of currNode (i.e. of x)
  TreeNode *T3 = currNode->left;

  // We use "true" as the third argument of the following call to indicate
  // that T2 should become the left child of ParentNode
  updateAVLParentChild(T2, parentNode, true);

  // We use "false" as the third argument of the following call to indicate
  // that T3 should NOT become the left child of grandParentNode
  updateAVLParentChild(T3, grandParentNode, false);


  // Make parentNode (y in Prof. Garg's lectures) the right child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that parentNode should NOT be
  // made the left child of currNode
  updateAVLParentChild(parentNode, currNode, false);

  // Make grandParentNode (z in Prof. Garg's lectures) the left child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that grandParentNode
  // should be made the left child of currNode
  updateAVLParentChild(grandParentNode, currNode, true);


  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Implement this yourself
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the right child of parentNode, and
  // parentNode is the right child of grandParentNode
  // That's why we are doing a rotateRightRight

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  if(greatGrandParentNode==nullptr)
  {
    // if our grandParentNode is root
    // parentNode becomes new root
    parentNode->parent=nullptr;
    root=parentNode;
  }
  else
  {
    // First find if grandParentNode is the left or right child of
    // greatGrandParentNode

    bool isGPLeftChild;
    if (greatGrandParentNode->left == grandParentNode) {
      isGPLeftChild = true;
    }
    else if (greatGrandParentNode->right == grandParentNode) {
      isGPLeftChild = false;
    }
    else {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }

    // Now replicate the single rotation for RightRight as from the lecture
    // notes/video using *ONLY* calls to updateAVLParentChild

    // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
    // child of greatGrandParentNode
    updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  }


  // Recall from Prof. Garg's lectures that the left and right subtrees
  // of currNode (i.e. x in Prof. Garg's lectures) stay unchanged after
  // the RightRight rotation.  So you don't need to update the children of
  // currNode at all.
  // Similarly, the left subtree of grandParentNode (i.e. z in Prof.
  // Garg's lectures) stays unchanged.  Hence, the left child of
  // grandParentNode doesn't need to be updated at all.
  // The only update needed is that the left subtree of parentNode (i.e.
  // y in Prof. Garg's notes) should now become right
  // child of grandParentNode (i.e. of z in Prof. Garg's notes).

  // Let T3 be the left child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures
  TreeNode *T3 = parentNode->left;

  // We use "false" as the third argument of the following call to indicate
  // that T3 should NOT become the left child of grandParentNode
  updateAVLParentChild(T3, grandParentNode, false);


  // Make grandParentNode (z in Prof. Garg's lectures) the left child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that grandParentNode
  // should be made the left child of parentNode
  updateAVLParentChild(grandParentNode, parentNode, true);

  return true;
}

// updates height of the node passed
void AVLTree::updateAVLsingleheight(TreeNode* node)
{
  if(node->left==nullptr && node->right==nullptr)
  {
    // no child i.e leaf
    node->height=0;
  }
  else if(node->left==nullptr)
  {
    // only right child is present
    node->height=((node->right)->height) + 1;
  }
  else if(node->right==nullptr)
  {
    // only left child is present
    node->height=((node->left)->height) + 1;
  }
  else
  {
    // both left and right children are present, then height is maximum of height of them + 1
    node->height=max((node->left)->height, (node->right)->height) + 1;
  }
}

// updates height of nodes up the tree starting at parentOfCurrNode
TreeNode* AVLTree::updateAVLheight(TreeNode *parentOfCurrNode)
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
      if((parentOfCurrNode->right)->height>0) // height imbalance since left is at height -1 i.e. nullptr
        return parentOfCurrNode;
    }
    else if(parentOfCurrNode->right==nullptr)
    {
      // only left child is present
      parentOfCurrNode->height=((parentOfCurrNode->left)->height) + 1;
      if((parentOfCurrNode->left)->height>0) // height imbalance since right is at height -1 i.e. nullptr
        return parentOfCurrNode;
    }
    else
    {
      // both left and right children are present, then height is maximum of height of them + 1
      parentOfCurrNode->height=max((parentOfCurrNode->left)->height, (parentOfCurrNode->right)->height) + 1;
      if(abs((parentOfCurrNode->left)->height - (parentOfCurrNode->right)->height) > 1)  // height imbalance
        return parentOfCurrNode;
    }
    parentOfCurrNode=parentOfCurrNode->parent;  // move control up the tree
  }
  return nullptr; // No imbalance found
}

// rotates at passed node according to what situation demands
void AVLTree::rotate(TreeNode *z)
{
  if(z!=nullptr)
  {
    int rot=0; // rotation specifier LeftLeft==0, LeftRight==1, RightLeft==2, RightRight==3
    TreeNode *x,*y;
    if(z->left==nullptr)  // only right is present
    {
      rot+=2;
      y=z->right;
    }
    else if(z->right==nullptr)  // only left is present
      y=z->left;
    else
    {
      if((z->left)->height==z->height-1)  // this means left has height >= right's height
      {
        y=z->left;
      }
      else  // this means left has height < right's height
      {
        rot+=2;
        y=z->right;
      }
    }
    if(y->left==nullptr)  // only right is present
    {
      rot+=1;
      x=y->right;
    }
    else if(y->right==nullptr)  // only left is present
      x=y->left;
    else
    {
      if((y->left)->height==y->height-1)  // this means left has height >= right's height
      {
        x=y->left;
      }
      else  // this means left has height < right's height
      {
        rot+=1;
        x=y->right;
      }
    }
    switch(rot)
    {
      case 0: // height of x doesn't change
      rotateLeftLeft(x, y, z);
      updateAVLsingleheight(z);
      updateAVLsingleheight(y);
      break;
      case 1:
      rotateLeftRight(x, y, z);
      updateAVLsingleheight(y);
      updateAVLsingleheight(z);
      updateAVLsingleheight(x);
      break;
      case 2:
      rotateRightLeft(x, y, z);
      updateAVLsingleheight(y);
      updateAVLsingleheight(z);
      updateAVLsingleheight(x);
      break;
      case 3: // height of x doesn't change
      rotateRightRight(x, y, z);
      updateAVLsingleheight(z);
      updateAVLsingleheight(y);
      break;
    }
  }
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

  // It is your responsibility to find out the right x, y, z (or currNode,
  // parentNode, grandParentNode) following Prof. Garg's lectures
  //
  // Once you identify these correctly, simply invoking the appropriate
  // rotation should do the job.
  // You don't even need to invoke rotation twice for the double
  // rotations -- the way rotationLeftRight is implemented, and
  // rotationRightLeft should be implemented, you should be able to achieve
  // the effect of the double rotation using one invokation of the
  // appropriate member function.

  // You MUST use only AVLLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke AVLLessThan on the current node in the tree that you
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
    if (AVLLessThan(currNode, toinsert)) {
      // go right the tree
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }
    else if (AVLLessThan(toinsert, currNode)) {
      // go left the tree
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
    else { // currNode->JourneyCode == JourneyCode
      return false;
    }
  }
  if(AVLLessThan(toinsert, parentOfCurrNode))
  {
    // left insert
    updateAVLParentChild(toinsert, parentOfCurrNode, true);
    (parentOfCurrNode->left)->height=0;
  }
  else
  {
    // right insert
    updateAVLParentChild(toinsert, parentOfCurrNode, false);
    (parentOfCurrNode->right)->height=0;
  }

  TreeNode* z=updateAVLheight(parentOfCurrNode); // update height up the tree until we get at a node at which first imbalance happened
  rotate(z);  // rotate at imbalance point

  return true;
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

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.

  TreeNode *tofind = new TreeNode(jrnyCode, 0);
  TreeNode *currNode = root;
  while(currNode!=nullptr)
  {
    if(AVLLessThan(tofind , currNode))  // go left the tree
      currNode=currNode->left;
    else if(AVLLessThan(currNode, tofind))  // go right the tree
      currNode=currNode->right;
    else  // this is required node
      return currNode->getPrice();
  }
  return -1;  // not found
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

// Returns node with minimum price in the AVL whose root is passed
TreeNode* AVLTree::getMinimumNode(TreeNode* curr)
{
	// Minimum jc node is the leftmost node in the AVL
	if(curr==nullptr)
		return nullptr;
	if(curr->left==nullptr)
		return curr;	// This will be leftmost node
	return getMinimumNode(curr->left);
}


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

  // You MUST use only AVLLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke AVLLessThan on the
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
    if(AVLLessThan(todelete, currNode)) // go left the tree
      currNode=currNode->left;
    else if(AVLLessThan(currNode, todelete))  // go right the tree
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
    		TreeNode* successor= getMinimumNode(toremove->right); // This will be node to replace
    		int jc= successor->getJourneyCode();
    		int pc= successor->getPrice();
    		this->remove(jc); // successor will be removed from it's place
        int ht= toremove->height;
    		TreeNode* newNode= new TreeNode(jc, pc);
        // make apt parent child updates
        updateAVLParentChild(toremove->left, newNode, true);
        updateAVLParentChild(toremove->right, newNode, false);
        if(root==toremove)  // if toremove is still root, then newNode will be newRoot
          root=newNode;
        else
        {
          // make newNode child of toremove->parent
          if((toremove->parent)->left == toremove)
            updateAVLParentChild(newNode, toremove->parent, true);
          else
            updateAVLParentChild(newNode, toremove->parent, false);
        }
        newNode->height=ht;
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
        TreeNode* z=updateAVLheight(toremove->parent);  // update height up the tree until we get at a node at which first imbalance happened
        while(z!=nullptr) // while imbalance exists, rotate the tree
        {
          rotate(z);
          z = updateAVLheight(z->parent);  // update height up the tree until we get at a node at which first imbalance happened
        }
        return true;
    	}
    	else if(toremove->right==nullptr)  // Only left child
    	{
        // make toremove->left to be apt child of toremove->parent
        if((toremove->parent)->right == toremove)
    			updateAVLParentChild(toremove->left, toremove->parent, false);
    		else
    			updateAVLParentChild(toremove->left, toremove->parent, true);
        TreeNode* z=updateAVLheight(toremove->parent);  // update height up the tree until we get at a node at which first imbalance happened
        while(z!=nullptr) // while imbalance exists, rotate the tree
        {
          rotate(z);
          z = updateAVLheight(z->parent);  // update height up the tree until we get at a node at which first imbalance happened
        }
    		return true;
    	}
    	else if(toremove->left==nullptr)  // Only right child
    	{
        // make toremove->right to be apt child of toremove->parent
        if((toremove->parent)->right == toremove)
    			updateAVLParentChild(toremove->right, toremove->parent, false);
    		else
    			updateAVLParentChild(toremove->right, toremove->parent, true);
        TreeNode* z=updateAVLheight(toremove->parent);  // update height up the tree until we get at a node at which first imbalance happened
        while(z!=nullptr)  // while imbalance exists, rotate the tree
        {
          rotate(z);
          z = updateAVLheight(z->parent);  // update height up the tree until we get at a node at which first imbalance happened
        }
    		return true;
    	}
    	else  // Both left and right child
    	{
        TreeNode* successor= getMinimumNode(toremove->right);  // This will be node to replace
    		int jc= successor->getJourneyCode();
    		int pc= successor->getPrice();
    		this->remove(jc);  // successor will be removed from it's place
        int ht= toremove->height;
    		TreeNode* newNode= new TreeNode(jc, pc);
        // make apt parent child updates
        updateAVLParentChild(toremove->left, newNode, true);
        updateAVLParentChild(toremove->right, newNode, false);
        // make newNode apt child of toremove->parent
        if((toremove->parent)->left == toremove)
          updateAVLParentChild(newNode, toremove->parent, true);
        else
          updateAVLParentChild(newNode, toremove->parent, false);
        newNode->height=ht;
    		return true;
    	}
      return false;
    }
  }
  return false;
}
