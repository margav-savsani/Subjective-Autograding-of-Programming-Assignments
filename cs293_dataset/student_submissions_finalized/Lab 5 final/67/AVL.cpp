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

/* Implemented */bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the left child of parentNode, and
  // parentNode is the left child of grandParentNode
  // That's why we are doing a rotateLeftLeft

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  if(greatGrandParentNode){
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
	  // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
	  // child of greatGrandParentNode
	  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  }else{
	  root=parentNode;
	  updateAVLParentChild(parentNode,NULL,true);
  }

  // Let T3 be the right child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures
  TreeNode *T3 = parentNode->right;

  // // Make currNode (x in Prof. Garg's lectures) the left child of
  // // parentNode (y in Prof. Garg's lectures)
  // // The last parameter is "true" to indicate that currNode should be
  // // made the left child of parentNode
  // updateAVLParentChild(currNode, parentNode, true);
  
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

  int lh=-1,rh=-1;
  if(grandParentNode->left)	lh=grandParentNode->left->height;
  if(grandParentNode->right)	rh=grandParentNode->right->height;
  grandParentNode->height=max(lh,rh)+1;

  lh=-1,rh=-1;
  if(currNode->left)	lh=currNode->left->height;
  if(currNode->right)	rh=currNode->right->height;
  currNode->height=max(lh,rh)+1;

  lh=-1,rh=-1;
  if(parentNode->left)	lh=parentNode->left->height;
  if(parentNode->right)	rh=parentNode->right->height;
  parentNode->height=max(lh,rh)+1;
  return true;
}

/* Implemented */bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the right child of parentNode, and
  // parentNode is the left child of grandParentNode.  That's
  // why we are doing a rotateLeftRight

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  if(greatGrandParentNode){
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
	  // Make currNode (x in Prof. Naveen Garg's lectures) the appropriate
	  // child of greatGrandParentNode
	  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  }else{
	  root=currNode;
	  updateAVLParentChild(root,NULL,true);
  }

  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;

  // Now replicate the double rotation for LeftRight as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild
  //
  // We can directly implement the double rotation, instead of doing two
  // rotations sequentially.  So we'll look at the end-result of the
  // double rotation (refer Prof. Garg's lecture notes) and arrive at that
  // from the original tree.


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

  int lh=-1,rh=-1;
  if(grandParentNode->left)	lh=grandParentNode->left->height;
  if(grandParentNode->right)	rh=grandParentNode->right->height;
  grandParentNode->height=max(lh,rh)+1;

  lh=-1,rh=-1;
  if(parentNode->left)	lh=parentNode->left->height;
  if(parentNode->right)	rh=parentNode->right->height;
  parentNode->height=max(lh,rh)+1;

  lh=-1,rh=-1;
  if(currNode->left)	lh=currNode->left->height;
  if(currNode->right)	rh=currNode->right->height;
  currNode->height=max(lh,rh)+1;

  return true;
}

/* Implemented */bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Implement this yourself
	TreeNode* ggp=grandParent->parent;
	if(ggp){
		if(ggp->left==grandParent){
			updateAVLParentChild(currNode,ggp,true);
		}
		else if(ggp->right==grandParent){
			updateAVLParentChild(currNode,ggp,false);
		}
		else{
			cerr << "Unexpected condition encountered!" << endl;
			return false;
		}
	}else{
		root=currNode;
		updateAVLParentChild(root,NULL,true);
	}
	//parent->left=currNode->right;
	updateAVLParentChild(currNode->right,parent,true);
	// gp->right=curr->left
	updateAVLParentChild(currNode->left,grandParent,false);
	// The above two steps place child trees of curr correctly
	// Now, take the currNode to top as it is the middle node
	updateAVLParentChild(grandParent,currNode,true);
	updateAVLParentChild(parent,currNode,false);
	int lh=-1,rh=-1;
	if(grandParent->left)	lh=grandParent->left->height;
	if(grandParent->right)	rh=grandParent->right->height;
	grandParent->height=max(lh,rh)+1;

	lh=-1,rh=-1;
	if(parent->left)	lh=parent->left->height;
	if(parent->right)	rh=parent->right->height;
	parent->height=max(lh,rh)+1;

	lh=-1,rh=-1;
	if(currNode->left)	lh=currNode->left->height;
	if(currNode->right)	rh=currNode->right->height;
	currNode->height=max(lh,rh)+1;

	return true;
}

