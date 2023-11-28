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

// update height of the current node according to the heights of its child.
void BST::updateHeight(TreeNode* node){
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


// just update the height and not balance maintain is happening here because its BST :)
void BST::updateBalance(TreeNode* currNode){
    if(currNode == nullptr) return;
    else {
		updateHeight(currNode);
		updateBalance(currNode->parent);
	}
}

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

//-----------------------------------------------------------------------------------------------//

// Case when the root itself is nullptr
	if(root == nullptr){
        root = new TreeNode(jrnyCode, price, nullptr, nullptr, nullptr);
        root->height = 0;
        return true;
    }
    TreeNode* parent = nullptr;
    TreeNode* currNode = root;

    // dummy node to compare journey code with other nodes
	TreeNode* toComp = new TreeNode(jrnyCode, 0);

    // bool variable to check the currNode is the left or right child of its parent.
    bool isLeft = false;
    while(currNode!=nullptr){

        // checking whether the element to be inserted is already present or not.
        if(!BSTLessThan(currNode, toComp) && !BSTLessThan(toComp, currNode)){
            return false;
        }

        // moving to the currNode pointer accordingly to reach a leaf, so as to insert the node accordingly.
        else if(!BSTLessThan(currNode, toComp)){
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
    if(isLeft){
        TreeNode* newNode = new TreeNode(jrnyCode, price, nullptr, nullptr, parent);
        updateBSTParentChild(parent, newNode, isLeft);

        // actually just update heights.
        updateBalance(parent->left);
    }
    else{
        TreeNode* newNode = new TreeNode(jrnyCode, price, nullptr, nullptr, parent);
        updateBSTParentChild(parent, newNode, isLeft);

        // actually just update heights.
        updateBalance(parent->right);
    }

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

	//--------------------------------------------------------------------------------//

    TreeNode* toComp = new TreeNode(jrnyCode, 0); //
	TreeNode* currNode = root;
    while(currNode!= nullptr){
        if(!BSTLessThan(currNode, toComp) && !BSTLessThan(toComp, currNode)){ // comparing for equality
			delete toComp;
            return currNode->getPrice();
        }

        // if currentNode's price > price current moves left.
        else if(!BSTLessThan(currNode, toComp)){
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

	// REMEMBER to update the height of appropriate nodes in the tree
	// after a successful deletion.

	// We use "return true" below to enable compilation.  Change this as you
	// see fit.
    //----------------------------------------------------------------------//


	TreeNode* toComp = new TreeNode(jrnyCode, 0);
	TreeNode* currNode = root;
    TreeNode* parent = nullptr;

    // bool variable to ckeck the currNode is the left or right child of its parent, which is used to check whether the 
    // node which has to be deleted comes from the left parent or from the right parent.
    bool isLeft = false;
    while(currNode!= nullptr){
        if(!BSTLessThan(currNode, toComp) && !BSTLessThan(toComp, currNode)){ // when jrny code matches
			
            if(currNode->right == nullptr && currNode->left == nullptr){ // both child null

                // handling the case fo root separately.
                if(parent == nullptr){
                    root = nullptr;
                    delete currNode;
                }
                else if(isLeft){
                    delete currNode;
                    parent->left = nullptr;
					updateBalance(parent);
                }
                else if(!isLeft){
                    delete currNode;
                    parent->right = nullptr;
					updateBalance(parent);
                }
            }
            else if(currNode->left != nullptr && currNode->right == nullptr){ // one child null

            // handling the case fo root separately.
                if(parent == nullptr){
                    root = currNode->left;
					root->parent = nullptr;
                    delete currNode;
                }
                else if(isLeft){
                    updateBSTParentChild(currNode->left, parent, isLeft);
                    delete currNode;
					updateBalance(parent);
                }
                else if(!isLeft){
                    updateBSTParentChild(currNode->left, parent, isLeft);
                    delete currNode;
					updateBalance(parent);
                }
            }
            else if(currNode->right != nullptr && currNode->left == nullptr){ // one child null
            
            // handling the case fo root separately.
                if(parent == nullptr){
                    root = currNode->right;
					root->parent = nullptr;
                    delete currNode;
                }
                else if(isLeft){
                    updateBSTParentChild(currNode->right, parent, isLeft);
                    delete currNode;
					updateBalance(parent);
                }
                else if(!isLeft){
                    updateBSTParentChild(currNode->right, parent, isLeft);
                    delete currNode;
					updateBalance(parent);
                }
            }
            else { // both child not null

                // finding the predecesor to remove accordingly.
                TreeNode* pred = predecesor(currNode);
                int a = pred->getPrice();
                int b = pred->getJrnyCode();
                remove(b);
                currNode->getPrice() = a;
                currNode->getJrnyCode() = b;
            }

            return true;
        }
        // shifting the currNode pointer accordingly, if currentNode doesn't match.
        else if(!BSTLessThan(currNode, toComp)){
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
    return false;
}

TreeNode* BST::predecesor(TreeNode* node){

    // getting the rightmost child of the leftsubtree, since left child is not null.
    if(node->left){
        TreeNode* currNode = node;
        currNode = currNode->left;
        while(currNode->right!=nullptr){
            currNode = currNode->right;
        }
        return currNode;
    }
    // actually this never get called because pred() gets called only when both child of node is not null so...
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