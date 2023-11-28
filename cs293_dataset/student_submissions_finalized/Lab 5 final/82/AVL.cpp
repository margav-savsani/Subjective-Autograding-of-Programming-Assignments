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
	if(greatGrandParentNode)
	{
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
			// cout << "Pelo" << endl;
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

	if(!greatGrandParentNode){root = parentNode;}

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
	if(greatGrandParentNode)
	{
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

	if(!greatGrandParentNode){root = currNode;}

	return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
	TreeNode* greatGrandParentNode = grandParent->parent;


	bool isGPLeftChild;
	if(greatGrandParentNode)
	{
		if (greatGrandParentNode->left == grandParent)
		{
			isGPLeftChild = true;
		}
		else if (greatGrandParentNode->right == grandParent)
		{
			isGPLeftChild = false;
		}
		else
		{
			cerr << "Unexpected condition encountered!" << endl;
			return false;
		}
	}

	TreeNode* T1 = currNode->right;
	TreeNode* T2 = currNode->left;

	updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
	updateAVLParentChild(grandParent, currNode, true);
	updateAVLParentChild(parent, currNode, false);

	updateAVLParentChild(T1, parent, true);
	updateAVLParentChild(T2, grandParent, false);

	if(!greatGrandParentNode){root = currNode;}

	return true;

}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
	// Implement this yourself

	TreeNode *greatGrandParentNode = grandParent->parent;

	bool isGPLeftChild;
	if(greatGrandParentNode)
	{
		if (greatGrandParentNode->left == grandParent)
		{
			isGPLeftChild = true;
		}
		else if (greatGrandParentNode->right == grandParent)
		{
			isGPLeftChild = false;
		}
		else
		{
			cerr << "Unexpected condition encountered!" << endl;
			return false;
		}
	}

	updateAVLParentChild(parent, greatGrandParentNode, isGPLeftChild);

	TreeNode *T = parent->left;

	updateAVLParentChild(grandParent, parent, true);
	updateAVLParentChild(T, grandParent, false);

	// handling the case, when root is null ==> greatGrandParent has to be null.
	if(!greatGrandParentNode){root = parent;}

	return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.


// This function updates the height at the nodes accordingly according to the child nodes.
void AVLTree::updateHeight(TreeNode* node){
	if(node == nullptr) return;

	if(node->left && node->right){
		node->height = max(node->left->height , node->right->height) + 1;
	}
	else if(node->right){
		node->height = node->right->height + 1;
	}
	else if(node->left){
		node->height = node->left->height + 1;
	}
	else{
		node->height = 0;
	}
}


// this function simply mimics the implementation of the rotation in case when there is an imbalance at a particular node.
void AVLTree::updateBalance(TreeNode* currNode){
    if(currNode == nullptr) return;
    else {
		updateHeight(currNode);

		if(currNode->getBalance() < -1 || currNode->getBalance() > 1){
			if(currNode->getBalance() >0){
				if(currNode->left->getBalance() > 0){

				// This is the case for a LL-rotation
				rotateLeftLeft(currNode->left->left, currNode->left, currNode);

				// update the heights of the nodes whose height got messed up while rotation usig the update height function described earlier.
				updateHeight(currNode);
				updateHeight(currNode->parent->left);
				updateHeight(currNode->parent);
				return;
				}
				else if(currNode->left->getBalance() < 0){

					// LR-rotation
					rotateLeftRight(currNode->left->right, currNode->left, currNode);

					// similar update in heights
					updateHeight(currNode);
					updateHeight(currNode->parent->left);
					updateHeight(currNode->parent);
					return;
				}
			}
			else if(currNode->getBalance() < 0){
				if(currNode->right->getBalance() < 0){

					// RR-rotation
					rotateRightRight(currNode->right->right, currNode->right, currNode);

					// similar update in heights
					updateHeight(currNode);
					updateHeight(currNode->parent->right);
					updateHeight(currNode->parent);
					return;
				}
				else if(currNode->right->getBalance() > 0){
					// RL-rotation
					rotateRightLeft(currNode->right->left, currNode->right, currNode);

					// similar update in heights
					updateHeight(currNode);
					updateHeight(currNode->parent->right);
					updateHeight(currNode->parent);
					return;
				}
			}
		}
		else{

			// recursive call to this function again if there is not an imbalance till now.
			updateBalance(currNode->parent);
		}
	}

}



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
// ---------------------------------------------------------------------------------------------//


// handling the case when root is null pointer.
	if(root == nullptr){
        root = new TreeNode(jrnyCode, price, nullptr, nullptr, nullptr);
        root->height = 0;
        return true;
    }

	// here toComp is a random TreeNode to just compare the given journeyCode with other journey codes.
	TreeNode* toComp = new TreeNode(jrnyCode, 0);
    TreeNode* parent = nullptr;
    TreeNode* currNode = root;

    // bool variable to ckeck the currNode is the left or right child of its parent.
    bool isLeft = false;
    while(currNode!=nullptr){

        // checking whether the element to be inserted is already present or not.
        if(!AVLLessThan(currNode, toComp) && !AVLLessThan(toComp, currNode)){
			delete toComp;
            return false;
        }

        // moving to the currNode pointer accordingly to reach a leaf so as to insert the node accordingly.
        else if(!AVLLessThan(currNode, toComp)){
            parent = currNode;
            currNode = currNode->left;
            isLeft = true;
        }
        else{
            parent = currNode;
            currNode = currNode->right;
            isLeft = false;
        }
    }

	// creating, inserting a new node and updating the balance.
	TreeNode* newNode = new TreeNode(jrnyCode, price, nullptr, nullptr, parent);
	updateAVLParentChild(newNode, parent, isLeft);
    updateBalance(newNode);

	delete toComp;
	return true;
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

// ------------------------------------------------------------------------------------------//
// Don't think this needs any comments.
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

	TreeNode* toComp = new TreeNode(jrnyCode, 0);
	TreeNode*toCheck = new TreeNode(jrnyCode, 0, nullptr, nullptr, nullptr);
	TreeNode* currNode = root;
	while(currNode!=nullptr){
		if(!AVLLessThan(currNode, toComp) && !AVLLessThan(toComp, currNode)) {
			delete toComp;
			return 1;
		}
		if(!AVLLessThan(currNode, toCheck)){
			currNode = currNode->left;
		}
		else{
			currNode = currNode->right;
		}
	}
	delete toComp;
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
// ---------------------------------------------------------------------------------//

// This updateBalance Del is very similar to the updateBalance function, defined previousl, 
// so I am just commenting that part which is different than the previous one
void AVLTree::updateBalanceDel(TreeNode* currNode){
    if(currNode == nullptr) return;
    else {
		updateHeight(currNode);

		// storing the height so as to know whether to perform update balance of tree again or not
		int h = currNode->height;

		if(currNode->getBalance() < -1 || currNode->getBalance() > 1){
			if(currNode->getBalance() >0){
				if(currNode->left->getBalance() >= 0){
					rotateLeftLeft(currNode->left->left, currNode->left, currNode);
					updateHeight(currNode);
					updateHeight(currNode->parent->left);
					updateHeight(currNode->parent);

					// updating the balance again, if the height of the current parent after rotation is not equal to the previous node where the imbalance happened.
					if(currNode->parent->height != h) updateBalanceDel(currNode->parent);
					return;
				}
				else if(currNode->left->getBalance() < 0){
					rotateLeftRight(currNode->left->right, currNode->left, currNode);
					updateHeight(currNode);
					updateHeight(currNode->parent->left);
					updateHeight(currNode->parent);
					
					// similar
					if(currNode->parent->height != h) updateBalanceDel(currNode->parent);
					return;
				}
			}
			else if(currNode->getBalance() < 0){
				if(currNode->right->getBalance() <= 0){
					rotateRightRight(currNode->right->right, currNode->right, currNode);
					updateHeight(currNode);
					updateHeight(currNode->parent->right);
					updateHeight(currNode->parent);
					
					// similar
					if(currNode->parent->height != h) updateBalanceDel(currNode->parent);
					return;
				}
				else if(currNode->right->getBalance() > 0){
					rotateRightLeft(currNode->right->left, currNode->right, currNode);
					updateHeight(currNode);
					updateHeight(currNode->parent->right);
					updateHeight(currNode->parent);
					
					// similar
					if(currNode->parent->height != h) updateBalanceDel(currNode->parent);
					return;
				}
			}
		}
		else{
			updateBalanceDel(currNode->parent);
		}
	}
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




	TreeNode* toComp = new TreeNode(jrnyCode, 0);
    TreeNode* currNode = root;
    TreeNode* parent = nullptr;

    // bool variable to ckeck the currNode is the left or right child of its parent.
    bool isLeft = false;
    while(currNode!= nullptr){
        if(!AVLLessThan(currNode, toComp) && !AVLLessThan(toComp, currNode)){ 
			
            if(currNode->right == nullptr && currNode->left == nullptr){// both child null
                
				// handling the case fo root separately.
                if(parent == nullptr){
                    root = nullptr;
                    delete currNode;
                }
                else if(isLeft){
                    delete currNode;
                    parent->left = nullptr;
					
					// maintaining the imbalance if created.
					updateBalanceDel(parent);
                }
                else if(!isLeft){
                    delete currNode;
                    parent->right = nullptr;
					
					// maintaining the imbalance if created.
					updateBalanceDel(parent);
                }
            }
            else if(currNode->left != nullptr && currNode->right == nullptr){ // right child null
			
			// handling the case fo root separately.
                if(parent == nullptr){
                    root = currNode->left;
					root->parent = nullptr;
                    delete currNode;
                }
                else if(isLeft){
                    updateAVLParentChild(currNode->left, parent, isLeft);
                    delete currNode;
					
					// maintaining the imbalance if created.
					updateBalanceDel(parent);
                }
                else if(!isLeft){
                    updateAVLParentChild(currNode->left, parent, isLeft);
                    delete currNode;
					
					// maintaining the imbalance if created.
					updateBalanceDel(parent);
                }
            }
            else if(currNode->right != nullptr && currNode->left == nullptr){ //l;eft child null
                
				// handling the case fo root separately.
				if(parent == nullptr){
                    root = currNode->right;
					root->parent = nullptr;
                    delete currNode;
                }
                else if(isLeft){
                    updateAVLParentChild(currNode->right, parent, isLeft);
                    delete currNode;
					
					// update the height to maintain balance using a different updateBalanceDel function specific for del.
					updateBalanceDel(parent);
                }
                else if(!isLeft){
                    updateAVLParentChild(currNode->right, parent, isLeft);
                    delete currNode;
					updateBalanceDel(parent);
                }
            }
            else { // no child null
                
				// finding the predecesor to remove accordingly.
                TreeNode* pred = predecesor(currNode);
                int a = pred->getPrice();
                int b = pred->getJrnyCode();
                remove(b);
                currNode->getPrice() = a;
                currNode->getJrnyCode() = b;
            }
			delete toComp;
            return true;
        }
        
		// shifting the currNode pointer accordingly and continue the iterations.
        else if(!AVLLessThan(currNode, toComp)){
            parent = currNode;
            currNode = currNode->left;
            isLeft = true;
        }
        else{
            parent = currNode;
            currNode = currNode->right;
            isLeft = false;
        }
    }
	delete toComp;
    return false;
}

TreeNode* AVLTree::predecesor(TreeNode* node){
	
	// the case when the left child of the node for woch the  predecessor has to be found is not null.
    if(node->left){
        TreeNode* currNode = node;
        currNode = currNode->left;
        while(currNode->right!=nullptr){
            currNode = currNode->right;
        }
        return currNode;
    }

    // actually this never get called because pred() gets called only when both child of node is not null(see updateBalanceDel function) so...
    else if(node->parent){
        TreeNode* par = node->parent;
        TreeNode* currNode = node;
        while(par!=nullptr){
            if(par->right == currNode){
                return par;
            }
            else{
                currNode = par;
                par = par->parent;
            }
        }
    }
    return nullptr;
}
