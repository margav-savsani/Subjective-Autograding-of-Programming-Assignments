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
  if (greatGrandParentNode == nullptr){
	isGPLeftChild == true;
  }
  else if (greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  // Let T3 be the right child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures
  TreeNode *T3 = parentNode->right;

  // Now replicate the single rotation for LeftLeft as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild

  // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);

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

  if(greatGrandParentNode == nullptr){
	root = parentNode;
  }

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
    if (greatGrandParentNode == nullptr){
		isGPLeftChild == true;
  	}
  	else if (greatGrandParentNode->left == grandParentNode) {
    	isGPLeftChild = true;
	}
	else if (greatGrandParentNode->right == grandParentNode) {
		isGPLeftChild = false;
	}
	else {
		cerr << "Unexpected condition encountered!" << endl;
		return false;
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

  // Make currNode (x in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

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

    if(greatGrandParentNode == nullptr){
		root = currNode;
  	}

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
	// similare to rotateLR

	TreeNode *greatGrandParentNode = grandParentNode->parent;

  	bool isGPLeftChild;
  	if (greatGrandParentNode == nullptr){
		isGPLeftChild == true;
  	}
  	else if (greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
	}
	else if (greatGrandParentNode->right == grandParentNode) {
		isGPLeftChild = false;
	}
	else {
		cerr << "Unexpected condition encountered!" << endl;
		return false;
  	}

	// Let T2 be the right child of currNode (i.e. of x)
	TreeNode *T2 = currNode->right;
	
	// Let T3 be the left child of currNode (i.e. of x)
	TreeNode *T3 = currNode->left;

	updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

	updateAVLParentChild(parentNode, currNode, false);
	
	updateAVLParentChild(grandParentNode, currNode, true);
	
	updateAVLParentChild(T2, parentNode, true);

	updateAVLParentChild(T3, grandParentNode, false);

	if(greatGrandParentNode == nullptr){
		root = currNode;
  	}
	
	return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
	// similar to rotateLL
	TreeNode *greatGrandParentNode = grandParentNode->parent;
	
	bool isGPLeftChild;
	if (greatGrandParentNode == nullptr){
		isGPLeftChild == true;
  	}
  	else if (greatGrandParentNode->left == grandParentNode) {
		isGPLeftChild = true;
	}
	else if (greatGrandParentNode->right == grandParentNode) {
		isGPLeftChild = false;
	}
	else {
		cerr << "Unexpected condition encountered!" << endl;
		return false;
	}

	// Let T3 be the left child of parentNode (i.e. of y, using notation
	// from Prof. Garg's lectures

	TreeNode *T3 = parentNode->left;

	updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);

	updateAVLParentChild(currNode, parentNode, false);

	updateAVLParentChild(grandParentNode, parentNode, true);

	updateAVLParentChild(T3, grandParentNode, false);

	if(greatGrandParentNode == nullptr){
		root = parentNode;
  	}
	
	return true;
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

  	if(root == nullptr){
		root = new TreeNode(jrnyCode, price);
		return true;
	}

	// node to be inserted and used for comparisons
	TreeNode* search_node = new TreeNode(jrnyCode, price);

	struct TreeNode *curr = root, *parent = nullptr;

    // finding place to insert
	while (curr != nullptr) {
		if (AVLLessThan(curr, search_node)) {
			parent = curr;
			curr = curr->right;
		}
		else if (AVLLessThan(search_node, curr)) {
			parent = curr;
			curr = curr->left;
		}
		else { // curr->JourneyCode == JourneyCode
			delete search_node;
			return false;
		}
  	}

    // JourneyCode is not present in the AVL.  We must now
    // insert an appropriate child of parent.

    // inserting the node
	curr = search_node;
	// curr->updateParentChild(parent, AVLLessThan(search_node, parent));
	updateAVLParentChild(curr, parent, AVLLessThan(search_node, parent));

	// updating the height
	unsigned int new_height; // stores the new height to update

	TreeNode* grandParent = parent;
	parent = curr;
	curr=nullptr;

	while(grandParent!=nullptr){
		if(grandParent->left == nullptr ){
			new_height = grandParent->right->height + 1;
		}
		else if(grandParent->right == nullptr ){
			new_height = grandParent->left->height + 1;
		}
		else{
			new_height = max(grandParent->left->height, grandParent->right->height) + 1;
		}
        if(new_height == grandParent->height){
            // no need to go up if not changed at this node
            return true;
        }
        grandParent->height = new_height;
		if(!grandParent->Isbalance()){
			if(grandParent->left == parent){
				if(parent->left == curr){
					rotateLeftLeft(curr, parent, grandParent);
					grandParent->height -= 2;
					return true;
				}
				else{
					rotateLeftRight(curr, parent, grandParent);
					grandParent->height -=2;
					curr->height += 1;
					parent->height -= 1;
					return true;
				}
			}
			else{
				if(parent->right == curr){
					rotateRightRight(curr, parent, grandParent);
					grandParent->height -= 2;
					return true;
				}
				else{
					rotateRightLeft(curr, parent, grandParent);
					grandParent->height -=2;
					curr->height += 1;
					parent->height -= 1;
					return true;
				}
			}
		}
		curr = parent;
		parent = grandParent;
		grandParent = grandParent->parent;
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
  // Implement find in AVL tree.
  // This is really no different from finding in a binary search tree.
  // This operation cannot cause any balance factor disturbances.

  // You MUST use only AVLLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke AVLLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  	//similar to BSTfind
    if(root == nullptr){
        return -1;
    }

	// node used for comparisons
	TreeNode* search_node = new TreeNode(jrnyCode, 0);

    struct TreeNode *curr = root, *parent = nullptr;

    while (curr != nullptr) {
		if (AVLLessThan(curr, search_node)) {
			parent = curr;
			curr = curr->right;
		}
		else if (AVLLessThan(search_node, curr)) {
			parent = curr;
			curr = curr->left;
		}
		else { // curr->JourneyCode == JourneyCode
			delete search_node;
			return curr->getPrice();
		}
  	}

    // if not found above
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


	// empty tree case
	if(root == nullptr){
		return false;
	}

	// node to be used for comparisons
	TreeNode* search_node = new TreeNode(jrnyCode, 0);

    // finding that node
	struct TreeNode *curr = root;

	while (curr != nullptr) {
		if (AVLLessThan(curr, search_node)) {
			curr = curr->right;
		}
		else if (AVLLessThan(search_node, curr)) {
			curr = curr->left;
		}
		else { // curr->JourneyCode == JourneyCode
			break;
		}
  	}
	delete search_node;

	if(curr == nullptr){
		// element not found 
		return false;
	}

	TreeNode* delNode; // it has 1/0 child
	if(curr->left == nullptr || curr->right == nullptr){
		// 0 or 1 child
		delNode = curr;
	}
	else{
		// 2 childs, so find succesor
		TreeNode* successor = curr->right;
            while(successor->left != nullptr){
                successor = successor->left;
			}
		delNode = successor;
		// update the values
		curr->reset(delNode);
	}

	// child of delNode
	TreeNode* delChild = (delNode->left != nullptr)?(delNode->left):(delNode->right);

	if(delChild != nullptr){
		// 1 child case
		delChild->parent = delNode->parent;
	}
	
	if (delNode->parent == nullptr){
		// delNode is root with 1/0 child
		root = delChild;
		return true;
		// no more updates required anywhere
	}
	else{
		updateAVLParentChild(delChild, delNode->parent, delNode == delNode->parent->left);
	}

	// updating heights
	TreeNode* parent = delNode->parent; // parent of the delNode
	delete delNode; // deleting the delNode
	unsigned int old_height; // stores the new height to update

	// handling case if delNode was a leaf
	if(delChild == nullptr){
		if(parent->left == nullptr && parent->right == nullptr){
			// parent has 0 child
			parent->height = 0;
		}
		else{
			// parent has 1 child
			if(parent->height == 1){
				// child is leaf
				return true;
			}
			else
			{ 	// balancing height 2 tree with only 1 child

				TreeNode* child, *grandchild;
				if(parent->left != nullptr){
					child = parent->left;
					if(child->left != nullptr){
						//LL
						grandchild = child->left;
						rotateLeftLeft(grandchild, child, parent);

						if(parent->left != nullptr){
							parent->height = 1;
							child->height = 2; 
							return true;
						}
						parent->height = 0; 
						parent = child;
					}
					else{
						//LR
						grandchild = child->right;
						rotateLeftRight(grandchild, child, parent);

						parent->height = 0;
						child->height = 0;
						grandchild->height = 1;
						parent = grandchild;
					}
				}
				else{
					child = parent->right;
					if(child->right != nullptr){
						//RR
						grandchild = child->right;
						rotateRightRight(grandchild, child, parent);

						if(parent->right != nullptr){
							parent->height = 1;
							child->height = 2; 
							return true;
						}
						parent->height = 0; 
						parent = child;
					}
					else{
						//RL
						grandchild = child->left;
						rotateRightLeft(grandchild, child, parent);

						parent->height = 0;
						child->height = 0;
						grandchild->height = 1;
						parent = grandchild;
					}
				}
			}
		}
		parent = parent->parent;
	}

	while(parent!=nullptr){
		old_height = parent->height;
		parent->height = max(parent->left->height, parent->right->height) + 1;

		if(!parent->Isbalance()){

			TreeNode* child, *grandchild;

			if(parent->left->height > parent->right->height)
			{
				child = parent->left;
				if(child->left->height >= child->right->height)
				{
					// LL
					grandchild = child->left;
					rotateLeftLeft(grandchild, child, parent);

					if(parent->left->height != parent->right->height)
					{
						parent->height -= 1;
						child->height += 1;
						return true;
					}
					parent->height -= 2;
					parent = child;
				}
				else{
					// LR
					grandchild = child->right;
					rotateLeftRight(grandchild, child, parent);

					parent->height -= 2;
					child->height -= 1;
					grandchild->height += 1;
					parent = grandchild;
				}
			}
			else{
				child = parent->right;
				if(child->left->height <= child->right->height)
				{
					// RR
					grandchild = child->right;
					rotateRightRight(grandchild, child, parent);

					if(parent->left->height != parent->right->height)
					{
						parent->height -= 1;
						child->height += 1;
						return true;
					}
					parent->height -= 2;
					parent = child;
				}
				else{
					// RL
					grandchild = child->left;
					rotateRightLeft(grandchild, child, parent);

					parent->height -= 2;
					child->height -= 1;
					grandchild->height += 1;
					parent = grandchild;
				}

			}
		}
		if(parent->height == old_height){
			// no need to go up if height hasn't changed here
			return true;
		}
		parent = parent->parent;
	}
	return true;
}


