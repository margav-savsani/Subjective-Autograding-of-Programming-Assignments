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
  	bool isGPLeftChild;
	if(greatGrandParentNode==nullptr)
	{
		isGPLeftChild=false;//some dummy variable
	}
  	else if (greatGrandParentNode->left == grandParentNode)
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
  	TreeNode *T3 = parentNode->right;
  	updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  	updateAVLParentChild(grandParentNode, parentNode, false);
  	updateAVLParentChild(T3, grandParentNode, true);
  	return true;
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
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the right child of parentNode, and
  // parentNode is the left child of grandParentNode.  That's
  // why we are doing a rotateLeftRight
	TreeNode *greatGrandParentNode = grandParentNode->parent;
  	bool isGPLeftChild;
	if(greatGrandParentNode==nullptr)
	{
		isGPLeftChild=false;//some dummy variable
	}
  	else if (greatGrandParentNode->left == grandParentNode)
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
  	TreeNode *T2 = currNode->left;
  	TreeNode *T3 = currNode->right;
	updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
	updateAVLParentChild(parentNode, currNode, true);
  	updateAVLParentChild(grandParentNode, currNode, false);
  	updateAVLParentChild(T2, parentNode, false);
	updateAVLParentChild(T3, grandParentNode, true);
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
  	return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
	TreeNode *greatGrandParentNode = grandParentNode->parent;//be careful
  	bool isGPLeftChild;
	if(greatGrandParentNode==nullptr)
	{
		isGPLeftChild=false;//some dummy variable
	}
	else if(greatGrandParentNode==nullptr)
	{
		isGPLeftChild=false;//some dummy variable
	}
  	else if (greatGrandParentNode->left == grandParentNode)
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
  	TreeNode *T2 = currNode->left;
  	TreeNode *T3 = currNode->right;
	updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
	updateAVLParentChild(parentNode, currNode, false);
  	updateAVLParentChild(grandParentNode, currNode, true);
  	updateAVLParentChild(T2, grandParentNode, false);
	updateAVLParentChild(T3, parentNode, true);
	return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  	TreeNode *greatGrandParentNode = grandParentNode->parent;
  	bool isGPLeftChild;
	if(greatGrandParentNode==nullptr)
	{
		isGPLeftChild=false;//some dummy variable
	}
  	else if (greatGrandParentNode->left == grandParentNode)
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
  	TreeNode *T3 = parentNode->left;
  	updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  	updateAVLParentChild(grandParentNode, parentNode, true);
  	updateAVLParentChild(T3, grandParentNode, false);
  	return true;
}

bool AVLTree::insert(int jrnyCode, int price)
{

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.
	TreeNode* N=new TreeNode(jrnyCode,price);
	TreeNode* a=root;
	bool lessthan;
	while(a!=nullptr)
	{
		if(AVLLessThan(a,N))//be careful i didn't check equality case
		{
			if(a->right==nullptr)
			{
				updateAVLParentChild(N,a,false);
				break;
			}
			else
			{
				a=a->right;
			}
		}
		else if(AVLLessThan(N,a))
		{
			if(a->left==nullptr)
			{
				updateAVLParentChild(N,a,true);
				break;
			}
			else
			{
				a=a->left;
			}
		}
		else
		{
			return false;
		}
	}
	if(a==nullptr)
	{
		root=N;
		return true;
	}
	//inserted
	//have to rebalance tree and update heights
	TreeNode* currNode=N;
	TreeNode* parentNode=nullptr;
	TreeNode* grandParentNode=nullptr;
	int height_dummy=0;
	int height_left;
	int height_right;
	int height_diff;
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
	while(currNode!=nullptr)
	{
		parentNode=currNode->parent;
		if(parentNode==nullptr)
		{
			currNode->height=height_dummy;
			break;
		}
		grandParentNode=parentNode->parent;
		if(grandParentNode==nullptr)
		{
			currNode->height=height_dummy;
			int a1=0;
			int b1=0;
			if(parentNode->left!=nullptr)
			{
				a1=parentNode->left->height+1;
			}
			if(parentNode->right!=nullptr)
			{
				b1=parentNode->right->height+1;
			}
			if(a1<b1)
			{
				a1=b1;
			}
			parentNode->height=a1;
			break;
		}
		if(parentNode->height==height_dummy+1)
		{
			currNode->height=height_dummy;
			break;
		}
		if(grandParentNode->height==height_dummy+2)
		{
			currNode->height=height_dummy;
			int a1=0;
			int b1=0;
			if(parentNode->left!=nullptr)
			{
				a1=parentNode->left->height+1;
			}
			if(parentNode->right!=nullptr)
			{
				b1=parentNode->right->height+1;
			}
			if(a1<b1)
			{
				a1=b1;
			}
			parentNode->height=a1;
			break;
		}
		if(grandParentNode->left==parentNode)
		{
			height_left=height_dummy+2;
			if(grandParentNode->right!=nullptr)
			{
				height_right=grandParentNode->right->height+1;
			}
			else
			{
				height_right=0;
			}
		}
		else
		{
			height_right=height_dummy+2;
			if(grandParentNode->left!=nullptr)
			{
				height_left=1+grandParentNode->left->height;
			}
			else
			{
				height_left=0;
			}
		}
		height_diff=height_left-height_right;
		if(height_diff<2 && height_diff>-2)
		{
			currNode->height=height_dummy;
			height_dummy++;
			currNode=parentNode;
		}
		else
		{
			if(parentNode->left==currNode && grandParentNode->left==parentNode)
			{
				currNode->height=height_dummy;
				parentNode->height=height_dummy+1;
				grandParentNode->height=height_dummy;
				rotateLeftLeft(currNode,parentNode,grandParentNode);
			}
			else if(parentNode->left==currNode && grandParentNode->right==parentNode)
			{
				currNode->height=height_dummy+1;
				parentNode->height=height_dummy;
				grandParentNode->height=height_dummy;
				rotateRightLeft(currNode,parentNode,grandParentNode);
			}
			else if(parentNode->right==currNode && grandParentNode->left==parentNode)
			{
				currNode->height=height_dummy+1;
				parentNode->height=height_dummy;
				grandParentNode->height=height_dummy;
				rotateLeftRight(currNode,parentNode,grandParentNode);
			}
			else if(parentNode->right==currNode && grandParentNode->right==parentNode)
			{
				currNode->height=height_dummy;
				parentNode->height=height_dummy+1;
				grandParentNode->height=height_dummy;
				rotateRightRight(currNode,parentNode,grandParentNode);
			}
			break;
		}
	}

  	// You MUST use only AVLLessThan to compare two journey codes.  You
  	// can create a new node containing the journey code to be inserted
  	// and invoke AVLLessThan on the current node in the tree that you
  	// are inspecting and the new node to do your comparison.
  	// REMEMBER to update the heights of appropriate nodes in the tree
  	// after an insertion.
	return true;
}

int AVLTree::find(int jrnyCode)
{
	TreeNode* search = new TreeNode(jrnyCode,0);
	TreeNode* a =root;
	bool comparison;
	while(a!=nullptr)
	{
		comparison= AVLLessThan( a, search);
		if(a->JourneyCode==jrnyCode)
		{
			return a->price;
		}
		else if(!comparison)
		{
			a=a->left;
		}
		else
		{
			a=a->right;
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