/* Implemented */bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
	if(grandParent->parent){
		TreeNode* ggp=grandParent->parent;
		if(ggp->left==grandParent){
			updateAVLParentChild(parent,ggp,true);
		}
		else if(ggp->right==grandParent){
			updateAVLParentChild(parent,ggp,false);
		}
		else {
		  cerr << "Unexpected condition encountered!" << endl;
		  return false;
		}
	}
	else{
		root=parent;
		updateAVLParentChild(root,NULL,true);
	}
	// grandParent->right=parent->left
	updateAVLParentChild(parent->left,grandParent,false);
	// parent->right=grandParent
	updateAVLParentChild(grandParent,parent,true);

	int lh=-1,rh=-1;
	if(grandParent->left)	lh=grandParent->left->height;
	if(grandParent->right)	rh=grandParent->right->height;
	grandParent->height=max(lh,rh)+1;

	lh=-1,rh=-1;
	if(currNode->left)	lh=currNode->left->height;
	if(currNode->right)	rh=currNode->right->height;
	currNode->height=max(lh,rh)+1;

	lh=-1,rh=-1;
	if(parent->left)	lh=parent->left->height;
	if(parent->right)	rh=parent->right->height;
	parent->height=max(lh,rh)+1;

	return true;
}

/* Implemented */bool AVLTree::heightCorrect(TreeNode* grandParent, TreeNode* parent, TreeNode* currNode) // Calls the required rotate function
{
	bool l1=true;
	bool l2=true;
	if(grandParent->right==parent)	l1=false;
	if(parent->right==currNode)	l2=false;
	if(l1 && l2)	return rotateLeftLeft(currNode,parent,grandParent);
	else if(!l1 && l2)	return rotateRightLeft(currNode,parent,grandParent);
	else if(l1 && !l2)	return rotateLeftRight(currNode,parent,grandParent);
	else if(!l1 && !l2)	return rotateRightRight(currNode,parent,grandParent);
	return false;
}
// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

/* Implemented */bool AVLTree::insert(int jrnyCode, int price)
{
	TreeNode* to_insert=new TreeNode(jrnyCode,price);
	TreeNode* curr=root;
	bool isLeft;
	while(curr){
		if(AVLLessThan(to_insert,curr)){
			if(curr->left){	
				curr=curr->left;
				continue;
			}
			isLeft=true;
			break;
		}
		else if(AVLLessThan(curr,to_insert)){
			if(curr->right){
				curr=curr->right;
				continue;
			}
			isLeft=false;
			break;
		}
		return false; // Already present
	}
	updateAVLParentChild(to_insert,curr,isLeft);
	//Insertion Done
	// Balancing test and height update starts
	TreeNode* currNode=to_insert;
	if(root==NULL){
		root=to_insert;
		return true;
	}
	TreeNode* parent=currNode->parent;
	parent->height=1;
	if(!parent->parent){
		return true;
	}
	TreeNode* grandParent=parent->parent;
	while(grandParent){
		int diff;
		if(!grandParent->left){
			diff=2;
		}else if(!grandParent->right){
			diff=2;
		}else{
			diff=grandParent->left->height-grandParent->right->height;
		}
		if(diff<-1 || diff>1){
			if(!heightCorrect(grandParent,parent,currNode))	return false;
			int lh=-1,rh=-1;
			if(grandParent->left)	lh=grandParent->left->height;
			if(grandParent->right)	rh=grandParent->right->height;
			grandParent->height=max(lh,rh)+1;
			return true;
		}
		int lh=-1,rh=-1;
		if(grandParent->left)	lh=grandParent->left->height;
		if(grandParent->right)	rh=grandParent->right->height;
		grandParent->height=max(lh,rh)+1;
		currNode=parent;
		parent=grandParent;
		grandParent=grandParent->parent;
	}
	return true;
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

  return true;
}


/* Implemented */int AVLTree::find(int jrnyCode)
{
	// Returns the price on finding an element in the AVL tree that matches
	// journey code. Returns -1 otherwise.
	// You may assume that no two node in the tree have the same journey
	// code, and journey code is the key for insertion and finding in the AVL
	// tree.
	// Implement find in AVL tree.
	// This is really no different from finding in a binary search tree.
	// This operation cannot cause any balance factor disturbances.
	
	// You MUST use only AVLLessThan to compare two journey codes.  You
	// can create a new node containing the journey code to be searched
	// (along with some arbitrary price) and invoke AVLLessThan on the
	// current node in the tree that you are inspecting and the new node
	// to do your comparison.
	TreeNode* to_find=new TreeNode(jrnyCode,0);
	TreeNode* curr=root;
	while(curr){ // Ensures that curr is not NULL inside the loop
		if(AVLLessThan(to_find,curr)){
			curr=curr->left;
			continue;
		}
		if(AVLLessThan(curr,to_find)){
			curr=curr->right;
			continue;
		}
		return curr->getPrice(); // It is neither less, nor more, therefore, it is the required node.
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


